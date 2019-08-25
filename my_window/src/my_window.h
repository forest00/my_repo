//file:my_window.h
//date:2019/08/25
//auther:forest00
//�E�B���h�E�̈���������N���X�Q�ł�
//�E�B���h�E�N���X�͂��̖��̒ʂ�A�E�B���h�E�̕��ނ�\�����̂��Ɨ���

#pragma once
#include "tstring.h"
#include <Windows.h>

namespace myWindow
{
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
        //�E�B���h�E�����֐�(CreateWindowEx)�̃��b�p�[�֐��ł�
        //������g�����_�́A�������Ƒ�O������tstring�ɂȂ��Ă��邱�Ƃł�(���ƃ}�N������Ȃ��B������ˁI)
        static auto createWindow(
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
        )->HWND;
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
        //Visible�擾
        virtual auto getVisible()const->bool;
        //Enable�擾
        virtual auto getEnable()const->bool;
        //Text�擾
        virtual auto getText()const->tstring;
        //Position�擾
        virtual auto getPosition()const->POINT;
        //Visible�ݒ�
        virtual auto setVisible(bool newVisible)->void;
        //Enable�ݒ�
        virtual auto setEnable(bool newEnable)->void;
        //Text�ݒ�
        virtual auto setText(const tstring &newText)->void;
        //Position�ݒ�
        virtual auto setPosition(POINT newPosition)->void;
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
        WindowWithControls();
        ~WindowWithControls();
    protected://�I�[�o�[���C�h����
        virtual auto onCommand(WPARAM wParam, LPARAM lParam)->LRESULT override;
    };

    //�R���g���[�����N���X
    class Control : public Window
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        Control(const Control &) = delete;
        Control &operator=(const Control &) = delete;
        Control();
        ~Control();
    public://�I�[�o�[���C�h����
        virtual auto onControllCommand(WORD code, WORD id)->LRESULT = 0;
    };

    //�{�^��
    class Button : public Control
    {
    public://�R���X�g���N�^�ƃf�X�g���N�^
        Button(const Button &) = delete;
        Button &operator=(const Button &) = delete;
        Button();
        ~Button();
    public://����{
        //�E�B���h�E����
        virtual auto create(const tstring &_caption, int _x, int _y, int _width, int _height, Window *_parent)->void;
    protected://�I�[�o�[���C�h����
        virtual auto onControllCommand(WORD code, WORD id)->LRESULT override;
    public://�����o�[�ϐ�
        void (*onClick)(Button *button);
    };
}
