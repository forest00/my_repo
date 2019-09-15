//file:my_window.h
//date:2019/08/25
//auther:forest00
//ウィンドウの扱いをするクラス群です
//ウィンドウクラスはその名の通り、ウィンドウの分類を表すものだと理解
//topic:2019/09/01いろいろ追加。クッソ大変だわこれ。。。

#pragma once
#include "tstring.h"
#include <Windows.h>
#include    <commctrl.h>

#pragma comment(lib, "ComCtl32.lib")

namespace myWindow
{
    //クラスリスト
    class Wrap;
    class CommonWindowClass;
    class Window;
    class WindowWithControls;
    class Control;
    class Label;
    class Edit;
    class Button;
    class CheckBox;
    class CheckBox3State;
    class GroupBox;
    class RadioButton;
    class ListBox;
    class ComboBox;
    //class ProgressBar//todo;
    class TrackBar;
    class Numeric;

    //Windowsの関数ラッパークラス
    class Wrap
    {
    public:
        //ウィンドウ生成関数(CreateWindowEx)のラッパー関数です
        //第二引数と第三引数がtstringになっています
        static auto createWindow(
            DWORD extendedWindowStyle,
            const tstring &className,
            const tstring &windowText,
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
        //ShowCursorのラッパー関数です
        static auto showCursor(bool show);
        //GetOpenFileNameのラッパーです
        //指定した拡張子を持つファイルを探してくれます
        //フィルターの形式
        //"説明文\0*.拡張子\0"
        //"説明文\0*.拡張子\0"
        //"説明文\0*.拡張子\0\0"
        //見つかった場合:ファイル名,それ以外:空文字列
        static auto getOpenFileName(const Window *owner, const TCHAR *filter)->tstring;
        //GetSaveFileNameのラッパーです
        //指定した拡張子を持つファイルを探してくれます
        //フィルターの形式
        //"説明文\0*.拡張子\0"
        //"説明文\0*.拡張子\0"
        //"説明文\0*.拡張子\0\0"
        //見つかった場合:ファイル名,それ以外:空文字列
        static auto getSaveFileName(const Window *owner, const TCHAR *filter)->tstring;
    };

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
        //ウィンドウ生成
        virtual auto create(
            DWORD _extendedWindowStyle,
            const tstring &_className,
            const tstring &_windowText,
            DWORD _windowStyle,
            int _x,
            int _y,
            int _width,
            int _height,
            Window *_parent,
            HMENU _menuHandle,
            HINSTANCE _instanceHandle,
            void *_param
        )->void;
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
        //Style取得
        virtual auto getStyle()->DWORD;
        //Visible取得
        virtual auto getVisible()const->bool;
        //Enable取得
        virtual auto getEnable()const->bool;
        //Text取得
        virtual auto getText()const->tstring;
        //Pos取得
        virtual auto getPos()const->POINT;
        //Size取得
        virtual auto getSize()const->SIZE;
        //Rect取得
        virtual auto getRect()const->RECT;
        //Style反映
        virtual auto reflectStyle()->void;
        //メッセージを送る
        virtual auto sendMessage(UINT message, WPARAM wParam, LPARAM lParam)->LRESULT;
        //Style設定
        virtual auto setStyle(DWORD newStyle, bool reflectImmediately)->void;
        //Visible設定
        virtual auto setVisible(bool newVisible)->void;
        //Enable設定
        virtual auto setEnable(bool newEnable)->void;
        //Text設定(SetWindowText)
        virtual auto setText(const tstring &newText)->void;
        //Pos設定(SetWindowPos)
        virtual auto setPos(POINT newPos)->void;
        //Size設定(SetWindowPos)
        virtual auto setSize(SIZE newSize)->void;
        //Rect設定(SetWindowPos)
        virtual auto setRect(RECT newRect)->void;
        //InvalidateRect(windowHandle, nullptr, erase)を呼び出す
        virtual auto redraw(bool erase)->void;
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
        //マウス退却時処理(このメッセージを受け取るには特別な処理が必要)
        virtual auto onMouseLeave(WPARAM wParam, LPARAM lParam)->LRESULT;
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
        WindowWithControls() = default;
        virtual ~WindowWithControls() = 0;
    protected://オーバーライドした
        virtual auto onCommand(WPARAM wParam, LPARAM lParam)->LRESULT override;
    protected://オーバーライドする
        virtual auto onCommandMain(WORD code, WORD id, Control *controllWindow)->LRESULT = 0;
    };

    //コントロール基底クラス
    class Control : public Window
    {
    public://コンストラクタとデストラクタ
        Control(const Control &) = delete;
        Control &operator=(const Control &) = delete;
        Control() = default;
        ~Control() = default;
    protected://オーバーライドする
        //ウィンドウ生成
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void = 0;
    };

    //スタティック(ラベル)
    class Label : public Control
    {
    public://コンストラクタとデストラクタ
        Label(const Label &) = delete;
        Label &operator=(const Label &) = delete;
        Label() = default;
        virtual ~Label() = default;
    public://超基本
        //ウィンドウ生成
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    };

    //エディット
    class Edit : public Control
    {
    public://コンストラクタとデストラクタ
        Edit(const Edit &) = delete;
        Edit &operator=(const Edit &) = delete;
        Edit() = default;
        virtual ~Edit() = default;
    public://超基本
        //ウィンドウ生成
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    };

    //ボタン
    class Button : public Control
    {
    public://コンストラクタとデストラクタ
        Button(const Button &) = delete;
        Button &operator=(const Button &) = delete;
        Button() = default;
        virtual ~Button() = default;
    public://超基本
        //ウィンドウ生成
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    };

