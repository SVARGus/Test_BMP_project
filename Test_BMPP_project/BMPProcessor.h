#pragma once
#include <vector>
#include <string>
#include <Windows.h>

using std::vector;
using std::string;

class BMPProcessor
{
private:
	BITMAPFILEHEADER fileHeader{}; // ��������� BMP ����� (���������)
	BITMAPINFOHEADER infoHeader{}; // �������������� ��������� �� �������� � ���������� � �������� ������� (���������)
	vector<uint8_t> pixels{};
	int width{};
	int height{};
	int rowSize{};
	void SetPixel(int x, int y); // ������������ ��������
public:
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	bool Load(const string& filename); // ������ ������ �� �����
	bool Save(const string& filename); // ������ � ����
	void Display(); // ����� �������� � �������
	void DrawLine(int x1, int y1, int x2, int y2); // ��������� ����� �� ������ ��������� ����������
};

