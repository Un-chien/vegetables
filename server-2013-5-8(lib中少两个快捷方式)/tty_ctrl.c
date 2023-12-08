#include "tty.h"
#include "global.h"
#include "zigbee_ctrl.h"
#include "gprs.h"

pthread_mutex_t mutex;

volatile int STOP=FALSE;

int zb_fd;
int bt_fd;
int rf_fd;
int gprs_fd;


#define ZB_BAUDRATE B115200
#define BT_BAUDRATE B9600
#define RF_BAUDRATE B9600
#define GPRS_BAUDRATE B9600

struct sigaction sa;
pthread_t th_kb, th_rev, th_send,bt_rev,rf_rev,msg_rev;
void * retval;


unsigned char gNwkStatusFlag;
unsigned char gFrameValidFlag;
unsigned char gCmdValidFlag;
unsigned char gIntLock;

NwkDesp gNwkDesp;
DeviceInfo gDeviceInfo;
SensorDesp gSensorDesp;

void ProcessNwkConnectRSP( unsigned char  *_pData , unsigned char _len );
void ProcessGetNwkDespRSP( unsigned char  *_pData , unsigned char _len );
void ProcessGetNwkTopoRSP( unsigned char  *_pData , unsigned char _len  );
void ProcesssSetSensorModeRSP( unsigned char  *_pData , unsigned char _len );
void ProcessGetSensorStatusRSP( unsigned char  *_pData , unsigned char _len );
void ProcessSetSensorStatusRSP( unsigned char  *_pData , unsigned char _len );
void ProcessGetDevInfoRSP( unsigned char  *_pData , unsigned char _len );
void ProcessRptNodeOutRSP( unsigned char  *_pData , unsigned char _len );

unsigned int gBTStatusFlag;
unsigned long int gBTDatas;
unsigned long int gRFDatas;
//int msgid;
//struct msgbuf msg_rbuf;

unsigned char Data_CalcFCS( unsigned char  *msg_ptr, unsigned char  len )
{
      unsigned char  x;
      unsigned char  xorResult;

      xorResult = 0;

      for ( x = 0; x < len; x++, msg_ptr++ )
        xorResult = xorResult ^ *msg_ptr;

      return ( xorResult );
}

int CMD_CalcFCS( unsigned char  *msg_ptr, unsigned char  len )
{
	unsigned int  cmd;
	unsigned int flag = 0;

	cmd = BUILD_UINT16( msg_ptr[1], msg_ptr[0] );
	//printf("cmd=0x%x\n",cmd);
	printf("cmd calcfcs.\n");
	
	//Process the contents of the message
	switch ( cmd )
	{	  
	  case SPI_CMD_GET_NWK_TOPO_RSP:
	    flag = 1;
	    break;

	  case SPI_CMD_NWK_CONNECT_RSP:
	    flag = 1;
	    break;

	  case SPI_CMD_GET_NWK_DESP_RSP:
	    flag = 1;
	    break;

	  case SPI_CMD_SET_SENSOR_MODE_RSP:
	    flag = 1;
	    break;

	  case SPI_CMD_GET_SENSOR_STATUS_RSP:
	    flag = 1;
	    break;

	  case SPI_CMD_SET_SENSOR_STATUS_RSP:
	    flag = 1;
	    break;

	  case SPI_CMD_GET_DEVINFO_RSP:
	    flag = 1;
	    break;

	  case SPI_CMD_RPT_NODEOUT_RSP:
	    flag = 1;
	    break;	  	
		
	  default:
	    break;
	}

	return flag;
}

int Data_PackageParser( unsigned char  *_pData, unsigned char  len )
{
	unsigned int  cmd;

	cmd = BUILD_UINT16( _pData[2], _pData[1] );
	printf("cmd=0x%x\n",cmd);
	
	//Process the contents of the message
	switch ( cmd )
	{	  
	  case SPI_CMD_NWK_CONNECT_RSP:
	    ProcessNwkConnectRSP( _pData, len );
	    break;

	  case SPI_CMD_GET_NWK_DESP_RSP:
	    ProcessGetNwkDespRSP( _pData, len );
	    break;

	  case SPI_CMD_GET_NWK_TOPO_RSP:	  	
	    ProcessGetNwkTopoRSP( _pData, len );				
	    break;

	  case SPI_CMD_SET_SENSOR_MODE_RSP:
	    ProcesssSetSensorModeRSP( _pData, len );
	    break;

	  case SPI_CMD_GET_SENSOR_STATUS_RSP:
	    ProcessGetSensorStatusRSP( _pData, len );
	    break;

	  case SPI_CMD_SET_SENSOR_STATUS_RSP:
	    ProcessSetSensorStatusRSP( _pData, len );
	    break;

	  case SPI_CMD_GET_DEVINFO_RSP:
	    ProcessGetDevInfoRSP( _pData, len );
	    break;

	  case SPI_CMD_RPT_NODEOUT_RSP:
	    ProcessRptNodeOutRSP( _pData, len );
	    break;	  	
		
	  default:
	    break;
	}

	return TRUE;

}


