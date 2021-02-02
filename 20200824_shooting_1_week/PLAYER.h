#pragma once
#include "UNIT.h"

class bulletManager;

enum PLAYERSTATE
{
	IDLE,
	LEFT,
	RIGHT,
	SPAWN
};

class Player : public UNIT
{
private:
	bulletManager* _bulletManager;
	image* playerWhite;
	image* playerBlack;
	image* thrusterWhite;
	image* barrierImg;
	PLAYERSTATE state;
	COLOR playerColor;
	RECT playerBody;
	RECT barrierBody;

	int thrusterIndex, barrierIndex, count, barrierAlpha, playerIndex, hp, lifeCount, comboGauge, spawnAlpha, spawnCount;
	bool isDead;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	
	void initImages();
	void playerAnimation();
	void thrusterAnimation();
	void barrierAnimation();
	void fireBullet();
	void fireLaser();
	void respawn();
	void spawnMove();

	float getPlayerCenterX() { return centerX; }
	float getPlayerCenterY() { return centerY; }
	bool verifyPlayerIsDead() { return isDead; }
	void setPlayerIsDead(bool deadState) { isDead = deadState; }
	PLAYERSTATE getPlayerState() { return state; }
	int getPlayerHp() { return hp; }
	void setPlayerHp(int _hp) { hp = _hp; }
	int getPlayerLife() { return lifeCount; }
	int getPlayerGauge() { return comboGauge; }
	void setPlayerGauge(int gauge) { comboGauge = gauge; }
	RECT getPlayerBody() { return playerBody; }
	RECT getBarrierBody() { return barrierBody; }
	COLOR getPlayerColor() { return playerColor; }

	void setBulletManagerAD(bulletManager* bm) { _bulletManager = bm; }
};

