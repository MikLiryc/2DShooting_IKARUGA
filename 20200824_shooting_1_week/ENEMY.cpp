#include "stdafx.h"
#include "ENEMY.h"
#include "BULLET.h"
#include "PLAYER.h"

HRESULT Enemy::init()
{
	initImages();
	
	DAGBCount = 
		RTLCount = 
		LTRCount = 
		spawnCount = 
		count = 0;
	RTLSpawnCount = LTRSpawnCount = DAGBSpawnCount  = lESpawnCount = 0;
	patternCounter = 1;
	rndPattern = 5;
	patternPos = 0;
	pat2PosX = -40;
	pat2PosY = 90;
	bossCrashIndex = bossCrashIndex2 = bossCrashIndex3 = bossCrashIndex4 = 0;
	bossPatternCounterOne = bossPatternCounterTwo = bossPatternCounterThree = bossCount = 0;
	pat1Angle = 0.0f;
	bossHpBar = 0.0f;
	isSpawn = false;
	isBossAppear = false;
	isRotateLeft = false;
	isPattern2Start = false;
	is1 = is2 = is3 = false;
	
	Boss = new tagEnemy;
	Boss->hp = 1000;
	Boss->width = 300;
	Boss->height = 350;
	Boss->crashIndex = 0;
	Boss->crashCount = 0;
	Boss->fireCount = 0;
	Boss->enemyColor = WHITE;
	Boss->centerX = WINSIZEX / 2;
	Boss->centerY = -180;
	Boss->speed = 1.0f;
	Boss->angle = 3 * PI_2;
	Boss->isCrash = false;
	Boss->isAppear = false;
	Boss->isDown = true;

	for (int i = 0; i < MAXENEMY; i++)
	{
		tagEnemy* temp = new tagEnemy;
		temp->hp = 2;
		temp->width = 50;
		temp->height = 57;
		temp->crashIndex = 0;
		temp->crashCount = 0;
		temp->fireCount = 0;
		temp->enemyColor = WHITE;
		temp->centerX = WINSIZEX/2;
		temp->centerY = WINSIZEY/2;
		temp->speed = 3.0f;
		temp->angle = 0.0f;
		temp->isCrash = false;
		temp->isAppear = false;
		temp->isDown = true;
		enemyVector.push_back(temp);
	}
	return S_OK;
}

void Enemy::release()
{
}

void Enemy::update()
{
	if (!isBossAppear)
	{
		bossCount++;
		patternCounter++;
		count++;
		if (patternCounter % 600 == 0)
		{
			rndPattern = RND->getInt(4);
			patternCounter = 1;
			lESpawnCount = 0;
			count = 0;
			patternPos = 0;
			std::cout << rndPattern << std::endl;
		}
		switch (rndPattern)
		{
		case 0:
			if (count % 150 == 0)
			{
				isSpawn = true;
			}
			smallEnemyLeftToRight();
			smallEnemyRightToLeft();
			break;
		case 1:
			if (count % 150 == 0)
			{
				isSpawn = true;
			}
			smallEnemyLeftToRight();
			smallEnemyDownAndGoBack();
			break;
		case 2:
			if (count % 150 == 0)
			{
				isSpawn = true;
			}
			smallEnemyLeftToRight();
			smallEnemyDownAndGoBack();
			break;
		case 3:
			if (count % 150 == 0)
			{
				isSpawn = true;
			}
			smallEnemyDownAndGoBack();
			largeEnemyPattern();
			break;
		}
		for (auto iter : enemyVector)
		{
			if (iter->isAppear)
			{
				iter->body = RectMakeCenter(iter->centerX, iter->centerY, iter->width, iter->height);
			}
		}
		enemyMove();
		enemyFireBullet();
		enemyDie();
		enemyCrashAnimation();
		bossAppear();
	}
	else if (isBossAppear)
	{
		if (Boss->hp > 0)
		{
			bossMove();
			bossHpBar = 0.96 * Boss->hp;
			patternCounter++;
			count++;
			if (patternCounter % 300 == 0)
			{
				rndPattern = RND->getInt(4);
				patternCounter = 1;
				lESpawnCount = 0;
				count = 0;
				patternPos = 0;
				patternCounter = -500;
				std::cout << rndPattern << std::endl;
			}
			switch (rndPattern)
			{
			case 0:
				bossPattern1();
				break;
			case 1:
				bossPattern2();
				break;
			case 2:
				bossPattern1();
				smallEnemyLeftToRight();
				break;
			case 3:
				bossPattern2();
				smallEnemyRightToLeft();
				smallEnemyDownAndGoBack();
				break;
			}
			enemyMove();
			enemyFireBullet();
			enemyDie();
			enemyCrashAnimation();
			bossAppear();
		}
		else if (Boss->hp <= 0)
		{
			for (auto iter : _bullet->getBulletVector())
			{
				if (iter->object == ENEMYOBJECT)
				{
					iter->isFire = false;
				}
			}
		}
	}

}

