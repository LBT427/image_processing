#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#pragma pack(1)  //这个选项挺重要，不加的话程序就会报错，原因参考
//https://blog.csdn.net/qq_44310495/article/details/109181857

typedef struct {
	unsigned char bfType[2];
	unsigned int bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int bfOffBits;
}bitmapFileHeader;

typedef struct {
	unsigned long biSize;
	int biWidth;	//图像宽度
	long biHeight;  //图像的高度
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
	unsigned char rgbBlue;   //该颜色的蓝色分量  (值范围为0-255)
	unsigned char rgbGreen;  //该颜色的绿色分量  (值范围为0-255)
	unsigned char rgbRed;    //该颜色的红色分量  (值范围为0-255)
	unsigned char rgbReserved;// 保留，必须为0
}RGBQUAD;


void readHead(bitmapFileHeader *bfHeader, bitmapInfoHeader *biHeader,FILE* fpBMP)
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



int main() {

	unsigned char ImgData[2000][3];//将位图信息转为灰度 存储RGB图像的一行像素点	
	//unsigned char ImgData2[2000];//将灰度图的像素存到一个一维数组中

	unsigned char imgbufferData[1000][1000];

	int i, j, k;
////////////////打开文件
	FILE* fpBMP;
	if ((fpBMP = fopen((char*)"D:\\desk\\a.bmp", (char*)"rb")) == NULL) {
		perror("can not open file!");
		return -1;
	}
/////////////////////////////
	bitmapFileHeader *bfHeader=(bitmapFileHeader*)malloc(sizeof(bitmapFileHeader));
	bitmapInfoHeader *biHeader = (bitmapInfoHeader*)malloc(sizeof(bitmapInfoHeader));

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

/////////////////////////////////////////////修改信息头
    //信息头共有11部分，灰度化时需要修改两部分	
	biHeader->biBitCount = 8;//将24位真彩图转换成8位灰度图
	biHeader->biSizeImage = ((biHeader->biWidth * 3 + 3) / 4) * 4 * biHeader->biHeight;//24Bit真彩图每一行占的实际字节数
/////////////////////////////////////////////修改文件头
    //文件头共有5部分，灰度化时需要修改两部分
	bfHeader->bfOffBits = sizeof(bitmapFileHeader) + sizeof(bitmapInfoHeader) + 256 * sizeof(RGBQUAD);
	bfHeader->bfSize = bfHeader->bfOffBits + biHeader->biSizeImage;//文件大小

	printf("修改后的图片每个像素的位数:%d\n" ,biHeader->biBitCount);   
    printf("修改后的图片每个像素数据偏移:%d\n" ,bfHeader->bfOffBits);

//////////////创建调色版 应为灰度图像的调色板是 R=G=B.而真彩图的三值不相等
	RGBQUAD* ipRGB = (RGBQUAD *)malloc(256 * sizeof(RGBQUAD));
	rgbColer(ipRGB);
///////////////////////////////////////////创建一个新的位图文件	
	FILE* fpGray = fopen((char*)"D:\\desk\\a1.bmp", (char*)"wb"); 
	if (fpGray == NULL)
	{
		printf("文件打开失败\n");
		exit(0);
	}
/////////////////////////////////////写入BMP图像的信息头、文件头、BMP调色板到新建的图片
	fwrite(bfHeader, sizeof(bitmapFileHeader), 1,   fpGray);
	fwrite(biHeader, sizeof(bitmapInfoHeader), 1,   fpGray);
	fwrite(ipRGB     , sizeof(RGBQUAD)         , 256, fpGray);

//////////////////////////////////////////////读取RGB图像素并转换为灰度值
	for (i = 0; i < biHeader->biHeight; i++)//一行一行的扫描
	{
		//24Bit真彩图每一行占的实际字节数：[(biWidth*3+3)/4*4]  故biHeight行每行扫描[(biWidth*3+3)/4*4]次
		for (j = 0; j < (biHeader->biWidth + 3) / 4 * 4; j++)//写BMP图像的位图数据部分 
		{
			for (k = 0; k < 3; k++)
				fread(&ImgData[j][k], 1, 1, fpBMP);//每次只读取一个字节，存入数组 
		}
		//修改位图数据部分这部分主要是由原真彩图的rgbRed、rgbGreen、rgbBlue分量值得到灰度图像的灰度值Y，可以用下面公式得到：
		for (j = 0; j < (biHeader->biWidth + 3) / 4 * 4; j++)  
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

	static unsigned char arr[512*512];
	int num=0;


///////////////////////////把二维缓存填充到一维缓存里
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
		if (arr[i] < 127) arr[i] = 0;
		else arr[i] = 255;
	}

	//for (size_t i = 0; i < 512; i++)
	//{
	//	for(size_t j = 0; j < 512; j++)
	//	{
	//		fwrite(&imgbufferData[i][j], 1, 1, fpGray);//按顺序写入BMP图像的各个部分
	//	}
	//}

	fwrite(arr, num *sizeof(unsigned char), 1, fpGray);//按顺序写入BMP图像的各个部分

	fclose(fpBMP);//关闭文件
	fclose(fpGray);//关闭文件

	//fwrite(&bfHeader, sizeof(bitmapFileHeader), 1, fp1);  //写入位图文件头

	//fwrite(&biHeader, sizeof(bitmapInfoHeader), 1, fp1); //写入位图信息头
	//fwrite(pColorTable, sizeof(RGBQUAD), 256, fp1);  //写入位图调色板
	//fwrite(imageData, imSize * sizeof(unsigned char), 1, fp1); //写入位图数据
	//fclose(fp1);

	//free(imageData);









	//getchar();
	return 0;
}
