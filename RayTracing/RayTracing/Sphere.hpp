#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#include "defines.h"

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
	ColorRGB phong( Vector3D viewerVec, vector<Light>& lights, Point3D intersPoint, ColorRGB global_ambient );


	friend istream& operator>>(istream& in, Sphere& s);
	friend ostream& operator<<(ostream& in, Sphere& s);

};
#endif