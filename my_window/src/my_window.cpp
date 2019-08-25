#include "my_window.h"

namespace myWindow
{
    //---------------------------------------------------------------------------------------------------------
    CommonWindowClass::CommonWindowClass()
        : name()
        , instanceHandle(nullptr)
    {

    }
    CommonWindowClass::~CommonWindowClass()
    {
        unregisterClass();
    }
    auto CommonWindowClass::registerClass(const tstring &_name, HINSTANCE _instanceHandle)->void
    {
        name = _name;
        instanceHandle = _instanceHandle;
        WNDCLASS wndclass;
        wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        wndclass.lpfnWndProc = CommonWindowClass::windowProcedure;
        wndclass.cbClsExtra = 0;
        wndclass.cbWndExtra = 0;
        wndclass.hInstance = instanceHandle;
        wndclass.hIcon = nullptr;
        wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wndclass.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
        wndclass.lpszMenuName = nullptr;
        wndclass.lpszClassName = name.c_str();
        RegisterClass(&wndclass);
    }
    auto CommonWindowClass::unregisterClass()->void
    {
        UnregisterClass(getName().c_str(), getInstanceHandle());
    }
    auto CommonWindowClass::getName()const->const tstring &
    {
        return name;
    }
    auto CommonWindowClass::getInstanceHandle()const->const HINSTANCE
    {
        return instanceHandle;
    }
    auto CommonWindowClass::createWindow(
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
    )->HWND
    {
        return CreateWindowEx(
            extendedWindowStyle,
            className.c_str(),
            windowName.c_str(),
            windowStyle,
            x,
            y,
            width,
            height,
            parentWindowHandle,
            menuHandle,
            instanceHandle,
            param
        );
    }
    auto CALLBACK CommonWindowClass::windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)->LRESULT
    {
        //拡張メモリ取得
        auto window = reinterpret_cast<Window *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        //nullだったらデフォルト処理
        if (window == nullptr)
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        //ちゃんと取得できたらイベント割り振り
        return window->windowProcedure(message, wParam, lParam);
    }
    //---------------------------------------------------------------------------------------------------------
    Window::Window()
        : className()
        , instanceHandle(nullptr)
        , parent(nullptr)
        , windowHandle(nullptr)
    {

    }
    Window::~Window()
    {
        destroy();
    }
    auto Window::destroy()->void
    {
        if (windowHandle == nullptr)
        {
            return;
        }
        DestroyWindow(windowHandle);
        windowHandle = nullptr;
    }
    auto Window::getClassName()const->const tstring &
    {
        return className;
    }
    auto Window::getInstanceHandle()const->const HINSTANCE
    {
        return instanceHandle;
    }
    auto Window::getWindowHandle()->HWND
    {
        return windowHandle;
    }
    auto Window::getWindowHandle()const->const HWND
    {
        return windowHandle;
    }
    auto Window::getParent()->Window *
    {
        return parent;
    }
    auto Window::getParent()const->const Window *
    {
        return parent;
    }
    auto Window::setVisible(bool newVisible)->void
    {
        if (newVisible)
        {
            ShowWindow(getWindowHandle(), SW_SHOW);
        }
        else
        {
            ShowWindow(getWindowHandle(), SW_HIDE);
        }
    }
    auto Window::setEnable(bool newEnable)->void
    {
        EnableWindow(windowHandle, newEnable);
    }
    auto Window::setText(const tstring &newText)->void
    {
        SetWindowText(windowHandle, &newText.front());
    }
    auto Window::setPosition(POINT newPosition)->void
    {
        SetWindowPos(windowHandle, 0, newPosition.x, newPosition.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);
    }
    auto Window::getVisible()const->bool
    {
        return IsWindowVisible(windowHandle) != 0;
    }
    auto Window::getEnable()const->bool
    {
        return IsWindowEnabled(windowHandle) != 0;
    }
    auto Window::getText()const->tstring
    {
        auto windowTextLength = GetWindowTextLength(windowHandle);
        tstring text;
        text.reserve(windowTextLength + 1);
        GetWindowText(windowHandle, &text.front(), text.capacity());
        return text;
    }
    auto Window::getPosition()const->POINT
    {
        RECT rect;
        GetWindowRect(windowHandle, &rect);
        POINT point;
        point.x = rect.left;
        point.y = rect.top;
        return point;
    }
    auto Window::windowProcedure(UINT message, WPARAM wParam, LPARAM lParam)->LRESULT
    {
        switch (message)
        {
        case WM_CREATE:             return onCreate();
        case WM_DESTROY:            return onDestroy();
        case WM_MOVE:               return onMove(wParam, lParam);
        case WM_SIZE:               return onSize(wParam, lParam);
        case WM_ACTIVATE:           return onActivate(wParam, lParam);
        case WM_MOUSEMOVE:          return onMouseMove(wParam, lParam);
        case WM_LBUTTONDOWN:        return onLButtonDown(wParam, lParam);
        case WM_LBUTTONUP:          return onLButtonUP(wParam, lParam);
        case WM_LBUTTONDBLCLK:      return onLButtonDblClk(wParam, lParam);
        case WM_RBUTTONDOWN:        return onRButtonDown(wParam, lParam);
        case WM_RBUTTONUP:          return onRButtonUP(wParam, lParam);
        case WM_RBUTTONDBLCLK:      return onRButtonDblClk(wParam, lParam);
        case WM_MBUTTONDOWN:        return onMButtonDown(wParam, lParam);
        case WM_MBUTTONUP:          return onMButtonUP(wParam, lParam);
        case WM_MBUTTONDBLCLK:      return onMButtonDblClk(wParam, lParam);
        case WM_MOUSEHWHEEL:        return onMouseWheel(wParam, lParam);
        case WM_PAINT:              return onPaint(wParam, lParam);
        case WM_COMMAND:            return onCommand(wParam, lParam);
        case WM_NOTIFY:             return onNotify(wParam, lParam);
        case WM_DROPFILES:          return onDropFiles(wParam, lParam);
        case WM_TIMER:              return onTimer(wParam, lParam);
        }
        return DefWindowProc(getWindowHandle(), message, wParam, lParam);
    }
    auto Window::onCreate()->LRESULT { return 0; }
    auto Window::onDestroy()->LRESULT { return 0; }
    auto Window::onMove(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onSize(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onActivate(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onMouseMove(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onLButtonDown(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onLButtonUP(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onLButtonDblClk(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onRButtonDown(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onRButtonUP(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onRButtonDblClk(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onMButtonDown(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onMButtonUP(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onMButtonDblClk(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onMouseWheel(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onPaint(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onCommand(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onKeyDown(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onNotify(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onDropFiles(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onTimer(WPARAM, LPARAM)->LRESULT { return 0; }
    //---------------------------------------------------------------------------------------------------------
    WindowWithControls::WindowWithControls()
        : Window()
    {

    }
    WindowWithControls::~WindowWithControls()
    {

    }
    auto WindowWithControls::onCommand(WPARAM wParam, LPARAM lParam)->LRESULT
    {
        auto code = HIWORD(wParam);
        auto id = LOWORD(wParam);
        auto controllWindowHandle = reinterpret_cast<HWND>(lParam);
        auto controllWindow = reinterpret_cast<Control *>(GetWindowLongPtr(controllWindowHandle, GWLP_USERDATA));
        return controllWindow->onControllCommand(code, id);
    }
    //---------------------------------------------------------------------------------------------------------
    Control::Control()
        : Window()
    {

    }
    Control::~Control()
    {

    }
    //---------------------------------------------------------------------------------------------------------
    Button::Button()
        : Control()
        , onClick(nullptr)
    {

    }
    Button::~Button()
    {

    }
    auto Button::create(const tstring &_caption, int _x, int _y, int _width, int _height, Window *_parent)->void
    {
        auto exStyle = 0;
        auto style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;
        this->className = TEXT("BUTTON");
        this->instanceHandle = _parent->getInstanceHandle();
        this->parent = _parent;
        this->windowHandle = CommonWindowClass::createWindow(
            exStyle,
            this->className,
            _caption,
            style,
            _x,
            _y,
            _width,
            _height,
            _parent->getWindowHandle(),
            nullptr,
            this->instanceHandle,
            nullptr
        );
        SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        onCreate();
        setVisible(true);
    }
    auto Button::onControllCommand(WORD code, WORD)->LRESULT
    {
        switch (code)
        {
        case BN_CLICKED:
            if (onClick != nullptr)
            {
                onClick(this);
            }
            break;
        default:
            break;
        }
        return 0;
    }
    //---------------------------------------------------------------------------------------------------------
}
