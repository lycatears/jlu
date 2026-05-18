#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <deque>

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

deque<TreeNode*> NodeDequeA;
deque<TreeNode*> NodeDequeB;

void ClearStack(stack<TreeNode>& stack);
TreeNode* CreateBinaryTree(void);

int main(void)
{
	TreeNode* root = CreateBinaryTree();
	TreeNode* temp = nullptr;
	int level = 0;
	bool isout = false;
	int a = 0, b = 0;
	cin >> a >> b;
	NodeDequeA.push_front(root);
	while (1)
	{
		while (!NodeDequeA.empty())
		{
			temp = NodeDequeA.back();
			NodeDequeA.pop_back();
			if (temp->right)
			{
				NodeDequeB.push_front(temp->right);
			}
			if (temp->left)
			{
				NodeDequeB.push_front(temp->left);
			}
			if (temp->data == a)
			{
				isout = true;
			}
			if (temp->data == b)
			{
				printf("%d \n", temp->data);
				return 0;
			}
			if (isout)
			{
				printf("%d ", temp->data);
			}
		}
		while (!NodeDequeB.empty())
		{
			temp = NodeDequeB.front();
			NodeDequeB.pop_front();
			if(temp->left)
			{
				NodeDequeA.push_back(temp->left);
			}
			if(temp->right)
			{
				NodeDequeA.push_back(temp->right);
			}
			if (temp->data == a)
			{
				isout = true;
			}
			if (temp->data == b)
			{
				printf("%d \n", temp->data);
				return 0;
			}
			if (isout)
			{
				printf("%d ", temp->data);
			}
		}
		if (NodeDequeA.empty() && NodeDequeB.empty())
		{
			break;
		}
	}
	
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

