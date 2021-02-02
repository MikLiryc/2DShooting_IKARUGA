#include "stdafx.h"
#include "BULLET.h"
#include "ENEMY.h"
#include "PLAYER.h"

HRESULT bulletManager::init()
{
	IMAGEMANAGER->addFrameImage("PLAYERBULLETS", "image/playerBullets.bmp", 26, 50, 2, 1, true);
	playerBulletImg = IMAGEMANAGER->findImage("PLAYERBULLETS");
	IMAGEMANAGER->addFrameImage("ENEMYBULLETS", "image/enemyBullets.bmp", 26, 13, 2, 1, true);
	enemyBulletImg = IMAGEMANAGER->findImage("ENEMYBULLETS");
	IMAGEMANAGER->addFrameImage("BLAST", "image/blast.bmp", 82, 50, 2, 1, true);
	blastImg = IMAGEMANAGER->findImage("BLAST");
	IMAGEMANAGER->addImage("LASER_BULLET", "image/laserBullet.bmp", 30, 30, true);
	laserBulletImg = IMAGEMANAGER->findImage("LASER_BULLET");
	IMAGEMANAGER->addFrameImage("CARRIER", "image/carrierBullet.bmp", 360, 100, 3, 1, true);
	carrierBulletImg = IMAGEMANAGER->findImage("CARRIER");


	for (int i = 0; i < MAXBULLET; i++)
	{
		tagBullet* temp = new tagBullet;
		temp->centerX = 0;
		temp->centerY = 0;
		temp->speed = 0;
		temp->angle = 0;
		temp->object = 0;
		temp->dmg = 1;
		temp->index = 0;
		temp->count = 0;
		temp->bulletType = NORMAL;
		temp->color = WHITE;
		temp->isFire = false;
		temp->isCollide = false;
		temp->body = RectMakeCenter(temp->centerX, temp->centerY, 10, 10);
		vBullets.push_back(temp);
	}

	carrierCount = count = 0;

	return S_OK;
}

void bulletManager::release()
{
	this->deleteAll();
}

void bulletManager::update()
{
	count++;
	carrierCount++;
	bulletMove();
	bulletCollision();
	carrierAnimation();
	carrierBulletFire();
	bossPat2BulletMove();
}

void bulletManager::render()
{
	for (auto iter : vBullets)
	{
		if (iter->bulletType == NORMAL && iter->isFire)
		{
			if (iter->object == PLAYEROBJECT)
			{
				playerBulletImg->frameRender(getMemDC(),
					iter->centerX - 6, iter->centerY - 25, iter->color, 0);
			}
			else if (iter->object == ENEMYOBJECT)
			{
				enemyBulletImg->frameRender(getMemDC(),
					iter->centerX - 6, iter->centerY - 6, iter->color, 0);
			}
		}
		else if (iter->bulletType == LASER && iter->isFire)
		{
			laserBulletImg->render(getMemDC(),
				iter->centerX - 15, iter->centerY - 15);
		}
		else if (iter->bulletType == CARRIER && iter->isFire)
		{
			carrierBulletImg->frameRender(getMemDC(), iter->centerX - 60, iter->centerY - 50,
				iter->index, 0);
		}
		if (iter->isCollide && iter->bulletType == NORMAL)
		{
			blastImg->frameRender(getMemDC(), iter->centerX - 20, iter->centerY - 25, iter->color, 0);
		}
	}
}

void bulletManager::setBullet(float centerX, float centerY, float speed, float angle, int object, BULLETTYPE bulletType, COLOR color, PATTERNNUMBER patternNum)
{
	for (auto iter : vBullets)
	{
		if (iter->isFire || iter->isCollide) continue;
		iter->centerX = centerX;
		iter->centerY = centerY;
		iter->speed = speed;
		iter->angle = angle;
		iter->object = object;
		iter->patternNum = patternNum;
		iter->bulletType = bulletType;
		iter->color = color;
		iter->isFire = true;
		iter->isCollide = false;
		break;
	}
}

