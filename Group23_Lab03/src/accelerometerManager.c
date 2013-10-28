/**
 * @file accelerometerManager.c
 * @author Jean-Sebastien Dery (260430688) and Matthew Johnston (260349319)
 * @version 1.0
 * @date October 25th 2013
 * @brief Manages all the interactions with the on-board accelerometer (initialization, read, etc.).
*/

#include "accelerometerManager.h"
#include "stm32f4_discovery_lis302dl.h"
#include "math.h"
#include "movingAverageFilter.h"

const double PI = 3.1415926535;

// NOTE: *** This is temporary calibration, I want to do the real shit if we have time.
double AxOffset = -18;
double AyOffset = +90;
double AzOffset = +26;

/**
 * Initializes the on-board accelerometer.
 *
 * Sets all the parameters defined, and needed, for the experiment on the LIS302DL accelerometer.
 * Initializes it and setup the SPI connection with the chip.
*/
void initializeAccelerometer() {
	// Sets up all the parameters in order to initialize the accelerometer.
	LIS302DL_InitTypeDef accInitParameters;
	// Activates the accelerometer.
	accInitParameters.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;
	// Sets the output data rate, it needs to be more than 25 Hz since we will be collecting the data at 25 Hz.
	// There are only two choices available anyway (100 Hz or 400 Hz).
	// The rate was chosen since it meets the requirement and it has a lower power consumption than running it at 400 Hz.
	accInitParameters.Output_DataRate = LIS302DL_DATARATE_100;
	// Sets the axis to be activated. All the axis are activated (X, Y and Z) since we want to be able to have the Yaw, Pitch and Roll of the board.
	accInitParameters.Axes_Enable = LIS302DL_XYZ_ENABLE;
	// The Full Scale range was set to 2_3 so we can achieve a better precision on the readings that we are doing.
	// The scale is going to be +/-2g at this mode (we don't need to have a larger scale for this lab experiment).
	// Go to the Accelerometer Application Notes at page 18 for more details about that.
	accInitParameters.Full_Scale = LIS302DL_FULLSCALE_2_3;
	// NOTE: *** I don't know what I'm doing here... need to figure this out before demo ***
	accInitParameters.Self_Test = LIS302DL_SELFTEST_NORMAL;

	// Initializes the LIS302DL accelerometer with the specified parameters in accInitParameters.
	// NOTE: *** need to explain what's going on under the hood right here ***
	LIS302DL_Init(&accInitParameters);
}

/**
 * Gives the 3-axis tilt angles in an array. The first position is Pitch, then Roll and finaly Yaw.
 *
 * @param The array that will contain the 3-axis tilt angles in degree.
*/
void getAngles(int* allAxisAngles) {
	// Creates the array that will contain the acceleration readings for all axis.
	int32_t allAxisAcceleration[3];
	// Reads the acceleration from the accelerometer on all axis.
	readAcceleration(allAxisAcceleration);
	
	// Stores the accelerations in different variables.
	double Ax = (double)allAxisAcceleration[0] - AxOffset;
	double Ay = (double)allAxisAcceleration[1] - AyOffset;
	double Az = (double)allAxisAcceleration[2] - AzOffset;
	
	// Compite the 3-axis tilt angles. Those formulas can be found in the AN3182 Application note at page 14.
	// Those values will are in radians.
	double pitchInRad = atan(Ax / sqrt(Ay*Ay + Az*Az));
	double rollInRad = atan(Ay / sqrt(Ax*Ax + Az*Az));
	double yawInRad = atan(Az / sqrt(Ay*Ay + Ax*Ax));
	
	// Converts the readings from radian to degree.
	int pitch = radianToDegree(pitchInRad);
	int roll = radianToDegree(rollInRad);
	int yaw = radianToDegree(yawInRad);
	
	// Add those readings to the moving average filter and extract the average.
	addToXBuffer(pitch);
	pitch = getXValue();
	addToYBuffer(roll);
	roll = getYValue();
	addToZBuffer(yaw);
	yaw = getZValue();
	
	// Stores the computed tilt angles (in degree) in the array passed in the signature.
	allAxisAngles[0] = pitch;
	allAxisAngles[1] = roll;
	allAxisAngles[2] = yaw;
}

/**
 * Converts the angles from radians to degrees.
 * 
 * @param Converted value in degree.
*/
int radianToDegree(double radian) {
	return (radian*360)/(2*PI);
}

/**
 * Reads the acceleration from the 3-axis onboard accelerometer.
 *
 * @param The array that will contain the acceleration for each axis.
*/
void readAcceleration(int32_t* allAxisAcceleration) {
	LIS302DL_ReadACC(allAxisAcceleration);
}