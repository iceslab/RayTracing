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

Wrapper & Wrapper::operator =(const Wrapper & w)
{
	for (unsigned i = 0; i < 3; i++)
		content[i] = w.content[i];
	return *this;
}

// OPERATORY KLASA @ KLASA

Wrapper Wrapper::operator +(const Wrapper & w)
{
	Wrapper wrap;
	for (unsigned i = 0; i < 3; i++)
		wrap[i] = content[i] + w.content[i];
	return wrap;
}

Wrapper & Wrapper::operator +=(const Wrapper & w)
{
	for (unsigned i = 0; i < 3; i++)
		content[i] += w.content[i];
	return *this;
}

Wrapper Wrapper::operator -(const Wrapper & w)
{
	Wrapper wrap;
	for (unsigned i = 0; i < 3; i++)
		wrap[i] = content[i] - w.content[i];
	return wrap;
}

Wrapper & Wrapper::operator -=(const Wrapper & w)
{
	for (unsigned i = 0; i < 3; i++)
		content[i] -= w.content[i];
	return *this;
}

Wrapper Wrapper::operator *(const Wrapper & w)
{
	Wrapper wrap;
	for (unsigned i = 0; i < 3; i++)
		wrap[i] = content[i] * w.content[i];
	return wrap;
}

Wrapper & Wrapper::operator *=(const Wrapper & w)
{
	for (unsigned i = 0; i < 3; i++)
		content[i] *= w.content[i];
	return *this;
}

Wrapper Wrapper::operator /(const Wrapper & w)
{
	Wrapper wrap;
	for (unsigned i = 0; i < 3; i++)
		wrap[i] = content[i] / w.content[i];
	return wrap;
}

Wrapper & Wrapper::operator /=(const Wrapper & w)
{
	for (unsigned i = 0; i < 3; i++)
		content[i] /= w.content[i];
	return *this;
}

// OPERATORY KLASA @ TYP_WBUDOWANY

Wrapper Wrapper::operator +(float w)
{
	Wrapper wrap;
	for (unsigned i = 0; i < 3; i++)
		wrap[i] = content[i] + w;
	return wrap;
}

Wrapper & Wrapper::operator +=(float w)
{
	for (unsigned i = 0; i < 3; i++)
		content[i] += w;
	return *this;
}

Wrapper Wrapper::operator -(float w)
{
	Wrapper wrap;
	for (unsigned i = 0; i < 3; i++)
		wrap[i] = content[i] - w;
	return wrap;
}

Wrapper & Wrapper::operator -=(float w)
{
	for (unsigned i = 0; i < 3; i++)
		content[i] -= w;
	return *this;
}

Wrapper Wrapper::operator *(float w)
{
	Wrapper wrap;
	for (unsigned i = 0; i < 3; i++)
		wrap[i] = content[i] * w;
	return wrap;
}

Wrapper & Wrapper::operator *=(float w)
{
	for (unsigned i = 0; i < 3; i++)
		content[i] *= w;
	return *this;
}

Wrapper Wrapper::operator /(float w)
{
	Wrapper wrap;
	for (unsigned i = 0; i < 3; i++)
		wrap[i] = content[i] / w;
	return wrap;
}

Wrapper & Wrapper::operator /=(float w)
{
	for (unsigned i = 0; i < 3; i++)
		content[i] /= w;
	return *this;
}