
#if !defined(_SERIALCOMM32_H_INCLUDE_)
#define _SERIALCOMM32_H_INCLUDE_

#include "windows.h"
#include <string>
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef SERIALCOMM_EXPORTS
#define SERIALCOMM_API __declspec(dllexport)
#else
#define SERIALCOMM_API __declspec(dllimport)
#pragma comment(lib, "SerialComm.lib")
#pragma message("Automatically linking with SerialComm.dll")
#endif

#define EVT_BREAK		CE_BREAK		// �n�[�h�E�F�A���u���[�N���������o���܂����B 
#define EVT_DNS			CE_DNS			// Windows 95/98�F�p�������f�o�C�X���I������Ă��܂���B 
#define EVT_FRAME		CE_FRAME		// �n�[�h�E�F�A���t���[�~���O�G���[�����o���܂����B 
#define EVT_IOE			CE_IOE			// �f�o�C�X�Ƃ̒ʐM���� I/O �G���[���������܂����B 
#define EVT_MODE		CE_MODE			// �v���������[�h���T�|�[�g����Ă��܂���B�܂��́A�n���h���������ł��i ���̒l���w�肳�ꂽ�ꍇ�A���̃G���[�R�[�h�݂̂��L���l�ƂȂ�܂��j�B 
#define EVT_OOP			CE_OOP			// Windows 95/98�F�p�������f�o�C�X���p���؂�ɂȂ��Ă��܂��B 
#define EVT_OVERRUN		CE_OVERRUN		// �����o�b�t�@�������ς��ɂȂ�܂����B���̕����͎����܂��B 
#define EVT_PTO			CE_PTO			// Windows 95/98�F�p�������f�o�C�X�Ń^�C���A�E�g�ɂȂ�܂����B 
#define EVT_RXOVER		CE_RXOVER		// ���̓o�b�t�@�̃I�[�o�[�t���[���������܂����B���̓o�b�t�@�ɋ󂫂��Ȃ����AEOF �̌�ɕ�������M���܂����B 
#define EVT_RXPARITY	CE_RXPARITY		// �n�[�h�E�F�A���p���e�B�G���[�����o���܂����B 
#define EVT_TXFULL		CE_TXFULL		// �A�v���P�[�V�����������𑗐M���悤�Ƃ��܂������A�o�̓o�b�t�@�������ς��ł����B 
#define	EVT_DONEINIT	0x00010000		// �ʐM���W���[���̃C���X�^���X���������������܂����B
#define EVT_DONEOPEN	0x00020000		// ���W���[���̃I�[�v�����������܂����B
#define EVT_RXCHAR		0x00100000		// �f�[�^����M���܂����B
#define EVT_ERROR		0x00200000		// �ʐM�G���[���������܂����B

///////////////////////////////////////////////////////////////////////////////
// �R�[���o�b�N�֐�
///////////////////////////////////////////////////////////////////////////////
// �T�v:
// �ʐM���W���[������̃R�[���o�b�N�֐��ł��B
// ���������B�C�x���g�ʒm�ɂ͈ȉ��̂��̂�����܂��B
//		EVT_BREAK		�n�[�h�E�F�A���u���[�N���������o���܂����B 
//		EVT_DNS			Windows 95/98�F�p�������f�o�C�X���I������Ă��܂���B 
//		EVT_FRAME		�n�[�h�E�F�A���t���[�~���O�G���[�����o���܂����B 
//		EVT_IOE			�f�o�C�X�Ƃ̒ʐM���� I/O �G���[���������܂����B 
//		EVT_MODE		�v���������[�h���T�|�[�g����Ă��܂���B�܂��́A�n���h
//						���������ł��i ���̒l���w�肳�ꂽ�ꍇ�A���̃G���[�R�[
//						�h�݂̂��L���l�ƂȂ�܂��j�B 
//		EVT_OOP			Windows 95/98�F�p�������f�o�C�X���p���؂�ɂȂ��Ă��܂��B 
//		EVT_OVERRUN		�����o�b�t�@�������ς��ɂȂ�܂����B���̕����͎����܂��B 
//		EVT_PTO			Windows 95/98�F�p�������f�o�C�X�Ń^�C���A�E�g�ɂȂ�܂����B 
//		EVT_RXOVER		���̓o�b�t�@�̃I�[�o�[�t���[���������܂����B���̓o�b�t�@
//						�ɋ󂫂��Ȃ����AEOF �̌�ɕ�������M���܂����B 
//		EVT_RXPARITY	�n�[�h�E�F�A���p���e�B�G���[�����o���܂����B 
//		EVT_TXFULL		�A�v���P�[�V�����������𑗐M���悤�Ƃ��܂������A�o�̓o�b
//						�t�@�������ς��ł����B 
//		EVT_DONEINIT	�ʐM���W���[���̃C���X�^���X���������������܂����B
//		EVT_DONEOPEN	���W���[���̃I�[�v�����������܂����B
//		EVT_RXCHAR		�f�[�^����M���܂����B
//		EVT_ERROR		�ʐM�G���[���������܂����B
//
// �p�����[�^:
// UINT uEvent(O)�F�R�[���o�b�N�֐��̃C�x���g�ʒm
// WPARAM wParam(O)�F�����̂��߂ɗ\��
// LPARAM lParam1(O)�F�ʐM�n���h���l
// LPARAM lParam2(O)�F�����̂��߂ɗ\��
// LPARAM lParam3(O)�F�����̂��߂ɗ\��
//
// �߂�l�F
// ����ɏI�������ꍇ�́AHANDLE �^�̃n���h���l��Ԃ��܂��B
//
///////////////////////////////////////////////////////////////////////////////
typedef VOID (CALLBACK* LPFNCALLBACK)(UINT uEvent, WPARAM wParam, LPARAM lParam1, LPARAM lParam2, LPARAM lParam3);

