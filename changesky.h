#pragma once


// changesky 对话框

class changesky : public CDialogEx
{
	DECLARE_DYNAMIC(changesky)

public:
	changesky(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~changesky();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