void Enemy::render()
{
	for (auto iter : enemyVector)
	{
		switch (iter->enemyType)
		{
		case SMALL:
			if (iter->isAppear && !iter->isCrash)
			{
				smallEnemyImg->frameRender(getMemDC(),
					iter->centerX - 25,
					iter->centerY - 28,
					iter->enemyColor, 0);
			}
			if (!iter->isAppear && iter->isCrash)
			{
				smallEnemyCrashImg->frameRender(getMemDC(),
					iter->centerX - 20,
					iter->centerY - 20,
					iter->crashIndex, 0);
			}
			break;
		case LARGE:
			if (iter->isAppear && !iter->isCrash)
			{
				largeEnemyImg->render(getMemDC(),
					iter->centerX - 75,
					iter->centerY - 75);
			}
			if (!iter->isAppear && iter->isCrash)
			{
				largeEnemyCrashImg->frameRender(getMemDC(),
					iter->centerX - 75,
					iter->centerY - 75,
					iter->crashIndex, 0);
			}
			break;
		}
	}
	if (Boss->isAppear)
	{
		bossImg->render(getMemDC(), Boss->centerX - 180, Boss->centerY - 180);
		IMAGEMANAGER->findImage("BOSS_HP")->render(getMemDC(), 0, 0, 0, 0, bossHpBar, 40);
	}
	if (Boss->hp <= 0)
	{
		bossCrashIndex++;
		bossCrashImg->frameRender(getMemDC(), Boss->centerX - 150, Boss->centerY - 120, bossCrashIndex, 0);
		if (bossCrashIndex >= 32)
		{
			bossCrashIndex2++;
			bossCrashImg->frameRender(getMemDC(), Boss->centerX - 80, Boss->centerY + 80, bossCrashIndex2, 0);
		}
		if (bossCrashIndex2 >= 32)
		{
			bossCrashIndex3++;
			bossCrashImg->frameRender(getMemDC(), Boss->centerX +10, Boss->centerY - 20, bossCrashIndex3, 0);
		}
		if (bossCrashIndex3 >= 32)
		{
			bossCrashIndex4++;
			bossCrashImg->frameRender(getMemDC(), Boss->centerX + 60, Boss->centerY -170, bossCrashIndex4, 0);
		}
		if (bossCrashIndex4 >= 100)
		{

		}
	}
	
}

void Enemy::initImages()
{
	IMAGEMANAGER->addFrameImage("SMALL", "image/small_enemy.bmp", 100, 57, 2, 1, true);
	smallEnemyImg = IMAGEMANAGER->findImage("SMALL");
	IMAGEMANAGER->addFrameImage("SMALL_CRASH", "image/smallEnemyCrash.bmp", 1000, 50, 20, 1, true);
	smallEnemyCrashImg = IMAGEMANAGER->findImage("SMALL_CRASH");
	IMAGEMANAGER->addFrameImage("LARGE_CRASH", "image/largeEnemyCrash.bmp", 3000, 150, 20, 1, true);
	largeEnemyCrashImg = IMAGEMANAGER->findImage("LARGE_CRASH");
	IMAGEMANAGER->addImage("LARGE", "image/largeEnemy.bmp", 150, 150, true);
	largeEnemyImg = IMAGEMANAGER->findImage("LARGE");
	IMAGEMANAGER->addImage("BOSS", "image/boss.bmp", 360, 360, true);
	bossImg = IMAGEMANAGER->findImage("BOSS");
	IMAGEMANAGER->addImage("BOSS_HP", "image/boss_hp_bar.bmp", 960, 40);
	IMAGEMANAGER->addFrameImage("BOSS_EXPLOSION", "image/boss_explosion.bmp", 8192, 128, 64, 1, true);
	bossCrashImg = IMAGEMANAGER->findImage("BOSS_EXPLOSION");

}

