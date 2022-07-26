/***
 * @Author: liubotao
 * @Date: 2022-07-22 17:32:21
 * @LastEditors: liubotao
 * @LastEditTime: 2022-07-26 17:50:59
 * @FilePath: \pic2\pic2.cpp
 * @Description:
 * @
 */
//#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include "bmp.h"


int main() {

	//static unsigned char ImgData[2000][3];//将位图信息转为灰度 存储RGB图像的一行像素点	
	//unsigned char ImgData2[2000];//将灰度图的像素存到一个一维数组中
	//unsigned char* imgbufferData = (unsigned char*)malloc(1000*1000*sizeof(unsigned char));

	//static unsigned char imgbufferData[1000][1000];

////////////////打开文件
	FILE* fpBMP;
	if ((fpBMP = fopen((char*)"D:\\desk\\a.bmp", (char*)"rb")) == NULL) {
		perror("can not open file!");
		return -1;
	}
	/////////////////////////////
	bitmapFileHeader* bfHeader = new bitmapFileHeader;
	bitmapInfoHeader* biHeader = new bitmapInfoHeader;

	/////////////////////////////////////////读取头部
	readHead(bfHeader, biHeader, fpBMP);

	int imSize = biHeader->biSizeImage;	//获取大小
	int width = biHeader->biWidth;		//获取图像宽度
	int height = biHeader->biHeight;		//获取图像高度
	int bitCount = biHeader->biBitCount; //获取图像位数
//////////////////////////////////////////读取头部
	//fseek(fpBMP, bfHeader.bfOffBits, SEEK_SET);//跳到图片数据开始位置
	//unsigned char* imageData = (unsigned char*)malloc(imSize * sizeof(unsigned char));//分配图片数据空间
	//fread(imageData, imSize * sizeof(unsigned char), 1, fpBMP);//获取图片数据
///////////////////////////////////////////


	////图像为24位图像
	//int lineBytes = (bitCount * width + 31) / 32 * 4;//得到图像数据的bitwidth'
	//int i, j;
	//int r, g, b;
	//for (i = 0; i < height; i++) { //对于每一行
	//	for (j = 0; j < width * 3; j++) { //对于每一列
	//		r = *(imageData + lineBytes * (height - 1 - i) + j); //从最后一行往上读
	//		j++;
	//		g = *(imageData + lineBytes * (height - 1 - i) + j);
	//		j++;
	//		b = *(imageData + lineBytes * (height - 1 - i) + j);
	//		if (r == 255 && g == 255 && b == 255) //模拟二值图像展示
	//			printf("  ");
	//		else
	//			printf(".$");
	//	}
	//	printf("\n");
	//}
	unsigned char** ImgData = new unsigned char* [2000];
	for (int i = 0; i < 2000; i++)   //给每行的数组分配一下空间 
	{
		ImgData[i] = new unsigned char[3];
	}
	unsigned char** imgbufferData = new unsigned char* [width];
	for (int i = 0; i < width; i++)   //给每行的数组分配一下空间 
	{
		imgbufferData[i] = new unsigned char[height];
	}

	//////////////////////////////////////////////读取RGB图像素并转换为灰度值
	ToGray(width, height, imgbufferData, (unsigned char**)ImgData, fpBMP);


	////大津

#define GrayScale 256//定义256个灰度级
	unsigned char width_O = width;   //图像宽度
	unsigned char height_O = height;  //图像长度
	int pixelCount[GrayScale];  //每个灰度值所占像素个数
	float pixelPro[GrayScale]; //每个灰度值所占总像素比例
	int i, j;
	int sumPixel = width * height;//总像素点
	unsigned char threshold = 0; //最佳阈值

	for (i = 0; i < GrayScale; i++)
	{
		pixelCount[i] = 0;
		pixelPro[i] = 0;
	}

	//统计灰度级中每个像素在整幅图像中的个数  
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			//pixelCount[(int)data[i * width + j]]++;  //将像素值作为计数数组的下标
			pixelCount[(int)imgbufferData[i][j]]++;    //若不用指针用这个
		}
	}

	//遍历灰度级[0,255]  
	////float w0 = 0, w1 = 0, u0Sum = 0, u1Sum = 0, u0 = 0, u1 = 0, u = 0, variance = 0, maxVariance = 0;
	//目标像素占总图像比例w0
	//背景像素占总图像比例w1 
	//目标平均灰度值u0 
	//背景平均灰度值u1
	//总平均灰度值u
	//类间方差 variance
	//最大类间方差 maxVariance
	float u = 0;
	//计算每个像素在整幅图像中的比例  
	for (i = 0; i < GrayScale; i++)
	{
		pixelPro[i] = (float)pixelCount[i] / sumPixel;
		u += i * pixelPro[i];  //总平均灰度
	}


	//for (i = 0; i < GrayScale; i++)     // i作为阈值 阈值从1-255遍历 
	//{

	//	for (j = 0; j < GrayScale; j++)    //求目标前景和背景
	//	{
	//		if (j <= i)   //前景部分    
	//		{
	//			w0 += pixelPro[j];
	//			u0Sum += j * pixelPro[j];
	//		}
	//		else   //背景部分  
	//		{
	//			w1 += pixelPro[j];
	//			u1Sum += j * pixelPro[j];
	//		}
	//	}
	//	u0 = u0Sum / w0;
	//	u1 = u1Sum / w1;

	//	variance = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);  //类间方差计算公式

	//	if (variance > maxVariance)   //判断是否为最大类间方差
	//	{
	//		maxVariance = variance;
	//		threshold = i;
	//	}
	//}

	float maxVariance = 0.0;  //最大类间方差
	float w0 = 0, avgValue = 0;  //w0 前景比例 ，avgValue 前景平均灰度
	for (int i = 0; i < 256; i++)     //每一次循环都是一次完整类间方差计算 (两个for叠加为1个)
	{
		w0 += pixelPro[i];  //假设当前灰度i为阈值, 0~i 灰度像素所占整幅图像的比例即前景比例
		avgValue += i * pixelPro[i];

		float variance = pow((avgValue / w0 - u), 2) * w0 / (1 - w0);    //类间方差   
		if (variance > maxVariance)
		{
			maxVariance = variance;
			threshold = i;
		}
	}
	printf("threshold = %d\n", threshold);




	///////////////////////////把二维缓存填充到一维缓存里
	static unsigned char arr[512 * 512];
	int num = 0;
	for (size_t i = 0; i < 512; i++)
	{
		for (size_t j = 0; j < 512; j++)
		{
			arr[num] = imgbufferData[i][j];
			num++;
		}
	}
	//////////////////二值化（使用一维缓存）
	for (int i = 0; i < 512 * 512; i++)
	{
		if (arr[i] < threshold) arr[i] = 0;
		else arr[i] = 255;
	}

	//
	//	/////////////////////////////////////////////修改信息头


	setHeader(bfHeader, biHeader);

	//		//信息头共有11部分，灰度化时需要修改两部分	
	//	biHeader->biBitCount = 8;//将24位真彩图转换成8位灰度图
	//	biHeader->biSizeImage = ((biHeader->biWidth * 3 + 3) / 4) * 4 * biHeader->biHeight;//24Bit真彩图每一行占的实际字节数
	///////////////////////////////////////////////修改文件头
	//	//文件头共有5部分，灰度化时需要修改两部分
	//	bfHeader->bfOffBits = sizeof(bitmapFileHeader) + sizeof(bitmapInfoHeader) + 256 * sizeof(RGBQUAD);
	//	bfHeader->bfSize = bfHeader->bfOffBits + biHeader->biSizeImage;//文件大小
	//
	//	printf("修改后的图片每个像素的位数:%d\n", biHeader->biBitCount);
	//	printf("修改后的图片每个像素数据偏移:%d\n", bfHeader->bfOffBits);



		//////////////创建调色版 应为灰度图像的调色板是 R=G=B.而真彩图的三值不相等
	RGBQUAD* ipRGB = (RGBQUAD*)malloc(256 * sizeof(RGBQUAD));
	rgbColer(ipRGB);
	///////////////////////////////////////////创建一个新的位图文件	
	FILE* fpGray = fopen((char*)"D:\\desk\\a2.bmp", (char*)"wb");
	if (fpGray == NULL)
	{
		printf("文件打开失败\n");
		exit(0);
	}
	///////////////////////////////////////写入BMP图像的信息头、文件头、BMP调色板到新建的图片
	//fwrite(bfHeader, sizeof(bitmapFileHeader), 1, fpGray);
	//fwrite(biHeader, sizeof(bitmapInfoHeader), 1, fpGray);
	//fwrite(ipRGB, sizeof(RGBQUAD), 256, fpGray);

	writeHeader(bfHeader, biHeader, fpGray);
	/////////////////////////////////////////////////////////////////////////

	//for (size_t i = 0; i < 512; i++)
	//{
	//	for(size_t j = 0; j < 512; j++)
	//	{
	//		fwrite(&imgbufferData[i][j], 1, 1, fpGray);//按顺序写入BMP图像的各个部分
	//	}
	//}

	fwrite(arr, num * sizeof(unsigned char), 1, fpGray);//按顺序写入BMP图像的各个部分

	fclose(fpBMP);//关闭文件
	fclose(fpGray);//关闭文件

	//fwrite(&bfHeader, sizeof(bitmapFileHeader), 1, fp1);  //写入位图文件头

	//fwrite(&biHeader, sizeof(bitmapInfoHeader), 1, fp1); //写入位图信息头
	//fwrite(pColorTable, sizeof(RGBQUAD), 256, fp1);  //写入位图调色板
	//fwrite(imageData, imSize * sizeof(unsigned char), 1, fp1); //写入位图数据
	//fclose(fp1);

	//free(imageData);



	//free(bfHeader);
	//free(biHeader);
	//free(ipRGB);
	delete bfHeader;
	delete biHeader;
	//delete ipRGB;

	for (int i = 0; i < width; i++)
	{
		delete[] imgbufferData[i];
	}
	delete[]imgbufferData;
	imgbufferData = 0;

	for (int i = 0; i < 2000; i++)
	{
		delete[] ImgData[i];
	}
	delete[]ImgData;
	ImgData = 0;


	//getchar();
	return 0;
}
