// searchdiff.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "searchdiff.h"
#include "afxdialogex.h"

#include<opencv2\highgui.hpp>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2\core.hpp>
#include <conio.h>
using namespace std;
using namespace cv;
// searchdiff 对话框

IMPLEMENT_DYNAMIC(searchdiff, CDialogEx)

searchdiff::searchdiff(CWnd* pParent /*=NULL*/)
	: CDialogEx(searchdiff::IDD, pParent)
{

}

searchdiff::~searchdiff()
{
}

void searchdiff::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(searchdiff, CDialogEx)
	ON_BN_CLICKED(IDOK, &searchdiff::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &searchdiff::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &searchdiff::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &searchdiff::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &searchdiff::OnBnClickedButton3)
END_MESSAGE_MAP()


// searchdiff 消息处理程序


void searchdiff::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	// TODO:  在此添加控件通知处理程序代码
	
}


void searchdiff::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void searchdiff::OnBnClickedButton1()
{
	//禁用“开始游戏”按钮
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);

	//打开“下一张”按钮
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);

}


void searchdiff::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void searchdiff::OnBnClickedButton3()
{
	//获取桌面窗口的CDC 相当于画布，你可以使用笔、刷、位图、字体等在画笔上画图
	CDC *pdeskdc = GetDesktopWindow()->GetDC();
	CRect re;
	//获取窗口的大小
	GetDesktopWindow()->GetClientRect(&re);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pdeskdc, re.Width(), re.Height());
	//创建一个兼容的内存画板
	CDC memorydc;
	memorydc.CreateCompatibleDC(pdeskdc);

	//选中画笔
	CBitmap *pold = memorydc.SelectObject(&bmp);

	//绘制图像    
	//x：目标矩形区域的左上角x轴坐标点。
	//y：目标矩形区域的左上角y轴坐标点。
	//nWidth：在目标设备中绘制位图的宽度。
	//nHight：在目标设备中绘制位图的高度。
	//pdeskdc：源设备上下文对象指针。
	//xSrc：源设备上下文的起点x轴坐标，函数从该起点复制位图到目标设备。
	//ySrc：源设备上下文的起点y轴坐标，函数从该起点复制位图到目标设备。
	//SRCCOPY：光栅操作代码
	memorydc.BitBlt(0, 0, re.Width(), re.Height(), pdeskdc, 0, 0, SRCCOPY);

	//获取鼠标位置，然后添加鼠标图像
	CPoint po;
	GetCursorPos(&po);
	HICON hinco = (HICON)GetCursor();
	memorydc.DrawIcon(po.x - 10, po.y - 10, hinco);
	//选中原来的画笔
	memorydc.SelectObject(pold);
	BITMAP bit;
	bmp.GetBitmap(&bit);
	//	DWORD size = bit.bmWidth * bit.bmHeight ;

	//定义 图像大小（单位：byte）
	DWORD size = bit.bmWidthBytes * bit.bmHeight;
	LPSTR lpdata = (LPSTR)GlobalAlloc(GPTR, size);

	//后面是创建一个bmp文件的必须文件头，想要了解可以参考msdn

	BITMAPINFOHEADER pbitinfo;
	pbitinfo.biBitCount = 24;
	pbitinfo.biClrImportant = 0;
	pbitinfo.biCompression = BI_RGB;
	pbitinfo.biHeight = bit.bmHeight;
	pbitinfo.biPlanes = 1;
	pbitinfo.biSize = sizeof(BITMAPINFOHEADER);
	pbitinfo.biSizeImage = size;
	pbitinfo.biWidth = bit.bmWidth;
	pbitinfo.biXPelsPerMeter = 0;
	pbitinfo.biYPelsPerMeter = 0;

	GetDIBits(pdeskdc->m_hDC, bmp, 0, pbitinfo.biHeight, lpdata,
		(BITMAPINFO*)&pbitinfo, DIB_RGB_COLORS);

	BITMAPFILEHEADER bfh;
	bfh.bfReserved1 = bfh.bfReserved2 = 0;
	bfh.bfType = ((WORD)('M' << 8) | 'B');
	bfh.bfSize = 54 + size;
	bfh.bfOffBits = 54;

	//写入文件

	CFile file;
	if (file.Open((LPCTSTR)L"base6.jpg", CFile::modeCreate | CFile::modeWrite))
		//if (file.Open("1.bmp", CFile::modeCreate | CFile::modeWrite))
	{
		file.Write(&bfh, sizeof(BITMAPFILEHEADER));
		file.Write(&pbitinfo, sizeof(BITMAPINFOHEADER));
		file.Write(lpdata, size);
		file.Close();
	}
	Mat image = imread("base6.jpg");
	//转化成二值图
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	cv::Mat contours;
	cv::Canny(gray,
		contours,
		250,            //调了了很长时间，还是感觉大于875为边缘，小于250不是边缘效果最好。
		875);
	//imshow("Canny", contours);

	int hight, width;
	hight = image.rows;
	width = image.cols;
	//用于记录连续像素点存在的次数
	int number = 0;
	bool istrue = false;
	//截图窗口的高和宽
	int imageheight, imagewidth;
	//int widthget;
	for (int i = 0; i < hight; i++)
	{
		uchar* data = contours.ptr<uchar>(i);
		//w
		for (int j = 0; j < width; j++)
		{
			if (istrue)
			{
				break;
			}
			//white = 255;
			if ((int)data[j] != 0)
			{
				//widthget = j;
				number++;
				if (number>100)
				{
					cout << "number:" << number;
					number = 0;
					cout << "高：" << i << "宽：" << j - 101 << endl;
					imageheight = i;
					imagewidth = j - 101;
					istrue = true;
					break;
				}
			}
			else
			{
				//如果断一次，都要初始化值，防止当前行存在其他像素的干扰
				number = 0;
			}

		}
		//每行遍历结束，若未发现游戏边框，便要初始化记录值
		number = 0;
	}

	//(x,y)  x:宽   y：高

	//imshow("原图", image);
	//Rect mainimage(imagewidth, imageheight, 1282, 959);        2k分辨率下的位置
	Rect mainimage(imagewidth, imageheight, 1282, 959);

	//imshow("切割图", mainimage);
		Mat ROImainImage = image(mainimage);
		//imshow("ROImainImage",ROImainImage);
		Rect rectLeft(117, 390, 474, 356);
		Rect rectRight(688, 390, 474, 356);
		Mat ROILeft = ROImainImage(rectLeft);
		Mat ROIRight = ROImainImage(rectRight);
		//imshow("ROI_Left", ROILeft);
		//imshow("ROIRight", ROIRight);
		Mat outputimage, out, andout;
		bitwise_xor(ROILeft, ROIRight, outputimage);
		imshow("xor", outputimage);
}
