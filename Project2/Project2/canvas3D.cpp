
#include "canvas3D.h"



canvas3D::canvas3D(int w, int h):canvas(w, h)
{
	_matModel = Matrix4<float>(1);
	 _matView = Matrix4<float>(1);
	_matProj = Matrix4<float>(1);
	_zBuffer = new float[_screenH*_screenW];
	//for(int i=0;i<_screenH*_screenW;i++)
	//{
	//	_zBuffer[i] = 0;
	//}
}


canvas3D::~canvas3D()
{
	delete[]_zBuffer;
}
void canvas3D::clear()
{
	memset(_zBuffer, 100, 4 * _screenW*_screenH);
	canvas::clear();
}
void * canvas3D::GetBuffer()
{
	return canvas::GetBuffer();
}
int canvas3D::addTexture(const char * url)
{
	return canvas::addTexture(url);
}

void canvas3D::drawTriangle(const point3 data[3], bool isFill, color col)
{
	if (isFill)
	{
		point3 min1 = data[0], min2 = data[1], min3 = data[2];
		if (min1.y>min2.y)
		{
			min1 = data[1];
			min2 = data[0];
		}
		if (min2.y>min3.y)
		{
			point3 temp = min2;
			min2 = min3;
			min3 = temp;
			if (min1.y>min2.y)
			{
				temp = min1;
				min1 = min2;
				min2 = temp;
			}
		}


		float e1 = (min2.x - min1.x) / float(min2.y - min1.y);//相对于Y的斜率
		float e2 = (min3.x - min1.x) / float(min3.y - min1.y);//相对于Y的斜率
		float k1 = min1.x;//增量，初始位置为min1；
		float k2 = min1.x;//增量，初始位置为min1；

		float k1z = min1.z;
		float k2z = min1.z;
		float e1z = (min2.z - min1.z) / float(min2.y - min1.y);//相对于Y的斜率
		float e2z = (min3.z - min1.z) / float(min3.y - min1.y);//相对于Y的斜率

		float x2 = min3.x - (min3.y - min2.y)*e2;
		if (min2.x < x2)
		{
			for (int i = min1.y; i < min3.y; i++)
			{

				if (i == min2.y)
				{
					e1 = (min3.x - min2.x) / float(min3.y - min2.y);
					e1z= (min3.z - min2.z) / float(min3.y - min2.y);
					k1 = min2.x;
					k1z = min2.z;
				}
				float z = k1z;
				float scale;
				for (int j = k1; j < k2; j++)
				{
					
					 if (_zBuffer[j + i * _screenH]<z)
					 {
						 _zBuffer[j + i * _screenH] = z;

						 drawPoint(j, i, col);
					 }
					 scale = (j - k1) / (float)(k2 - k1);
					 z = k1z * scale + k2z * (1 - scale);

				}
				k1 += e1;
				k2 += e2;
				k1z += e1z;
				k2z += e2z;
			}
		}
		else
		{
			for (int i = min1.y; i <min3.y; i++)
			{

				if (i == min2.y)
				{
					e1 = (min3.x - min2.x) / float(min3.y - min2.y);
					e1z = (min3.z - min2.z) / float(min3.y - min2.y);
					k1 = min2.x;
					k1z = min2.z;
				}
				float z = k1z;
				float scale;
				for (int j = k2; j < k1; j++)
				{


					if(_zBuffer[j+i* _screenH]<z)
					{
						_zBuffer[j + i * _screenH] = z;
						drawPoint(j, i, col);
					}
					scale = (j - k2) / (float)(k1 - k2);
					z = k1z * scale + k2z * (1 - scale);

				}
				k1 += e1;
				k2 += e2;
				k1z += e1z;
				k2z += e2z;
			}

		}


	}
	else
	{

		drawLine({ (short)data->x, (short)data->y },{ (short)(data+1)->x, (short)(data+1)->y}, col);
		drawLine({ (short)(data+1)->x, (short)(data+1)->y }, { (short)(data + 2)->x, (short)(data + 2)->y }, col);
		drawLine({ (short)(data + 2)->x, (short)(data + 2)->y  },{ (short)data->x, (short)data->y }, col);


	}

}

