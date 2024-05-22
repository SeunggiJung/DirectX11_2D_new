#include "stdafx.h"
#include "Program.h"

#include "Systems/Window.h"

#include "Demos/00_RectDemo.h"
#include "Demos/01_CollisionDemo.h"
#include "Demos/02_TextureDemo.h"
#include "Demos/03_ShaderDemo.h"

void Program::Init()
{
	// Create VPBuffer
	{
		vpb = new VPBuffer();

		// View 행렬 설정
		{
			D3DXMatrixLookAtLH
			(
				&view,				// 카메라
				&Vector3(0, 0, 0),	// 카메라 위치
				&Vector3(0, 0, 1),	// 시야 방향
				&Vector3(0, 1, 0)	// 카메라 위 방향
			);

			vpb->SetView(view);
		}

		// projection 행렬 설정
		{
			D3DXMatrixOrthoOffCenterLH
			(
				&proj,
				0.0f,				// 왼쪽 끝	// x좌표 최소값
				(float)WinMaxWidth,	// 오른쪽 끝	// x좌표 최대값
				0.0f,				// 맨 아래	// y좌표 최소값
				(float)WinMaxHeight,// 맨 위		// y좌표 최대값
				0,					// 최소 깊이	// z좌표 최소값
				1					// 최대 깊이	// z좌표 최대값
			);

			vpb->SetProj(proj);
		}
	}

	// Push(new RectDemo);
	// Push(new CollisionDemo);
	// Push(new TextureDemo);
	Push(new ShaderDemo);
}

void Program::Destroy()
{
	SAFE_DELETE(vpb);

	for (IObject* obj : objs)
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
}

void Program::Update()
{
	for (IObject* obj : objs)
		obj->Update();
}

void Program::Render()
{
	vpb->SetVSBuffer(1);

	for (IObject* obj : objs)
		obj->Render();
}

void Program::PostRender()
{
	for (IObject* obj : objs)
		obj->PostRender();
}

void Program::GUI()
{
	for (IObject* obj : objs)
	{
		obj->GUI();
	}
}

void Program::Push(IObject* obj)
{
	objs.push_back(obj);
	obj->Init();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	srand((UINT)time(NULL));

	DXDesc desc;
	desc.AppName = L"D2DGame";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Program* program = new Program();
	Window* window = new Window(desc);
	WPARAM wParam = window->Run(program);

	SAFE_DELETE(window);
	SAFE_DELETE(program);

	return wParam;

}
