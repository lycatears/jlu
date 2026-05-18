TreeNode* CreateBinaryTreeNonRec(void)
{
	TreeNode* root = nullptr;
	TreeNode* p = nullptr;

	if (nodes[0] == 0)
	{
		return nullptr;
	}
	root = new TreeNode(nodes[0]);
	p = root;
	NodeStack.push(root);

	for (int i = 1; i < count_of_nodes; i++)
	{
		if (p == nullptr)
		{
			break;
		}
		if (NodeStack.empty())
		{
			break;
		}
		if (nodes[i] != 0)
		{
			TreeNode* new_node = new TreeNode(nodes[i]);
			if (p->status == 0)
			{
				p->left = new_node;
				p->status = 1;
				p = p->left;
				NodeStack.push(p);
			}
			else if (p->status == 1)
			{
				p->right = new_node;
				p->status = 2;
				p = p->right;
				NodeStack.push(p);
			}
			else if (p->status == 2)
			{
				while (!NodeStack.empty())
				{
					if (NodeStack.top()->status != 2)
					{
						break;
					}
					NodeStack.pop();
				}
				if (!NodeStack.empty())
				{
					p = NodeStack.top();
				}
				i--;
			}
		}
		else
		{
			if (p->status < 2)
			{
				p->status++;
			}
			else
			{
				while (!NodeStack.empty())
				{
					if (NodeStack.top()->status != 2)
					{
						break;
					}
					NodeStack.pop();
				}
				if (!NodeStack.empty())
				{
					p = NodeStack.top();
				}
				i--;
			}
		}
	}
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

void PreOrderNonRec(TreeNode* root)
{
	TreeNode* p = root;
	while(1)
	{
		while (p != nullptr)
		{
			printf("%d ", p->data);
			NodeStack.push(p);
			p = p->left;
		}
		if (NodeStack.empty())
		{
			return;
		}
		p = NodeStack.top();
		NodeStack.pop();
		p = p->right;
	}
}

void MidOrderNonRec(TreeNode* root)
{
	TreeNode* p = root;
	while (1)
	{
		while (p != nullptr)
		{
			NodeStack.push(p);
			p = p->left;
		}
		if (NodeStack.empty())
		{
			return;
		}
		p = NodeStack.top();
		printf("%d ", p->data);
		NodeStack.pop();
		p = p->right;
	}
}

void PostOrderNonRec(TreeNode* root)
{
	TreeNode* p = root;
	TreeNode* pre = nullptr;

	while (1)
	{
		while (p != nullptr)
		{
			NodeStack.push(p);
			p = p->left;
		}
		if (NodeStack.empty())
		{
			return;
		}
		p = NodeStack.top();
		if (p->right == nullptr || p->right == pre)
		{
			p = NodeStack.top();
			NodeStack.pop();
			printf("%d ", p->data);
			pre = p;
			p = nullptr;
		}
		else
		{
			p = p->right;
		}
	}
}
