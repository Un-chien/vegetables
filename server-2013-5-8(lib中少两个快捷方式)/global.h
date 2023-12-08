#ifndef GLOBAL_H
#define GLOBAL_H

#include <sys/types.h>  /* open() */
#include <sys/stat.h>  /* open() */
#include <fcntl.h>  /* open() */
#include <unistd.h>  /* close() */
#include <string.h>  /* bzero() */
#include <sys/signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <termios.h>
//#include"sys/types.h"
#include "sys/msg.h"
//#include "unistd.h"
//#include"stdio.h"
typedef signed   char   int8;
typedef unsigned char   uint8;
typedef unsigned char   byte;
typedef signed   short  int16;
typedef unsigned short  uint16;

typedef signed   long   int32;
typedef unsigned long   uint32;


#define BUFSIZE 256
#define SOP_VALUE       0x02
#define MAX_APP_PKT_SIZE 	256


#define ENDMINITERM1 27 /* ESC to quit miniterm */
#define ENDMINITERM2 3  /*ctl +c  to quit miniterm */
//#define FALSE 0
//#define TRUE 1

#define SPI_CMD_NWK_CONNECT_REQ        			0x0050
#define SPI_CMD_NWK_CONNECT_RSP                   	0x1050
#define SPI_CMD_GET_NWK_DESP_REQ                	0x0051
#define SPI_CMD_GET_NWK_DESP_RSP                   	0x1051
#define SPI_CMD_GET_NWK_TOPO_REQ                   	0x0052
#define SPI_CMD_GET_NWK_TOPO_RSP                   	0x1052
#define SPI_CMD_SET_SENSOR_MODE_REQ             	0x0053
#define SPI_CMD_SET_SENSOR_MODE_RSP             	0x1053
#define SPI_CMD_GET_SENSOR_STATUS_REQ             0x0054
#define SPI_CMD_GET_SENSOR_STATUS_RSP             0x1054

#define SPI_CMD_SET_SENSOR_STATUS_REQ             0x0055
#define SPI_CMD_SET_SENSOR_STATUS_RSP             0x1055

#define SPI_CMD_GET_DEVINFO_REQ             0x0056
#define SPI_CMD_GET_DEVINFO_RSP             0x1056

#define SPI_CMD_RPT_NODEOUT_REQ             0x0057
#define SPI_CMD_RPT_NODEOUT_RSP             0x1057


/* takes a byte out of a uint32 : var - uint32,  ByteNum - byte to take out (0 - 3) */
#define BREAK_UINT32( var, ByteNum ) \
          (byte)((uint32)(((var) >>((ByteNum) * 8)) & 0x00FF))

#define BUILD_UINT32(Byte0, Byte1, Byte2, Byte3) \
          ((uint32)((uint32)((Byte0) & 0x00FF) \
          + ((uint32)((Byte1) & 0x00FF) << 8) \
          + ((uint32)((Byte2) & 0x00FF) << 16) \
          + ((uint32)((Byte3) & 0x00FF) << 24)))

#define BUILD_UINT16(loByte, hiByte) \
          ((uint16)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))

#define HI_UINT16(a) (((a) >> 8) & 0xFF)
#define LO_UINT16(a) ((a) & 0xFF)

#define BUILD_UINT8(hiByte, loByte) \
          ((uint8)(((loByte) & 0x0F) + (((hiByte) & 0x0F) << 4)))

#define HI_UINT8(a) (((a) >> 4) & 0x0F)
#define LO_UINT8(a) ((a) & 0x0F)


typedef struct{
    unsigned char sop;
    unsigned char cmdH;
    unsigned char cmdL;
    unsigned char len;
    unsigned char data[MAX_APP_PKT_SIZE];
    unsigned char fcs;
}AppCmdPack,*pAppCmdPack;


typedef struct NwkDesp{
    unsigned int  panid;// 16bits
    unsigned long int  channel;//32bits
    unsigned char  maxchild;
    unsigned char  maxdepth;
    unsigned char  maxrouter;
}NwkDesp,*pNwkDesp;

typedef struct{
    unsigned int  nwkaddr;
    unsigned char  	sensortype;
    unsigned long int  sensorvalue;// 32bits
} SensorDesp,*pSensorDesp;


typedef struct DeviceInfo{
    unsigned int  nwkaddr;
    unsigned char  macaddr[8];
    unsigned char  depth;
    unsigned char  devtype;
    unsigned int  parentnwkaddr;
    unsigned char  sensortype;
    unsigned long int  sensorvalue;
    unsigned char  status;
}DeviceInfo,*pDeviceInfo;

typedef struct NodeInfo NodeInfo,*pNodeInfo;

struct NodeInfo{
    DeviceInfo *devinfo;
    NodeInfo *next;
    unsigned char row;
    unsigned char num;
};


typedef struct{
    struct DeviceInfo *devinfo;
    struct NodeNwkTopoInfo *next;
    unsigned char row;
    unsigned char num;
    struct NodeNwkTopoInfo *parent;
    unsigned int pos_x;
    unsigned int pos_y;
}NodeNwkTopoInfo,*pNodeNwkTopoInfo;

#include "tty_ctrl.h"

//#define FALSE 0
//#define TRUE 1
typedef enum bool{FALSE, TRUE} bool;
struct msgbuf{
    long mtype;
    char phone[12];
};
int msgid;
struct msgbuf msg_sbuf;
struct msgbuf msg_rbuf;


#endif // GLOBAL_H
