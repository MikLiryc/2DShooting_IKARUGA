#include "stdafx.h"
#include "imageManager.h"

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
	this->deleteAll();
}

image * imageManager::addImage(std::string strkey, int width, int height)
{
	//추가해주려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strkey);

	//추가해주려는 이미지가 이미 존재한다면 -> 새로 만들지 않고 해당 이미지만 리턴시킨다
	if (img) return img;

	//해당 이미지가 없으면 새로 생성후 초기화
	img = new image;
	if (FAILED(img->init(width, height)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}
	
	//맵이미지 리스트에 추가
	//_mImageList.insert(std::pair<std::string, image*>(strkey, img));
	_mImageList.insert(make_pair(strkey, img));

	return img;
}

image * imageManager::addImage(std::string strkey, const char * _fileName, int width, int height, bool _isTrans, COLORREF _transColor)
{
	//추가해주려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strkey);

	//추가해주려는 이미지가 이미 존재한다면 -> 새로 만들지 않고 해당 이미지만 리턴시킨다
	if (img) return img;

	//해당 이미지가 없으면 새로 생성후 초기화
	img = new image;
	if (FAILED(img->init(_fileName, width, height, _isTrans, _transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	//맵이미지 리스트에 추가
	//_mImageList.insert(std::pair<std::string, image*>(strkey, img));
	_mImageList.insert(make_pair(strkey, img));

	return img;
}

image * imageManager::addImage(std::string strkey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//추가해주려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strkey);

	//추가해주려는 이미지가 이미 존재한다면 -> 새로 만들지 않고 해당 이미지만 리턴시킨다
	if (img) return img;

	//해당 이미지가 없으면 새로 생성후 초기화
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	//맵이미지 리스트에 추가
	//_mImageList.insert(std::pair<std::string, image*>(strkey, img));
	_mImageList.insert(make_pair(strkey, img));

	return img;
}

image * imageManager::addFrameImage(std::string strkey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF _transColor)
{
	//추가해주려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strkey);

	//추가해주려는 이미지가 이미 존재한다면 -> 새로 만들지 않고 해당 이미지만 리턴시킨다
	if (img) return img;

	//해당 이미지가 없으면 새로 생성후 초기화
	img = new image;
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, _transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	//맵이미지 리스트에 추가
	//_mImageList.insert(std::pair<std::string, image*>(strkey, img));
	_mImageList.insert(make_pair(strkey, img));

	return img;
}

image * imageManager::addFrameImage(std::string strkey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF _transColor)
{
	//추가해주려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strkey);

	//추가해주려는 이미지가 이미 존재한다면 -> 새로 만들지 않고 해당 이미지만 리턴시킨다
	if (img) return img;

	//해당 이미지가 없으면 새로 생성후 초기화
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, _transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	//맵이미지 리스트에 추가
	//_mImageList.insert(std::pair<std::string, image*>(strkey, img));
	_mImageList.insert(make_pair(strkey, img));

	return img;
}

image * imageManager::findImage(std::string strkey)
{
	mapImageIter key = _mImageList.find(strkey);

	//검색한 키를 찾았다면 이미지 클래스 리턴
	if (key != _mImageList.end())
	{
		//key->first => 키
		//key->second => 이미지 클래스
		return key->second;	//키에 해당하는 이미지 반환
	}
	return nullptr;
}

BOOL imageManager::deleteImage(std::string strkey)
{
	mapImageIter key = _mImageList.find(strkey);

	//검색한 키를 찾았다면 이미지 삭제
	if (key != _mImageList.end())
	{
		//이미지 해제
		key->second->release();
		//메모리 해제
		SAFE_DELETE(key->second);
		//맵의 반복자 해제
		_mImageList.erase(key);
		return true;
	}
	return false;
}

BOOL imageManager::deleteAll()
{
	//맵 전체를 돌면서 하나씩 전부 지운다
	mapImageIter iter = _mImageList.begin();
	for (iter; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	//맵 전체를 삭제
	_mImageList.clear();
	return true;
}

void imageManager::render(std::string strkey, HDC hdc, int destX, int destY)
{
	//이미지 찾아서 이미지 클래스의 함수를 실행한다
	image* img = findImage(strkey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(std::string strkey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//이미지 찾아서 이미지 클래스의 함수를 실행한다
	image* img = findImage(strkey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::alphaRender(std::string strkey, HDC hdc, BYTE alpha)
{
	//이미지 찾아서 이미지 클래스의 함수를 실행한다
	image* img = findImage(strkey);
	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(std::string strkey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//이미지 찾아서 이미지 클래스의 함수를 실행한다
	image* img = findImage(strkey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(std::string strkey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//이미지 찾아서 이미지 클래스의 함수를 실행한다
	image* img = findImage(strkey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::frameRender(std::string strkey, HDC hdc, int destX, int destY)
{
	//이미지 찾아서 이미지 클래스의 함수를 실행한다
	image* img = findImage(strkey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(std::string strkey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//이미지 찾아서 이미지 클래스의 함수를 실행한다
	image* img = findImage(strkey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}
