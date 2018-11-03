//===================================================================================================
//		�|���S��
//																	2017/06/05			�c���@��P
//===================================================================================================

#include "main.h"

//======================================================
//		�O���[�o���ϐ�
//======================================================

static float g_fScale = 1.0f;
static float g_fScaleAdd = 0.02f;

static float g_fAngle = 0.0f;
static float g_fScaleX = 1.0f;
static float g_fScaleY = 1.0f;

static float g_fRotationOffsetX = 0.0f;
static float g_fRotationOffsetY = 0.0f;

static float g_fScaleOffsetX = 0.0f;
static float g_fScaleOffsetY = 0.0f;



//======================================================
//		�\����
//======================================================

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DTEXTURE9	g_pTextures[TEXTURE_MAX] = { NULL };

static void CreateVertexAffine(int texNum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);
static void CreateVertex(int texNum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);
//===================================================================================================
//		�|���S��������
//===================================================================================================
bool InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL) { return false; }

	

	//�T���v���[�X�e�[�g�̐ݒ�

	//WRAP...����
	//CLAMP...�����L�΂�
	//MIRROR...����
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�t�B���^�����O
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	HRESULT hr;
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		hr = D3DXCreateTextureFromFile(pDevice, g_aTextureFileNames[i].fileName, &g_pTextures[i]);
	}
	if (FAILED(hr))
	{
		return false;
	}

	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,	//���o�C�g�؂�邩 * �|���S����
		D3DUSAGE_WRITEONLY,		//�g�p�p�r �������݂̂݁@���g�͕ۏ؂���Ȃ��̂Ō��ɍs���Ȃ�
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,		//�f�o�C�X�ɊǗ�������
		&g_pVertexBuffer,		//�����݂̍菈
		NULL
	);
	if (FAILED(hr))
	{
		MessageBox(NULL, "���_�o�b�t�@������܂���ł����B", "ERROR", MB_OK);
	}

	return true;
}
//===================================================================================================
//		�|���S���I������
//===================================================================================================
void UninitPolygon(void)
{
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_pTextures[i] != NULL)
		{
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}
//===================================================================================================
//		�|���S���X�V����
//===================================================================================================
void UpdatePolygon(void)
{

}
//===================================================================================================
//		�|���S���`�揈��
//===================================================================================================
void DrawPolygon(int texNum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, bool Affine)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL) { return; }

	if (Affine == true)
	{
		CreateVertexAffine(texNum, color, dx, dy, dw, dh, tcx, tcy, tcw, tch);
	}
	else
	{
		CreateVertex(texNum, color, dx, dy, dw, dh, tcx, tcy, tcw, tch);
	}
	//GPU��VertexBuffer���p�C�v���C���łȂ�-+
	pDevice->SetStreamSource(
		0,
		g_pVertexBuffer,
		0,
		sizeof(VERTEX_2D)//�ׂ̒��_�܂łǂꂭ�炢�̒���
	);
	pDevice->SetTexture(0, g_pTextures[texNum]);
	//�|���S����`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,						//���o�C�g�ڂ���ǂݍ��ނ�
		2						//�O�p�`
	);
}
TEXPATTERN PatternPolygon(int Count, int Frame, int texWNum, int texHNum, int texW, int texH)
{
	TEXPATTERN texpattern;
	texpattern.patternNum = (Count / Frame) % (texWNum * texHNum);
	texpattern.patternW = texpattern.patternNum % texWNum;
	texpattern.patternH = texpattern.patternNum / texWNum;
	texpattern.tcx = texpattern.patternW * texW;
	texpattern.tcy = texpattern.patternH * texH;

	return texpattern;

}
void CreateVertex(int texNum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch)
{
	VERTEX_2D* pV;

	g_pVertexBuffer->Lock(
		0,				//�������烍�b�N���Ăق���
		0,				//�����܂Ń��b�N 0�������ƑS���؂�邱�Ƃ��ł���
		(void**)&pV,	//�^���A�h���X�@�b�o�t�̃������ɂ�������X�g�A���ăA�����b�N�����Ƃ��ɂu�q�`�l�ɓ]�������
		D3DLOCK_DISCARD	//�ӂ炮�@�O�ł������������׸ނ������ƌ������悭�Ȃ�
	);

	int tw = g_aTextureFileNames[texNum].width;
	int th = g_aTextureFileNames[texNum].height;

	float u0 = (float)tcx / tw;
	float v0 = (float)tcy / th;
	float u1 = (float)(tcx + tcw) / tw;
	float v1 = (float)(tcy + tch) / th;

	pV[0].pos = D3DXVECTOR4(dx + 0.0f - 0.5f, dy + 0.0f - 0.5f, 1.0f, 1.0f);
	pV[1].pos = D3DXVECTOR4(dx + dw - 0.5f, dy + 0.0f - 0.5f, 1.0f, 1.0f);
	pV[2].pos = D3DXVECTOR4(dx + 0.0f - 0.5f, dy + dh - 0.5f, 1.0f, 1.0f);
	pV[3].pos = D3DXVECTOR4(dx + dw - 0.5f, dy + dh - 0.5f, 1.0f, 1.0f);

	pV[0].color =
		pV[1].color =
		pV[2].color =
		pV[3].color = color;

	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	g_pVertexBuffer->Unlock();

}
void CreateVertexAffine(int texNum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch)
{
	VERTEX_2D* pV;

	g_pVertexBuffer->Lock(
		0,				//�������烍�b�N���Ăق���
		0,				//�����܂Ń��b�N 0�������ƑS���؂�邱�Ƃ��ł���
		(void**)&pV,	//�^���A�h���X�@�b�o�t�̃������ɂ�������X�g�A���ăA�����b�N�����Ƃ��ɂu�q�`�l�ɓ]�������
		D3DLOCK_DISCARD	//�ӂ炮�@�O�ł������������׸ނ������ƌ������悭�Ȃ�
	);

	int tw = g_aTextureFileNames[texNum].width;
	int th = g_aTextureFileNames[texNum].height;
	float u0 = (float)tcx / tw;
	float v0 = (float)tcy / th;
	float u1 = (float)(tcx + tcw) / tw;
	float v1 = (float)(tcy + tch) / th;

	float x = (-g_fScaleOffsetX) * g_fScaleX + g_fScaleOffsetX;
	float x_w = (tcw - g_fScaleOffsetX) * g_fScaleX + g_fScaleOffsetX;
	float y = (-g_fScaleOffsetY) * g_fScaleY + g_fScaleOffsetY;
	float y_h = (tch - g_fScaleOffsetY) * g_fScaleY + g_fScaleOffsetY;

	float fRotationOffsetX = g_fRotationOffsetX * g_fScaleX;
	float fRotationOffsetY = g_fRotationOffsetY * g_fScaleY;

	x -= fRotationOffsetX;
	x_w -= fRotationOffsetX;
	y -= fRotationOffsetY;
	y_h -= fRotationOffsetY;
	dx += fRotationOffsetX - 0.5f;
	dy += fRotationOffsetY - 0.5f;

	pV[0].pos = D3DXVECTOR4(dx + x  * cosf(g_fAngle) - y  * sinf(g_fAngle), dy + x  * sinf(g_fAngle) + y  * cosf(g_fAngle), 1.0f, 1.0f);
	pV[1].pos = D3DXVECTOR4(dx + x_w * cosf(g_fAngle) - y  * sinf(g_fAngle), dy + x_w * sinf(g_fAngle) + y  * cosf(g_fAngle), 1.0f, 1.0f);
	pV[2].pos = D3DXVECTOR4(dx + x  * cosf(g_fAngle) - y_h * sinf(g_fAngle), dy + x  * sinf(g_fAngle) + y_h * cosf(g_fAngle), 1.0f, 1.0f);
	pV[3].pos = D3DXVECTOR4(dx + x_w * cosf(g_fAngle) - y_h * sinf(g_fAngle), dy + x_w * sinf(g_fAngle) + y_h * cosf(g_fAngle), 1.0f, 1.0f);

	pV[0].color =
		pV[1].color =
		pV[2].color =
		pV[3].color = color;


	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	g_pVertexBuffer->Unlock();
}

//==================================================================================================
//		�|���S���p�x
//==================================================================================================
void SetPolygonRotation(float cx, float cy, float angle)
{
	g_fAngle = angle;			//�p�x
	g_fRotationOffsetX = cx;
	g_fRotationOffsetY = cy;
}
//==================================================================================================
//		�|���S���X�P�[��
//==================================================================================================
void SetPolygonScale(float cx, float cy, float sx, float sy)
{
	g_fScaleOffsetX = cx;	//�X�P�[���䗦x
	g_fScaleOffsetY = cy;	//�X�P�[���䗦y
	g_fScaleX = sx;
	g_fScaleY = sy;
}