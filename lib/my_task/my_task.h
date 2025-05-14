#ifndef MY_TASK_H
#define MY_TASK_H

#include <Arduino.h>
#include "config.h"
#include "own_stdio.h"
#include <DHT.h>
#include <DHT_U.h>


void parsing(const char *command);
void systemSetup(void);
void MyDutyForErverAndEverAgain(void);

#endif // MY_TASK_H