#include "my_test_main_window.h"
#include <ctime>

MyTestMainWindow::MyTestMainWindow(float _fps)
    : MainWindow(_fps)
{

}
MyTestMainWindow::~MyTestMainWindow()
{

}
auto MyTestMainWindow::onPaintMain(HDC hdc)->void
{
    auto c = clock() / 20;
    Rectangle(hdc, 100 + c, 100, 500, 500);
}
