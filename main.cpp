#pragma once
//=====================================================================================================
//		�Q�[�����[�v			2017/05/25
//		
//=====================================================================================================

#include"main.h"
//====================================================================================================
//		�萔��`
//====================================================================================================




//====================================================================================================
//		�v���g�^�C�v�錾
//====================================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	//������
void Uninit(void);										//�I������
void Update(void);										//update
void Draw(void);										//�`��

#ifdef _DEBUG
void DrawFPS(void);										//FPS�\��
#endif // _DEBUG

//===================================================================================================
//		�O���[�o���ϐ�
//===================================================================================================
static LPDIRECT3D9			g_pD3D = NULL;			//Direct3D�C���^�[�t�F�C�X
static LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//Direct3D�f�o�C�X
static HWND g_hWnd;
static bool g_bLoop = true;



//#ifdef _DEBUG
//LPD3DXFONT			g_pFont = NULL;
//int					g_nCountFPS = 0;
//#endif // _DEBUG


//===================================================================================================
//		WinMain�֐�
//===================================================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int WindowWidth = 0;
	int WindowHeight = 0;
	int StartWindowLocateX = 0;
	int StartWindowLocateY = 0;
	DWORD FrameTime = 0;
	DWORD FrameOldTime = 0;

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW | CS_HREDRAW;						//�c���̍ĕ`�������
	wcex.lpfnWndProc = WndProc;								//�E�B���h�E�v���V�[�W���̖��O
	wcex.cbClsExtra = 0;										//�g��Ȃ�����O��NULL
	wcex.cbWndExtra = 0;										//�g��Ȃ�����O��NULL
	wcex.hInstance = hInstance;									//�C���X�^���X�n���h��
	wcex.hIcon = NULL;											//NULL�Ŗ��Ȃ�
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);					//�}�E�X�J�[�\��
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);			//�w�i�ݒ�
	wcex.lpszMenuName = NULL;									//���j���[�͎g�p���Ȃ��̂�NULL
	wcex.lpszClassName = CLASS_NAME;							//�N���X�o�^��
	wcex.hIconSm = NULL;										//NULL�Ŗ��Ȃ�


	RegisterClassEx(&wcex);

	RECT wr = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&wr, WINDOW_STYLE, false);			//�o�[�̕����܂߂�WINDOW�T�C�Y�ɂȂ� 800*600 -> 808 * 608

	WindowWidth = wr.right - wr.left;
	WindowHeight = wr.bottom - wr.top;

	RECT dr;
	GetWindowRect(GetDesktopWindow(), &dr);

	StartWindowLocateX = (dr.right - WindowWidth) / 2;
	StartWindowLocateY = (dr.bottom - WindowHeight) / 2;

	g_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		(WINDOW_STYLE &~(WS_THICKFRAME | WS_MAXIMIZEBOX)),	//WindowsStyle		^���g�����Ƃ�MINIMIZEBOX�𕕈�
		StartWindowLocateX,						//Window�̊J�n���@��X
		StartWindowLocateY,						//Window�̊J�n��  ��Y
		WindowWidth,						//Frame���܂߂���
		WindowHeight,						//Frame���܂߂�����
		NULL,								//
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(g_hWnd, nCmdShow);

	UpdateWindow(g_hWnd);

	MSG msg;

	if (!Init(hInstance, g_hWnd, TRUE))
	{
		MessageBox(g_hWnd, "�������Ɏ��s���܂���", "ERROR", MB_OK);
		return -1;
	}

	timeBeginPeriod(1);
	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{//���b�Z�[�W����
			if (msg.message == WM_QUIT)
			{
				//�Q�[�����[�v�I��
				break;
			}
			else
			{
				//���b�Z�[�W����
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//�Q�[������
			FrameTime = timeGetTime();
			if ((FrameTime - FrameOldTime) >= (1000 / GAME_FPS))
			{
				Update();
				Draw();
				FrameOldTime = FrameTime;	//OldTime�X�V
			}
		}
	} while (g_bLoop);
	timeEndPeriod(1);
	Uninit();

	return (int)msg.wParam;
}
//==============================================================================
//	WndProc�֐�
//==============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//[ESC]�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);		//�E�B���h�E��j������
			}
			break;
		}
		break;

	case WM_CLOSE:
		nID = MessageBox(hWnd, "�I�����܂����H", "�I���{�^��", MB_YESNO | MB_DEFBUTTON2);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;

	case WM_RBUTTONDOWN://�}�E�X�E�N���b�N�������b�Z�[�W
		break;

	case WM_LBUTTONDOWN://�}�E�X���N���b�N�������b�Z�[�W
		SetFocus(hWnd);
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//===================================================================================================
//		�������֐�
//===================================================================================================
BOOL Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{


	//Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D9b_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	D3DDISPLAYMODE d3ddm;
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))	//���s������^��Ԃ�
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̍쐬
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//�������������� d3dpp�̍\���̂�0�ŏ�����
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//�o�b�N�o�b�t�@�̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//				����
	d3dpp.BackBufferFormat = d3ddm.Format;							//�f�B�X�v���C���[�h�̃t�H�[�}�b�g��ݒ�
	d3dpp.BackBufferCount = 1;										//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//�������������̂�	DISCARD�ɂ��Ă����΂���
	d3dpp.EnableAutoDepthStencil = TRUE;							//3�����̂��̂����̂ŕK��TRUE
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//
	d3dpp.Windowed = bWindow;										//TRUE:Window���[�h		FALSE:FULLSCREEN
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//FullScreen���̃��t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�����������݂čX�V

																	//�f�o�C�X�I�u�W�F�N�g�̐���
																	//[�f�o�C�X�쐬����0]<�`��>��<���_����>��
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice
	)))
	{
		//��L�̐ݒ肪���s������
		//[�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A
		MessageBox(hWnd, "�f�o�C�X�����Ɏ��s���܂����B", "ERROR", MB_OK);
		return false;
	};


	InitKeyboard(hInstance, hWnd);
	if (!InitPolygon())
	{
		MessageBox(hWnd, "�|���S���̏������Ɏ��s���܂���", "ERROR", MB_OK);
		return false;
	}

	//�����_�\�X�e�[�g�̐ݒ�

	//���u�����h���s��
	//SRC...������`�����́B�܂�|���S���Ƀe�N�X�`�����`�悳�����́B
	//DEST...���łɕ`�悳��Ă����ʂ̂��ƁB
	//SRC_RGB * SRC_�� + DEST_RGB * (1 - SRC_��)
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�e�N�X�`���\�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	srand((unsigned)time(NULL));

	InitDebugText();
	InitSound(g_hWnd);
	InitScene();
	InitPEnter();


	LPDIRECT3DDEVICE9 GetD3DDevice();

	return true;
}
//===================================================================================================
//	�I������
//===================================================================================================
void Uninit(void)
{
	
	UninitKeyboard();
	UninitDebugText();
	UninitSound();
	UninitPolygon();
	UninitScene();
	UninitPEnter();
	
	if (g_pD3DDevice != NULL)
	{
		//�f�o�C�X�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	if (g_pD3D != NULL)
	{
		//Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}

}
//===================================================================================================
//		�X�V����
//===================================================================================================
void Update(void)
{
	//�L�[�{�[�h�X�V
	UpdateKeyboard();
	//�V�[���X�V
	UpdateScene();
	//Enter�X�V
	UpdatePEnter();
	
}
//===================================================================================================
//		�`�揈��
//===================================================================================================
void Draw(void)
{

	g_pD3DDevice->Clear(
		0,												//�S��ʃN���A
		NULL,											//�S��ʃN���A
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),			//�N���A�����׸� TARGET:�F�@
		D3DCOLOR_RGBA(100, 100, 100, 255),				//�N���A�J���[ TARGET������邱�ƂŗL���ɂȂ�@�ŏ��̂����͔���������Ȃ�����
		1.0f,											//ZBUFFER�̃N���A�l
		0												//�X�e���V���̃N���A���l	���̓X�e���V�����׸ނ��ĂĂȂ��̂Ŗ��������
	);

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);			//FVF(������g�p���钸�_���)

		//�`��J�n
		DrawScene();

		g_pD3DDevice->EndScene();//Direct3D�ɂ��`��̏I��
	}

	g_pD3DDevice->Present(
		NULL,
		NULL,
		NULL,											//�ΏۂƂȂ�E�B���h�E�n���h��
		NULL
	);
}
//===================================================================================================
//		�e�o�r�\��
//===================================================================================================
void DrawFPS(void)
{

}
LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	//�f�o�C�X���������return
	return g_pD3DDevice;
}
void EndLoop(void)
{
	g_bLoop = false;
}