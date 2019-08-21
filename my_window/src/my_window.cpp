#include "my_window.h"

namespace myWindow
{
    //---------------------------------------------------------------------------------------------------------
    WindowClass::WindowClass(tstring _name, HINSTANCE _instanceHandle)
        : name(_name)
        , instanceHandle(_instanceHandle)
    {
        WNDCLASS wndclass;
        wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        wndclass.lpfnWndProc = WindowClass::commonWindowProcedure;
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
    WindowClass::~WindowClass()
    {
        UnregisterClass(getName().c_str(), getInstanceHandle());
    }
    auto WindowClass::getName()const->const tstring &
    {
        return name;
    }
    auto WindowClass::getInstanceHandle()const->const HINSTANCE
    {
        return instanceHandle;
    }
    auto CALLBACK WindowClass::commonWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)->LRESULT
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
        , windowHandle(nullptr)
        , parent(nullptr)
    {

    }
    Window::~Window()
    {
        destroy();
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
    auto Window::create(const tstring &_className, HINSTANCE _instanceHandle, HWND _parentWindowHandle, HMENU _menuHandle, const tstring &_text, DWORD _exStyle, DWORD _style, RECT _rect)->void
    {
        className = _className;
        instanceHandle = _instanceHandle;
        auto &rect = _rect;
        windowHandle = CreateWindowEx(
            _exStyle,
            className.c_str(),
            _text.c_str(),
            _style,
            rect.left,
            rect.top,
            rect.right,
            rect.bottom,
            _parentWindowHandle,
            _menuHandle,
            instanceHandle,
            nullptr
        );
        SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        onCreate();
        setVisible(true);
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
    auto Window::onMove(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onSize(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onActivate(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onMouseMove(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onLButtonDown(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onLButtonUP(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onLButtonDblClk(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onRButtonDown(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onRButtonUP(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onRButtonDblClk(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onMButtonDown(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onMButtonUP(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onMButtonDblClk(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onMouseWheel(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onPaint(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onCommand(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onKeyDown(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onNotify(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onDropFiles(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::onTimer(WPARAM wParam, LPARAM lParam)->LRESULT { return 0; }
    auto Window::setVisible(bool newVisible)->void
    {
        auto windowHandle = getWindowHandle();
        if (newVisible)
        {
            ShowWindow(windowHandle, SW_SHOW);
        }
        else
        {
            ShowWindow(windowHandle, SW_HIDE);
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
    //---------------------------------------------------------------------------------------------------------
    TimerWindow::TimerWindow(float _fps)
        : Window()
        , onTick()
        , fps(_fps)
    {

    }
    TimerWindow::~TimerWindow()
    {

    }
    auto TimerWindow::onCreate()->LRESULT
    {
        SetTimer(windowHandle, 0, static_cast<UINT>(1000.0f / fps), nullptr);
        return 0;
    }
    auto TimerWindow::onTimer(WPARAM wParam, LPARAM lParam)->LRESULT
    {
        if (onTick != nullptr)
        {
            onTick();
        }
        return 0;
    }
    //---------------------------------------------------------------------------------------------------------
    MainWindow::MainWindow(float _fps)
        : TimerWindow(_fps)
    {

    }
    MainWindow::~MainWindow()
    {

    }
    auto MainWindow::create(WindowClass *_windowClass, const tstring &_text, DWORD _exStyle, DWORD _style, RECT _rect)->void
    {
        Window::create(_windowClass->getName(), _windowClass->getInstanceHandle(), nullptr, nullptr, _text, _exStyle, _style, _rect);
    }
    auto MainWindow::onDestroy()->LRESULT
    {
        PostQuitMessage(0);
        return 0;
    }
    auto MainWindow::onTimer(WPARAM wParam, LPARAM lParam)->LRESULT
    {
        auto windowHandle = getWindowHandle();
        InvalidateRect(windowHandle, nullptr, true);
        return 0;
    }
    auto MainWindow::onPaint(WPARAM wParam, LPARAM lParam)->LRESULT
    {
        auto windowHandle = getWindowHandle();
        HDC hdc;
        PAINTSTRUCT ps;
        hdc = BeginPaint(windowHandle, &ps);
        onPaintMain(hdc);
        EndPaint(windowHandle, &ps);
        return 0;
    }
    auto MainWindow::onCommand(WPARAM wParam, LPARAM lParam)->LRESULT
    {
        auto menu = reinterpret_cast<HMENU>(LOWORD(wParam));
        auto gui = reinterpret_cast<GUI *>(menu);//ここtodo:どうにかする、親にメッセージ送りやがるからどうにもならんてmjd
        //親はすべての子供が分かるようにするしかないねこれはねそうだね
        return gui->windowProcedure(WM_COMMAND, wParam, lParam);
    }
    //---------------------------------------------------------------------------------------------------------
    GUI::GUI()
        : Window()
    {

    }
    GUI::~GUI()
    {

    }
    auto GUI::create(Window *_parent, const tstring &_className, const tstring &_text, DWORD _exStyle, DWORD _style, RECT _rect)->void
    {
        Window::create(_className, _parent->getInstanceHandle(), _parent->getWindowHandle(), reinterpret_cast<HMENU>(this), _text, _exStyle, _style, _rect);
    }
    auto GUI::onCommand(WPARAM wParam, LPARAM lParam)->LRESULT
    {
        WORD code = HIWORD(wParam);
        WORD id = LOWORD(wParam);
        return onGUICommand(code, id);
    }
    //---------------------------------------------------------------------------------------------------------
    Button::Button(Window *_parent, RECT _rect, const tstring &caption)
        : GUI()
        , onClick(nullptr)
        , onDoubleClick(nullptr)
        , onPush(nullptr)
        , onUnpush(nullptr)
        , onSetFocus(nullptr)
        , onKillFocus(nullptr)
    {
        parent = _parent;
        GUI::create(_parent, TEXT("BUTTON"), caption, 0, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_NOTIFY, _rect);
    }
    Button::~Button()
    {

    }
    auto Button::onGUICommand(WORD code, WORD id)->LRESULT
    {
        switch (code)
        {
        case BN_CLICKED:
            if (onClick != nullptr)
            {
                onClick();
            }
            break;
        case BN_DOUBLECLICKED:
            if (onDoubleClick != nullptr)
            {
                onDoubleClick();
            }
            break;
        case BN_PUSHED:
            if (onPush != nullptr)
            {
                onPush();
            }
            break;
        case BN_UNPUSHED:
            if (onUnpush != nullptr)
            {
                onUnpush();
            }
            break;
        case BN_SETFOCUS:
            if (onSetFocus != nullptr)
            {
                onSetFocus();
            }
            break;
        case BN_KILLFOCUS:
            if (onKillFocus != nullptr)
            {
                onKillFocus();
            }
            break;
        default:
            break;
        }
        return 0;
    }
}
