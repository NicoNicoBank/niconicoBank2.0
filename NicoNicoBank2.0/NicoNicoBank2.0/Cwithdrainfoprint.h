#pragma once


// Cwithdrainfoprint 对话框

class Cwithdrainfoprint : public CDialogEx
{
	DECLARE_DYNAMIC(Cwithdrainfoprint)

public:
	Cwithdrainfoprint(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cwithdrainfoprint();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WITHDRAINFOPRINT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_username;
	double withdramoney;
	CString m_withdradate;
	double m_profit;
	double m_principal;
	CString m_begindate;
	CString m_type;
};
