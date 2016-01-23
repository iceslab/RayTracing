#include "RayTracing.hpp"

RayTracing::RayTracing(decltype(spheres) spheres, decltype(lights) lights, decltype(color) color, int maxSteps)
	: spheres(spheres), lights(lights), color(color), maxSteps(maxSteps)
{}

int RayTracing::Intersect(Point3D p, Vector3D v) {
	float r, a, b, c, d;
	float distance = 1000000000000;
	int status = -1;
	for (unsigned i = 0; i < spheres.size(); i++) {
		a = sq(v[0]) + sq(v[1]) + sq(v[2]);
		b = 2 * (v[0] * (p[0] - spheres[i].position[0])
			+ v[1] * (p[1] - spheres[i].position[1])
			+ v[2] * (p[2] - spheres[i].position[2]));
		c = sq(p[0]) + sq(p[1]) + sq(p[2])
			- 2 * (spheres[i].position[0] * p[0]
			+ spheres[i].position[1] * p[1]
			+ spheres[i].position[2] * p[2])
			+ sq(spheres[i].position[0])
			+ sq(spheres[i].position[1])
			+ sq(spheres[i].position[2])
			- sq(spheres[i].radius);
		d = b*b - 4 * a*c;
		if (d >= 0)
		{
			r = (-b - sqrt(d)) / (2 * a);
			if (r > 0 && r < distance)
			{
				intersPoint[0] = p[0] + r*v[0];
				intersPoint[1] = p[1] + r*v[1];
				intersPoint[2] = p[2] + r*v[2];
				distance = sqrt(sq(intersPoint[0] - p[0]) +
					sq(intersPoint[1] - p[1]) +
					sq(intersPoint[2] - p[2])
					);
				status = i;
			}
		}
	}
	return status;
}

//Funkcja oblicza kolor piksela dla promienia zaczynajacego sie w punkcie p i biegnacego w kierunku wskazywanym przez wektor v
void RayTracing::Trace(Point3D p, Vector3D v, int step)
{
	if (step > maxSteps)
		return;

	auto number = Intersect(p, v);
	if (number >= 0) {
		normalVector = spheres[number].getNormalVector(intersPoint);
		Reflect(v);
		color += spheres[number].phong(v, lights, intersPoint, global_ambient);
		Trace(intersPoint, reflectionVector, step + 1);
	}
	else
		return;
}

void RayTracing::TraceFast(Point3D p, Vector3D v)
{
	intersPoint = p;
	reflectionVector = v;
	int number = 0;
	for (int i = 0; i < maxSteps; ++i)
	{

		number = Intersect(intersPoint, reflectionVector);
		if (number >= 0) {
			normalVector = spheres[number].getNormalVector(intersPoint);
			Reflect(v);
			color += spheres[number].phong(reflectionVector, lights, intersPoint, global_ambient);
		}
		else
			break;
	}
}

//Funkcja oblicza kierunek odbicia promienia w punkcie
void RayTracing::Reflect(Vector3D v) {
	float	n_dot_i;
	Vector3D   invert = { -v[0], -v[1], -v[2] };

	invert.normalize();

	n_dot_i = Vector3D::scalarMul(invert, normalVector);
	reflectionVector[0] = 2 * (n_dot_i)*normalVector[0] - invert[0];
	reflectionVector[1] = 2 * (n_dot_i)*normalVector[1] - invert[1];
	reflectionVector[2] = 2 * (n_dot_i)*normalVector[2] - invert[2];

	reflectionVector.normalize();
}