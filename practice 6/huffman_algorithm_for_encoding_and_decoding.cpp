#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;
 
#define EMPTY_STRING ""
 
// Узел дерева
struct Node {
    char ch;
    int freq;
    Node *left, *right;
};

Node* getNode(char ch, int freq, Node* left, Node* right) { // Функция для выделения нового узла дерева
    Node* node = new Node();
 
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
 
    return node;    
}

struct comp {
    bool operator()(const Node* l, const Node* r) const // Объект сравнения, который будет использоваться для упорядочивания кучи
    {
        return l->freq > r->freq; // элемент с наивысшим приоритетом имеет наименьшую частоту
    }
};

bool isLeaf(Node* root) { // Вспомогательная функция для проверки, содержит ли дерево Хаффмана только один узел
    return root->left == nullptr && root->right == nullptr;
}

void encode(Node* root, string str, unordered_map<char, string> &huffmanCode) { // Проходим по дереву Хаффмана и сохраняем коды Хаффмана на карте.
    if (root == nullptr) {
        return;
    }

    if (isLeaf(root)) { // найден листовой узел
        huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
    }
 
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int &index, string str) { // Проходим по дереву Хаффмана и декодируем закодированную строку
    if (root == nullptr) {
        return;
    }

    if (isLeaf(root)) // найден листовой узел
    {
        cout << root->ch;
        return;
    }
 
    index++;
 
    if (str[index] == '0') {
        decode(root->left, index, str);
    }
    else {
        decode(root->right, index, str);
    }
}

void buildHuffmanTree(string text) { // Строит дерево Хаффмана и декодирует заданный входной текст

    if (text == EMPTY_STRING) { // базовый случай: пустая строка
        return;
    }

    unordered_map<char, int> freq; // подсчитываем частоту появления каждого символа и сохраняем его на карте
    for (char ch: text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, comp> pq; // Создаем приоритетную очередь для хранения активных узлов дерева Хаффмана

    for (auto pair: freq) { // Создаем конечный узел для каждого символа и добавляем его в приоритетную очередь
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1) // делаем до тех пор, пока в queue не окажется более одного узла
    {
        Node* left = pq.top(); pq.pop(); // Удаляем два узла с наивысшим приоритетом (самая низкая частота) из queue
        Node* right = pq.top(); pq.pop();

        int sum = left->freq + right->freq; // создаем новый внутренний узел с этими двумя узлами в качестве дочерних и с частотой, равной сумме частот двух узлов
        pq.push(getNode('\0', sum, left, right)); // Добавляем новый узел в приоритетную очередь.
    }

    Node* root = pq.top(); // `root` хранит указатель на корень дерева Хаффмана

    unordered_map<char, string> huffmanCode; // Проходим по дереву Хаффмана и сохраняем коды Хаффмана на карте
    encode(root, EMPTY_STRING, huffmanCode);
 
    cout << "Коды Хаффмана:" << endl;
    for (auto pair: huffmanCode) {
        cout << pair.first << " " << pair.second << endl;
    }
 
    cout << "\nИсходная строка:\n" << text << endl;

    string str;
    for (char ch: text) { // Печатаем закодированную строку
        str += huffmanCode[ch];
    }
 
    cout << "\nЗакодированная строка:\n" << str << endl;
    cout << "\nДекодированная строка:\n";
 
    if (isLeaf(root))
    {
        while (root->freq--) { // Особый случай: для ввода типа a, aa, aaa и т. д.
            cout << root->ch;
        }
    }
    else {
        int index = -1;
        while (index < (int)str.size() - 1) { // Снова проходим по дереву Хаффмана и на этот раз декодируем закодированную строку
            decode(root, index, str);
        }
    }
}

int main() { // Основная функция программы
    cout << "\nПрактическая работа №6. Кодирование и сжатие данных методами без потерь. Задание №2 (метод Хаффмана.). Киселёв Максим. ИКБО-08-21. Вариант №14.\n" << endl;
    string text = "Kiselev Maxim Alekseevich";
    buildHuffmanTree(text);
    return 0;
}