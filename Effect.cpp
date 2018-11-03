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
		//Effect �S�����g�p�@�ɂ���
		Effect[i].bEffect = false;
	}
	//�G�t�F�N�g�@�O���[�o�����ԁ@������
	g_nFrameCount = 0;
}
void UninitEffect(void)
{

}
void UpdateEffect(void)
{
	//�����̃`�F�b�N
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!Effect[i].bEffect) continue;

		float nAge = (float)g_nFrameCount - Effect[i].nBirth;
		//�N��ɂ���ă��l��ύX����
		//0�΂͍ŏ��ɐݒ肳�ꂽ���l
		//�������}����N��̎��A�� == 0
		Effect[i].color.a = 1.0f - nAge / Effect[i].nLimit;

		if (nAge >= Effect[i].nLimit)
		{
			//���肪�Ƃ�
			Effect[i].bEffect = false;
		}
	}

	//Effect �O���[�o���^�C���X�V
	g_nFrameCount++;
}
void DrawEffect(void)
{
	//���Z�����̐ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (Effect[i].bEffect)
		{

			//Effect�����݂��Ă���Ƃ��`��
			//Effect�̊ۂ�`��
			DrawPolygon(TEXTURE_EFFECT, Effect[i].color, (float)Effect[i].vPos.x, (float)Effect[i].vPos.y, (float)EFFECT_WIDTH, (float)EFFECT_HEIGHT, 0, 0, 80, 80);
			
		}
	}
	//�ʏ�̃��u�����h�i�����������j�ɖ߂�
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
			break;		//break����Ȃ��ƈ�C�ɐ������Ă��܂�
		}
	}
}