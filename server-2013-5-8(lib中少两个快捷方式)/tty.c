#include "tty.h"


#include <sys/types.h>  /* open() */
#include <sys/stat.h>  /* open() */
#include <fcntl.h>  /* open() */
#include <unistd.h>  /* close() */
#include <string.h>  /* bzero() */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <termios.h>

static struct termios oldtio,newtio;

int tty_end(int _fd)
{
        tcsetattr(_fd,TCSANOW,&oldtio);	 	/* restore old modem setings */
        close(_fd);
}

int tty_read(int _fd,unsigned char *buf,int nbytes)
{
        return read(_fd,buf,nbytes);
}
int tty_read_t(int _fd,unsigned char *data)
{
int time_out = TTY_TIME_OUT;
char ch;
int len = 0;
for(;;){
    if(read(_fd,&ch,1) ==  -1){
        printf("=");
//	    fflush(stdout);
        if(time_out-- <= 0){
            printf("\n");
            return -1;
        }
        usleep(30000);
        continue;
    }
    data[len] = ch;
    printf("~~%c",ch);
    if(ch == '\n'){
        if(len > 1){
            return len;
        }else{
            len = 0;
            continue;
        }
    }
    len ++;
}
}

int tty_write(int _fd,unsigned char *buf,int nbytes)
{
    //printf("tty_write:____________________________\n");
        int i;
        for(i=0; i<nbytes; i++) {
                write(_fd,&buf[i],1);
                printf("%c",buf[i]);
                usleep(100);
        }
        printf("\n");
        return tcdrain(_fd);
}

int tty_writecmd(int _fd,unsigned char *buf,int nbytes)
{
        int i;
        for(i=0; i<nbytes; i++) {
                write(_fd,&buf[i],1);
                printf("__%c",buf[i]);
                usleep(100);
        }
        printf("\n");
        write(_fd,"\r",1);
        usleep(300000);
        return tcdrain(_fd);
}

int tty_init(int *_fd, const char*_name, int _baud)
{
        *_fd = open(_name, O_RDWR | O_NONBLOCK);//| O_NOCTTY); //| O_NONBLOCK);//
        if (*_fd <0) {
                perror(_name);
                exit(-1);
        }

        tcgetattr(*_fd,&oldtio); /* save current modem settings */
        bzero(&newtio, sizeof(newtio));

        newtio.c_cflag = /*BAUDRATE*/_baud | /*CRTSCTS |*/ CS8 | CLOCAL | CREAD ;
        newtio.c_iflag = IGNPAR/*| ICRNL*/;
        newtio.c_iflag &= ~(IXON | IXOFF | IXANY); // by sprife

        newtio.c_oflag = 0;
        newtio.c_lflag = 0;

        //newtio.c_oflag &= ~(OPOST);
        //newtio.c_lflag &= ~ICANON;

         newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */
         newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
         newtio.c_cc[VERASE]   = 0;     /* del */
         newtio.c_cc[VKILL]    = 0;     /* @ */
         newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */

         newtio.c_cc[VTIME]    = 0;     /* 不使用分割字元组的计时器 */
         newtio.c_cc[VMIN]     = 1;     /* 在读取到 1 个字元前先停止 */

         newtio.c_cc[VSWTC]    = 0;     /* '\0' */
         newtio.c_cc[VSTART]   = 0;     /* Ctrl-q */
         newtio.c_cc[VSTOP]    = 0;     /* Ctrl-s */
         newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
         newtio.c_cc[VEOL]     = 0;     /* '\0' */
         newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
         newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
         newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
         newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
         newtio.c_cc[VEOL2]    = 0;     /* '\0' */

        tcflush(*_fd, TCIFLUSH);
        tcsetattr(*_fd,TCSANOW,&newtio);/*set attrib	  */

        return 0;
}

void tty_fflush(int _fd){
        tcflush(_fd,TCIFLUSH);//刷新输入输出缓冲
}
