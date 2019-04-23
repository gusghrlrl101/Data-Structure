#include <iostream>
#include <string>
#include "MyAVLTree.hpp"
using namespace std;

int main() {
	MyAVLTree<int> myAvlTree;

	int man;
	int temp;
	while (true) {
		cout << "input (0: finish, 1: insert, 2: remove) : ";
		cin >> man;


		if (man == 0)
			break;
		else if (man==1) {
			cout << "insert input: ";
			cin >> temp;
			myAvlTree.insert(temp);
		}
		else if (man == 2) {
			cout << "remove input: ";
			cin >> temp;
			myAvlTree.remove(temp);
		}

		myAvlTree.preorder();
	}

	return 0;
}