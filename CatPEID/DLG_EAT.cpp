#include "stdafx.h"
#include "CatPEID.h"
#include "DLG_Eat.h"
#include "afxdialogex.h"


// DLG_Eat �Ի���

IMPLEMENT_DYNAMIC(DLG_Eat, CDialogEx)

DLG_Eat::DLG_Eat(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EAT, pParent)
{

}

DLG_Eat::~DLG_Eat()
{
}

void DLG_Eat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_Tree_Eat);
}


BEGIN_MESSAGE_MAP(DLG_Eat, CDialogEx)
END_MESSAGE_MAP()


// DLG_Eat ��Ϣ�������
