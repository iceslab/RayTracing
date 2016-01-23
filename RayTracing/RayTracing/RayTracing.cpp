#include "RayTracing.hpp"

RayTracing::RayTracing(int maxSteps)
	: maxSteps(maxSteps)
{

}

void RayTracing::addSolid(Solid * object)
{
	solids.push_back(object);
}
void RayTracing::addLight(Light light)
{
	lights.push_back(light);
}
ColorRGB RayTracing::getColor()
{
	return color;
}

Solid* RayTracing::Intersect(Point3D p, Vector3D v) 
{
	float min_distance = numeric_limits<float>::max(), distance = 0;
	Solid* result = nullptr;
	Point3D temp_point;
	for(auto& s : solids)
	{
		temp_point = s->getIntersectionPoint(p, v);
		distance = sqrt(sq(temp_point[0] - p[0]) +
					sq(temp_point[1] - p[1]) +
					sq(temp_point[2] - p[2])
					);
		if(min_distance > distance)
			result = s;
	}
	return result;
}

void RayTracing::print()
{
	for(auto& s : solids)
	{
		cout << "Object: "<<*dynamic_cast<Sphere*>(s) << endl;
	}
	for(auto& l : lights)
	{
		cout << "Source: "<< l << endl;
	}
}

//Funkcja oblicza kolor piksela dla promienia zaczynajacego sie w punkcie p i biegnacego w kierunku wskazywanym przez wektor v

void RayTracing::TraceFast(Point3D p, Vector3D v)
{
	intersPoint = p;
	reflectionVector = v;
	Solid* solid = nullptr;
	for (int i = 0; i < maxSteps; ++i)
	{
		solid = Intersect(intersPoint, reflectionVector);
		if (solid) 
		{
			normalVector = solid->getNormalVector(intersPoint);
			Reflect(v);
			color += solid->phong(v, lights, intersPoint, global_ambient);
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

RayTracing::~RayTracing()
{
	for(auto& p : solids)
		delete p;
}