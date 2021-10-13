/*
 * animaly_detection_util.cpp
 *
 * Author: write your ID and name here
 */

#include <math.h>
#include "anomaly_detection_util.h"

float avg(float* x, int size){
	float var_avg = 0;
	for (int i = 0; i < size; i++) {
		var_avg += x[i];
	}
	return var_avg/size;
}

// returns the variance of X and Y
float var(float* x, int size){
	float average = avg(x, size);
	float variance = 0;
	for (int i = 0; i < size; i++) {
		variance += (x[i] - average) * (x[i] - average);
	}
	return variance / size;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
	return 0;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
	return 0;
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){

	return Line(0,0);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
	return 0;
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
	return 0;
}



