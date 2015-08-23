
// PEDlg.h : 头文件
//

#pragma once
#include "CommonDef.h"

#define WM_Login_Finish (WM_USER+100)

// PEDlg 对话框
class PEDlg : public CDialogEx
{
// 构造
public:
	PEDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
