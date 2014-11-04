#pragma once

#include "Easing.h"

class Keyframe{
public:
	Keyframe(float _time, float _startValue, float _value, Easing::Type _interpolation);
	~Keyframe();

	float time;
	float startValue;
	float value;
	Easing::Type interpolation;

private:

};