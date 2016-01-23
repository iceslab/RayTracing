#include "Vector3D.hpp"

float Vector3D::scalarMul(Vector3D v)
{
	return (*this)[0] * v[0] + (*this)[1] * v[1] + (*this)[2] * v[2];
}

void Vector3D::normalize()
{
	auto d = sqrt(scalarMul(*this));

	if (d > 0.0)
	{
		(*this) /= d;
	}
}

float Vector3D::scalarMul(Vector3D p, Vector3D v)
{
	return p[0] * v[0] + p[1] * v[1] + p[2] * v[2];
}