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
	//////////////////////////////////////////////��ȡRGBͼ���ز�ת��Ϊ�Ҷ�ֵ
	for (int i = 0; i < height; i++)//һ��һ�е�ɨ��
	{
		//24Bit���ͼÿһ��ռ��ʵ���ֽ�����[(biWidth*3+3)/4*4]  ��biHeight��ÿ��ɨ��[(biWidth*3+3)/4*4]��
		for (int j = 0; j < (width + 3) / 4 * 4; j++)//дBMPͼ���λͼ���ݲ��� 
		{
			for (int k = 0; k < 3; k++)
				//fread(*((ImgData+k*width*height)+1), 1, 1, fpBMP);//ÿ��ֻ��ȡһ���ֽڣ��������� 
				fread(&ImgData[j][k], 1, 1, fpBMP);//ÿ��ֻ��ȡһ���ֽڣ��������� 
		}
		//�޸�λͼ���ݲ����ⲿ����Ҫ����ԭ���ͼ��rgbRed��rgbGreen��rgbBlue����ֵ�õ��Ҷ�ͼ��ĻҶ�ֵY�����������湫ʽ�õ���
		for (int j = 0; j < (width + 3) / 4 * 4; j++)
		{

			/*ImgData2[j] = (int)((float)ImgData[j][0] * 0.114 +
								(float)ImgData[j][1] * 0.587 +
								(float)ImgData[j][2] * 0.299  );*/
			imgbufferData[i][j] = (int)((float)ImgData[j][0] * 0.114 +
				(float)ImgData[j][1] * 0.587 +
				(float)ImgData[j][2] * 0.299);//���Ҷ�ͼ��ĻҶ�ֵ��������
		}
		//���Ҷ�ͼ��Ϣд��
		//fwrite(ImgData2, j, 1, fpGray);//��˳��д��BMPͼ��ĸ�������
	}



}
void readHead(bitmapFileHeader* bfHeader, bitmapInfoHeader* biHeader, FILE* fpBMP)
{

	fread(bfHeader, 14, 1, fpBMP);//��ȡͷ����Ϣ
	fread(biHeader, 40, 1, fpBMP);//��ȡͷ����Ϣ


}

//////////����һ����ɫ�幹��ָ��	
void rgbColer(RGBQUAD* ipRGB)
{

	//////////////������ɫ�� ӦΪ�Ҷ�ͼ��ĵ�ɫ���� R=G=B.�����ͼ����ֵ�����

	for (int i = 0; i < 256; i++)
	{


		ipRGB[i].rgbBlue = ipRGB[i].rgbGreen = ipRGB[i].rgbRed = i;
	}

}




void  setHeader(bitmapFileHeader* bfHeader, bitmapInfoHeader* biHeader)
{


	/////////////////////////////////////////////�޸���Ϣͷ
		//��Ϣͷ����11���֣��ҶȻ�ʱ��Ҫ�޸�������	
	biHeader->biBitCount = 8;//��24λ���ͼת����8λ�Ҷ�ͼ
	biHeader->biSizeImage = ((biHeader->biWidth * 3 + 3) / 4) * 4 * biHeader->biHeight;//24Bit���ͼÿһ��ռ��ʵ���ֽ���
	/////////////////////////////////////////////�޸��ļ�ͷ
		//�ļ�ͷ����5���֣��ҶȻ�ʱ��Ҫ�޸�������
	bfHeader->bfOffBits = sizeof(bitmapFileHeader) + sizeof(bitmapInfoHeader) + 256 * sizeof(RGBQUAD);
	bfHeader->bfSize = bfHeader->bfOffBits + biHeader->biSizeImage;//�ļ���С

	printf("�޸ĺ��ͼƬÿ�����ص�λ��:%d\n", biHeader->biBitCount);
	printf("�޸ĺ��ͼƬÿ����������ƫ��:%d\n", bfHeader->bfOffBits);



}

void  writeHeader(bitmapFileHeader* bfHeader, bitmapInfoHeader* biHeader, FILE* fpGray)
{
	RGBQUAD ipRGB;
	rgbColer(&ipRGB);
	/////////////////////////////////////д��BMPͼ�����Ϣͷ���ļ�ͷ��BMP��ɫ�嵽�½���ͼƬ
	fwrite(bfHeader, sizeof(bitmapFileHeader), 1, fpGray);
	fwrite(biHeader, sizeof(bitmapInfoHeader), 1, fpGray);
	fwrite(&ipRGB, sizeof(RGBQUAD), 256, fpGray);
}