#pragma once
#include "afxcmn.h"


// DLG_IAT �Ի���

class DLG_IAT : public CDialogEx
{
	DECLARE_DYNAMIC(DLG_IAT)

public:
	DLG_IAT(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DLG_IAT();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IAT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_Tree_Iat;
};
