#pragma once
#include "Wrapper.hpp"
#include <cmath>
class Vector3D : public Wrapper
{
public:
	Vector3D() = default;
	~Vector3D() = default;
	Vector3D(initializer_list<float> il) :Wrapper(il){};

	float scalarMul(Vector3D v);
	void normalize();
	static float scalarMul(Vector3D p, Vector3D v);
};

