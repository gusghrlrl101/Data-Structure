#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <iostream>
#include <algorithm>
using namespace std;

typedef struct node {
	int value = 0;
	int height = 0;
	short balance = 0;
	node* left = NULL;
	node* right = NULL;
	node* parent = NULL;

	node(int value = 0) {
		this->value = value;
	}
}node;

class AVL_tree {
private:
	node* root = new node();
	int size = 0;

	void preorder_in(node*);
	void insert_to_leap(int, node*);
	int refresh_height(node*);
	void refresh_balance(node*);
	void rotation(node*);
	node* ll_rotation(node*);
	node* rr_rotation(node*);

public:
	void insert(int);
	bool isEmpty();
	int getSize();
	void preorder();
};

// private function

void AVL_tree::preorder_in(node* item) {
	if (item->left != NULL)
		preorder_in(item->left);

	if (item == root)
		cout << '[';
	cout << item->value << '(' << item->height << ')';
	if (item == root)
		cout << ']';
	cout << ' ';

	if (item->right != NULL)
		preorder_in(item->right);
}

void AVL_tree::insert_to_leap(int item, node* n) {
	node* temp = root;

	while (true) {
		if (item < temp->value) {
			if (temp->left != NULL)
				temp = temp->left;
			else {
				temp->left = n;
				n->parent = temp;
				n->height = 1;
				temp = temp->left;
				break;
			}
		}
		else {
			if (temp->right != NULL)
				temp = temp->right;
			else {
				temp->right = n;
				n->parent = temp;
				n->height = 1;
				temp = temp->right;
				break;
			}
		}
	}

	refresh_height(root);
	refresh_balance(root);
}

int AVL_tree::refresh_height(node* n) {
	node* temp = n;

	int left_height = 0;
	if (temp->left != NULL)
		left_height = refresh_height(temp->left);

	int right_height = 0;
	if (temp->right != NULL)
		right_height = refresh_height(temp->right);

	return (temp->height = max(left_height, right_height) + 1);
}

void AVL_tree::refresh_balance(node* n) {
	node* temp = n;

	int left_height = 0;
	if (temp->left != NULL) {
		left_height = temp->left->height;
		refresh_balance(temp->left);
	}

	int right_height = 0;
	if (temp->right != NULL) {
		right_height = temp->right->height;
		refresh_balance(temp->right);
	}

	temp->balance = left_height - right_height;
}

void AVL_tree::rotation(node * n) {
	node* temp = n;

	while (temp->parent != NULL) {
		temp = temp->parent;

		// L
		if (1 < temp->balance) {
			// LL
			if (0 < temp->left->balance) {
				node* temp_parent = temp->parent;
				bool isLeft = true;
				if (temp_parent != NULL && temp_parent->right == temp)
					isLeft = false;

				temp = ll_rotation(temp->left);

				if (temp_parent != NULL) {
					if (isLeft)
						temp_parent->left = temp;
					else
						temp_parent->right = temp;
				}
				break;
			}
			// LR
			else if (temp->left->balance < 0) {
				node* temp_parent = temp;
				temp = rr_rotation(temp->left->right);

				temp_parent->left = temp;
				ll_rotation(temp);
				break;
			}
		}
		// R
		else if (temp->balance < -1) {
			// RR
			if (temp->right->balance < 0) {
				node* temp_parent = temp->parent;
				bool isLeft = true;
				if (temp_parent != NULL && temp_parent->right == temp)
					isLeft = false;

				temp = rr_rotation(temp->right);

				if (temp_parent != NULL) {
					if (isLeft)
						temp_parent->left = temp;
					else
						temp_parent->right = temp;
				}
				break;
			}
			// RL
			else if (0 < temp->right->balance) {
				node* temp_parent = temp;
				temp = ll_rotation(temp->right->left);

				temp_parent->right = temp;
				rr_rotation(temp);
				break;
			}
		}
	}

	refresh_height(root);
	refresh_balance(root);
}

node* AVL_tree::ll_rotation(node* temp) {
	temp->parent->left = temp->right;
	if (temp->right != NULL)
		temp->right->parent = temp->parent;

	temp->right = temp->parent;
	node* temp_parent = temp->parent->parent;
	temp->parent->parent = temp;
	temp->parent = temp_parent;

	if (temp->parent == NULL)
		root = temp;

	return temp;
}

node* AVL_tree::rr_rotation(node* temp) {
	temp->parent->right = temp->left;
	if (temp->left != NULL)
		temp->left->parent = temp->parent;

	temp->left = temp->parent;
	node* temp_parent = temp->parent->parent;
	temp->parent->parent = temp;
	temp->parent = temp_parent;

	if (temp->parent == NULL)
		root = temp;

	return temp;
}

// public function

void AVL_tree::insert(int item) {
	node* n = new node(item);
	n->value = item;


	if (isEmpty()) {
		root = n;
		root->value = item;
		root->height = 1;
	}
	else {
		insert_to_leap(item, n);
		rotation(n);
	}

	size++;
}

bool AVL_tree::isEmpty() {
	return (size == 0);
}

int AVL_tree::getSize() {
	return size;
}

void AVL_tree::preorder() {
	preorder_in(root);
	cout << '\n';
}


#endif