void CMD_NwkDetect(void)
{

	pthread_mutex_lock(&mutex);	

	unsigned char txbuff[5]={0,};
	//unsigned char rxbuff[11];

	//int i=0,j=0;

	txbuff[0]=SOP_VALUE;// SOP
	txbuff[1]=0x00;// CMDH
	txbuff[2]=0x50;// CMDL
	txbuff[3]=0x00;// LEN

	txbuff[4]=Data_CalcFCS(txbuff+1, (unsigned char)3);// FCS
	printf("\ncmd nwk deteck\n");
	tty_write(zb_fd,txbuff,5);


	pthread_mutex_unlock(&mutex);

#if 0
    //发送命令
    while ((i++)< ITIMEOUT) {
            tty_write(txbuff,10);
            //预接收11个字节的返回数据信息
            while(tty_read(rxbuff,10) < 0 && (j++) < JTIMEOUT);
            //对接收到的数据进行预处理
            if((rxbuff[0]!= 0xBB) || (rxbuff[3] != 0x00 || rxbuff[4] != cmd)){ //判断文件头，以及机号
                    //验证错误
                    continue;
            }else{
                    //输入超时处理
                    *rx_param = rxbuff[5];//传递参数到上层
                    break;
            }
    }

    return (i == ITIMEOUT+1)?0:1;
#endif
}

void CMD_GetNwkDesp(void)
{
	pthread_mutex_lock(&mutex);	

	unsigned char txbuff[5]={0,};

	txbuff[0]=SOP_VALUE;// SOP
	txbuff[1]=0x00;// CMDH
	txbuff[2]=0x51;// CMDL
	txbuff[3]=0x00;// LEN

	txbuff[4]=Data_CalcFCS(txbuff+1, (unsigned char)3);// FCS
	tty_write(zb_fd,txbuff,5);

	pthread_mutex_unlock(&mutex);	
}

void CMD_SetSensorWorkMode(/*unsigned int nwkaddr,*/unsigned char Mode)
{

	pthread_mutex_lock(&mutex);	

	unsigned char txbuff[6]={0,};

	txbuff[0]=SOP_VALUE;// SOP
	txbuff[1]=0x00;// CMDH
	txbuff[2]=0x53;// CMDL
	txbuff[3]=0x01;// LEN
	txbuff[4]=Mode;// LEN

	txbuff[5]=Data_CalcFCS(txbuff+1, (unsigned char)4);// FCS
	tty_write(zb_fd,txbuff,6);

	pthread_mutex_unlock(&mutex);	
}

void CMD_SetSensorStatus(unsigned int nwkaddr, unsigned  int status)
{
	pthread_mutex_lock(&mutex);	
	
	unsigned char txbuff[8]={0,};
	unsigned char addr[2];

	addr[0]=(unsigned char)HI_UINT16(nwkaddr);
	addr[1]=(unsigned char)LO_UINT16(nwkaddr);

	txbuff[0]=SOP_VALUE;// SOP
	txbuff[1]=0x00;// CMDH
	txbuff[2]=0x55;// CMDL
	txbuff[3]=0x03;// LEN
	txbuff[4]=addr[0];// nwkaddr H
	txbuff[5]=addr[1];// nwkaddr L
	txbuff[6]= status;

	txbuff[7]=Data_CalcFCS(txbuff+1, (unsigned char)6);// FCS
        //printf("\ncmd set sensor status\n");
	tty_write(zb_fd,txbuff,8);
	
	pthread_mutex_unlock(&mutex);
}

void CMD_GetSensorStatus(unsigned int nwkaddr)
{

	pthread_mutex_lock(&mutex);	

	unsigned char txbuff[7]={0,};
	unsigned char addr[2];

	addr[0]=(unsigned char)HI_UINT16(nwkaddr);
	addr[1]=(unsigned char)LO_UINT16(nwkaddr);

	txbuff[0]=SOP_VALUE;// SOP
	txbuff[1]=0x00;// CMDH
	txbuff[2]=0x54;// CMDL
	txbuff[3]=0x02;// LEN
	txbuff[4]=addr[0];// nwkaddr H
	txbuff[5]=addr[1];// nwkaddr L


	txbuff[6]=Data_CalcFCS(txbuff+1, (unsigned char)5);// FCS
        //printf("\ncmd get sensor status\n");
	tty_write(zb_fd,txbuff,7);

	pthread_mutex_unlock(&mutex);	
}

void CMD_GetZigBeeDevInfo(unsigned int nwkaddr)
{

	pthread_mutex_lock(&mutex);	

	unsigned char txbuff[7]={0,};
	unsigned char addr[2];

	addr[0]=(unsigned char)HI_UINT16(nwkaddr);
	addr[1]=(unsigned char)LO_UINT16(nwkaddr);

	txbuff[0]=SOP_VALUE;// SOP
	txbuff[1]=0x00;// CMDH
	txbuff[2]=0x56;// CMDL
	txbuff[3]=0x02;// LEN
	txbuff[4]=addr[0];// nwkaddr H
	txbuff[5]=addr[1];// nwkaddr L


	txbuff[6]=Data_CalcFCS(txbuff+1, (unsigned char)5);// FCS
        //printf("\ncmd get dev info\n");
	tty_write(zb_fd,txbuff,7);

	pthread_mutex_unlock(&mutex);	
}

