#pragma once


// Cstaffregist 对话框

class Cstaffregist : public CDialogEx
{
	DECLARE_DYNAMIC(Cstaffregist)

public:
	Cstaffregist(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cstaffregist();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STAFFREGIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CString m_account;
	CString m_pwd;
	afx_msg void OnBnClickedOk();
};
