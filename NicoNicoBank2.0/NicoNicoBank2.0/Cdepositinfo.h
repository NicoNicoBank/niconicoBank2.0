#pragma once


// Cdepositinfo 对话框

class Cdepositinfo : public CDialogEx
{
	DECLARE_DYNAMIC(Cdepositinfo)

public:
	Cdepositinfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cdepositinfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CString m_yearchange;
	int m_monthchange;
	int m_yearchange;
	CString m_daychange;
	afx_msg void OnBnClickedOk();
};