void CMD_GetZigBeeNwkTopo(void)
{

	pthread_mutex_lock(&mutex);	

	unsigned char txbuff[5]={0,};

	txbuff[0]=SOP_VALUE;// SOP
	txbuff[1]=0x00;// CMDH
	txbuff[2]=0x52;// CMDL
	txbuff[3]=0x00;// LEN

	txbuff[4]=Data_CalcFCS(txbuff+1, (unsigned char)3);// FCS
        //printf("\ncmd get nwk topologic\n");
	tty_write(zb_fd,txbuff,5);

	pthread_mutex_unlock(&mutex);
}


void ProcessNwkConnectRSP( unsigned char  *_pData , unsigned char _len)
{
	printf("cmd:nwk connect rsp\n");
	//gNwkStatusFlag = _pData[3+_len];
	pthread_mutex_lock(&mutex);	
	gNwkStatusFlag = 0x01;
        //printf("gNwkStatusFlag=0x%x\n", gNwkStatusFlag);
	pthread_mutex_unlock(&mutex);

	return;		
}

void ProcessGetNwkDespRSP( unsigned char  *_pData , unsigned char _len )
{
        //printf("cmd:get nwk desp rsp\n");
	unsigned int panid;
	unsigned long int channel;

	pthread_mutex_lock(&mutex);	

	panid = BUILD_UINT16(_pData[5], _pData[4]);
	channel = BUILD_UINT32(_pData[9], _pData[8], _pData[7], _pData[6]);
	
	gNwkDesp.panid = panid;
	gNwkDesp.channel = channel;
	gNwkDesp.maxchild = _pData[10];
	gNwkDesp.maxdepth = _pData[11];	
	gNwkDesp.maxrouter =_pData[12];

        /*printf("gNwkDesp.panid=0x%x\n", gNwkDesp.panid);
	printf("gNwkDesp.channel=0x%lx\n", gNwkDesp.channel);
	printf("gNwkDesp.maxchild=0x%x\n", gNwkDesp.maxchild);
	printf("gNwkDesp.maxdepth=0x%x\n", gNwkDesp.maxdepth);
        printf("gNwkDesp.maxrouter=0x%x\n", gNwkDesp.maxrouter);*/

	pthread_mutex_unlock(&mutex);	

	return;	
}

void ProcessGetNwkTopoRSP( unsigned char  *_pData , unsigned char _len  )
{
        //printf("cmd:get nwk topo rsp\n");
	int i;
	unsigned int  nwkaddr;
	unsigned char  macaddr[8];
	unsigned char  depth;
	unsigned char  devtype;
	unsigned int  parentnwkaddr;
	unsigned char  sensortype;
	unsigned long int  sensorvalue;
	unsigned char  status;

	pthread_mutex_lock(&mutex);

	if((_pData[3])==0x01){// cmd ack pakage. not real datapakage.
		pthread_mutex_unlock(&mutex);		
		return;
	}	

	nwkaddr = BUILD_UINT16(_pData[5], _pData[4]);
	for(i=0; i<8; i++){
		macaddr[i] = _pData[i+6];
	}
	depth = _pData[14];
	devtype = _pData[15];
	parentnwkaddr = BUILD_UINT16(_pData[17], _pData[16]);
	sensortype = _pData[18];
	sensorvalue = BUILD_UINT32(_pData[22], _pData[21], _pData[20], _pData[19]);	

	gDeviceInfo.nwkaddr = nwkaddr;
	for(i=0; i<8; i++){
		gDeviceInfo.macaddr[i] = macaddr[i];
	}
	gDeviceInfo.depth = depth;
	gDeviceInfo.devtype = devtype;
	gDeviceInfo.parentnwkaddr = parentnwkaddr;
	gDeviceInfo.sensortype = sensortype;
	gDeviceInfo.sensorvalue = sensorvalue;
	gDeviceInfo.status = 0x01;// node status 
	
        printf("gDeviceInfo.nwkaddr=0x%x\n", gDeviceInfo.nwkaddr);

        printf("gDeviceInfo.macaddr=0x");
	for(i=0; i<8; i++){
		printf("%lx ", gDeviceInfo.macaddr[i]);
	}
        printf("\n");
	
	printf("gDeviceInfo.depth=0x%lx\n", gDeviceInfo.depth);
	printf("gDeviceInfo.devtype=0x%x\n", gDeviceInfo.devtype);
	printf("gDeviceInfo.parentnwkaddr=0x%x\n", gDeviceInfo.parentnwkaddr);
	printf("gDeviceInfo.sensortype=0x%x\n", gDeviceInfo.sensortype);
	printf("gDeviceInfo.sensorvalue0x%x\n", gDeviceInfo.sensorvalue);
        printf("gDeviceInfo.status=0x%x\n", gDeviceInfo.status);

	pNodeInfo p = DeviceNodeSearch(nwkaddr);
	if(NULL != p){// exist node nwkaddr
		printf("nwkaddr :%x exist update info.\n",nwkaddr);
		//p->devinfo = &gDeviceInfo;// update datas
		{
			p->devinfo->nwkaddr = gDeviceInfo.nwkaddr;
			
			for(i=0;i<8;i++){
				p->devinfo->macaddr[i] = gDeviceInfo.macaddr[i];
			}
			p->devinfo->depth = gDeviceInfo.depth;
			p->devinfo->devtype = gDeviceInfo.devtype;
			p->devinfo->parentnwkaddr = gDeviceInfo.parentnwkaddr;
			p->devinfo->sensortype = gDeviceInfo.sensortype;
			if((p->devinfo->sensortype) !=0 &&(gIntLock==0)){
				p->devinfo->sensorvalue = gDeviceInfo.sensorvalue;
			}
			else if((p->devinfo->sensortype) ==0){//sht11 sensor
				p->devinfo->sensorvalue = gDeviceInfo.sensorvalue;
			}
			p->devinfo->status = gDeviceInfo.status;// recover status		
		}
	}
	else if(NULL == p){// new node nwkaddr
                //printf("new nwkaddr:%x make node.\n",nwkaddr);
		pNodeInfo pp = DeviceNodeCreate(&gDeviceInfo);
		DeviceNodeAdd(pp);		
	}
        printf("node num:%x\n",DeviceNodeNum(NodeInfoHead));


	pthread_mutex_unlock(&mutex);	

}

