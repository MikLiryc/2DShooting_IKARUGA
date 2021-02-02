#pragma once
#include "UNIT.h"
#include "ENEMY.h"
#define MAXBULLET 2000

class Player;

struct tagBullet
{
	RECT body;
	float centerX, centerY, speed, angle;
	int object, count, dmg, index;
	BULLETTYPE bulletType;
	PATTERNNUMBER patternNum;
	COLOR color;
	bool isFire, isCollide;
};

class bulletManager : public UNIT
{
private:
	typedef std::vector<tagBullet*> vectorBullets;
	typedef std::vector<tagBullet*>::iterator bulletIter;
	
	image* playerBulletImg;
	image* enemyBulletImg;
	image* blastImg;
	image* laserBulletImg;
	image* carrierBulletImg;
	vectorBullets vBullets;
	Player* _player;
	Enemy* _enemy;

	int count;
	int carrierCount;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setBullet(float centerX, float centerY, float speed, float angle, int object,  BULLETTYPE bulletType, COLOR color, PATTERNNUMBER patternNum = NO);
	void bulletMove();
	void bossPat2BulletMove();
	void bulletCollision();
	void carrierBulletFire();
	void carrierAnimation();
	BOOL deleteAll();

	void setPlayerAD(Player* player) { _player = player; }
	void setEnemyAD(Enemy* enemy) { _enemy = enemy; }
	vectorBullets getBulletVector() { return vBullets; }
	RECT getBulletBody() 
	{
		for (auto iter : vBullets)
		{
			if (iter->isFire)
			{
				return iter->body;
			}
		}
	}
};

