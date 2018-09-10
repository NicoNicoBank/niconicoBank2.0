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
extern int m_sysyear;
extern int m_sysmonth;
extern int m_sysday;


CString types[6] = { _T("活期存款"),_T("三个月"),_T("六个月"),_T("一年"),_T("二年"),_T("三年") };

IMPLEMENT_DYNAMIC(CwithdrawalDlg2, CDialogEx)

CwithdrawalDlg2::CwithdrawalDlg2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WITHDRAWAL2, pParent)
	, m_sysdate2(_T(""))
	, m_infotitle(_T(""))
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
	DDX_Text(pDX, IDC_timedate, m_sysdate2);
	DDX_Text(pDX, IDC_infotitle, m_infotitle);
}


BEGIN_MESSAGE_MAP(CwithdrawalDlg2, CDialogEx)

	ON_NOTIFY(NM_CLICK, IDC_withdralist, &CwithdrawalDlg2::OnNMClickwithdralist)
	ON_BN_CLICKED(IDOK, &CwithdrawalDlg2::OnBnClickedOk)
END_MESSAGE_MAP()


// CwithdrawalDlg2 消息处理程序

vector <int> id;
BOOL CwithdrawalDlg2::OnInitDialog()
{

	//初始化时间
	CString year3;
	CString month3;
	CString day3;
	year3.Format(_T("%d"), m_sysyear);
	month3.Format(_T("%d"), m_sysmonth);
	day3.Format(_T("%d"), m_sysday);
	m_sysdate2 = year3 + "-" + month3 + "-" + day3;
	UpdateData(FALSE);
	//初始化listbox
	//UpdateData(TRUE);
	if (m_infotitle == "存款信息查询" || m_infotitle == "存款查询")
	{

		//初始化表头
		m_withdrabox.InsertColumn(0, _T("单号"), LVCFMT_LEFT, 100);
		m_withdrabox.InsertColumn(1, _T("储种"), LVCFMT_LEFT, 100);
		m_withdrabox.InsertColumn(2, _T("本金"), LVCFMT_LEFT, 100);
		m_withdrabox.InsertColumn(3, _T("存款日期"), LVCFMT_LEFT, 150);
		//m_withdrabox.InsertColumn(4, _T("单号"), LVCFMT_CENTER, 100);
		//设置风格
		DWORD dwstyle = m_withdrabox.GetExtendedStyle();
		dwstyle |= LVS_EX_FULLROWSELECT;
		m_withdrabox.SetExtendedStyle(dwstyle);

		//初始化列表
		//先清空
		m_withdrabox.DeleteAllItems();

		//std::string _daccount(CW2A(m_daccount.GetString()));
		std::string _useraccount(CW2A(m_useraccount.GetString()));
		//bool userDepositDetail(string account, vector <int> & id, vector <int> & type, vector <double> & principal, vector <Date> & date);
		//m_withdrabox.InsertItem(0, id[i]);
		Logic logic;
		//vector<int> id;
		id.clear();
		vector <int> type;
		vector <double> principal;
		vector <Date> date2; //公用
		if (logic.userDepositDetail(_useraccount, id, type, principal, date2))
		{

			
			size_t idlen = id.size();
			for (size_t i = 0; i < idlen; i++) {
				//m_withdrabox.InsertItem(i, id[i]);
				CString str;
				str.Format(_T("%d"), id[i]);
				m_withdrabox.InsertItem(i, str);
				//type转换
				int t = type[i];
				m_withdrabox.SetItemText(i, 1, types[t]);

				//principal转换
				CString strp;
				strp.Format(_T("%.2lf"), principal[i]);
				m_withdrabox.SetItemText(i, 2, strp);
				//date转化加拼接
				int year2 = date2[i].get(0);
				int month2 = date2[i].get(1);
				int day2 = date2[i].get(2);
				CString year3;
				CString month3;
				CString day3;
				CString date;
				year3.Format(_T("%d"), year2);
				month3.Format(_T("%d"), month2);
				day3.Format(_T("%d"), day2);
				date = year3 + "-" + month3 + "-" + day3;
				m_withdrabox.SetItemText(i, 3, date);



			}
		}
	}
	else if (m_infotitle == "取款信息查询")
	{
		//AfxMessageBox(_T("取款啦!"));
		//初始化表头
		//m_withdrabox.InsertColumn(0, _T("单号"), LVCFMT_LEFT, 100);
		//m_withdrabox.InsertColumn(1, _T("储种"), LVCFMT_CENTER, 100);
		m_withdrabox.InsertColumn(0, _T("取款单号"), LVCFMT_LEFT, 100);
		m_withdrabox.InsertColumn(1, _T("储蓄员工号"), LVCFMT_LEFT, 100);
		m_withdrabox.InsertColumn(2, _T("日期"), LVCFMT_LEFT, 150);
		m_withdrabox.InsertColumn(3, _T("取款金额"), LVCFMT_LEFT, 100);
		

		//设置风格
		DWORD dwstyle = m_withdrabox.GetExtendedStyle();
		dwstyle |= LVS_EX_FULLROWSELECT;
		m_withdrabox.SetExtendedStyle(dwstyle);

		//初始化列表
		//先清空
		m_withdrabox.DeleteAllItems();

		//std::string _daccount(CW2A(m_daccount.GetString()));
		std::string _useraccount(CW2A(m_useraccount.GetString()));
		//bool userWithDrawDetail(string account, vector <Date> & date, vector <double>& money);
		//m_withdrabox.InsertItem(0, id[i]);
		Logic logic;
		vector <Date> date2; //公用
		vector <double> money;
		vector <string> staffAccount;
		vector <int> depositID;
		if (logic.userWithDrawDetail(_useraccount, date2, money, staffAccount, depositID))
		{
			
			//size_t len = vec.size();
			size_t mlen = money.size();

			for (size_t i = 0; i < mlen; i++) {
				CString str;
				m_withdrabox.InsertItem(i, str);
				
				CString temp;
				temp.Format(_T("%d"), depositID[i]);
				m_withdrabox.SetItemText(i, 0, temp);
				temp = staffAccount[i].c_str();
				m_withdrabox.SetItemText(i, 1, temp);
				//date转化加拼接
				int year2 = date2[i].get(0);
				int month2 = date2[i].get(1);
				int day2 = date2[i].get(2);
				string date = to_string(date2[i].get(0)) + "-" + to_string(date2[i].get(1)) + "-" + to_string(date2[i].get(2));
				temp = date.c_str();
				m_withdrabox.SetItemText(i, 2, temp);
				//principal转换
				temp.Format(_T("%.2lf"), money[i]);
				m_withdrabox.SetItemText(i, 3, temp);
				
			}
		
		}
		else {
			AfxMessageBox(_T("出现系统错误,请检查软件配置"));
		}
	}
	return TRUE;

}