void ProcesssSetSensorModeRSP( unsigned char  *_pData , unsigned char _len )
{
	printf("cmd:set sensor mode rsp\n");
}

void ProcessGetSensorStatusRSP( unsigned char  *_pData , unsigned char _len )
{	
        //printf("cmd:get sensor status rsp\n");
	unsigned int nwkaddr;
	unsigned char type;
	unsigned long int value;

	pthread_mutex_lock(&mutex);	

	gIntLock = 0x01;
	nwkaddr = BUILD_UINT16(_pData[5], _pData[4]);
	type = _pData[6];
	value = BUILD_UINT32(_pData[10], _pData[9], _pData[8], _pData[7]);

	pNodeInfo p = DeviceNodeSearch(nwkaddr);

	if(NULL != p){// exist node nwkaddr
                //printf("nwkaddr :%x is interrupt.\n",nwkaddr);
		//p->devinfo->sensortype;
		p->devinfo->sensorvalue = value;
	}
	else if(NULL == p){// new node nwkaddr
		printf("new nwkaddr:%x is not find.\n",nwkaddr);	
	}
	
	pthread_mutex_unlock(&mutex);	

	return;	
}

void ProcessSetSensorStatusRSP( unsigned char  *_pData , unsigned char _len )
{
	printf("cmd:set sensor status rsp\n");
}

void ProcessGetDevInfoRSP( unsigned char  *_pData , unsigned char _len )
{	
        //printf("cmd:get dev info rsp\n");
	int i;
	unsigned int  nwkaddr;
	unsigned char  macaddr[8];
	unsigned char  depth;
	unsigned char  devtype;
	unsigned int  parentnwkaddr;
	unsigned char  sensortype;
	unsigned long int  sensorvalue;
	unsigned char  status;

	pthread_mutex_lock(&mutex);

	nwkaddr = BUILD_UINT16(_pData[5], _pData[4]);
	for(i=0; i<8; i++){
		macaddr[i] = _pData[i+6];
	}
	depth = _pData[14];
	devtype = _pData[15];
	parentnwkaddr = BUILD_UINT16(_pData[17], _pData[16]);
	sensortype = _pData[18];
	sensorvalue = BUILD_UINT32(_pData[22], _pData[21], _pData[20], _pData[19]);	

	gDeviceInfo.nwkaddr = nwkaddr;
	for(i=0; i<8; i++){
		gDeviceInfo.macaddr[i] = macaddr[i];
	}
	gDeviceInfo.depth = depth;
	gDeviceInfo.devtype = devtype;
	gDeviceInfo.parentnwkaddr = parentnwkaddr;
	gDeviceInfo.sensortype = sensortype;
	gDeviceInfo.sensorvalue = sensorvalue;
	gDeviceInfo.status = 0x01;// node status 
	
        printf("gDeviceInfo.nwkaddr=0x%x\n", gDeviceInfo.nwkaddr);

	printf("gDeviceInfo.macaddr=0x");
	for(i=0; i<8; i++){
		printf("%lx ", gDeviceInfo.macaddr[i]);
	}
        printf("\n");
	
	printf("gDeviceInfo.depth=0x%lx\n", gDeviceInfo.depth);
	printf("gDeviceInfo.devtype=0x%x\n", gDeviceInfo.devtype);
	printf("gDeviceInfo.parentnwkaddr=0x%x\n", gDeviceInfo.parentnwkaddr);
	printf("gDeviceInfo.sensortype=0x%x\n", gDeviceInfo.sensortype);
	printf("gDeviceInfo.sensorvalue0x%x\n", gDeviceInfo.sensorvalue);
        printf("gDeviceInfo.status=0x%x\n", gDeviceInfo.status);

	pNodeInfo p = DeviceNodeSearch(nwkaddr);
	if(NULL != p){// exist node nwkaddr
                printf("nwkaddr :%x exist update info.\n",nwkaddr);
		//p->devinfo = &gDeviceInfo;// update datas
		{
			p->devinfo->nwkaddr = gDeviceInfo.nwkaddr;
			
			for(i=0;i<8;i++){
				p->devinfo->macaddr[i] = gDeviceInfo.macaddr[i];
			}
			p->devinfo->depth = gDeviceInfo.depth;
			p->devinfo->devtype = gDeviceInfo.devtype;
			p->devinfo->parentnwkaddr = gDeviceInfo.parentnwkaddr;
			p->devinfo->sensortype = gDeviceInfo.sensortype;
			if((p->devinfo->sensortype) !=0 &&(gIntLock==0)){
				p->devinfo->sensorvalue = gDeviceInfo.sensorvalue;
			}
			else if((p->devinfo->sensortype) ==0){
				p->devinfo->sensorvalue = gDeviceInfo.sensorvalue;
			}
			p->devinfo->status = gDeviceInfo.status;		
		}
	}
	else if(NULL == p){// new node nwkaddr
                printf("new nwkaddr:%x make node.\n",nwkaddr);
		pNodeInfo p = DeviceNodeCreate(&gDeviceInfo);
		DeviceNodeAdd(p);		
	}

        printf("node num:%x\n",DeviceNodeNum(NodeInfoHead));

	pthread_mutex_unlock(&mutex);		
}

