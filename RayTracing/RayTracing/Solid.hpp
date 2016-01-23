#ifndef _SOLID_HPP_
#define _SOLID_HPP_

#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <limits>
#include <vector>

#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "ColorRGB.hpp"
#include "Light.hpp"

using namespace std;

class Solid
{
private:

public:
	Point3D position;
	ColorRGB specular;
	ColorRGB diffuse;
	ColorRGB ambient;
	float shine;

	virtual void rotateZ( double angle ) = 0;
	virtual void rotateX( double angle ) = 0;

	virtual Point3D getIntersectionPoint(Point3D p, Vector3D v) = 0;
	virtual Vector3D getNormalVector( Point3D p ) = 0;
	virtual ColorRGB phong( Vector3D viewerVec, vector<Light>& lights, Point3D intersPoint, ColorRGB global_ambient ) = 0;

	static void normalizeVector( Vector3D& v );
	static inline float sq( float a ) { return a*a; }

};
#endif
