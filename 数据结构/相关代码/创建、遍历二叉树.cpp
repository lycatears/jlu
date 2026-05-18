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
int index = 0;

void ClearStack(stack<TreeNode>& stack);
TreeNode* CreateBinaryTree(void);
void PreOrder(TreeNode* root);
void MidOrder(TreeNode* root);
void PostOrder(TreeNode* root);

int main(void)
{
	TreeNode* root = CreateBinaryTree();
	PreOrder(root);
	putchar(10);
	MidOrder(root);
	putchar(10);
	PostOrder(root);
	putchar(10);

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
