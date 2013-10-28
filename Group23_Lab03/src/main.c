/**
 * @file main.c
 * @author Jean-Sebastien Dery (260430688) and Matthew Johnston (260349319)
 * @version 1.0
 * @date October 25th 2013
 * @brief This C file will contain all the main flow of the program.
*/

#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4_discovery_lis302dl.h"
#include "accelerometerManager.h"
#include "tim4Manager.h"

void preamble();

int32_t allAxisAcceleration[3];
int allAxisAngles[3];

/**
 * The main method of the program.
 *
 * Contains the main flow of the program, from initialization to continuous execution.
 * @return The exit status of the program.
*/
int main() {
	printf("[INFO] main()\n");
	
	// Executes the main initialization.
	preamble();
	
	// The infinite while loop 
	while(1) {
		//readAcceleration(allAxisAcceleration);
		//printf("Raw acceleration in X=%d, Y=%d and Z=%d\n", allAxisAcceleration[0], allAxisAcceleration[1], allAxisAcceleration[2]);
		getAngles(allAxisAngles);
		printf("Raw acceleration in X=%d, Y=%d and Z=%d\n", allAxisAngles[0], allAxisAngles[1], allAxisAngles[2]);
	}
}

/**
 * Setup the software so it can run continuously afterwards.
 *
 * Contains all the initialization that this program will need: variables, peripherals, etc.
*/
void preamble() {
	printf("[INFO] Preamble()\n");
	
	initializeAccelerometer();
	initializeTimer();	
}