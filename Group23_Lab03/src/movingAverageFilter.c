/**
 * @file movingAverageFilter.c
 * @author Jean-Sebastien Dery (260430688) and Matthew Johnston (260349319)
 * @version 1.0
 * @date October 27th 2013
 * @brief Manages the Low-Pass filters for the 3-axis tilt angles.
*/

#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "movingAverageFilter.h"

/**
 * Defines the buffer size used for the moving average filter.
*/
const uint8_t bufferDepth = 10;

/**
 * Defines the buffers used for all axis.
*/
double xAxisBuffer[bufferDepth];
double yAxisBuffer[bufferDepth];
double zAxisBuffer[bufferDepth];

/**
 * Defines the pointers of the circular buffers used for the moving average filter.
*/
uint8_t xBufferPointer = 0;
uint8_t yBufferPointer = 0;
uint8_t zBufferPointer = 0;

/**
 * Adds an angle reading the the X-axis buffer.
 *
 * @param The angle to be added.
*/
void addToXBuffer(int angle){
	// Adds the angle at the end of the circular buffer.
	xAxisBuffer[xBufferPointer] = angle;
	
	// Increments the pointer in the circular buffer and sets it back to 0 if it overbounds.
	if (xBufferPointer == (bufferDepth-1)) {
		xBufferPointer = 0;
	} else {
		xBufferPointer++;
	}
}

/**
 * Returns the average value of the moving average filter for the X-axis.
 *
 * @return The average angle on the X-axis.
*/
int getXValue(){
	int sum = 0;
	uint8_t i = 0;
	for (i = 0; i < bufferDepth; i++){
		sum += xAxisBuffer[i];
	}
	int average = sum / bufferDepth;
	return average;
}

/**
 * Adds an angle reading the the Y-axis buffer.
 *
 * @param The angle to be added.
*/
void addToYBuffer(int angle){
	// Adds the angle at the end of the circular buffer.
	yAxisBuffer[yBufferPointer] = angle;
	
	// Increments the pointer in the circular buffer and sets it back to 0 if it overbounds.
	if (yBufferPointer == (bufferDepth-1)) {
		yBufferPointer = 0;
	} else {
		yBufferPointer++;
	}
}

/**
 * Returns the average value of the moving average filter for the Y-axis.
 *
 * @return The average angle on the Y-axis.
*/
int getYValue(){
	int sum = 0;
	uint8_t i = 0;
	for (i = 0; i < bufferDepth; i++){
		sum += yAxisBuffer[i];
	}
	int average = sum / bufferDepth;
	return average;
}

/**
 * Adds an angle reading the the Z-axis buffer.
 *
 * @param The angle to be added.
*/
void addToZBuffer(int angle){
	// Adds the angle at the end of the circular buffer.
	zAxisBuffer[zBufferPointer] = angle;
	
	// Increments the pointer in the circular buffer and sets it back to 0 if it overbounds.
	if (zBufferPointer == (bufferDepth-1)) {
		zBufferPointer = 0;
	} else {
		zBufferPointer++;
	}
}

/**
 * Returns the average value of the moving average filter for the Z-axis.
 *
 * @return The average angle on the Z-axis.
*/
int getZValue(){
	int sum = 0;
	uint8_t i = 0;
	for (i = 0; i < bufferDepth; i++){
		sum += zAxisBuffer[i];
	}
	int average = sum / bufferDepth;
	return average;
}