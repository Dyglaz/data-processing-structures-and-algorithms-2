#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

struct SampleSubstring{
    int substringNumb;
	string substring;
	SampleSubstring(int _substringNumb, string _substring) : substringNumb(_substringNumb), substring(_substring) {}
	SampleSubstring() {}
};

ostream& operator<<(ostream& out, SampleSubstring& s) {
	out << s.substringNumb << " " << left << setw(5) << s.substring;
	return out;
}

void wordRepresentation(string text) {
	string punctuationMarks = ".?!;,:";
    size_t min,max;
    string rep1,rep2;

    for (int i = 0; i < text.size(); i++) {
        if (punctuationMarks.find(text[i]) != string::npos) {
            min = i;
            break;
        }
    }
    for (int i = text.size() - 2; 0 < i; i--) {
        if (punctuationMarks.find(text[i]) != string::npos) {
            max = i;
            break;
        }
    }

    rep1 = text.substr(0, min);
    rep2 = text.substr(max + 1, text.length() - max - 2);

    text.replace(max + 1, text.length() - max - 2, rep1);
    text.replace(0, min, rep2);

    cout << "Результат редактирования: " << text << endl;
}


class HashTable {
private:

	vector<SampleSubstring*> hashTable;
	int numElems;

public:

    // Конструктор, задающий размер таблицы
	HashTable(int capacity) {
		numElems = 0;
		hashTable = vector<SampleSubstring*>(capacity);
	}

	// Функция хеширования
	int hash1(int substringNumb) {
		return substringNumb % hashTable.size();
	}

    int hash2(int substringNumb) {
		return 1 + substringNumb % (hashTable.size() - 2);
	}

    int hash3(int substringNumb, int i) {
		return (hash1(substringNumb) + i * hash2(substringNumb)) % hashTable.size();
	}

	// Операция вставки
	void push(SampleSubstring* obj) {
        if (numElems / (hashTable.size() * 1.0) >= 0.75) {
			rehash();
		}
        for (int i = 0; i < hashTable.size(); i++) {
            int hashId = hash3(obj->substringNumb, i);
            if (hashTable[hashId] == NULL) {
                hashTable[hashId] = obj;
                numElems++;
                return;
            }
        }
	}

	// Операция рехеширования
	void rehash() {
		vector<SampleSubstring*> temp = hashTable;
		hashTable.clear();
		hashTable.resize(temp.size() * 2);
		numElems = 0;
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i] != NULL && temp[i]) {
				push(temp[i]);
			}
		}
		
	}

	// Операция вывода образцов и их количество входов в основной текст
	void printNumberOfOccurrences(string text) {
		int n = text.length();
		int temp, m, j, k, i;
		for (i = 0; i < hashTable.size(); i++) {
			if (hashTable[i] != NULL) {
				temp = 0;
				m = hashTable[i]->substring.length();
				for (k = 0; k <= n - m; k++) {
					for (j = 0; j < m; ++j) {
						if (hashTable[i]->substring[j] != text[k + j]) {
							break;
						}
					}
					if (j == m) {
						temp++;
					}
				}
				cout << *hashTable[i] << " повторений в тексте: " << temp << endl;
			}
		}
	}

	void searchPattern(string & text, string & pattern) {

      int n = text.length();
      int m = pattern.length();

      int j;
      for (int i = 0; i <= n - m; i++) {

        for (j = 0; j < m; ++j) {
          if (pattern[j] != text[i + j]) {
            break;
          }
        }

        if (j == m) {
          cout << "index = " << i << "\n";
        }
      }
    }
};

int main() {
	cout << "Практическая работа №3. Поиск образца в тексте. Киселёв Максим. ИКБО-08-21. Вариант №14." << endl;
	cout << "Введите размер хеш-таблицы: ";
	int size, cmd;
    bool addElem;
	cin >> size;
	HashTable hashTable = HashTable(size);
	cout << "Заполнить таблицу несколькими записями? 1/0 ";
	cin >> addElem;
	if (addElem) {
		hashTable.push(new SampleSubstring(1001, "abc"));
		hashTable.push(new SampleSubstring(1002, "qwe"));
		hashTable.push(new SampleSubstring(1003, "rty"));
		hashTable.push(new SampleSubstring(1004, "uio"));
		hashTable.push(new SampleSubstring(1005, "aaa"));
        hashTable.push(new SampleSubstring(1006, "bbb"));
        hashTable.push(new SampleSubstring(1007, "bnm"));
	}

	cout << "Список доступных комманд:" << endl;
	cout << "0) Завершение работы" << endl;
	cout << "1) Переставить первое и последнее слово в тексте" << endl;
	cout << "2) Добавить подстроку образца в хеш-таблицу" << endl;
	cout << "3) Проверка количества того, сколько раз каждый из образцов входит в текст" << endl;

	while (true) {
		while (true) {
			cin >> cmd;
			if (0 <= cmd && cmd <= 5) break;
			cout << "Неверная команда. Попробуйте снова." << endl;
		}
		switch (cmd)
		{
		case 0:
			return 0;
		case 1: {
			string text;
			cout << "Введите текст, разделённый знаками препинания, для редактирования:\n";
			cin >> text;
			wordRepresentation(text);
			break;
		}
		case 2: {
			int substringNumb;
			string substring;
			cout << "Введите номер и подсроку образца:\n";
			cin >> substringNumb >> substring;
			SampleSubstring* obj = new SampleSubstring(substringNumb, substring);
			hashTable.push(obj);
			break;
		}
		case 3: {
			string text;
			cout << "Введите текст, по которому будет производиться поиск:\n";
			cin >> text;
			hashTable.printNumberOfOccurrences(text);
			break;
		}
		default:
			break;
		}
		cout << endl << "Следующая команда: " << endl;
	}
}
