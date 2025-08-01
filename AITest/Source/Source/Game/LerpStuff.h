#pragma once

#define Deg2Rad 0.0174532925f
#define Rad2Deg 1.f / 0.0174532925f

inline float LerpTrue(const float a, const float b, const float aTime)
{
	float aa = a * (1 - aTime);
	float bb = b * aTime;
	return aa + bb;
};