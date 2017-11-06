#include<stdio.h>
#include<stdlib.h>

//트리 노드 선언
typedef struct Node {
	int data;
	struct Node *left;
	struct Node *right;
} Node;

//이진 탐색 트리의 선언
typedef struct BST {
	Node* root;
} BST;

//노드의 생성자
Node* newNode(int data) {
	Node* returnNode = (Node*)malloc(sizeof(Node));
	returnNode->data = data;
	returnNode->left = NULL;
	returnNode->right = NULL;
	return returnNode;
}

//이진 탐색 트리의 생성자
BST* newBST() {
	BST* returnBST = (BST*)malloc(sizeof(BST));
	returnBST->root = NULL;
	return returnBST;
}

//노드의 소멸자
void freeNode(Node* p) {
	if (p == NULL) return;
	freeNode(p->left);
	freeNode(p->right);
	free(p);
}

//이진 탐색 트리의 소멸자
void freeBST(BST* bst) {
	if (bst == NULL) return;
	freeNode(bst->root);
	free(bst);
}

//이진탐색을 이용한 삽입
void bSearchInsert(Node* p, int data) {
	if (p->data > data) {
		if (p->left == NULL) p->left = newNode(data);
		else bSearchInsert(p->left, data);
	}
	else {
		if (p->right == NULL) p->right = newNode(data);
		else bSearchInsert(p->right, data);
	}
}

//이진 탐색 트리에서 삽입
void InsertBST(BST* t, int data) {
	if (t->root == NULL) t->root = newNode(data);
	else bSearchInsert(t->root, data);
}

//이진 탐색
Node* bSearch(Node* p, int data) {
	if (p == NULL) return NULL;
	if (p->data == data) return p;
	if (p->data > data) return bSearch(p->left, data);
	else return bSearch(p->right, data);
}

//이진 탐색 트리에서의 이진 탐색
Node* SearchBST(BST* t, int data) {
	return bSearch(t->root, data);
}
//최소값
Node* MinNode(Node* p) {
	if (p == NULL) return NULL;
	if (p->left == NULL) return p;
	return MinNode(p->left);
}
//최대값
Node* MaxNode(Node* p) {
	if (p == NULL) return NULL;
	if (p->right == NULL) return p;
	return MaxNode(p->right);
}

//특정 노드의 부모노드를 반환
Node* FindParentNode(Node* p, Node* dest) {
	Node* left, *right;
	if (p == NULL) return NULL;
	if (p->left != NULL) { if (p->left == dest) return p; }
	if (p->right != NULL) { if (p->right == dest) return p; }
	if (p->left == NULL && p->right == NULL) return NULL;
	left = FindParentNode(p->left, dest);
	right = FindParentNode(p->right, dest);
	if (left != NULL) return left;
	else if (right != NULL) return right;
	else return NULL;
}

//노드의 삭제 - 후행 작업
int DeleteNode(Node* p, int data) {
	Node* tmp, *p_tmp, *max, *p_max;
	if ((tmp = bSearch(p, data)) == NULL) return 0;
	p_tmp = FindParentNode(p, tmp);
	if (tmp->left != NULL) {
		max = MaxNode(tmp->left);
		p_max = FindParentNode(p, max);
		if (p_max->left == max) p_max->left = max->left;
		else p_max->right = max->left;
		max->left = tmp->left;
		max->right = tmp->right;
		if (p_tmp->left == tmp) p_tmp->left = max;
		else p_tmp->right = max;
		free(tmp);
		return 1;
	}
	else if (tmp->right != NULL) {
		if (p_tmp->left == tmp) p_tmp->left = tmp->right;
		else p_tmp->right = tmp->right;
		free(tmp);
		return 1;
	}
	else {
		if (p_tmp->left == tmp) p_tmp->left = NULL;
		else p_tmp->right = NULL;
		free(tmp);
		return 1;
	}
}
//이진 탐색 트리에서의 삭제 - 선행 작업
int DeleteBST(BST* bst, int data) {
	Node* max, *p_max, *tmp;
	if (bst == NULL) return 0;
	if (bst->root == NULL) return 0;
	if (bst->root->data == data) {
		if (bst->root->left != NULL) {
			tmp = bst->root;
			max = MaxNode(bst->root->left);
			p_max = FindParentNode(bst->root, max);
			if (p_max->left == max) p_max->left = max->left;
			else p_max->right = max->left;
			max->left = tmp->left;
			max->right = tmp->right;
			bst->root = max;
			free(tmp);
			return 1;
		}
		else if (bst->root->right != NULL) {
			tmp = bst->root;
			bst->root = tmp->right;
			free(tmp);
			return 1;
		}
		else {
			free(bst->root);
			bst->root = NULL;
			return 1;
		}
	}
	else return DeleteNode(bst->root, data);
}
