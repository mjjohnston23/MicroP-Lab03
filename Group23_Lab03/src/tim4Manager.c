/**
 * @file tim4Manager.c
 * @author Jean-Sebastien Dery (260430688) and Matthew Johnston (260349319)
 * @version 1.0
 * @date October 25th 2013
 * @brief Manages all the interactions with the on-board TIM4 timer's peripheral.
*/

#include "accelerometerManager.h"
#include "stm32f4xx_tim.h"

/**
 * Initializes the on-board TIM3 timer at a frequency of 25 Hz, as per lab requirement.
*/
void initializeTimer() {
	// To have information about the Nested Vectored Interrupt Controller go to Reference Manual page 195.
	// TIM2 to TIM5 main features explained in Reference Manual at page 361.
	
	// Enables the clock for the TIM3 timer.
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	// When defining the prescaler remember that the speed is 84Mhz
	
	//TIM_ITConfig();
}