#include "BMPProcessor.h"
#include <fstream>
#include <iostream>

using std::endl;
using std::cout;
using std::cerr;
using std::ifstream;
using std::ofstream;

bool BMPProcessor::Load(const string& filename)
{
	ifstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		cerr << "Ошибка открытия файла: " << filename << endl;
		return false;
	}
	file.read((char*)&fileHeader, sizeof(fileHeader));
	file.read((char*)&infoHeader, sizeof(infoHeader));


	if (infoHeader.biBitCount != 24 && infoHeader.biBitCount != 32) // Проверка битности 24 и 32 бита
	{
		cerr << "Ошибка загрузки файла. BMP файл не является 24-bit или 32-bit." << endl;
		return false;
	}

	width = infoHeader.biWidth;
	height = infoHeader.biHeight;

	rowSize = ((width * (infoHeader.biBitCount / 8)) + 3) & ~3; // Вычисление размера строки с учетом выравнивания для 24 и 32 бит на пиксель

	pixels.resize(rowSize * height);
	file.seekg(fileHeader.bfOffBits);
	file.read((char*)pixels.data(), pixels.size());
	return true;
}

bool BMPProcessor::Save(const string& filename)
{
	ofstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		cerr << "Ошибка открытия файла: " << filename << endl;
		return false;
	}
	file.write((char*)&fileHeader, sizeof(fileHeader));
	file.write((char*)&infoHeader, sizeof(infoHeader));
	file.seekp(fileHeader.bfOffBits);
	file.write((char*)pixels.data(), pixels.size());
	return true;
}

void BMPProcessor::Display()
{
	for (int y = height - 1; y >= 0; --y)
	{
		for (int x = 0; x < width; ++x)
		{
			int offset = y * rowSize + x * (infoHeader.biBitCount / 8);
			uint8_t B = pixels[offset];
			uint8_t G = pixels[offset+1];
			uint8_t R = pixels[offset+2];
			if (R == 255 && G == 255 && B == 255)
				cout << ' ';
			else if (R == 0 && G == 0 && B == 0)
				cout << '#';
		}
		cout << endl;
	}
}

void BMPProcessor::DrawLine(int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1);
	int sx = x1 < x2 ? 1 : -1;
	int dy = -abs(y2 - y1);
	int sy = y1 < y2 ? 1 : -1;
	int err = dx + dy;
	while (true)
	{
		SetPixel(x1, y1);
		if (x1 == x2 && y1 == y2)
			break;
		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x1 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void BMPProcessor::SetPixel(int x, int y)
{
	int offset = (height - 1 - y) * rowSize + x * (infoHeader.biBitCount / 8);
	pixels[offset] = 0; // B
	pixels[offset + 1] = 0; // G
	pixels[offset + 2] = 0; // R
}
