/*
14 Вариант
1) 12-ый, 14-ый, 3-ий
2) Все нечетные
3) 512
4) 512
5) Установить n-ый бит в 1, используя маску 2
*/

#include <iostream>
#include <iomanip>
using namespace std;

void coutp (unsigned int x) {
    int n = sizeof(int) * 8;
    unsigned mask = (1 << (n-1));
    for(int i=1; i <= n; i++) {
        cout << ((x & mask) >> (n-i));
        mask = mask >> 1;
    }   
    cout << endl;
}

unsigned int taskOne(unsigned int x) {
    return x | 0b101000000001000;
}

unsigned int taskTwo(unsigned int x) {
    return x & 0b101010101010101;
}

unsigned int taskThree(unsigned int x) {
    return x << 9;
}

unsigned int taskFour(unsigned int x) {
    return x >> 9;
}

unsigned int taskFive(unsigned int x, unsigned int mask, int n) {
    mask = 1 << 31;
    mask = mask >> (31 - n);
    coutp(mask);
    return x | mask;
}

void coutRes(unsigned int x, unsigned int mask, unsigned int res) {
    cout << left;
    cout << "x↓10 = " << x << "; " << "mask↓10 = " << mask << ";" << endl;
    cout << setw(11) << "x↓2 = ";
    coutp(x);
    cout << setw(11) << "mask↓2 = ";
    coutp(mask);
    cout << setw(11) << "res↓2 = ";
    coutp(res);
}

int main()
{
    unsigned int x,res,mask;
    int n,i;

    cout << "Список доступных комманд:" << endl;
    cout << "0) Завершение работы" << endl;
    cout << "1) Замена указанных битов на 1" << endl;
    cout << "2) Замена указанных битов на 0" << endl;
    cout << "3) Умножение с помощью поразрядных операций" << endl;
    cout << "4) Деление с помощью поразрядных операций" << endl;
    cout << "5) Установка n-го бита в 1" << endl;
    cout << "Выберите команду: ";

    while (true) {
        while (true) {
            cin >> i;
            if (0 <= i && i <= 5) break;
            cout << "Неверная команда. Попробуйте снова." << endl;
        }
        switch (i) {
        case 0:
            return 0;
        case 1: {
            x = 0x4E20;
            mask = 0b101000000001000;
            res = taskOne(x);
            cout << "\n";
            coutRes(x, mask, res);
            break;
        }
        case 2: {
            cout << "\nВведите x↓10: ";
            cin >> x;
            mask = 0x55555555;
            res = taskTwo(x);
            coutRes(x, mask, res);
            break;
        }
        case 3: {
            cout << "\nВведите x↓10: ";
            cin >> x;
            res = taskThree(x);
            cout << "res↓10 = " << res << "; res↓2 = ";
            coutp(res);
            break;
        }
        case 4: {
            cout << "\nВведите x↓10: ";
            cin >> x;
            res = taskFour(x);
            cout << "res↓10 = " << res << "; res↓2 = ";
            coutp(res);
            break;
        }
        case 5: {
            cout << "\nВведите x↓10: ";
            cin >> x;
            cout << "Введите n: ";
            cin >> n;
            cout << left;
            cout << setw(16) << "x↓2 = ";
            coutp(x);
            cout << setw(16) << "maskNbit↓2 = ";
            res = taskFive(x, mask, n);
            cout << setw(16) << "res↓2 = ";
            coutp(res);
            break;
        }
        default:
            break;
        }
        cout << "\nСледующая команда: ";
    }
    return 0;
}
