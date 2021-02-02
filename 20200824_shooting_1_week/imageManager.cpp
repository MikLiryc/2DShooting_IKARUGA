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
	//�߰����ַ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strkey);

	//�߰����ַ��� �̹����� �̹� �����Ѵٸ� -> ���� ������ �ʰ� �ش� �̹����� ���Ͻ�Ų��
	if (img) return img;

	//�ش� �̹����� ������ ���� ������ �ʱ�ȭ
	img = new image;
	if (FAILED(img->init(width, height)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}
	
	//���̹��� ����Ʈ�� �߰�
	//_mImageList.insert(std::pair<std::string, image*>(strkey, img));
	_mImageList.insert(make_pair(strkey, img));

	return img;
}

image * imageManager::addImage(std::string strkey, const char * _fileName, int width, int height, bool _isTrans, COLORREF _transColor)
{
	//�߰����ַ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strkey);

	//�߰����ַ��� �̹����� �̹� �����Ѵٸ� -> ���� ������ �ʰ� �ش� �̹����� ���Ͻ�Ų��
	if (img) return img;

	//�ش� �̹����� ������ ���� ������ �ʱ�ȭ
	img = new image;
	if (FAILED(img->init(_fileName, width, height, _isTrans, _transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	//���̹��� ����Ʈ�� �߰�
	//_mImageList.insert(std::pair<std::string, image*>(strkey, img));
	_mImageList.insert(make_pair(strkey, img));

	return img;
}

image * imageManager::addImage(std::string strkey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//�߰����ַ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strkey);

	//�߰����ַ��� �̹����� �̹� �����Ѵٸ� -> ���� ������ �ʰ� �ش� �̹����� ���Ͻ�Ų��
	if (img) return img;

	//�ش� �̹����� ������ ���� ������ �ʱ�ȭ
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	//���̹��� ����Ʈ�� �߰�
	//_mImageList.insert(std::pair<std::string, image*>(strkey, img));
	_mImageList.insert(make_pair(strkey, img));

	return img;
}

image * imageManager::addFrameImage(std::string strkey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF _transColor)
{
	//�߰����ַ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strkey);

	//�߰����ַ��� �̹����� �̹� �����Ѵٸ� -> ���� ������ �ʰ� �ش� �̹����� ���Ͻ�Ų��
	if (img) return img;

	//�ش� �̹����� ������ ���� ������ �ʱ�ȭ
	img = new image;
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, _transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	//���̹��� ����Ʈ�� �߰�
	//_mImageList.insert(std::pair<std::string, image*>(strkey, img));
	_mImageList.insert(make_pair(strkey, img));

	return img;
}

image * imageManager::addFrameImage(std::string strkey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF _transColor)
{
	//�߰����ַ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strkey);

	//�߰����ַ��� �̹����� �̹� �����Ѵٸ� -> ���� ������ �ʰ� �ش� �̹����� ���Ͻ�Ų��
	if (img) return img;

	//�ش� �̹����� ������ ���� ������ �ʱ�ȭ
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, _transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return nullptr;
	}

	//���̹��� ����Ʈ�� �߰�
	//_mImageList.insert(std::pair<std::string, image*>(strkey, img));
	_mImageList.insert(make_pair(strkey, img));

	return img;
}

image * imageManager::findImage(std::string strkey)
{
	mapImageIter key = _mImageList.find(strkey);

	//�˻��� Ű�� ã�Ҵٸ� �̹��� Ŭ���� ����
	if (key != _mImageList.end())
	{
		//key->first => Ű
		//key->second => �̹��� Ŭ����
		return key->second;	//Ű�� �ش��ϴ� �̹��� ��ȯ
	}
	return nullptr;
}

BOOL imageManager::deleteImage(std::string strkey)
{
	mapImageIter key = _mImageList.find(strkey);

	//�˻��� Ű�� ã�Ҵٸ� �̹��� ����
	if (key != _mImageList.end())
	{
		//�̹��� ����
		key->second->release();
		//�޸� ����
		SAFE_DELETE(key->second);
		//���� �ݺ��� ����
		_mImageList.erase(key);
		return true;
	}
	return false;
}

BOOL imageManager::deleteAll()
{
	//�� ��ü�� ���鼭 �ϳ��� ���� �����
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
	//�� ��ü�� ����
	_mImageList.clear();
	return true;
}

void imageManager::render(std::string strkey, HDC hdc, int destX, int destY)
{
	//�̹��� ã�Ƽ� �̹��� Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strkey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(std::string strkey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//�̹��� ã�Ƽ� �̹��� Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strkey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::alphaRender(std::string strkey, HDC hdc, BYTE alpha)
{
	//�̹��� ã�Ƽ� �̹��� Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strkey);
	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(std::string strkey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//�̹��� ã�Ƽ� �̹��� Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strkey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(std::string strkey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//�̹��� ã�Ƽ� �̹��� Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strkey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::frameRender(std::string strkey, HDC hdc, int destX, int destY)
{
	//�̹��� ã�Ƽ� �̹��� Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strkey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(std::string strkey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//�̹��� ã�Ƽ� �̹��� Ŭ������ �Լ��� �����Ѵ�
	image* img = findImage(strkey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}
