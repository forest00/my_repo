// --------------------------------------------------------------------------
/// @file 
/// @brief 
// 
// --------------------------------------------------------------------------
#pragma once 
#if			defined( _SI_WIN32 )
#include	<Windows.h>

// --------------------------------------------------------------------------
/// @brief Window クラスの根底クラス 
// --------------------------------------------------------------------------
class WindowBase
{
public:
	/// ハンドルの取り出し 
	HWND			GethWnd()       { return _hWnd; }
	/// 親ハンドルの取り出し 
	HWND			GethWndParent() { return _hWndParent; }
	/// Windowの位置取り出し 
	virtual	POINT	GetPosition() const;
protected:
	/// コンストラクタ 
	WindowBase( HINSTANCE hInstance , HWND hWndParent = NULL );
	/// デストラクタ 
	virtual	~WindowBase();

protected:
	virtual	BOOL	_OnCreate();								///< Window作成時メッセージ処理 
	virtual	BOOL	_OnDestroy();								///< Window破棄時メッセージ処理 
	virtual BOOL	_OnLButtonDown(WPARAM , LPARAM);			///< マウス左ボタン押下時処理
	virtual BOOL	_OnLButtonUP(WPARAM , LPARAM);				///< マウス左ボタン離上時処理
	virtual BOOL	_OnRButtonDown(WPARAM , LPARAM);			///< マウス左ボタン押下時処理
	virtual BOOL	_OnRButtonUP(WPARAM , LPARAM);				///< マウス左ボタン離上時処理
	virtual BOOL	_OnMButtonDown(WPARAM , LPARAM);			///< マウス中ボタン押下時処理
	virtual BOOL	_OnMButtonUP(WPARAM , LPARAM);				///< マウス中ボタン離上時処理
	virtual BOOL	_OnMouseMove(WPARAM , LPARAM);				///< マウス移動時処理 
	virtual BOOL	_OnMouseWheel(WPARAM , LPARAM);				///< マウスホイール処理 
	virtual BOOL	_OnPaint(WPARAM , LPARAM);					///< 描画処理 
	virtual BOOL	_OnActive(WPARAM , LPARAM);					///< アクティブ化の処理 
	virtual BOOL	_OnCommand( WPARAM , LPARAM );				///< Window コマンド処理 
	virtual BOOL	_OnKeyDown( WPARAM , LPARAM );				///< キーボード処理 
	virtual BOOL	_OnNotify( WPARAM , LPARAM );				///< Window 通知処理 
	virtual BOOL	_OnDropFiles( WPARAM , LPARAM );			///< ドロップ処理 
	virtual BOOL	_OnTimer( WPARAM , LPARAM );				///< タイマー処理 
	virtual BOOL	_OnMove( WPARAM , LPARAM );					///< 移動時処理 

	/// オーバーライド可能なウィンドウプロシージャ
	virtual LRESULT _WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

protected:
																/// Window Class を登録する 
	void	_RegistWindowClass( const char * szWindowClass , const char * szMenuName = NULL );
																/// Window Class を登録解除する 
	void	_UnRegistWindowClass( const char * szWindowClass );
																/// メッセージを振り分けるウィンドウプロシージャ
static LRESULT CALLBACK _WindowMapProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void	_Attach( HWND hWnd );						///< アタッチ 
	virtual void	_Detach();									///< デタッチ 
protected:
	HWND			_hWnd;										///< Window ハンドル 
	HWND			_hWndParent;								///< Window ハンドル 
	HINSTANCE		_hInstance;									///< Window 起動時のインスタンス 
	WNDPROC			_lpWindowProc;   							///< 元のウィンドウプロシージャ 
	POINT			_tWindowPosition;							///< WIndowの表示位置 
};
#endif
