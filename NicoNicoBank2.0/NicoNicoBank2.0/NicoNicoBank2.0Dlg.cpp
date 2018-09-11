
// NICONICOBANK2.0Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "NICONICOBANK2.0.h"
#include "NICONICOBANK2.0Dlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "Logic.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 这个开成全局来保存当前登录的储蓄员
CString m_staffaccount = _T("未登录");
// 这个开成全局保存当前登录的用户
CString m_useraccount = _T("未登录");
// 记录当前系统的日期
int m_sysyear ;
// 记录系统的月份
int m_sysmonth ;
// 记录系统当前日子
int m_sysday ;
// 记录拼接好的时间
CString m_sysdate ;
//CString m_sysdate = _T( +"-" +  +"-"+);



//尝试着初始化
//m_sysyear = 2018;
//m_sysmonth = 9;
//m_sysday = 5;

//这个指针指向主菜单中关于储蓄员账户的按钮

//CButton *pBtn1 = (CButton *)GetDlgItem(IDC_staffchange);

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNICONICOBANK20Dlg 对话框



CNICONICOBANK20Dlg::CNICONICOBANK20Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NICONICOBANK20_DIALOG, pParent)

	//, m_staffaccount(_T(""))
	//, m_useraccount(_T(""))
	//, m_sysyear(0)
	//, m_sysmonth(0)
	//, m_sysday(0)
	//, m_sysdate(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNICONICOBANK20Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//  DDX_Text(pDX, IDC_staffpwd, staff);

	DDX_Text(pDX, IDC_staffaccount, m_staffaccount);
	DDX_Text(pDX, IDC_useraccount, m_useraccount);
	//DDX_Text(pDX, IDC_year, m_sysyear);
	//DDX_Text(pDX, IDC_month, m_sysmonth);
	//DDX_Text(pDX, IDC_day, m_sysday);
	DDX_Text(pDX, IDC_timedate, m_sysdate);
}

