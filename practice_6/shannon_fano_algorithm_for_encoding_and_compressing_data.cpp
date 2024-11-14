#include <bits/stdc++.h>
using namespace std;
 
struct node { // Структура массива
    string sym;
    float pro;
    int in;
    int arr[24];
    int top;
} p[24];
 
void shannon(int l, int h, node p[]) { // Алгоритм Шеннона-Фано
    float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
    int i, d, k, j;
    if ((l + 1) == h || l == h || l > h) {
        if (l == h || l > h)
            return;
        p[h].arr[++(p[h].top)] = 0;
        p[l].arr[++(p[l].top)] = 1;
        return;
    }
    else {
        for (i = l; i <= h - 1; i++)
            pack1 = pack1 + p[i].pro;
        pack2 = pack2 + p[h].pro;
        diff1 = pack1 - pack2;
        if (diff1 < 0)
            diff1 = diff1 * -1;
        j = 2;
        while (j != h - l + 1) {
            k = h - j;
            pack1 = pack2 = 0;
            for (i = l; i <= k; i++)
                pack1 = pack1 + p[i].pro;
            for (i = h; i > k; i--)
                pack2 = pack2 + p[i].pro;
            diff2 = pack1 - pack2;
            if (diff2 < 0)
                diff2 = diff2 * -1;
            if (diff2 >= diff1)
                break;
            diff1 = diff2;
            j++;
        }
        k++;
        for (i = l; i <= k; i++)
            p[i].arr[++(p[i].top)] = 1;
        for (i = k + 1; i <= h; i++)
            p[i].arr[++(p[i].top)] = 0;
 
        shannon(l, k, p);
        shannon(k + 1, h, p);
    }
}

void reverse(node arr[], int n) { // Упорядочивание элементов массива
    for (int low = 0, high = n - 1; low < high; low++, high--) {
        swap(arr[low].pro, arr[high].pro);
        swap(arr[low].sym, arr[high].sym);
        swap(arr[low].in, arr[high].in);
    }
}
 
void sortBubble(int n, node p[]) { // Пузырьковая сортировка
    int i, j;
    node temp;
    for (j = 1; j <= n - 1; j++) {
        for (i = 0; i < n - 1; i++) {
            if ((p[i].pro) < (p[i + 1].pro)) {
                swap(p[i].pro, p[i + 1].pro);
                swap(p[i].sym, p[i + 1].sym);
                swap(p[i].in, p[i + 1].in);
            }
        }
    }
    reverse(p, n);
}

void display(int n, node p[]) { // Вывод значений на консоль
    int i, j;
    cout << "\n\n\tСимвол\tВероястность\tКод";
    for (i = n - 1; i >= 0; i--) {
        cout << "\n\t" << p[i].sym << "\t" << p[i].pro << "\t\t";
        for (j = 0; j <= p[i].top; j++) {
            cout << p[i].arr[j];
        }
    }
}

void compPers(int n) { // Определение процента сжатия
    float temp1 = 0;
    float temp2 = 0;
    for (int i = 0; i < n; i++) {
        temp1 += p[i].in;
        temp2 += p[i].in * (p[i].top + 1);
    }
    cout << "\n\nНе закодированная фраза: " << temp1 * 8 << " бит" << endl;
    cout << "Закодированная фраза: " << temp2 << " бит" << endl;
    cout << "Процент сжатия: " << temp2 / (temp1 * 8) * 100 << " %" << endl;

}
 
int main() { // Основная функция программы
    int n, i, j;
    float total = 0;
    string ch;
    node temp;
    string mass[] = {"А", "н", "а", "-", "д", "э", "у", "с", "р", "и", "к", "п", ",", " ", "Д", "о", "м", "ы", "т", "Э", "Б", "Ц", "!"};
    float x[] = {0.03, 0.06, 0.07, 0.12, 0.04, 0.04, 0.07, 0.07, 0.04, 0.06, 0.09, 0.02, 0.03, 0.03, 0.02, 0.04, 0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.02};
    int y[] = {2, 4, 5, 8, 3, 3, 5, 5, 3, 4, 6, 1, 2, 2, 1, 3, 2, 2, 2, 1, 1, 1, 1};
    n = 23;

    cout << "\nПрактическая работа №6. Кодирование и сжатие данных методами без потерь. Задание №1 (метод Шеннона-Фано). Киселёв Максим. ИКБО-08-21. Вариант №14.\n" << endl;
    cout << "Введите количесвто символов: ";
    cout << n << endl;

    for (i = 0; i < n; i++) {
        cout << "Введите символ: " << i + 1 << " : ";
        ch = mass[i];
        cout << ch << endl;
        p[i].sym += ch;
    }

    cout << "\n\n";

    for (i = 0; i < n; i++) {
        cout << "Введите вероятность символа " << p[i].sym << ": ";
        cout << x[i] << endl;
        p[i].pro = x[i];
        p[i].in = y[i];
        total = total + p[i].pro;
        if (total > 1) {
            cout << "Неверная вероястность, введите новое значение: ";
            total = total - p[i].pro;
            i--;
        }
    }

    sortBubble(n, p);

    for (i = 0; i < n; i++) {
        p[i].top = -1;
    }
 
    shannon(0, n - 1, p);
 
    display(n, p);

    compPers(n);

    return 0;
}