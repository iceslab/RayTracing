#pragma once
#include <vector>
#include "Sphere.hpp"
class RayTracing
{
private:
	vector<Sphere>& spheres;
	vector<Light>& lights;
	ColorRGB& color;

	int maxSteps;
	Point3D intersPoint;
	Vector3D normalVector, reflectionVector;
	ColorRGB global_ambient;

	//Funkcja oblicza kierunek odbicia promienia w punkcie
	void Reflect(Vector3D v);
	int Intersect(Point3D p, Vector3D v);
	float sq(float a)
	{
		return a*a;
	}
public:
	RayTracing(decltype(spheres) spheres, decltype(lights) lights, decltype(color) color, int maxSteps);
	~RayTracing() = default;

	//Funkcja oblicza kolor piksela dla promienia zaczynajacego sie w punkcie p i biegnacego w kierunku wskazywanym przez wektor v
	void Trace(Point3D p, Vector3D v, int step);
	void TraceFast(Point3D p, Vector3D v);
};

