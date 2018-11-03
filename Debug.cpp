//===================================================================================================
//		DEBUG
//																	2017/07/10			�c���@��P
//===================================================================================================

#include "main.h"

#ifdef _DEBUG
static LPD3DXFONT g_pFont = NULL;
#endif
//============================================================
//		������
//============================================================
void InitDebugText(void)
{
#ifdef _DEBUG
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL) { return; }

	D3DXCreateFont(pDevice,18,0,0,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"Terminal",&g_pFont);
#endif
}
//============================================================
//		�I������
//============================================================
void UninitDebugText(void)
{
#ifdef _DEBUG
	if (g_pFont)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
#endif
}
//============================================================
//		�f�o�b�O�����\��
//============================================================
void DebugText(int x, int y, const char* pFormat, ...)
{
#ifdef _DEBUG
	va_list argp;
	char strBuf[512];
	va_start(argp, pFormat);				//...�̖��������̊J�n
	vsprintf_s(strBuf,512,pFormat,argp);
	va_end(argp);							//...�I���

	RECT rect = { x,y,SCREEN_WIDTH,SCREEN_HEIGHT };
	g_pFont->DrawText(
		NULL,
		strBuf,
		-1, 
		&rect,								//rect�\����
		DT_LEFT,							//����
		D3DCOLOR_RGBA(128, 255, 64, 255));	//�F�@��
#endif
}
//============================================================
//		�f�o�b�O�p�@���p�`�\��
//============================================================
void DebugPrimitive(int n, float x, float y, float r)
{
#ifdef _DEBUG
	
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL) { return; }

	const float C_R = D3DX_PI * 2 / n;

	//���_�o�b�t�@�쐬
	DEBUG_VERTEX* pV = (DEBUG_VERTEX*)malloc(sizeof(DEBUG_VERTEX) * (n + 1));

	for (int i = 0; i < n + 1; i++)
	{
		pV[i].pos.x = x + cosf(C_R * i) * r;
		pV[i].pos.y = y + sinf(C_R * i) * r;
		pV[i].pos.z = 1.0f;
		pV[i].pos.w = 1.0f;
		pV[i].color = D3DCOLOR_RGBA(128, 255, 64, 255);	//�F�@��
	}

	pDevice->SetTexture(0,NULL);
	pDevice->SetFVF(FVF_DEBUG);
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, n, pV, sizeof(DEBUG_VERTEX));

	free(pV);
#endif
}
