#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
//#include <sys/signal.h>
#include "tty.h"
#include"gprs.h"
#include"global.h"
extern gprs_fd;
char rfid_msg[]="In the balcony of the IFRD sensor warn!";
char int_msg[]="In the door of the INTT sensor warn!!!!";
char smog_msg[]="In the kitchen of the SMOG sensor warn!";
int sensor;
struct timeval tv;
fd_set ds;

unsigned int gSim=0;
unsigned int gSend=0;
pthread_t send_msg,write_send;
void * retval;
UINT_QUEUE pQueue;

pthread_mutex_t lock; /* 互斥锁 */
pthread_cond_t wait; /* wait信号 */

unsigned int gSendLock=0;
void enqueue_int_queue2(PUINT_QUEUE pQ, unsigned int c)
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
int dequeue_int_queue(PUINT_QUEUE pQ, unsigned int *p)
{
    int rv = -1;
    pthread_mutex_lock(&pQ->lock);

    if(pQ->head == pQ->tail) // queue empty
    {

        rv = -1;
    }
    else
    {

        printf("_________________denqueue_int_queue: %d\n",pQ->data[pQ->tail]);

        *p = pQ->data[pQ->tail];
        pQ->tail = (pQ->tail + 1 ) % UINT_QUEUE_SIZE;
        rv = 0;
    }
    pthread_mutex_unlock(&pQ->lock);
    return rv;
}
void* SendMsg(void * data)
{


    char ctl[]={26,0};

    char ch;
    while(1)
    {
        tv.tv_sec=2;
        tv.tv_usec=0;
        FD_ZERO(&ds);
        FD_SET(gprs_fd, &ds);
        int ret = select(1+gprs_fd, &ds, NULL, NULL, &tv);

        if(ret >0)
        {
            if (FD_ISSET(gprs_fd, &ds))
            {
                pthread_mutex_lock(&lock);
                gSendLock=0;
                pthread_mutex_unlock(&lock);

                read(gprs_fd,&ch,1);
                if(ch == '>')
                {
                    pthread_mutex_lock(&lock);
                    gSendLock=1;
                    pthread_mutex_unlock(&lock);


                    if((sensor)==1)
                       tty_write(gprs_fd, rfid_msg, strlen(rfid_msg));
                    else if((sensor)==2)
                       tty_write(gprs_fd, smog_msg, strlen(smog_msg));
                    else if((sensor)==3)
                       tty_write(gprs_fd, int_msg, strlen(int_msg));
                    tty_write(gprs_fd, ctl, 1);      //?°CTRL+Z"μáSCII?
                    tty_write(gprs_fd, &ctl[1], 1);
                    gSend=1;
                    pthread_mutex_lock(&lock);
                    gSendLock=0;
                    pthread_mutex_unlock(&lock);

                }
            }
            else{
                 printf("not tty gprs_fd.\n");
            }
        }
        else if(ret == 0){
                printf("gprs_fd read wait timeout!!!\n");
        }
        else{// ret <0
            printf("gprs_fd select error.\n");
        }
        usleep(100);
    }


}

void gprs_wmsg(void * data)
{

    //printf("*******************gprs_msg start write *****************\n");
    while(1)
    {
         //printf("*******************gprs_wmsg *****************\n");
        if(dequeue_int_queue(&pQueue, &sensor)!= -1)
        {
            if(gSendLock==0)
            {
            //pthread_mutex_lock(lock);
            tty_writecmd(gprs_fd, "AT", strlen("AT"));
            tty_writecmd(gprs_fd, "AT+CMGF=1", strlen("AT+CMGF=1"));		//发送修改字符集命令
            tty_write(gprs_fd, "AT+CMGS=", strlen("AT+CMGS="));	//发送发短信命令，具体格式见手册
            tty_write(gprs_fd, "\"", strlen("\""));
            tty_write(gprs_fd, phone_buf, 11);
            tty_write(gprs_fd, "\"", strlen("\""));
            tty_write(gprs_fd, ";\r", strlen(";\r"));

            }
            else{
                enqueue_int_queue2(&pQueue,sensor);
            }
            //pthread_cond_wait(&wait, &lock);
            //pthread_mutex_unlock(lock);


        }
        usleep(5000000);
    }

}
void gprs_init()
{


    tty_writecmd(gprs_fd, "AT", strlen("AT"));
    usleep(5000);
    tty_writecmd(gprs_fd, "AT", strlen("AT"));
    usleep(5000);
    tty_writecmd(gprs_fd, "ATE0", strlen("ATE0"));
    usleep(5000);
    tty_writecmd(gprs_fd, "AT+CMGF=1", strlen("AT+CMGF=1"));

    gSim=1;
    gSend=0;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&wait, NULL);


    pthread_create(&send_msg,NULL,SendMsg,0);
    pthread_create(&write_send,NULL,gprs_wmsg,0);

}
void gprs_exit()
{

     pthread_join(write_send, &retval);
      pthread_join(send_msg, &retval);

}

void gprs_hold()
{
        tty_writecmd(gprs_fd, "AT", strlen("AT"));
        tty_writecmd(gprs_fd, "ATH", strlen("ATH"));//·￠?1??ATH
}

void gprs_ans()
{
        tty_writecmd(gprs_fd, "AT", strlen("AT"));
        tty_writecmd(gprs_fd, "ATA", strlen("ATA"));//·￠????TA
}

//2|?Π
void gprs_call(char *number, int num)
{

        tty_write(gprs_fd, "ATD", strlen("ATD")); //·￠?2|′???D
        tty_write(gprs_fd, number, num);
        tty_write(gprs_fd, ";\r", strlen(";\r"));
        usleep(200000);

}

//·￠???í

void gprs_msg(char *number, int num)
{

    printf("*******************gprs_msg start write sensor:%d*****************\n",num);


    tty_writecmd(gprs_fd, "AT", strlen("AT"));
    tty_writecmd(gprs_fd, "AT+CMGF=1", strlen("AT+CMGF=1"));		//发送修改字符集命令
    tty_write(gprs_fd, "AT+CMGS=", strlen("AT+CMGS="));	//发送发短信命令，具体格式见手册
    tty_write(gprs_fd, "\"", strlen("\""));
    tty_write(gprs_fd, number, 11);
    tty_write(gprs_fd, "\"", strlen("\""));
    tty_write(gprs_fd, ";\r", strlen(";\r"));
    sensor=num;

}

void gprs_baud(char *baud,int num)
{
        tty_write(gprs_fd, "AT+IPR=", strlen("AT+IPR="));
        tty_writecmd(gprs_fd, baud, strlen(baud) );
        usleep(200000);
}