BEGIN_MESSAGE_MAP(CNICONICOBANK20Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_staffchange, &CNICONICOBANK20Dlg::OnBnClickedstaffchange)
	ON_BN_CLICKED(IDC_userchange, &CNICONICOBANK20Dlg::OnBnClickeduserchange)
	ON_BN_CLICKED(IDC_userlogout, &CNICONICOBANK20Dlg::OnBnClickeduserlogout)
	ON_BN_CLICKED(IDC_stafflogout, &CNICONICOBANK20Dlg::OnBnClickedstafflogout)
	ON_BN_CLICKED(IDC_deposit, &CNICONICOBANK20Dlg::OnBnClickeddeposit)
	ON_BN_CLICKED(IDC_withdrawal, &CNICONICOBANK20Dlg::OnBnClickedwithdrawal)

	ON_BN_CLICKED(IDC_depositinfo, &CNICONICOBANK20Dlg::OnBnClickeddepositinfo)
	ON_BN_CLICKED(IDC_withdrainfo, &CNICONICOBANK20Dlg::OnBnClickedwithdrainfo)
	ON_BN_CLICKED(IDC_timechange, &CNICONICOBANK20Dlg::OnBnClickedtimechange)
	ON_BN_CLICKED(IDC_BUTTON7, &CNICONICOBANK20Dlg::OnBnClickedButton7)

	ON_BN_CLICKED(IDC_openaccount, &CNICONICOBANK20Dlg::OnBnClickedopenaccount)
	ON_BN_CLICKED(IDC_reportloss, &CNICONICOBANK20Dlg::OnBnClickedreportloss)
	ON_BN_CLICKED(IDC_changeinfo, &CNICONICOBANK20Dlg::OnBnClickedchangeinfo)
	ON_BN_CLICKED(IDC_staffregist, &CNICONICOBANK20Dlg::OnBnClickedstaffregist)
	ON_BN_CLICKED(IDC_BUTTON4, &CNICONICOBANK20Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CNICONICOBANK20Dlg 消息处理程序

BOOL CNICONICOBANK20Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//默认未登录，故隐藏注销
	hidestafflogout();
	hideuserlogout();




	//用系统时间进行初始化试试
	//got it!
	CTime time = CTime::GetCurrentTime();
	//time.GetCurrentTime();
	/*CString stryear = time.Format("%Y");
	CString strmonth = time.Format("%m");
	CString strday = time.Format("%d");
	
	stryear.Format(_T("%d"), m_sysyear);
	strmonth.Format(_T("%d"), m_sysmonth);
	strday.Format(_T("%d"), m_sysday);
	m_sysyear = _ttoi(stryear);
	
	//m_sysyear = _ttoi(stryear);*/
	m_sysyear = time.GetYear();
	m_sysmonth = time.GetMonth();
	m_sysday = time.GetDay();
	CString syear;
	syear.Format(_T("%d"), m_sysyear);
	CString smonth;
	smonth.Format(_T("%d"), m_sysmonth);
	CString sday;
	sday.Format(_T("%d"), m_sysday);
	m_sysdate = syear + "-" + smonth + "-" + sday;
	UpdateData(FALSE);

	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNICONICOBANK20Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNICONICOBANK20Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNICONICOBANK20Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNICONICOBANK20Dlg::OnBnClickedstafflogin()
{
	// TODO: 在此添加控件通知处理程序代码


}


void CNICONICOBANK20Dlg::OnBnClickedstaffchange()
{
	//如果储蓄员未登录进入登录界面，如果储蓄员已登录进入切换界面
	CButton *pBtn1 = (CButton *)GetDlgItem(IDC_staffchange);
	if (m_staffaccount == _T("未登录"))
	{
		logindlg.m_logintitle = "储蓄员登录";
		logindlg.m_account = "";
		logindlg.m_pwd = "";
		if (logindlg.DoModal() == IDOK)
		{
			m_staffaccount = logindlg.m_account;
			UpdateData(FALSE);

			pBtn1->SetWindowText(_T("切换"));
			showstafflogout();
		}
	}
	else
	{
		logindlg.m_logintitle = "储蓄员账号切换";
		logindlg.m_account = "";
		logindlg.m_pwd = "";
		if (logindlg.DoModal() == IDOK)
		{
			showstafflogout();
		}
	}
	// TODO: 在此添加控件通知处理程序代码

}


void CNICONICOBANK20Dlg::OnBnClickeduserchange()
{
	if (m_staffaccount == _T("未登录"))
	{
		AfxMessageBox(_T("请先登录储蓄员账号!"));
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
	//如果用户未登录进入登录界面，如果用户已登录进入切换界面,但是，在这里应该还有账户注销的功能
	CButton *pBtn2 = (CButton *)GetDlgItem(IDC_userchange);
	if (m_useraccount == _T("未登录"))
	{
		logindlg.m_logintitle = "用户登录";
		logindlg.m_account = "";
		logindlg.m_pwd = "";
		if (logindlg.DoModal() == IDOK)
		{
			m_useraccount = logindlg.m_account;
			UpdateData(FALSE);

			pBtn2->SetWindowText(_T("切换"));
			showuserlogout();
		}
	}
	else
	{
		logindlg.m_logintitle = "用户账号切换";
		logindlg.m_account = "";
		logindlg.m_pwd = "";
		if (logindlg.DoModal() == IDOK)
		{
			showuserlogout();
		}
	}
}
//隐藏注销按钮
void CNICONICOBANK20Dlg::hidestafflogout()
{
	CButton *stafflogout = (CButton*)GetDlgItem(IDC_stafflogout);
	stafflogout->ShowWindow(FALSE);
}

void CNICONICOBANK20Dlg::hideuserlogout()
{
	CButton *userlogout = (CButton*)GetDlgItem(IDC_userlogout);
	userlogout->ShowWindow(FALSE);
}

//显示注销按钮
void CNICONICOBANK20Dlg::showstafflogout()
{
	CButton *stafflogout = (CButton*)GetDlgItem(IDC_stafflogout);
	stafflogout->ShowWindow(TRUE);

}

void CNICONICOBANK20Dlg::showuserlogout()
{

	CButton *userlogout = (CButton*)GetDlgItem(IDC_userlogout);
	userlogout->ShowWindow(TRUE);
}

//储蓄员账号注销
void CNICONICOBANK20Dlg::OnBnClickedstafflogout()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton *pBtn1 = (CButton *)GetDlgItem(IDC_staffchange);

	if (::MessageBox(NULL, _T("你确定要注销吗"), _T("注销页"), MB_OKCANCEL) == IDCANCEL)
	{
		/*m_staffaccount = _T("未登录");
		UpdateData(FALSE);
		AfxMessageBox(_T("注销成功！"));
		hidestafflogout();*/
		return;
	}
	else {
		m_staffaccount = _T("未登录");
		UpdateData(FALSE);
		pBtn1->SetWindowText(_T("登录"));
		hidestafflogout();
		AfxMessageBox(_T("注销成功！"));
		
	}

	
}


//用户账号注销
void CNICONICOBANK20Dlg::OnBnClickeduserlogout()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton *pBtn2 = (CButton *)GetDlgItem(IDC_userchange);
	if (::MessageBox(NULL, _T("你确定要注销吗"), _T("注销页"), MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}
	else {
		m_useraccount = _T("未登录");
		UpdateData(FALSE);
		pBtn2->SetWindowText(_T("登录"));
		hideuserlogout();
		AfxMessageBox(_T("注销成功！"));
		

	}
	
}

//点击该控件后应该先验证密码
void CNICONICOBANK20Dlg::OnBnClickeddeposit()
{
	// TODO: 在此添加控件通知处理程序代码
	//在进行存款前必须登录用户与储蓄员账号
	if (m_staffaccount == "未登录" || m_useraccount == "未登录")
	{
		AfxMessageBox(_T("请先登录!"));
		return;
	}
	depositdlg.m_damount = 0;
	depositdlg.m_dselect = -1;
	if (depositdlg.DoModal() == IDOK)
	{
	//	depositdlg.m_damount = 0;

		//显示当前的储蓄员等状态
		//UpdateData(FALSE);
	}
}



void CNICONICOBANK20Dlg::OnBnClickedwithdrawal()
{
	// TODO: 在此添加控件通知处理程序代码
		//在进行取款前必须登录用户与储蓄员账号
	if (m_staffaccount == "未登录" || m_useraccount == "未登录")
	{
		AfxMessageBox(_T("请先登录储蓄员与用户账户!"));
		return;
	}
	withdrawaldlg2.m_infotitle = "存款查询";
	if (withdrawaldlg2.DoModal() == IDOK)
	{
		

	}
}



void CNICONICOBANK20Dlg::OnBnClickeddepositinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_staffaccount == "未登录" || m_useraccount == "未登录")
	{
		AfxMessageBox(_T("请先登录!"));
		return;
	}
	withdrawaldlg2.m_infotitle = "存款信息查询";
	if (withdrawaldlg2.DoModal() == IDOK)
	{
		

	}
}


