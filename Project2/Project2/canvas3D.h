#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"myMath.h"
#include"canvas.h"
using namespace myMath;
struct point3
{
	float x, y, z;
};

struct coord3
{
	float x, y,z;
	float _u, _v;

};

enum DrawType
{
	DrawType_POINT,
	DrawType_LINE,
	DrawType_TRIANGLE
};
enum DataType
{
	DataType_DOUBLE = 8,
	DataType_FLOAT = 4,
	DataType_INT = 4,
	DataType_BYTE = 1
};
struct DATA
{
	int count;
	DataType type;
	int dataStride;
	 void *data;
};
class canvas3D:protected canvas
{
private:
	//Matrix4<float> _matProj;
	Matrix4<float> _matModel;
	Matrix4<float> _matView;
	Matrix4<float> _matProj;
	float *_zBuffer;
	DATA _colorData;
	DATA _uvData;
	DATA  _vertexData;
public:
	canvas3D(int w, int h);
	~canvas3D();
	void clear();//重写的函数
	void * GetBuffer();//重写的函数
	int addTexture(const char * url);//重写的函数
	void drawTriangle(const point3 data[3], bool isFill, color col);//重写的函数
	void drawTriangle(const coord3 data[3], int imgNum);//重写的函数
	void colorPointer(int count, DataType type,int dataStride, void *data);
	void texturePointer(int count, DataType type, int dataStride,  void *data);
	void vertexPointer(int count, DataType type, int dataStride,  void *data);
	void drawArrays(DrawType type,int start,int size);
	//void drawPoint(point3 point, color col);
	//void drawLine(point3 l1, point3 l2, const color & col);

	void viewMatrix(float3   eye, float3   center, float3   up);//相当于OpenGL的lookat();
	
	void projMatrix(float fovy, float aspect, float zNear, float zFar);//相当于OpenGL的设置投影矩阵的那个函数
	void projIdentity();
	void viewIdentity();
	void setModelMatrix(Matrix4<float> &mat);
	//void drawTriangle(const coord _coord[3], int imgNum);
protected:
	point3 worldToScreen(point3 world);
};

