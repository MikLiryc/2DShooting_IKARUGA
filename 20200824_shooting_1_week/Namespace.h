#pragma once

//============================================================================
//				## namespace ## MY_NAMESPACE
//============================================================================

#define PI2 (M_PI*2)		//360도
#define PI_2 (M_PI/2)		//90도
#define PI_4 (M_PI/4)		//45도
#define PI_8 (M_PI/8)		//22.5도

namespace MY_NAMESPACE
{
	//두점 사이의 거리, 각도
	float getDistance(float startX, float startY, float endX, float endY);
	float getAngle(float startX, float startY, float endX, float endY);
	


};

