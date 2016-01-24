#pragma once
#include <vector>
#include "Solid.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
class RayTracing
{
private:
	
	vector<Light> lights;
	
	ColorRGB global_ambient;
	ColorRGB background_color;

	//Funkcja oblicza kierunek odbicia promienia w punkcie
	Vector3D Reflect(Vector3D ray, Vector3D normal);
	Solid* Intersect(Point3D p, Vector3D v);
	float sq(float a)
	{
		return a*a;
	}
public:
	RayTracing( int maxSteps = 1 );
	~RayTracing();
	
	int maxSteps;
	vector<Solid*> solids;

	void addSolid(Solid* object);
	void addLight(Light light);
	void setGlobalAmbient(ColorRGB c);
	void setBackgroundColor(ColorRGB c);
	void print();

	//Funkcja oblicza kolor piksela dla promienia zaczynajacego sie w punkcie p i biegnacego w kierunku wskazywanym przez wektor v
	ColorRGB TraceFast(Point3D p, Vector3D v);
};

