//�E�B���h�E�\����DirectX������
#include<Windows.h>
#include<tchar.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<vector>
#ifdef _DEBUG
#include<iostream>
#endif


#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

///@brief �R���\�[����ʂɃt�H�[�}�b�g�t���������\��
///@param format �t�H�[�}�b�g(%d�Ƃ�%f�Ƃ���)
///@param �ϒ�����
///@remarks���̊֐��̓f�o�b�O�p�ł��B�f�o�b�O���ɂ������삵�܂���
void DebugOutputFormatString(const char* format, ...) {
#ifdef _DEBUG
	va_list valist;
	va_start(valist, format);
	vprintf(format, valist);
	va_end(valist);
#endif
}

//�ʓ|�����Ǐ����Ȃ�������
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (msg == WM_DESTROY) {//�E�B���h�E���j�����ꂽ��Ă΂�܂�
		PostQuitMessage(0);//OS�ɑ΂��āu�������̃A�v���͏I�����v�Ɠ`����
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);//�K��̏������s��
}

const unsigned int window_width = 1280;
const unsigned int window_height = 720;


#ifdef _DEBUG
int main() {
#else
#include<Windows.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#endif
	DebugOutputFormatString("Show window test.");
	HINSTANCE hInst = GetModuleHandle(nullptr);
	//�E�B���h�E�N���X�������o�^
	WNDCLASSEX w = {};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProcedure;//�R�[���o�b�N�֐��̎w��
	w.lpszClassName = _T("DirectXTest");//�A�v���P�[�V�����N���X��(�K���ł����ł�)
	w.hInstance = GetModuleHandle(0);//�n���h���̎擾
	RegisterClassEx(&w);//�A�v���P�[�V�����N���X(���������̍�邩���낵������OS�ɗ\������)

	RECT wrc = { 0,0, window_width, window_height };//�E�B���h�E�T�C�Y�����߂�
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);//�E�B���h�E�̃T�C�Y�͂�����Ɩʓ|�Ȃ̂Ŋ֐����g���ĕ␳����
	//�E�B���h�E�I�u�W�F�N�g�̐���

	HWND hwnd = CreateWindow(w.lpszClassName,//�N���X���w��
		_T("DX12�e�X�g"),//�^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,//�^�C�g���o�[�Ƌ��E��������E�B���h�E�ł�
		CW_USEDEFAULT,//�\��X���W��OS�ɂ��C�����܂�
		CW_USEDEFAULT,//�\��Y���W��OS�ɂ��C�����܂�
		wrc.right - wrc.left,//�E�B���h�E��
		wrc.bottom - wrc.top,//�E�B���h�E��
		nullptr,//�e�E�B���h�E�n���h��
		nullptr,//���j���[�n���h��
		w.hInstance,//�Ăяo���A�v���P�[�V�����n���h��
		nullptr);//�ǉ��p�����[�^

	ShowWindow(hwnd, SW_SHOW);//�E�B���h�E�\��

	MSG msg = {};
	while (true) {

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//�����A�v���P�[�V�������I�����Ď���message��WM_QUIT�ɂȂ�
		if (msg.message == WM_QUIT) {
			break;
		}
	}
	//�����N���X�g��񂩂�o�^�������Ă�
	UnregisterClass(w.lpszClassName, w.hInstance);
	return 0;
}