void CwithdrawalDlg2::OnNMClickwithdralist(NMHDR *pNMHDR, LRESULT *pResult)
{
	Logic logic;
	//vector<int> id;
	vector <int> type;
	vector <double> principal;
	vector <Date> date2; //公用
	if (m_infotitle == "存款查询")
	{
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		// TODO: 在此添加控件通知处理程序代码
		//获取第一个点击的条目
		CString select_withdra;
		int nId;
		//首先得到点击的位置
		POSITION pos = m_withdrabox.GetFirstSelectedItemPosition();
		if (pos == NULL)
		{
			//AfxMessageBox(_T("请至少选择一项", "提示", MB_ICONEXCLAMATION);
			return;
		}
		//得到行号，通过POSITION转化
		nId = (int)m_withdrabox.GetNextSelectedItem(pos);
		select_withdra.Format(_T("%d"), nId);
		std::string _useraccount(CW2A(m_useraccount.GetString()));
		//bool drawMoney(string account, int id, double money, string & error, const Date & now);
		//储存错误信息
		

		string error_withdra;
		Date sysdate;
		sysdate.setDate(m_sysyear, m_sysmonth, m_sysday);
		CString m_userpwd;
		//储存取款的利息和取款金额
		double withdraamount;
		double withdraprofit;
		checkinfo.m_userpwd = "";
		checkinfo.m_withdraamount = 0;
		if (checkinfo.DoModal()== IDOK)
		{
			m_userpwd = checkinfo.m_userpwd;
			withdraamount = checkinfo.m_withdraamount;

		std::string _pwd(CW2A(m_userpwd.GetString()));
		std::string _account(CW2A(m_useraccount.GetString()));
		//先进行登录的验证
		if (logic.verifyUser(_account, _pwd))
		{
			//AfxMessageBox(_T("用户登录成功！"));

			//将主页的登录改成切换


			//CDialog::OnOK();

			//CDialogEx::OnOK();
			int error;
			string staffAccountTemp(CW2A(m_staffaccount.GetString()));
			double profit_t;
			string saveDate_t;
			int type_t;
			//string account, int id, double money,const Date & now, string staffAccount, double & profit,string & saveDate, int & type
			error = logic.drawMoney(_useraccount, id[nId], withdraamount,sysdate, staffAccountTemp, profit_t, saveDate_t, type_t);
			if (!error)
			{
				CString profit;
				//profit.Format(_T("%.2lf"), withdraprofit);
				AfxMessageBox(_T("取款成功!"));
				withdrainfoprint.m_username = m_useraccount;
				withdrainfoprint.withdramoney = withdraamount + profit_t;
				withdrainfoprint.m_withdradate = sysdate.formatOut().c_str();
				withdrainfoprint.m_profit = profit_t;
				withdrainfoprint.m_principal = withdraamount;
				withdrainfoprint.m_begindate = saveDate_t.c_str();
				string temp;
				switch (type_t) {
				case 0: temp = "活期"; break;
				case 3: temp = "三个月"; break;
				case 6: temp = "半年"; break;
				case 12: temp = "一年"; break;
				case 24: temp = "两年"; break;
				case 36: temp = "三年"; break;
				}
				withdrainfoprint.m_type = temp.c_str();
				UpdateData(FALSE);
				if (withdrainfoprint.DoModal() == IDOK)
				{
					//接下来打印取款信息清单
					// 用户名， 取款，取款日期, 利息，存入时间，存款类型
					/*	DDX_Text(pDX, IDC_username, m_username);
					DDX_Text(pDX, IDC_withdramoney, withdramoney);
					DDX_Text(pDX, IDC_withdradate, m_withdradate);
					DDX_Text(pDX, IDC_profit, m_profit);
					DDX_Text(pDX, IDC_principal, m_principal);
					DDX_Text(pDX, IDC_begindate, m_begindate);
					DDX_Text(pDX, IDC_type, m_type);
					DDX_Text(pDX, IDC_useraccount, m_useraccount);*/
					//bool userDepositDetail(string account, vector <int> & id, vector <int> & type, vector <double> & principal, vector <Date> & date);

					if (logic.userDepositDetail(_useraccount, id, type, principal, date2))
					{
	
						//为取款工单赋值
						
						/*withdrainfoprint.m_principal = principal[nId];
						int typeselect = type[nId];
						withdrainfoprint.m_type = types[typeselect];
						int year2 = date2[nId].get(0);
						int month2 = date2[nId].get(1);
						int day2 = date2[nId].get(2);
						CString year3;
						CString month3;
						CString day3;
						year3.Format(_T("%d"), year2);
						month3.Format(_T("%d"), month2);
						day3.Format(_T("%d"), day2);
						withdrainfoprint.m_begindate = year3 + "-" + month3 + "-" + day3;
						
						CString year4;
						CString month4;
						CString day4;
						year4.Format(_T("%d"), m_sysyear);
						month4.Format(_T("%d"), m_sysmonth);
						day4.Format(_T("%d"), m_sysday);
						m_sysdate2 = year4 + "-" + month4 + "-" + day4;
						withdrainfoprint.m_withdradate = year4 + "-" + month4 + "-" + day4;
						UpdateData(FALSE);
						*/
					}
					

				}
				CDialog::OnOK();
				
				//UpdateWindow();
			}
			else
			{
				/*
					取款,若返回值:
					0: 取款成功
					1: 则说明无法取款，定期已经取过一次;
					2: 金额超过存款数 或 金额小于0
					3: 无法取全额，未到期
					*/
		
				//error.Format(_T("%s"), error_withdra.c_str());
				int error2 = error;
				switch (error2)
				{
				//case 0:AfxMessageBox(_T("取款成功"));
				case 1:AfxMessageBox(_T("无法取款，定期已经取过一次！"));break;
				case 2:AfxMessageBox(_T("金额超限!"));break;
				case 3:AfxMessageBox(_T("无法取全额，未到期!"));break;
				}
				//AfxMessageBox(error);
			}
		}
		else {
			AfxMessageBox(_T("账号或密码错误!"));
		}

		}
	}
	*pResult = 0;
}


void CwithdrawalDlg2::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
