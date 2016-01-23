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
