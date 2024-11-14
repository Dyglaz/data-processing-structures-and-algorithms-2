#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

struct RegSmallBusin{
    int license;
	string name;
	string founder;
	RegSmallBusin(int _license, string _name, string _founder) : license(_license), name(_name), founder(_founder) {}
	RegSmallBusin() { }
};

ostream& operator<<(ostream& out, RegSmallBusin& s) {
	out << s.license << " " << left << setw(5) << s.name << " " << s.founder;
	return out;
}

class HashTable {
private:

	vector<RegSmallBusin*> hashTable;
	int numElems;
	RegSmallBusin* delElem = new RegSmallBusin();

public:
    // Конструктор, задающий размер таблицы
	HashTable(int capacity) {
		numElems = 0;
		hashTable = vector<RegSmallBusin*>(capacity);
	}

	// Функция хеширования
	int hash1(int licens) {
		return licens % hashTable.size();
	}

    int hash2(int licens) {
		return 1 + licens % (hashTable.size() - 2);
	}

    int hash3(int licens, int i) {
		return (hash1(licens) + i * hash2(licens)) % hashTable.size();
	}

	// Операция вставки
	void push(RegSmallBusin* obj) {
        if (numElems / (hashTable.size() * 1.0) >= 0.75) {
			rehash();
		}
        for (int i = 0; i < hashTable.size(); i++) {
            int hashId = hash3(obj->license, i);
            if (hashTable[hashId] == NULL || hashTable[hashId] == delElem) {
                hashTable[hashId] = obj;
                numElems++;
                return;
            }
        }
	}

	// Операция рехеширования
	void rehash() {
		vector<RegSmallBusin*> temp = hashTable;
		hashTable.clear();
		hashTable.resize(temp.size() * 2);
		numElems = 0;
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i] != NULL && temp[i] != delElem) {
				push(temp[i]);
			}
		}
		
	}

	// Операция вывода таблицы
	void print() {
		for (int i = 0; i < hashTable.size(); i++) {
			if (hashTable[i] != NULL && hashTable[i] != delElem) {
				cout << *hashTable[i] << endl;;
			}
			
		}
	}

	// Операция поиска по ключу
	RegSmallBusin* find(int license) { 
        for (int i = 0; i < hashTable.size(); i++) {
            int hashId = hash3(license, i);
            if (hashTable[hashId]->license == license) {
                return hashTable[hashId];
            }
        }
        return NULL;
    }

	// Операция удаления
	void deletEl(int license) {
        for (int i = 0; i < hashTable.size(); i++) {
            int hashId = hash3(license, i);
            if (hashTable[hashId]->license == license) {
                hashTable[hashId] = delElem;
                return;
            }
        }
    }

	// Получить размер таблицы
	int get() {
		return hashTable.size();
	}
};

/*
Приложение должно содержать класс с базовыми операциями : вставки, удаления, поиска по ключу, вывода.
Включите в класс массив полезных данных и хеш - таблицу.
Хеш - функцию подберите самостоятельно, используя правила выбора функции.
Реализуйте расширение размера таблицы и рехеширование, когда это требуется, в соответствии с типом разрешения коллизий.
*/

int main()
{
	cout << "Практическая работа №2. Таблица хеширования" << endl;
	cout << "Введите размер таблицы: ";
	int size, cmd;
    bool addElem;
	cin >> size;
	HashTable hashTable = HashTable(size);
	cout << "Заполнить таблицу несколькими записями? 1/0 ";
	cin >> addElem;
	if (addElem) {
		hashTable.push(new RegSmallBusin(1001, "ООО Ромашка", "Киселёв М.А."));
		hashTable.push(new RegSmallBusin(1002, "ООО Зенит", "Гришин Г.С."));
		hashTable.push(new RegSmallBusin(1003, "ИП Загородом", "Загородный Д.А."));
		hashTable.push(new RegSmallBusin(1004, "ООО СССР", "Сталин И.В."));
		hashTable.push(new RegSmallBusin(1005, "ООО Балтика", "Пивной Г.Ч."));
        hashTable.push(new RegSmallBusin(1006, "ООО Тердельник", "Булка О.А."));
	}

	cout << "Список доступных комманд:" << endl;
	cout << "0) Завершение работы" << endl;
	cout << "1) Вставить элемент в таблицу" << endl;
	cout << "2) Удалить элемент" << endl;
	cout << "3) Найти элемент по ключу" << endl;
	cout << "4) Вывести таблицу" << endl;
	cout << "5) Текущий размер таблицы" << endl;

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
            int license;
			string name, founder;
			cout << "Введите номер лицензии, название предприятия и учредителя:\n";
			cin >> license >> name >> founder;
			RegSmallBusin* obj = new RegSmallBusin(license, name, founder);
			hashTable.push(obj);
			break;
		}
		case 2: {
			int license;
			cout << "Введите номер лицензии для удаления:\n";
			cin >> license;
			hashTable.deletEl(license);
			break;
		}
		case 3: {
			int license;
			cout << "Введите номер лицензии для поиска:\n";
			cin >> license;
			RegSmallBusin* tmp = hashTable.find(license);
			if (tmp == nullptr)
				cout << "Введённый элемент отсутствует в таблице" << endl;
			else
				cout << *tmp << endl;
			break;
		}
		case 4:
			hashTable.print();
			break;
		case 5:
			cout << "Размер таблицы: " << hashTable.get() << endl;
			break;
		default:
			break;
		}
		cout << endl << "Следующая команда: " << endl;
	}
}