void bulletManager::bulletMove()
{
	for (auto iter : vBullets)
	{
		if (iter->centerY + 10 < 0 || iter->centerY - 10 > WINSIZEY
			|| iter->centerX - 10 > WINSIZEX || iter->centerX + 10 < 0)
		{
			iter->isFire = false;
		}
		if (iter->isFire && iter->bulletType == NORMAL)
		{
			switch (iter->object)
			{
			case PLAYEROBJECT:
				iter->centerX += cosf(iter->angle) * iter->speed;
				iter->centerY += -sinf(iter->angle) * iter->speed;
				iter->body = RectMakeCenter(iter->centerX, iter->centerY, 11, 50);
				break;
			case ENEMYOBJECT:
				iter->centerX += cosf(iter->angle) * iter->speed;
				iter->centerY += -sinf(iter->angle) * iter->speed;
				iter->body = RectMakeCenter(iter->centerX, iter->centerY, 11, 11);
				break;
			}
		}
		if (iter->isFire && iter->bulletType == CARRIER)
		{
			iter->centerX += cosf(iter->angle) * iter->speed;
			iter->centerY += -sinf(iter->angle) * iter->speed;
			iter->body = RectMakeCenter(iter->centerX, iter->centerY, 100, 100);
		}
		if (iter->isFire && iter->bulletType == LASER)
		{
			float tempDis, dis, enemyCenterX, enemyCenterY;;
			tempDis = 5000;
			if (_enemy->getIsBossAppear() == false)
			{
				for (auto enemyIter : _enemy->getSmallEmenyVector())
				{
					dis = sqrtf(pow(iter->centerX - enemyIter->centerX, 2) + pow(iter->centerY - enemyIter->centerY, 2));
					if (tempDis > dis)
					{
						tempDis = dis;
						enemyCenterX = enemyIter->centerX;
						enemyCenterY = enemyIter->centerY;
					}
				}
				if (iter->angle < -atan2f(enemyCenterY - iter->centerY, enemyCenterX - iter->centerX))
				{
					iter->angle += 0.08f;
				}
				else if (iter->angle > -atan2f(enemyCenterY - iter->centerY, enemyCenterX - iter->centerX))
				{
					iter->angle -= 0.08f;
				}
				iter->centerX += cosf(iter->angle) * iter->speed;
				iter->centerY += -sinf(iter->angle) * iter->speed;
				iter->body = RectMakeCenter(iter->centerX, iter->centerY, 30, 30);
			}
			else if (_enemy->getIsBossAppear() == true)
			{
				if (iter->angle < -atan2f(_enemy->getBossCenterY()- iter->centerY, _enemy->getBossCenterX() - iter->centerX))
				{
					iter->angle += 0.08f;
				}
				else if (iter->angle > -atan2f(_enemy->getBossCenterY() - iter->centerY, _enemy->getBossCenterX() - iter->centerX))
				{
					iter->angle -= 0.08f;
				}
				iter->centerX += cosf(iter->angle) * iter->speed;
				iter->centerY += -sinf(iter->angle) * iter->speed;
				iter->body = RectMakeCenter(iter->centerX, iter->centerY, 30, 30);
			}
		}
	}
}

void bulletManager::bossPat2BulletMove()
{
	if (_enemy->getIsPattern2Start())
	{
		for (auto iter : vBullets)
		{
			if (iter->patternNum == BOSSPAT2)
			{
				iter->angle = -atan2(_player->getPlayerCenterY() - _enemy->getBossCenterY(),
					_player->getPlayerCenterX() - _enemy->getBossCenterX());
			}
		}
	}
	else if (!_enemy->getIsPattern2Start())
	{
		for (auto iter : vBullets)
		{
			if (iter->isFire && iter->patternNum == BOSSPAT2)
			{
				iter->angle = -atan2(_player->getPlayerCenterY() - _enemy->getBossCenterY(),
					_player->getPlayerCenterX() - _enemy->getBossCenterX());
				iter->speed += 0.05;
			}
		}
	}
}

void bulletManager::bulletCollision()
{
	for (auto iter : vBullets)
	{
		//플레이어가 발사한 총알만 검사
		if (iter->isFire && iter->object == PLAYEROBJECT)
		{
			RECT temp;
			for (auto enemyIter : _enemy->getSmallEmenyVector())
			{
				if (IntersectRect(&temp, &iter->body, &enemyIter->body) 
					&& enemyIter->isAppear && !enemyIter->isCrash)
				{   
					iter->count = 3;
					enemyIter->hp -= iter->dmg;
					iter->isFire = false;
					iter->isCollide = true;
				}
			}
			if (IntersectRect(&temp, &iter->body, &_enemy->getBossBody()) && _enemy->getIsBossAppear() == true)
			{
				iter->count = 3;
				_enemy->setBossHp(_enemy->getBossHp() - iter->dmg);
				iter->isFire = false;
				iter->isCollide = true;
			}
		}
		else if (iter->isFire && iter->object == ENEMYOBJECT && _player->getPlayerState() != SPAWN)
		{
			RECT temp;
			if (IntersectRect(&temp, &iter->body, &_player->getBarrierBody())
				&& _player->getPlayerColor() == iter->color)
			{
				if (_player->getPlayerGauge() < 100)
				{
					_player->setPlayerGauge(_player->getPlayerGauge() + 2);
				}
				iter->isFire = false;
			}
			else if (IntersectRect(&temp, &iter->body, &_player->getPlayerBody())
				&& _player->getPlayerColor() != iter->color)
			{
				_player->setPlayerHp(_player->getPlayerHp() - iter->dmg);
				_player->setPlayerIsDead(true);
				iter->isFire = false;
			}
		}
		if (iter->count > 0)
		{
			iter->count--;
		}
		else
		{
			iter->isCollide = false;
		}
	}

}

void bulletManager::carrierBulletFire()
{
	if (carrierCount % 70 == 0)
	{
		for (auto iter : vBullets)
		{
			if (iter->isFire && iter->bulletType == CARRIER)
			{
				for (int i = 0; i < 36; i++)
				{
					setBullet(iter->centerX, iter->centerY, 2.0f, 0.0f + (2 * M_PI) / 36 * i, ENEMYOBJECT, NORMAL, iter->color, NO);
				}
			}
		}
	}
}

void bulletManager::carrierAnimation()
{
	if (count % 5 == 0)
	{
		for (auto iter : vBullets)
		{
			if (iter->isFire && iter->bulletType == CARRIER)
			{
				iter->index++;
				if (iter->index > 2)
				{
					iter->index = 0;
				}
			}
		}
	}
}

BOOL bulletManager::deleteAll()
{
	vBullets.clear();
	return true;
}