#pragma once


// searchdiff 对话框

class searchdiff : public CDialogEx
{
	DECLARE_DYNAMIC(searchdiff)

public:
	searchdiff(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~searchdiff();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
