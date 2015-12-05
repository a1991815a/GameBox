#include <windows.h>
#include "Application.h"
#include "DXUtils.h"
#include "GTerrian.h"
#include "GCameraFP.h"
#include "GListenerKeyboard.h"
#include "GEventDispatcher.h"
#include <iostream>
#include "D3DXInputEngine.h"
#include "GListenerMouse.h"
using namespace std;

GTerrian* ter;
GCameraFP* fp = nullptr;

int main(){
	Application app("��Ϸ����", 0, 0, 800, 600);
	return app.run();
};

void WinUpdate();

bool WinCreate(HWND hwnd){
	dxInit(hwnd);
	dxSetRenderState(D3DRS_LIGHTING, FALSE);
	dxSetFillMode(D3DFILL_WIREFRAME);
	ter = new GTerrian();
	ter->init(120, 120, 20, 20, 10);
	fp = new GCameraFP();
	fp->setView(
		0, 10, -10, 
		0, 10, 0,
		0, 1, 0);

	_dxInputEngine->Init(hwnd);
	GListenerKeyboard* listener = new GListenerKeyboard();
	listener->setName("aa");
	listener->OnKeyDown = [](GEvent* e) {
		switch (e->getParam())
		{
		case DIK_UP:
			fp->MoveZ(1);
			break;
		case DIK_DOWN:
			fp->MoveZ(-1);
			break;
		case DIK_LEFT:
			fp->MoveX(-1);
			break;
		case DIK_RIGHT:
			fp->MoveX(1);
			break;
		case DIK_E:
			fp->RotateY(0.03);
			break;
		case DIK_Q:
			fp->RotateY(-0.03);
			break;
		case DIK_W:
			fp->RotateX(-0.03);
			break;
		case DIK_S:
			fp->RotateX(0.03);
			break;
		default:
			break;
		}
		return false;
	};

	GListenerMouse* mouse = new GListenerMouse();
	mouse->OnMouseMove = [](GEvent* e) {
		Point point = e->getMouseMove();
		if (GetAsyncKeyState(VK_RBUTTON))
		{
			fp->RotateY(point.x * 0.02f);
			fp->RotateX(point.y * 0.02f);
		}
		return true;
	};
	_eventDispatcher->addListener(mouse);

	_eventDispatcher->addListener(listener);
	

	return true;
};

void WinDestroy(){

};

void WinDraw(){
	WinUpdate();
	_eventDispatcher->loop();
	fp->setupCamera();
	dxBeginScene();

	ter->Draw();

	dxEndScene();
};

void WinUpdate(){
//	if(GetAsyncKeyState('W'))
//	{
//		fp->MoveZ(1);
//	}
//	if(GetAsyncKeyState('S'))
//	{
//		fp->MoveZ(-1);
//	}
//	if(GetAsyncKeyState('A'))
//	{
//		fp->MoveX(-1);
//	}
//	if(GetAsyncKeyState('D'))
//	{
//		fp->MoveX(1);
//	}
//
//	{
//		if(GetAsyncKeyState(VK_UP))
//		{
//			fp->RotateX(-0.01f);
//		}
//		if(GetAsyncKeyState(VK_DOWN))
//		{
//			fp->RotateX(0.01f);
//		}
//		if(GetAsyncKeyState(VK_LEFT))
//		{
//			fp->RotateY(-0.01f);
//		}
//		if(GetAsyncKeyState(VK_RIGHT))
//		{
//			fp->RotateY(0.01f);
//		}
//	}
//	
//	{
//		const D3DXVECTOR3* pos = fp->getPosition();
//		const D3DXVECTOR3* dst = fp->getDestPosition();
//		const D3DXVECTOR3* up = fp->getUp();
//		char text[1024] = { 0 };
//// 		sprintf_s(text, 
//// 			"{\n"
//// 			"position: x:%f, y:%f, z:%f \n"
//// 			"dstPos  : x:%f, y:%f, z:%f \n"
//// 			"Up      : x:%f, y:%f, z:%f \n"
//// 			"}\n",
//// 			pos->x, pos->y , pos->z,
//// 			dst->x, dst->y, dst->z,
//// 			up->x, up->y, up->z
//// 			);
//// 		OutputDebugStringA(text);
//	}
};

