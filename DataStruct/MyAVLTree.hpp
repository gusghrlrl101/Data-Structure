#ifndef MYAVLTREE_HPP
#define MYAVLTREE_HPP

#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class MyNode {
public:
	T value;
	int height = 0;
	short balance = 0;
	MyNode* left = NULL;
	MyNode* right = NULL;
	MyNode* parent = NULL;

	MyNode() {};
	MyNode(T value) {
		this->value = value;
	}
};

template <class T>
class MyAVLTree {
private:
	MyNode<T>* root = new MyNode<T>();
	int size = 0;

	void preorder_in(MyNode<T>*);
	void insert_to_leap(T, MyNode<T>*);
	int refresh_height(MyNode<T>*);
	void refresh_balance(MyNode<T>*);
	void rotation(MyNode<T>*);
	MyNode<T>* ll_rotation(MyNode<T>*);
	MyNode<T>* rr_rotation(MyNode<T>*);

public:
	void insert(T);
	bool remove(T);
	bool isEmpty();
	int getSize();
	void preorder();
};

// private function

template <class T>
void MyAVLTree<T>::preorder_in(MyNode<T>* item) {
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

template <class T>
void MyAVLTree<T>::insert_to_leap(T item, MyNode<T>* n) {
	MyNode<T>* temp = root;

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

template <class T>
int MyAVLTree<T>::refresh_height(MyNode<T>* n) {
	MyNode<T>* temp = n;

	int left_height = 0;
	if (temp->left != NULL)
		left_height = refresh_height(temp->left);

	int right_height = 0;
	if (temp->right != NULL)
		right_height = refresh_height(temp->right);

	return (temp->height = max(left_height, right_height) + 1);
}

template <class T>
void MyAVLTree<T>::refresh_balance(MyNode<T>* n) {
	MyNode<T>* temp = n;

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

template <class T>
void MyAVLTree<T>::rotation(MyNode<T> * n) {
	MyNode<T>* temp = n;

	while (temp->parent != NULL) {
		temp = temp->parent;

		// L
		if (1 < temp->balance) {
			// LL
			if (0 < temp->left->balance) {
				MyNode<T>* temp_parent = temp->parent;
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
				MyNode<T>* temp_parent = temp->parent;
				bool isLeft = true;
				if (temp_parent != NULL && temp_parent->right == temp)
					isLeft = false;

				temp = rr_rotation(temp->left->right);

				if (temp_parent != NULL) {
					if (isLeft)
						temp_parent->left = temp;
					else
						temp_parent->right = temp;
				}

				ll_rotation(temp);
				break;
			}
		}
		// R
		else if (temp->balance < -1) {
			// RR
			if (temp->right->balance < 0) {
				MyNode<T>* temp_parent = temp->parent;
				bool isLeft = true;
				if (temp_parent != NULL && temp_parent->right == temp)
					isLeft = false;

				temp = rr_rotation(temp->right);

				if (temp_parent != NULL) 
					(isLeft ? temp_parent->left : temp_parent->right) = temp;
				break;
			}
			// RL
			else if (0 < temp->right->balance) {
				MyNode<T>* temp_parent = temp->parent;
				bool isLeft = true;
				if (temp_parent != NULL && temp_parent->right == temp)
					isLeft = false;

				temp = ll_rotation(temp->right->left);

				if (temp_parent != NULL)
					(isLeft ? temp_parent->left : temp_parent->right) = temp;

				rr_rotation(temp);
				break;
			}
		}
	}

	refresh_height(root);
	refresh_balance(root);
}

template <class T>
MyNode<T>* MyAVLTree<T>::ll_rotation(MyNode<T>* temp) {
	temp->parent->left = temp->right;
	if (temp->right != NULL)
		temp->right->parent = temp->parent;

	temp->right = temp->parent;
	MyNode<T>* temp_parent = temp->parent->parent;
	temp->parent->parent = temp;
	temp->parent = temp_parent;

	if (temp->parent == NULL)
		root = temp;

	return temp;
}

template <class T>
MyNode<T>* MyAVLTree<T>::rr_rotation(MyNode<T>* temp) {
	temp->parent->right = temp->left;
	if (temp->left != NULL)
		temp->left->parent = temp->parent;

	temp->left = temp->parent;
	MyNode<T>* temp_parent = temp->parent->parent;
	temp->parent->parent = temp;
	temp->parent = temp_parent;

	if (temp->parent == NULL)
		root = temp;

	return temp;
}

// public function

template <class T>
void MyAVLTree<T>::insert(T item) {
	MyNode<T>* n = new MyNode<T>(item);
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

template <class T>
bool MyAVLTree<T>::remove(T item) {
	bool isRemove = false;

	MyNode<T>* temp = root;

	while (true) {
		if (item < temp->value) {
			if (temp->left != NULL)
				temp = temp->left;
			else
				break;
		}
		else if (temp->value < item) {
			if (temp->right != NULL)
				temp = temp->right;
			else
				break;
		}
		else {
			isRemove = true;
			break;
		}
	}

	if (isRemove) {
		MyNode<T>* temp_parent = temp->parent;
		MyNode<T>* ttemp = temp;

		if (ttemp->left != NULL) {
			ttemp = ttemp->left;

			if (ttemp->right != NULL) {
				while (ttemp->right != NULL)
					ttemp = ttemp->right;
				
				if (temp_parent != NULL) {
					bool isLeft = true;
					if (temp_parent->right == temp)
						isLeft = false;

					(isLeft ? temp_parent->left : temp_parent->right) = ttemp;
					ttemp->parent = temp_parent;

					ttemp->left = temp->left;
					temp->left->parent = ttemp;

					ttemp->right = temp->right;
					if (temp->right != NULL)
						temp->right->parent = ttemp;

					delete temp;
				}
				else {
					root = ttemp;
					ttemp->parent = NULL;

					ttemp->left = temp->left;
					temp->left->parent = ttemp;

					ttemp->right = temp->right;
					if (temp->right != NULL)
						temp->right->parent = ttemp;

					delete temp;
				}
			}
			else {
				if (temp_parent != NULL) {
					bool isLeft = true;
					if (temp_parent->right == temp)
						isLeft = false;

					(isLeft ? temp_parent->left : temp_parent->right) = ttemp;
					ttemp->parent = temp_parent;

					ttemp->right = temp->right;
					if (temp->right != NULL)
						temp->right->parent = ttemp;

					delete temp;
				}
				else {
					root = ttemp;
					ttemp->parent = NULL;

					ttemp->right = temp->right;
					if (temp->right != NULL)
						temp->right->parent = ttemp;

					delete temp;
				}
			}
		}
		else {
			if (temp->right != NULL) {
				if (temp_parent != NULL) {
					bool isLeft = true;
					if (temp_parent->right == temp)
						isLeft = false;

					(isLeft ? temp_parent->left : temp_parent->right) = temp->right;
					temp->right->parent = temp_parent;

					delete temp;
				}
				else {
					root = temp->right;
					temp->right->parent = NULL;
					delete temp;
				}
			}
			else {
				if (temp_parent != NULL) {
					bool isLeft = true;
					if (temp_parent->right == temp)
						isLeft = false;

					(isLeft ? temp_parent->left : temp_parent->right) = NULL;

					delete temp;
				}
				else {
					root = NULL;
					delete temp;
				}
			}
		}


		size--;
		refresh_height(root);
		refresh_balance(root);
	}

	return isRemove;
}

template <class T>
bool MyAVLTree<T>::isEmpty() {
	return (size == 0);
}

template <class T>
int MyAVLTree<T>::getSize() {
	return size;
}

template <class T>
void MyAVLTree<T>::preorder() {
	preorder_in(root);
	cout << '\n';
}


#endif