#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include "Point3D.hpp"
#include "ColorRGB.hpp"
#include <iostream>

#include "defines.h"

using namespace std;

class Light
{
private:

public:
	Point3D position;
	ColorRGB specular;
	ColorRGB diffuse;
	ColorRGB ambient;
	Light() = default;
	friend istream& operator>>(istream& in, Light& s);
	friend ostream& operator<<(ostream& out, Light& s);

};

#endif
