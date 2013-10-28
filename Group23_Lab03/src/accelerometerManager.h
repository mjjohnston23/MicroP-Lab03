#ifndef ACCELEROMETERMANAGER_H
#define ACCELEROMETERMANAGER_H

#include "stm32f4xx.h"

void initializeAccelerometer();
void readAcceleration(int32_t* allAxisAcceleration);
void getAngles(int* allAxisAngles);

#endif