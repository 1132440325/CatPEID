// DLG_IAT.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CatPEID.h"
#include "DLG_IAT.h"
#include "afxdialogex.h"


// DLG_IAT �Ի���

IMPLEMENT_DYNAMIC(DLG_IAT, CDialogEx)

DLG_IAT::DLG_IAT(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IAT, pParent)
{

}

DLG_IAT::~DLG_IAT()
{
}

void DLG_IAT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_Tree_Iat);
}


BEGIN_MESSAGE_MAP(DLG_IAT, CDialogEx)
END_MESSAGE_MAP()


// DLG_IAT ��Ϣ�������
