#pragma once


// CwithdrawalDlg 对话框

class CwithdrawalDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CwithdrawalDlg)

public:
	CwithdrawalDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CwithdrawalDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WITHDRAWAL };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 记录已存款项
	CListCtrl m_withdrabox;
};
