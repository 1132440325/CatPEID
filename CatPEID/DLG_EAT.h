#pragma once
#include "afxcmn.h"
// DLG_Eat �Ի���

class DLG_Eat : public CDialogEx
{
	DECLARE_DYNAMIC(DLG_Eat)

public:
	DLG_Eat(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DLG_Eat();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EAT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_Tree_Eat;
};
