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
	result[0] = 123.5;
	result[1] = numeric_limits<float>::quiet_NaN();
	result[2] = numeric_limits<float>::quiet_NaN();
	if (d >= 0)
	{
		r = (-b - sqrt(d)) / (2 * a);
		result[0] = p[0] + r*v[0];
		result[1] = p[1] + r*v[1];
		result[2] = p[2] + r*v[2];
	}
	return result;
}
Vector3D Sphere::getNormalVector( Point3D p )
{
	Vector3D result;
	result[0] = p[0] - position[0];
	result[1] = p[1] - position[1];
	result[2] = p[2] - position[2];
	result.normalize();
	return result;
}
ColorRGB Sphere::phong( Vector3D viewerVec, vector<Light>& lights, Point3D intersPoint, ColorRGB global_ambient )
{
	Vector3D reflectionVec;           //wektor kierunku odbicia swiatla
	Vector3D lightVec;                //wektor wskazujacy zrodel
	Vector3D normalVector = getNormalVector( intersPoint );
	float n_dot_l, v_dot_r;			//zmienne pomocnicze

	Vector3D viewer = { -viewerVec[0], -viewerVec[1], -viewerVec[2] };

	ColorRGB resultColor;
	resultColor[0] = 0;
	resultColor[1] = 0;
	resultColor[2] = 0;

	for (unsigned i = 0; i < lights.size(); i++) {
		lightVec[0] = lights[i].position[0] - intersPoint[0]; //wektor wskazujacy kierunek zrodla
		lightVec[1] = lights[i].position[1] - intersPoint[1];
		lightVec[2] = lights[i].position[2] - intersPoint[2];

		lightVec.normalize();    //normalizacja wektora kierunku swiecenia zrodla           

		n_dot_l = Vector3D::scalarMul(lightVec, normalVector);

		reflectionVec[0] = 2 * (n_dot_l)*normalVector[0] - lightVec[0];
		reflectionVec[1] = 2 * (n_dot_l)*normalVector[1] - lightVec[1];
		reflectionVec[2] = 2 * (n_dot_l)*normalVector[2] - lightVec[2];

		//obliczenie wektora opisujacego kierunek swiatla odbitego od punktu na powierzchni sfery

		reflectionVec.normalize(); //normalizacja wektora kierunku swiatla odbitego

		v_dot_r = Vector3D::scalarMul(reflectionVec, viewer);

		if (v_dot_r < 0)                  //obserwator nie widzi oswietlanego punktu
			v_dot_r = 0;

		//sprawdzenie czy punkt na powierzchni sfery jest oswietlany przez zrodlo

		if (n_dot_l > 0)    //punkt jest oswietlany,
		{                   //oswietlenie wyliczane jest ze wzorow dla modelu Phonga
			float x = sqrt((lights[i].position[0] - intersPoint[0])*(lights[i].position[0] - intersPoint[0]) + (lights[i].position[1] - intersPoint[1])*(lights[i].position[1] - intersPoint[1]) + (lights[i].position[2] - intersPoint[2])*(lights[i].position[2] - intersPoint[2]));
			resultColor[0] += (1.0 / (1.0 + 0.01*x + 0.001*x*x))*(diffuse[0] * lights[i].diffuse[0] * n_dot_l + specular[0] * lights[i].specular[0] * pow(double(v_dot_r), (double)shine)) + ambient[0] * lights[i].ambient[0];
			resultColor[1] += (1.0 / (1.0 + 0.01*x + 0.001*x*x))*(diffuse[1] * lights[i].diffuse[1] * n_dot_l + specular[1] * lights[i].specular[1] * pow(double(v_dot_r), (double)shine)) + ambient[1] * lights[i].ambient[1];
			resultColor[2] += (1.0 / (1.0 + 0.01*x + 0.001*x*x))*(diffuse[2] * lights[i].diffuse[2] * n_dot_l + specular[2] * lights[i].specular[2] * pow(double(v_dot_r), (double)shine)) + ambient[2] * lights[i].ambient[2];
		}
		//punkt nie jest oswietlany   
		//uwzgledniane jest tylko swiatlo rozproszone
		resultColor[0] += ambient[0] * global_ambient[0];
		resultColor[1] += ambient[1] * global_ambient[1];
		resultColor[2] += ambient[2] * global_ambient[2];
	}
	return resultColor;
}