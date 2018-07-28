#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"canvas.h"
#include"canvas3D.h"
int Height = 800;
int Width = 800;

point _rButton;
bool _rButtonFlag = false;
point _lButton;
bool _lButtonFlag = false;
float _scaleScreen=10.0;
Matrix4<float> _modelMat(1.0);
LRESULT CALLBACK RenderWindowproc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParm)
{
	switch (msg)
	{
	case WM_SIZE:
		break;
	case WM_LBUTTONDOWN:
	{
		_lButton.x = LOWORD(lParm);
		_lButton.y = HIWORD(lParm);
		_lButtonFlag = true;
	}
		break;

	case  WM_LBUTTONUP:
	{
		_lButtonFlag = false;
	}
	break;
	case WM_RBUTTONDOWN:
	{
		_rButton.x = LOWORD(lParm);
		_rButton.y = HIWORD(lParm);
		_rButtonFlag = true;
	}
	break;
	case WM_RBUTTONUP:
	{

		_rButtonFlag = false;
	}
	break;
	case WM_MOUSEMOVE:
	{
		int x = LOWORD(lParm);
		int y = HIWORD(lParm); 
		if(_rButtonFlag)
		{
			int offsetX = x - _rButton.x;
			int offsetY = y - _rButton.y;
			_modelMat.rotateY(offsetX);
			_modelMat.rotateX(offsetY);
			_rButton.x = x;
			_rButton.y = y;
		}


		if (_lButtonFlag)
		{
			int offsetX = x - _lButton.x;
			int offsetY = y - _lButton.y;
			//_viewMat.rotateY(offsetX);
			//_viewMat.rotateX(offsetY);
			_modelMat.translate(offsetX*0.01, -offsetY*0.01,0.0);

			_lButton.x = x;
			_lButton.y = y;
		}
	}
	break;

	case WM_MOUSEWHEEL:
	{
		short delta = GET_WHEEL_DELTA_WPARAM(wParam);
		if (delta > 0)
			_scaleScreen++;
		else
		{
			_scaleScreen--;

		}
		
	}
	break;




	case WM_CLOSE:						// 关闭窗口

		PostQuitMessage(0);
		return 0;		break;

	case WM_DESTROY:					// 退出消息
		PostQuitMessage(0);
		return 0;		break;
	case WM_KEYUP:						// 按ESC退出，全屏模式必需要加入的退出方式。
		switch (wParam)
		{
		case VK_ESCAPE:

			PostQuitMessage(0);
			return 0; break;
		}
	default:			break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParm);
}

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = NULL;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = NULL;
	wndClass.hIconSm = NULL;
	wndClass.hInstance = NULL;
	wndClass.lpfnWndProc = RenderWindowproc;
	wndClass.lpszClassName = "OpenglWindow";
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// 使窗口具有3D外观
	ATOM atom = RegisterClassEx(&wndClass);



	HWND hwnd = CreateWindowEx(NULL, "OpenglWindow", "Render Window", WS_OVERLAPPEDWINDOW, 100, 100, Width, Height, NULL, NULL, hInstance, NULL);

	if (!hwnd)
	{
		return 0;
	}
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	void *buffer = 0;
	HDC hDC = GetDC(hwnd);
	HDC hMem = ::CreateCompatibleDC(hDC);

	BITMAPINFO bmpInfor;
	bmpInfor.bmiHeader.biBitCount = 32;
	bmpInfor.bmiHeader.biClrImportant = 0;
	bmpInfor.bmiHeader.biClrUsed = 0;
	bmpInfor.bmiHeader.biCompression = BI_RGB;
	bmpInfor.bmiHeader.biHeight = Height;
	bmpInfor.bmiHeader.biPlanes = 1;
	bmpInfor.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfor.bmiHeader.biSizeImage = 0;
	bmpInfor.bmiHeader.biWidth = Width;
	bmpInfor.bmiHeader.biXPelsPerMeter = 0;
	bmpInfor.bmiHeader.biYPelsPerMeter = 0;
	
	HBITMAP hBmp = CreateDIBSection(hDC, &bmpInfor, DIB_RGB_COLORS, (void**)&buffer, 0, 0);//创建一张位图，返回输出buffer

	SelectObject(hMem, hBmp);
	int a = sizeof(buffer);
	canvas* _canvas = new canvas(Width, Height);
	canvas3D*_canvas3D = new canvas3D(Width, Height);
	//memset(buffer, 0, Width*Height * 4);
	
	//消息循环
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))

		{
			if (msg.message == WM_QUIT)
			{

				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
		
			static	int num = _canvas3D->addTexture("aa.bmp");



			//static int i = 0; i++;
			//_viewMat.rotateX(i);

			_canvas3D->viewMatrix({5.0f, 0.0f, _scaleScreen }, { 0.0f, 0.0f,1.0f }, { 0.0f, 1.0f, 0.0f });
			_canvas3D->setModelMatrix(_modelMat);
			_canvas3D->projMatrix(30, (float)(Width) / (float)(Height), 0.1, 1000);
			coord3 b2[] = {  1.0f, 1.0f, -1.0f,  1.0f, 1.0f,
							 1.0f,-1.0f, -1.0f,  1.0f, 0.0f, 
						    -1.0f, 1.0f, -1.0f,  0.0f, 1.0f,
							-1.0f,-1.0f, -1.0f,  0.0f, 0.0f,

							 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
							 1.0f,-1.0f, 1.0f,  1.0f, 0.0f,
							-1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
							-1.0f,-1.0f, 1.0f,  0.0f, 0.0f,

							 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
							 1.0f, 1.0f,-1.0f,  1.0f, 0.0f,
							 1.0f,-1.0f, 1.0f,  0.0f, 1.0f,
							 1.0f,-1.0f,-1.0f,  0.0f, 0.0f,


							-1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
							-1.0f, 1.0f,-1.0f, 1.0f, 0.0f,
							-1.0f,-1.0f, 1.0f, 0.0f, 1.0f,
							-1.0f,-1.0f,-1.0f, 0.0f, 0.0f,
			};

			_canvas3D->clear();

			_canvas3D->vertexPointer(4,DataType_FLOAT,sizeof(coord3)/4,&b2[0].x);
			_canvas3D->texturePointer(2, DataType_FLOAT, sizeof(coord3)/4, &b2[0]._u);
			_canvas3D->drawArrays(DrawType_TRIANGLE,0,4);

			_canvas3D->vertexPointer(4, DataType_FLOAT, sizeof(coord3) / 4, &b2[1].x);
			_canvas3D->texturePointer(2, DataType_FLOAT, sizeof(coord3) / 4, &b2[1]._u);
			_canvas3D->drawArrays(DrawType_TRIANGLE, 0, 4);
			void  * rgb = (float*)_canvas3D->GetBuffer();


			memcpy( buffer, rgb, 4*Width*Height);
			BitBlt(hDC, 0, 0, Width, Height, hMem, 0, 0, SRCCOPY);
		}

	}

}