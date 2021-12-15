
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"
#include<unordered_set>
#include<math.h>

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------
bool isInCircle(Circle c, Point* p);
Point* randomElement(vector<Point*>& p);
Circle findMinCircle(Point** points,size_t size);
Circle findMinCircle(vector<Point*>& p, vector<Point*>& r);
Circle trivial(vector<Point*>& points);
double average(double num1, double num2);
double distance(const Point* p1, const Point* p2);
Circle makeCircle(const Point* p1, const Point* p2);
Circle makeCircle(const Point* p1, const Point* p2, const Point* p3);
Point calculateCircleCenter(double p1x, double p1y, double p2x, double p2y);
bool isTrueCircle(const vector<Point*> points, const Circle& c);
// you can add here additional methods

#endif /* MINCIRCLE_H_ */
