#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
using namespace std;

struct node // Cтруктура для представления узлов дерева
{
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};

string repeatString(string s, int count) { // Повторение строки
    string res = "";
    for (int i = 0; i < count; i++) res += s;
    return res;
}

void printTreeIn(node* root, int lvl) { // Симметричный обход
    if (root == nullptr) {
        return;
    }
    printTreeIn(root->left, lvl + 1);
	cout << repeatString("    ", lvl) << root->key << endl;
    printTreeIn(root->right, lvl + 1);
}

void printTreePost(node* root, int lvl) { // Обратный обход
    if (root == nullptr) {
        return;
    }
    printTreePost(root->left, lvl + 1);
    printTreePost(root->right, lvl + 1);
    cout << repeatString("    ", lvl) << root->key << endl;
}

int getSumOfLeaves(node* root) { // Сумма значений листьев
    if (root == nullptr) {
        return 0;
    }
    if (root->left == nullptr && root->right == nullptr)
        return root->key;
    return getSumOfLeaves(root->left) + getSumOfLeaves(root->right);
}

int depth(node *p) // Высота дерева
{  
    if (p == NULL)  
        return 0;  
    return p->height;  
}

unsigned char height(node* p)
{
	return p?p->height:0;
}

int bfactor(node* p)
{
	return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
{
	fixheight(p);
	if( bfactor(p)==2 )
	{
		if( bfactor(p->right) < 0 )
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( bfactor(p)==-2 )
	{
		if( bfactor(p->left) > 0  )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if( !p ) return new node(k);
	if( k<p->key )
		p->left = insert(p->left,k);
	else
		p->right = insert(p->right,k);
	return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left?findmin(p->left):p;
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int k) // удаление ключа k из дерева p
{
	if( !p ) return 0;
	if( k < p->key )
		p->left = remove(p->left,k);
	else if( k > p->key )
		p->right = remove(p->right,k);	
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if( !r ) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

void write_menu_start() {
	string start_menu;
    start_menu += "1 - Создать список вручную\n";
    start_menu += "2 - Готовый спискок\n";
    cout << start_menu;
}

void write_menu() {
	string menu = "Список команд:\n";
	menu += "0 - Прекратить работу программы\n";
	menu += "3 - Вставка элемента и балансировка\n";
	menu += "4 - Обратный обход дерева\n";
	menu += "5 - Симметричный обход дерева\n";
	menu += "6 - Найти сумму значений листьев\n";
	menu += "7 - Найти высоту дерева\n";
	cout << menu;
}

int get_command() {
	int command;
	cout << "Новая команда: " << endl;
	cin >> command;
	return command;
}

int main() {
    int n = 10, num, command_start, command;
	node* p;
	p = nullptr;
	
	cout << "Практическая работа №4. Бинарное дерево поиска. AVL дерево. Киселёв Максим. ИКБО-08-21. Вариант №14.";
    cout << "\nКоманды:\n";

    write_menu_start();

	cout << "\nВыбранная команда:\n";
	cin >> command_start;

    if (command_start == 1) {
        cout << "Введите 10 элементов списка:\n";
        for (int i = 0; i < 10; i++) {
		    cin >> num;
            p = insert(p, num);
        }
    }
    else if (command_start != 1) {
        for (int i = 0; i < 10; i++) {
		    num = rand() % 70;
            p = insert(p, num);
        }
        cout << "Ваш список\n";
    }

	write_menu();

	cout << "\nВыбранная команда:\n";
	cin >> command;

	while (command != 0) {
		switch (command) {
		case 3: {
			cout << "Введите элемент, который хотите вставить в дерево: ";
			cin >> num;
			p = insert(p, num);
			break;
		}
		case 4: {
			printTreePost(p, 0);
			break;
		}
		case 5: {
			printTreeIn(p, 0);
			break;
		}
		case 6: {
			cout << "Сумма листьев: " << getSumOfLeaves(p) << endl;
			break;
		}
		case 7: {
			cout << "Высота дерева: " << depth(p) << endl;
			break;
		}
		default:
			break;
		}
		command = get_command();
	}
    return 0;
}