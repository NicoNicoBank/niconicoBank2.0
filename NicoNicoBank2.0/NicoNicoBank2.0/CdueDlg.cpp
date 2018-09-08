// CdueDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "NicoNicoBank2.0.h"
#include "CdueDlg.h"
#include "afxdialogex.h"
#include "Logic.h"
#include "Date.h"


extern int m_sysyear;
extern int m_sysmonth;
extern int m_sysday;

// CdueDlg 对话框

IMPLEMENT_DYNAMIC(CdueDlg, CDialogEx)

CdueDlg::CdueDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DUEDLG, pParent)
	, m_duetoday(0)
	, m_duetomorrow(0)
	, m_dueafter(0)
	, m_bankbalance(0)
	
{

}

CdueDlg::~CdueDlg()
{
}

void CdueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_duetoday, m_duetoday);
	DDX_Text(pDX, IDC_duetomorrow, m_duetomorrow);
	DDX_Text(pDX, IDC_dueafter, m_dueafter);
	DDX_Text(pDX, IDC_timedate, m_sysdate);
	//  DDX_Text(pDX, IDC_bankbalance, m_bankbalance);
	DDX_Text(pDX, IDC_bankbalance, m_bankbalance);
}


BEGIN_MESSAGE_MAP(CdueDlg, CDialogEx)
END_MESSAGE_MAP()


// CdueDlg 消息处理程序
BOOL CdueDlg::OnInitDialog()
{
	//初始化时间
	CString year3;
	CString month3;
	CString day3;
	year3.Format(_T("%d"), m_sysyear);
	month3.Format(_T("%d"), m_sysmonth);
	day3.Format(_T("%d"), m_sysday);
	m_sysdate = year3 + "-" + month3 + "-" + day3;

	//获取到期的储金数
	//double getMoneyNeed(const Date & now);
	Logic logic;
	Date date1;
	Date date2;
	Date date3;
	date1.setDate(m_sysyear, m_sysmonth, m_sysday);
	date2.setDate(m_sysyear, m_sysmonth, m_sysday+1);
	date3.setDate(m_sysyear, m_sysmonth, m_sysday+2);
	m_duetoday = logic.getMoneyNeed(date1);
	m_duetomorrow = logic.getMoneyNeed(date2);
	m_dueafter = logic.getMoneyNeed(date3);

	//返回银行的余额


	//m_bankbalance = logic.getAllPrincipal();
	//double getAllPrincipal();

	UpdateData(FALSE);
	return TRUE;
}