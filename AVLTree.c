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

int CalHeight(treeNode* node) { // 높이 구하는 함수 (BF를 구하기 위해) 
	if (node == NULL)
		return 0;
	int height = 0; // 계산할 높이 초기화
	height = CalHeight(node->left) > CalHeight(node->right) ? CalHeight(node->left) + 1 : CalHeight(node->right) + 1;
	return height; 
}

int CalBF(treeNode* node) { // BF(Balance Factor) 계산 함수
	return CalHeight(node->left) - CalHeight(node->right);
}

treeNode* LL(treeNode* node) { // LL 회전 연산
	treeNode* child = node->left; 
	node->left = child->right;
	if (child->right != NULL)
		child->right->parent = node;
	child->right = node;
	child->parent = node->parent;
	node->parent = child;
	return child;
}

treeNode* RR(treeNode* node) { // RR 회전 연산
	treeNode* child = node->right;
	node->right = child->left;
	if (child->left != NULL)
		child->left->parent = node;
	child->left = node;
	child->parent = node->parent;
	node->parent = child;
	return child;
}

treeNode* LR(treeNode* node) { // LR 회전 연산
	node->left = RR(node->left);  // RR 회전 후 LL 회전
	return LL(node);
}

treeNode* RL(treeNode* node) { // RL 회전 연산
	node->right = LL(node->right); // LL 회전 후 RR 회전
	return RR(node);
}

treeNode* balancing(treeNode* node) {
	int BF = CalBF(node); 
	// BF가 -1,0,1이 아니면 불균형
	if (BF >= 2) { // 균형이 깨진 노드의 BF가 +이면 왼쪽 서브 트리에 문제가 있다.
		BF = CalBF(node->left);  
		if (BF >= 1) {
			node = LL(node); // LL 회전 연산
		}
		else {
			node = LR(node); // LR 회전 연산
		}
	}
	else if (BF <= -2) { // 균형이 깨진 노드의 BF가 -이면 오른쪽 서브 트리에 문제가 있다.
		BF = CalBF(node->right);
		if (BF <= -1) {
			node = RR(node); // RR 회전 연산
		}
		else {
			node = RL(node); // RL 회전 연산
		}
	}
	return node;
}

treeNode* insert(treeNode* node, int data) {
	if (node == NULL) { // node가 비었을 때
		node = (treeNode*)malloc(sizeof(treeNode));
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		node->data = data; // 삽입할 데이타 노드에 삽입
		return node;
	}
	else if (data < node->data) { // 새로 삽입된 데이타가 원래 노드에 있던 데이타보다 작을 때
		node->left = insert(node->left, data); // 왼쪽 노드에 삽입
		node->left->parent = node;
		node = balancing(node); // 불균형인 노드를 균형있는 노드로 
	}
	else if (data > node->data) { // 새로 삽입된 데이타가 원래 노드에 있던 데이타보다 클 때
		node->right = insert(node->right, data); // 오른쪽 노드에 삽입
		node->right->parent = node;
		node = balancing(node); // 불균형인 노드를 균형있는 노드로 
	}
	else {
		printf("\n데이타가 중복됩니다.\n");
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

treeNode* search(treeNode* root, int data) { // AVL 트리에서 데이타를 탐색하는 함수
	treeNode* node;
	int count = 0;
	node = root;
	while (node != NULL) {
		count++;
		if (data < node->data)
			node = node->left;
		else if (data == node->data) {
			printf("%d번째에 탐색 성공", count);
			return node;
		}
		else
			node = node->right;
	}
	count++;
	printf("%d번째에 탐색 실패", count);
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
		printf("파일이 열리지 않음");
		return 0;
	}
	fread(input_data, 1,MAX, fp);

	char* ptr = strtok(input_data, ","); // ","을 기준으로 분리해서 데이타 저장
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
		int_data = atoi(string_data[j]); // 문자열인 데이타를 정수형으로 변환
		printf("%d ", int_data);
		root = insert(root,int_data); 
		int_data = 0;
		k++;
	}

	printf("\nAVL\n");
	Inorder(root);

	int random = 0; // 정수형 변수 선언
	random = rand() % 99; // 난수 생성

	printf("\n\n AVL 트리에서 %d 탐색 : ", random);
	search(root, random);
}