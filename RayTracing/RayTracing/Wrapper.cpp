#include "Wrapper.hpp"

Wrapper::Wrapper(initializer_list<float> il)
{
	for (unsigned i = 0; i < 3; i++)
	{
		content[i] = *(il.begin() + i);
	}
}

Wrapper::Wrapper(initializer_list<double> il)
{
	for (unsigned i = 0; i < 3; i++)
	{
		content[i] = float(*(il.begin() + i));
	}
}

float& Wrapper::operator[](unsigned el)
{
	return content[el];
}