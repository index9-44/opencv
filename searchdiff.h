#pragma once


// searchdiff �Ի���

class searchdiff : public CDialogEx
{
	DECLARE_DYNAMIC(searchdiff)

public:
	searchdiff(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~searchdiff();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