void Enemy::smallEnemyLeftToRight()
{
	if (isSpawn)
	{
		RTLSpawnCount++;
		if (RTLSpawnCount % 25 == 0)
		{
			setEnemy(-50, 200, 0.0f, LEFTTORIGHT, WHITE);
			setEnemy(-100, 250, 0.0f, LEFTTORIGHT, BLACK);
		}
		else if (RTLSpawnCount >= 99)
		{
			RTLSpawnCount = 0;
			isSpawn = false;
		}
	}
}

void Enemy::smallEnemyRightToLeft()
{
	if (isSpawn)
	{
		LTRSpawnCount++;
		if (LTRSpawnCount % 25 == 0)
		{
			setEnemy(WINSIZEX + 50, 100, M_PI, RIGHTTOLEFT, WHITE);
			setEnemy(WINSIZEX + 100, 150, M_PI, RIGHTTOLEFT, BLACK);
		}
		else if (LTRSpawnCount >= 99)
		{
			LTRSpawnCount = 0;
			isSpawn = false;
		}
	}
}

void Enemy::smallEnemyDownAndGoBack()
{
	if (isSpawn)
	{
		DAGBSpawnCount++;
		if (DAGBSpawnCount % 20 == 0)
		{
			setEnemy(WINSIZEX / 2 - 40  - 160 * patternPos, -25, 3 * M_PI / 2, DOWNANDGOBACK, WHITE);
			setEnemy(WINSIZEX / 2 + 40  + 160* patternPos, -75, 3 * M_PI / 2, DOWNANDGOBACK, BLACK);
			patternPos += 1;
		}
		else if (DAGBSpawnCount >= 99)
		{
			DAGBSpawnCount = 0;
			patternPos = 0;
			isSpawn = false;
		}
	}
}

void Enemy::largeEnemyPattern()
{
	if (isSpawn)
	{
		lESpawnCount++;
		if (lESpawnCount == 100)
		{
			setEnemy(240, -75, 3 * PI_2, DOWNANDSTAY, WHITE, LARGE, 50);
			setEnemy(720, -75, 3 * PI_2, DOWNANDSTAY, BLACK, LARGE, 50);
			isSpawn = false;
		}
	}
}

void Enemy::bossAppear()
{
	if (bossCount >= 4000)
	{
		isBossAppear = true;
		Boss->isAppear = true;
	}
}

void Enemy::bossMove()
{
	if (Boss->centerY < 250)
	{
		Boss->centerY += Boss->speed;
		Boss->body = RectMakeCenter(Boss->centerX, Boss->centerY, 300, 100);
	}
}

void Enemy::bossPattern1()
{
	bossPatternCounterOne++;
	pat1Angle += M_PI / 108;
	if (bossPatternCounterOne % 5 == 0)
	{
		_bullet->setBullet(Boss->centerX + 135, Boss->centerY + 10, 2.0f, M_PI_4 + pat1Angle, ENEMYOBJECT, NORMAL, BLACK);
		_bullet->setBullet(Boss->centerX + 135, Boss->centerY + 10, 2.0f, 3 * M_PI_4 + pat1Angle, ENEMYOBJECT, NORMAL, BLACK);
		_bullet->setBullet(Boss->centerX + 135, Boss->centerY + 10, 2.0f, 5 * M_PI_4 + pat1Angle, ENEMYOBJECT, NORMAL, BLACK);
		_bullet->setBullet(Boss->centerX + 135, Boss->centerY + 10, 2.0f, 7 * M_PI_4 + pat1Angle, ENEMYOBJECT, NORMAL, BLACK);
		
		_bullet->setBullet(Boss->centerX - 135, Boss->centerY + 10, 2.0f, 2 * M_PI_4 - pat1Angle, ENEMYOBJECT, NORMAL, WHITE);
		_bullet->setBullet(Boss->centerX - 135, Boss->centerY + 10, 2.0f, 4 * M_PI_4 - pat1Angle, ENEMYOBJECT, NORMAL, WHITE);
		_bullet->setBullet(Boss->centerX - 135, Boss->centerY + 10, 2.0f, 6 * M_PI_4 - pat1Angle, ENEMYOBJECT, NORMAL, WHITE);
		_bullet->setBullet(Boss->centerX - 135, Boss->centerY + 10, 2.0f, 8 * M_PI_4 - pat1Angle, ENEMYOBJECT, NORMAL, WHITE);
	}
	if (bossPatternCounterOne % 5 == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			_bullet->setBullet(Boss->centerX + 100, Boss->centerY - 160, 3.0f + 0.2 * i,
				-atan2f(_player->getPlayerCenterY() - (Boss->centerY - 160), _player->getPlayerCenterX() - (Boss->centerX + 100))
				, ENEMYOBJECT, NORMAL, WHITE);
			_bullet->setBullet(Boss->centerX - 100, Boss->centerY - 160, 3.0f + 0.2 * i,
				-atan2f(_player->getPlayerCenterY() - (Boss->centerY - 160), _player->getPlayerCenterX() - (Boss->centerX - 100))
				, ENEMYOBJECT, NORMAL, BLACK);
		}
	}
}

