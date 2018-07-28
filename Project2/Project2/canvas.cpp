#include "canvas.h"
#include"Image.h"
#define Min(x,y) (x)>(y)?(y):(x)

canvas::canvas(int w,int h): _screenW(w), _screenH(h)
{
	for (int i = 0; i < 10; i++)
		_img[i] = NULL;
	_buffer = new color[w*h];
	clear();
}



canvas::~canvas()
{
	for (int i = 0; i < 10; i++)
	{
	delete _img[i];
	}

	delete _buffer;
	_buffer = NULL;
}

void canvas::clear()
{
	memset(_buffer, 0, 4 * _screenW*_screenH);
}

void * canvas::GetBuffer()
{
	return _buffer;
}


//画点
void canvas::drawPoint(const point& a,  color col)
{
	_buffer[a.y*_screenW + a.x] = col;
}

void canvas::drawPoint(int x,int y, color col)
{
	_buffer[y*_screenW + x] = col;
}
void canvas::addColor(int x, int y, color col)
{
	_buffer[y*_screenW + x] = _buffer[y*_screenW + x]+col;
}
void canvas::drawLine(point l1, point l2, const color & col)
{
	if (l2.x == l1.x)
	{
		int t = l1.y > l2.y ? -1 : 1;
		int i = l1.y;
		while (i != l2.y)
		{
			_buffer[l1.x + i * _screenW] = col;
			i += t;
		}

	}
	else
	{
		float k = (l2.y - l1.y) / (float)(l2.x - l1.x);
			if (k >= 0&&k<=1)
			{
				int t = l1.x > l2.x ? -1 : 1;
				int i = l1.x, j = l1.y;

				int e = l1.x - l2.x;
				int add1 = t * 2 * (l2.y - l1.y);
				int add2 = t * 2 * (l2.x - l1.x);

				while (i != l2.x)
				{

					_buffer[i + j * _screenW] = col;
					e += add1;
					i += t;
					if (e >= 0)
					{
						j += t; e -= add2;
					}

				}


			}
			else if(k>=-1&&k<0)
			{
				int t = l1.x > l2.x ? -1 : 1;
				int i = l1.x, j = l1.y;

				int e = l1.x - l2.x;
				int add1 = -t * 2 * (l2.y - l1.y);
				int add2 = t * 2 * (l2.x - l1.x);

				while (i != l2.x)
				{

					_buffer[i + j * _screenW] = col;
					e += add1;
					i += t;
					if (e >= 0)
					{
						j += -t; e -= add2;
					}

				}
			}
			else if (k >1)
			{
				int t = l1.y > l2.y ? -1 : 1;
				int i = l1.y, j = l1.x;

				int e = l1.y - l2.y;
				int add1 = t * 2 * (l2.x - l1.x);
				int add2 = t * 2 * (l2.y - l1.y);

				while (i != l2.y)
				{

					_buffer[j + i * _screenW] = col;
					e += add1;
					i += t;
					if (e >= 0)
					{
						j += t; e -= add2;
					}

				}


			}
			else
			{
				int t = l1.y > l2.y ? -1 : 1;
				int i = l1.y, j = l1.x;

				int e = l1.y - l2.y;
				int add1 = -t * 2 * (l2.x - l1.x);
				int add2 = t * 2 * (l2.y - l1.y);

				while (i != l2.y)
				{

					_buffer[j + i * _screenW] = col;
					e += add1;
					i += t;
					if (e >= 0)
					{
						j += -t; e -= add2;
					}

				}
			}
		

	}
}

