#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <ev.h>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>

#include "global.h"

#define MAXLEN 1023

unsigned int topo_buffer[256*18+3];
char phone_buf[11]={0};
unsigned int sensor=0;
int sockfd;
struct timeval tv;
fd_set sds;
static int flag_bind=0;

bool Server_GetZigBeeNwkInfo(int fd);

bool Server_GetZigBeeNwkTopo(int fd);
bool Server_GetTempHum(int fd);

bool Server_SetSensorStatus(int fd,unsigned int addr,unsigned int state);

int Server_GetRfidId(int fd);
int Server_GetGPRSSignal(int fd);
bool Server_SendGprsMessage(int fd,unsigned int *phone,unsigned int sensor);
int socket_init(char** argv);
void accept_callback(struct ev_loop *loop, ev_io *w, int revents);
void recv_callback(struct ev_loop *loop, ev_io *w, int revents);
void write_callback(struct ev_loop *loop, ev_io *w, int revents);
void gprs_send();

void init_int_queue(PUINT_QUEUE pQ)
{
    pQ->head = 0;
    pQ->tail = 0;
    //pQ->lock =  SPIN_LOCK_UNLOCKED;
    pthread_mutex_init(&pQ->lock, NULL);
}
void enqueue_int_queue(PUINT_QUEUE pQ, unsigned int c)
{
    pthread_mutex_lock(&pQ->lock);
    printf("________________enqueue_int_queue: %d\n",c);
    if((pQ->head + 1) % UINT_QUEUE_SIZE == pQ->tail) // queue full
    {
        pQ->tail = (pQ->tail + 1 ) % UINT_QUEUE_SIZE;
    }
    pQ->data[pQ->head] = c;
    pQ->head = (pQ->head + 1 ) % UINT_QUEUE_SIZE;
    pthread_mutex_unlock(&pQ->lock);
    return;
}
int main(int argc ,char** argv)
{
	int listen;
	ev_io ev_io_watcher;



        printf("flag_bind%d",flag_bind);
	signal(SIGPIPE,SIG_IGN);
	printf("start com monitor\n");	
	listen=socket_init(argv);
        printf("flag_bind%d",flag_bind);
        if(flag_bind)
        {

            ComPthreadMonitorStart();

        }
        init_int_queue(&pQueue);

	//struct ev_loop *loop = ev_loop_new(EVBACKEND_EPOLL);
	struct ev_loop *loop = ev_default_loop(EVBACKEND_EPOLL);
	ev_io_init(&ev_io_watcher, accept_callback,listen, EV_READ);
	ev_io_start(loop,&ev_io_watcher); 
	ev_loop(loop,0);
        ev_loop_destroy(loop);
        if(flag_bind)
        {

            ComPthreadMonitorExit();

        }

        printf("exit com monitor\n");

	return 0;

}

int socket_init(char** argv)
{

	struct sockaddr_in my_addr;
	int listener;
	//socklen_t len;
	unsigned int myport, lisnum;
	
	if (argv[1])
	{
		printf("argv1%s\n",argv[1]);
		myport = atoi(argv[1]);
	}
	else
		myport = 7838;

	if (argv[2])
	{	
		printf("argv1%s\n",argv[2]);
		lisnum = atoi(argv[2]);
	}
	else
		lisnum = 2;
	
	if ((listener = socket(PF_INET, SOCK_STREAM, 0)) == -1) 
	{
                flag_bind=0;
                perror("socket");
		exit(1);
	} 
	else
	{
            printf("flag_bind=1\n");
                flag_bind=1;
		printf("SOCKET CREATE SUCCESS!\n");
	}
	//setnonblocking(listener);
	int so_reuseaddr=1;
	setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&so_reuseaddr,sizeof(so_reuseaddr));
	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_family = PF_INET;
	my_addr.sin_port = htons(myport);
	if(argv[3])
		my_addr.sin_addr.s_addr = inet_addr(argv[3]);
	else 
		my_addr.sin_addr.s_addr = INADDR_ANY;


	if (bind(listener, (struct sockaddr *) &my_addr, sizeof(struct sockaddr))== -1) 
	{
		perror("bind error!\n");
		exit(1);
	} 
	else
	{
		printf("BIND SUCCESS\n");
		//printf("IP BIND SUCCESS,IP:%s\n",my_addr.sin_addr.s_addr);
	}

	if (listen(listener, lisnum) == -1) 
	{
		perror("listen error!\n");
		exit(1);
	} 
	else
	{
		printf("LISTEN SUCCESS,PORT:%d\n",myport);
	}
	return listener;
}