void	ProcessRptNodeOutRSP( unsigned char  *_pData , unsigned char _len )
{
	printf("cmd:rpt node out rsp\n");
	int i;
	unsigned int  nwkaddr;

	pthread_mutex_lock(&mutex);

	nwkaddr = BUILD_UINT16(_pData[5], _pData[4]);

	pNodeInfo p = DeviceNodeSearch(nwkaddr);
	if(NULL != p){// fint out node nwkaddr
		p->devinfo->status = 0x0;

		//DeviceNodeDel(p);
		//DeviceNodeFree(p);				
		printf("find a out node and nwkaddr=%x\n",p->devinfo->nwkaddr);
	}
	
	pthread_mutex_unlock(&mutex);		

}


int ZigBeeNwkDetect(void)
{
	//unsigned char nwkstatusflag;
	CMD_NwkDetect();
	//nwkstatusflag = gNwkStatusFlag;		
	//return nwkstatusflag;
	return gNwkStatusFlag;
}


NwkDesp *GetZigBeeNwkDesp(void)
{
	CMD_GetNwkDesp();
	pNwkDesp nwkdesp = &gNwkDesp;
	
	return nwkdesp;
}

int SetSensorWorkMode(/*unsigned int nwkaddr,*/unsigned char Mode)
{
	CMD_SetSensorWorkMode(Mode);
	return 0;
}

int SetSensorStatus(unsigned int nwkaddr, unsigned  int status)
{
	CMD_SetSensorStatus(nwkaddr, status);
	return 0;
}

// do not forget free SensorDesp buffer!!!
SensorDesp *GetSensorStatus(unsigned int nwkaddr)
{
	//CMD_GetSensorStatus(nwkaddr);

	pNodeInfo p = DeviceNodeSearch(nwkaddr);
	pSensorDesp sensordesp = malloc(sizeof(*sensordesp));
	if(NULL != p){// exist node nwkaddr
                printf("nwkaddr :%x is find.\n",nwkaddr);
		sensordesp->nwkaddr = p->devinfo->nwkaddr;
		sensordesp->sensortype = p->devinfo->sensortype;
		sensordesp->sensorvalue = p->devinfo->sensorvalue;
		return sensordesp;
	}
	else if(NULL == p){// new node nwkaddr
                printf("new nwkaddr:%x is not find.\n",nwkaddr);
		//free(sensordesp);
		return NULL;
	}
	
}

DeviceInfo* GetZigBeeDevInfo(unsigned int nwkaddr)
{
	//CMD_GetZigBeeDevInfo(nwkaddr);
	int i;

	pNodeInfo p = DeviceNodeSearch(nwkaddr);
	if(NULL != p){// exist node nwkaddr
                printf("nwkaddr :%x is find.\n",nwkaddr);
		{
			return p->devinfo;
		}
	}
	else if(NULL == p){// new node nwkaddr
                printf("new nwkaddr:%x is not find.\n",nwkaddr);
		return NULL;
	}

}

NodeInfo *GetZigBeeNwkTopo(void)
{
	CMD_GetZigBeeNwkTopo();

	return NodeInfoHead;
}

void ShowNodeListInfo(pNodeInfo pNodeHead)
{
        int len,i;
	pNodeInfo p;

	len = DeviceNodeNum(NodeInfoHead);
        //printf("\r\nnodelist len=%x\n",len);
	
	for(p=NodeInfoHead; p;p=p->next){
		
                printf("\r\np->DeviceInfo.nwkaddr=0x%x\n", p->devinfo->nwkaddr);
                printf("p->DeviceInfo.macaddr=0x");
		for(i=0; i<8; i++){
			printf("%lx ", p->devinfo->macaddr[i]);
		}
		printf("\n");
		
		printf("p->DeviceInfo.depth=0x%lx\n", p->devinfo->depth);
		printf("p->DeviceInfo.devtype=0x%x\n", p->devinfo->devtype);
		printf("p->DeviceInfo.parentnwkaddr=0x%x\n", p->devinfo->parentnwkaddr);
		printf("p->DeviceInfo.sensortype=0x%x\n", p->devinfo->sensortype);
		printf("p->DeviceInfo.sensorvalue0x%x\n", p->devinfo->sensorvalue);
		printf("p->DeviceInfo.status=0x%x\n", p->devinfo->status);	
				
        }
	
}

void SigChild_Handler(int s)
{
        printf("stop!!!\n");
        STOP=TRUE;
}

unsigned long int GetBlueToothData(void)
{
	return gBTDatas;
}

unsigned int GetBlueToothStatus(void)
{
	return gBTStatusFlag;
}

