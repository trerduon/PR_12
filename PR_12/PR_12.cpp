#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

string converter_to16(int num) //�������������� ����� �� ���������� ������� ��������� � �����������������
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

int converter_to10(string num) //�������������� ����� �� ����������������� ������� ��������� � ����������
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
    cout << "�������: \n[1], ����� ��������� ���������� ������� ������� \n[2], ����� ��������� ������� ������������������������ �������\n";
    bool flag = 0;
    string strread;
    int way;
    string matrix[4][4];//������� �������� � ����������������� ������� ���������
    int matrixten[4][4];//������� �������� � ���������� ������� ���������
    while (flag == 0)
    {
        cin >> strread;
        try
        {
            way = stoi(strread);
            if (way != 1 && way != 2) cout << "������� ����� ����� � ��������� �� 1 �� 2!" << endl;
            else flag = 1;
        }
        catch (const exception) { cout << "������� ����� ����� � ��������� �� 1 �� 2!" << endl; }
    }
    cout << "\n\n";
    flag = 0;

    char symbol[22] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'a', 'b', 'c', 'd', 'e', 'f' };//������ ��������, �� ������� ����� �������� ����� � ����������������� ������� ��������
    switch (way)
    {
    case 1:
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                flag = 0;
                cout << "������� ������� " << i + 1 << " ������, " << j + 1 << " ������� " << endl;
                while (flag == 0)
                {
                    int count = 0;
                    string element;
                    cin >> element;
                    if (element.length() == 2)//�������� ���������� ����� �� ������������
                    {
                        for (int i = 0; i < 22; i++)
                        {
                            if (element[0] == symbol[i]) count++;//�������� ������ ����� ����� �� �������������� ���������� ����� ����������������� ������� ���������
                            if (element[1] == symbol[i]) count++;//�������� ������ ����� ����� �� �������������� ���������� ����� ����������������� ������� ���������
                        }
                        if (count == 2)//�������� ����� �� �������������� ���������� ����� ����������������� ������� ���������
                        {
                            matrix[i][j] = element;
                            matrixten[i][j] = converter_to10(element);
                            flag = 1;
                        }
                        else cout << "������� �����, ���������� ����� � ����������������� �������� ���������!" << endl;
                    }
                    else cout << "������� �����, ���������� ����� � ����������������� �������� ���������!" << endl;
                }
            }
    }
    break;
    case 2:
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                int element = rand() % (256 - 16 + 1) + 16;//������������ ��������� ������� � ���������� ������� ��������� � ��������� [16;256]
                matrixten[i][j] = element;//��������������� ������� ������������ � ������� �� ��������� � ���������� ������� ���������
                matrix[i][j] = converter_to16(element);//��������������� ������� ����������� � ����������������� ������� ��������� � ������������ � ������� �� ��������� ����������������� ������� ���������
            }
    }
    break;
    }

    cout << "�������� �������: \n" << endl;
    for (int i = 0; i < 4; i++)//����� �������� �������
    {
        for (int j = 0; j < 4; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "\n\n";

    for (int k = 0; k < 4; k++)
        for (int i = 0; i < 4; i++)//���������� "���������"
            for (int j = 0; j < 3; j++)
            {
                if ((k + 1) % 2 == 1)//�������� ������ ������� �� ����������
                    if (matrixten[j][k] > matrixten[j + 1][k])
                    {
                        //������������ ��������� � ������� � ���������� � ���������� ������� ���������
                        int x = matrixten[j][k];
                        matrixten[j][k] = matrixten[j + 1][k];
                        matrixten[j + 1][k] = x;

                        //������������ ��������� � ������� � ���������� � ����������������� ������� ���������
                        string y = matrix[j][k];
                        matrix[j][k] = matrix[j + 1][k];
                        matrix[j + 1][k] = y;
                    };
                if ((k + 1) % 2 == 0)//�������� ������ ������� �� ����������
                    if (matrixten[j][k] < matrixten[j + 1][k])
                    {
                        //������������ ��������� � ������� � ���������� � ���������� ������� ���������
                        int x = matrixten[j][k];
                        matrixten[j][k] = matrixten[j + 1][k];
                        matrixten[j + 1][k] = x;

                        //������������ ��������� � ������� � ���������� � ����������������� ������� ���������
                        string y = matrix[j][k];
                        matrix[j][k] = matrix[j + 1][k];
                        matrix[j + 1][k] = y;
                    };
            }

    cout << "��������������� �������: \n" << endl;
    for (int i = 0; i < 4; i++)//����� ��������������� �������
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
