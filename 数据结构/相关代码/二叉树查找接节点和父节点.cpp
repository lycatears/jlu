#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stack>

using namespace std;

struct TreeNode
{
public:
	TreeNode* left;
	TreeNode* right;
	int data;
	TreeNode();
	TreeNode(int data);
	TreeNode(int data, TreeNode* left, TreeNode* right);
};

stack<TreeNode*> NodeStack;
int m = 0, k = 0;

void ClearStack(stack<TreeNode>& stack);
TreeNode* CreateBinaryTree(void);
void PreOrder(TreeNode* root);
void MidOrder(TreeNode* root);
void PostOrder(TreeNode* root);
int FindFather(int k, TreeNode* root);

int main(void)
{
	TreeNode* root = CreateBinaryTree();
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> k;
		if (root->data == k)
		{
			printf("0\n");
			continue;
		}
		else
		{
			printf("%d\n", FindFather(k, root));
		}
	}

	return 0;
}

TreeNode::TreeNode()
{
	data = 0;
	left = right = nullptr;
}

TreeNode::TreeNode(int data)
{
	this->data = data;
	left = right = nullptr;
}

TreeNode::TreeNode(int data, TreeNode* left, TreeNode* right)
{
	this->data = data;
	this->left = left;
	this->right = right;
}

void ClearStack(stack<TreeNode>& Stack)
{
	while (!Stack.empty())
	{
		Stack.pop();
	}

	return;
}

TreeNode* CreateBinaryTree(void)
{
	int temp = 0;
	cin >> temp;
	if (temp == 0)
	{
		return nullptr;
	}
	TreeNode* root = new TreeNode(temp);
	root->left = CreateBinaryTree();
	root->right = CreateBinaryTree();

	return root;
}

void PreOrder(TreeNode* root)
{
	if (!root)
	{
		return;
	}
	printf("%d ", root->data);
	PreOrder(root->left);
	PreOrder(root->right);
	return;
}

void MidOrder(TreeNode* root)
{
	if (!root)
	{
		return;
	}
	MidOrder(root->left);
	printf("%d ", root->data);
	MidOrder(root->right);
	return;
}

void PostOrder(TreeNode* root)
{
	if (!root)
	{
		return;
	}
	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d ", root->data);
	return;
}

int FindFather(int k, TreeNode* root)
{
	if (!root)
	{
		return 0;
	}
	if (root->left)
	{
		if (root->left->data == k)
		{
			return root->data;
		}
	}
	if (root->right)
	{
		if (root->right->data == k)
		{
			return root->data;
		}
	}
	return FindFather(k, root->left) + FindFather(k, root->right);
}
