
// CatPEID.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCatPEIDApp: 
// �йش����ʵ�֣������ CatPEID.cpp
//

class CCatPEIDApp : public CWinApp
{
public:
	CCatPEIDApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCatPEIDApp theApp;