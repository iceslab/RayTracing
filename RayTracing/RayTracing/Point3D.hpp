#pragma once
#include "Wrapper.hpp"
class Point3D : public Wrapper
{
public:
	Point3D() = default;
	~Point3D() = default;
	Point3D(initializer_list<float> il) :Wrapper(il){};
};

