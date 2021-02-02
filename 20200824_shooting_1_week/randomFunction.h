#pragma once
#include"singletonBase.h"

class randomFunction : public singletonBase<randomFunction>
{
public:
	randomFunction() {
		srand(GetTickCount());
	}
	~randomFunction() {}

	inline int getInt(int num)
	{
		return rand() % num;
	}

	inline int range(int from, int to)
	{
		return rand() % (to - from + 1) + from;
	}

	// 3/2 = 1 (정수형)
	// 3.0 / 2.0 = 1.5 (실수형)
	/*
	rand () -> 0 ~ 32767 
	RAND_MAX -> 32767
	rand() % RAND_MAX -> 값의 범위: 0.0f ~ 1.0f
	*/
	inline float getFloat(float num)
	{
		return ((float)rand() / (float)RAND_MAX) * num;
	}

	inline float floatRange(float from, float to)
	{
		float rnd = ((float)rand() / (float)RAND_MAX);
		return (rnd * (to - from)) + from;
	}

};