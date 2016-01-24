#include "RayTracing.hpp"

RayTracing::RayTracing( int maxSteps )
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
void RayTracing::setGlobalAmbient(ColorRGB c)
{
	global_ambient = c;
}

Solid* RayTracing::Intersect(Point3D p, Vector3D v) 
{
	Solid* result = nullptr;
	Point3D temp_point;
	float min_dist = numeric_limits<float>::max(), dist = numeric_limits<float>::max();
	for (Solid* s : solids) {
		temp_point = s->getIntersectionPoint( p, v );
		if(temp_point[0] != 123.5 )
		{
			dist = sqrt(sq(temp_point[0] - p[0]) +
					sq(temp_point[1] - p[1]) +
					sq(temp_point[2] - p[2])
					);
			if(min_dist > dist)
			{
				min_dist = dist;
				result = s;
			}
		}
	}
	return result;
}

void RayTracing::print()
{
	cout << flow(global_ambient, <<" "<<)<<endl;
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

ColorRGB RayTracing::TraceFast(Point3D startPoint, Vector3D vector)
{
	Solid* solid = nullptr;
	Vector3D normalVector;
	ColorRGB color;
	color[0] = 0.0;
	color[1] = 0.0;
	color[2] = 0.0;
	// cout << flow(vector, <<", "<<)<<endl;
	for (int i = 0; i < maxSteps; ++i)
	{
		solid = Intersect(startPoint, vector);
		if (solid) 
		{
			startPoint = solid->getIntersectionPoint(startPoint, vector);
			
			
			color += solid->phong(vector, lights, startPoint, global_ambient);
			normalVector = solid->getNormalVector( startPoint );
			vector = Reflect(vector, normalVector);
			// cout << "Hit\n";
			
			// cout << "Hit: " <<solid <<endl;
		}
		else
		{
			break;
		}
	}
	// cout << flow(color, <<", "<<)<<endl;
	return color;
}

//Funkcja oblicza kierunek odbicia promienia w punkcie
Vector3D RayTracing::Reflect(Vector3D ray, Vector3D normal) {
	float	n_dot_i;
	Vector3D   invert = { -ray[0], -ray[1], -ray[2] };
	invert.normalize();

	Vector3D result;

	n_dot_i = Vector3D::scalarMul(invert, normal);
	result[0] = 2 * (n_dot_i)*normal[0] - invert[0];
	result[1] = 2 * (n_dot_i)*normal[1] - invert[1];
	result[2] = 2 * (n_dot_i)*normal[2] - invert[2];
	result.normalize();

	return result;
}

RayTracing::~RayTracing()
{
	for(auto& p : solids)
		delete p;
}