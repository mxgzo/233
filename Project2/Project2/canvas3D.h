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
	void clear();//��д�ĺ���
	void * GetBuffer();//��д�ĺ���
	int addTexture(const char * url);//��д�ĺ���
	void drawTriangle(const point3 data[3], bool isFill, color col);//��д�ĺ���
	void drawTriangle(const coord3 data[3], int imgNum);//��д�ĺ���
	void colorPointer(int count, DataType type,int dataStride, void *data);
	void texturePointer(int count, DataType type, int dataStride,  void *data);
	void vertexPointer(int count, DataType type, int dataStride,  void *data);
	void drawArrays(DrawType type,int start,int size);
	//void drawPoint(point3 point, color col);
	//void drawLine(point3 l1, point3 l2, const color & col);

	void viewMatrix(float3   eye, float3   center, float3   up);//�൱��OpenGL��lookat();
	
	void projMatrix(float fovy, float aspect, float zNear, float zFar);//�൱��OpenGL������ͶӰ������Ǹ�����
	void projIdentity();
	void viewIdentity();
	void setModelMatrix(Matrix4<float> &mat);
	//void drawTriangle(const coord _coord[3], int imgNum);
protected:
	point3 worldToScreen(point3 world);
};

