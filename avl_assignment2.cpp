#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

struct AVL_TreeNode {
	int value; /* value to govern the AVL tree */
	int ** matrix; /* matrix variable */
	AVL_TreeNode * left;
	AVL_TreeNode * right;
}*tree;

class AVL_Tree {
public:
	AVL_TreeNode * tree;
	AVL_Tree() {
		tree = NULL;
	}
	AVL_TreeNode * makeNode(int number, int M) {
		AVL_TreeNode * newNode = new AVL_TreeNode;
		newNode->value = number;
		newNode->left = NULL;
		newNode->right = NULL;

		newNode->matrix = new int *[M];
		for (int i = 0; i < M; i++) {
			newNode->matrix[i] = new int[M];
		}
		for (int k = 0; k < M; k++) {
			for (int l = 0; l < M; l++) {
				newNode->matrix[k][l] = 1;
			}
		}

		return newNode;
	}

	int height_of_Tree(AVL_TreeNode * treeList) {
		/* function to return the height of a given tree*/
		int height = 0;
		if (treeList != NULL) {
			int left_height = height_of_Tree(treeList->left);
			int right_height = height_of_Tree(treeList->right);
			int max_height = (left_height, right_height);
			height = max_height;
		}
		return height;
	}

	int balance_factor(AVL_TreeNode * root) {
		/* calculate the balance factor of the AVL tree */
		int left_height = height_of_Tree(root->left);
		int right_height = height_of_Tree(root->right);
		int balance_Factor = left_height - right_height;
		return balance_Factor;
	}

	AVL_TreeNode * leftRotation(AVL_TreeNode * root) {
		/* left rotation */
		AVL_TreeNode * temp = root->left;
		temp->left = temp->right;
		temp->right = root;
		return temp;
	}

	AVL_TreeNode * rightRotation(AVL_TreeNode * root) {
		/* right rotation */
		AVL_TreeNode * temp = root->right;
		temp->right = temp->left;
		temp->left = root;
		return temp;
	}

	AVL_TreeNode * leftRightRotation(AVL_TreeNode * root) {
		AVL_TreeNode * temp = root->left;
		root->left = rightRotation(temp);
		return leftRotation(root);
	}

	AVL_TreeNode * rightLeftRotation(AVL_TreeNode * root) {
		AVL_TreeNode * temp = root->right;
		root->right = leftRotation(temp);
		return rightRotation(root);
	}

	AVL_TreeNode * balance(AVL_TreeNode * treeList) {
		int balanceFactor = balance_factor(treeList);
		if (balanceFactor > 1) {
			if (balance_factor(treeList->left) > 0) {
				treeList = leftRotation(treeList);
			}
			else {
				treeList = leftRightRotation(treeList);
			}
		}
		else if (balanceFactor < -1) {
			if (balance_factor(treeList->right) > 0) {
				treeList = rightLeftRotation(treeList);
			}
			else {
				treeList = rightRotation(treeList);
			}
		}
		return treeList;
	}

	int num_of_Nodes(AVL_TreeNode * tree) {
		int count = 1;
		if (tree == NULL) {
			return 0;
		}
		else {
			count += num_of_Nodes(tree->left);
			count += num_of_Nodes(tree->right);
			//cout << "Number of nodes: " << count << endl;
			return count;
		}
	}

	int min_number(AVL_TreeNode * tree) {
		AVL_TreeNode * current = tree;
		if (tree != NULL) {
			while (current->left != NULL) {
				current = current->left;
			}
			return (current->value);
		}


	}

	AVL_TreeNode * insert(AVL_TreeNode * tree, int number, int M) {
		int numOfNodes = num_of_Nodes(tree);
		clock_t deleteTimer;
		int min_value = min_number(tree);
		if (numOfNodes > 50) {
			deleteTimer = clock();
			tree = deleteTree(tree, min_value);
			cout << "Time elapsed for search: " << ((((double)clock() - deleteTimer) * 1000) / CLOCKS_PER_SEC) << " milliseconds for deletion" << endl;

		}
		clock_t insertionTimer;
		insertionTimer = clock();
		AVL_TreeNode * newNode = makeNode(number, M);
		if (tree == NULL) {
			return newNode;
		}
		if (number < tree->value) {
			tree->left = insert(tree->left, number, M);
			tree = balance(tree);
		}
		else if (number >= tree->value) {
			tree->right = insert(tree->right, number, M);
			tree = balance(tree);
		}
		cout << "Time elapsed for search: " << ((((double)clock() - deleteTimer) * 1000) / CLOCKS_PER_SEC) << " milliseconds for insertion " << endl;

		return tree;
	}

	AVL_TreeNode * deleteTree(AVL_TreeNode * tree, int min_number) {

		if (tree == NULL) {
			return tree;
		}
		if (min_number < tree->value) {
			tree->left = deleteTree(tree->left, min_number);
			tree = balance(tree);
		}
		else if (min_number >= tree->value) {
			tree->right = deleteTree(tree->right, min_number);
			tree = balance(tree);
		}
		else {
			AVL_TreeNode * temp = new AVL_TreeNode;
			temp = tree;
			delete temp;
		}
		/*
		AVL_TreeNode * current = tree;
		AVL_TreeNode * previous = tree;
		while (current->left != NULL) {
		previous = current;
		current = current->left;
		}
		delete current;
		previous->left = NULL;
		/*
		AVL_TreeNode * temp = new AVL_TreeNode;
		temp = tree;
		delete temp;

		tree = balance(tree);
		*/
		return tree;
	}
};

int M_value_return(int number) {
	int power_two = 1;
	int total;
	if (number == (0 % 3)) {
		for (int i = 0; i < 20; i++) {
			power_two *= 2;
		}
		return power_two;
	}
	else if (number == (1 % 3)) {
		for (int i = 0; i < 19; i++) {
			power_two *= 2;
		}
		int temp = 1;
		for (int i = 0; i < 18; i++) {
			temp *= 2;
		}
		total = power_two + temp;
		return total;
	}
	else if (number == (2 % 3)) {
		for (int i = 0; i < 18; i++) {
			power_two *= 2;
		}
		int temp = 1;
		for (int i = 0; i < 17; i++) {
			temp *= 2;
		}
		total = power_two + temp;
		return total;
	}

}

int main() {
	int rand_num;
	int M;
	clock_t timeBeg;
	AVL_Tree newTree;
	AVL_TreeNode * newNode = new AVL_TreeNode;
	timeBeg = clock();

	int recursive_value[] = { 100,200,500,1000,1500,2000,2500,5000,8000,10000 };
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < recursive_value[i]; j++) {
			rand_num = rand() % 299;
			M = M_value_return(rand_num);
			tree = newTree.insert(tree, rand_num, M);
			cout<<"-------------"<<endl;
		}
		cout << "Time elapsed forb search: " << ((((double)clock() - timeBeg) * 1000) / CLOCKS_PER_SEC) << " milliseconds for " << recursive_value[i] << endl;
        cout<<"------------------------";
	}
	/*
	for (int i = 0; i < 60; i++){
	rand_num = rand() % 299;
	M = M_value_return(rand_num);
	tree = newTree.insert(tree, rand_num, M);
	}
	cout << "Time elapsed for search: " << ((((double)clock() - timeBeg) * 1000) / CLOCKS_PER_SEC) << " milliseconds" <<  endl;
	*/
	system("pause");
	return 0;
}
