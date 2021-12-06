#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

string converter_to16(int num) //Преобразование числа из десятичной системы счисления в шестнадцатеричную
{
    string newnum;
    int c[2];
    int i = 0;
    c[i] = num % 16;
    while (num / 16 != 0)
    {
        i++;
        num /= 16;
        c[i] = num % 16;
    }

    for (i; i >= 0; i--)
    {
        if (c[i] < 10)
            newnum += to_string(c[i]);
        if (c[i] == 10)
            newnum += "A";
        if (c[i] == 11)
            newnum += "B";
        if (c[i] == 12)
            newnum += "C";
        if (c[i] == 13)
            newnum += "D";
        if (c[i] == 14)
            newnum += "E";
        if (c[i] == 15)
            newnum += "F";
    }
    return newnum;
}

int converter_to10(string num) //Преобразование числф из шестнадцетиричной системы счисления в десятичную
{
    int newnum, k, p;
    newnum = 0;
    p = num.length() - 1;
    for (int i = 0; num[i] != '\0'; i++)
    {
        switch (toupper(num[i]))
        {
        case '0': k = 0; break;
        case '1': k = 1; break;
        case '2': k = 2; break;
        case '3': k = 3; break;
        case '4': k = 4; break;
        case '5': k = 5; break;
        case '6': k = 6; break;
        case '7': k = 7; break;
        case '8': k = 8; break;
        case '9': k = 9; break;
        case 'A': k = 10; break;
        case 'B': k = 11; break;
        case 'C': k = 12; break;
        case 'D': k = 13; break;
        case 'E': k = 14; break;
        case 'F': k = 15; break;
        }
        newnum = newnum + k * pow(10, p);
        p--;
    }
    return newnum;
}


int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));
    cout << "Введите: \n[1], чтобы заполнить квадратную матрицу вручную \n[2], чтобы заполнить матрицу случайносгенерированными числами\n";
    bool flag = 0;
    string strread;
    int way;
    string matrix[4][4];//Матрица символов в шестнадцатеричной системе счисления
    int matrixten[4][4];//Матрица символов в десятичной системе счисления
    while (flag == 0)
    {
        cin >> strread;
        try
        {
            way = stoi(strread);
            if (way != 1 && way != 2) cout << "Введите целое число в интервале от 1 до 2!" << endl;
            else flag = 1;
        }
        catch (const exception) { cout << "Введите целое число в интервале от 1 до 2!" << endl; }
    }
    cout << "\n\n";
    flag = 0;

    char symbol[22] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'a', 'b', 'c', 'd', 'e', 'f' };//Массив символов, из которых может состоять число в шестнадцатеричной системе счисленя
    switch (way)
    {
    case 1:
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                flag = 0;
                cout << "Введите элемент " << i + 1 << " строки, " << j + 1 << " столбца " << endl;
                while (flag == 0)
                {
                    int count = 0;
                    string element;
                    cin >> element;
                    if (element.length() == 2)//Проверка введенного числа на двузначность
                    {
                        for (int i = 0; i < 22; i++)
                        {
                            if (element[0] == symbol[i]) count++;//Проверка первой цифры числа на принадлежность введенного числа шестнадцатеричной системе счисления
                            if (element[1] == symbol[i]) count++;//Проверка второй цифры числа на принадлежность введенного числа шестнадцатеричной системе счисления
                        }
                        if (count == 2)//Проверка числа на принадлежность введенного числа шестнадцатеричной системе счисления
                        {
                            matrix[i][j] = element;
                            matrixten[i][j] = converter_to10(element);
                            flag = 1;
                        }
                        else cout << "Введите целое, двузначное число в шестнадцатеричной сисчтеме счисления!" << endl;
                    }
                    else cout << "Введите целое, двузначное число в шестнадцатеричной сисчтеме счисления!" << endl;
                }
            }
    }
    break;
    case 2:
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                int element = rand() % (256 - 16 + 1) + 16;//Генерируется случайный элемент в десятичной системе счисления в интервале [16;256]
                matrixten[i][j] = element;//Сгенерированный элемент записывается в матрицу из элементов в десятичной системе счисления
                matrix[i][j] = converter_to16(element);//Сгенерированный элемент переводится в шестнадцатеричную систему счисления и записывается в матрицу из элементов шестнадцатеричной системы счисления
            }
    }
    break;
    }

    cout << "Исходная матрица: \n" << endl;
    for (int i = 0; i < 4; i++)//Вывод исходной матрицы
    {
        for (int j = 0; j < 4; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "\n\n";

    for (int k = 0; k < 4; k++)
        for (int i = 0; i < 4; i++)//Сортирвока "пузырьком"
            for (int j = 0; j < 3; j++)
            {
                if ((k + 1) % 2 == 1)//Проверка номера столбца на нечетность
                    if (matrixten[j][k] > matrixten[j + 1][k])
                    {
                        //Перестановка элементов в матрице с элементами в десятичной системе счисления
                        int x = matrixten[j][k];
                        matrixten[j][k] = matrixten[j + 1][k];
                        matrixten[j + 1][k] = x;

                        //Перестановка элементов в матрице с элиментами с шестнадцатеричной системе счисления
                        string y = matrix[j][k];
                        matrix[j][k] = matrix[j + 1][k];
                        matrix[j + 1][k] = y;
                    };
                if ((k + 1) % 2 == 0)//Проверка номера столбца на нечетность
                    if (matrixten[j][k] < matrixten[j + 1][k])
                    {
                        //Перестановка элементов в матрице с элементами в десятичной системе счисления
                        int x = matrixten[j][k];
                        matrixten[j][k] = matrixten[j + 1][k];
                        matrixten[j + 1][k] = x;

                        //Перестановка элементов в матрице с элиментами с шестнадцатеричной системе счисления
                        string y = matrix[j][k];
                        matrix[j][k] = matrix[j + 1][k];
                        matrix[j + 1][k] = y;
                    };
            }

    cout << "Отсортированная матрица: \n" << endl;
    for (int i = 0; i < 4; i++)//Вывод отсортированной матрицы
    {
        for (int j = 0; j < 4; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }

    string end;
    cin >> end;
}
