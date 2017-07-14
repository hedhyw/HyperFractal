/*
 * The MIT License
 *
 * Copyright 2016 Maxim Krivchun.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* 
 * File:   bitmapCore.cpp
 * Author: hedhyw
 * 
 * Created on October 29, 2016, 5:19 PM
 */

#include "bitmapCore.hpp"

uint16_t bitmapCore::getWidth()
{
	return bitmapInformationHeader1.width;
}

uint16_t bitmapCore::getHeight()
{
	return bitmapInformationHeader1.height;
}

void bitmapCore::writePixel(pixel pxl)
{
	ofs->write(reinterpret_cast<char*>(&pxl),sizeof(pxl));
}

void bitmapCore::writeLine(pixel* pxls)
{
	ofs->write(reinterpret_cast<char*>(pxls), sizeof(pixel)*getWidth());
}

void bitmapCore::endLine()
{
	ofs->write(align,getWidth() % 4);
}

void bitmapCore::writeHeader(uint16_t imageWidth, uint16_t imageHeight)
{
	bitmapInformationHeader1.header_size = sizeof(bitmapInformationHeader1);
	bitmapInformationHeader1.width = imageWidth;
	bitmapInformationHeader1.height = imageHeight;
	
	bitmapFileHeader1.offset = sizeof(bitmapFileHeader1) + sizeof(bitmapInformationHeader1);
	bitmapFileHeader1.size = bitmapInformationHeader1.bits/8 * imageWidth * imageHeight;
	bitmapFileHeader1.size += (imageWidth%4) * imageHeight;
	bitmapFileHeader1.size += bitmapFileHeader1.offset;
	
	ofs->write(reinterpret_cast<char*>(&bitmapFileHeader1),sizeof(bitmapFileHeader1));
	ofs->write(reinterpret_cast<char*>(&bitmapInformationHeader1), sizeof(bitmapInformationHeader1));
}

bitmapCore::bitmapCore(std::ofstream *outputFileStream)
{
	setOutputFileStream(outputFileStream);
}

void bitmapCore::setOutputFileStream(std::ofstream *outputFileStream)
{
	ofs = outputFileStream;
}

/* example.cpp

#include "./bitmapCore.hpp"
#include <fstream>
#include <cmath>
using namespace std;

int main(int argc, char **argv)
{
	ofstream ofs("img.bmp",ios_base::trunc);
	bitmapCore bmp(&ofs);
	bitmapCore::pixel* pxls = new bitmapCore::pixel[200];
	bmp.writeHeader(200,200);
	for (int Y = 0; Y < bmp.getHeight(); ++Y)
	{
		for (int X = 0; X < bmp.getWidth(); ++X)
		{
			// {blue%0xFF, green%0xFF, red%0xFF}
			pxls[X] = {(uint8_t)(0xFF*(X/(double)bmp.getWidth())),
			           (uint8_t)(0xFF*(Y/(double)bmp.getHeight())),
			           0};
		}
		bmp.writeLine(pxls);
		bmp.endLine();
	}
	delete [] pxls;
	ofs.close();
	return 0;
}

*/