void canvas3D::drawTriangle(const coord3 data[3], int imgNum)
{

	if (_img[imgNum] == NULL)
		return;
	int imgW = _img[imgNum]->width();
	int imgH = _img[imgNum]->height();

	//排序，min1.y最小，min3.y最大
	coord3 min1 = data[0], min2 = data[1], min3 = data[2];
	if (min1.y>min2.y)
	{
		min1 = data[1];
		min2 = data[0];
	}
	if (min2.y>min3.y)
	{
		coord3 temp = min2;
		min2 = min3;
		min3 = temp;
		if (min1.y>min2.y)
		{
			temp = min1;
			min1 = min2;
			min2 = temp;
		}
	}
	/*************************重心坐标画纹理************************/
	/**************min1=A,min2=B，min3=C,当前正要画的点为P************/
	int SS = (min2.y - min3.y)*(min3.x - min1.x) - (min3.y - min1.y)*(min2.x - min3.x);//ABC的面积
	if (0 == SS)
		return;



	float k1z = min1.z;
	float k2z = min1.z;
	float e1z = (min2.z - min1.z) / float(min2.y - min1.y);//相对于Y的斜率
	float e2z = (min3.z - min1.z) / float(min3.y - min1.y);//相对于Y的斜率


	float e1 = (min2.x - min1.x) / float(min2.y - min1.y);//相对于Y的斜率
	float e2 = (min3.x - min1.x) / float(min3.y - min1.y);//相对于Y的斜率
	float x1 = min1.x;//x增量，初始位置为min1；
	float x2 = min1.x;//x增量，初始位置为min1；

	int S1y;////没有什么意义的定义
	int S2y;////只是为了一点运行效率
	int S3y;////相当于#define,在引用处替换就容易理解点

	float b1;//重心坐标 PBC/ABC  \             
	float b2;//重心坐标 PAC/ABC — --->b1+b2+b3==1;
	float b3;//重心坐标 PAB/ABC  /

	float u;//P点的u坐标
	float v;//P点的v坐标
	bool isLeft = min3.x - (min3.y - min2.y)*e2> min2.x ? true : false;//判断min2.x是否在对边线的左边
	if (isLeft)//ture 则从x1到x2遍历，false 则从x2到x1遍历
	{
		for (int i = min1.y; i < min3.y; i++)

		{
			x1 += e1;
			x2 += e2;
			k1z += e1z;
			k2z += e2z;
			if (i == (int)min2.y)
			{
				e1 = (min3.x - min2.x) / float(min3.y - min2.y);
				e1z = (min3.z - min2.z) / float(min3.y - min2.y);
				x1 = min2.x;
				k1z = min2.z;
			}

			if (i<0 || i>=_screenH)
				continue;

			 S1y = (i - min3.y)*(min2.x - min3.x);
			 S2y = (i - min1.y)*(min3.x - min1.x);
			 S3y = (i - min2.y)*(min1.x - min2.x);
			 float z = k1z;
			 float scale;
			for (int j = x1; j <x2; j++)
			{
				if (j < 0 || j >= _screenW)
					continue;
				scale = (j - x1) / (float)(x2 - x1);
				z = k1z * scale + k2z * (1 - scale);
				 b1 = (S1y + (min3.x - j)*(min2.y - min3.y)) / SS;////加权平均值，重心坐标；
				 b2 = (S2y + (min1.x - j)*(min3.y - min1.y)) / SS;////
				 b3 = (S3y + (min2.x - j)*(min1.y - min2.y)) / SS;////
				 u  = b1 * min1._u + b2 * min2._u + b3 * min3._u;
				 v  = b1 * min1._v + b2 * min2._v + b3 * min3._v;
				
				 
				if (_zBuffer[j + i * _screenH]>z)
				{
					_zBuffer[j + i * _screenH] = z;
					
					//_buffer[j + i * _screenH] = _img[imgNum]->getPixel((u*imgW), (v*imgH));
					drawPoint(j, i, _img[imgNum]->getPixel((u*imgW), (v*imgH)));
				}


			}

		}
	}
	else
	{
		for (int i = min1.y; i < min3.y; i++)
		{
			x1 += e1;
			x2 += e2;
			k1z += e1z;
			k2z += e2z;
			if (i == (int)min2.y)
			{
				e1 = (min3.x - min2.x) / float(min3.y - min2.y);
				e1z = (min3.z - min2.z) / float(min3.y - min2.y);
				x1 = min2.x;
				k1z = min2.z;
			}


			if (i<0 || i >= _screenH)
				continue;


			S1y = (i - min3.y)*(min2.x - min3.x);
			S2y = (i - min1.y)*(min3.x - min1.x);
			S3y = (i - min2.y)*(min1.x - min2.x);
			float z = k1z;
			float scale;
			for (int j = x2; j < x1; j++)
			{
				if (j < 0 || j >= _screenW)
					continue;
				b1 = (float)(S1y + (min3.x - j)*(min2.y - min3.y)) / SS;////加权平均值，重心坐标；
				b2 = (float)(S2y + (min1.x - j)*(min3.y - min1.y)) / SS;////
				b3 = (float)(S3y + (min2.x - j)*(min1.y - min2.y)) / SS;////
				u = b1 * min1._u + b2 * min2._u + b3 * min3._u;
				v = b1 * min1._v + b2 * min2._v + b3 * min3._v;
				
	
				if (_zBuffer[j + i * _screenH]>z)
				{
					_zBuffer[j + i * _screenH] = z;
					drawPoint(j, i, _img[imgNum]->getPixel((u*imgW), (v*imgH)));
					//_buffer[j + i * _screenH] = _img[imgNum]->getPixel((u*imgW), (v*imgH));
				}
				scale = (j - x2) / (float)(x1 - x2);
				z = k1z * scale + k2z * (1 - scale);

			}

		}
		}

	}



