#include "Point3D.hpp"
#include "ColorRGB.hpp"
#include <iostream>

#define flow(array, dir) array[0] dir array[1] dir array[2]

using namespace std;

class Light
{
private:

public:
	Point3D position;
	ColorRGB specular;
	ColorRGB diffuse;
	ColorRGB ambient;
	Light(){};
	friend istream& operator>>(istream& in, Light& s);
	friend ostream& operator<<(ostream& out, Light& s);

};