/***
 * @Author: liubotao
 * @Date: 2022-07-26 13:49:56
 * @LastEditors: liubotao
 * @LastEditTime: 2022-07-26 17:45:29
 * @FilePath: \pic2\ToGray.h
 * @Description:
 * @
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>



#pragma pack(1)  //���ѡ��ͦ��Ҫ�����ӵĻ�����ͻᱨ��ԭ��ο�
 //https://blog.csdn.net/qq_44310495/article/details/109181857

typedef struct {
	unsigned char bfType[2];
	unsigned int bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int bfOffBits;
}bitmapFileHeader;

#pragma pack(1)
typedef struct {
	unsigned long biSize;
	int biWidth;	//ͼ����
	long biHeight;  //ͼ��ĸ߶�
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	int biXPixPerMeter;
	int biYPixPerMeter;
	unsigned int biClrused;
	unsigned int biClrImportant;
}bitmapInfoHeader;


#pragma pack(1)
typedef struct tagRGBQUAD
{
	unsigned char rgbBlue;   //����ɫ����ɫ����  (ֵ��ΧΪ0-255)
	unsigned char rgbGreen;  //����ɫ����ɫ����  (ֵ��ΧΪ0-255)
	unsigned char rgbRed;    //����ɫ�ĺ�ɫ����  (ֵ��ΧΪ0-255)
	unsigned char rgbReserved;// ����������Ϊ0
}RGBQUAD;


void ToGray(int width, int height, unsigned char** imgbufferData, unsigned char** ImgData, FILE* fpBMP);
void readHead(bitmapFileHeader* bfHeader, bitmapInfoHeader* biHeader, FILE* fpBMP);
void rgbColer(RGBQUAD* ipRGB);
void  setHeader(bitmapFileHeader* bfHeader, bitmapInfoHeader* biHeader);
void  writeHeader(bitmapFileHeader* bfHeader, bitmapInfoHeader* biHeader, FILE* fpGray);