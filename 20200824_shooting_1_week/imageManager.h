#pragma once
#include "stdafx.h"
#include "singletonBase.h"
#include "image.h"
class imageManager : public singletonBase <imageManager>
{
private:
	typedef std::map<std::string, image*> mapImageList;				//맵으로 만든 이미지 목록
	typedef std::map<std::string, image*> ::iterator mapImageIter;	//이미지 맵 반복자

	mapImageList _mImageList;				//실제 이미지 클래스를 담을 STL맵


public:
	//이미지 매니저 초기화
	HRESULT init();
	//해제
	void release();

	//빈 비트맵 초기화
	image* addImage(std::string strkey, int width, int height);
	//이미지 파일로 초기화
	image* addImage(std::string strkey, const char* _fileName, int width, int height, bool _isTrans = false, COLORREF _transColor = RGB(255, 0, 255));
	image* addImage(std::string strkey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	//프레임 이미지 파일로 초기화
	image* addFrameImage(std::string strkey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF _transColor = RGB(255, 0, 255));
	image* addFrameImage(std::string strkey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF _transColor = RGB(255, 0, 255));

	//이미지 키값으로 찾기
	image* findImage(std::string strkey);
	//이미지 키값으로 삭제
	BOOL deleteImage(std::string strkey);
	//이미지 전체 삭제
	BOOL deleteAll();

	//일반 렌더
	void render(std::string strkey, HDC hdc, int destX = 0, int destY = 0);
	void render(std::string strkey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	//알파렌더
	void alphaRender(std::string strkey, HDC hdc, BYTE alpha);
	void alphaRender(std::string strkey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(std::string strkey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	//프레임 렌더
	void frameRender(std::string strkey, HDC hdc, int destX, int destY);
	void frameRender(std::string strkey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);


	imageManager() {}
	~imageManager() {}
};

