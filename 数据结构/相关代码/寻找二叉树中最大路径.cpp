#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
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


void ClearStack(stack<TreeNode>& stack);
TreeNode* CreateBinaryTree(void);
void PreOrder(TreeNode* root, int father_val, int explore_stage);
vector<int> current_path;
vector<int> max_path;
int max_path_val;

int main(void)
{
	TreeNode* root = CreateBinaryTree();
	PreOrder(root, 0, 0);
	printf("%d\n", max_path_val);
	for (int i = 0; i < max_path.size(); i++)
	{
		printf("%d ", max_path[i]);
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

void PreOrder(TreeNode* root, int father_val, int explore_stage)
{
	int original_count = current_path.size();
	if (!root)
	{
		if (father_val > max_path_val)
		{
			max_path_val = father_val;
			max_path = current_path;
		}
		return;
	}
	current_path.push_back(root->data);
	PreOrder(root->left, father_val + root->data, 0);
	PreOrder(root->right, father_val + root->data, 1);
	while (current_path.size() > original_count)
	{
		current_path.pop_back();
	}

	return;
}