#ifndef TTY_H
#define TTY_H

extern int fd;
#define TTY_TIME_OUT 2
extern int tty_init(int* _fd, const char*_name, int _baud);
extern int tty_end(int _fd);
extern int tty_read(int _fd,unsigned char *buf,int nbytes);
extern int tty_write(int _fd,unsigned char *buf,int nbytes);
extern int tty_writecmd(int _fd,unsigned char *buf,int nbytes);
extern void tty_fflush(int _fd);
extern int tty_read_t(int _fd,unsigned char *data);

#endif // TTY_H
