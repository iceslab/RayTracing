#include "Sphere.hpp"

istream& operator>>(istream& in, Sphere& s)
{
	in >> s.radius >> flow(s.position, >>);
	in >> flow(s.specular, >>);
	in >> flow(s.diffuse, >>);
	in >> flow(s.ambient, >>);
	in >> s.shine;
	return in;
}

ostream& operator<<(ostream& out, Sphere& s)
{
	out << "Sphere: \n\tPosition: ( "<< flow(s.position, <<", "<<) <<" )\n";
	out << "\tRadius: " << s.radius<<"\n";
	return out;
}

void Sphere::rotateZ(double angle)
{
	double x = position[0] * cos(angle) - position[1] * sin(angle);
	double y = position[0] * sin(angle) + position[1] * cos(angle);
	position[0] = x;
	position[1] = y;
}

void Sphere::rotateX(double angle)
{
	position[2] += 5;
	double z = position[0] * cos(angle) - position[2] * sin(angle);
	double y = position[0] * sin(angle) + position[2] * cos(angle);
	position[0] = z;
	position[2] = y;
	position[2] -= 5;
}
Point3D Sphere::getIntersectionPoint(Point3D p, Vector3D v)
{
	float r, a, b, c, d;
	float distance = numeric_limits<float>::max();
	a = sq(v[0]) + sq(v[1]) + sq(v[2]);
	b = 2 * (v[0] * (p[0] - position[0])
		+ v[1] * (p[1] - position[1])
		+ v[2] * (p[2] - position[2]));
	c = sq(p[0]) + sq(p[1]) + sq(p[2])
		- 2 * (position[0] * p[0]
		+ position[1] * p[1]
		+ position[2] * p[2])
		+ sq(position[0])
		+ sq(position[1])
		+ sq(position[2])
		- sq(radius);
	d = b*b - 4 * a*c;
	Point3D result;
	if (d >= 0)
	{
		r = (-b - sqrt(d)) / (2 * a);
		if (r > 0 && r < distance)
		{
			result[0] = p[0] + r*v[0];
			result[1] = p[1] + r*v[1];
			result[2] = p[2] + r*v[2];
		}
	}
	return result;
}
Vector3D Sphere::getNormalVector( Point3D p )
{
	Vector3D result;
	result[0] = p[0] - position[0];
	result[1] = p[1] - position[1];
	result[2] = p[2] - position[2];
	return result;
}
ColorRGB Sphere::phong()
{

}