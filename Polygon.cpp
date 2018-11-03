//===================================================================================================
//		ポリゴン
//																	2017/06/05			田中　大輝
//===================================================================================================

#include "main.h"

//======================================================
//		グローバル変数
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
//		構造体
//======================================================

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DTEXTURE9	g_pTextures[TEXTURE_MAX] = { NULL };

static void CreateVertexAffine(int texNum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);
static void CreateVertex(int texNum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);
//===================================================================================================
//		ポリゴン初期化
//===================================================================================================
bool InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL) { return false; }

	

	//サンプラーステートの設定

	//WRAP...反復
	//CLAMP...引き伸ばし
	//MIRROR...反射
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//フィルタリング
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
		sizeof(VERTEX_2D) * 4,	//何バイト借りるか * ポリゴン数
		D3DUSAGE_WRITEONLY,		//使用用途 書き込みのみ　中身は保証されないので見に行けない
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,		//デバイスに管理させる
		&g_pVertexBuffer,		//メモの在り処
		NULL
	);
	if (FAILED(hr))
	{
		MessageBox(NULL, "頂点バッファが作られませんでした。", "ERROR", MB_OK);
	}

	return true;
}
//===================================================================================================
//		ポリゴン終了処理
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
//		ポリゴン更新処理
//===================================================================================================
void UpdatePolygon(void)
{

}
//===================================================================================================
//		ポリゴン描画処理
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
	//GPUとVertexBufferをパイプラインでつなぐ-+
	pDevice->SetStreamSource(
		0,
		g_pVertexBuffer,
		0,
		sizeof(VERTEX_2D)//隣の頂点までどれくらいの長さ
	);
	pDevice->SetTexture(0, g_pTextures[texNum]);
	//ポリゴンを描く
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,						//何バイト目から読み込むか
		2						//三角形
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
		0,				//ここからロックしてほしい
		0,				//ここまでロック 0をいれると全部借りることができる
		(void**)&pV,	//疑似アドレス　ＣＰＵのメモリにいったんストアしてアンロックしたときにＶＲＡＭに転送される
		D3DLOCK_DISCARD	//ふらぐ　０でもいいがこのﾌﾗｸﾞをいれると効率がよくなる
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
		0,				//ここからロックしてほしい
		0,				//ここまでロック 0をいれると全部借りることができる
		(void**)&pV,	//疑似アドレス　ＣＰＵのメモリにいったんストアしてアンロックしたときにＶＲＡＭに転送される
		D3DLOCK_DISCARD	//ふらぐ　０でもいいがこのﾌﾗｸﾞをいれると効率がよくなる
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
//		ポリゴン角度
//==================================================================================================
void SetPolygonRotation(float cx, float cy, float angle)
{
	g_fAngle = angle;			//角度
	g_fRotationOffsetX = cx;
	g_fRotationOffsetY = cy;
}
//==================================================================================================
//		ポリゴンスケール
//==================================================================================================
void SetPolygonScale(float cx, float cy, float sx, float sy)
{
	g_fScaleOffsetX = cx;	//スケール比率x
	g_fScaleOffsetY = cy;	//スケール比率y
	g_fScaleX = sx;
	g_fScaleY = sy;
}