#pragma once
class Wrapper
{
public:
	Wrapper() = default;
	~Wrapper() = default;
	float& operator[](size_t el);
private:
	float content[3];
};

