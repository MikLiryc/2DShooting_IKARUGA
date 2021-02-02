#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();

	IMAGEMANAGER->addImage("BACKGROUND", "image/background.bmp", 960, 1440, true);
	bgImg = IMAGEMANAGER->findImage("BACKGROUND");
	IMAGEMANAGER->addImage("BG_PART", "image/bg_part.bmp", 960, 900, true);
	bg_part = IMAGEMANAGER->findImage("BG_PART");
	IMAGEMANAGER->addImage("BG_BAR", "image/bg_bar.bmp", 47, 488);
	bg_bar = IMAGEMANAGER->findImage("BG_BAR");
	bgRect = RectMake(0, 0, WINSIZEX, WINSIZEY);

	IMAGEMANAGER->addImage("GAMESTART", "image/gameStart.bmp", 960, 500, true);
	IMAGEMANAGER->addImage("STAGECLEAR", "image/stageClear.bmp", 960, 500, true);

	player = new Player;
	bullet = new bulletManager;
	enemy = new Enemy;

	player->setBulletManagerAD(bullet);
	enemy->setBulletManagerAD(bullet);
	enemy->setPlayerAD(player);

	bullet->setPlayerAD(player);
	bullet->setEnemyAD(enemy);

	player->init();
	enemy->init();
	bullet->init();

	alpha = 255;
	loopY = 0;
	barY = 0;
	gaugeCount = 0;
	isShowRect = false;
	isGameOver = false;

	return S_OK;
}

//=============================================================
//	## ���� ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();

	player->release();
	SAFE_DELETE(player);

	bullet->release();
	SAFE_DELETE(bullet);

	enemy->release();
	SAFE_DELETE(enemy);
}

//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
		if (INPUT->GetKeyDown(VK_TAB))
		{
			if (isShowRect)
			{
				isShowRect = false;
			}
			else
			{
				isShowRect = true;
			}
		}

		loopY -= 2;
		alpha -= 255 / 100;

		player->update();
		enemy->update();
		bullet->update();

		gaugeCount++;
		if (barY < player->getPlayerGauge() && gaugeCount % 3 == 0)
		{
			barY += 1;
		}
		else if (barY > player->getPlayerGauge() && gaugeCount % 3 == 0)
		{
			barY -= 5;
		}
		if (!isGameOver)
		{
			if (enemy->getBossHp() <= 0)
			{
				alpha = 255;
				isGameOver = true;
			}

		}
}

//=============================================================
//	## ���� ## render()
//=============================================================
void mainGame::render()
{ 
	//��� �� ��Ʈ�� (�̰��� ������ �׳� �α�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=============================================================
	//WM_PAINT���� �ߴ��� ó��
	
	//��׶��� ��������
	bgImg->loopRender(getMemDC(), &bgRect, bgImg->getX(), bgImg->getY() + loopY);
	bg_bar->render(getMemDC(), 19, 866 - barY * 4.72);
	bg_part->render(getMemDC(), 0, 0);

	enemy->render();
	player->render();
	bullet->render();

	if (loopY >= -200)
	{
		IMAGEMANAGER->findImage("GAMESTART")->alphaRender(getMemDC(), 0, 200, alpha);
	}

	if (isShowRect)
	{
		DrawEllipse(getMemDC(), player->getBarrierBody());
		DrawEllipse(getMemDC(), player->getPlayerBody());
	}

	if (isGameOver)
	{
		IMAGEMANAGER->findImage("STAGECLEAR")->alphaRender(getMemDC(), 0, 200, alpha);
	}

	//============================================================= 
	//������� ������ ȭ�� DC�� �׸���
	this->getBackBuffer()->render(getHDC());
}
