#include "stdafx.h"
#include "PLAYER.h"
#include "BULLET.h"

HRESULT Player::init()
{
	initImages();

	centerX = WINSIZEX / 2;
	centerY = WINSIZEY - 100;
	playerBody = RectMakeCenter(centerX, centerY, 50, 50);
	speed = 4.0f;
	playerColor = WHITE;
	hp = 100;
	comboGauge = 0;

	count = barrierIndex = thrusterIndex = -1;
	barrierAlpha = 150;
	lifeCount = 5;
	spawnAlpha = 255;
	spawnCount = 0;

	isDead = false;


	return S_OK;
}

void Player::release()
{
	
}

void Player::update()
{
	if (!isDead)
	{
		count++;
		if (INPUT->GetKey('A') && centerX - 25 >= 5.0f)
		{
			state = LEFT;
			centerX -= speed;
		}
		if (INPUT->GetKey('D') && centerX + 25 <= WINSIZEX - 5.0f)
		{
			state = RIGHT;
			centerX += speed;
		}
		if (INPUT->GetKey('W') && centerY - 25 >= 5.0f)
		{
			centerY -= speed;
		}
		if (INPUT->GetKey('S') && centerY + 25 <= WINSIZEY - 5.0f)
		{
			centerY += speed;
		}
		if (INPUT->GetKeyUp('D') || INPUT->GetKeyUp('A'))
		{
			state = IDLE;
		}
		if (INPUT->GetKey(VK_NUMPAD0))
		{
			fireBullet();
		}
		if (INPUT->GetKeyDown(VK_LSHIFT))
		{
			if (playerColor == BLACK)
			{
				playerColor = WHITE;
				barrierIndex = -1;
			}
			else if (playerColor == WHITE)
			{
				playerColor = BLACK;
				barrierIndex = -1;
			}
		}

		playerBody = RectMakeCenter(centerX, centerY, 10, 10);
		barrierBody = RectMakeCenter(centerX, centerY, 94, 94);
		playerAnimation();
		thrusterAnimation();
		barrierAnimation();
		fireLaser();
	}
	else if (isDead)
	{
		count++;
		if (INPUT->GetKey('A') && centerX - 25 >= 5.0f)
		{
			centerX -= speed;
		}
		if (INPUT->GetKey('D') && centerX + 25 <= WINSIZEX - 5.0f)
		{
			centerX += speed;
		}
		if (INPUT->GetKey('W') && centerY - 25 >= 5.0f)
		{
			centerY -= speed;
		}
		if (INPUT->GetKey('S') && centerY + 25 <= WINSIZEY - 5.0f)
		{
			centerY += speed;
		}	
		if (INPUT->GetKeyDown(VK_LSHIFT))
		{
			if (playerColor == BLACK)
			{
				playerColor = WHITE;
				barrierIndex = -1;
			}
			else if (playerColor == WHITE)
			{
				playerColor = BLACK;
				barrierIndex = -1;
			}
		}
		if (INPUT->GetKey(VK_NUMPAD0))
		{
			fireBullet();
		}
		playerBody = RectMakeCenter(centerX, centerY, 10, 10);
		barrierBody = RectMakeCenter(centerX, centerY, 94, 94);
		respawn();
		spawnMove();
		playerAnimation(); 
		thrusterAnimation();
		barrierAnimation();
	}

}

void Player::render()
{
	switch (playerColor)
	{
	case WHITE:
		barrierImg->alphaFrameRender(getMemDC(), centerX - 47, centerY - 47, barrierIndex, WHITE, barrierAlpha);
		break;
	case BLACK:
		barrierImg->alphaFrameRender(getMemDC(), centerX - 47, centerY - 47, barrierIndex, BLACK, barrierAlpha);
		break;
	}
	           
	playerWhite->alphaFrameRender(getMemDC(), centerX - 25, centerY - 25, playerIndex, 0, spawnAlpha);
	thrusterWhite->alphaFrameRender(getMemDC(), centerX - 12.0f, centerY + 8.0f, thrusterIndex, 1, spawnAlpha);
	thrusterWhite->alphaFrameRender(getMemDC(), centerX + 6.0f, centerY + 8.0f, thrusterIndex, 1, spawnAlpha);

	for (int i = 0; i < lifeCount; i++)
	{
		IMAGEMANAGER->findImage("LIFE")->render(getMemDC(), 20, 338 - 50 * i);
	}
}

