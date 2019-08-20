// --------------------------------------------------------------------------
/// @file 
/// @brief 
// 
// --------------------------------------------------------------------------
#if			defined( _SI_WIN32 )
#include	"WindowMain.h"
#include	"SiLibrary.h"
#include	"SiLibraryServer.h"
#include	"SiDraw.h"
#include	"SiDrawConfig.h"
#include	"SiDrawServer.h"
#include	"SiFileServer.h"
#include	"SiVector2.h"
#include	"SiTouchServer.h"
#include	"ApplicationBase.h"

static char szWindowTitle[] = ("[SiLibrary]メインウィンドウ");			// タイトル バーのテキスト 
static char szWindowClass[] = ("WindowMain");							// メイン ウィンドウ クラス名 

typedef		std::vector<HWND>	vecHWND;

static	BOOL	s_bMouseToTouch = TRUE;

// --------------------------------------------------------------------------
/// @brief コンストラクタ 
// --------------------------------------------------------------------------
WindowMain::WindowMain( HINSTANCE hInstance ) : WindowBase( hInstance )
{
	_bLeft   = FALSE;
	_bRight  = FALSE;
	_bCenter = FALSE;

	DWORD	dwStyle = WS_CAPTION | WS_SYSMENU;
	// ウィンドウの登録 
	_RegistWindowClass( szWindowClass );
	HWND	hWnd = CreateWindow(	szWindowClass, 
									szWindowTitle, 
									dwStyle , 
									CW_USEDEFAULT, 
									CW_USEDEFAULT , 
									SI_SCREEN_WIDTH , 
									SI_SCREEN_HEIGHT , 
									NULL , 
									NULL , 
									hInstance , 
									this );
	// 表示設定 
	ShowWindow( hWnd, FALSE );
	UpdateWindow( hWnd );

	// サイズの調整 
	RECT tRect;
	GetClientRect( hWnd , &tRect );
	SetWindowPos( hWnd , NULL , 0 , 0 , SI_SCREEN_WIDTH * 2 - tRect.right , SI_SCREEN_HEIGHT * 2 - tRect.bottom  , SWP_NOMOVE | SWP_NOZORDER );

	// 表示開始 
	ShowWindow( hWnd, TRUE );
}

// --------------------------------------------------------------------------
/// @brief デストラクタ 
// --------------------------------------------------------------------------
WindowMain::~WindowMain()
{
	_UnRegistWindowClass( szWindowClass );
}

