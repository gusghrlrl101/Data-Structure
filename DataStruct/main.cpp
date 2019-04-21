#include <iostream>
#include "AVL_tree.hpp"
using namespace std;

int main() {
	AVL_tree avlTree;

	int temp;
	while (true) {
		cin >> temp;
		if (temp == 0)
			break;

		avlTree.insert(temp);
		avlTree.preorder();
	}

	return 0;
}