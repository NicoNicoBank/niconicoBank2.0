#pragma once


// Creportloss 对话框

class Creportloss : public CDialogEx
{
	DECLARE_DYNAMIC(Creportloss)

public:
	Creportloss(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Creportloss();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REPORTLOSS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
