#pragma once


// changesky �Ի���

class changesky : public CDialogEx
{
	DECLARE_DYNAMIC(changesky)

public:
	changesky(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~changesky();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
