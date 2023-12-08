//##########################################################################
文件说明：
//##########################################################################
-tty.h	：底层串口读写及初始化接口头文件。
-zigbee_ctrl.h	：zigbee设备链表底层接口头文件，包括链表节点的创建、添加、删除、遍历、查找等。
-tty_ctrl.h	:	zigbee设备管理层API封装接口头文件，包括已定义的对zigbee网络及设备的管理API，上层直接使用该文件提供接口即可。

//###########################################################################
重要数据及函数说明（tty_ctrl.h）：
//数据部分
typedef struct{
    unsigned int  panid;// 16bit PANID标识
    unsigned long int  channel;//32bits 物理信道
    unsigned char  maxchild;// 最大子节点数目
    unsigned char  maxdepth;// 最大网络深度
    unsigned char  maxrouter;// 最大路由节点数目(当前层)
}NwkDesp,*pNwkDesp;
结构体说明：表示zigbee网络基本信息。

typedef struct{
    unsigned int  nwkaddr;//16bit网络地址
    unsigned char  	sensortype;// 传感器类型
    unsigned long int  sensorvalue;// 32bits 传感器数据
} SensorDesp,*pSensorDesp;
结构体说明：表示zigbee传感器节点的基本信息。
sensortype值如下：
						0：  SHT11传感器        
						1：  IRDA传感器             
						2：  SMOG传感器         
						3：  INT传感器
						4：  MICP传感器
						5：  SET传感器
						6：  无传感器


typedef struct{
    unsigned int  nwkaddr;//16bit网络地址
    unsigned char  macaddr[8];//8字节64bit物理地址
    unsigned char  depth;// 节点网络深度
    unsigned char  devtype;// 节点设备类型，0表示协调器，1表示路由器，2表示普通节点
    unsigned int  parentnwkaddr;//16bit父节点网络地址
    unsigned char  sensortype;// 当前zigbee节点的传感器类型
    unsigned long int  sensorvalue;//当前zigbee节点的传感器数据
    unsigned char  status;// 当前zigbee节点的在线状态
}DeviceInfo,*pDeviceInfo;
结构体说明：表示zigbee节点的基本信息。

struct NodeInfo{
    DeviceInfo *devinfo;// 同上
    NodeInfo *next;// 链表指针域
    unsigned char row;// 保留
    unsigned char num;// 保留
};
结构体说明：表示zigbee节点的链表。
NodeInfo *NodeInfoHead=NULL;// 全局的zigbee节点链表头。



//函数部分
int ZigBeeNwkDetect(void);
功能：检测协调器是否上电。
参数：无
返回值：整形。
0 协调器未上电，1 协调器上电。


NwkDesp *GetZigBeeNwkDesp(void);
功能：获取当前zigbee网络的基本信息。
参数：无
返回值：NwkDesp指针。


int SetSensorWorkMode(unsigned char Mode);
功能：设置zigbee网络中传感器工作模式(只针对中断型传感器)。
参数：0查询模式，1自动报告模式。
返回值：整形，0成功，非0失败。


int SetSensorStatus(unsigned int nwkaddr, unsigned  int status);
功能：设置zigbee网络中传感器状态(只针对设置型传感器)。
参数：nwkaddr 传感器节点网络地址，status 状态，0设置IO低电平，1设置IO高电平。
返回值：整形，0成功，非0失败。


SensorDesp *GetSensorStatus(unsigned int nwkaddr);
功能：获取当前zigbee网络节点的传感器状态。
参数：zigbee网络节点网络地址
返回值：SensorDesp指针。

DeviceInfo* GetZigBeeDevInfo(unsigned int nwkaddr);
功能：获取当前zigbee网络节点的设备信息。
参数：zigbee网络节点网络地址
返回值：DeviceInfo指针。


NodeInfo *GetZigBeeNwkTopo(void);
功能：获取当前zigbee网络节点的拓扑结构数据链表。
参数：无
返回值：DeviceInfo指针，即保存zigbee节点信息的链表头。



int ComPthreadMonitorStart(void);
功能：zigbee串口监听线程开启处理函数。负责创建串口监听线程，并处理相应串口数据包。
			应用程序需要调用该函数方可以更新监测zigbee网络信息及节点状态。
参数：无
返回值：整形，0成功，非0失败。


int ComPthreadMonitorExit(void);
功能：zigbee串口监听线程关闭函数。
参数：无
返回值：整形，0成功，非0失败。 