#include "Light.hpp"

istream& operator>>(istream& in, Light& s)
{
	in >> flow(s.position, >> );
	in >> flow(s.specular, >> );
	in >> flow(s.diffuse, >> );
	in >> flow(s.ambient, >> );
	return in;
}

ostream& operator<<(ostream& out, Light& s)
{
	out << flow(s.position, << ", " << ) << endl;
	out << flow(s.specular, << ", " << ) << endl;
	out << flow(s.diffuse, << ", " << ) << endl;
	out << flow(s.ambient, << ", " << ) << endl;
	return out;
}

