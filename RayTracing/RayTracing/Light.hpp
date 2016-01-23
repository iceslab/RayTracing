#include "Point3D.hpp"
#include "ColorRGB.hpp"
#include <iostream>

#ifndef flow(array, dir)
#define flow(array, dir) array[0] dir array[1] dir array[2]
#endif

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