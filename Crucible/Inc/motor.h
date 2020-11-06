#ifndef __MOTOR_H
#define __MOTOR_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
void move_forward(void);
void move_backward(void);
void stop(void);
void move_right(void);
void move_left(void);
void move_Ncircle(void);
void move_Scircle(void);
void speed_up(void);
void speed_down(void);


#endif
