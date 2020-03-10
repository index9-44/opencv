#include<opencv2\highgui.hpp>
#include<iostream>
#include "stdafx.h"
#include "MFCApplication1.h"
#include "changesky.h"
#include "afxdialogex.h"
#include<opencv2/opencv.hpp>
#include<opencv2\core.hpp>
using namespace cv;
class ColorDetector {
private:
	int maxDist;		// ����������ɫ���
	cv::Vec3b target;		// Ŀ����ɫ
	// ����������ɫ֮��ľ���
	int getColorDistance(const cv::Vec3b &color1,
		const cv::Vec3b &color2) const {
		// �����������
		return  abs(color1[0] - color2[0]) +
			abs(color1[1] - color2[1]) +
			abs(color1[2] - color2[2]);
	}
	// ������Ŀ����ɫ�Ĳ��
	int getDistanceToTargetColor(const cv::Vec3b &color) const {
		return getColorDistance(color, target);
	}
public:
	ColorDetector() : maxDist(100), target(0, 0, 0) {}
	Mat process(const cv::Mat &image) {
		cv::Mat result;
		// ���·����ֵ���ͼ��
		// ������ͼ��ĳߴ���ͬ�������ǵ�ͨ��
		result.create(image.size(), CV_8U);
		// ����ͼ�񣬴���ÿ������
		for (int j = 0; j < image.rows; j++) {
			// ȡ����j���׵�ַ
			const cv::Vec3b *input = image.ptr<cv::Vec3b>(j);
			uchar *output = result.ptr<uchar>(j);
			// �������е�ÿһ������
			for (int i = 0; i < image.cols; i++) {
				// �Ƚ���Ŀ����ɫ�Ĳ��
				if (getDistanceToTargetColor(input[i]) <= maxDist)
					output[i] = 255;
				else
					output[i] = 0;
			}
		}
		return result;
	}


	// ������ɫ������ֵ
	// ��ֵ�������������������Ϊ0
	void setColorDistanceThreshold(int distance) {
		if (distance < 0)
			distance = 0;
		maxDist = distance;
	}
	// ȡ����ɫ������ֵ
	int getColorDistanceThreshold() const {
		return maxDist;
	}
	// ������Ҫ������ɫ
	void setTargetColor(uchar blue, uchar green, uchar red) {
		// ����ΪBGR
		target = cv::Vec3b(blue, green, red);
	}
	// ������Ҫ������ɫ
	void setTargetColor(cv::Vec3b color) {
		target = color;
	}
	// ��ȡ��Ҫ������ɫ
	cv::Vec3b getTargetColor() const {
		return target;
	}
};