// --------------------------------------------------------------------------
/// @file 
/// @brief 
// 
// --------------------------------------------------------------------------
#if			defined( _SI_WIN32 )
#include	"SiLibrary.h"
#include	"WindowBase.h"

// --------------------------------------------------------------------------
/// @brief コンストラクタ 
// --------------------------------------------------------------------------
WindowBase::WindowBase( HINSTANCE hInstance , HWND hWndParent )
{
	_hWnd         = NULL;
	_hWndParent   = hWndParent;
	_hInstance    = hInstance;
	_lpWindowProc = NULL;
}

// --------------------------------------------------------------------------
/// @brief デストラクタ 
// --------------------------------------------------------------------------
WindowBase::~WindowBase()
{
}

/// --------------------------------------------------------------------------
// @brief Window Class を登録する 
// --------------------------------------------------------------------------
void	WindowBase::_RegistWindowClass( const char * szWindowClass , const char * szMenuName )
{
	// Ｗｉｎｄｏｗクラスの設定
	WNDCLASS			myProg;

	myProg.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	myProg.lpfnWndProc   = WindowBase::_WindowMapProc;
	myProg.cbClsExtra    = 0;
	myProg.cbWndExtra    = 0;
	myProg.hInstance     = _hInstance;
	myProg.hIcon         = NULL;
	myProg.hCursor       = LoadCursor( NULL , IDC_ARROW );
	myProg.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	myProg.lpszMenuName  = szMenuName;
	myProg.lpszClassName = szWindowClass;

	RegisterClass(&myProg);
}

// --------------------------------------------------------------------------
/// @brief Window Class を登録解除する 
// --------------------------------------------------------------------------
void	WindowBase::_UnRegistWindowClass( const char * szWindowClass )
{
	UnregisterClass( szWindowClass , _hInstance );
}

// --------------------------------------------------------------------------
/// @brief メッセージを振り分けるウィンドウプロシージャ
// --------------------------------------------------------------------------
LRESULT CALLBACK WindowBase::_WindowMapProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// ウィンドウのプロパティリストからWindowBaseへのポインタの取得を試みる
	WindowBase* lpWindowBase = (WindowBase*)GetWindowLongPtr( hWnd , GWLP_USERDATA );
	// Window 作成時ならば 
	if( uMsg == WM_CREATE )
	{
		lpWindowBase = (WindowBase*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		// USER DATA にデータを登録する 
		if( lpWindowBase )
		{
			lpWindowBase->_Attach( hWnd );
		}
	}
	if( lpWindowBase )
	{
		return	lpWindowBase->_WindowProc( hWnd , uMsg , wParam , lParam );
	}
	// を呼び出す
	return DefWindowProc( hWnd , uMsg , wParam , lParam );
}

// --------------------------------------------------------------------------
/// @brief アタッチ 
// --------------------------------------------------------------------------
void	WindowBase::_Attach( HWND hWnd )
{
	// ウィンドウハンドル hWnd を m_hWnd に保存
	_hWnd = hWnd;
	// 既存のウィンドウをサブクラス化する場合は、ウィンドウプロシージャ
	// をWindowMapProcに置き換える
	if (GetWindowLongPtr( hWnd , GWLP_WNDPROC) != (LONG_PTR)_WindowMapProc )
	{
		_lpWindowProc = (WNDPROC)SetWindowLongPtr( hWnd, GWLP_WNDPROC, (LONG_PTR)_WindowMapProc );
	}
	// ウィンドウハンドルとIWindowBaseオブジェクトを結びつける
	SetWindowLongPtr( hWnd , GWLP_USERDATA , (LONG_PTR)this );
}

// --------------------------------------------------------------------------
/// @brief デタッチ 
// --------------------------------------------------------------------------
void	WindowBase::_Detach()
{
	if(( _lpWindowProc ) && ( _hWnd ))
	{
		// アタッチ済みの場合、設定する 
		if (GetWindowLongPtr( _hWnd , GWLP_WNDPROC) == (LONG_PTR)_WindowMapProc )
		{
			// ウィンドウがサブクラス化されている場合は、ウィンドウプロシージャ
			// を元に戻す。
			SetWindowLongPtr(_hWnd, GWLP_WNDPROC, (LONG_PTR)_lpWindowProc );
			// ポインタクリア 
			_lpWindowProc = NULL;
		}
		else
		{
			// エラー 
			SI_ASSERT( NULL , "[ERROR] _Detach\n" );
		}
	}
	if( _hWnd )
	{
		// ウィンドウハンドルをIWindowBaseオブジェクトから切り離す
		SetWindowLongPtr( _hWnd , GWLP_USERDATA , (LONG_PTR)0 );
	}
}

