#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
};

void add(int x, Node*& node) {
	if (node == NULL) {
		node = new Node;
		node->data = x;
		node->left = NULL;
		node->right = NULL;
	}
	else {
		if (x < node->data) {
			add(x, node->left);
		}
		else {
			add(x, node->right);
		}
	}
}

void printTree1(Node*& node) {  //прямой обход
	if (node != NULL) {
		cout << node->data << " ";
		printTree1(node->left);
		printTree1(node->right);
	}
}

void printTree2(Node*& node) {   //симметричный обход
	if (node != NULL) {
		printTree2(node->left);
		cout << node->data << " ";
		printTree2(node->right);
	}
}

void printTree3(Node*& node) {   //обратный обход
	if (node != NULL) {
		printTree3(node->left);
		printTree3(node->right);
		cout << node->data << " ";
	}
}

Node* copyTree(Node*& original) {
	if (original == NULL)
		return NULL;
	else {
		Node* node2 = new Node;
		node2->data = original->data;
		node2->left = copyTree(original->left);
		node2->right = copyTree(original->right);
		return node2;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	Node* root = NULL;
	int elements = rand() % 11 + 10;
	for (int i = 1; i <= elements; i++)
		add(rand() % 100, root);
	cout << "Оригинальное дерево" << endl << "Прямой обход: ";
	printTree1(root);
	cout << endl << "Симметричный обход: ";
	printTree2(root);
	cout << endl << "Обратный обход: ";
	printTree3(root);
	cout << endl << endl;
	Node* root2 = copyTree(root);
	cout << "Копия" << endl << "Прямой обход: ";
	printTree1(root2);
	cout << endl << "Симметричный обход: ";
	printTree2(root2);
	cout << endl << "Обратный обход: ";
	printTree3(root2);
	cout << endl;
	system("pause");
	return 0;
}