void HandleBlueToothData(unsigned char  *_pData , unsigned char _len)
{
	printf("handle bluetooth data\n");
	int i;
	//unsigned long int  data;

	pthread_mutex_lock(&mutex);
	
	gBTDatas = BUILD_UINT32(_pData[3], _pData[2], _pData[1], _pData[0]);	

	pthread_mutex_unlock(&mutex);	
}

unsigned long int GetRFIDData(void)
{
	return gRFDatas;
}

void HandleRFIDData(unsigned char  *_pData , unsigned char _len)
{
	printf("handle rfid data\n");
	int i;
	//unsigned long int  data;

	pthread_mutex_lock(&mutex);
	
	gRFDatas= BUILD_UINT32(_pData[3], _pData[2], _pData[1], _pData[0]);	

	pthread_mutex_unlock(&mutex);	
}

/*--------------------------------------------------------*/
void* KeyBoardPthread(void * data)
{
        int c;
	 int i,j,len;

	//pthread_detach(pthread_self());
	 
        for (;;){		 	
                c=getchar();
          	 //printf("getchar is :%d\n",c);
                if( (c== ENDMINITERM1) | (c==ENDMINITERM2)){
                        STOP=TRUE;
                        break ;
                }
		 if(c==0x30){
		 	pNodeInfo p = DeviceNodeSearch(0x796F);
			if(NULL != p){
				printf("Find it and Del it!!!\n");
				DeviceNodeDel(p);
				DeviceNodeFree(p);
			}
			continue;
		 }
		 if(c==0x31){
			pNwkDesp nwkdesp;

			nwkdesp  = GetZigBeeNwkDesp();
			
                        printf("nwkdesp->panid=0x%x\n", nwkdesp->panid);
			printf("nwkdesp->channel=0x%lx\n", nwkdesp->channel);
			printf("nwkdesp->maxchild=0x%x\n", nwkdesp->maxchild);
			printf("nwkdesp->maxdepth=0x%x\n", nwkdesp->maxdepth);
                        printf("nwkdesp->maxrouter=0x%x\n", nwkdesp->maxrouter);
			
			continue;
		 }
		 if(c==0x32){
			pNodeInfo nodehead;
			
			nodehead  = GetZigBeeNwkTopo();
			ShowNodeListInfo(nodehead);			
			continue;
		 }
		 if(c==0x33){
			pDeviceInfo devinfo;
			
			devinfo  = GetZigBeeDevInfo(0x796F);
			if(NULL != devinfo){			
                                printf("devinfo->nwkaddr=0x%x\n", devinfo->nwkaddr);

				printf("devinfo->macaddr=0x");
				for(i=0; i<8; i++){
					printf("%lx ", devinfo->macaddr[i]);
				}
				printf("\n");
				
				printf("devinfo->depth=0x%lx\n", devinfo->depth);
				printf("devinfo->devtype=0x%x\n", devinfo->devtype);
				printf("devinfo->parentnwkaddr=0x%x\n", devinfo->parentnwkaddr);
				printf("devinfo->sensortype=0x%x\n", devinfo->sensortype);
				printf("devinfo->sensorvalue0x%x\n", devinfo->sensorvalue);
                                printf("devinfo->status=0x%x\n", devinfo->status);
			}
			continue;
		 }		 
		 
/*				
                // test tty_write cmd.
                CMD_NwkDetect();
                CMD_GetSensorStatus(0x796F);
                CMD_GetZigBeeNwkTopo();
*/		
	
        }

        return NULL;
}
/*--------------------------------------------------------*/
/* modem input handler */
void* ComRevPthread(void * data)
{

    struct timeval tv;
    fd_set rfds;

    tv.tv_sec=15;
    tv.tv_usec=0;

    int nread;
    int i,j,ret,datalen;

    unsigned char buff[BUFSIZE]={0,};
    unsigned char databuf[BUFSIZE]={0,};
    ret = 0;

    while (STOP==FALSE)
    {
        //printf("zb phread wait...\n");
        tv.tv_sec=15;
        tv.tv_usec=0;

        FD_ZERO(&rfds);
        FD_SET(zb_fd, &rfds);
        ret = select(1+zb_fd, &rfds, NULL, NULL, &tv);
        if(ret >0)
        {
            printf("zb select wait...\n");
            if (FD_ISSET(zb_fd, &rfds))
            {
                gNwkStatusFlag = 0x01;// any data of uart can flag it's status.
                nread=tty_read(zb_fd,buff, 1);
		for(;nread == -1;){
			nread=tty_read(zb_fd,buff, 1);
               	}
                printf("readlen=%d\n", nread);
                //printf("0x%x\n",buff[0]);

                if(buff[0]==0x02){
		    i=0;
		    databuf[i] = buff[0];
		    i++;
		    nread=tty_read(zb_fd,buff, 2);
                    databuf[i] = buff[0];
                    i++;
                    databuf[i] = buff[1];
                    i++;
                    //printf("%x",buff[0]);
                    //printf("%x",buff[1]);
                    //printf("\n");

                    gCmdValidFlag = CMD_CalcFCS(buff, 2);
                    if(gCmdValidFlag == 1){
			printf("cmd is valid\n");
			nread=tty_read(zb_fd,buff, 1);
			for(;nread == -1;){
                                nread=tty_read(zb_fd,buff, 1);
                        }
			//printf("readlen=%d\n", nread);
			databuf[i] = buff[0];
                        datalen = buff[0];
                        i++;
                        if(datalen!=0){
                            nread=tty_read(zb_fd,buff, datalen);
                            for(j=0;j<nread;j++,i++){
                         	databuf[i]= buff[j];
                            }
			}
                        nread=tty_read(zb_fd,buff, 1);
			for(;nread == -1;){
                       		printf("\rreadlen esc =%d", nread);
                       		//usleep(1000);
                        	nread=tty_read(zb_fd,buff, 1);
                	}
			printf("\n");
                       	//printf("readlen=%d\n", nread);
                        printf("rCalcFcs:%x\n",buff[0]);

                      	databuf[datalen+1+2+1]= Data_CalcFCS(databuf+1, datalen+3);
                        printf("cCalcFcs:%x\n",databuf[datalen+1+2+1]);
                        if(databuf[datalen+1+2+1]==buff[0]){
			    printf("CalcFcs OK\n");
                            gFrameValidFlag = 0x01;
                            gNwkStatusFlag = 0x01;// recover the coord's status.
                        }
                        else{
                            gFrameValidFlag = 0x0;
                            continue;
                      	}
                        printf("\n---ZIGBEE DATA:");
                        for(j=0;j<(datalen+1+2+1+1);j++){
                      	    printf("%-4x",databuf[j]);
                        }
                        printf("\n");

                        if(gFrameValidFlag == 0x01){
                            Data_PackageParser(databuf, datalen+1+2+1);
                        }
		    }

           	}
            }
            else{
            	printf("not tty zb_fd.\n");
            }
        }
        else if(ret == 0){
       	    printf("zb read wait timeout!!!\n");
            gNwkStatusFlag = 0x00;
            DeviceNodeDestory();
        }
        else{// ret <0
                printf("zb select error.\n");
                //perror(ret);
        }

    }

    printf("exit from reading zb com\n");
    return NULL;
}

