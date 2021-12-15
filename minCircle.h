
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"
#include<unordered_set>

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

Circle findMinCircle(Point** points,size_t size);
Circle findMinCircle(unordered_set<Point*> &p, unordered_set<Point*> &r);
Circle trivial(vector<Point*> points);

// you can add here additional methods

#endif /* MINCIRCLE_H_ */