//---------------------------------------------------------------------------
// The following is threads for the serial port watch.
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// ���W���[���̏�����
///////////////////////////////////////////////////////////////////////////////
// �T�v:
// ���W���[�������������܂��B���̃��W���[�����g�p����O�ɍŏ��ɂP��Ăяo����
// ���������B
//
// �p�����[�^:
// LPFNCALLBACK lpfnCallBackFn(I)�F�R�[���o�b�N�֐��̃A�h���X
// LPVOID lpArgument(I)�FNULL�i�����̂��߂ɗ\��j
//
// �߂�l�F
// ����ɏI�������ꍇ�́AHANDLE �^�̃n���h���l��Ԃ��܂��B
//
///////////////////////////////////////////////////////////////////////////////
SERIALCOMM_API HANDLE WINAPI rs232c_CreateSerial(LPFNCALLBACK lpfnCallBackFn, LPVOID lpArgument);

///////////////////////////////////////////////////////////////////////////////
// ���W���[���̏I������
///////////////////////////////////////////////////////////////////////////////
// �T�v:
// ���W���[�������\�[�X��������܂��B���̃��W���[���̎g�p���I�������P��Ăяo
// ���Ă��������B
//
// �p�����[�^:
// HANDLE hSerial(I)�F�ʐM�n���h��
//
// �߂�l�F
// ����ɏI�������ꍇ�́ATRUE ��Ԃ��܂��B
//
///////////////////////////////////////////////////////////////////////////////
SERIALCOMM_API BOOL WINAPI rs232c_DestroySerial(HANDLE hSerial);

///////////////////////////////////////////////////////////////////////////////
// �V���A�����W���[���̃I�[�v������
///////////////////////////////////////////////////////////////////////////////
// �T�v:
// �V���A�����W���[���̃I�[�v�������ł��BhSerial �ɂ͒ʐM�n���h�����w�肵�܂��B
// nPort �ɂ͒ʐM�f�o�C�X�̃|�[�g�ԍ����w�肵�Ă��������Bdcb �ɂ̓V���A���ʐM
// �f�o�C�X�� DCB �\���̂��w�肵�܂��BDCB �\���̂̏ڍׂɂ��Ă� Windows API 
// �̃��t�@�����X�iMSDN ���j���Q�Ƃ��Ă��������B���M����ю�M�̗����� XON ��
// ���iXonChar�j�� 0x11�B���M����ю�M�̗����� XOFF �����iXoffChar�j�� 0x13�B
// �܂��A�\�t�g�E�F�A�t���[����̍ő�ƍŏ��������� 100 �Őݒ肳���̂Œ���
// ���Ă��������i�ύX�s�j�B
//
// �p�����[�^:
// HANDLE hSerial(I)�F�ʐM�n���h��
// int nPort(I)�F�|�[�g�ԍ�
// DCB dcb(I)�FDCB �\����
//
// �߂�l�F
// ����ɏI�������ꍇ�́ATRUE ��Ԃ��܂��B
//
///////////////////////////////////////////////////////////////////////////////
SERIALCOMM_API BOOL WINAPI rs232c_OpenSerial(HANDLE hSerial, int nPort, DCB dcb);

///////////////////////////////////////////////////////////////////////////////
// �V���A�����W���[���̃N���[�Y����
///////////////////////////////////////////////////////////////////////////////
// �T�v:
// �V���A�����W���[���̃N���[�Y�����ł��BhSerial �ɂ͒ʐM�n���h�����w�肵�܂��B
//
// �p�����[�^:
// HANDLE hSerial(I)�F�ʐM�n���h��
//
// �߂�l�F
// ����ɏI�������ꍇ�́ATRUE ��Ԃ��܂��B
//
///////////////////////////////////////////////////////////////////////////////
SERIALCOMM_API BOOL WINAPI rs232c_CloseSerial(HANDLE hSerial);

