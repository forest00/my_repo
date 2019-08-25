//file:my_window.h
//date:2019/08/25
//auther:forest00
//ウィンドウの扱いをするクラス群です
//ウィンドウクラスはその名の通り、ウィンドウの分類を表すものだと理解

#pragma once
#include "tstring.h"
#include <Windows.h>

namespace myWindow
{
    //共通ウィンドウクラス
    class CommonWindowClass
    {
    public://コンストラクタとデストラクタ
        CommonWindowClass(const CommonWindowClass &) = delete;
        CommonWindowClass &operator=(const CommonWindowClass &) = delete;
        CommonWindowClass();
        virtual ~CommonWindowClass();
    public://超基本
        //登録
        auto registerClass(const tstring &_name, HINSTANCE _instanceHandle)->void;
        //登録解除(デストラクタでも呼ばれるので呼び忘れることはない。多分)
        auto unregisterClass()->void;
    public://基本操作
        //名前取得
        virtual auto getName()const->const tstring &;
        //HINSTANCE取得
        virtual auto getInstanceHandle()const->const HINSTANCE;
    public://その他の静的関数
        //ウィンドウ生成関数(CreateWindowEx)のラッパー関数です
        //これを使う利点は、第二引数と第三引数がtstringになっていることです(あとマクロじゃない。やったね！)
        static auto createWindow(
            DWORD extendedWindowStyle,
            const tstring &className,
            const tstring &windowName,
            DWORD windowStyle,
            int x,
            int y,
            int width,
            int height,
            HWND parentWindowHandle,
            HMENU menuHandle,
            HINSTANCE instanceHandle,
            void *param
        )->HWND;
        //ウィンドウプロシージャーです
        static auto CALLBACK windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)->LRESULT;
    protected://メンバー変数
        tstring name;
        HINSTANCE instanceHandle;
    };

    //ウィンドウ基底クラス
    class Window
    {
    public://コンストラクタとデストラクタ
        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;
        Window();
        virtual ~Window() = 0;
    public://超基本
        //ウィンドウ破棄
        virtual auto destroy()->void;
        //ウィンドウクラス名取得
        virtual auto getClassName()const->const tstring &;
        //ウィンドウクラスHINSTANCE取得
        virtual auto getInstanceHandle()const->const HINSTANCE;
        //ウィンドウハンドル取得
        virtual auto getWindowHandle()->HWND;
        //ウィンドウハンドル取得(const)
        virtual auto getWindowHandle()const->const HWND;
        //親ウィンドウ取得
        virtual auto getParent()->Window *;
        //親ウィンドウ取得(const)
        virtual auto getParent()const->const Window *;
    public://基本操作
        //Visible取得
        virtual auto getVisible()const->bool;
        //Enable取得
        virtual auto getEnable()const->bool;
        //Text取得
        virtual auto getText()const->tstring;
        //Position取得
        virtual auto getPosition()const->POINT;
        //Visible設定
        virtual auto setVisible(bool newVisible)->void;
        //Enable設定
        virtual auto setEnable(bool newEnable)->void;
        //Text設定
        virtual auto setText(const tstring &newText)->void;
        //Position設定
        virtual auto setPosition(POINT newPosition)->void;
    public://イベント処理
        //ウィンドウイベント振り分け機
        virtual auto windowProcedure(UINT message, WPARAM wParam, LPARAM lParam)->LRESULT;
    protected://オーバーライドする
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
        //Window通知処理
        virtual auto onNotify(WPARAM wParam, LPARAM lParam)->LRESULT;
        //ファイルドロップ処理
        virtual auto onDropFiles(WPARAM wParam, LPARAM lParam)->LRESULT;
        //タイマー処理
        virtual auto onTimer(WPARAM wParam, LPARAM lParam)->LRESULT;
    protected://メンバー変数
        tstring className;                  //ウィンドウクラス名
        HINSTANCE instanceHandle;           //ウィンドウクラスHINSTANCE
        Window *parent;                     //親Window
        HWND windowHandle;                  //Windowハンドル
    };

    //何かしらのコントロールを所有するウィンドウ
    class WindowWithControls : public Window
    {
    public://コンストラクタとデストラクタ
        WindowWithControls(const WindowWithControls &) = delete;
        WindowWithControls &operator=(const WindowWithControls &) = delete;
        WindowWithControls();
        ~WindowWithControls();
    protected://オーバーライドした
        virtual auto onCommand(WPARAM wParam, LPARAM lParam)->LRESULT override;
    };

    //コントロール基底クラス
    class Control : public Window
    {
    public://コンストラクタとデストラクタ
        Control(const Control &) = delete;
        Control &operator=(const Control &) = delete;
        Control();
        ~Control();
    public://オーバーライドする
        virtual auto onControllCommand(WORD code, WORD id)->LRESULT = 0;
    };

    //ボタン
    class Button : public Control
    {
    public://コンストラクタとデストラクタ
        Button(const Button &) = delete;
        Button &operator=(const Button &) = delete;
        Button();
        ~Button();
    public://超基本
        //ウィンドウ生成
        virtual auto create(const tstring &_caption, int _x, int _y, int _width, int _height, Window *_parent)->void;
    protected://オーバーライドした
        virtual auto onControllCommand(WORD code, WORD id)->LRESULT override;
    public://メンバー変数
        void (*onClick)(Button *button);
    };
}
