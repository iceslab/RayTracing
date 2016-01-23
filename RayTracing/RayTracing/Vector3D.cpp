#include "Vector3D.hpp"

float Vector3D::scalarMul(Vector3D v)
{
	return (*this)[0] * v[0] + (*this)[1] * v[1] + (*this)[2] * v[2];
}

void Vector3D::normalize()
{
	float d = 0.0;
	int i;

	for (i = 0; i < 3; i++)
		d += (*this)[i] * (*this)[i];

	d = sqrt(d);

	if (d > 0.0)
	{
		for (i = 0; i < 3; i++)
			(*this)[i] /= d;
	}
}

float Vector3D::scalarMul(Vector3D p, Vector3D v)
{
	return p[0] * v[0] + p[1] * v[1] + p[2] * v[2];
}