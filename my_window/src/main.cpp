#include "my_window.h"

//テスト用ウィンドウクラス
class MyTestWindow : public myWindow::WindowWithControls
{
public://コンストラクタとデストラクタ
    MyTestWindow(const MyTestWindow &) = delete;
    MyTestWindow &operator=(const MyTestWindow &) = delete;
    MyTestWindow() = default;
    virtual ~MyTestWindow() = default;
public://超基本
    //ウィンドウ生成
    virtual auto create(const tstring &_windowClassName, HINSTANCE _instanceHandle, const tstring &_name, int _x, int _y, int _width, int _height)->void;
protected://オーバーライドした
    virtual auto onDestroy()->LRESULT override;
    virtual auto onPaint(WPARAM wParam, LPARAM lParam)->LRESULT override;
    virtual auto onCommandMain(WORD code, WORD id, myWindow::Control *controllWindow)->LRESULT override;
protected://メンバー変数
    myWindow::Label label1;
    myWindow::Label label2;
    myWindow::Label label3;
    myWindow::Edit edit1;
    myWindow::CheckBox checkBox1;
    myWindow::CheckBox3State checkBox3State1;
    myWindow::GroupBox groupBox1;
    myWindow::RadioButton groupRadioButton1;
    myWindow::RadioButton groupRadioButton2;
    myWindow::RadioButton radioButton1;
    myWindow::RadioButton radioButton2;
    myWindow::Button button1;
    myWindow::Button button2;
    myWindow::ListBox listBox1;
    myWindow::ComboBox comboBox1;
    myWindow::ComboBox comboBox2;
    myWindow::TrackBar trackBar1;
    myWindow::Numeric numeric1;
    myWindow::Numeric numeric2;
    myWindow::Numeric numeric3;
};

auto MyTestWindow::create(const tstring &_windowClassName, HINSTANCE _instanceHandle, const tstring &_name, int _x, int _y, int _width, int _height)->void
{
    auto exStyle = WS_EX_COMPOSITED;
    auto style = WS_OVERLAPPEDWINDOW;
    this->className = _windowClassName;
    this->instanceHandle = _instanceHandle;
    this->windowHandle = myWindow::Wrap::createWindow(
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
    label1.create(TEXT("label1"), 0, 0, 500, 24, this, 0);
    label2.create(TEXT("label2"), 0, 24, 500, 24, this, 1);
    label3.create(TEXT("label3"), 0, 48, 500, 24, this, 2);
    edit1.create(TEXT("edit1"), 0, 100, 500, 24, this, 3);
    checkBox1.create(TEXT("checkBox1"), 0, 200, 500, 24, this, 4);
    checkBox3State1.create(TEXT("checkBox3State1"), 0, 300, 500, 24, this, 5);
    groupBox1.create(TEXT("groupBox1"), 0, 400, 500, 72 + 8, this, 6);
    groupRadioButton1.create(TEXT("groupRadioButton1"), 10, 24, 480, 24, &groupBox1, 7);
    groupRadioButton2.create(TEXT("groupRadioButton2"), 10, 48, 480, 24, &groupBox1, 8);
    radioButton1.create(TEXT("radioButton1"), 0, 550, 500, 24, this, 9);
    radioButton2.create(TEXT("radioButton2"), 0, 550 + 24, 500, 24, this, 10);
    button1.create(TEXT("button1"), 0, 600, 100, 24, this, 11);
    button2.create(TEXT("button2"), 0, 624, 100, 24, this, 12);
    listBox1.create(TEXT("listBox1"), 500, 0, 300, 300, this, 13);
    comboBox1.create(TEXT("comboBox1"), 500, 300, 300, 300, this, 14);
    comboBox2.create(TEXT("comboBox2"), 500, 350, 300, 300, this, 15);
    trackBar1.create(TEXT("trackBar1"), 500, 400, 300, 64, this, 16);
    numeric1.create(TEXT("0.0"), 500, 500, 100, 24, this, 17);
    numeric2.create(TEXT("10.0"), 500, 532, 100, 24, this, 18);
    numeric3.create(TEXT("100.0"), 500, 564, 100, 32, this, 19);
    listBox1.lbAddItem(TEXT("listItemA"));
    listBox1.lbAddItem(TEXT("listItemB"));
    listBox1.lbAddItem(TEXT("listItemC"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    listBox1.lbAddItem(TEXT("listItem"));
    comboBox1.cbAddItem(TEXT("saaaAAA"));
    comboBox1.cbAddItem(TEXT("bbbBBB0"));
    comboBox1.cbAddItem(TEXT("bbbBBB1"));
    comboBox1.cbAddItem(TEXT("bbbBBB2"));
    comboBox1.cbAddItem(TEXT("bbbBBB3"));
    comboBox1.cbAddItem(TEXT("bbbBBB4"));
    comboBox1.cbAddItem(TEXT("bbbBBB5"));
    comboBox1.cbAddItem(TEXT("bbbBBB6"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox1.cbAddItem(TEXT("cccCCC"));
    comboBox2.cbAddItem(TEXT("saaaAAA"));
    comboBox2.cbAddItem(TEXT("bbbBBB0"));
    comboBox2.cbAddItem(TEXT("bbbBBB1"));
    comboBox2.cbAddItem(TEXT("bbbBBB2"));
    comboBox2.cbAddItem(TEXT("bbbBBB3"));
    comboBox2.cbAddItem(TEXT("bbbBBB4"));
    comboBox2.cbAddItem(TEXT("bbbBBB5"));
    comboBox2.cbAddItem(TEXT("bbbBBB6"));
    comboBox2.cbAddItem(TEXT("cccCCC"));
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
    //HDCここから

    //HDCここまで
    EndPaint(getWindowHandle(), &ps);
    return 0;
}
auto MyTestWindow::onCommandMain(WORD code, WORD id, myWindow::Control *controllWindow)->LRESULT
{
    int x = code;
    int u = id;
    auto f = to_tstring('\0');
    if (controllWindow != nullptr)
    {
        f = controllWindow->getText();
    }
    auto s = TEXT("code : ") + to_tstring(x);
    auto m = TEXT("id   : ") + to_tstring(u);
    label1.setText(s);
    label2.setText(m);
    label3.setText(f);
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
    //コモンコントロールの初期化
    InitCommonControls();
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
