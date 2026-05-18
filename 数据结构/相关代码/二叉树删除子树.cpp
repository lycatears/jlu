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
void DelNode(TreeNode* root);
TreeNode* FindNode(int k, TreeNode* root);
//Reflectiom: we need to find the parents of the target node instead of the node itself
//bacause the deleted memory is invalid and it will cause exception 
//when we mid-traverse the binary tree
void MidOrder(TreeNode* root);

int main(void)
{
	TreeNode* root = CreateBinaryTree();
	TreeNode* temp = nullptr;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> k;
		temp = FindNode(k, root);
		if (temp == nullptr)
		{
			printf("0\n");
		}
		else
		{
			DelNode(temp);
			MidOrder(root);
            putchar(10);
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

void DelNode(TreeNode* root)
{
	if (!root)
	{
		return;
	}

	if (root->left == nullptr && root->right == nullptr)
	{
		delete root;
		return;
	}
	DelNode(root->left);
	DelNode(root->right);
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

TreeNode* FindNode(int k, TreeNode* root)
{
	TreeNode* p = nullptr;
	if (!root)
	{
		return nullptr;
	}
	if (k == root->data)
	{
		return nullptr;
	}
	if (root->left)
	{
		if (root->left->data == k)
		{
			p = root->left;
			root->left = nullptr;
			return p;
		}
	}
	if (root->right)
	{
		if (root->right->data == k)
		{
			p = root->right;
			root->right = nullptr;
			return p;
		}
	}
	p = FindNode(k, root->left);
	if (p)
	{
		return p;
	}
	else
	{
		return FindNode(k, root->right);
	}
}