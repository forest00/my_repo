// --------------------------------------------------------------------------
/// @file 
/// @brief 
// 
// --------------------------------------------------------------------------
#pragma once 
#if			defined( _SI_WIN32 )
#include	"WindowBase.h"

// --------------------------------------------------------------------------
/// @brief Window クラスの根底クラス 
// --------------------------------------------------------------------------
class WindowMain : public WindowBase
{
public:
	WindowMain( HINSTANCE hInstance );
	~WindowMain();

	BOOL	_OnCreate();								///< Window作成時メッセージ処理 
	BOOL	_OnDestroy();								///< Window破棄時メッセージ処理 
	BOOL	_OnLButtonDown(WPARAM , LPARAM);			///< マウス左ボタン押下時処理
	BOOL	_OnLButtonUP(WPARAM , LPARAM);				///< マウス左ボタン離上時処理
	BOOL	_OnMouseMove(WPARAM , LPARAM);				///< マウス移動時処理 
	BOOL	_OnPaint(WPARAM , LPARAM);					///< 描画処理 
private:
	BOOL	_bLeft;
	BOOL	_bRight;
	BOOL	_bCenter;
};

/// アクティブハンドルの設定 
void	WindowMain_SetActiveHandle( HWND hWnd );

/// マウスメッセージをタッチメッセージに変更するか 
void	WindowMain_SetMouseToTouch( BOOL bEnable );
#endif
