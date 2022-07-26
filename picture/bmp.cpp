/***
 * @Author: liubotao
 * @Date: 2022-07-26 13:42:41
 * @LastEditors: liubotao
 * @LastEditTime: 2022-07-26 17:42:06
 * @FilePath: \pic2\ToGray.cpp
 * @Description:
 * @
 */
#include "bmp.h"

void ToGray(int width, int height, unsigned char** imgbufferData, unsigned char** ImgData, FILE* fpBMP)
{
	//////////////////////////////////////////////读取RGB图像素并转换为灰度值
	for (int i = 0; i < height; i++)//一行一行的扫描
	{
		//24Bit真彩图每一行占的实际字节数：[(biWidth*3+3)/4*4]  故biHeight行每行扫描[(biWidth*3+3)/4*4]次
		for (int j = 0; j < (width + 3) / 4 * 4; j++)//写BMP图像的位图数据部分 
		{
			for (int k = 0; k < 3; k++)
				//fread(*((ImgData+k*width*height)+1), 1, 1, fpBMP);//每次只读取一个字节，存入数组 
				fread(&ImgData[j][k], 1, 1, fpBMP);//每次只读取一个字节，存入数组 
		}
		//修改位图数据部分这部分主要是由原真彩图的rgbRed、rgbGreen、rgbBlue分量值得到灰度图像的灰度值Y，可以用下面公式得到：
		for (int j = 0; j < (width + 3) / 4 * 4; j++)
		{

			/*ImgData2[j] = (int)((float)ImgData[j][0] * 0.114 +
								(float)ImgData[j][1] * 0.587 +
								(float)ImgData[j][2] * 0.299  );*/
			imgbufferData[i][j] = (int)((float)ImgData[j][0] * 0.114 +
				(float)ImgData[j][1] * 0.587 +
				(float)ImgData[j][2] * 0.299);//将灰度图像的灰度值存入数组
		}
		//将灰度图信息写入
		//fwrite(ImgData2, j, 1, fpGray);//按顺序写入BMP图像的各个部分
	}



}
void readHead(bitmapFileHeader* bfHeader, bitmapInfoHeader* biHeader, FILE* fpBMP)
{

	fread(bfHeader, 14, 1, fpBMP);//读取头部信息
	fread(biHeader, 40, 1, fpBMP);//读取头部信息


}

//////////定义一个调色板构体指针	
void rgbColer(RGBQUAD* ipRGB)
{

	//////////////创建调色版 应为灰度图像的调色板是 R=G=B.而真彩图的三值不相等

	for (int i = 0; i < 256; i++)
	{


		ipRGB[i].rgbBlue = ipRGB[i].rgbGreen = ipRGB[i].rgbRed = i;
	}

}




void  setHeader(bitmapFileHeader* bfHeader, bitmapInfoHeader* biHeader)
{


	/////////////////////////////////////////////修改信息头
		//信息头共有11部分，灰度化时需要修改两部分	
	biHeader->biBitCount = 8;//将24位真彩图转换成8位灰度图
	biHeader->biSizeImage = ((biHeader->biWidth * 3 + 3) / 4) * 4 * biHeader->biHeight;//24Bit真彩图每一行占的实际字节数
	/////////////////////////////////////////////修改文件头
		//文件头共有5部分，灰度化时需要修改两部分
	bfHeader->bfOffBits = sizeof(bitmapFileHeader) + sizeof(bitmapInfoHeader) + 256 * sizeof(RGBQUAD);
	bfHeader->bfSize = bfHeader->bfOffBits + biHeader->biSizeImage;//文件大小

	printf("修改后的图片每个像素的位数:%d\n", biHeader->biBitCount);
	printf("修改后的图片每个像素数据偏移:%d\n", bfHeader->bfOffBits);



}

void  writeHeader(bitmapFileHeader* bfHeader, bitmapInfoHeader* biHeader, FILE* fpGray)
{
	RGBQUAD ipRGB;
	rgbColer(&ipRGB);
	/////////////////////////////////////写入BMP图像的信息头、文件头、BMP调色板到新建的图片
	fwrite(bfHeader, sizeof(bitmapFileHeader), 1, fpGray);
	fwrite(biHeader, sizeof(bitmapInfoHeader), 1, fpGray);
	fwrite(&ipRGB, sizeof(RGBQUAD), 256, fpGray);
}