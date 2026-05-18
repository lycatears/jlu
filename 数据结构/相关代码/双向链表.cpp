#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;
char in_str[50050] = { 0 };
struct DoubleNode
{
	char data;
	DoubleNode* left;
	DoubleNode* right;
	DoubleNode();
	DoubleNode(char& x);
	DoubleNode(char& x, DoubleNode* left, DoubleNode* right);
};

DoubleNode::DoubleNode()
{
	left = right = nullptr;
	data = '\0';
}

DoubleNode::DoubleNode(char& x)
{
	left = right = nullptr;
	data = x;
}

DoubleNode::DoubleNode(char& x, DoubleNode* left, DoubleNode* right)
{
	this->right = right;
	this->left = left;
	left->right = this;
	if (right)
	{
		right->left = this;
	}
	data = x;
}

DoubleNode* End(DoubleNode* head)
{
	DoubleNode* p = head;
	while (p->right)
	{
		p = p->right;
	}
	return p;
}

int main(void)
{
	DoubleNode* head = new DoubleNode;
	head->right = new DoubleNode(in_str[0], head, NULL);
	DoubleNode* cursor = head;
	DoubleNode* end = head->right;
	//this is the cursor of our string and the new in_str[i]aracter will be appended to the 'right' pointer
	
	cin.getline(in_str, 50050);
	for (int i = 0; i < 50000 && in_str[i] != '\0'; i++)
	{
		if (in_str[i] == ' ' || in_str[i] == '_' ||
			(in_str[i] >= 'a' && in_str[i] <= 'z') ||
			(in_str[i] >= 'A' && in_str[i] <= 'Z'))
		{
			cursor->right = new DoubleNode(in_str[i], cursor, cursor->right);
			cursor = cursor->right;
		}
		else if (in_str[i] == '{')
		{
			cursor = head;
		}
		else if (in_str[i] == '}')
		{
			cursor = end->left;
		}
		else if (in_str[i] == '<')
		{
			if (cursor != head)
			{
				cursor = cursor->left;
			}
		}
		else if (in_str[i] == '>')
		{
			if (cursor->right != end)
			{
				cursor = cursor->right;
			}
		}
		else if (in_str[i] == '#')
		{
			if (cursor == head)
			{//do NOT delete the head
				continue;
			}
			else
			{
				DoubleNode* temp = cursor;
				cursor->left->right = cursor->right;
				if (cursor->right)
				{
					cursor->right->left = cursor->left;
				}
				cursor = cursor->left;
				delete temp;
			}
		}
	}

	DoubleNode* p = head->right;
	while (p->right)
	{
		putchar(p->data);
		p = p->right;
	}

	return 0;
}
