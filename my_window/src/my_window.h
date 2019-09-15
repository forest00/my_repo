//file:my_window.h
//date:2019/08/25
//auther:forest00
//�E�B���h�E�̈���������N���X�Q�ł�
//�E�B���h�E�N���X�͂��̖��̒ʂ�A�E�B���h�E�̕��ނ�\�����̂��Ɨ���
//topic:2019/09/01���낢��ǉ��B�N�b�\��ς��킱��B�B�B

#pragma once
#include "tstring.h"
#include <Windows.h>
#include    <commctrl.h>

#pragma comment(lib, "ComCtl32.lib")

namespace myWindow
{
    //�N���X���X�g
    class Wrap;
    class CommonWindowClass;
    class Window;
    class WindowWithControls;
    class Control;
    class Label;
    class Edit;
    class Button;
    class CheckBox;
    class CheckBox3State;
    class GroupBox;
    class RadioButton;
    class ListBox;
    class ComboBox;
    //class ProgressBar//todo;
    class TrackBar;
    class Numeric;

    //Windows�̊֐����b�p�[�N���X
    class Wrap
    {
    public:
        //�E�B���h�E�����֐�(CreateWindowEx)�̃��b�p�[�֐��ł�
        //�������Ƒ�O������tstring�ɂȂ��Ă��܂�
        static auto createWindow(
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
        )->HWND;
        //ShowCursor�̃��b�p�[�֐��ł�
        static auto showCursor(bool show);
        //GetOpenFileName�̃��b�p�[�ł�
        //�w�肵���g���q�����t�@�C����T���Ă���܂�
        //�t�B���^�[�̌`��
        //"������\0*.�g���q\0"
        //"������\0*.�g���q\0"
        //"������\0*.�g���q\0\0"
        //���������ꍇ:�t�@�C����,����ȊO:�󕶎���
        static auto getOpenFileName(const Window *owner, const TCHAR *filter)->tstring;
        //GetSaveFileName�̃��b�p�[�ł�
        //�w�肵���g���q�����t�@�C����T���Ă���܂�
        //�t�B���^�[�̌`��
        //"������\0*.�g���q\0"
        //"������\0*.�g���q\0"
        //"������\0*.�g���q\0\0"
        //���������ꍇ:�t�@�C����,����ȊO:�󕶎���
        static auto getSaveFileName(const Window *owner, const TCHAR *filter)->tstring;
    };

