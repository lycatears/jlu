#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;

stack<char> Stack;
string in_str;
void clear(void);
bool JudgeMatch(string& in_str);
void FixMatch(string& in_str);

int main(void)
{
	while (cin >> in_str)
	{
		if (JudgeMatch(in_str))
		{
			cout << "Match" << endl;
		}
		else
		{
			FixMatch(in_str);
		}
		clear();
	}
	return 0;
}

bool JudgeMatch(string& in_str)
{
	for (int i = 0; i < in_str.size(); i++)
	{
		if (Stack.empty())
		{
			Stack.push(in_str[i]);
		}
		else if (in_str[i] == '(')
		{
			Stack.push(in_str[i]);
		}
		else if (in_str[i] == ')')
		{
			if (Stack.empty())
			{
				return false;
			}
			else if (Stack.top() == '(')
			{
				Stack.pop();
			}
			else if (Stack.top() == ')')
			{
				Stack.push(')');
			}
		}
	}
	if (Stack.empty())
	{
		return true;
	}
	return false;
}

void clear(void)
{
	while (!Stack.empty())
	{
		Stack.pop();
	}
}

void FixMatch(string& in_str)
{
	int left = 0, right = 0;
	while (!Stack.empty())
	{
		if (Stack.top() == '(')
		{
			left++;
		}
		else if (Stack.top() == ')')
		{
			right++;
		}
		Stack.pop();
	}
	char* pre_post_fix = new char[10010];
	memset(pre_post_fix, ')', left);
	pre_post_fix[left] = '\0';
	in_str = in_str + string(pre_post_fix);
	memset(pre_post_fix, '(', right);
	pre_post_fix[right] = '\0';
	in_str = string(pre_post_fix) + in_str;
	cout << right + left << endl;
	cout << in_str << endl;
	delete[] pre_post_fix;
	return;
}