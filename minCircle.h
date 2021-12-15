
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
Point* randomElement(unordered_set<Point*>& p);
Circle findMinCircle(Point** points,size_t size);
Circle findMinCircle(unordered_set<Point*> &p, unordered_set<Point*> &r);
Circle trivial(vector<Point*> points);

// you can add here additional methods

#endif /* MINCIRCLE_H_ */