void Enemy::bossPattern2()
{
	bossPatternCounterTwo++;
	if (bossPatternCounterTwo % 500 == 0) { isPattern2Start = true; is1 = true; }
	if (isPattern2Start)
	{
		if (bossPatternCounterTwo % 5 == 0)
		{
			_bullet->setBullet(Boss->centerX + pat2PosX, Boss->centerY + pat2PosY, 0.0f, 3*M_PI/2, ENEMYOBJECT, NORMAL, BLACK, BOSSPAT2);
			_bullet->setBullet(Boss->centerX + pat2PosX, Boss->centerY - pat2PosY + 125, 0.0f, 3 * M_PI / 2, ENEMYOBJECT, NORMAL, WHITE, BOSSPAT2);

			_bullet->setBullet(Boss->centerX + 100 + pat2PosX, Boss->centerY - 150 + pat2PosY, 0.0f, 3*M_PI/2, ENEMYOBJECT, NORMAL, BLACK, BOSSPAT2);
			_bullet->setBullet(Boss->centerX + 100 + pat2PosX, Boss->centerY - 150 - pat2PosY + 125, 0.0f, 3 * M_PI / 2, ENEMYOBJECT, NORMAL, WHITE, BOSSPAT2);

			_bullet->setBullet(Boss->centerX - 100 + pat2PosX, Boss->centerY - 150 + pat2PosY, 0.0f, 3 * M_PI / 2, ENEMYOBJECT, NORMAL, BLACK, BOSSPAT2);
			_bullet->setBullet(Boss->centerX - 100 + pat2PosX, Boss->centerY - 150 - pat2PosY + 125, 0.0f, 3 * M_PI / 2, ENEMYOBJECT, NORMAL, WHITE, BOSSPAT2);
			if (is1 && !is2 && !is3)
			{
				pat2PosX += 6;
				if (pat2PosX >= 40)
				{
					is1 = false;
					is2 = true;
				}
			}
			else if (!is1 && is2 && !is3)
			{
				pat2PosX -= 3;
				pat2PosY -= 6;
				if (pat2PosY <= 10)
				{
					is2 = false;
					is3 = true;
				}
			}
			else if (!is1 && !is2 && is3)
			{
				pat2PosX -= 3;
				pat2PosY += 6;
				if (pat2PosX <= -40 && pat2PosY >= 90)
				{
					is3 = false;
				}
			}
			else if (!is1 && !is2 && !is3)
			{
				isPattern2Start = false;
			}
		}
	}
	if (bossPatternCounterTwo % 400 == 0)
	{
		_bullet->setBullet(Boss->centerX - 50, Boss->centerY, 1.0f, 7 * M_PI / 5, ENEMYOBJECT, CARRIER, BLACK, RIGHTTOLEFT);
		_bullet->setBullet(Boss->centerX + 50, Boss->centerY, 1.0f, 8 * M_PI / 5, ENEMYOBJECT, CARRIER, WHITE, LEFTTORIGHT);
	}
	std::cout << Boss->hp << std::endl;
}

void Enemy::bossPattern3()
{
}

void Enemy::setEnemy(float centerX, float centerY, float angle, PATTERNNUMBER patternNum, COLOR enemyColor, ENEMYTYPE enemyType, int hp)
{
	for (auto iter : enemyVector)
	{
		if (iter->isAppear || iter->isCrash) continue;
		iter->centerX = centerX;
		iter->centerY = centerY;
		iter->angle = angle;
		iter->enemyColor = enemyColor;
		iter->hp = hp;
		iter->crashCount = 0;
		iter->crashIndex = 0;
		iter->fireCount = 0;
		iter->patternNum = patternNum;
		iter->enemyType = enemyType;
		iter->body = RectMakeCenter(iter->centerX, iter->centerY, iter->width, iter->height);
		iter->isAppear = true;
		iter->isCrash = false;
		iter->isDown = true;
		break;
	}
}

