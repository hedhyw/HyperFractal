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
 * File:   bitmapCore.hpp
 * Author: hedhyw
 *
 * Created on October 29, 2016, 5:21 PM
 */

#ifndef BITMAPCORE_HPP
#define BITMAPCORE_HPP

#include <fstream>
// {blue, green, red} color format
// start point in bottom left

class bitmapCore
{
	private:
		std::ofstream *ofs;
		char align[4] = {0,0,0,0};
		#pragma pack(push,1)
		struct bitmapFileHeader
		{
			uint8_t type[2] = {'B', 'M'}; // Bitmap
			uint32_t size;
			uint16_t res[2] = {0,0}; // reserve
			uint32_t offset;
		} bitmapFileHeader1;
		struct bitmapInformationHeader // CORE ver.
		{
			uint32_t header_size;
			uint16_t width;
			uint16_t height;
			uint16_t planes = 1; // Bitmap
			uint16_t bits = 24; // rgb
		} bitmapInformationHeader1;
		#pragma pack(pop)
	public:
		#pragma pack(push,1)
		struct pixel
		{
			uint8_t blue;
			uint8_t green;
			uint8_t red;
		};
		#pragma pack(pop)
		uint16_t getWidth();
		uint16_t getHeight();
		void writePixel(pixel pxl);
		void writeLine(pixel* pxls);
		void endLine();
		void writeHeader(uint16_t width, uint16_t height);
		void setOutputFileStream(std::ofstream *outputFileStream);
		bitmapCore();
		bitmapCore(std::ofstream *outputFileStream);
};

#endif /* BITMAPCORE_HPP */

