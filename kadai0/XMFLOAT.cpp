#include "stdafx.h"

XMFLOAT2 operator+(const XMFLOAT2& vector1, const XMFLOAT2& vector2)
{
	XMFLOAT2 vector = { vector1.x + vector2.x, vector1.y + vector2.y };
	return vector;
}
XMFLOAT2 operator+=(XMFLOAT2& vector1, const XMFLOAT2& vector2)
{
	vector1.x += vector2.x;
	vector1.y += vector2.y;
	return vector1;
}
XMFLOAT2 operator-(const XMFLOAT2& vector1, const XMFLOAT2& vector2)
{
	XMFLOAT2 vector = { vector1.x - vector2.x, vector1.y - vector2.y };
	return vector;
}
XMFLOAT2 operator-=(XMFLOAT2& vector1, const XMFLOAT2& vector2)
{
	vector1.x -= vector2.x;
	vector1.y -= vector2.y;
	return vector1;
}
XMFLOAT2 operator*(const XMFLOAT2& vector1, const float& _num)
{
	XMFLOAT2 vector = { vector1.x * _num, vector1.y * _num };
	return vector;
}
XMFLOAT2 operator*=(XMFLOAT2& vector1, const float& _num)
{
	vector1.x *= _num;
	vector1.y *= _num;
	return vector1;
}
XMFLOAT2 operator/(const XMFLOAT2& vector1, const float& _num)
{
	XMFLOAT2 vector = { vector1.x / _num, vector1.y / _num };
	return vector;
}
XMFLOAT2 operator/=(XMFLOAT2& vector1, const float& _num)
{
	vector1.x /= _num;
	vector1.y /= _num;
	return vector1;
}