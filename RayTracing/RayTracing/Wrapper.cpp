#include "Wrapper.hpp"

float& Wrapper::operator[](size_t el)
{
	return content[el];
}