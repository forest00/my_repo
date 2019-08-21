#pragma once
#include "my_window.h"

class MyTestMainWindow : public myWindow::MainWindow
{
public:
    MyTestMainWindow(const MyTestMainWindow &) = delete;
    MyTestMainWindow &operator=(const MyTestMainWindow &) = delete;
    MyTestMainWindow(float _fps);
    ~MyTestMainWindow();
protected:
    virtual auto onPaintMain(HDC hdc)->void override;
};
