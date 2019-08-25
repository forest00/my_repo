#include "my_window.h"

//テスト用ウィンドウクラス
class MyTestWindow : public myWindow::WindowWithControls
{
public://コンストラクタとデストラクタ
    MyTestWindow(const MyTestWindow &) = delete;
    MyTestWindow &operator=(const MyTestWindow &) = delete;
    MyTestWindow();
    virtual ~MyTestWindow();
public://超基本
    //ウィンドウ生成
    virtual auto create(const tstring &_windowClassName, HINSTANCE _instanceHandle, const tstring &_name, int _x, int _y, int _width, int _height)->void;
protected://オーバーライドした
    virtual auto onCreate()->LRESULT override;
    virtual auto onDestroy()->LRESULT override;
    virtual auto onPaint(WPARAM wParam, LPARAM lParam)->LRESULT override;
    virtual auto onTimer(WPARAM wParam, LPARAM lParam)->LRESULT override;
protected://メンバー変数
    myWindow::Button *saveButton;
    myWindow::Button *loadButton;
public:
    int u;
};

//テスト用SaveButton
class SaveButton : public myWindow::Button
{
public://コンストラクタとデストラクタ
    SaveButton(const SaveButton &) = delete;
    SaveButton &operator=(const SaveButton &) = delete;
    SaveButton() = default;
    virtual ~SaveButton() = default;
protected://オーバーライドした
    virtual auto onClick(WORD id)->LRESULT override;
};
auto SaveButton::onClick(WORD)->LRESULT
{
    auto trueParent = reinterpret_cast<MyTestWindow *>(getParent());
    trueParent->u += 10;
    return 0;
}

//LoadButton for Test
class LoadButton : public myWindow::Button
{
public://コンストラクタとデストラクタ
    LoadButton(const LoadButton &) = delete;
    LoadButton &operator=(const LoadButton &) = delete;
    LoadButton() = default;
    virtual ~LoadButton() = default;
protected://オーバーライドした
    virtual auto onClick(WORD id)->LRESULT override;
};
auto LoadButton::onClick(WORD)->LRESULT
{
    auto trueParent = reinterpret_cast<MyTestWindow *>(getParent());
    trueParent->u += 1000;
    return 0;
}

MyTestWindow::MyTestWindow()
    : WindowWithControls()
    , saveButton()
    , loadButton()
    , u()
{
    saveButton = new SaveButton;
    loadButton = new LoadButton;
}
MyTestWindow::~MyTestWindow()
{
    delete saveButton;
    delete loadButton;
}
auto MyTestWindow::create(const tstring &_windowClassName, HINSTANCE _instanceHandle, const tstring &_name, int _x, int _y, int _width, int _height)->void
{
    auto exStyle = WS_EX_COMPOSITED;
    auto style = WS_OVERLAPPEDWINDOW;
    this->className = _windowClassName;
    this->instanceHandle = _instanceHandle;
    this->windowHandle = myWindow::CommonWindowClass::createWindow(
        exStyle,
        this->className,
        _name,
        style,
        _x,
        _y,
        _width,
        _height,
        nullptr,
        nullptr,
        this->instanceHandle,
        nullptr
    );
    SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    onCreate();
    setVisible(true);
    RECT thisRect;
    GetWindowRect(getWindowHandle(), &thisRect);
    saveButton->create(TEXT("保存"), thisRect.right / 2, thisRect.bottom / 2, 100, 64, this);
    loadButton->create(TEXT("読み込み"), thisRect.right / 2 + 100, thisRect.bottom / 2 + 64, 100, 64, this);
}
auto MyTestWindow::onCreate()->LRESULT
{
    SetTimer(getWindowHandle(), 0, 1000 / 60, nullptr);
    return 0;
}
auto MyTestWindow::onDestroy()->LRESULT
{
    PostQuitMessage(0);
    return 0;
}
auto MyTestWindow::onPaint(WPARAM, LPARAM)->LRESULT
{
    HDC hdc;
    PAINTSTRUCT ps;
    hdc = BeginPaint(getWindowHandle(), &ps);
    tstring ss = to_tstring(u);
    TextOut(hdc, 0, 0, ss.c_str(), ss.length());
    EndPaint(getWindowHandle(), &ps);
    return 0;
}
auto MyTestWindow::onTimer(WPARAM, LPARAM)->LRESULT
{
    InvalidateRect(getWindowHandle(), nullptr, true);
    return 0;
}





//エントリーポイント
int WINAPI WinMain(
    _In_ HINSTANCE instanceHandle,
    _In_opt_ HINSTANCE prevInstanceHandle,
    _In_ PSTR cmdLine,
    _In_ int cmdShow
)
{
    UNREFERENCED_PARAMETER(prevInstanceHandle);
    UNREFERENCED_PARAMETER(cmdLine);
    UNREFERENCED_PARAMETER(cmdShow);
    //ウィンドウクラス登録
    myWindow::CommonWindowClass commonWindowClass;
    commonWindowClass.registerClass(TEXT("CommonWindowClass"), instanceHandle);
    //ウィンドウ生成
    MyTestWindow window;
    window.create(commonWindowClass.getName(), instanceHandle, TEXT("MyTestWindow"), 0, 0, 1280, 720);
    //メッセージループ
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    //ウィンドウクラス登録解除
    commonWindowClass.unregisterClass();
    //WinMainを抜ける
    return msg.wParam;
}
