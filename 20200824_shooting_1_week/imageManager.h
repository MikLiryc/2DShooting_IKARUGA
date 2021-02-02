#pragma once
#include "stdafx.h"
#include "singletonBase.h"
#include "image.h"
class imageManager : public singletonBase <imageManager>
{
private:
	typedef std::map<std::string, image*> mapImageList;				//������ ���� �̹��� ���
	typedef std::map<std::string, image*> ::iterator mapImageIter;	//�̹��� �� �ݺ���

	mapImageList _mImageList;				//���� �̹��� Ŭ������ ���� STL��


public:
	//�̹��� �Ŵ��� �ʱ�ȭ
	HRESULT init();
	//����
	void release();

	//�� ��Ʈ�� �ʱ�ȭ
	image* addImage(std::string strkey, int width, int height);
	//�̹��� ���Ϸ� �ʱ�ȭ
	image* addImage(std::string strkey, const char* _fileName, int width, int height, bool _isTrans = false, COLORREF _transColor = RGB(255, 0, 255));
	image* addImage(std::string strkey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	//������ �̹��� ���Ϸ� �ʱ�ȭ
	image* addFrameImage(std::string strkey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF _transColor = RGB(255, 0, 255));
	image* addFrameImage(std::string strkey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF _transColor = RGB(255, 0, 255));

	//�̹��� Ű������ ã��
	image* findImage(std::string strkey);
	//�̹��� Ű������ ����
	BOOL deleteImage(std::string strkey);
	//�̹��� ��ü ����
	BOOL deleteAll();

	//�Ϲ� ����
	void render(std::string strkey, HDC hdc, int destX = 0, int destY = 0);
	void render(std::string strkey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	//���ķ���
	void alphaRender(std::string strkey, HDC hdc, BYTE alpha);
	void alphaRender(std::string strkey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(std::string strkey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	//������ ����
	void frameRender(std::string strkey, HDC hdc, int destX, int destY);
	void frameRender(std::string strkey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);


	imageManager() {}
	~imageManager() {}
};