    //チェックボックス
    class CheckBox : public Control
    {
    public://コンストラクタとデストラクタ
        CheckBox(const CheckBox &) = delete;
        CheckBox &operator=(const CheckBox &) = delete;
        CheckBox() = default;
        virtual ~CheckBox() = default;
    public://超基本
        //ウィンドウ生成
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    public://基本操作
        auto bGetState()->bool;
    };

    //3状態チェックボックス
    class CheckBox3State : public Control
    {
    public://コンストラクタとデストラクタ
        CheckBox3State(const CheckBox3State &) = delete;
        CheckBox3State &operator=(const CheckBox3State &) = delete;
        CheckBox3State() = default;
        virtual ~CheckBox3State() = default;
    public://超基本
        //ウィンドウ生成
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    public://基本操作
        auto bGetState()->int;
    };

    //グループボックス
    class GroupBox : public Control
    {
    public://コンストラクタとデストラクタ
        GroupBox(const GroupBox &) = delete;
        GroupBox &operator=(const GroupBox &) = delete;
        GroupBox() = default;
        virtual ~GroupBox() = default;
    public://超基本
        //ウィンドウ生成
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    };

    //ラジオボタン
    class RadioButton : public Control
    {
    public://コンストラクタとデストラクタ
        RadioButton(const RadioButton &) = delete;
        RadioButton &operator=(const RadioButton &) = delete;
        RadioButton() = default;
        virtual ~RadioButton() = default;
    public://超基本
        //ウィンドウ生成
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    };

    //リストボックス
    class ListBox : public Control
    {
    public://コンストラクタとデストラクタ
        ListBox(const ListBox &) = delete;
        ListBox &operator=(const ListBox &) = delete;
        ListBox() = default;
        virtual ~ListBox() = default;
    public://超基本
        //ウィンドウ生成
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    public://基本操作
        //アイテム追加
        virtual auto lbAddItem(const tstring &newItem)->void;
        //アイテム変更
        virtual auto lbChangeItem(int itemIndex, const tstring &newItem)->void;
        //アイテム削除
        virtual auto lbDeleteItem(int itemIndex)->void;
        //全アイテム削除
        virtual auto lbDeleteItems()->void;
        //アイテム取得
        virtual auto lbGetItem(int itemIndex)->tstring;
        //アイテム数取得
        virtual auto lbGetItemNum()->int;
        //カーソルの位置を取得
        virtual auto lbGetSelectedIndex()->int;
        //アイテム挿入
        virtual auto lbInsertItem(int itemIndex, const tstring &newItem)->void;
        //カーソルの位置を設定
        virtual auto lbSetSelectedIndex(int newSelectedIndex)->void;
    };

    //コンボボックス
    class ComboBox : public Control
    {
    public://コンストラクタとデストラクタ
        ComboBox(const ComboBox &) = delete;
        ComboBox &operator=(const ComboBox &) = delete;
        ComboBox() = default;
        virtual ~ComboBox() = default;
    public://超基本
        //ウィンドウ生成
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    public://基本操作
        //アイテム追加
        virtual auto cbAddItem(const tstring &newItem)->void;
        //アイテム変更
        virtual auto cbChangeItem(int itemIndex, const tstring &newItem)->void;
        //アイテム削除
        virtual auto cbDeleteItem(int itemIndex)->void;
        //全アイテム削除
        virtual auto cbDeleteItems()->void;
        //アイテム取得
        virtual auto cbGetItem(int itemIndex)->tstring;
        //アイテム数取得
        virtual auto cbGetItemNum()->int;
        //カーソルの位置を取得
        virtual auto cbGetSelectedIndex()->int;
        //アイテム挿入
        virtual auto cbInsertItem(int itemIndex, const tstring &newItem)->void;
        //カーソルの位置を設定
        virtual auto cbSetSelectedIndex(int newSelectedIndex)->void;
    };

    //トラックバー(スライダー)
    class TrackBar : public Control
    {
    public://コンストラクタとデストラクタ
        TrackBar(const TrackBar &) = delete;
        TrackBar &operator=(const TrackBar &) = delete;
        TrackBar() = default;
        virtual ~TrackBar() = default;
    public://超基本
        //ウィンドウ生成
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    };

    //数値
    class Numeric : public Control
    {
    public://定数
        static constexpr WORD Message_GotFocus = 0;
        static constexpr WORD Message_LostFocus = 1;
        static constexpr WORD Message_ValueChangeStarted = 2;
        static constexpr WORD Message_ValueChangeIsOver = 3;
        static constexpr WORD Message_ValueWasReset = 4;
        static constexpr WORD Message_ChangingValue = 5;
    public://コンストラクタとデストラクタ
        Numeric(const Numeric &) = delete;
        Numeric &operator=(const Numeric &) = delete;
        Numeric();
        virtual ~Numeric() = default;
    public://超基本
        //ウィンドウ生成
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    public://基本操作
        //基底値の取得
        virtual auto nGetDefaultValue()->float;
        //数値の取得
        virtual auto nGetValue()->float;
        //基底値の設定
        virtual auto nSetDefaultValue(float newDefaultValue)->void;
        //数値の設定
        virtual auto nSetValue(float newValue)->void;
    protected://オーバーライドした
        virtual auto onCreate()->LRESULT override;
        virtual auto onMouseMove(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onMouseLeave(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onLButtonDown(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onLButtonUP(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onLButtonDblClk(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onPaint(WPARAM wParam, LPARAM lParam)->LRESULT override;
    protected://メンバー変数
        bool mouseOn;//マウスが乗っかっているか
        bool changing;//値の変更中
        float defaultValue;//規定値
        WORD mouseLastClickedX;//マウスをクリックした位置(X)
        WORD mouseLastClickedY;//マウスをクリックした位置(Y)
    };
}
