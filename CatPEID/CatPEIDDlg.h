
// CatPEIDDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "Dlg_Section.h"
#include "DLG_IAT.h"
#include "DLG_EAT.h"

// CCatPEIDDlg �Ի���
class CCatPEIDDlg : public CDialogEx
{
// ����
public:
	CCatPEIDDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CATPEID_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CString m_EditStrFilePath;
	afx_msg void OnBnClickedButton1();
	void OnFileGet(CString Path);
	CString m_EditStrLog;
	void AppendLog(CString Text);
	void AppendLog(LPSTR Text);
	CTabCtrl m_Tab;

	DLG_Section m_Dlg_Section;
	DLG_IAT m_Dlg_Iat;
	DLG_Eat m_Dlg_Eat;
	afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);
	DWORD RAV2RAW(DWORD Rav);
};
