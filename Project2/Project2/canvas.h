#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>
#include"Image.h"



struct coord
{
	short int x, y;
	float _u, _v;
};
struct point
{
	short int x, y;
};
class canvas
{
public:
	canvas(int w,int h);
	virtual ~canvas();
	void clear();
	void * GetBuffer();

	void drawPoint(const point& a,  color col);
	inline void drawPoint(int x, int y, color col);
	void addColor(int x, int y, color col);
	void drawLine( point l1,  point l2, const color & col);
	void drawTriangle(const point t1[3],  bool isFill, color col);
	void drawTriangle(const coord _coord[3], int imgNum);//带纹理

	void drawImage(const char * url, int offsetX, int offsetY);
	void drawImage(const char * url, int offsetX, int offsetY, float scale);//简单粗暴的缩放
	int addTexture(const char * url);//添加纹理，最多有10张

protected:
	int _screenW, _screenH;

	Image *_img[8];
private:
	color *_buffer;

};

