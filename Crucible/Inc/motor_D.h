#ifndef __MOTOR_D_H
#define __MOTOR_D_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
/*********¸Ä*********/
#define L_PWM_CLOSE		1
#define L_PWM_OPEN		1
#define R_PWM_CLOSE		1
#define R_PWM_OPEN		1
#define D_PWM_CLOSE		1
#define D_PWM_OPEN		1
#define FL_PWM_CLOSE	1
#define FL_PWM_OPEN		1
#define FR_PWM_CLOSE	1
#define FR_PWM_OPEN		1

void catch_fk(void);
void open_door(void);
void open_front_door(void);
void release_fk(void);
void close_door(void);
void close_front_door(void);


#endif
