// Cdepositinfoprint.cpp: 实现文件
//

#include "stdafx.h"
#include "NicoNicoBank2.0.h"
#include "Cdepositinfoprint.h"
#include "afxdialogex.h"


// Cdepositinfoprint 对话框

IMPLEMENT_DYNAMIC(Cdepositinfoprint, CDialogEx)

Cdepositinfoprint::Cdepositinfoprint(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEPOSITINFOPRINT, pParent)
{

}

Cdepositinfoprint::~Cdepositinfoprint()
{
}

void Cdepositinfoprint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Cdepositinfoprint, CDialogEx)

END_MESSAGE_MAP()


// Cdepositinfoprint 消息处理程序