void accept_callback(struct ev_loop *loop, ev_io *w, int revents)
{
	int newfd;
	struct sockaddr_in their_addr;
	socklen_t addrlen = sizeof(struct sockaddr);
	ev_io* accept_watcher=malloc(sizeof(ev_io));
	
	while ((newfd = accept(w->fd, (struct sockaddr *)&their_addr, &addrlen)) < 0)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK) 
		{
		//these are transient, so don't log anything.
			continue; 
		}
		else
		{
			printf("accept error.[%s]\n", strerror(errno));
			break;
		}
	}
	printf("Got connection from %s\n",inet_ntoa(their_addr.sin_addr));
	ev_io_init(accept_watcher,recv_callback,newfd,EV_READ);
	//ev_io_start(loop,accept_watcher);
	//ev_io_init(accept_watcher,write_callback,newfd,EV_WRITE);
        ev_io_start(loop,accept_watcher);
	printf("accept callback : fd :%d\n",accept_watcher->fd);

}

void recv_callback(struct ev_loop *loop, ev_io *w, int revents)
{
    printf("\nrecv_callback:\n");

    if(gSend==1)
    {
        gSend=0;
        unsigned int buffer[4]={0};
        buffer[0]=0x26;
        buffer[1]=0x06;

        buffer[3]='\n';


        buffer[2]=1;
        write(w->fd, (unsigned int*)(&buffer), sizeof(buffer));

    }

    unsigned int buffer[15]={0};
    unsigned int temp;
    int i=0;
    tv.tv_sec=60;
    tv.tv_usec=0;
    FD_ZERO(&sds);
    FD_SET(w->fd, &sds);
    int ret = select((1+w->fd), &sds, NULL, NULL, &tv);
    if(ret >0)
    {
        //printf("server select wait...\n");
        if (FD_ISSET(w->fd, &sds))
        {
            //printf("server FD_ISSET...\n");
            int len=0;
            len=recv(w->fd,&buffer[i],sizeof(unsigned int),0);
            if(len>0)
            {
                //printf("server buffer[i]=%d\n",buffer[i]);
            while(buffer[i]!=0x0A)
            {
               i++;
               len=recv(w->fd,&buffer[i],sizeof(unsigned int),0);
               //printf("server buffer[i]=%d\n",buffer[i]);
            }
            if(buffer[0]==0x15)
            {
                temp=buffer[1];
                switch(temp)
                {
                case 0x01:

                        printf("COMMAND:-------TOPOINFO--------:\n");
                        Server_GetZigBeeNwkTopo(w->fd);
                        break;
                case 0x02:

                        printf("COMMAND:-------GetZigBeeNwkInfo--------:\n");
                        Server_GetZigBeeNwkInfo(w->fd);
                        break;
                case 0x03:

                        printf("CMOMAND:-------SET_SENSOR_STATUS:--------:\n");//
                        Server_SetSensorStatus(w->fd,buffer[2],buffer[3]);
                        break;
                case 0x04:

                        printf("COMMAND:-------GetRfidId--------:\n");
                        Server_GetRfidId(w->fd);
                        break;
                case 0x05:

                        printf("COMMAND:-------GetTempHum--------:\n");
                        Server_GetTempHum(w->fd);
                        break;
                case 0x06:

                        printf("COMMAND:-------SendGprsMessage--------:\n");//
                        Server_SendGprsMessage(w->fd,&buffer[2],buffer[13]);
                        break;
                case 0x07:

                        printf("COMMAND:-------get GPRSSignal--------:\n");
                        Server_GetGPRSSignal(w->fd);
                        break;
                case 0x08:

                        printf("COMMAND:-------clear intrupt--------:\n");
                        gIntLock=0;
                        break;
                default:
                        printf("error COMMAND\n");
                        break;

                }
            }
            else
            {
                printf("other protrol.\n");
            }
        }
            else if(len ==0)
            {
                    printf("remote socket closed!socket fd: %d\n",w->fd);
                    close(w->fd);
                    ev_io_stop(loop, w);
                    free(w);
                    return;
            }
            else
            {
                    if(errno == EAGAIN ||errno == EWOULDBLOCK)
                    {
                        printf("errno == EAGAIN ||errno == EWOULDBLOCK\n");
                            //goto loop;
                    }
                    else
                    {
                            printf("ret :%d ,close socket fd : %d\n",ret,w->fd);
                            close(w->fd);
                            ev_io_stop(loop, w);
                            free(w);
                            return;
                    }
            }
        }
        else{
                           printf("not  server fd.\n");
                }
    }
    else if(ret == 0){
            printf("server read wait timeout!!!\n");

    }
    else{// ret <0
            printf("server select error.\n");
            //perror(ret);
    }



}


