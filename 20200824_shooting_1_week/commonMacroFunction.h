#pragma once
//=============================================================
//	## commonMacroFunction ##
//=============================================================

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

//선 그리기
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//RECT 만들기
//RECT rc = { 128, 59, 228, 159 };
//RECT rc = RectMake(128, 59, 100, 100)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}
//RECT 중심좌표로 만들기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//Rectangle 함수 이용해서 사각형 그리기
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//Ellipse 함수 이용해서 타원 그리기
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}
//Ellipse 함수 이용해서 타원 중심좌표에 그리기
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

//편하쥬?
inline void Rectangle(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline void DrawEllipse(HDC hdc, RECT rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//네모 색칠하기
inline void FillRect(HDC hdc, int red, int green, int blue, RECT rc)
{
	HBRUSH newBrush;
	newBrush = CreateSolidBrush(RGB(red, green, blue));
	Rectangle(hdc, rc);
	FillRect(hdc, &rc, newBrush);
	DeleteObject(newBrush);
}

//주변 선까지 제거
inline void FillEllipse(HDC hdc, int red, int green, int blue, RECT rc)
{
	HPEN newPen, oldPen;
	HBRUSH newBrush, oldBrush;
	newPen = CreatePen(PS_SOLID, 1, RGB(red, green, blue));
	oldPen = (HPEN)SelectObject(hdc, newPen);
	newBrush = CreateSolidBrush(RGB(red, green, blue));
	oldBrush = (HBRUSH)SelectObject(hdc, newBrush);
	DrawEllipse(hdc, rc);
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
	DeleteObject(newPen);
	DeleteObject(newBrush);
}

inline void bitmapDisplay(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, 0, 0, bx, by, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}