// test4.24.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

void getHist(Mat srcMat, float * hist, int nX, int nY, int cellsize);
float getDistance(float * hist1, float * hist2, int bins);

int main()
{
	Mat refMat = imread("hogTemplate.jpg", 0);
	Mat Mat1 = imread("img1.jpg", 0);
	Mat Mat2 = imread("img2.jpg", 0);
	int cellsize = 16;
	int nX = refMat.cols / cellsize;
	int nY = refMat.rows / cellsize;
	int bins = 8 * nX * nY;
	float * ref_hist = new float[bins];
	memset(ref_hist, 0, sizeof(float)*bins);
	float * hist1 = new float[bins];
	memset(hist1, 0, sizeof(float)*bins);
	float * hist2 = new float[bins];
	memset(hist2, 0, sizeof(float)*bins);

	getHist(refMat, ref_hist, nX, nY, cellsize);
	getHist(Mat1, hist1, nX, nY, cellsize);
	getHist(Mat2, hist2, nX, nY, cellsize);
	float dis1 = getDistance(ref_hist, hist1, bins);
	float dis2 = getDistance(ref_hist, hist2, bins);
	cout << "与img1距离：" << dis1 << endl;
	cout << "与img2距离：" << dis2 << endl;
	if (dis1 < dis2)
	{
		cout << "与refMat更相似的是：img1" << endl;
	}
	else if (dis1 > dis2)
	{
		cout << "与refMat更相似的是：img2" << endl;
	}
	else
	{
		cout << "相似度相同" << endl;
	}
	delete[] ref_hist, hist1, hist2;
	waitKey();
}

void getHist(Mat srcMat, float * hist, int nX, int nY, int cellsize)
{
	Mat gx, gy;
	Mat mag, angle;
	Sobel(srcMat, gx, CV_32F, 1, 0, 1);
	Sobel(srcMat, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);
	for (int i = 0; i < nY * 16; i++)
	{
		for (int j = 0; j < nX * 16; j++)
		{
			int angle_q = angle.at<float>(i, j) / 45;
			*(hist + (j / cellsize * nX + i / cellsize) * 8 + angle_q) += mag.at<float>(i, j);
		}
	}
}

float getDistance(float * hist1, float * hist2, int bins)
{
	float sum = 0;
	for (int i = 0; i < bins; i++)
	{
		sum += pow(*(hist1 + i) - *(hist2 + i), 2);
	}
	return sqrt(sum);
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
