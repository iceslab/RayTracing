#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#define flow(array, dir) array[0] dir array[1] dir array[2]

#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>

#include "Solid.hpp"

using namespace std;

class Sphere : public Solid
{
private:

public:
	float radius;

	Sphere(){};

	void rotateZ(double angle);
	void rotateX(double angle);

	Point3D getIntersectionPoint(Point3D p, Vector3D v);
	Vector3D getNormalVector( Point3D p );
	ColorRGB phong();


	friend istream& operator>>(istream& in, Sphere& s);
	friend ostream& operator<<(ostream& in, Sphere& s);

};
#endif