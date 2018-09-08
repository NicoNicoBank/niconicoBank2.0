#pragma once


// CdueDlg 对话框

class CdueDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CdueDlg)

public:
	CdueDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CdueDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DUEDLG };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_duetoday;
	double m_duetomorrow;
	double m_dueafter;
	CString m_sysdate;
//	double m_bankbalance;
	double m_bankbalance;
};
