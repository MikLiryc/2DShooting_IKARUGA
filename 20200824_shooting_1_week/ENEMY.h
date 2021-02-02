#pragma once
#include "UNIT.h"
#define MAXENEMY 100

enum ENEMYTYPE
{
	SMALL,
	LARGE
};

struct tagEnemy
{
	RECT body;
	COLOR enemyColor;
	ENEMYTYPE enemyType;
	float centerX, centerY, speed, angle;
	int hp, width, height, crashIndex, crashCount, fireCount, patternNum;
	bool isCrash, isAppear, isDown;
};

struct tagBossCrash
{
	RECT body;
	float centerX, centerY;
	int width, height, crashIndex;
};

class bulletManager;
class Player;

class Enemy : public UNIT
{
private:
	bulletManager* _bullet;
	Player* _player;
	image* smallEnemyImg;
	image* smallEnemyCrashImg;
	image* largeEnemyCrashImg;
	image* largeEnemyImg;
	image* bossImg;
	image* bossCrashImg;
	
	typedef std::vector<tagEnemy*> EnemyVector;
	typedef std::vector<tagEnemy*>::iterator enemyIter;
	EnemyVector enemyVector;
	tagEnemy* Boss;

	int count, spawnCount, bossCount, patternCounter, rndPattern, patternPos;
	int RTLCount, LTRCount, DAGBCount;
	int RTLSpawnCount, LTRSpawnCount, DAGBSpawnCount, lESpawnCount;
	int bossPatternCounterOne, bossPatternCounterTwo, bossPatternCounterThree;
	float pat1Angle;
	int pat2PosX, pat2PosY;
	int pat2_PosX, pat2_PosY;
	int bossCrashIndex;
	int bossCrashIndex2;
	int bossCrashIndex3;
	int bossCrashIndex4;
	float bossHpBar;
	bool isPattern2Start;
	bool is1, is2, is3;
	bool is4, is5, is6;
	bool isRotateLeft;
	bool isSpawn, isBossAppear;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void initImages();
	void smallEnemyLeftToRight();
	void smallEnemyRightToLeft();
	void smallEnemyDownAndGoBack();
	void largeEnemyPattern();
	void bossAppear();
	void bossMove();
	void bossPattern1();
	void bossPattern2();
	void bossPattern3();
	void setEnemy(float centerX, float centerY, float angle, PATTERNNUMBER patternNum, COLOR enemyColor, ENEMYTYPE enemyType = SMALL, int hp = 1);
	void enemyMove();
	void enemyFireBullet();
	void enemyDie();
	void enemyCrashAnimation();

	EnemyVector getSmallEmenyVector() { return enemyVector; }
	float getLockedEnemyCenterX(tagEnemy* enemy) { return enemy->centerX; }
	float getLockedEnemyCenterY(tagEnemy* enemy) { return enemy->centerY; }
	tagEnemy* getBoss() { return Boss; }
	int getBossHp() { return Boss->hp; }
	void setBossHp(int hp) { Boss->hp = hp; }
	float getBossCenterX() { return Boss->centerX; }
	float getBossCenterY() { return Boss->centerY; }
	RECT getBossBody() { return Boss->body; }
	BOOL getIsBossAppear() { return isBossAppear; }
	BOOL getIsPattern2Start() { return isPattern2Start; }

	void setBulletManagerAD(bulletManager* bm) { _bullet = bm; }
	void setPlayerAD(Player* player) { _player = player; }
};

