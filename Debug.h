//===================================================================================================
//		�f�o�b�O
//																	2017/07/10			�c���@��P
//===================================================================================================
#ifndef _DEBUG_H_
#define _DEBUG_H_

//#if defined(_DEBUG) || defined(DEBUG)

typedef struct
{
	D3DXVECTOR4 pos;
	D3DCOLOR color;
}DEBUG_VERTEX;
#define FVF_DEBUG	(D3DFVF_XYZRHW || D3DFVF_DIFFUSE | D3DFVF_TEX1)

void InitDebugText(void);
void UninitDebugText(void);
void DebugText(int x, int y, const char* pFormat, ...);		//...�i�����_�j�����ƈ��������ɂł��� printf�̂悤��

void DebugPrimitive(int n, float x, float y, float r);

#endif
