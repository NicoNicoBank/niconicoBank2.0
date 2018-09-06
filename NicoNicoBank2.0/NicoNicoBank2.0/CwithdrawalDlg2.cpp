// CwithdrawalDlg2.cpp: 实现文件
//

#include "stdafx.h"
#include "NicoNicoBank2.0.h"
#include "CwithdrawalDlg2.h"
#include "afxdialogex.h"
#include "Date.h"
#include <vector>
#include "Logic.h"


// CwithdrawalDlg2 对话框
extern CString m_staffaccount;
extern CString m_useraccount;

IMPLEMENT_DYNAMIC(CwithdrawalDlg2, CDialogEx)

CwithdrawalDlg2::CwithdrawalDlg2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WITHDRAWAL2, pParent)
{

}

CwithdrawalDlg2::~CwithdrawalDlg2()
{
}

void CwithdrawalDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_withdralist, m_withdrabox);
	DDX_Text(pDX, IDC_staffaccount, m_staffaccount);
	DDX_Text(pDX, IDC_useraccount, m_useraccount);
	DDX_Control(pDX, IDC_withdralist, m_withdrabox);
}


BEGIN_MESSAGE_MAP(CwithdrawalDlg2, CDialogEx)
END_MESSAGE_MAP()


// CwithdrawalDlg2 消息处理程序
BOOL CwithdrawalDlg2::OnInitDialog()
{
	UpdateData(FALSE);
	//初始化listbox
	//初始化表头
	m_withdrabox.InsertColumn(0, _T("单号"), LVCFMT_CENTER, 150);
	m_withdrabox.InsertColumn(1, _T("储种"), LVCFMT_CENTER, 100);
	m_withdrabox.InsertColumn(2, _T("本金"), LVCFMT_CENTER, 150);
	m_withdrabox.InsertColumn(3, _T("日期"), LVCFMT_CENTER, 150);
	//m_withdrabox.InsertColumn(4, _T("单号"), LVCFMT_CENTER, 100);
	//设置风格
	DWORD dwstyle = m_withdrabox.GetExtendedStyle();
	dwstyle |= LVS_EX_FULLROWSELECT;
	m_withdrabox.SetExtendedStyle(dwstyle);

	//初始化列表
	Logic logic;
	vector<int> id;
	vector <int> type;
	vector <double> principal;
	vector <Date> date2;
	//std::string _daccount(CW2A(m_daccount.GetString()));
	std::string _useraccount(CW2A(m_useraccount.GetString()));
	//bool userDepositDetail(string account, vector <int> & id, vector <int> & type, vector <double> & principal, vector <Date> & date);
	//m_withdrabox.InsertItem(0, id[i]);
	if (logic.userDepositDetail(_useraccount, id, type, principal, date2))
	{
		//size_t len = vec.size();
		size_t idlen = id.size();
		vector<CString>str(10);
		//CString str[];
		for (size_t i = 0; i < idlen; i++) {
			//m_withdrabox.InsertItem(i, id[i]);
			//int d = vec[i];


			str[i].Format(_T("%d"), id[i]);
			m_withdrabox.InsertItem(i, str[i]);
		}
	}
	return TRUE;

}