void Player::initImages()
{
	IMAGEMANAGER->addFrameImage("PLAYER_WHITE", "image/player_white.bmp", 250, 50, 5, 1, true);
	playerWhite = IMAGEMANAGER->findImage("PLAYER_WHITE");
	IMAGEMANAGER->addImage("PLAYER_BLACK", "image/player_black.bmp", 50, 50, true);
	playerBlack = IMAGEMANAGER->findImage("PLAYER_BLACK");
	IMAGEMANAGER->addFrameImage("THRUSTER_WHITE", "image/thrust_white.bmp", 36, 20, 6, 1, true);
	thrusterWhite = IMAGEMANAGER->findImage("THRUSTER_WHITE");
	IMAGEMANAGER->addFrameImage("BARRIER", "image/barrier.bmp", 658, 188, 7, 2, true);
	barrierImg = IMAGEMANAGER->findImage("BARRIER");
	IMAGEMANAGER->addImage("LIFE", "image/life.bmp", 50, 50, true);
}

void Player::playerAnimation()
{
	switch (state)
	{
	case IDLE:
		playerIndex = 2;
		break;
	case SPAWN:
		playerIndex = 2;
		spawnCount++;
			if (spawnCount % 20 == 0)
			{
				switch (spawnAlpha)
				{
				case 0:
					spawnAlpha = 255;
					break;
				case 255:
					spawnAlpha = 0;
					break;
				}
				if (spawnCount > 180)
				{
					state = IDLE;
					isDead = false;
				}
			}
	case LEFT:
		if (count % 5 == 0)
		{
			playerIndex--;
			if (playerIndex <= 0)
			{
				playerIndex = 0;
			}
		}
		break;
	case RIGHT:
		if (count % 5 == 0)
		{
			playerIndex++;
			if (playerIndex >= 4)
			{
				playerIndex = 4;
			}
		}
		break;
	}
}

void Player::thrusterAnimation()
{
	if (count % 5 == 0)
	{
		thrusterIndex++;
		if (thrusterIndex > 5)
		{
			thrusterIndex = 0;
		}
	}
}

void Player::barrierAnimation()
{
	if (count % 4 == 0)
	{
		barrierIndex++;
		if (barrierIndex > 6)
		{
			barrierIndex = 6;
		}
	}
}

void Player::fireBullet()
{
	if (count % 5 == 0)
	{
		_bulletManager->setBullet(centerX - 15, centerY - 55, 15.0f, M_PI / 2, PLAYEROBJECT, NORMAL, playerColor);
		_bulletManager->setBullet(centerX + 15, centerY - 55, 15.0f, M_PI / 2, PLAYEROBJECT, NORMAL, playerColor);
	}
}

void Player::fireLaser()
{
	if (comboGauge >= 100)
	{
		for (int i = 0; i < 5; i++)
		{
			_bulletManager->setBullet(centerX - 20, centerY, 14.0f, 0.0f + 0.15f * i, PLAYEROBJECT, LASER, playerColor);
			_bulletManager->setBullet(centerX + 20, centerY, 14.0f, M_PI - 0.15f * i, PLAYEROBJECT, LASER, playerColor);
		}
		comboGauge = 0;
	}
}

void Player::respawn()
{
	if (isDead && lifeCount > 0 && state != SPAWN)
	{
		centerX = WINSIZEX / 2;
		centerY = WINSIZEY + 50;
		lifeCount -= 1;
		spawnCount = 0;
		state = SPAWN;
	}
}

void Player::spawnMove()
{
	if (centerY + 25 >= WINSIZEY - 50)
	{
		centerY -= 5.0f;
	}
}
		
