#ifndef __GPRS_H__
#define __GPRS_H__

void gprs_init();

void gprs_msg(char *number, int num);
void gprs_hold();
void gprs_ans();
void gprs_call(char *number, int num);
void gprs_baud(char *baud,int num);
void gprs_sim_state();
void gprs_at();
void gprs_ate0();
void gprs_exit();

#endif
