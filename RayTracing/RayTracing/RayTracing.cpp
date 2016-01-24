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
	// float min_distance = numeric_limits<float>::max(), distance = 0;
	Solid* result = nullptr;
	Point3D temp_point;
	float r, a, b, c, d;
	float distance = 1000000000000;
	for (unsigned i = 0; i < solids.size(); i++) {
		a = sq(v[0]) + sq(v[1]) + sq(v[2]);
		b = 2 * (v[0] * (p[0] - solids[i]->position[0])
			+ v[1] * (p[1] - solids[i]->position[1])
			+ v[2] * (p[2] - solids[i]->position[2]));
		c = sq(p[0]) + sq(p[1]) + sq(p[2])
			- 2 * (solids[i]->position[0] * p[0]
			+ solids[i]->position[1] * p[1]
			+ solids[i]->position[2] * p[2])
			+ sq(solids[i]->position[0])
			+ sq(solids[i]->position[1])
			+ sq(solids[i]->position[2])
			- sq(dynamic_cast<Sphere*>(solids[i])->radius);
		d = b*b - 4 * a*c;
		temp_point = solids[i]->getIntersectionPoint( p, v );
		if(temp_point[0] != 123.5 )
		// if (d >= 0)
		{
			r = (-b - sqrt(d)) / (2 * a);
			if (r > 0 && r < distance)
			{
				// temp_point[0] = p[0] + r*v[0];
				// temp_point[1] = p[1] + r*v[1];
				// temp_point[2] = p[2] + r*v[2];
				temp_point = solids[i]->getIntersectionPoint( p, v );
				distance = sqrt(sq(temp_point[0] - p[0]) +
					sq(temp_point[1] - p[1]) +
					sq(temp_point[2] - p[2])
					);
				result = solids[i];
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