#pragma once
#include "Wrapper.hpp"
class Vector3D : public Wrapper
{
public:
	Vector3D() = default;
	~Vector3D() = default;
	Vector3D(initializer_list<float> il) :Wrapper(il){};
};

