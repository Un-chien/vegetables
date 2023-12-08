#include "global.h"

NodeInfo *NodeInfoHead=NULL;


pNodeInfo DeviceNodeCreate(pDeviceInfo pItem)
{
	int i;
	pNodeInfo p = malloc(sizeof(*p));
	p->devinfo = malloc(sizeof(*(p->devinfo)));

///*
	p->devinfo->nwkaddr = pItem->nwkaddr;
	
	for(i=0;i<8;i++){
		p->devinfo->macaddr[i] = pItem->macaddr[i];
	}
	p->devinfo->depth = pItem->depth;
	p->devinfo->devtype = pItem->devtype;
	p->devinfo->parentnwkaddr = pItem->parentnwkaddr;
	p->devinfo->sensortype = pItem->sensortype;
	p->devinfo->sensorvalue = pItem->sensorvalue;
	p->devinfo->status = pItem->status;
//*/	
	//p->devinfo = pItem;
	//memcpy(p->devinfo, pItem, sizeof(pNodeInfo));//segment fault.
	p->next = NULL;
	return p;
}

void DeviceNodeFree(pNodeInfo p)
{
	free(p->devinfo);
	free(p);
}

pNodeInfo DeviceNodeSearch(unsigned int nwkaddr)
{
	pNodeInfo p;
	for (p = NodeInfoHead; p; p = p->next){
		if ((p->devinfo->nwkaddr) == nwkaddr){
			return p;
		}
	}	
	return NULL;
}

void DeviceNodeAdd(pNodeInfo p)
{
	p->next = NodeInfoHead;
	NodeInfoHead = p;
}

void DeviceNodeDel(pNodeInfo p)
{
	pNodeInfo pre;
	if (p == NodeInfoHead) {
		NodeInfoHead = p->next;
		return;
	}
	for (pre = NodeInfoHead; pre; pre = pre->next)
		if (pre->next == p) {
			pre->next = p->next;
			return;
		}
}

void DeviceNodeTraverse(void (*visit)(pNodeInfo))
{
	pNodeInfo p;
	for (p = NodeInfoHead; p; p = p->next)
		visit(p);
}

void DeviceNodeDestory(void)
{
	pNodeInfo q, p = NodeInfoHead;
	NodeInfoHead = NULL;
	while (p) {
		q = p;
		p = p->next;
		DeviceNodeFree(q);
	}
}

int DeviceNodeNum(pNodeInfo head)	
{
	int count = 0;
	pNodeInfo current  =  head;
	while(current != NULL){
		count++;
		current = current->next;
	}

	return count;
}

void DeviceNodePush(pNodeInfo p)
{
	DeviceNodeAdd(p);
}

pNodeInfo DeviceNodePop(void)
{
	if (NodeInfoHead == NULL)
		return NULL;
	else {
		pNodeInfo p = NodeInfoHead;
		NodeInfoHead = NodeInfoHead->next;
		return p;
	}
}