/*--------------------------------------------------------*/
void* ComSendPthread(void * data)
{
        printf("zb send com cmd\n");
		
	//pthread_detach(pthread_self());
        while (STOP==FALSE)
        {
           	//CMD_NwkDetect();
           	CMD_GetZigBeeNwkTopo();
		usleep(6000);
               //usleep(600000);
		//usleep(600000);
		//usleep(600000);
               //usleep(600000);
		//usleep(600000);
		//usleep(600000);
               //usleep(600000);
	
        }

        return NULL; /* wait for child to die or it will become a zombie */
}

void* BlueToothRevPthread(void * data)
{
    printf("bluetooth rev pthread.\n");

    struct timeval tv;
    fd_set rfds;

    tv.tv_sec=15;
    tv.tv_usec=0;

    int nread;
    int i,j,ret,datalen;

    unsigned char buff[BUFSIZE]={0,};
    unsigned char databuf[BUFSIZE]={0,};
    ret = 0;
		
	//pthread_detach(pthread_self());
        while (STOP==FALSE)
        {
                //printf("bt phread wait...\n");
		
	        tv.tv_sec=10;
	        tv.tv_usec=0;
			
	        FD_ZERO(&rfds);
	        FD_SET(bt_fd, &rfds);
		ret = select(1+bt_fd, &rfds, NULL, NULL, &tv);

	        if(ret >0)
	        {
                    printf("bt select wait...\n");
	            if (FD_ISSET(bt_fd, &rfds))
	            {
	                gBTStatusFlag = 0x01;// any data of uart can flag it's status.
	                nread=tty_read(bt_fd,buff, 1);
			for(;nread == -1;){ 
				nread=tty_read(bt_fd,buff, 1);
			}

			if(buff[0]==0xBB){
			    nread=tty_read(bt_fd,buff, 1);
			    for(;nread == -1;){ 
                    		nread=tty_read(bt_fd,buff, 1);
                            }
	   	       	
			    if(buff[0]==0xFF){
				nread=tty_read(bt_fd,buff, 1);
				for(;nread == -1;){ 
                              	    nread=tty_read(bt_fd,buff, 1);
                        	}
	   	                	 
			    	if(buff[0]==0x06){
				    nread=tty_read(bt_fd,buff, 1);
				    for(;nread == -1;){ 
                                	nread=tty_read(bt_fd,buff, 1);
                        	    }                                          
	   	                	 	 
				    if(buff[0]==0x00){
					nread=tty_read(bt_fd,buff, 1);
					for(;nread == -1;){ 
                                	    nread=tty_read(bt_fd,buff, 1);
                        		}                
                              
	   	                	if(buff[0]==0x03){
					    nread=tty_read(bt_fd,databuf, 4);
                                            //printf("read bt datalen=%d\n", nread);
				   	    buff[nread]='\0';
                                            /*printf("\n---BLUETH DATA:");
                                            printf("0x%x",databuf[0]);
                                            printf("\t0x%x",databuf[1]);
                                            printf("\t0x%x",databuf[2]);
                                            printf("\t0x%x",databuf[3]);
                                            printf("\n");*/
					    HandleBlueToothData(databuf, 4);
	   	                	 }
	   	               	    }
								
	   	               	}
			    }						
	
	          	}

	            }
		     else{
			 	printf("not tty bt_fd.\n");
		     }		
	        }
		else if(ret == 0){
			printf("bt read wait timeout!!!\n");
			gBTStatusFlag = 0x00;
		}
		else{// ret <0
			printf("bt select error.\n");
			//perror(ret);
		}
		
	
        }
		
    	printf("exit from reading bt com\n");
        return NULL; /* wait for child to die or it will become a zombie */
}



