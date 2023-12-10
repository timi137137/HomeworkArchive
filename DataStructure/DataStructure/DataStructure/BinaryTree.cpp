#include <iostream>

using namespace std;

#pragma region -- Define --

#define OK 1;
#define ERROR -1;
#define OVERFLOW -2;

typedef int status;

/// <summary>
///  Binary Tree Node Structure
/// </summary>
typedef struct TreeNode {
	char value; // Node Value
	struct TreeNode *left; // Left Tree
	struct TreeNode *right; // Right Tree
} TreeNode, *Tree;


#pragma endregion

#pragma region -- Functions --

status CreateTree(Tree& tree) {
	char input;

	cout << "������Ҫ�����Ķ�������չ�����������(��*�Ŵ����): " << endl;
	cin >> input;

	if (input == '*') {
		tree = NULL;
	}
	else {
		tree = new TreeNode;
		if (tree == NULL) return OVERFLOW;
		tree->value = input;
		CreateTree(tree->left);
		CreateTree(tree->right);
	}

	return OK;
}

void Preorder(Tree tree) {
	if (tree == NULL) return;

	cout << tree->value << " -> ";
	Preorder(tree->left);
	Preorder(tree->right);
}

void MiddleOrder(Tree tree) {
	if (tree == NULL) return;

	MiddleOrder(tree->left);
	cout << tree->value << " -> ";
	MiddleOrder(tree->right);
}

void Postorder(Tree tree) {
	if (tree == NULL) return;

	Postorder(tree->left);
	Postorder(tree->right);
	cout << tree->value << " -> ";
}

int GetNodesCount(Tree tree) {
	if (tree == NULL) return 0;

	int left = GetNodesCount(tree->left);
	int right = GetNodesCount(tree->right);
	int count = left + right + 1;
	
	return count;
}

int GetTreeDepth(Tree tree) {
	if (tree == NULL) return 0;

	return max(GetTreeDepth(tree->left), GetTreeDepth(tree->right)) + 1;
}

int GetLeafNode(Tree tree) {
	if (tree == NULL) return 0;
	if (tree->left == NULL && tree->right == NULL) return 1;

	return GetLeafNode(tree->left) + GetLeafNode(tree->right);
}

#pragma endregion

#pragma region -- Main --

int main2() {
	Tree BinaryTree;

	CreateTree(BinaryTree);
	system("cls");

	cout << "�ö��������������Ϊ: " << endl;
	Preorder(BinaryTree);
	cout << "NULL \n" << endl;

	cout << "�ö��������������Ϊ: " << endl;
	MiddleOrder(BinaryTree);
	cout << "NULL \n" << endl;

	cout << "�ö������ĺ������Ϊ: " << endl;
	Postorder(BinaryTree);
	cout << "NULL \n" << endl;

	cout << "�������Ϊ: " << GetTreeDepth(BinaryTree) << endl;
	cout << "��������Ϊ: " << GetNodesCount(BinaryTree) << endl;
	cout << "����Ҷ�ӽ����Ϊ: " << GetLeafNode(BinaryTree) << endl;

	system("pause");

	return OK;
}

#pragma endregion