void write_callback(struct ev_loop *loop, ev_io *w, int revents)
{


	int fd=w->fd;
	ev_io_stop(loop,  w);

}

bool Server_GetZigBeeNwkInfo(int fd){
	printf("Server:___________GetZigBeeNwkInfo\n");

        unsigned int buffer[9]={0};
        buffer[0]=0x26;
        buffer[1]=0x02;

        buffer[8]='\n';

        struct NwkDesp *pNwkDesp2;
        //bool netinfo
        pNwkDesp2 =GetZigBeeNwkDesp();
        buffer[2]=pNwkDesp2->panid;
        buffer[3]=pNwkDesp2->channel;

        buffer[4]=pNwkDesp2->channel>>16;
        printf("pNwkDesp2->channel=%ld %d %d %ld\n",pNwkDesp2->channel,pNwkDesp2->channel>>16,pNwkDesp2->channel,pNwkDesp2->channel>>16+pNwkDesp2->channel);
        buffer[5]=pNwkDesp2->maxchild;
        buffer[6]=pNwkDesp2->maxdepth;
        buffer[7]=pNwkDesp2->maxrouter;

        int len=write(fd, (unsigned int*)(&buffer), sizeof(buffer));
        if(len<=0)
        {

            return FALSE;
        }


        return TRUE;

}


bool Server_SetSensorStatus(int fd,unsigned int addr,unsigned int state)
{
    SetSensorStatus(addr,state);
    printf("Server:Server_SetSensorStatus end");
    return TRUE;

}



