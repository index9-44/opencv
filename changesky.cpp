// changesky.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "changesky.h"
#include "afxdialogex.h"
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2\core.hpp>
#include"ColorDetector.h"
using namespace cv;

// changesky 对话框

IMPLEMENT_DYNAMIC(changesky, CDialogEx)

changesky::changesky(CWnd* pParent /*=NULL*/)
	: CDialogEx(changesky::IDD, pParent)
{

}

changesky::~changesky()
{
}

void changesky::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(changesky, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &changesky::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &changesky::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &changesky::OnBnClickedButton2)
END_MESSAGE_MAP()


// changesky 消息处理程序


void changesky::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();

}



void changesky::OnBnClickedButton1()
{
	//IDC_BUTTON1.vissi
	
}


void changesky::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	/*CString str;
	str.Format("start explorer %s","www.baidu.com");
	system(str);*/

	char* open = "open";
	CString str1 = CString(open);
	USES_CONVERSION;
	LPCWSTR openLPCWSTR = A2CW(W2A(str1));

	char* uri = "https://blog.csdn.net/qq_41966009";
	CString str2 = CString(uri);
//	USES_CONVERSION;
	LPCWSTR uriLPCWSTR = A2CW(W2A(str2));

	//str.ReleaseBuffer();


	//LPCWSTR op="open";

	ShellExecute(NULL, openLPCWSTR, uriLPCWSTR, NULL, NULL, SW_SHOWNORMAL);
}
