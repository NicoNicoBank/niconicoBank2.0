// CdepositDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "NicoNicoBank2.0.h"
#include "CdepositDlg.h"
#include "afxdialogex.h"
#include "Logic.h"
#include "Date.h"
#include "NICONICOBANK2.0Dlg.h"
#include <vector>
#include "Func.h"

// CdepositDlg 对话框
extern CString m_staffaccount;
extern CString m_useraccount;
extern int m_sysyear;
extern int m_sysmonth;
extern int m_sysday;

IMPLEMENT_DYNAMIC(CdepositDlg, CDialogEx)

CdepositDlg::CdepositDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEPOSIT, pParent)
	, m_dselect(-1)
	, m_sysdate3(_T(""))
{

}

CdepositDlg::~CdepositDlg()
{

}
void CdepositDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_damount, m_damount);
	DDX_Radio(pDX, IDC_RADIO1, m_dselect);
	DDX_Text(pDX, IDC_staffaccount, m_staffaccount);
	DDX_Text(pDX, IDC_useraccount, m_useraccount);
	//DDX_Text(pDX, IDC_year, m_sysyear);
	//DDX_Text(pDX, IDC_month, m_sysmonth);
	//DDX_Text(pDX, IDC_day, m_sysday);

	DDX_Text(pDX, IDC_timedate, m_sysdate3);
}


BEGIN_MESSAGE_MAP(CdepositDlg, CDialogEx)
	
	ON_BN_CLICKED(IDOK, &CdepositDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CdepositDlg 消息处理程序


BOOL CdepositDlg::OnInitDialog()
{
	//初始化时间
	CString year3;
	CString month3;
	CString day3;
	year3.Format(_T("%d"), m_sysyear);
	month3.Format(_T("%d"), m_sysmonth);
	day3.Format(_T("%d"), m_sysday);
	m_sysdate3 = year3 + "-" + month3 + "-" + day3;
	UpdateData(FALSE);
	return TRUE;
}

void CdepositDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_damount == 0 || m_dselect == -1)
	{
		AfxMessageBox(_T("不能留有空白项！"));
		return;
	}
	else
	{
		Logic logic;
		Date date;
		Func func;
		date.setDate(m_sysyear, m_sysmonth, m_sysday);
		//std::string _daccount(CW2A(m_daccount.GetString()));
		std::string _useraccount(CW2A(m_useraccount.GetString()));
		string staffAccountTemp(CW2A(m_staffaccount.GetString()));
		if (logic.saveMoney(_useraccount, m_dselect, m_damount, date, staffAccountTemp))
		{
			AfxMessageBox(_T("存款成功"));
			//接下来打印存款信息
			/*vector<int> id;
			vector <int> type;
			vector <double> principal;
			vector <Date> date2;
			if (logic.userDepositDetail(_useraccount, id, type, principal, date2))
			{

			}*/

		}
		
	}

	CDialogEx::OnOK();
}