// --------------------------------------------------------------------------
/// @brief オーバーライド可能なウィンドウプロシージャ
// --------------------------------------------------------------------------
LRESULT WindowBase::_WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	// メッセージを仕分ける 
	switch (uMsg)
	{
		case WM_CREATE:			if( _OnCreate()                         == TRUE ) return 0;break;
		case WM_ACTIVATE:		if( _OnActive(        wParam , lParam ) == TRUE ) return 0;break;
		case WM_LBUTTONDOWN:	if( _OnLButtonDown(   wParam , lParam ) == TRUE ) return 0;break;
		case WM_LBUTTONUP:		if( _OnLButtonUP(     wParam , lParam ) == TRUE ) return 0;break;
		case WM_RBUTTONDOWN:	if( _OnRButtonDown(   wParam , lParam ) == TRUE ) return 0;break;
		case WM_RBUTTONUP:		if( _OnRButtonUP(     wParam , lParam ) == TRUE ) return 0;break;
		case WM_MBUTTONDOWN:	if( _OnMButtonDown(   wParam , lParam ) == TRUE ) return 0;break;
		case WM_MBUTTONUP:		if( _OnMButtonUP(     wParam , lParam ) == TRUE ) return 0;break;
		case WM_MOUSEMOVE:		if( _OnMouseMove(     wParam , lParam ) == TRUE ) return 0;break;
		case WM_MOUSEHWHEEL:	if( _OnMouseWheel(    wParam , lParam ) == TRUE ) return 0;break;
		case WM_PAINT:			if( _OnPaint(         wParam , lParam ) == TRUE ) return 0;break;
		case WM_COMMAND:		if( _OnCommand(       wParam , lParam ) == TRUE ) return 0;break;
		case WM_NOTIFY:			if( _OnNotify(        wParam , lParam ) == TRUE ) return 0;break;
		case WM_DROPFILES:		if( _OnDropFiles(     wParam , lParam ) == TRUE ) return 0;break;
		case WM_TIMER:			if( _OnTimer(         wParam , lParam ) == TRUE ) return 0;break;
		case WM_MOVE:			if( _OnMove(          wParam , lParam ) == TRUE ) return 0;break;
			break;

			// 終了するときにサブクラス化を解除
		case WM_DESTROY:
			if( !_OnDestroy() )
			{
				_Detach();
				PostQuitMessage( 0 );
			}
			return	0;
	}
	// を呼び出す
	return DefWindowProc( hWnd , uMsg , wParam , lParam );
}

// --------------------------------------------------------------------------
/// @brief  Window作成時メッセージ処理 
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnCreate()
{
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief  Window破棄時メッセージ処理 
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnDestroy()
{
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief アクティブ化の処理 
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnActive(WPARAM , LPARAM)
{
	return FALSE;
}

// --------------------------------------------------------------------------
/// @brief Window キーボード処理 
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnKeyDown( WPARAM wParam , LPARAM lParam )
{
	return FALSE;
}

// --------------------------------------------------------------------------
/// @brief Window コマンド処理 
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnCommand( WPARAM wParam , LPARAM lParam )
{
	return FALSE;
}

// --------------------------------------------------------------------------
/// @brief  マウス中ボタン押下時処理
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnMButtonDown(WPARAM , LPARAM)
{
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief  マウス中ボタン離上時処理
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnMButtonUP(WPARAM , LPARAM)
{
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief  マウス左ボタン押下時処理
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnLButtonDown(WPARAM , LPARAM)
{
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief  マウス左ボタン離上時処理
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnLButtonUP(WPARAM , LPARAM)
{
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief  マウス右ボタン離上時処理
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnRButtonUP(WPARAM , LPARAM)
{
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief  マウス右ボタン押下時処理
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnRButtonDown(WPARAM , LPARAM)
{
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief  マウスホイール処理
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnMouseWheel(WPARAM , LPARAM)
{
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief  マウス移動時処理
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnMouseMove(WPARAM , LPARAM)
{
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief 描画処理 
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnPaint(WPARAM , LPARAM)
{
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief Window 通知処理 
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnNotify( WPARAM , LPARAM )
{
	return	FALSE;
}
// --------------------------------------------------------------------------
/// @brief Window タイマー処理  
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnTimer( WPARAM , LPARAM )
{
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief ドロップ処理 
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnDropFiles( WPARAM , LPARAM )
{
	return	FALSE;
}

// --------------------------------------------------------------------------
/// @brief Window 移動時処理 
// --------------------------------------------------------------------------
BOOL	WindowBase::_OnMove( WPARAM wParam , LPARAM lParam )
{
	RECT	rectScreen;
	GetWindowRect( _hWnd , &rectScreen );
	POINT	tRect = { rectScreen.left , rectScreen.top };
	_tWindowPosition = tRect;
	return FALSE;
}

POINT			WindowBase::GetPosition() const
{
	return _tWindowPosition;
}


#endif
