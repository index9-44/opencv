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
	int maxDist;		// 允许的最大颜色差距
	cv::Vec3b target;		// 目标颜色
	// 计算两个颜色之间的距离
	int getColorDistance(const cv::Vec3b &color1,
		const cv::Vec3b &color2) const {
		// 计算城区距离
		return  abs(color1[0] - color2[0]) +
			abs(color1[1] - color2[1]) +
			abs(color1[2] - color2[2]);
	}
	// 计算与目标颜色的差距
	int getDistanceToTargetColor(const cv::Vec3b &color) const {
		return getColorDistance(color, target);
	}
public:
	ColorDetector() : maxDist(100), target(0, 0, 0) {}
	Mat process(const cv::Mat &image) {
		cv::Mat result;
		// 重新分配二值结果图像
		// 与输入图像的尺寸相同，不过是单通道
		result.create(image.size(), CV_8U);
		// 遍历图像，处理每个像素
		for (int j = 0; j < image.rows; j++) {
			// 取得行j的首地址
			const cv::Vec3b *input = image.ptr<cv::Vec3b>(j);
			uchar *output = result.ptr<uchar>(j);
			// 遍历该行的每一个像素
			for (int i = 0; i < image.cols; i++) {
				// 比较与目标颜色的差距
				if (getDistanceToTargetColor(input[i]) <= maxDist)
					output[i] = 255;
				else
					output[i] = 0;
			}
		}
		return result;
	}


	// 设置颜色差距的阈值
	// 阈值必须是正数，否则就置为0
	void setColorDistanceThreshold(int distance) {
		if (distance < 0)
			distance = 0;
		maxDist = distance;
	}
	// 取得颜色差距的阈值
	int getColorDistanceThreshold() const {
		return maxDist;
	}
	// 设置需要检测的颜色
	void setTargetColor(uchar blue, uchar green, uchar red) {
		// 次序为BGR
		target = cv::Vec3b(blue, green, red);
	}
	// 设置需要检测的颜色
	void setTargetColor(cv::Vec3b color) {
		target = color;
	}
	// 获取需要检测的颜色
	cv::Vec3b getTargetColor() const {
		return target;
	}
};