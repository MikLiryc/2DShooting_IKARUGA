#include "stdafx.h"
#include "Namespace.h"

float MY_NAMESPACE::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrtf(x*x + y * y);
}

float MY_NAMESPACE::getAngle(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return -atan2f(y, x);
}
