
// PEDlg.h : ͷ�ļ�
//

#pragma once
#include "CommonDef.h"

#define WM_Login_Finish (WM_USER+100)

// PEDlg �Ի���
class PEDlg : public CDialogEx
{
// ����
public:
	PEDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogout();
	afx_msg void OnBnClickedLogin();
	afx_msg LRESULT OnLoginThreadFinish(WPARAM wParam, LPARAM lParam);
	static void LoginThread(void* arg);
private:
	Account m_Account;
	static int mMinites;
};
