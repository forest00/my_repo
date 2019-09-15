#include "my_window.h"
#include <cassert>

namespace myWindow
{
    //---------------------------------------------------------------------------------------------------------
    auto Wrap::createWindow(
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
    )->HWND
    {
        return CreateWindowEx(
            extendedWindowStyle,
            className.c_str(),
            windowText.c_str(),
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
    auto Wrap::showCursor(bool show)
    {
        if (show)
        {
            while (ShowCursor(true) < 0)
            {

            }
        }
        else
        {
            while (ShowCursor(false) >= 0)
            {

            }
        }
    }
    auto Wrap::getOpenFileName(const Window *owner, const TCHAR *filter)->tstring
    {
        OPENFILENAME ofn = {0};
        tstring foundFileName;
        foundFileName.resize(MAX_PATH);
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = owner->getWindowHandle();
        ofn.lpstrFilter = filter;
        ofn.lpstrFile = &foundFileName.front();
        ofn.nMaxFile = foundFileName.size();
        ofn.Flags = OFN_FILEMUSTEXIST;
        GetOpenFileName(&ofn);
        return foundFileName;
    }
    auto Wrap::getSaveFileName(const Window *owner, const TCHAR *filter)->tstring
    {
        OPENFILENAME ofn = {0};
        tstring foundFileName;
        foundFileName.resize(MAX_PATH);
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = owner->getWindowHandle();
        ofn.lpstrFilter = filter;
        ofn.lpstrFile = &foundFileName.front();
        ofn.nMaxFile = foundFileName.size();
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
        GetSaveFileName(&ofn);
        return foundFileName;
    }
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
    auto Window::create(
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
    )->void
    {
        assert(getWindowHandle() == nullptr);
        HWND parentWindowHandle = nullptr;
        if (_parent != nullptr)
        {
            parentWindowHandle = _parent->getWindowHandle();
        }
        this->className = _className;
        this->instanceHandle = _instanceHandle;
        this->parent = _parent;
        this->windowHandle = Wrap::createWindow(
            _extendedWindowStyle,
            this->className,
            _windowText,
            _windowStyle,
            _x,
            _y,
            _width,
            _height,
            parentWindowHandle,
            reinterpret_cast<HMENU>(_menuHandle),
            this->instanceHandle,
            _param
        );
        SetWindowLongPtr(getWindowHandle(), GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        onCreate();
    }
    auto Window::destroy()->void
    {
        if (getWindowHandle() == nullptr)
        {
            return;
        }
        DestroyWindow(getWindowHandle());
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
    auto Window::getStyle()->DWORD
    {
        return GetWindowLongPtr(getWindowHandle(), GWL_STYLE);
    }
    auto Window::getVisible()const->bool
    {
        return IsWindowVisible(getWindowHandle()) != 0;
    }
    auto Window::getEnable()const->bool
    {
        return IsWindowEnabled(getWindowHandle()) != 0;
    }
    auto Window::getText()const->tstring
    {
        auto textLength = GetWindowTextLength(getWindowHandle());
        tstring text;
        text.resize(textLength + 1);
        GetWindowText(getWindowHandle(), &text.front(), text.size());
        return text;
    }
    auto Window::getPos()const->POINT
    {
        RECT rect;
        GetWindowRect(getWindowHandle(), &rect);
        POINT point;
        point.x = rect.left;
        point.y = rect.top;
        return point;
    }
    auto Window::getSize()const->SIZE
    {
        RECT rect;
        GetWindowRect(getWindowHandle(), &rect);
        SIZE size;
        size.cx = rect.right - rect.left;
        size.cy = rect.bottom - rect.top;
        return size;
    }
    auto Window::getRect()const->RECT
    {
        RECT rect;
        GetWindowRect(getWindowHandle(), &rect);
        return rect;
    }
    auto Window::reflectStyle()->void
    {
        SetWindowPos(getWindowHandle(), nullptr, 0, 0, 0, 0, (SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED));
    }
    auto Window::sendMessage(UINT message, WPARAM wParam, LPARAM lParam)->LRESULT
    {
        return SendMessage(getWindowHandle(), message, wParam, lParam);
    }
    auto Window::setStyle(DWORD newStyle, bool reflectImmediately)->void
    {
        SetWindowLong(getWindowHandle(), GWL_STYLE, newStyle);
        if (reflectImmediately)
        {
            reflectStyle();
        }
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
        EnableWindow(getWindowHandle(), newEnable);
    }
    auto Window::setText(const tstring &newText)->void
    {
        SetWindowText(getWindowHandle(), &newText.front());
    }
    auto Window::setPos(POINT newPos)->void
    {
        SetWindowPos(getWindowHandle(), nullptr, newPos.x, newPos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);
    }
    auto Window::setSize(SIZE newSize)->void
    {
        SetWindowPos(getWindowHandle(), nullptr, 0, 0, newSize.cx, newSize.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW);
    }
    auto Window::setRect(RECT newRect)->void
    {
        SetWindowPos(getWindowHandle(), nullptr, newRect.left, newRect.top, newRect.right - newRect.left, newRect.bottom - newRect.top, SWP_NOZORDER | SWP_SHOWWINDOW);
    }
    auto Window::redraw(bool erase)->void
    {
        InvalidateRect(getWindowHandle(), nullptr, erase);
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
        case WM_MOUSELEAVE:         return onMouseLeave(wParam, lParam);
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
        default:                    return DefWindowProc(getWindowHandle(), message, wParam, lParam);
        }
    }
    auto Window::onCreate()->LRESULT { return 0; }
    auto Window::onDestroy()->LRESULT { return 0; }
    auto Window::onMove(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onSize(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onActivate(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onMouseMove(WPARAM, LPARAM)->LRESULT { return 0; }
    auto Window::onMouseLeave(WPARAM, LPARAM)->LRESULT { return 0; }
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
    WindowWithControls::~WindowWithControls()
    {

    }
    auto WindowWithControls::onCommand(WPARAM wParam, LPARAM lParam)->LRESULT
    {
        auto code = HIWORD(wParam);
        auto id = LOWORD(wParam);
        auto controllWindowHandle = reinterpret_cast<HWND>(lParam);
        auto controllWindow = reinterpret_cast<Control *>(GetWindowLongPtr(controllWindowHandle, GWLP_USERDATA));
        return onCommandMain(code, id, controllWindow);
    }
    //---------------------------------------------------------------------------------------------------------
    auto Label::create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void
    {
        Window::create(
            0,
            TEXT("STATIC"),
            _text,
            WS_CHILD | WS_VISIBLE,
            _x,
            _y,
            _width,
            _height,
            _parent,
            reinterpret_cast<HMENU>(id),
            _parent->getInstanceHandle(),
            nullptr
        );
    }
    //---------------------------------------------------------------------------------------------------------
    auto Edit::create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void
    {
        Window::create(
            0,
            TEXT("EDIT"),
            _text,
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            _x,
            _y,
            _width,
            _height,
            _parent,
            reinterpret_cast<HMENU>(id),
            _parent->getInstanceHandle(),
            nullptr
        );
    }
    //---------------------------------------------------------------------------------------------------------
    auto Button::create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void
    {
        Window::create(
            0,
            TEXT("BUTTON"),
            _text,
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            _x,
            _y,
            _width,
            _height,
            _parent,
            reinterpret_cast<HMENU>(id),
            _parent->getInstanceHandle(),
            nullptr
        );
    }
    //---------------------------------------------------------------------------------------------------------
    auto CheckBox::create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void
    {
        Window::create(
            0,
            TEXT("BUTTON"),
            _text,
            WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
            _x,
            _y,
            _width,
            _height,
            _parent,
            reinterpret_cast<HMENU>(id),
            _parent->getInstanceHandle(),
            nullptr
        );
    }
    auto CheckBox::bGetState()->bool
    {
        return static_cast<bool>(sendMessage(BM_GETCHECK, 0, 0));
    }
    //---------------------------------------------------------------------------------------------------------
    auto CheckBox3State::create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void
    {
        Window::create(
            0,
            TEXT("BUTTON"),
            _text,
            WS_CHILD | WS_VISIBLE | BS_AUTO3STATE,
            _x,
            _y,
            _width,
            _height,
            _parent,
            reinterpret_cast<HMENU>(id),
            _parent->getInstanceHandle(),
            nullptr
        );
    }
    auto CheckBox3State::bGetState()->int
    {
        return static_cast<int>(sendMessage(BM_GETCHECK, 0, 0));
    }
    //---------------------------------------------------------------------------------------------------------
    auto GroupBox::create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void
    {
        Window::create(
            0,
            TEXT("BUTTON"),
            _text,
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            _x,
            _y,
            _width,
            _height,
            _parent,
            reinterpret_cast<HMENU>(id),
            _parent->getInstanceHandle(),
            nullptr
        );
    }
    //---------------------------------------------------------------------------------------------------------
    auto RadioButton::create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void
    {
        Window::create(
            0,
            TEXT("BUTTON"),
            _text,
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            _x,
            _y,
            _width,
            _height,
            _parent,
            reinterpret_cast<HMENU>(id),
            _parent->getInstanceHandle(),
            nullptr
        );
    }
    //---------------------------------------------------------------------------------------------------------
    auto ListBox::create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void
    {
        Window::create(
            0,
            TEXT("LISTBOX"),
            _text,
            WS_CHILD | WS_VISIBLE | (LBS_STANDARD & (~LBS_SORT)),
            _x,
            _y,
            _width,
            _height,
            _parent,
            reinterpret_cast<HMENU>(id),
            _parent->getInstanceHandle(),
            nullptr
        );
    }
    auto ListBox::lbAddItem(const tstring &newItem)->void
    {
        sendMessage(LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(newItem.c_str()));
    }
    auto ListBox::lbChangeItem(int itemIndex, const tstring &newItem)->void
    {
        assert(itemIndex >= 0);
        assert(itemIndex < lbGetItemNum());
        lbDeleteItem(itemIndex);
        lbInsertItem(itemIndex, newItem);
    }
    auto ListBox::lbDeleteItem(int itemIndex)->void
    {
        assert(itemIndex >= 0);
        assert(itemIndex < lbGetItemNum());
        sendMessage(LB_DELETESTRING, static_cast<WPARAM>(itemIndex), 0);
    }
    auto ListBox::lbDeleteItems()->void
    {
        sendMessage(LB_RESETCONTENT, 0, 0);
    }
    auto ListBox::lbGetItem(int itemIndex)->tstring
    {
        assert(itemIndex >= 0);
        assert(itemIndex < lbGetItemNum());
        auto textLength = sendMessage(LB_GETTEXTLEN, static_cast<WPARAM>(itemIndex), 0);
        tstring text;
        text.resize(textLength + 1);
        sendMessage(LB_GETTEXT, 0, reinterpret_cast<LPARAM>(&text.front()));
        return text;
    }
    auto ListBox::lbGetItemNum()->int
    {
        return sendMessage(LB_GETCOUNT, 0, 0);
    }
    auto ListBox::lbGetSelectedIndex()->int
    {
        return sendMessage(LB_GETCURSEL, 0, 0);
    }
    auto ListBox::lbInsertItem(int itemIndex, const tstring &newItem)->void
    {
        assert(itemIndex >= 0);
        assert(itemIndex < lbGetItemNum());
        sendMessage(LB_INSERTSTRING, static_cast<WPARAM>(itemIndex), reinterpret_cast<LPARAM>(newItem.c_str()));
    }
    auto ListBox::lbSetSelectedIndex(int newSelectedIndex)->void
    {
        sendMessage(LB_SETCURSEL, static_cast<WPARAM>(newSelectedIndex), 0);
    }
    //---------------------------------------------------------------------------------------------------------
    auto ComboBox::create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void
    {
        Window::create(
            0,
            TEXT("COMBOBOX"),
            _text,
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
            _x,
            _y,
            _width,
            _height,
            _parent,
            reinterpret_cast<HMENU>(id),
            _parent->getInstanceHandle(),
            nullptr
        );
    }
    auto ComboBox::cbAddItem(const tstring &newItem)->void
    {
        sendMessage(CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(newItem.c_str()));
    }
    auto ComboBox::cbChangeItem(int itemIndex, const tstring &newItem)->void
    {
        assert(itemIndex >= 0);
        assert(itemIndex < cbGetItemNum());
        cbDeleteItem(itemIndex);
        cbInsertItem(itemIndex, newItem);
    }
    auto ComboBox::cbDeleteItem(int itemIndex)->void
    {
        assert(itemIndex >= 0);
        assert(itemIndex < cbGetItemNum());
        sendMessage(CB_DELETESTRING, static_cast<WPARAM>(itemIndex), 0);
    }
    auto ComboBox::cbDeleteItems()->void
    {
        sendMessage(CB_RESETCONTENT, 0, 0);
    }
    auto ComboBox::cbGetItem(int itemIndex)->tstring
    {
        assert(itemIndex >= 0);
        assert(itemIndex < cbGetItemNum());
        auto textLength = sendMessage(CB_GETLBTEXTLEN, static_cast<WPARAM>(itemIndex), 0);
        tstring text;
        text.resize(textLength + 1);
        sendMessage(CB_GETLBTEXT, 0, reinterpret_cast<LPARAM>(&text.front()));
        return text;
    }
    auto ComboBox::cbGetItemNum()->int
    {
        return sendMessage(CB_GETCOUNT, 0, 0);
    }
    auto ComboBox::cbGetSelectedIndex()->int
    {
        return sendMessage(CB_GETCURSEL, 0, 0);
    }
    auto ComboBox::cbInsertItem(int itemIndex, const tstring &newItem)->void
    {
        assert(itemIndex >= 0);
        assert(itemIndex < cbGetItemNum());
        sendMessage(CB_INSERTSTRING, static_cast<WPARAM>(itemIndex), reinterpret_cast<LPARAM>(newItem.c_str()));
    }
    auto ComboBox::cbSetSelectedIndex(int newSelectedIndex)->void
    {
        sendMessage(CB_SETCURSEL, static_cast<WPARAM>(newSelectedIndex), 0);
    }
    //---------------------------------------------------------------------------------------------------------
    auto TrackBar::create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void
    {
        assert(getWindowHandle() == nullptr);
        Window::create(
            0,
            TRACKBAR_CLASS,
            _text,
            WS_CHILD | WS_VISIBLE,
            _x,
            _y,
            _width,
            _height,
            _parent,
            reinterpret_cast<HMENU>(id),
            _parent->getInstanceHandle(),
            nullptr
        );
    }
    //---------------------------------------------------------------------------------------------------------
    Numeric::Numeric()
        : mouseOn()
        , changing()
        , defaultValue()
        , mouseLastClickedX()
        , mouseLastClickedY()
    {

    }
    auto Numeric::create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void
    {
        assert(_parent != nullptr);
        Window::create(
            0,
            _parent->getClassName(),
            _text,
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            _x,
            _y,
            _width,
            _height,
            _parent,
            reinterpret_cast<HMENU>(id),
            _parent->getInstanceHandle(),
            nullptr
        );
        auto value = std::stof(_text);
        nSetDefaultValue(value);
        nSetValue(value);
    }
    auto Numeric::nGetDefaultValue()->float
    {
        return defaultValue;
    }
    auto Numeric::nGetValue()->float
    {
        auto text = getText();
        auto value = std::stof(text);
        return value;
    }
    auto Numeric::nSetDefaultValue(float newDefaultValue)->void
    {
        defaultValue = newDefaultValue;
    }
    auto Numeric::nSetValue(float newValue)->void
    {
        auto newText = to_tstring(newValue);
        setText(newText);
    }
    auto Numeric::onCreate()->LRESULT
    {
        return 0;
    }
    auto Numeric::onMouseMove(WPARAM wParam, LPARAM lParam)->LRESULT
    {
        UNREFERENCED_PARAMETER(wParam);
        UNREFERENCED_PARAMETER(lParam);
        //フォーカスを得た瞬間なら
        if (mouseOn == false)
        {
            //親に「フォーカスを得た」のメッセージを送る
            auto controlID = GetDlgCtrlID(getWindowHandle());
            getParent()->sendMessage(WM_COMMAND, MAKEWPARAM(controlID, Message_GotFocus), reinterpret_cast<LPARAM>(getWindowHandle()));
        }
        //マウスが乗っかっているフラグオン
        mouseOn = true;
        //再描画メッセージを送る
        InvalidateRect(getWindowHandle(), nullptr, false);
        //左クリック判定
        if (wParam & MK_LBUTTON)
        {
            POINT mousePos;
            GetCursorPos(&mousePos);
            ScreenToClient(getWindowHandle(), &mousePos);
            auto mouseX = mousePos.x;
            auto delta = (mouseX - mouseLastClickedX) * 0.125f;
            auto value = nGetValue();
            auto newValue = value + delta;
            nSetValue(newValue);
            mousePos.x = mouseLastClickedX;
            mousePos.y = mouseLastClickedY;
            ClientToScreen(getWindowHandle(), &mousePos);
            SetCursorPos(mousePos.x, mousePos.y);
            //親に「値変更中」のメッセージを送る
            auto controlID = GetDlgCtrlID(getWindowHandle());
            getParent()->sendMessage(WM_COMMAND, MAKEWPARAM(controlID, Message_ChangingValue), reinterpret_cast<LPARAM>(getWindowHandle()));
        }
        //WM_MOUSELEAVEを受け取れるようにする
        //参考1:http://hp.vector.co.jp/authors/VA016117/hoverbtn2.html
        //参考2:https://xyuyux.hatenadiary.org/entries/2009/02/11
        //参考3:https://blog.systemjp.net/entry/20110815/p1
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_LEAVE;
        tme.hwndTrack = getWindowHandle();
        _TrackMouseEvent(&tme);
        return 0;
    }
    auto Numeric::onMouseLeave(WPARAM wParam, LPARAM lParam)->LRESULT
    {
        UNREFERENCED_PARAMETER(wParam);
        UNREFERENCED_PARAMETER(lParam);
        //親に「フォーカスを失った」のメッセージを送る
        auto controlID = GetDlgCtrlID(getWindowHandle());
        getParent()->sendMessage(WM_COMMAND, MAKEWPARAM(controlID, Message_LostFocus), reinterpret_cast<LPARAM>(getWindowHandle()));
        //マウスが乗っかっているフラグオフ
        mouseOn = false;
        //再描画メッセージを送る
        InvalidateRect(getWindowHandle(), nullptr, false);
        return 0;
    }
    auto Numeric::onLButtonDown(WPARAM wParam, LPARAM lParam)->LRESULT
    {
        UNREFERENCED_PARAMETER(wParam);
        UNREFERENCED_PARAMETER(lParam);
        //位置保存
        mouseLastClickedX = LOWORD(lParam);
        mouseLastClickedY = HIWORD(lParam);
        //RECT計算
        RECT rect;
        GetClientRect(getWindowHandle(), &rect);
        POINT leftTop;
        POINT rightBottom;
        leftTop.x = rect.left;
        leftTop.y = rect.top;
        rightBottom.x = rect.right;
        rightBottom.y = rect.bottom;
        ClientToScreen(getWindowHandle(), &leftTop);
        ClientToScreen(getWindowHandle(), &rightBottom);
        rect.left = leftTop.x + 1;
        rect.top = leftTop.y + 1;
        rect.right = rightBottom.x - 1;
        rect.bottom = rightBottom.y - 1;
        //マウスを閉じ込める
        ClipCursor(&rect);
        //変更中になる
        changing = true;
        //親に「値変更が開始された」のメッセージを送る
        auto controlID = GetDlgCtrlID(getWindowHandle());
        getParent()->sendMessage(WM_COMMAND, MAKEWPARAM(controlID, Message_ValueChangeStarted), reinterpret_cast<LPARAM>(getWindowHandle()));
        return 0;
    }
    auto Numeric::onLButtonUP(WPARAM wParam, LPARAM lParam)->LRESULT
    {
        UNREFERENCED_PARAMETER(wParam);
        UNREFERENCED_PARAMETER(lParam);
        //変更中じゃなくなる
        changing = false;
        //マウスを解放
        ClipCursor(nullptr);
        //親に「値変更が終わった」のメッセージを送る
        auto controlID = GetDlgCtrlID(getWindowHandle());
        getParent()->sendMessage(WM_COMMAND, MAKEWPARAM(controlID, Message_ValueChangeIsOver), reinterpret_cast<LPARAM>(getWindowHandle()));
        return 0;
    }
    auto Numeric::onLButtonDblClk(WPARAM wParam, LPARAM lParam)->LRESULT
    {
        UNREFERENCED_PARAMETER(wParam);
        UNREFERENCED_PARAMETER(lParam);
        nSetValue(defaultValue);
        //親に「値がリセットされた」のメッセージを送る
        auto controlID = GetDlgCtrlID(getWindowHandle());
        getParent()->sendMessage(WM_COMMAND, MAKEWPARAM(controlID, Message_ValueWasReset), reinterpret_cast<LPARAM>(getWindowHandle()));
        return 0;
    }
    auto Numeric::onPaint(WPARAM wParam, LPARAM lParam)->LRESULT
    {
        UNREFERENCED_PARAMETER(wParam);
        UNREFERENCED_PARAMETER(lParam);
        HDC hdc;
        PAINTSTRUCT ps;
        auto text = getText();
        auto size = getSize();
        hdc = BeginPaint(getWindowHandle(), &ps);
        //RECT計算
        RECT rect;
        rect.left = 0;
        rect.top = 0;
        rect.right = size.cx;
        rect.bottom = size.cy;
        //マウスが乗っかっているだけなら
        if (mouseOn)
        {
            //斜め赤線
            auto brush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 0));
            FillRect(hdc, &rect, brush);
        }
        //値が変更中なら
        if (changing)
        {
            //縦横青線
            auto brush = CreateHatchBrush(HS_CROSS, RGB(0, 0, 255));
            FillRect(hdc, &rect, brush);
        }
        //現在の値を出す(文字幅=8 && 文字高さ=20が前提で成り立ってる。調べる方法は...?)
        TextOut(hdc, size.cx / 2 - (text.length() - 1) * 4, size.cy / 2 - 10, text.c_str(), text.length() - 1);
        EndPaint(getWindowHandle(), &ps);
        return 0;
    }
    //---------------------------------------------------------------------------------------------------------
}