void Enemy::enemyMove()
{
	for (auto iter : enemyVector)
	{
		if (iter->centerY - 100 < -200 || iter->centerY + 100 > 900 + 200
			|| iter->centerX - 100 > WINSIZEX + 200 || iter->centerX + 100 < -200)
		{
			iter->isAppear = false;
		}
		if (iter->isAppear)
		{
			if (iter->patternNum == LEFTTORIGHT || iter->patternNum == RIGHTTOLEFT)
			{
				iter->centerX += cosf(iter->angle) * iter->speed;
				iter->centerY += -sinf(iter->angle) * iter->speed;
			}
			else if (iter->patternNum == DOWNANDGOBACK)
			{
				if (iter->isDown)
				{
					iter->centerX += cosf(iter->angle) * iter->speed;
					iter->centerY += -sinf(iter->angle) * iter->speed;
					if (iter->centerY > 300) { iter->isDown = false; }
				}
				else if (!iter->isDown)
				{
					iter->centerX -= cosf(iter->angle) * iter->speed;
					iter->centerY -= -sinf(iter->angle) * iter->speed;
				}
			}
			else if (iter->patternNum = DOWNANDSTAY)
			{
				if (iter->isDown)
				{
					iter->centerX += cosf(iter->angle) * 1.0f;
					iter->centerY += -sinf(iter->angle) * 1.0f;
					if (iter->centerY > 300) { iter->isDown = false; }
				}
			}
		}
	}
}

void Enemy::enemyFireBullet()
{
	for (auto iter : enemyVector)
	{
		if (iter->isAppear)
		{
			switch (iter->patternNum)
			{
			case LEFTTORIGHT:
				iter->fireCount++;
				if (iter->fireCount % 10 == 0 && iter->fireCount <= 99)
				{
					_bullet->setBullet(
						iter->centerX, iter->centerY,
						4.0f, 8 * M_PI / 5, ENEMYOBJECT, NORMAL,
						iter->enemyColor);
				}
				if (iter->fireCount >= 150)
				{
					iter->fireCount = 0;
				}
				break;
			case RIGHTTOLEFT:
				iter->fireCount++;
				if (iter->fireCount % 10 == 0 && iter->fireCount <= 99)
				{
					_bullet->setBullet(iter->centerX, iter->centerY,
						4.0f, 7 * M_PI / 5, ENEMYOBJECT, NORMAL,
						iter->enemyColor);
				}
				if (iter->fireCount >= 150)
				{
					iter->fireCount = 0;
				}
				break;
			case DOWNANDGOBACK:
				iter->fireCount++;
				if (iter->fireCount % 10 == 0 && iter->fireCount <= 100)
				{
					_bullet->setBullet(iter->centerX, iter->centerY, 3.0f, 
						-atan2f(_player->getPlayerCenterY() - iter->centerY, _player->getPlayerCenterX() - iter->centerX)
						, ENEMYOBJECT, NORMAL,
						iter->enemyColor);
				}
				if (iter->fireCount >= 150)
				{
					iter->fireCount = 0;
				}
				break;
			case DOWNANDSTAY:
				iter->fireCount++;
				if (iter->fireCount % 300 == 0)
				{
					if (iter->enemyColor == WHITE)
					{
						_bullet->setBullet(iter->centerX, iter->centerY,
							1.0f, 2 * M_PI - 0.5f, ENEMYOBJECT, CARRIER,
							iter->enemyColor);
					}
					else if (iter->enemyColor == BLACK)
					{
						_bullet->setBullet(iter->centerX, iter->centerY,
							1.0f, M_PI + 0.5f, ENEMYOBJECT, CARRIER,
							iter->enemyColor);
					}
				}
				if (iter->fireCount >=599)
				{
					iter->fireCount = 0;
				}
				break;


			}
		}
	}
}

void Enemy::enemyDie()
{
	for (auto iter : enemyVector)
	{
		if (iter->hp <= 0 && iter->isAppear && !iter->isCrash)
		{
			iter->isAppear = false;
			iter->isCrash = true;
		}
	}
	if (Boss->hp <= 0 && Boss->isAppear && !Boss->isCrash)
	{
		Boss->isCrash = true;
	}
}

void Enemy::enemyCrashAnimation()
{
	for (auto iter : enemyVector)
	{
		if (!iter->isAppear && iter->isCrash)
		{
			iter->crashCount++;
			if (count % 5 == 0)
			{
				iter->crashIndex++;
				if (iter->crashIndex > 19)
				{
					iter->isCrash = false;
				}
			}
		}
	}
}
