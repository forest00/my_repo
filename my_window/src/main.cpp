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
protected://アクション
    static auto action1(myWindow::Button *button)->void;
    static auto action2(myWindow::Button *button)->void;
    static auto action3(myWindow::Button *button)->void;
    static auto action4(myWindow::Button *button)->void;
    static auto action5(myWindow::Button *button)->void;
    static auto action6(myWindow::Button *button)->void;
    static auto action7(myWindow::Button *button)->void;
protected://メンバー変数
    myWindow::Button button;
    myWindow::Button button2;
public:
    int u;
};

MyTestWindow::MyTestWindow()
    : WindowWithControls()
    , button()
    , button2()
    , u()
{

}
MyTestWindow::~MyTestWindow()
{

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
    button.create(TEXT("保存"), thisRect.right / 2, thisRect.bottom / 2, 100, 64, this);
    button.onClick = MyTestWindow::action1;
    button2.create(TEXT("読み込み"), thisRect.right / 2 + 100, thisRect.bottom / 2 + 64, 100, 64, this);
    button2.onClick = MyTestWindow::action2;
}
void MyTestWindow::action1(myWindow::Button *button)
{
    auto parent = button->getParent();
    auto trueParent = dynamic_cast<MyTestWindow *>(parent);
    if (trueParent == nullptr)
    {
        return;
    }
    trueParent->u = 1;
}
void MyTestWindow::action2(myWindow::Button *button)
{
    auto parent = button->getParent();
    auto trueParent = dynamic_cast<MyTestWindow *>(parent);
    if (trueParent == nullptr)
    {
        return;
    }
    trueParent->u = 2;
}
void MyTestWindow::action3(myWindow::Button *button)
{
    auto parent = button->getParent();
    auto trueParent = dynamic_cast<MyTestWindow *>(parent);
    if (trueParent == nullptr)
    {
        return;
    }
    trueParent->u = 3;
}
void MyTestWindow::action4(myWindow::Button *button)
{
    auto parent = button->getParent();
    auto trueParent = dynamic_cast<MyTestWindow *>(parent);
    if (trueParent == nullptr)
    {
        return;
    }
    trueParent->u = 4;
}
void MyTestWindow::action5(myWindow::Button *button)
{
    auto parent = button->getParent();
    auto trueParent = dynamic_cast<MyTestWindow *>(parent);
    if (trueParent == nullptr)
    {
        return;
    }
    trueParent->u = 5;
}
void MyTestWindow::action6(myWindow::Button *button)
{
    auto parent = button->getParent();
    auto trueParent = dynamic_cast<MyTestWindow *>(parent);
    if (trueParent == nullptr)
    {
        return;
    }
    trueParent->u = 6;
}
void MyTestWindow::action7(myWindow::Button *button)
{
    auto parent = button->getParent();
    auto trueParent = dynamic_cast<MyTestWindow *>(parent);
    if (trueParent == nullptr)
    {
        return;
    }
    trueParent->u = 7;
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
