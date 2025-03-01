#include <iostream>
#include "BMPProcessor.h"

using std::cout;
using std::endl;
using std::cin;
using std::cerr;

int main()
{
    setlocale(LC_ALL, "ru");

    BMPProcessor processor{};
    string inputFilename{};
    cout << "Введите путь BMP файла: ";
    cin >> inputFilename;

    if (!processor.Load(inputFilename))
    {
        return 1;
    }
    cout << "Оригиналдьное изображение:" << endl;
    processor.Display();

    int width = processor.GetWidth();
    int height = processor.GetHeight();
    processor.DrawLine(0, 0, width - 1, height - 1);
    processor.DrawLine(0, height - 1, width - 1, 0);

    cout << "Модифицированное изображение: " << endl;
    processor.Display();

    string outputGilename{};
    cout << "Укажите путь сохранения BMP файла: " << endl;
    cin >> outputGilename;

    if (!processor.Save(outputGilename))
    {
        cerr << "Ошибка сохранения BMP файла" << endl;
        return 1;
    }

    cout << "Файл успешно сохранен в " << outputGilename << endl;
    return 0;
}