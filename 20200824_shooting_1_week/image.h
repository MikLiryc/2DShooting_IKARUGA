#pragma once
//=============================================================
//	## image ## 앞으로 계속 업데이트됨
//=============================================================
class image
{
public:
	enum IMAGE
	{
		LOAD_EMPTY,		//빈 비트맵 로딩
		LOAD_FILE		//비트맵 파일 로딩
	};

	typedef struct tagImage
	{
		HDC hMemDC;			//메모리 DC
		HBITMAP hBit;		//비트맵
		HBITMAP hOBit;		//올드 비트맵
		float x;			//이미지 x 좌표
		float y;			//이미지 y 좌표
		int width;			//이미지 가로길이
		int height;			//이미지 세로길이
		int currentFrameX;	//현재 프레임 X
		int currentFrameY;	//현재 프레임 Y
		int maxFrameX;		//최대 프레임 X 개수
		int maxFrameY;		//최대 프레임 Y 개수
		int frameWidth;		//1 프레임 가로길이
		int frameHeight;	//1 프레임 세로길이
		BYTE loadType;		//이미지 로드 타입
		tagImage()			//구조체 생성자
		{
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_EMPTY;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	char*			_fileName;		//이미지 파일이름
	bool			_isTrans;		//배경색 없앨거냐?
	COLORREF		_transColor;	//배경색 없앨 RGB(마젠타 = RGB(255, 0, 255))

	LPIMAGE_INFO	_blendImage;	//알파블렌드 이미지
	BLENDFUNCTION	_blendFunc;		//알파블렌드

public:
	image();
	~image();

	//빈 비트맵 초기화
	HRESULT init(int width, int height);

	//이미지 파일로 초기화
	HRESULT init(const char* _fileName, int width, int height, bool _isTrans = false, COLORREF _transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	//프레임 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF _transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF _transColor = RGB(255, 0, 255));


	//알파블렌드 초기화
	HRESULT initForAlphaBlend();

	//해제
	void release();

	//렌더(내가 원하는 좌표에 출력시키기. 일반적으로 우리는 RECT의 LT좌표를 작성)
	void render(HDC hdc, int destX = 0, int destY = 0);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//알파렌더 (이미지를 알파값만큼 투명화시켜준다)
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	//여러 오브젝트의 프레임이 다르게 돌게 할 때 사용

	//루프렌더
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//DC 얻기
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//이미지 x, y 좌표 get, set
	inline float getX() { return _imageInfo->x; }
	inline float getY() { return _imageInfo->y; }
	inline void setX(float x) { _imageInfo->x = x; }
	inline void setY(float y) { _imageInfo->y = y; }

	//이미지 센터좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x + (_imageInfo->width / 2);
		_imageInfo->y = y + (_imageInfo->height / 2);
	}

	//이미지 가로, 세로 길이 가져오기
	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	//바운딩 박스 (충돌용 렉트)
	inline RECT boundingBox()
	{
		RECT rc = { (int)_imageInfo->x,
					(int)_imageInfo->y,
					(int)_imageInfo->x + _imageInfo->width,
					(int)_imageInfo->x + _imageInfo->height };
		return rc;
	}
	inline RECT boundingBoxWithFrame()
	{
		RECT rc = { (int)_imageInfo->x,
					(int)_imageInfo->y,
					(int)_imageInfo->x + _imageInfo->frameWidth,
					(int)_imageInfo->x + _imageInfo->frameHeight };
		return rc;
	}

	//프레임 x, y
	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//1프레임 가로, 세로 길이 가져오기
	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }
	//맥스 프레임 가져오기

	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }





};

