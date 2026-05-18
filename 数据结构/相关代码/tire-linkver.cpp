#include <iostream>
#include <memory>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

class DictionaryTreeNode
{
public:
	char val;
	int frequency;
	DictionaryTreeNode* branch[36];
	DictionaryTreeNode();
	DictionaryTreeNode(char ch);
	DictionaryTreeNode(char ch, int freq);
	bool isLeafNode();
};

DictionaryTreeNode* BuildDictionary(vector<string>& words, vector<int>& freq);
void SearchForDictionary(DictionaryTreeNode* root, string keyword);
void SearchForPostfix(DictionaryTreeNode* endOfKeyword, string currentWord, string target);
bool CompareStrings(pair<int, string> a, pair<int, string> b);
priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> query_result;
vector<string> words;
vector<string> keywords;
vector<int> freq;
int count_of_words, count_of_queries, k;
string temp_string;
int temp_freq;

//bool operator > (pair<int, string> a, pair<int, string> b)
//{
//	return !CompareStrings(a, b);
//}
//
//bool operator < (pair<int, string> a, pair<int, string> b)
//{
//	return CompareStrings(a, b);
//}

int main(void)
{
	cin >> count_of_words >> count_of_queries >> k;
	for (int i = 0; i < count_of_words; i++)
	{
		cin >> temp_freq;
		cin >> temp_string;
		words.push_back(temp_string);
		freq.push_back(temp_freq);
	}
	for (int i = 0; i < count_of_queries; i++)
	{
		cin >> temp_string;
		keywords.push_back(temp_string);
	}
	DictionaryTreeNode* root_of_dictionary = BuildDictionary(words, freq);
	for (int i = 0; i < count_of_queries; i++)
	{
		SearchForDictionary(root_of_dictionary, keywords[i]);
		stack<string> temp_stack;
		if (query_result.empty())
		{
			cout << "no suggestion" << endl;
		}
		else
		{
			while (!query_result.empty())
			{
				temp_stack.push(query_result.top().second);
				query_result.pop();
			}
			while (!temp_stack.empty())
			{
				cout << temp_stack.top() << endl;
				temp_stack.pop();
			}
		}
		if (i < count_of_queries - 1)
		{
			putchar(10);
		}
		while (!query_result.empty())
		{
			query_result.pop();
		}
	}

	return 0;
}

DictionaryTreeNode::DictionaryTreeNode()
{
	val = 0;
	frequency = 0;
	memset(branch, 0x00, sizeof(DictionaryTreeNode*) * 36);
	return;
}

DictionaryTreeNode::DictionaryTreeNode(char ch)
{
	val = ch;
	frequency = 0;
	memset(branch, 0x00, sizeof(DictionaryTreeNode*) * 36);
	return;
}

DictionaryTreeNode::DictionaryTreeNode(char ch, int freq)
{
	val = ch;
	frequency = freq;
	memset(branch, 0x00, sizeof(DictionaryTreeNode*) * 36);
	return;
}

bool DictionaryTreeNode::isLeafNode()
{
	if (frequency == 0)
	{
		return false;
	}
	return true;
}

DictionaryTreeNode* BuildDictionary(vector<string>& words, vector<int>& freq)
{
	DictionaryTreeNode* pChar, * pRoot;
	pRoot = new DictionaryTreeNode;
	pChar = pRoot;
	for (int i = 0; i < count_of_words; i++)
	{
		temp_string = words[i];
		for (int j = 0; j < (int)temp_string.size(); j++)
		{
			if (temp_string[j] >= '0' && temp_string[j] <= '9')
			{
				if (pChar->branch[temp_string[j] - '0'] == nullptr)
				{
					pChar->branch[temp_string[j] - '0'] = new DictionaryTreeNode(temp_string[j]);
				}
				pChar = pChar->branch[temp_string[j] - '0'];
			}
			else if (temp_string[j] >= 'a' && temp_string[j] <= 'z')
			{
				if (pChar->branch[temp_string[j] - 'a' + 10] == nullptr)
				{
					pChar->branch[temp_string[j] - 'a' + 10] = new DictionaryTreeNode(temp_string[j]);
				}
				pChar = pChar->branch[temp_string[j] - 'a' + 10];
			}
			else
			{
				pChar->frequency = max(freq[i], pChar->frequency);
				//if a treenode has a frequency larger than 0 and null for all branches, it is a leaf node.
			}
		}
		pChar->frequency = max(freq[i], pChar->frequency);
		pChar = pRoot;
	}


	return pRoot;
}

//'root' for the root of the dictionary tree
void SearchForDictionary(DictionaryTreeNode* root, string keyword)
{
	DictionaryTreeNode* pChar = root;
	for (int i = 0; i < (int)keyword.size(); i++)
	{
		if (keyword[i] >= '0' && keyword[i] <= '9')
		{
			if (pChar->branch[keyword[i] - '0'] == nullptr)
			{
				return;
			}
			else
			{
				pChar = pChar->branch[keyword[i] - '0'];
			}
		}
		else if (keyword[i] >= 'a' && keyword[i] <= 'z')
		{
			if (pChar->branch[keyword[i] - 'a' + 10] == nullptr)
			{
				return;
			}
			else
			{
				pChar = pChar->branch[keyword[i] - 'a' + 10];
			}
		}
		else
		{
			return;
		}
	}
	SearchForPostfix(pChar, keyword, keyword);

	return;
}

void SearchForPostfix(DictionaryTreeNode* endOfKeyword, string currentWord, string target)
{
	string wordOfThisLevel = currentWord;
	if (endOfKeyword->isLeafNode() && target != currentWord)
	{
		query_result.emplace(pair<int, string>(endOfKeyword->frequency, currentWord));
		while (query_result.size() > k)
		{
			query_result.pop();
		}
		//return;
	}
	for (int i = 0; i < 36; i++)
	{
		if (endOfKeyword->branch[i] != nullptr)
		{
			currentWord += endOfKeyword->branch[i]->val;
			SearchForPostfix(endOfKeyword->branch[i], currentWord,target);
		}
		currentWord = wordOfThisLevel;
	}
	return;
}

bool CompareStrings(pair<int, string> a, pair<int, string> b)
{
	if (a.first > b.first)
	{
		return true;
	}
	else if (a.first < b.first)
	{
		return false;
	}
	for (int i = 0; i < (int)min(a.second.size(), b.second.size()); i++)
	{
		if (a.second[i] < b.second[i])
		{
			return true;
		}
		else return false;
	}
	if (a.second.size() < b.second.size())
	{
		return true;
	}
	return false;
}