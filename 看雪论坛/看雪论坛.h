
// ��ѩ��̳.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// PEApp:
// �йش����ʵ�֣������ ��ѩ��̳.cpp
//

class PEApp : public CWinApp
{
public:
	PEApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern PEApp theApp;