#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

string in_str;
stack<char> operations;
stack<int> nums;
vector<string> results;
bool SingleCalculate(stack<char>& opreations, stack<int>& nums);
void GenerateStacks(string& in_str, stack<char>& operations, stack<int>& nums);
int myPow(int a, int b);
void clear(void);

int main(void)
{
	while (cin >> in_str)
	{
		GenerateStacks(in_str, operations, nums);
		clear();
	}
	for (int i = 0; i < results.size(); i++)
	{
		if (i < results.size() - 1)
		{
			cout << results[i] << endl;
		}
		else
		{
			cout << results[i];
		}
	}
	return 0;
}

int myPow(int a, int b)
{
	int temp = 1;
	while (b > 0)
	{
		if (b & 1)
		{
			temp *= a;
		}
		a *= a;
		b >>= 1;
	}
	return temp;
}

void clear(void)
{
	while (!nums.empty())
	{
		nums.pop();
	}
	while (!operations.empty())
	{
		operations.pop();
	}
}

bool SingleCalculate(stack<char>& operations, stack<int>& nums)
{
	char op = operations.top();
	operations.pop();
	int arg_a = nums.top();
	nums.pop();
	int arg_b = nums.top();
	nums.pop();
	switch (op)
	{
	case '+':nums.push(arg_a + arg_b); break;
	case '-':nums.push(arg_b - arg_a); break;
	case '*':nums.push(arg_a * arg_b); break;
	case '/':
		if (arg_a == 0)
		{
			results.push_back("INVALID");
			return false;
		}
		nums.push(arg_b / arg_a);
		break;
	case '^':nums.push(myPow(arg_b, arg_a)); break;
	}
	return true;
}

void GenerateStacks(string& in_str, stack<char>& operations, stack<int>& nums)
{
	in_str = in_str + '#';
	int n = in_str.size();

	for (int i = 0; i < n; i++)
	{//mid
		char top;
		if (!operations.empty())
		{
			top = operations.top();
		}
		if (in_str.at(i) >= '0' && in_str.at(i) <= '9')//if it is a number
		{
			int temp = 0;
			while (i < n && in_str.at(i) >= '0' && in_str.at(i) <= '9')
			{
				temp = temp * 10 + in_str[i] - '0';
				i++;
			}
			nums.push(temp);
			i--;
		}
		else//NaN
		{
			if (operations.empty() || top == '(')//if the stack is empty or the top is '('
			{
				operations.push(in_str[i]);
			}
			else if ((in_str[i] == '*' || in_str[i] == '/' || in_str[i] == '^') && (top == '+' || top == '-'))//pirority
			{
				operations.push(in_str[i]);
			}
			else if ((in_str[i] == '^') && (top == '*' || top == '/' || top == '+' || top == '-'))//pirority
			{
				operations.push(in_str[i]);
			}
			else if (((top == '*' || top == '/' || top == '^') && (in_str[i] == '+' || in_str[i] == '-')) || ((top == '^') && (in_str[i] == '*' || in_str[i] == '/' || in_str[i] == '+' || in_str[i] == '-')))
			{
				while (!operations.empty())
				{
					if (operations.top() == '(')
					{
						//operations.pop();
						break;
					}
					else if ((in_str[i] == '*' || in_str[i] == '/' || in_str[i] == '^') && (operations.top() == '+' || operations.top() == '-'))
					{
						break;
					}
					else if ((in_str[i] == '^') && (operations.top() == '*' || operations.top() == '/' || operations.top() == '+' || operations.top() == '-'))
					{
						break;
					}
					if (!SingleCalculate(operations, nums))
					{
						return;
					}
					//operations.pop();
				}
				operations.push(in_str[i]);
			}
			else if (((top == '+' || top == '-') && (in_str[i] == '+' || in_str[i] == '-')) || ((top == '*' || top == '/') && (in_str[i] == '*' || in_str[i] == '/')) || ((top == '^') && (in_str[i] == '^')))
			{
				while (!operations.empty())
				{
					if (operations.top() == '(')
					{
						//operations.pop();
						break;
					}
					else if ((in_str[i] == '*' || in_str[i] == '/' || in_str[i] == '^') && (operations.top() == '+' || operations.top() == '-'))
					{
						break;
					}
					else if ((in_str[i] == '^') && (operations.top() == '*' || operations.top() == '/' || operations.top() == '+' || operations.top() == '-'))
					{
						break;
					}
					if (!SingleCalculate(operations, nums))
					{
						return;
					}
					
				}
				operations.push(in_str[i]);
			}
			else if (in_str[i] == '(')
			{
				operations.push('(');
			}
			else if (in_str[i] == ')')
			{
				while (operations.top() != '(')
				{
					if (!SingleCalculate(operations, nums))
					{
						return;
					}
					//operations.pop();
				}
				operations.pop();
			}
			else if (in_str[i] == '#')
			{
				while (!operations.empty() && nums.size() > 1)
				{
					if (!SingleCalculate(operations, nums))
					{
						return;
					}
				}
			}
		}
	}
	results.push_back(to_string(nums.top()));
	return;
}