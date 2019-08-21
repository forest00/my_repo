#pragma once
#include <string>
#include <Windows.h>
#include <tchar.h>

using tstring = std::basic_string<TCHAR>;

namespace myWindow
{
    //ウィンドウクラス
    //生成時に登録され、破棄時に登録解除される
    //名前とHINSTANCEを保持している
    //ウィンドウメッセージを振り分ける機能を持つ
    //ウィンドウの拡張メモリGWLP_USERDATAにWindow *を格納しておく必要がある
    class WindowClass
    {
    public:
        WindowClass(const WindowClass &) = delete;
        WindowClass &operator=(const WindowClass &) = delete;
        //コンストラクタ
        //生成と同時に登録される
        WindowClass(tstring _name, HINSTANCE _instanceHandle);
        //デストラクタ
        //破棄と同時に登録解除される
        ~WindowClass();
    public:
        virtual auto getName()const->const tstring &;
        virtual auto getInstanceHandle()const->const HINSTANCE;
    public:
        static auto CALLBACK commonWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)->LRESULT;
    protected:
        tstring name;
        HINSTANCE instanceHandle;
    };

    //ウィンドウ基底クラス
    class Window
    {
    protected:
        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;
        //コンストラクタ
        Window();
        //デストラクタ
        virtual ~Window();
    public:
        //ウィンドウクラスの名前取得
        virtual auto getClassName()const->const tstring &;
        //ウィンドウクラスのHINSTANCE取得
        virtual auto getInstanceHandle()const->const HINSTANCE;
        //ハンドルの取り出し
        virtual auto getWindowHandle()->HWND;
        virtual auto getWindowHandle()const->const HWND;
        //親ウィンドウの取り出し
        virtual auto getParent()->Window *;
        virtual auto getParent()const->const Window *;
        //生成
        virtual auto create(const tstring &_className, HINSTANCE _instanceHandle, HWND _parentWindowHandle, HMENU _menuHandle, const tstring &_text, DWORD _exStyle, DWORD _style, RECT _rect)->void;
        //破棄
        virtual auto destroy()->void;
        //ウィンドウイベント振り分け機
        virtual auto windowProcedure(UINT message, WPARAM wParam, LPARAM lParam)->LRESULT;
    protected:
        //Window作成時メッセージ処理
        virtual auto onCreate()->LRESULT;
        //Window破棄時メッセージ処理
        virtual auto onDestroy()->LRESULT;
        //移動時処理
        virtual auto onMove(WPARAM wParam, LPARAM lParam)->LRESULT;
        //サイズ変更時処理
        virtual auto onSize(WPARAM wParam, LPARAM lParam)->LRESULT;
        //アクティブ化の処理
        virtual auto onActivate(WPARAM wParam, LPARAM lParam)->LRESULT;
        //マウス移動時処理
        virtual auto onMouseMove(WPARAM wParam, LPARAM lParam)->LRESULT;
        //マウス左ボタン押下時処理
        virtual auto onLButtonDown(WPARAM wParam, LPARAM lParam)->LRESULT;
        //マウス左ボタン離上時処理
        virtual auto onLButtonUP(WPARAM wParam, LPARAM lParam)->LRESULT;
        //マウス左ボタンダブルクリック時処理
        virtual auto onLButtonDblClk(WPARAM wParam, LPARAM lParam)->LRESULT;
        //マウス左ボタン押下時処理
        virtual auto onRButtonDown(WPARAM wParam, LPARAM lParam)->LRESULT;
        //マウス左ボタン離上時処理
        virtual auto onRButtonUP(WPARAM wParam, LPARAM lParam)->LRESULT;
        //マウス左ボタンダブルクリック時処理
        virtual auto onRButtonDblClk(WPARAM wParam, LPARAM lParam)->LRESULT;
        //マウス中ボタン押下時処理
        virtual auto onMButtonDown(WPARAM wParam, LPARAM lParam)->LRESULT;
        //マウス中ボタン離上時処理
        virtual auto onMButtonUP(WPARAM wParam, LPARAM lParam)->LRESULT;
        //マウス中ボタンダブルクリック時処理
        virtual auto onMButtonDblClk(WPARAM wParam, LPARAM lParam)->LRESULT;
        //マウスホイール処理
        virtual auto onMouseWheel(WPARAM wParam, LPARAM lParam)->LRESULT;
        //描画処理
        virtual auto onPaint(WPARAM wParam, LPARAM lParam)->LRESULT;
        //Windowコマンド処理
        virtual auto onCommand(WPARAM wParam, LPARAM lParam)->LRESULT;
        //キーボード処理
        virtual auto onKeyDown(WPARAM wParam, LPARAM lParam)->LRESULT;
        //Window 通知処理
        virtual auto onNotify(WPARAM wParam, LPARAM lParam)->LRESULT;
        //ドロップ処理
        virtual auto onDropFiles(WPARAM wParam, LPARAM lParam)->LRESULT;
        //タイマー処理
        virtual auto onTimer(WPARAM wParam, LPARAM lParam)->LRESULT;
    public:
        //Visible設定
        virtual auto setVisible(bool newVisible)->void;
        //Enable設定
        virtual auto setEnable(bool newEnable)->void;
        //Text設定
        virtual auto setText(const tstring &newText)->void;
        //Position設定
        virtual auto setPosition(POINT newPosition)->void;
        //Visible取得
        virtual auto getVisible()const->bool;
        //Enable取得
        virtual auto getEnable()const->bool;
        //Text取得
        virtual auto getText()const->tstring;
        //Position取得
        virtual auto getPosition()const->POINT;
    protected:
        tstring className;                  //ウィンドウクラスの名前取得
        HINSTANCE instanceHandle;           //ウィンドウクラスのHINSTANCE取得
        HWND windowHandle;                  //Windowハンドル
        Window *parent;                     //親Window
    };

    //タイマーウィンドウ
    //タイマー処理がオーバーライドされてる
    class TimerWindow : public Window
    {
    public:
        TimerWindow(const TimerWindow &) = delete;
        TimerWindow &operator=(const TimerWindow &) = delete;
        TimerWindow(float _fps);
        ~TimerWindow();
    protected:
        virtual auto onCreate()->LRESULT override;
        virtual auto onTimer(WPARAM wParam, LPARAM lParam)->LRESULT override;
    public:
        void (*onTick)(void);
    protected:
        float fps;
    };

    //メインウィンドウ
    //GUIを持つことができる
    class MainWindow : public TimerWindow
    {
    protected:
        MainWindow(const MainWindow &) = delete;
        MainWindow &operator=(const MainWindow &) = delete;
        MainWindow(float _fps);
        ~MainWindow();
    public:
        virtual auto create(WindowClass *_windowClass, const tstring &_text, DWORD _exStyle, DWORD _style, RECT _rect)->void;
    protected:
        virtual auto onDestroy()->LRESULT override;
        virtual auto onTimer(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onPaint(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onCommand(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onPaintMain(HDC hdc)->void = 0;
    };

    //グラフィカルなユーザーインターフェース
    class GUI : public Window
    {
    protected:
        GUI(const GUI &) = delete;
        GUI &operator=(const GUI &) = delete;
        GUI();
        ~GUI();
    public:
        virtual auto create(Window *_parent, const tstring &_className, const tstring &_text, DWORD _exStyle, DWORD _style, RECT _rect)->void;
    protected:
        virtual auto onCommand(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onGUICommand(WORD code, WORD id)->LRESULT = 0;
    };

    //ボタン
    //自分が押された時の処理が書かれてる
    class Button : public GUI
    {
    public:
        Button(const Button &) = delete;
        Button &operator=(const Button &) = delete;
        Button(Window *_parent, RECT _rect, const tstring &caption);
        ~Button();
    protected:
        virtual auto onGUICommand(WORD code, WORD id)->LRESULT override;
    public:
        void (*onClick)(void);
        void (*onDoubleClick)(void);
        void (*onPush)(void);
        void (*onUnpush)(void);
        void (*onSetFocus)(void);
        void (*onKillFocus)(void);
    };
}