// --------------------------------------------------------------------------
/// @brief  Window作成時メッセージ処理 
// --------------------------------------------------------------------------
BOOL	WindowMain::_OnCreate()
{
	// パスの設定 
	SiFileServer::SetBasePath( "assets" );

	SiDrawConfig	tConfig;
	tConfig.hWnd   = _hWnd;
	tConfig.width  = SI_SCREEN_WIDTH;
	tConfig.height = SI_SCREEN_HEIGHT;

	// ハードウェアの初期化 
	SiLibraryServer::Initialize();

	// 描画サーバーの初期化 
	SiDrawServer::Initialize( &tConfig );

	SiApplicationBase::GetInstance()->CallInitialize();

	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief  Window破棄時メッセージ処理 
// --------------------------------------------------------------------------
BOOL	WindowMain::_OnDestroy()
{
	SiApplicationBase::GetInstance()->CallTerminate();
	// 描画サーバーの解放 
	SiDrawServer::Terminate();
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief  マウス左ボタン押下時処理
// --------------------------------------------------------------------------
BOOL	WindowMain::_OnLButtonDown(WPARAM , LPARAM lParam )
{
	if( s_bMouseToTouch )
	{
		_bLeft = TRUE;
		// キャプチャー 
		SetCapture( _hWnd );
		// 座標取りだし 
		SiVector2	vPosition;
		vPosition.x = (SiF32)(short)LOWORD( lParam );
		vPosition.y = (SiF32)(short)HIWORD( lParam );
		SiTouchServer::GetInstance()->Begin( 0 , &vPosition );
	}
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief  マウス左ボタン離上時処理
// --------------------------------------------------------------------------
BOOL	WindowMain::_OnLButtonUP(WPARAM , LPARAM lParam )
{
	if( s_bMouseToTouch )
	{
		_bLeft = FALSE;
		// 座標取りだし 
		SiVector2	vPosition;
		vPosition.x = (SiF32)(short)LOWORD( lParam );
		vPosition.y = (SiF32)(short)HIWORD( lParam );
		SiTouchServer::GetInstance()->End( 0 , &vPosition );
		// リリース 
		ReleaseCapture();
	}
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief  マウス移動時処理
// --------------------------------------------------------------------------
BOOL	WindowMain::_OnMouseMove(WPARAM , LPARAM lParam )
{
	if( _bLeft   || _bRight  || _bCenter )
	{
		// 座標取りだし 
		SiVector2	vPosition;
		vPosition.x = (SiF32)(short)LOWORD( lParam );
		vPosition.y = (SiF32)(short)HIWORD( lParam );
		SiTouchServer::GetInstance()->Move( 0 , &vPosition );
	}
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief 描画処理 
// --------------------------------------------------------------------------
BOOL	WindowMain::_OnPaint(WPARAM , LPARAM)
{
	// 初期化済みのみ実行 
	if( SiDrawServer::IsInitialize() )
	{
		SiApplicationBase::GetInstance()->CallStartFrame();
		SiApplicationBase::GetInstance()->CallProcess();
		SiApplicationBase::GetInstance()->CallRender();
		SiDrawServer::GetDraw()->Flip();
		SiApplicationBase::GetInstance()->CallEndFrame();
	}
	return	FALSE;
}

static	vecHWND		s_vhWnd;

// --------------------------------------------------------------------------
/// @brief メインプロセス 
// --------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG				tMessage;
	// 生成 
	WindowMain	oWindow( hInstance );
	// メイン メッセージ ループ:
	while ( SI_TRUE )
	{
		if( PeekMessage( &tMessage , NULL , 0 , 0 , PM_REMOVE ) )
		{
			if( tMessage.wParam == 0 )
			{
				if( tMessage.message == WM_QUIT )
				{
					break;
				}
			}
			// ダイアログ以外ならばメッセージを送る 
			SiBool	bDialog = SI_FALSE;
			for( vecHWND::iterator ite = s_vhWnd.begin() ; ite != s_vhWnd.end() ; ++ ite )
			{
				// ダイアログメッセージか確認して、ダイアログメッセージならば処理してフラグを立てる 
				if( IsDialogMessage( (*ite) , &tMessage ) )
				{
					bDialog = SI_TRUE;
					break;
				}
			}
			if( bDialog == SI_FALSE )
			{
				TranslateMessage(&tMessage);
				DispatchMessage(&tMessage);
			}
		}
		else if( oWindow.GethWnd() != NULL )
		{
			oWindow._OnPaint( NULL , NULL );
		}
	}
	// ハードウェアの解放 
	SiLibraryServer::Terminate();

	SiMemoryDebugPrint();

	return (int)tMessage.wParam;
}

/// マウスメッセージをタッチメッセージに変更するか 
void	WindowMain_SetMouseToTouch( BOOL bEnable )
{
	s_bMouseToTouch = bEnable;
}


/// アクティブダイアログハンドルの設定 
void	WindowMain_SetActiveHandle( HWND hWnd )
{
	// 未登録ならば追記する 
	if( hWnd != NULL )
	{
		vecHWND::iterator ite = std::find( s_vhWnd.begin() , s_vhWnd.end() , hWnd );
		if( ite == s_vhWnd.end() )
		{
			s_vhWnd.push_back( hWnd );
		}
	}
}

#endif
