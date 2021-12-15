#include "minCircle.h"


double distance(const Point* p1, const Point* p2) {
	double dis = sqrt(pow(p1->x - p2->x, 2.0) + pow(p1->y - p2->y, 2.0));
	return dis;
}

bool isInCircle(Circle c, Point* p) {
	float dx = p->x - c.center.x;
	float dy = p->y - c.center.y;
	float dist = sqrt(dx * dx + dy * dy);
	return dist <= c.radius;
}

Circle findMinCircle(Point** points, size_t size) {
	vector<Point*> p(points, points + size);
	vector<Point*> r;
	/*for (int i = 0; i < size; i++) {
		p.push_back(points[i]);
	}*/
	return findMinCircle(p, r);
}

Point* randomElement(vector<Point*>& p) {
	// put some elements into the set

	//int size = p.size(); // get the number of buckets
	//srand(time(0)); // random number generator (seeded with time(0))
	//int i = rand() % size;
	//swap(p[i], p[p.size() - 1]);
	return p[p.size() - 1];
}

Circle findMinCircle(vector<Point*>& p, vector<Point*>& r) {
	if (p.size() == 0 || r.size() == 3) {
		return trivial(r);
	}
	int i = rand() % p.size();
	swap(p[i], p[p.size() - 1]);
	Point* point = p[p.size() - 1]; //randomElement(p);
	p.pop_back();
	Circle c = findMinCircle(p, r);
	if (isInCircle(c, point)) {
		p.push_back(point);
		swap(p[i], p[p.size() - 1]);
		return c;
	}
	else {
		r.push_back(point);
		c = findMinCircle(p, r);
		r.pop_back();
		p.push_back(point);
		swap(p[i], p[p.size() - 1]);
		return c;
	}
}

Circle makeCircle(const Point* p1, const Point* p2)
{
	return Circle(Point(average(p1->x, p2->x), average(p1->y, p2->y)), distance(p1, p2) / 2.0);
}

Circle makeCircle(const Point* p1, const Point* p2, const Point* p3)
{
	Point temp = calculateCircleCenter((p2->x - p1->x), (p2->y - p1->y), (p3->x - p1->x), (p3->y - p1->y));
	temp.x += p1->x;
	temp.y += p1->y;
	return Circle(temp, distance(&temp, p1));
}

Point calculateCircleCenter(double p1x, double p1y, double p2x, double p2y)
{	
	double P1 = p1x * p1x + p1y * p1y;
	double P2 = p2x * p2x + p2y * p2y;
	double D = 2 * (p1x * p2y - p2x * p1y);
	return Point((P1 * p2y - P2 * p1y) / D, (P2 * p1x - P1 * p2x) / D);
}

bool isTrueCircle(const vector<Point*> points, const Circle &c)
{
	for (Point* p : points) {
		if (!isInCircle(c, p)) {
			return false;
		}
	}
	return true;
}

Circle trivial(vector<Point*>& points) {
	int size_of_vector = points.size();
	if (points.empty()) {
		Circle c = {{0, 0}, 0};
		return c;
	}
	else if (size_of_vector == 1) {
		Circle c = Circle(*points[0], 0);
		return c;
	}
	else if (size_of_vector == 2) {
		Circle c = makeCircle(points[0], points[1]);
		return c;
	}
	/*for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j < 3; j++) {
			Circle c = makeCircle(points[i], points[j]);
			if (isTrueCircle(points, c)) {
				return c;
			}
		}
	}*/
	return makeCircle(points[0], points[1], points[2]);
}

double average(double num1, double num2)
{
	return ((num1 + num2) / 2.0);
}
