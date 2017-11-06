#include <stdio.h>
#include <stdlib.h>

// 트리노드선언
typedef struct Tree_node {
	struct Tree_node* parent;
	struct Tree_node* left;
	struct Tree_node* right;
	int value;
}tree_node;

// 트리선언
typedef struct Tree {
	tree_node* root;
	int size;
	tree_node* ptr;
}tree;

// 노드초기화
void treenode_init(tree_node* tn, int val) {
	tn->left = NULL;
	tn->right = NULL;
	tn->parent = NULL;
	tn->value = val;
}

// 트리초기화
void tree_init(tree *tr)
{
	tr->root = NULL;
	tr->size = 0;
	tr->ptr = NULL;
}

// 트리탐색
void tree_search(tree* tr, tree_node* cur, int val) {
	if (cur->value == val) {
		tr->ptr = cur;
	}
	if (cur->left != NULL) {
		tree_search(tr, cur->left, val);
	}
	if (cur->right != NULL) {
		tree_search(tr, cur->right, val);
	}
}

//  트리terminal탐색
void tree_search_terminal(tree* tr, tree_node *cur) {
	tr->ptr = cur;
	if (cur->left != NULL) {
		tree_search_terminal(tr, cur->left);
	}
	if (cur->right != NULL) {
		tree_search_terminal(tr, cur->right);
	}
}
void tree_preorder(struct Tree_node* cur) {
	printf("%d ", cur->value);
	if (cur->left != NULL) {
		tree_preorder(cur->left);
	}
	if (cur->right != NULL) {
		tree_preorder(cur->right);
	}
}

void tree_inorder(tree_node* cur) {
	if (cur->left != NULL) {
		tree_inorder(cur->left);
	}
	printf("%d ", cur->value);
	if (cur->right != NULL) {
		tree_inorder(cur->right);
	}
}

void tree_postorder(tree_node* cur) {
	if (cur->left != NULL) {
		tree_postorder(cur->left);
	}
	if (cur->right != NULL) {
		tree_postorder(cur->right);
	}
	printf("%d ", cur->value);
}

// 노드삽입
void tree_insertion(tree *tr, int parent_value, int val) {
	tree_node *newNode = (tree_node*)malloc(sizeof(tree_node));
	if (tr->root == NULL) {
		tr->root = newNode;
		return;
	}
	tr->ptr = 0;
	tree_node *Parent;
	tree_search(tr, tr->root, parent_value);
	Parent = tr->ptr;
	if (Parent == NULL) {
		// Parent Node not exist
		return;
	}
	else if (Parent->left != NULL) {
		Parent->left = newNode;
		newNode->parent = Parent;
	}
	else if (Parent->right != NULL) {
		Parent->right = newNode;
		newNode->parent = Parent;
	}
	else {
		// parent node has left,right node
	}
}

// 
void tree_deletion(tree *tr, int val) {
	tree_node *remove_node = NULL;
	tree_search(tr, tr->root, val);
	remove_node = tr->ptr;
	if (remove_node == NULL) {
		// node is not exist
		return;
	}
	// Restructuring
	tree_node *remove_parent = remove_node->parent;
	if (remove_node->left == NULL &&remove_node->right == NULL) {
		// this node is leaf/terminal node
		int LR = (remove_parent->right == remove_node);
		if (LR == 0) {
			remove_parent->left = NULL;
		}
		else if (LR == 1) {
			remove_parent->right = NULL;
		}
		if (remove_parent == NULL) {

			free(remove_node);
			tr->root = NULL;
		}
	}
	else if (!(remove_node->left != NULL && remove_node->right != NULL)) {
		// has only one child
		int remove_child_LR = (remove_node->left == NULL); // remove node has left node? right node? [Left : 0 , Right : 1 ]
		tree_node *remove_child = (remove_child_LR == 0) ? remove_node->left : remove_node->right;
		if (remove_parent == NULL) {
			// this is root node
			tr->root = remove_child;
			tr->root->parent = NULL;
			free(remove_node);
			return;
		}
		int LR = (remove_parent->right == remove_node); // left node? right node? [ Left : 0, Right : 1 ]
		remove_child->parent = remove_parent;
		if (LR == 0) {
			remove_parent->left = remove_child;
		}
		else if (LR == 1) {
			remove_parent->right = remove_child;
		}
	}
	else {
		// has two node
		tree_node *swapnode = NULL;
		tree_search_terminal(tr, remove_node);
		swapnode = tr->ptr;
		tree_node *swap_parent = swapnode->parent;
		tree_node* left = remove_node->left;
		tree_node* right = remove_node->right;
		if (swap_parent != NULL) {
			int swap_LR = (swap_parent->right == swapnode);
			if (swap_LR == 0) {
				swap_parent->left = NULL;
			}
			else if (swap_LR == 1) {
				swap_parent->right = NULL;
			}
		}
		if (left != swapnode)
		{
			swapnode->left = left;
			left->parent = swapnode;
		}
		if (right != swapnode) {
			swapnode->right = right;
			right->parent = swapnode;
		}
		swapnode->parent = (remove_node->parent);
		if (remove_parent != NULL) {
			int LR = (remove_parent->right == remove_node);
			if (LR == 0) {
				remove_parent->left = swapnode;
			}
			else if (LR == 1) {
				remove_parent->right = swapnode;
			}
		}
		if (remove_parent == NULL)
		{
			tr->root = swapnode;
		}
	}
	free(remove_node);
}

int main()
{
	tree tr;
	tree_init(&tr);
	tree_insert(&tr, -1, 0);
	tree_insert(&tr, 0, 1);
	tree_insert(&tr, 0, 2);
	tree_insert(&tr, 1, 3);
	tree_insert(&tr, 1, 4);
	tree_insert(&tr, 2, 5);
	tree_insert(&tr, 2, 6);
	tree_insert(&tr, 3, 7);
	printf("tree pre-order result :");
	tree_preorder(tr.root);
	printf("\ntree in-order result :");
	tree_inorder(tr.root);
	printf("\ntree post-order result :");
	tree_postorder(tr.root);
	puts("");
}