void CNICONICOBANK20Dlg::OnBnClickedwithdrainfo()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_staffaccount == "未登录" || m_useraccount == "未登录")
	{
		AfxMessageBox(_T("请先登录!"));
		return;
	}
	withdrawaldlg2.m_infotitle = "取款信息查询";
	if (withdrawaldlg2.DoModal() == IDOK)
	{
		

	}

}


void CNICONICOBANK20Dlg::OnBnClickedtimechange()
{
	// TODO: 在此添加控件通知处理程序代码
	if (datechange.DoModal() == IDOK)
	{
		int m_yearchange = datechange.m_yearchange;
		int m_monthchange = datechange.m_monthchange;
		int m_daychange = datechange.m_daychange;
		m_sysyear = m_yearchange;
		m_sysday = m_daychange;
		m_sysmonth = m_monthchange;
		CString syear;
		syear.Format(_T("%d"), m_sysyear);
		CString smonth;
		smonth.Format(_T("%d"), m_sysmonth);
		CString sday;
		sday.Format(_T("%d"), m_sysday);
		m_sysdate = syear + "-" + smonth + "-" + sday;
		UpdateData(FALSE);
	}
}

//系统清算和银行余额
void CNICONICOBANK20Dlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	if (duedlg.DoModal() == IDOK)
	{

	}
}



//开户
void CNICONICOBANK20Dlg::OnBnClickedopenaccount()
{
	openaccount.m_userpwd = "";
	openaccount.m_useraddress = "";
	openaccount.m_username = "";
	openaccount.m_idnumber = "";
	UpdateData(FALSE);
	// TODO: 在此添加控件通知处理程序代码
	if (openaccount.DoModal() == IDOK)
	{

	}
}

//账户挂失
void CNICONICOBANK20Dlg::OnBnClickedreportloss()
{
	// TODO: 在此添加控件通知处理程序代码
	Logic logic;
	reportloss.m_newpwd = "";
	CButton *pBtn2 = (CButton *)GetDlgItem(IDC_userchange);
	reportloss.m_cuseraccount = logic.getRandomAccount().c_str();
	if (reportloss.DoModal() == IDOK)
	{
		UpdateData(FALSE);
		pBtn2->SetWindowText(_T("登录"));
		hideuserlogout();
	}

}

//信息修改
void CNICONICOBANK20Dlg::OnBnClickedchangeinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_staffaccount == "未登录" || m_useraccount == "未登录")
	{
		AfxMessageBox(_T("请先登录!"));
	}
	else {
		infochange.m_newaddress = "";
		infochange.m_newpwd = "";
		infochange.m_oldpwd = "";
		if (infochange.DoModal() == IDOK)
		{

		}
	}
}

//注册储蓄员
void CNICONICOBANK20Dlg::OnBnClickedstaffregist()
{
	// TODO: 在此添加控件通知处理程序代码
	staffregist.m_account = "";
	staffregist.m_pwd = "";
	staffregist.m_name = "";
	if (staffregist.DoModal() == IDOK)
	{

	}
}


void CNICONICOBANK20Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (UserInfo.DoModal() == IDOK)
	{

	}
}
