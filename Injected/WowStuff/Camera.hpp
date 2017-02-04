#pragma once
#include <d3d9.h>

typedef struct
{
	int vtable;
	int field2;
	C3Vector Position;
	float fViewMat[9];
	float NearPlane;
	float FarPlane;
	float FieldOfView;
	float Aspect;
}CameraInfo;

int GetActiveCamera() 
{ 
	auto world_frame = *(int*)(0x00B4B2BC);

	if (world_frame)
		return *(int*)(world_frame + 0x65B8);	/*WorldFrame + ActiveCamera*/
	else
		return 0;
}

//D3DXMATRIX Projection()
//{
//	CameraInfo* cam = (CameraInfo*)GetActiveCamera();
//	D3DXMATRIX matrix;
//	D3DXMatrixPerspectiveFovLH(&matrix, cam->FieldOfView * 0.6f, cam->Aspect, cam->NearPlane, cam->FarPlane);
//	return matrix;
//}

int GetVirtualFuncAddr(int addr, int offset) { return addr ? *(int*)(*(int*)addr + 4 * offset) : 0; }

C3Vector Forward()
{
	C3Vector res{};

	if (GetActiveCamera())
	{
		int funcaddr = GetVirtualFuncAddr(GetActiveCamera(), 1);
		((C3Vector*(__thiscall*)(int, C3Vector*))(funcaddr))(GetActiveCamera(), &res);
	}
	return res;
}

//D3DXMATRIX View()
//{
//	CameraInfo* cam = (CameraInfo*)GetActiveCamera();
//	C3Vector eye = cam->Position;
//	C3Vector at = eye + Forward();
//	C3Vector up = { 0, 0, 1 };
//	D3DXMATRIX matrix;
//	D3DXMatrixLookAtRH(&matrix, &eye, &at, &up);
//	return matrix;
//}