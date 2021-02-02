#pragma once
#include "gameNode.h"
#include "PLAYER.h"
#include "BULLET.h"
#include "ENEMY.h"

class mainGame : public gameNode
{
private:
	image* bgImg;
	image* bg_part;
	image* bg_bar;
	RECT bgRect;
	float loopY;
	int barY, gaugeCount;
	int alpha;

	Player* player;
	bulletManager* bullet;
	Enemy* enemy;

	bool isShowRect;
	bool isGameOver;

public:
	HRESULT init();
	void release();
	void update();
	void render();


	mainGame() {}
	~mainGame() {}
};