void canvas3D::colorPointer(int count, DataType type, int dataStride,  void * data)
{
	_colorData.count = count;
	_colorData.data = data;
	_colorData.dataStride = dataStride;
	_colorData.type = type;
}

void canvas3D::texturePointer(int count, DataType type, int dataStride,  void * data)
{
	_uvData.count = count;
	_uvData.data = data;
	_uvData.dataStride = dataStride;
	_uvData.type = type;
}

void canvas3D::vertexPointer(int count, DataType type, int dataStride,  void * data)
{

	_vertexData.count = count;
	_vertexData.data = data;
	_vertexData.dataStride = dataStride;
	_vertexData.type = type;
}


void canvas3D::drawArrays(DrawType type, int start, int size)
{

	if (_vertexData.data == 0)
		return;

	coord3 screenData[3];//三角形三个点的数据
	for(int i= start;i<start+size;i++)
	{
		float *p1 = (float*)_vertexData.data+i* _vertexData.dataStride*_vertexData.count;
		float *p2 = p1 + _vertexData.dataStride;
		float *p3 = p2+ _vertexData.dataStride;


		screenData[0] = {worldToScreen({*p1,*(p1 + 1),*(p1 + 2)}).x,
				         worldToScreen({*p1,*(p1 + 1),*(p1 + 2)}).y,
						 worldToScreen({*p1,*(p1 + 1),*(p1 + 2)}).z,
						 *(p1+3),*(p1+4)//u,v
						};
		screenData[1] = {worldToScreen({ *p2,*(p2 + 1),*(p2 + 2) }).x,
						 worldToScreen({ *p2,*(p2 + 1),*(p2 + 2) }).y,
						 worldToScreen({ *p2,*(p2 + 1),*(p2 + 2) }).z,
					 	 *(p2 + 3),*(p2 + 4)//u,v
						};
		screenData[2] = {worldToScreen({ *p3,*(p3 + 1),*(p3 + 2) }).x,
						 worldToScreen({ *p3,*(p3 + 1),*(p3 + 2) }).y,
						 worldToScreen({ *p3,*(p3 + 1),*(p3 + 2) }).z,
						 *(p3 + 3),*(p3 + 4)//u,v
						};

		drawTriangle(screenData, 0);
	}

	
}

void canvas3D::viewMatrix(float3   eye, float3  center, float3  up)
{
	float3 f = (center - eye).normalize();
	float3 u =up.normalize();
	float3 s = vectorX(f, u).normalize();
	u = vectorX(s, f).normalize();

	_matView = Matrix4<float>(1.0);
	_matView[0][0] = s.x;
	_matView[1][0] = s.y;
	_matView[2][0] = s.z;
	_matView[0][1] = u.x;
	_matView[1][1] = u.y;
	_matView[2][1] = u.z;
	_matView[0][2] = -f.x;
	_matView[1][2] = -f.y;
	_matView[2][2] = -f.z;
	_matView[3][0] = -((s * eye).x+ (s * eye).y+ (s * eye).z);
	_matView[3][1] = -((u * eye).x + (u * eye).y + (u * eye).z);
	_matView[3][2] = (f * eye).x + (f * eye).y + (f * eye).z;

}

void canvas3D::projMatrix(float fovy, float aspect, float zNear, float zFar)
{
	float range = tan(fovy *0.0087266462583) * zNear;//0.0087266462583=float(3.1415926/180.0*(0.5))
	float left = -range * aspect;
	float right = range * aspect;
	float bottom = -range;
	float top = range;
	_matProj = Matrix4<float>(0);
	_matProj[0][0] = (2.0 * zNear) / (right - left);
	_matProj[1][1] = (2.0 * zNear) / (top - bottom);
	_matProj[2][2] = -(zFar + zNear) / (zFar - zNear);
	_matProj[2][3] = -1.0;
	_matProj[3][2] = -(2.0 * zFar * zNear) / (zFar - zNear);
}

void canvas3D::projIdentity()
{
	_matProj = Matrix4<float>(1);
}

void canvas3D::viewIdentity()
{
	_matView = Matrix4<float>(1);
}

void canvas3D::setModelMatrix(Matrix4<float> &mat)
{
	_matModel = mat;
}

point3 canvas3D::worldToScreen(point3 world)
{

	float4 f = (_matProj*_matView*_matModel)*float4(world.x, world.y, world.z, 1.0);
	point3 screen;
	f.x = f.x / f.w*0.5+0.5;
	f.y = f.y / f.w*0.5 + 0.5;
	//f.z = f.z / f.w*0.5 + 0.5;
	screen.x = f.x*_screenW;
	screen.y = f.y*_screenH;
	screen.z = f.z;

	return screen;
}
