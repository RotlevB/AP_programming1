/*
 * animaly_detection_util.cpp
 *
 * Author: write your ID and name here
 */

#include <math.h>
#include "anomaly_detection_util.h"
#include<iostream>

float avg(float* x, int size){
	float average = 0;
	for (int i = 0; i < size; i++) {
		average += x[i];
	}
	return average / size;
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
	float x_avg = avg(x, size);
	float y_avg = avg(y, size);
	float covariance = 0;
	for (int i = 0; i < size; i++) {
		covariance += (x[i] - x_avg) * (y[i] - y_avg);
	}
	return covariance / size;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
	float covariance = cov(x, y, size);
	double x_variance = (double) var(x, size);
	double y_variance = (double) var(y, size);
	return covariance / (float)(sqrt(x_variance * y_variance));
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){
	float* x = new float[size];
	float* y = new float[size];
	for (int i = 0; i < size; i++) {
		x[i] = points[i]->x;
		y[i] = points[i]->y;
	}
	float x_avg = avg(x, size);
	float y_avg = avg(y, size);
	float a = cov(x, y, size) / var(x, size);
	float b = y_avg - (a * x_avg);
	return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
	return dev(p, linear_reg(points, size));
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
	return fabs(l.f(p.x) - p.y);
}




