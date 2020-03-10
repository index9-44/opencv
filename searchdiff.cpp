// searchdiff.cpp : ʵ���ļ�
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
// searchdiff �Ի���

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


// searchdiff ��Ϣ�������


void searchdiff::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
}


void searchdiff::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

void searchdiff::OnBnClickedButton1()
{
	//���á���ʼ��Ϸ����ť
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);

	//�򿪡���һ�š���ť
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);

}


void searchdiff::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void searchdiff::OnBnClickedButton3()
{
	//��ȡ���洰�ڵ�CDC �൱�ڻ����������ʹ�ñʡ�ˢ��λͼ��������ڻ����ϻ�ͼ
	CDC *pdeskdc = GetDesktopWindow()->GetDC();
	CRect re;
	//��ȡ���ڵĴ�С
	GetDesktopWindow()->GetClientRect(&re);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pdeskdc, re.Width(), re.Height());
	//����һ�����ݵ��ڴ滭��
	CDC memorydc;
	memorydc.CreateCompatibleDC(pdeskdc);

	//ѡ�л���
	CBitmap *pold = memorydc.SelectObject(&bmp);

	//����ͼ��    
	//x��Ŀ�������������Ͻ�x������㡣
	//y��Ŀ�������������Ͻ�y������㡣
	//nWidth����Ŀ���豸�л���λͼ�Ŀ�ȡ�
	//nHight����Ŀ���豸�л���λͼ�ĸ߶ȡ�
	//pdeskdc��Դ�豸�����Ķ���ָ�롣
	//xSrc��Դ�豸�����ĵ����x�����꣬�����Ӹ���㸴��λͼ��Ŀ���豸��
	//ySrc��Դ�豸�����ĵ����y�����꣬�����Ӹ���㸴��λͼ��Ŀ���豸��
	//SRCCOPY����դ��������
	memorydc.BitBlt(0, 0, re.Width(), re.Height(), pdeskdc, 0, 0, SRCCOPY);

	//��ȡ���λ�ã�Ȼ��������ͼ��
	CPoint po;
	GetCursorPos(&po);
	HICON hinco = (HICON)GetCursor();
	memorydc.DrawIcon(po.x - 10, po.y - 10, hinco);
	//ѡ��ԭ���Ļ���
	memorydc.SelectObject(pold);
	BITMAP bit;
	bmp.GetBitmap(&bit);
	//	DWORD size = bit.bmWidth * bit.bmHeight ;

	//���� ͼ���С����λ��byte��
	DWORD size = bit.bmWidthBytes * bit.bmHeight;
	LPSTR lpdata = (LPSTR)GlobalAlloc(GPTR, size);

	//�����Ǵ���һ��bmp�ļ��ı����ļ�ͷ����Ҫ�˽���Բο�msdn

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

	//д���ļ�

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
	//ת���ɶ�ֵͼ
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	cv::Mat contours;
	cv::Canny(gray,
		contours,
		250,            //�����˺ܳ�ʱ�䣬���Ǹо�����875Ϊ��Ե��С��250���Ǳ�ԵЧ����á�
		875);
	//imshow("Canny", contours);

	int hight, width;
	hight = image.rows;
	width = image.cols;
	//���ڼ�¼�������ص���ڵĴ���
	int number = 0;
	bool istrue = false;
	//��ͼ���ڵĸߺͿ�
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
					cout << "�ߣ�" << i << "��" << j - 101 << endl;
					imageheight = i;
					imagewidth = j - 101;
					istrue = true;
					break;
				}
			}
			else
			{
				//�����һ�Σ���Ҫ��ʼ��ֵ����ֹ��ǰ�д����������صĸ���
				number = 0;
			}

		}
		//ÿ�б�����������δ������Ϸ�߿򣬱�Ҫ��ʼ����¼ֵ
		number = 0;
	}

	//(x,y)  x:��   y����

	//imshow("ԭͼ", image);
	//Rect mainimage(imagewidth, imageheight, 1282, 959);        2k�ֱ����µ�λ��
	Rect mainimage(imagewidth, imageheight, 1282, 959);

	//imshow("�и�ͼ", mainimage);
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