bool Server_GetZigBeeNwkTopo(int fd){
    struct NodeInfo* pNodeNwkTopoInfo ,*q;

    pNodeNwkTopoInfo=GetZigBeeNwkTopo();

    printf("gNwkStatusFlag=%d\n",gNwkStatusFlag);
    topo_buffer[0]=0x26;
    topo_buffer[1]=0x01;
    if(gNwkStatusFlag)
    {
        if(pNodeNwkTopoInfo==NULL)
        {
            topo_buffer[2]=0x02;//for online,but NULL
            topo_buffer[3]=0x0A;
            write(fd, (unsigned int*)(&topo_buffer), sizeof(unsigned int)*4);
        }
        else{
            int i=0,j=0;
            while(pNodeNwkTopoInfo!=NULL)
            {
               topo_buffer[2+18*i]=pNodeNwkTopoInfo->devinfo->nwkaddr;
               printf("cliect topo_buffer[%d]=%d\n",2+18*i,topo_buffer[2+18*i]);
               topo_buffer[3+18*i]=pNodeNwkTopoInfo->devinfo->macaddr[0];
               //printf("cliect topo_buffer[%d]=%d\n",3+18*i,topo_buffer[3+18*i]);
               topo_buffer[4+18*i]=pNodeNwkTopoInfo->devinfo->macaddr[1];
               //printf("cliect topo_buffer[%d]=%d\n",4+18*i,topo_buffer[4+18*i]);
               topo_buffer[5+18*i]=pNodeNwkTopoInfo->devinfo->macaddr[2];
               //printf("cliect topo_buffer[%d]=%d\n",5+18*i,topo_buffer[5+18*i]);
               topo_buffer[6+18*i]=pNodeNwkTopoInfo->devinfo->macaddr[3];
               //printf("cliect topo_buffer[%d]=%d\n",6+18*i,topo_buffer[6+18*i]);
               topo_buffer[7+18*i]=pNodeNwkTopoInfo->devinfo->macaddr[4];
               //printf("cliect topo_buffer[%d]=%d\n",7+18*i,topo_buffer[7+18*i]);
               topo_buffer[8+18*i]=pNodeNwkTopoInfo->devinfo->macaddr[5];
               //printf("cliect topo_buffer[%d]=%d\n",8+18*i,topo_buffer[8+18*i]);
               topo_buffer[9+18*i]=pNodeNwkTopoInfo->devinfo->macaddr[6];
               //printf("cliect topo_buffer[%d]=%d\n",9+18*i,topo_buffer[9+18*i]);
               topo_buffer[10+18*i]=pNodeNwkTopoInfo->devinfo->macaddr[7];
               //printf("cliect topo_buffer[%d]=%d\n",10+18*i,topo_buffer[10+18*i]);
               topo_buffer[11+18*i]=pNodeNwkTopoInfo->devinfo->depth;
               //printf("cliect topo_buffer[%d]=%d\n",11+18*i,topo_buffer[11+18*i]);
               topo_buffer[12+18*i]=pNodeNwkTopoInfo->devinfo->devtype;
               //printf("cliect topo_buffer[%d]=%d\n",12+18*i,topo_buffer[12+18*i]);
               topo_buffer[13+18*i]=pNodeNwkTopoInfo->devinfo->parentnwkaddr;
               //printf("cliect topo_buffer[%d]=%d\n",13+18*i,topo_buffer[13+18*i]);
               topo_buffer[14+18*i]=pNodeNwkTopoInfo->devinfo->sensortype;
               //printf("cliect topo_buffer[%d]=%d\n",14+18*i,topo_buffer[14+18*i]);
               topo_buffer[15+18*i]=pNodeNwkTopoInfo->devinfo->sensorvalue;
               //printf("cliect topo_buffer[%d]=%d\n",15+18*i,topo_buffer[15+18*i]);
               topo_buffer[16+18*i]=pNodeNwkTopoInfo->devinfo->sensorvalue>>16;
               //printf("cliect topo_buffer[%d]=%d\n",16+18*i,topo_buffer[16+18*i]);
               topo_buffer[17+18*i]=pNodeNwkTopoInfo->devinfo->status;
               printf("cliect topo_buffer[%d]=%d\n",17+18*i,topo_buffer[17+18*i]);
               topo_buffer[18+18*i]=pNodeNwkTopoInfo->row;
               //printf("cliect topo_buffer[%d]=%d\n",18+18*i,topo_buffer[18+18*i]);
               topo_buffer[19+18*i]=pNodeNwkTopoInfo->num;
               //printf("cliect topo_buffer[%d]=%d\n",19+18*i,topo_buffer[19+18*i]);
               pNodeNwkTopoInfo=pNodeNwkTopoInfo->next;
               j=i;
               i++;
            }
            topo_buffer[20+18*j]='\n';
            //printf("cliect topo_buffer[%d]=%d\n",20+18*j,topo_buffer[20+18*j]);
            write(fd, (unsigned int*)(&topo_buffer), sizeof(unsigned int)*(20+18*j+1));
        }
    }
    else{

        topo_buffer[2]=0x01;//for offline
        topo_buffer[3]='\n';
        write(fd, (unsigned int*)(&topo_buffer), sizeof(unsigned int)*4);
    }


	return TRUE;
}
bool Server_GetTempHum(int fd){
	printf("Server:___________GetTempHum\n");

        unsigned int buffer[5]={0};
        buffer[0]=0x26;
        buffer[1]=0x05;

        buffer[4]='\n';

        unsigned long int temp=GetBlueToothData();
        buffer[2]=temp;
        buffer[3]=temp>>16;

        int len=write(fd, (unsigned int*)(&buffer), sizeof(buffer));
        if(len<=0)
        {

            return FALSE;
        }


        return TRUE;
}
int Server_GetRfidId(int fd){
    printf("Server:___________GetRfidId\n");

    unsigned int buffer[5]={0};
    buffer[0]=0x26;
    buffer[1]=0x04;

    buffer[4]='\n';

    unsigned long int id= GetRFIDData();
    buffer[2]=id;
    buffer[3]=id>>16;

    int len=write(fd, (unsigned int*)(&buffer), sizeof(buffer));
    if(len<=0)
    {

        return 0;
    }


    return 1;

}
int Server_GetGPRSSignal(int fd){
    printf("Server:___________GetGPRSSignal\n");
    unsigned int buffer[4]={0};
    buffer[0]=0x26;
    buffer[1]=0x07;

    buffer[3]='\n';

    buffer[2]=gSim;

    int len=write(fd, (unsigned int*)(&buffer), sizeof(buffer));
    if(len<=0)
    {

        return 0;
    }


    return 1;
}
bool Server_SendGprsMessage(int fd,unsigned int *phone,unsigned int sensor){
    //printf("@@@@@@@@@@@@@@@@@@@@@Server:___________SendGprsMessage@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");


    int i=0;

    for(i=0;i<11;i++)
    {
    phone_buf[i]=*(phone+i);
    printf("%c",*(phone+i));

    }

    //gprs_msg(phone_buf,sensor);
    enqueue_int_queue(&pQueue,sensor);





    return TRUE;
}
void gprs_send()
{

}
