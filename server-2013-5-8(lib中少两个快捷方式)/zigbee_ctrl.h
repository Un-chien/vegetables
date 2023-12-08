#ifndef ZIGBEE_CTRL_H
#define ZIGBEE_CTRL_H

extern NodeInfo *NodeInfoHead;

extern pNodeInfo DeviceNodeCreate(pDeviceInfo item);
extern void DeviceNodeFree(pNodeInfo p);
extern pNodeInfo DeviceNodeSearch(unsigned int key);
extern void DeviceNodeAdd(pNodeInfo p);
extern void DeviceNodeDel(pNodeInfo p);
extern void DeviceNodeTraverse(void (*visit)(pNodeInfo));
extern void DeviceNodeDestory(void);
extern int DeviceNodeNum(pNodeInfo head);
extern void DeviceNodePush(pNodeInfo p);
extern pNodeInfo DeviceNodePop(void);

/*
extern bool ZigBeeNwkDetect(void);
extern bool GetZigBeeNwkInfo(NwkDesp *pNwkDesp);
extern bool SetSensorWorkMode(unsigned int nwkaddr,int Mode);
extern bool SetSensorStatus(unsigned int nwkaddr, unsigned  int status);
extern int GetSensorStatus(unsigned int nwkaddr);
extern DeviceInfo* GetZigBeeDevInfo(unsigned int nwkaddr);
extern NodeNwkTopoInfo* GetZigBeeNwkTopo(void);
*/


#endif // ZIGBEE_CTRL_H
