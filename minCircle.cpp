#include "minCircle.h"


bool isInCircle(Circle c, Point* p) {
	float dx = p->x - c.center.x;
	float dy = p->y - c.center.y;
	float dist = sqrt(dx * dx + dy * dy);
	return dist <= c.radius;
}

Circle findMinCircle(Point** points, size_t size) {
	unordered_set<Point*> p;
	unordered_set<Point*> r;
	for (int i = 0; i < size; i++) {
		p.insert(points[i]);
	}
	return findMinCircle(p, r);
}

Point* randomElement(unordered_set<Point*>& p) {
	// put some elements into the set

	int bnum = p.bucket_count(); // get the number of buckets
	srand(time(0)); // random number generator (seeded with time(0))
	int rb = rand() % bnum;
	auto it = p.begin(rb);
	return *it;
}

Circle findMinCircle(unordered_set<Point*>& p, unordered_set<Point*>& r) {
	if (p.size() == 0 || r.size() == 3) {
		vector<Point*> points;
		for (Point* point : r) {
			points.push_back(point);
		}
		return trivial(points);
	}
	Point* point = randomElement(p);
	p.erase(point);
	Circle c = findMinCircle(p, r);
	if (isInCircle(c, point)) {
		p.insert(point);
		return c;
	}
	else {
		r.insert(point);
		c = findMinCircle(p, r);
		r.erase(point);
		p.insert(point);
		return c;
	}
}
Circle trivial(vector<Point*> points) {

}