#include <iostream>
#include "MyAVLTree.hpp"
using namespace std;

int main() {
	MyAVLTree myAvlTree;

	int temp;
	while (true) {
		cin >> temp;
		if (temp == 0)
			break;

		myAvlTree.insert(temp);
		myAvlTree.preorder();
	}

	return 0;
}