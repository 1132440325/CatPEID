// Dlg_Section.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CatPEID.h"
#include "Dlg_Section.h"
#include "afxdialogex.h"


// Dlg_Section �Ի���

IMPLEMENT_DYNAMIC(DLG_Section, CDialogEx)

DLG_Section::DLG_Section(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SECTION, pParent)
{

}

DLG_Section::~DLG_Section()
{
}

void DLG_Section::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List_Section);
}


BEGIN_MESSAGE_MAP(DLG_Section, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Dlg_Section ��Ϣ�������


BOOL DLG_Section::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


BOOL DLG_Section::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return CDialogEx::OnEraseBkgnd(pDC);
}


void DLG_Section::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
}