void canvas::drawTriangle(const point t1[3],bool isFill ,color col)//顶点地址，顶点个数，是否填充模式，颜色
{ 


	if (isFill)
	{
		point min1 = t1[0], min2 = t1[1], min3 = t1[2];
		if (min1.y>min2.y)
		{
			min1 = t1[1];
			min2 = t1[0];
		}
		if (min2.y>min3.y)
		{
			point temp = min2;
			min2 = min3;
			min3 = temp;
			if (min1.y>min2.y)
			{
				temp = min1;
				min1 = min2;
				min2 = temp;
			}
		}




#if 0
		if (min2.y / (float)min2.x >= min3.y / (float)min3.x)
		{
			float e1 = (min2.x - min1.x) / float(min2.y - min1.y);
			float e2 = (min3.x - min1.x) / float(min3.y - min1.y);
			float k1 = 0;
			float k2 = 0;
			for (int i = min1.y; i < min2.y; i++)
			{

				k1 += e1;
				k2 += e2;

				for (int j = min1.x + k1 - 0.5; j <= min1.x + k2; j++)
					buffer[j + i * w] = col;
			}
			e1 = (min3.x - min2.x) / float(min3.y - min2.y);
			k1 = 0;

			for (int i = min2.y; i <= min3.y; i++)
			{

				k1 += e1;


				k2 += e2;
				for (int j = min2.x + k1 - 0.5; j <= min1.x + k2; j++)
					buffer[j + i * w] = col;
			}
		}
		else
		{
			float e1 = (min2.x - min1.x) / float(min2.y - min1.y);
			float e2 = (min3.x - min1.x) / float(min3.y - min1.y);
			float k1 = 0;
			float k2 = 0;
			for (int i = min1.y; i < min2.y; i++)
			{

				k1 += e1;


				k2 += e2;

				for (int j = min1.x + k2 - 0.5; j <= min1.x + k1; j++)
					buffer[j + i * w] = col;
			}
			e1 = (min3.x - min2.x) / float(min3.y - min2.y);
			k1 = 0;

			for (int i = min2.y; i <= min3.y; i++)
			{

				k1 += e1;


				k2 += e2;
				for (int j = min1.x + k2 - 0.5; j <= min2.x + k1; j++)
					buffer[j + i * w] = col;
			}
		}
#else



			float e1 = (min2.x - min1.x) / float(min2.y - min1.y);//相对于Y的斜率
			float e2 = (min3.x - min1.x) / float(min3.y - min1.y);//相对于Y的斜率
			float k1 = min1.x;//增量，初始位置为min1；
			float k2 = min1.x;//增量，初始位置为min1；
			float x2 = min3.x - (min3.y - min2.y)*e2;
			if (min2.x < x2)
			{
				for (int i = min1.y; i < min3.y; i++)
				{

					if (i == min2.y)
					{
						e1 = (min3.x - min2.x) / float(min3.y - min2.y);
						k1 = min2.x;
					}

					for (int j = k1; j < k2; j++)
					{
						_buffer[j + i * _screenW] = col;
					}
					k1 += e1;
					k2 += e2;
				}
			}
			else
			{
					for (int i = min1.y; i <min3.y; i++)
					{

						if (i == min2.y)
						{
							e1 = (min3.x - min2.x) / float(min3.y - min2.y);
							k1 = min2.x;
						}

						for (int j = k2; j < k1; j++)
						{
							_buffer[j + i * _screenW] = col;
						}
						k1 += e1;
						k2 += e2;
					}

					k1 += e1;
					k2 += e2;
			}


					
			

		
#endif // 0

	}
	else 
	{

			drawLine(*(t1), *(t1+ 1), col);
			drawLine(*(t1 + 1), *(t1 +2), col);
			drawLine(*(t1 +2), *(t1), col);


	}

}
void canvas::drawTriangle(const coord _coord[3],int imgNum)
{
	if (_img[imgNum] == NULL)
		return;
	int imgW =_img[imgNum]->width();
	int imgH = _img[imgNum]->height();

	//排序，min1.y最小，min3.y最大
	coord min1=_coord[0], min2=_coord[1], min3= _coord[2];
	if(min1.y>min2.y)
	{
		min1 = _coord[1];
		min2 = _coord[0];
	}
	if(min2.y>min3.y)
	{
		coord temp = min2;
		min2 = min3;
		min3 = temp;
		if(min1.y>min2.y)
		{
			temp = min1;
			min1 = min2;
			min2 = temp;
		}
	}
/*************************重心坐标画纹理***************/

	int SS = (min2.y - min3.y)*(min3.x - min1.x) - (min3.y - min1.y)*(min2.x - min3.x);//三角形面积
	if (0 == SS)
		return;

	float e1 = (min2.x - min1.x) / float(min2.y - min1.y);//相对于Y的斜率
	float e2 = (min3.x - min1.x) / float(min3.y - min1.y);//相对于Y的斜率
	float x1 = min1.x;//x增量，初始位置为min1；
	float x2 = min1.x;//x增量，初始位置为min1；

	bool isLeft = min3.x - (min3.y - min2.y)*e2> min2.x?true:false;//判断min2.x是否在对边线的左边
	if (isLeft)//目的只是在遍历x坐标的时候是++，还是--
	{
		for (int i = min1.y; i < min3.y; i++)
		{

			if (i == min2.y)
			{
				e1 = (min3.x - min2.x) / float(min3.y - min2.y);
				x1 = min2.x;
			}

			int S1y = (i - min3.y)*(min2.x - min3.x);
			int S2y = (i - min1.y)*(min3.x - min1.x);
			int S3y = (i - min2.y)*(min1.x - min2.x);

			for (int j = x1; j < x2; j++)
			{
				int S1 = S1y + (min3.x - j)*(min2.y - min3.y);//小三角形面积
				int S2 = S2y + (min1.x - j)*(min3.y - min1.y);//
				int S3 = S3y + (min2.x - j)*(min1.y - min2.y);//
				float b1 = (float)S1 / SS;//加权平均值，重心坐标；
				float b2 = (float)S2 / SS;//
				float b3 = (float)S3 / SS;//
				float u = b1 * min1._u + b2 * min2._u + b3 * min3._u;
				float v= b1 * min1._v + b2 * min2._v + b3 * min3._v;

				_buffer[j + i * _screenW] = _img[imgNum]->getPixel((u*imgW), (v*imgH));
			}
			x1 += e1;
			x2 += e2;
		}
	}
	else
	{

		for (int i = min1.y; i < min3.y; i++)
		{

			if (i == min2.y)
			{
				e1 = (min3.x - min2.x) / float(min3.y - min2.y);
				x1 = min2.x;
			}

			int S1y = (i - min3.y)*(min2.x - min3.x);
			int S2y = (i - min1.y)*(min3.x - min1.x);
			int S3y = (i - min2.y)*(min1.x - min2.x);

			for (int j = x2; j < x1; j++)
			{
				int S1 = S1y + (min3.x - j)*(min2.y - min3.y);//小三角形面积
				int S2 = S2y + (min1.x - j)*(min3.y - min1.y);//
				int S3 = S3y + (min2.x - j)*(min1.y - min2.y);//
				float b1 = (float)S1 / SS;//加权平均值，重心坐标；
				float b2 = (float)S2 / SS;//
				float b3 = (float)S3 / SS;//
				float u = b1 * min1._u + b2 * min2._u + b3 * min3._u;
				float v = b1 * min1._v + b2 * min2._v + b3 * min3._v;

				_buffer[j + i * _screenW] = _img[imgNum]->getPixel(u*_img[imgNum]->width(), v*_img[imgNum]->height());
			}
			x1 += e1;
			x2 += e2;
		}
	}

}

void canvas::drawImage(const char  * url, int offsetX, int offsetY)
{
	 static Image *img=Image::loadTeture(url);
	for (short int j = 0; j < img->width(); j++)
		for (short int i = 0; i < img->height(); i++)

			this->drawPoint(offsetX+j, offsetY+i, img->getPixel(j,i));
	//delete img;
}
void canvas::drawImage(const char  * url, int offsetX, int offsetY,float scale)
{
	static Image *img = Image::loadTeture(url);
	for (short int j = 0; j <img->width(); j++)
		for (short int i = 0; i < img->height(); i++)
		{
		
			if ((offsetX + j * scale) >= _screenW || (offsetY + i * scale) >= _screenH)break;
				this->drawPoint(offsetX + j * scale,offsetY + i * scale, img->getPixel( j,i ));
		}

			
	//delete img;
}
int  canvas::addTexture(const char * url)
{
	for (int i = 0; i < 8; i++)
	{
		if (_img[i] == NULL)
		{
			_img[i]= Image::loadTeture(url);
			return  i;
		}
	}
	return -1;
}
