//=================================================================================
//
//		Effect cpp
//
//=================================================================================


#include "main.h"

void InitEffect(void)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		//Effect 全部未使用　にする
		Effect[i].bEffect = false;
	}
	//エフェクト　グローバル時間　初期化
	g_nFrameCount = 0;
}
void UninitEffect(void)
{

}
void UpdateEffect(void)
{
	//寿命のチェック
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!Effect[i].bEffect) continue;

		float nAge = (float)g_nFrameCount - Effect[i].nBirth;
		//年齢によってα値を変更する
		//0歳は最初に設定されたα値
		//寿命を迎える年齢の時、α == 0
		Effect[i].color.a = 1.0f - nAge / Effect[i].nLimit;

		if (nAge >= Effect[i].nLimit)
		{
			//ありがとう
			Effect[i].bEffect = false;
		}
	}

	//Effect グローバルタイム更新
	g_nFrameCount++;
}
void DrawEffect(void)
{
	//加算合成の設定
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (Effect[i].bEffect)
		{

			//Effectが存在しているとき描画
			//Effectの丸を描く
			DrawPolygon(TEXTURE_EFFECT, Effect[i].color, (float)Effect[i].vPos.x, (float)Effect[i].vPos.y, (float)EFFECT_WIDTH, (float)EFFECT_HEIGHT, 0, 0, 80, 80);
			
		}
	}
	//通常のαブレンド（半透明処理）に戻す
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
void CreateEffect(float x, float y, D3DXCOLOR color, int nLimit)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!Effect[i].bEffect)
		{
			Effect[i].bEffect = true;
			Effect[i].color = color;
			Effect[i].nBirth = g_nFrameCount;
			Effect[i].nLimit = nLimit;
			Effect[i].vPos = D3DXVECTOR2(x,y);
			break;		//breakいれないと一気に生成してしまう
		}
	}
}