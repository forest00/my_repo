#pragma once
#include <string>
#include <Windows.h>
#include <tchar.h>

using tstring = std::basic_string<TCHAR>;

namespace myWindow
{
    //�E�B���h�E�N���X
    //�������ɓo�^����A�j�����ɓo�^���������
    //���O��HINSTANCE��ێ����Ă���
    //�E�B���h�E���b�Z�[�W��U�蕪����@�\������
    //�E�B���h�E�̊g��������GWLP_USERDATA��Window *���i�[���Ă����K�v������
    class WindowClass
    {
    public:
        WindowClass(const WindowClass &) = delete;
        WindowClass &operator=(const WindowClass &) = delete;
        //�R���X�g���N�^
        //�����Ɠ����ɓo�^�����
        WindowClass(tstring _name, HINSTANCE _instanceHandle);
        //�f�X�g���N�^
        //�j���Ɠ����ɓo�^���������
        ~WindowClass();
    public:
        virtual auto getName()const->const tstring &;
        virtual auto getInstanceHandle()const->const HINSTANCE;
    public:
        static auto CALLBACK commonWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)->LRESULT;
    protected:
        tstring name;
        HINSTANCE instanceHandle;
    };

    //�E�B���h�E���N���X
    class Window
    {
    protected:
        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;
        //�R���X�g���N�^
        Window();
        //�f�X�g���N�^
        virtual ~Window();
    public:
        //�E�B���h�E�N���X�̖��O�擾
        virtual auto getClassName()const->const tstring &;
        //�E�B���h�E�N���X��HINSTANCE�擾
        virtual auto getInstanceHandle()const->const HINSTANCE;
        //�n���h���̎��o��
        virtual auto getWindowHandle()->HWND;
        virtual auto getWindowHandle()const->const HWND;
        //�e�E�B���h�E�̎��o��
        virtual auto getParent()->Window *;
        virtual auto getParent()const->const Window *;
        //����
        virtual auto create(const tstring &_className, HINSTANCE _instanceHandle, HWND _parentWindowHandle, HMENU _menuHandle, const tstring &_text, DWORD _exStyle, DWORD _style, RECT _rect)->void;
        //�j��
        virtual auto destroy()->void;
        //�E�B���h�E�C�x���g�U�蕪���@
        virtual auto windowProcedure(UINT message, WPARAM wParam, LPARAM lParam)->LRESULT;
    protected:
        //Window�쐬�����b�Z�[�W����
        virtual auto onCreate()->LRESULT;
        //Window�j�������b�Z�[�W����
        virtual auto onDestroy()->LRESULT;
        //�ړ�������
        virtual auto onMove(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�T�C�Y�ύX������
        virtual auto onSize(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�A�N�e�B�u���̏���
        virtual auto onActivate(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�}�E�X�ړ�������
        virtual auto onMouseMove(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�}�E�X���{�^������������
        virtual auto onLButtonDown(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�}�E�X���{�^�����㎞����
        virtual auto onLButtonUP(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�}�E�X���{�^���_�u���N���b�N������
        virtual auto onLButtonDblClk(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�}�E�X���{�^������������
        virtual auto onRButtonDown(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�}�E�X���{�^�����㎞����
        virtual auto onRButtonUP(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�}�E�X���{�^���_�u���N���b�N������
        virtual auto onRButtonDblClk(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�}�E�X���{�^������������
        virtual auto onMButtonDown(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�}�E�X���{�^�����㎞����
        virtual auto onMButtonUP(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�}�E�X���{�^���_�u���N���b�N������
        virtual auto onMButtonDblClk(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�}�E�X�z�C�[������
        virtual auto onMouseWheel(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�`�揈��
        virtual auto onPaint(WPARAM wParam, LPARAM lParam)->LRESULT;
        //Window�R�}���h����
        virtual auto onCommand(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�L�[�{�[�h����
        virtual auto onKeyDown(WPARAM wParam, LPARAM lParam)->LRESULT;
        //Window �ʒm����
        virtual auto onNotify(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�h���b�v����
        virtual auto onDropFiles(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�^�C�}�[����
        virtual auto onTimer(WPARAM wParam, LPARAM lParam)->LRESULT;
    public:
        //Visible�ݒ�
        virtual auto setVisible(bool newVisible)->void;
        //Enable�ݒ�
        virtual auto setEnable(bool newEnable)->void;
        //Text�ݒ�
        virtual auto setText(const tstring &newText)->void;
        //Position�ݒ�
        virtual auto setPosition(POINT newPosition)->void;
        //Visible�擾
        virtual auto getVisible()const->bool;
        //Enable�擾
        virtual auto getEnable()const->bool;
        //Text�擾
        virtual auto getText()const->tstring;
        //Position�擾
        virtual auto getPosition()const->POINT;
    protected:
        tstring className;                  //�E�B���h�E�N���X�̖��O�擾
        HINSTANCE instanceHandle;           //�E�B���h�E�N���X��HINSTANCE�擾
        HWND windowHandle;                  //Window�n���h��
        Window *parent;                     //�eWindow
    };

    //�^�C�}�[�E�B���h�E
    //�^�C�}�[�������I�[�o�[���C�h����Ă�
    class TimerWindow : public Window
    {
    public:
        TimerWindow(const TimerWindow &) = delete;
        TimerWindow &operator=(const TimerWindow &) = delete;
        TimerWindow(float _fps);
        ~TimerWindow();
    protected:
        virtual auto onCreate()->LRESULT override;
        virtual auto onTimer(WPARAM wParam, LPARAM lParam)->LRESULT override;
    public:
        void (*onTick)(void);
    protected:
        float fps;
    };

    //���C���E�B���h�E
    //GUI�������Ƃ��ł���
    class MainWindow : public TimerWindow
    {
    protected:
        MainWindow(const MainWindow &) = delete;
        MainWindow &operator=(const MainWindow &) = delete;
        MainWindow(float _fps);
        ~MainWindow();
    public:
        virtual auto create(WindowClass *_windowClass, const tstring &_text, DWORD _exStyle, DWORD _style, RECT _rect)->void;
    protected:
        virtual auto onDestroy()->LRESULT override;
        virtual auto onTimer(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onPaint(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onCommand(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onPaintMain(HDC hdc)->void = 0;
    };

    //�O���t�B�J���ȃ��[�U�[�C���^�[�t�F�[�X
    class GUI : public Window
    {
    protected:
        GUI(const GUI &) = delete;
        GUI &operator=(const GUI &) = delete;
        GUI();
        ~GUI();
    public:
        virtual auto create(Window *_parent, const tstring &_className, const tstring &_text, DWORD _exStyle, DWORD _style, RECT _rect)->void;
    protected:
        virtual auto onCommand(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onGUICommand(WORD code, WORD id)->LRESULT = 0;
    };

    //�{�^��
    //�����������ꂽ���̏�����������Ă�
    class Button : public GUI
    {
    public:
        Button(const Button &) = delete;
        Button &operator=(const Button &) = delete;
        Button(Window *_parent, RECT _rect, const tstring &caption);
        ~Button();
    protected:
        virtual auto onGUICommand(WORD code, WORD id)->LRESULT override;
    public:
        void (*onClick)(void);
        void (*onDoubleClick)(void);
        void (*onPush)(void);
        void (*onUnpush)(void);
        void (*onSetFocus)(void);
        void (*onKillFocus)(void);
    };
}
