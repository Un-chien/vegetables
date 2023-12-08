#!/bin/bash
cd /mnt/yaffs/up_wsn/
insmod /mnt/yaffs/up_wsn/8250.ko
export QTDIR=$PWD
export LD_LIBRARY_PATH=$PWD/lib
export TSLIB_TSDEVICE=/dev/event1
export TSLIB_PLUGINDIR=$PWD/lib/ts
export TSLIB_CONSOLEDEVICE=none
export TSLIB_CONFFILE=$PWD/etc/ts.conf
export POINTERCAL_FILE=$PWD/etc/ts-calib.conf
export QWS_MOUSE_PROTO=tslib:/dev/event1
export TSLIB_CALIBFILE=$PWD/etc/ts-calib.conf
export QT_QWS_FONTDIR=$PWD/lib/fonts
export QT_PLUGIN_PATH=$PWD/plugins/
#export QWS_DISPLAY="LinuxFb:mmWidth260:mmHeight245:0"
export LANG=zh_CN
# for tslib                                 
if [ ! -f /mnt/yaffs/up_wsn/etc/ts-calib.conf ];then
/mnt/yaffs/up_wsn/bin/ts_calibrate
fi

ifconfig eth0 192.168.12.199
/usr/sbin/telnetd&
/mnt/yaffs/up_wsn/ev_server 7838 9&
usleep 10000
/mnt/nfs/vegetables/vegetable/vegetable  -qws -font wenquanyi
~
