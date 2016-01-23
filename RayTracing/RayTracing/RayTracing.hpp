#pragma once
#include <vector>
#include "Solid.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
class RayTracing
{
private:
	vector<Solid*> solids;
	vector<Light> lights;
	ColorRGB color;

	int maxSteps;
	Point3D intersPoint;
	Vector3D normalVector, reflectionVector;
	ColorRGB global_ambient;

	//Funkcja oblicza kierunek odbicia promienia w punkcie
	void Reflect(Vector3D v);
	Solid* Intersect(Point3D p, Vector3D v);
	float sq(float a)
	{
		return a*a;
	}
public:
	RayTracing( int maxSteps );
	~RayTracing();

	void addSolid(Solid* object);
	void addLight(Light light);
	void print();
	ColorRGB getColor();

	//Funkcja oblicza kolor piksela dla promienia zaczynajacego sie w punkcie p i biegnacego w kierunku wskazywanym przez wektor v
	void TraceFast(Point3D p, Vector3D v);
};

