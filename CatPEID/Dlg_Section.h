#pragma once
#include "afxcmn.h"


// Dlg_Section �Ի���

class DLG_Section : public CDialogEx
{
	DECLARE_DYNAMIC(DLG_Section)

public:
	DLG_Section(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DLG_Section();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SECTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List_Section;
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
};
