
#include <iostream>
#include<io.h>
#include<iomanip>
#include<stdio.h>
#include<string.h>
#include<Windows.h>
using namespace std;

struct Students {
    char LastName[255];
    int Number;
    float Fiz;
    float Mat;
    float Inf;
    float SrBal;
};

int CountOfStudents(FILE* file);
Students In();
void NewFile(FILE* file, char name[255]);
void ReadFile(FILE* file, char name[255]);
void AddStudent(FILE* file, char name[255]);
void Zadanie(FILE* file, char name[255]);


void meny() {
    int index = 2, m;
    char name[255];

    FILE* file = NULL;
    while (true) {
        cout << "Введите название файла\n";
        cin >> name;
        cout << "Выберите:\n1)Создать файл\n2)Просмотреть файл\n3)Добавить\n4)Найти студентов из определенной группы с определенным средним баллом"
            << "\n0)выйти из программы\n";
        cin >> index;
        switch (index)
        {
        case 1:
            SetConsoleCP(1251);
            NewFile(file, name);
            SetConsoleCP(866);
            break;
        default:
        case 2:
            ReadFile(file, name);
            break;
        case 3:
            AddStudent(file, name);
            break;
        case 4:
            Zadanie(file, name);
            break;
        case 0:
            return;
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    meny();
    return 0;
}

Students In() {
    Students z;
    cout << "Введите Фамилию студента\n";
    fflush(stdin);
    cin >> z.LastName; 
    cout << "Введите номер группы\n";
    cin >> z.Number;
    cout << "Введите оценку по физике\n";
    cin >> z.Fiz;
    cout << "Введите оценку по математике\n";
    cin >> z.Mat;
    cout << "Введите оценку по информатике\n";
    cin >> z.Inf;
    z.SrBal = (z.Fiz + z.Mat + z.Inf) / 3;
    cout << "Средний балл =" << z.SrBal << endl;
    return z;
}
int CountOfStudents(FILE* file) {
    int count;
    fseek(file, 0, SEEK_END);
    count = ftell(file) / sizeof(Students);
    fseek(file, 0, SEEK_SET);
    return count;
}
void NewFile(FILE* file, char name[255]) {
    int n;
    Students Spisok;
    fopen_s(&file, name, "wb");
    cout << "Введите количество студентов\n";
    cin >> n;
    for (int i = 0; i < n; i++) {
        Spisok = In();
        fwrite(&Spisok, sizeof(Students), 1, file);
    }
    fclose(file);
    cout << endl;
}
void ReadFile(FILE* file, char name[255]) {
    Students per;
    int k = 0;
    fopen_s(&file, name, "rb");
    if (file != NULL) {
        cout << " Группа   Фамилия   Физика   Математика   Информатика   Средний балл\n";
        while (fread(&per, sizeof(Students), 1, file))
        {
            k++;
            
            cout << " " << per.Number << "      " << per.LastName << "          " << per.Fiz <<"          " << per.Mat <<"            " << per.Inf <<"             " << per.SrBal << endl;
        }
        fclose(file);
    }
    else
        cout << "Файл не существует.\n";
    cout << endl;
}
void AddStudent(FILE* file, char name[255]) {
    int n;
    Students Spisok;
    ReadFile(file, name);
    fopen_s(&file, name, "ab");
    cout << "Введите количество студентов\n";
    cin >> n;
    
    fseek(file, 0, SEEK_END);
    for (int i = 0; i < n; i++) {
        Spisok = In();
        fwrite(&Spisok, sizeof(Students), 1, file);
    }
    fclose(file);
    cout << "резултат функции\n";
    ReadFile(file, name);
    cout << endl;
}
void Zadanie(FILE* file, char name[255]) {
    int numbers=0;
    double srbal=0;
    bool flag=false;
    cout << "Введите номер группы:"; cin >> numbers;
    cout << "Введите средний балл:"; cin >> srbal;
    //ReadFile(file, name);
    //cout << "резултат функции\n";
    fopen_s(&file, name, "rb");
    if (file != NULL) {
        Students per;
        cout << " Группа   Фамилия   Физика   Математика   Информатика   Средний балл\n";
        while (fread(&per, sizeof(Students), 1, file)) {
            if (per.Number == numbers and per.SrBal > srbal)
            {
                cout << " " << per.Number << "      " << per.LastName << "          " << per.Fiz << "          " << per.Mat << "            " << per.Inf << "             " << per.SrBal << endl;
                flag = true;
            }
        }
        fclose(file);
    }
    else
        cout << "Файл не существует";
    cout << endl;
}