    //���ʃE�B���h�E�N���X
    class CommonWindowClass
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        CommonWindowClass(const CommonWindowClass &) = delete;
        CommonWindowClass &operator=(const CommonWindowClass &) = delete;
        CommonWindowClass();
        virtual ~CommonWindowClass();
    public://����{
        //�o�^
        auto registerClass(const tstring &_name, HINSTANCE _instanceHandle)->void;
        //�o�^����(�f�X�g���N�^�ł��Ă΂��̂ŌĂіY��邱�Ƃ͂Ȃ��B����)
        auto unregisterClass()->void;
    public://��{����
        //���O�擾
        virtual auto getName()const->const tstring &;
        //HINSTANCE�擾
        virtual auto getInstanceHandle()const->const HINSTANCE;
    public://���̑��̐ÓI�֐�
        //�E�B���h�E�v���V�[�W���[�ł�
        static auto CALLBACK windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)->LRESULT;
    protected://�����o�[�ϐ�
        tstring name;
        HINSTANCE instanceHandle;
    };

    //�E�B���h�E���N���X
    class Window
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;
        Window();
        virtual ~Window() = 0;
    public://����{
        //�E�B���h�E����
        virtual auto create(
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
        )->void;
        //�E�B���h�E�j��
        virtual auto destroy()->void;
        //�E�B���h�E�N���X���擾
        virtual auto getClassName()const->const tstring &;
        //�E�B���h�E�N���XHINSTANCE�擾
        virtual auto getInstanceHandle()const->const HINSTANCE;
        //�E�B���h�E�n���h���擾
        virtual auto getWindowHandle()->HWND;
        //�E�B���h�E�n���h���擾(const)
        virtual auto getWindowHandle()const->const HWND;
        //�e�E�B���h�E�擾
        virtual auto getParent()->Window *;
        //�e�E�B���h�E�擾(const)
        virtual auto getParent()const->const Window *;
    public://��{����
        //Style�擾
        virtual auto getStyle()->DWORD;
        //Visible�擾
        virtual auto getVisible()const->bool;
        //Enable�擾
        virtual auto getEnable()const->bool;
        //Text�擾
        virtual auto getText()const->tstring;
        //Pos�擾
        virtual auto getPos()const->POINT;
        //Size�擾
        virtual auto getSize()const->SIZE;
        //Rect�擾
        virtual auto getRect()const->RECT;
        //Style���f
        virtual auto reflectStyle()->void;
        //���b�Z�[�W�𑗂�
        virtual auto sendMessage(UINT message, WPARAM wParam, LPARAM lParam)->LRESULT;
        //Style�ݒ�
        virtual auto setStyle(DWORD newStyle, bool reflectImmediately)->void;
        //Visible�ݒ�
        virtual auto setVisible(bool newVisible)->void;
        //Enable�ݒ�
        virtual auto setEnable(bool newEnable)->void;
        //Text�ݒ�(SetWindowText)
        virtual auto setText(const tstring &newText)->void;
        //Pos�ݒ�(SetWindowPos)
        virtual auto setPos(POINT newPos)->void;
        //Size�ݒ�(SetWindowPos)
        virtual auto setSize(SIZE newSize)->void;
        //Rect�ݒ�(SetWindowPos)
        virtual auto setRect(RECT newRect)->void;
        //InvalidateRect(windowHandle, nullptr, erase)���Ăяo��
        virtual auto redraw(bool erase)->void;
    public://�C�x���g����
        //�E�B���h�E�C�x���g�U�蕪���@
        virtual auto windowProcedure(UINT message, WPARAM wParam, LPARAM lParam)->LRESULT;
    protected://�I�[�o�[���C�h����
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
        //�}�E�X�ދp������(���̃��b�Z�[�W���󂯎��ɂ͓��ʂȏ������K�v)
        virtual auto onMouseLeave(WPARAM wParam, LPARAM lParam)->LRESULT;
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
        //Window�ʒm����
        virtual auto onNotify(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�t�@�C���h���b�v����
        virtual auto onDropFiles(WPARAM wParam, LPARAM lParam)->LRESULT;
        //�^�C�}�[����
        virtual auto onTimer(WPARAM wParam, LPARAM lParam)->LRESULT;
    protected://�����o�[�ϐ�
        tstring className;                  //�E�B���h�E�N���X��
        HINSTANCE instanceHandle;           //�E�B���h�E�N���XHINSTANCE
        Window *parent;                     //�eWindow
        HWND windowHandle;                  //Window�n���h��
    };

    //��������̃R���g���[�������L����E�B���h�E
    class WindowWithControls : public Window
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        WindowWithControls(const WindowWithControls &) = delete;
        WindowWithControls &operator=(const WindowWithControls &) = delete;
        WindowWithControls() = default;
        virtual ~WindowWithControls() = 0;
    protected://�I�[�o�[���C�h����
        virtual auto onCommand(WPARAM wParam, LPARAM lParam)->LRESULT override;
    protected://�I�[�o�[���C�h����
        virtual auto onCommandMain(WORD code, WORD id, Control *controllWindow)->LRESULT = 0;
    };

    //�R���g���[�����N���X
    class Control : public Window
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        Control(const Control &) = delete;
        Control &operator=(const Control &) = delete;
        Control() = default;
        ~Control() = default;
    protected://�I�[�o�[���C�h����
        //�E�B���h�E����
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void = 0;
    };

    //�X�^�e�B�b�N(���x��)
    class Label : public Control
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        Label(const Label &) = delete;
        Label &operator=(const Label &) = delete;
        Label() = default;
        virtual ~Label() = default;
    public://����{
        //�E�B���h�E����
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    };

    //�G�f�B�b�g
    class Edit : public Control
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        Edit(const Edit &) = delete;
        Edit &operator=(const Edit &) = delete;
        Edit() = default;
        virtual ~Edit() = default;
    public://����{
        //�E�B���h�E����
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    };

    //�{�^��
    class Button : public Control
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        Button(const Button &) = delete;
        Button &operator=(const Button &) = delete;
        Button() = default;
        virtual ~Button() = default;
    public://����{
        //�E�B���h�E����
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    };

    //�`�F�b�N�{�b�N�X
    class CheckBox : public Control
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        CheckBox(const CheckBox &) = delete;
        CheckBox &operator=(const CheckBox &) = delete;
        CheckBox() = default;
        virtual ~CheckBox() = default;
    public://����{
        //�E�B���h�E����
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    public://��{����
        auto bGetState()->bool;
    };

    //3��ԃ`�F�b�N�{�b�N�X
    class CheckBox3State : public Control
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        CheckBox3State(const CheckBox3State &) = delete;
        CheckBox3State &operator=(const CheckBox3State &) = delete;
        CheckBox3State() = default;
        virtual ~CheckBox3State() = default;
    public://����{
        //�E�B���h�E����
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    public://��{����
        auto bGetState()->int;
    };

    //�O���[�v�{�b�N�X
    class GroupBox : public Control
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        GroupBox(const GroupBox &) = delete;
        GroupBox &operator=(const GroupBox &) = delete;
        GroupBox() = default;
        virtual ~GroupBox() = default;
    public://����{
        //�E�B���h�E����
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    };

    //���W�I�{�^��
    class RadioButton : public Control
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        RadioButton(const RadioButton &) = delete;
        RadioButton &operator=(const RadioButton &) = delete;
        RadioButton() = default;
        virtual ~RadioButton() = default;
    public://����{
        //�E�B���h�E����
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    };

    //���X�g�{�b�N�X
    class ListBox : public Control
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        ListBox(const ListBox &) = delete;
        ListBox &operator=(const ListBox &) = delete;
        ListBox() = default;
        virtual ~ListBox() = default;
    public://����{
        //�E�B���h�E����
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    public://��{����
        //�A�C�e���ǉ�
        virtual auto lbAddItem(const tstring &newItem)->void;
        //�A�C�e���ύX
        virtual auto lbChangeItem(int itemIndex, const tstring &newItem)->void;
        //�A�C�e���폜
        virtual auto lbDeleteItem(int itemIndex)->void;
        //�S�A�C�e���폜
        virtual auto lbDeleteItems()->void;
        //�A�C�e���擾
        virtual auto lbGetItem(int itemIndex)->tstring;
        //�A�C�e�����擾
        virtual auto lbGetItemNum()->int;
        //�J�[�\���̈ʒu���擾
        virtual auto lbGetSelectedIndex()->int;
        //�A�C�e���}��
        virtual auto lbInsertItem(int itemIndex, const tstring &newItem)->void;
        //�J�[�\���̈ʒu��ݒ�
        virtual auto lbSetSelectedIndex(int newSelectedIndex)->void;
    };

    //�R���{�{�b�N�X
    class ComboBox : public Control
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        ComboBox(const ComboBox &) = delete;
        ComboBox &operator=(const ComboBox &) = delete;
        ComboBox() = default;
        virtual ~ComboBox() = default;
    public://����{
        //�E�B���h�E����
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    public://��{����
        //�A�C�e���ǉ�
        virtual auto cbAddItem(const tstring &newItem)->void;
        //�A�C�e���ύX
        virtual auto cbChangeItem(int itemIndex, const tstring &newItem)->void;
        //�A�C�e���폜
        virtual auto cbDeleteItem(int itemIndex)->void;
        //�S�A�C�e���폜
        virtual auto cbDeleteItems()->void;
        //�A�C�e���擾
        virtual auto cbGetItem(int itemIndex)->tstring;
        //�A�C�e�����擾
        virtual auto cbGetItemNum()->int;
        //�J�[�\���̈ʒu���擾
        virtual auto cbGetSelectedIndex()->int;
        //�A�C�e���}��
        virtual auto cbInsertItem(int itemIndex, const tstring &newItem)->void;
        //�J�[�\���̈ʒu��ݒ�
        virtual auto cbSetSelectedIndex(int newSelectedIndex)->void;
    };

    //�g���b�N�o�[(�X���C�_�[)
    class TrackBar : public Control
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        TrackBar(const TrackBar &) = delete;
        TrackBar &operator=(const TrackBar &) = delete;
        TrackBar() = default;
        virtual ~TrackBar() = default;
    public://����{
        //�E�B���h�E����
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    };

    //���l
    class Numeric : public Control
    {
    public://�萔
        static constexpr WORD Message_GotFocus = 0;
        static constexpr WORD Message_LostFocus = 1;
        static constexpr WORD Message_ValueChangeStarted = 2;
        static constexpr WORD Message_ValueChangeIsOver = 3;
        static constexpr WORD Message_ValueWasReset = 4;
        static constexpr WORD Message_ChangingValue = 5;
    public://�R���X�g���N�^�ƃf�X�g���N�^
        Numeric(const Numeric &) = delete;
        Numeric &operator=(const Numeric &) = delete;
        Numeric();
        virtual ~Numeric() = default;
    public://����{
        //�E�B���h�E����
        virtual auto create(const tstring &_text, int _x, int _y, int _width, int _height, Window *_parent, WORD id)->void override;
    public://��{����
        //���l�̎擾
        virtual auto nGetDefaultValue()->float;
        //���l�̎擾
        virtual auto nGetValue()->float;
        //���l�̐ݒ�
        virtual auto nSetDefaultValue(float newDefaultValue)->void;
        //���l�̐ݒ�
        virtual auto nSetValue(float newValue)->void;
    protected://�I�[�o�[���C�h����
        virtual auto onCreate()->LRESULT override;
        virtual auto onMouseMove(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onMouseLeave(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onLButtonDown(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onLButtonUP(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onLButtonDblClk(WPARAM wParam, LPARAM lParam)->LRESULT override;
        virtual auto onPaint(WPARAM wParam, LPARAM lParam)->LRESULT override;
    protected://�����o�[�ϐ�
        bool mouseOn;//�}�E�X����������Ă��邩
        bool changing;//�l�̕ύX��
        float defaultValue;//�K��l
        WORD mouseLastClickedX;//�}�E�X���N���b�N�����ʒu(X)
        WORD mouseLastClickedY;//�}�E�X���N���b�N�����ʒu(Y)
    };
}
