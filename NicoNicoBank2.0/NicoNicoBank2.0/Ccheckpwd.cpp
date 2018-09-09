// Ccheckpwd.cpp: 实现文件
//

#include "stdafx.h"
#include "NicoNicoBank2.0.h"
#include "Ccheckpwd.h"
#include "afxdialogex.h"


// Ccheckpwd 对话框

IMPLEMENT_DYNAMIC(Ccheckpwd, CDialogEx)

Ccheckpwd::Ccheckpwd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHECKPWD, pParent)
	, m_pwd(_T(""))
{

}

Ccheckpwd::~Ccheckpwd()
{
}

void Ccheckpwd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_pwd, m_pwd);
}


BEGIN_MESSAGE_MAP(Ccheckpwd, CDialogEx)
END_MESSAGE_MAP()


// Ccheckpwd 消息处理程序
