#pragma once


// CdepositDlg 对话框

class CdepositDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CdepositDlg)

public:
	CdepositDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CdepositDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEPOSIT };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	// 该项代表存了多少钱
	double m_damount;
	// 存款选了哪一项
	int m_dselect;
	afx_msg void OnBnClickedOk();
};
