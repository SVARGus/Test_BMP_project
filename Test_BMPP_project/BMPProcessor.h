#pragma once
#include <vector>
#include <string>
#include <Windows.h>

using std::vector;
using std::string;

class BMPProcessor
{
private:
	BITMAPFILEHEADER fileHeader{}; // Заголовок BMP файла (структура)
	BITMAPINFOHEADER infoHeader{}; // Информационный заголовок со сведения о измерениях и цветовом формате (структура)
	vector<uint8_t> pixels{};
	int width{};
	int height{};
	int rowSize{};
	void SetPixel(int x, int y); // Закрашивание пиксепля
public:
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	bool Load(const string& filename); // Чтение данных из файла
	bool Save(const string& filename); // Запись в файл
	void Display(); // Вывод символов в консоль
	void DrawLine(int x1, int y1, int x2, int y2); // Рисование линий на основе алгоритма Брезенхэма
};

