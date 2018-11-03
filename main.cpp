#pragma once
//=====================================================================================================
//		ゲームループ			2017/05/25
//		
//=====================================================================================================

#include"main.h"
//====================================================================================================
//		定数定義
//====================================================================================================




//====================================================================================================
//		プロトタイプ宣言
//====================================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	//初期化
void Uninit(void);										//終了処理
void Update(void);										//update
void Draw(void);										//描画

#ifdef _DEBUG
void DrawFPS(void);										//FPS表示
#endif // _DEBUG

//===================================================================================================
//		グローバル変数
//===================================================================================================
static LPDIRECT3D9			g_pD3D = NULL;			//Direct3Dインターフェイス
static LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//Direct3Dデバイス
static HWND g_hWnd;
static bool g_bLoop = true;



//#ifdef _DEBUG
//LPD3DXFONT			g_pFont = NULL;
//int					g_nCountFPS = 0;
//#endif // _DEBUG


//===================================================================================================
//		WinMain関数
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
	wcex.style = CS_VREDRAW | CS_HREDRAW;						//縦横の再描画をする
	wcex.lpfnWndProc = WndProc;								//ウィンドウプロシージャの名前
	wcex.cbClsExtra = 0;										//使わないから０かNULL
	wcex.cbWndExtra = 0;										//使わないから０かNULL
	wcex.hInstance = hInstance;									//インスタンスハンドル
	wcex.hIcon = NULL;											//NULLで問題なし
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);					//マウスカーソル
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);			//背景設定
	wcex.lpszMenuName = NULL;									//メニューは使用しないのでNULL
	wcex.lpszClassName = CLASS_NAME;							//クラス登録名
	wcex.hIconSm = NULL;										//NULLで問題なし


	RegisterClassEx(&wcex);

	RECT wr = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&wr, WINDOW_STYLE, false);			//バーの分を含めたWINDOWサイズになる 800*600 -> 808 * 608

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
		(WINDOW_STYLE &~(WS_THICKFRAME | WS_MAXIMIZEBOX)),	//WindowsStyle		^を使うことでMINIMIZEBOXを封印
		StartWindowLocateX,						//Windowの開始時　左X
		StartWindowLocateY,						//Windowの開始時  左Y
		WindowWidth,						//Frameを含めた幅
		WindowHeight,						//Frameを含めた高さ
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
		MessageBox(g_hWnd, "初期化に失敗しました", "ERROR", MB_OK);
		return -1;
	}

	timeBeginPeriod(1);
	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{//メッセージ処理
			if (msg.message == WM_QUIT)
			{
				//ゲームループ終了
				break;
			}
			else
			{
				//メッセージ処理
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//ゲーム処理
			FrameTime = timeGetTime();
			if ((FrameTime - FrameOldTime) >= (1000 / GAME_FPS))
			{
				Update();
				Draw();
				FrameOldTime = FrameTime;	//OldTime更新
			}
		}
	} while (g_bLoop);
	timeEndPeriod(1);
	Uninit();

	return (int)msg.wParam;
}
//==============================================================================
//	WndProc関数
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
			//[ESC]キーが押された
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);		//ウィンドウを破棄する
			}
			break;
		}
		break;

	case WM_CLOSE:
		nID = MessageBox(hWnd, "終了しますか？", "終了ボタン", MB_YESNO | MB_DEFBUTTON2);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;

	case WM_RBUTTONDOWN://マウス右クリックしたメッセージ
		break;

	case WM_LBUTTONDOWN://マウス左クリックしたメッセージ
		SetFocus(hWnd);
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//===================================================================================================
//		初期化関数
//===================================================================================================
BOOL Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{


	//Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D9b_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイモードを取得
	D3DDISPLAYMODE d3ddm;
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))	//失敗したら真を返す
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションパラメータの作成
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//メモリを初期化 d3dppの構造体を0で初期化
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//バックバッファの幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//				高さ
	d3dpp.BackBufferFormat = d3ddm.Format;							//ディスプレイモードのフォーマットを設定
	d3dpp.BackBufferCount = 1;										//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//垂直同期を守るのか	DISCARDにしておけばいい
	d3dpp.EnableAutoDepthStencil = TRUE;							//3次元のものをやるので必ずTRUE
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//
	d3dpp.Windowed = bWindow;										//TRUE:Windowモード		FALSE:FULLSCREEN
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//FullScreen時のリフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//垂直同期をみて更新

																	//デバイスオブジェクトの生成
																	//[デバイス作成制御0]<描画>と<頂点処理>を
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice
	)))
	{
		//上記の設定が失敗したら
		//[デバイス作成制御]<描画>をハードウェア
		MessageBox(hWnd, "デバイス生成に失敗しました。", "ERROR", MB_OK);
		return false;
	};


	InitKeyboard(hInstance, hWnd);
	if (!InitPolygon())
	{
		MessageBox(hWnd, "ポリゴンの初期化に失敗しました", "ERROR", MB_OK);
		return false;
	}

	//レンダ―ステートの設定

	//αブレンドを行う
	//SRC...今から描くもの。つまりポリゴンにテクスチャが描画されるもの。
	//DEST...すでに描画されている画面のこと。
	//SRC_RGB * SRC_α + DEST_RGB * (1 - SRC_α)
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチャ―ステートの設定
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
//	終了処理
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
		//デバイスの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	if (g_pD3D != NULL)
	{
		//Direct3Dオブジェクトの開放
		g_pD3D->Release();
		g_pD3D = NULL;
	}

}
//===================================================================================================
//		更新処理
//===================================================================================================
void Update(void)
{
	//キーボード更新
	UpdateKeyboard();
	//シーン更新
	UpdateScene();
	//Enter更新
	UpdatePEnter();
	
}
//===================================================================================================
//		描画処理
//===================================================================================================
void Draw(void)
{

	g_pD3DDevice->Clear(
		0,												//全画面クリア
		NULL,											//全画面クリア
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),			//クリアするﾌﾗｸﾞ TARGET:色　
		D3DCOLOR_RGBA(100, 100, 100, 255),				//クリアカラー TARGETをいれることで有効になる　最初のうちは白黒をいれないこと
		1.0f,											//ZBUFFERのクリア値
		0												//ステンシルのクリア数値	今はステンシルをﾌﾗｸﾞたててないので無視される
	);

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);			//FVF(今から使用する頂点情報)

		//描画開始
		DrawScene();

		g_pD3DDevice->EndScene();//Direct3Dによる描画の終了
	}

	g_pD3DDevice->Present(
		NULL,
		NULL,
		NULL,											//対象となるウィンドウハンドル
		NULL
	);
}
//===================================================================================================
//		ＦＰＳ表示
//===================================================================================================
void DrawFPS(void)
{

}
LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	//デバイスを作ったらreturn
	return g_pD3DDevice;
}
void EndLoop(void)
{
	g_bLoop = false;
}