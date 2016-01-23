#pragma once
#include <initializer_list>
using namespace std;
class Wrapper
{
public:
	Wrapper() = default;
	~Wrapper() = default;
	Wrapper(initializer_list<float> il);
	Wrapper(initializer_list<double> il);

	float& operator[](unsigned el);
	Wrapper & operator =(const Wrapper & w);
	Wrapper operator +(const Wrapper & w);
	Wrapper & operator +=(const Wrapper & w);
	Wrapper operator -(const Wrapper & w);
	Wrapper & operator -=(const Wrapper & w);
	Wrapper operator *(const Wrapper & w);
	Wrapper & operator *=(const Wrapper & w);
	Wrapper operator /(const Wrapper & w);
	Wrapper & operator /=(const Wrapper & w);

	Wrapper & operator =(float w);
	Wrapper operator +(float w);
	Wrapper & operator +=(float w);
	Wrapper operator -(float w);
	Wrapper & operator -=(float w);
	Wrapper operator *(float w);
	Wrapper & operator *=(float w);
	Wrapper operator /(float w);
	Wrapper & operator /=(float w);
private:
	float content[3];
};

