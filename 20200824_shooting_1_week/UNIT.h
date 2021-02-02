#pragma once
#include "gameNode.h"

enum OBJECT
{
	PLAYEROBJECT,
	ENEMYOBJECT
};

enum COLOR
{
	WHITE,
	BLACK
};

enum BULLETTYPE
{
	NORMAL,
	LASER,
	CARRIER
};

enum PATTERNNUMBER
{
	NO = 0,
	LEFTTORIGHT = 1,
	RIGHTTOLEFT,
	LEFTTOPTORIGHTBOTTOM,
	RIGHTTOPTOLEFTBOTTOM,
	DOWNANDGOBACK,
	DOWNANDSTAY,
	LEFTTOPTORIGHTTOP,
	RIGHTTOPTOLEFTTOP,
	BOSSPAT2
};

class UNIT : public gameNode
{
protected:
	int width, height;
	float centerX, centerY, speed;

public:
	UNIT() {}
	virtual ~UNIT() {}

	HRESULT init() = 0;
	void release() = 0;
	void update() = 0;
	void render() = 0;
};

