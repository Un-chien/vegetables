#ifndef TTY_CTRL_H
#define TTY_CTRL_H


extern pthread_mutex_t mutex;

extern struct sigaction sa;
extern pthread_t th_kb, th_rev, th_send,bt_rev,rf_rev,msg_rev;
extern void * retval;
extern unsigned int gSim;
extern unsigned int gSend;
extern unsigned char gIntLock;

extern unsigned char gNwkStatusFlag;
extern unsigned char gFrameValidFlag;
extern unsigned char gCmdValidFlag;

extern char phone_buf[11];
extern NwkDesp gNwkDesp;
extern DeviceInfo gDeviceInfo;
extern SensorDesp gSensorDesp;

extern unsigned int gBTStatusFlag;
extern unsigned long int gBTDatas;
extern unsigned long int gRFDatas;

extern unsigned char Data_CalcFCS( unsigned char  *msg_ptr, unsigned char  len );
extern int CMD_CalcFCS( unsigned char  *msg_ptr, unsigned char  len );
extern int Data_PackageParser( unsigned char  *msg_ptr, unsigned char  len );

extern void CMD_NwkDetect(void);
extern void CMD_GetNwkDesp(void);
extern void CMD_SetSensorWorkMode(/*unsigned int nwkaddr,*/unsigned char Mode);
extern void CMD_SetSensorStatus(unsigned int nwkaddr, unsigned  int status);
extern void CMD_GetSensorStatus(unsigned int nwkaddr);
extern void CMD_GetZigBeeDevInfo(unsigned int nwkaddr);
extern void CMD_GetZigBeeNwkTopo(void);


extern void ProcessNwkConnectRSP( unsigned char  *_pData, unsigned char _len );
extern void ProcessGetNwkDespRSP( unsigned char  *_pData, unsigned char _len );
extern void ProcessGetNwkTopoRSP( unsigned char  *_pData , unsigned char _len );
extern void ProcesssSetSensorModeRSP( unsigned char  *_pData, unsigned char _len );
extern void ProcessGetSensorStatusRSP( unsigned char  *_pData, unsigned char _len );
extern void ProcessSetSensorStatusRSP( unsigned char  *_pData, unsigned char _len );
extern void ProcessGetDevInfoRSP( unsigned char  *_pData , unsigned char _len );

extern int ZigBeeNwkDetect(void);
extern NwkDesp *GetZigBeeNwkDesp(void);
extern int SetSensorWorkMode(/*unsigned int nwkaddr,*/unsigned char Mode);
extern int SetSensorStatus(unsigned int nwkaddr, unsigned  int status);
extern SensorDesp *GetSensorStatus(unsigned int nwkaddr);
extern DeviceInfo* GetZigBeeDevInfo(unsigned int nwkaddr);
extern NodeInfo *GetZigBeeNwkTopo(void);
extern void ShowNodeListInfo(pNodeInfo pNodeHead);

extern void HandleBlueToothData(unsigned char  *_pData , unsigned char _len);
extern unsigned int GetBlueToothStatus(void);
extern unsigned long int GetBlueToothData(void);

extern void HandleRFIDData(unsigned char  *_pData , unsigned char _len);
extern unsigned long int GetRFIDData(void);

extern int ComPthreadMonitorStart(void);
extern int ComPthreadMonitorExit(void);
#define UINT_QUEUE_SIZE (6)
typedef struct
{
    unsigned int data[UINT_QUEUE_SIZE];
    unsigned int head;
    unsigned int tail;
    pthread_mutex_t lock;
}UINT_QUEUE, *PUINT_QUEUE;
extern UINT_QUEUE pQueue;
#endif // TTY_CTRL_H