void* RFIDRevPthread(void * data)
{
    //printf("rfid rev pthread.\n");

    struct timeval tv;
    fd_set rfds;

    tv.tv_sec=15;
    tv.tv_usec=0;

    int nread;
    int i,j,ret,datalen;

    unsigned char buff[BUFSIZE]={0,};
    unsigned char databuf[BUFSIZE]={0,};
	unsigned char bufff[BUFSIZE] = {0,};
    ret = 0;
		
	//pthread_detach(pthread_self());
        while (STOP==FALSE)
        {
                //printf("rf phread wait...\n");
		
	        tv.tv_sec=10;
	        tv.tv_usec=0;
			
	        FD_ZERO(&rfds);
	        FD_SET(rf_fd, &rfds);
		ret = select(1+rf_fd, &rfds, NULL, NULL, &tv);

	        if(ret >0)
	        {
                    //printf("rf select wait...\n");
	            if (FD_ISSET(rf_fd, &rfds))
	            {
//#if 0
	                nread=tty_read(rf_fd,buff, 6);
	                printf("readlenALD=%d\n", nread);
					//add by anld
					if(nread == 6){
	                buff[nread]='\0';				
					}else if(nread == 4){
ALD:
						nread=tty_read(rf_fd, bufff, 6);
						if(nread == 2){
							buff[4] = bufff[0];
							buff[5] = bufff[1];
							buff[6] = '\0';
						}else goto ALD;
					}	
			 databuf[0] = Data_CalcFCS(buff, 5);
			 if(databuf[0]==buff[5]){
				      HandleRFIDData(buff+1, 4);
						printf("buff[1]=0x%x\n", buff[1]);
						printf("buff[2]=0x%x\n", buff[2]);
						printf("buff[3]=0x%x\n", buff[3]);
						printf("buff[4]=0x%x\n", buff[4]);
			 }
			 else{
			 	continue;
			 }
//#endif				
	            }			
		     else{
			 	printf("not tty rf_fd.\n");
		     }				 
	        }
		else if(ret == 0){
			printf("rf read wait timeout!!!\n");
			//gBTStatusFlag = 0x00;
		}
		else{// ret <0
			printf("rf select error.\n");
			//perror(ret);
		}
		
	
        }
		
    	printf("exit from reading rf com\n");
        return NULL; /* wait for child to die or it will become a zombie */
}


void* MsgRevPthread(void )
{
int reval;
int rflags=IPC_NOWAIT|MSG_NOERROR;
while (STOP==FALSE)
{
    reval=msgrcv(msgid,&msg_rbuf,sizeof(msg_rbuf.phone),10,rflags);
if (reval==-1)
{
    printf("Read msg error!\n");
    //break;
}
else
{printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%gprs_msg%s%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",msg_rbuf.phone);
    int i=0;
    printf("msg_rbuf.phone:\n");
    for(i=0;i<12;i++)
    {
        printf("%c",msg_rbuf.phone[i]);
    }
    gprs_msg(msg_rbuf.phone, msg_rbuf.phone[11]);

}
usleep(50000);
usleep(50000);
usleep(50000);
usleep(50000);
usleep(50000);
}
}

int ComPthreadMonitorStart(void)
{
	gNwkStatusFlag = 0x0;
	gFrameValidFlag = 0x0;
	gCmdValidFlag = 0x0;
	gIntLock = 0x0;

	gBTStatusFlag =0x0;
	gBTDatas = 0x0;
	gRFDatas = 0x0;
	
        tty_init(&zb_fd, "/dev/ttySAC1",ZB_BAUDRATE);
        tty_init(&bt_fd, "/dev/ttySAC2",BT_BAUDRATE);
        tty_init(&rf_fd, "/dev/ttySAC3",RF_BAUDRATE);	
        tty_init(&gprs_fd, "/dev/ttyS0",GPRS_BAUDRATE);
		
	 gprs_init();
		
        sa.sa_handler = SigChild_Handler;
        sa.sa_flags = 0;
        sigaction(SIGCHLD,&sa,NULL); /* handle dying child */
		
	 pthread_mutex_init(&mutex, NULL);
	 
        pthread_create(&th_kb, NULL, KeyBoardPthread, 0);
        pthread_create(&th_rev, NULL, ComRevPthread, 0);
        //pthread_create(&th_send, NULL, ComSendPthread, 0);
		
	 pthread_create(&bt_rev, NULL, BlueToothRevPthread, 0);	
         pthread_create(&rf_rev, NULL, RFIDRevPthread, 0);
         //pthread_create(&msg_rev, NULL, MsgRevPthread, 0);

	return 0;
}

int ComPthreadMonitorExit(void)
{

        pthread_join(th_kb, &retval);
        pthread_join(th_rev, &retval);
        //pthread_join(th_send, &retval);

        pthread_join(bt_rev, &retval);		
        pthread_join(rf_rev, &retval);	

        //pthread_join(msg_rev, &retval);
	pthread_mutex_destroy(&mutex);
         gprs_exit();
        tty_end(zb_fd);
        tty_end(bt_fd);
        tty_end(rf_fd);		
        tty_end(gprs_fd);	
		
	DeviceNodeDestory();

	return 0;
}