///////////////////////////////////////////////////////////////////////////////
// �f�[�^���M
///////////////////////////////////////////////////////////////////////////////
// �T�v:
// �ʐM�|�[�g�ԍ��Ƀf�[�^���������݂܂��B���̊֐��́A�񓯊��̑����z�肵�Đ݌v
// ����Ă��܂��B�������݂���������ƁA�ʐM�|�[�g�Ɏ��ۂɏ������񂾃o�C�g������
// ���M����܂����A�񓯊���������̂��߁A���ۂɑ��M�����Ƃ͌���܂���B
//
// �p�����[�^:
// HANDLE hSerial(I)�F�ʐM�n���h��
// LPCTSTR lpBuffer(I)�F���M�f�[�^�o�b�t�@�̃|�C���^
// DWORD dwBytesToWrite(I)�F���M�f�[�^�o�C�g��
//
// �߂�l�F
// ���M�����o�C�g���B
//
///////////////////////////////////////////////////////////////////////////////
SERIALCOMM_API DWORD WINAPI rs232c_WriteCommBlock(HANDLE hSerial, LPCTSTR lpBuffer, DWORD dwBytesToWrite);

///////////////////////////////////////////////////////////////////////////////
// �f�[�^��M
///////////////////////////////////////////////////////////////////////////////
// �T�v:
// �ʐM�|�[�g����f�[�^��ǂݎ��܂��B���̊֐��́A�񓯊��̑����z�肵�Đ݌v��
// ��Ă��܂��B���̂��߁A�w�肳�ꂽ��M�f�[�^�o�C�g���Ǝ��ۂɎ�M���ꂽ�o�C�g��
// ���Ⴄ�ꍇ������܂��B
//
// �p�����[�^:
// HANDLE hSerial(I)�F�ʐM�n���h��
// LPTSTR lpBuffer(I)�F��M�f�[�^�o�b�t�@�̃|�C���^
// DWORD dwBytesToRead(I)�F��M�f�[�^�o�C�g��
//
// �߂�l�F
// ��M�����������B
//
///////////////////////////////////////////////////////////////////////////////
SERIALCOMM_API DWORD WINAPI rs232c_ReadCommBlock(HANDLE hSerial, LPTSTR lpBuffer, DWORD dwBytesToRead);

///////////////////////////////////////////////////////////////////////////////
// �X�e�[�^�X�̎擾
///////////////////////////////////////////////////////////////////////////////
// �T�v:
// �V���A�����W���[���̃X�e�[�^�X���擾���܂��B�X�e�[�^�X�ɂ͑���M�L���[�̃f�[
// �^�T�C�Y�A���f���̃X�e�[�^�X�����ꂼ��ݒ肵�܂��B
// lpModemStat �ɂ̓��f�����䃌�W�X�^�l�ŁA�ȉ��̒l�ɂȂ�܂��B
//		MS_CTS_ON�FCTS�i���M�j�M�����I���ł��B 
//		MS_DSR_ON�FDSR�i�f�[�^�Z�b�g���f�B�j�M�����I���ł��B 
//		MS_RING_ON�F�Ăяo���M�����I���ł��B 
//		MS_RLSD_ON�FRLSD�i��M���M�����o�j�M�����I���ł��B 
//
// �p�����[�^:
// HANDLE hSerial(I)�F�ʐM�n���h��
// LPDWORD lpInQueSize(O)�F��M�L���[�f�[�^�T�C�Y
// LPDWORD lpOutQueSize(O)�F���M�L���[�f�[�^�T�C�Y
// LPDWORD lpModemStat(O)�F���f���̃X�e�[�^�X
//
// �߂�l�F
// ����ɏI�������ꍇ�́ATRUE ��Ԃ��܂��B
//
///////////////////////////////////////////////////////////////////////////////
SERIALCOMM_API BOOL WINAPI rs232c_GetCommStatus(HANDLE hSerial, LPDWORD lpInQueSize, LPDWORD lpOutQueSize, LPDWORD lpModemStat);

///////////////////////////////////////////////////////////////////////////////
// ����M�f�[�^�̔j��
///////////////////////////////////////////////////////////////////////////////
// �T�v:
// �o�̓o�b�t�@�܂��͓��̓o�b�t�@�ɂ��邷�ׂĂ̕�����j�����܂��B�������̓ǂݎ�
// �葀��܂��͏������ݑ���𒆎~���邱�Ƃ��ł��܂��B
//
// �p�����[�^:
// HANDLE hSerial(I)�F�ʐM�n���h��
//
// �߂�l�F
// ����ɏI�������ꍇ�́ATRUE ��Ԃ��܂��B
//
///////////////////////////////////////////////////////////////////////////////
SERIALCOMM_API void WINAPI rs232c_FlushComm(HANDLE hSerial);

#endif // !defined(_SERIALCOMM32_H_INCLUDE_
