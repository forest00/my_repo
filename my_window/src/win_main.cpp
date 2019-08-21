#include "my_test_main_window.h"


void ss(void)
{
    int u = 0;
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
    //ウィンドウクラス登録
    auto windowClass = new myWindow::WindowClass(TEXT("TestWindowClass"), instanceHandle);
    //メインウィンドウ作成
    auto mainWindowRect = RECT{CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT};
    auto mainWindow = new MyTestMainWindow(60.0f);
    mainWindow->create(windowClass, TEXT("Main window"), WS_EX_COMPOSITED, WS_OVERLAPPEDWINDOW, mainWindowRect);
    auto button1 = new myWindow::Button(mainWindow, RECT{100,100,110,110}, TEXT("BUTTON!"));
    button1->onPush = ss;
    auto button2 = new myWindow::Button(mainWindow, RECT{200,200,110,110}, TEXT("BUTTON2!"));
    button2->onPush = ss;
    //メッセージループ
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    //ウィンドウクラス登録解除
    delete windowClass;
    windowClass = nullptr;
    //WinMainを抜ける
    return msg.wParam;
}
