#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10000

typedef struct treeNode {
	int data;
	struct treeNode* left;
	struct treeNode* right;
	struct treeNode* parent;
} treeNode;

int CalHeight(treeNode* node) { // ���� ���ϴ� �Լ� (BF�� ���ϱ� ����) 
	if (node == NULL)
		return 0;
	int height = 0; // ����� ���� �ʱ�ȭ
	height = CalHeight(node->left) > CalHeight(node->right) ? CalHeight(node->left) + 1 : CalHeight(node->right) + 1;
	return height; 
}

int CalBF(treeNode* node) { // BF(Balance Factor) ��� �Լ�
	return CalHeight(node->left) - CalHeight(node->right);
}

treeNode* LL(treeNode* node) { // LL ȸ�� ����
	treeNode* child = node->left; 
	node->left = child->right;
	if (child->right != NULL)
		child->right->parent = node;
	child->right = node;
	child->parent = node->parent;
	node->parent = child;
	return child;
}

treeNode* RR(treeNode* node) { // RR ȸ�� ����
	treeNode* child = node->right;
	node->right = child->left;
	if (child->left != NULL)
		child->left->parent = node;
	child->left = node;
	child->parent = node->parent;
	node->parent = child;
	return child;
}

treeNode* LR(treeNode* node) { // LR ȸ�� ����
	node->left = RR(node->left);  // RR ȸ�� �� LL ȸ��
	return LL(node);
}

treeNode* RL(treeNode* node) { // RL ȸ�� ����
	node->right = LL(node->right); // LL ȸ�� �� RR ȸ��
	return RR(node);
}

treeNode* balancing(treeNode* node) {
	int BF = CalBF(node); 
	// BF�� -1,0,1�� �ƴϸ� �ұ���
	if (BF >= 2) { // ������ ���� ����� BF�� +�̸� ���� ���� Ʈ���� ������ �ִ�.
		BF = CalBF(node->left);  
		if (BF >= 1) {
			node = LL(node); // LL ȸ�� ����
		}
		else {
			node = LR(node); // LR ȸ�� ����
		}
	}
	else if (BF <= -2) { // ������ ���� ����� BF�� -�̸� ������ ���� Ʈ���� ������ �ִ�.
		BF = CalBF(node->right);
		if (BF <= -1) {
			node = RR(node); // RR ȸ�� ����
		}
		else {
			node = RL(node); // RL ȸ�� ����
		}
	}
	return node;
}

treeNode* insert(treeNode* node, int data) {
	if (node == NULL) { // node�� ����� ��
		node = (treeNode*)malloc(sizeof(treeNode));
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		node->data = data; // ������ ����Ÿ ��忡 ����
		return node;
	}
	else if (data < node->data) { // ���� ���Ե� ����Ÿ�� ���� ��忡 �ִ� ����Ÿ���� ���� ��
		node->left = insert(node->left, data); // ���� ��忡 ����
		node->left->parent = node;
		node = balancing(node); // �ұ����� ��带 �����ִ� ���� 
	}
	else if (data > node->data) { // ���� ���Ե� ����Ÿ�� ���� ��忡 �ִ� ����Ÿ���� Ŭ ��
		node->right = insert(node->right, data); // ������ ��忡 ����
		node->right->parent = node;
		node = balancing(node); // �ұ����� ��带 �����ִ� ���� 
	}
	else {
		printf("\n����Ÿ�� �ߺ��˴ϴ�.\n");
		exit(1);
	}
	return node;
}

void Inorder(treeNode* node) {
	if (node == NULL)
		return;
	Inorder(node->left);
	printf("%d ", node->data);
	Inorder(node->right);
}

treeNode* search(treeNode* root, int data) { // AVL Ʈ������ ����Ÿ�� Ž���ϴ� �Լ�
	treeNode* node;
	int count = 0;
	node = root;
	while (node != NULL) {
		count++;
		if (data < node->data)
			node = node->left;
		else if (data == node->data) {
			printf("%d��°�� Ž�� ����", count);
			return node;
		}
		else
			node = node->right;
	}
	count++;
	printf("%d��°�� Ž�� ����", count);
	return node;
}

int main() {
	char* string_data[MAX] = { 0, };
	char input_data[MAX] = { 0, };
	treeNode* root = NULL;
	int i = 0;
	int k = 0;
	srand(time(NULL));

	FILE* fp;
	fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		printf("������ ������ ����");
		return 0;
	}
	fread(input_data, 1,MAX, fp);

	char* ptr = strtok(input_data, ","); // ","�� �������� �и��ؼ� ����Ÿ ����
	while (ptr != NULL) {
		string_data[i] = ptr;
		i++;
		ptr = strtok(NULL, ",");
	}

	for (int j = 0; j < MAX; j++) {

		int int_data = 0;
		if (string_data[j] == 0)
		{
			break;
		}
		int_data = atoi(string_data[j]); // ���ڿ��� ����Ÿ�� ���������� ��ȯ
		printf("%d ", int_data);
		root = insert(root,int_data); 
		int_data = 0;
		k++;
	}

	printf("\nAVL\n");
	Inorder(root);

	int random = 0; // ������ ���� ����
	random = rand() % 99; // ���� ����

	printf("\n\n AVL Ʈ������ %d Ž�� : ", random);
	search(root, random);
}