#include <iostream>
#include <memory>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

class DictionaryTreeNode
{
public:
	char val;
	int frequency;
	string word;
	DictionaryTreeNode* branch[36];
	DictionaryTreeNode();
	DictionaryTreeNode(char ch);
	DictionaryTreeNode(char ch, int freq);
	bool isLeafNode();
};

DictionaryTreeNode* BuildDictionary(vector<string>& words, vector<int>& freq);
vector<pair<string, int>> SearchForDictionary(DictionaryTreeNode* root, string keyword);
void SearchForPostfix(DictionaryTreeNode* endOfKeyword);
bool CompareStrings(pair<string, int> a, pair<string, int> b);
vector<string> words;
vector<pair<string, int>> query_result;
vector<string> keywords;
vector<int> freq;
int count_of_words, count_of_queries, k;
string temp_string;
int temp_freq;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
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
		for (int j = 0; j < (int)query_result.size(); j++)
		{
			if (query_result[j].first == keywords[i])
			{
				query_result.erase(query_result.begin() + j);
			}
		}
		sort(query_result.begin(), query_result.end(), CompareStrings);
		if ((int)query_result.size() < k && (int)query_result.size() > 0)
		{
			for (int j = 0; j < (int)query_result.size(); j++)
			{
				cout << query_result[j].first << endl;
			}
		}
		else if (query_result.size() == 0)
		{
			cout << "no suggestion" << endl;
		}
		else
		{
			for (int j = 0; j < k; j++)
			{
				cout << query_result[j].first << endl;
			}
		}
		if (i < count_of_queries - 1)
		{
			cout << endl;
		}
		query_result.clear();
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
		pChar->word = temp_string;
		pChar = pRoot;
	}


	return pRoot;
}

//'root' for the root of the dictionary tree
vector<pair<string, int>> SearchForDictionary(DictionaryTreeNode* root, string keyword)
{
	DictionaryTreeNode* pChar = root;
	for (int i = 0; i < (int)keyword.size(); i++)
	{
		if (keyword[i] >= '0' && keyword[i] <= '9')
		{
			if (pChar->branch[keyword[i] - '0'] == nullptr)
			{
				return query_result;
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
				return query_result;
			}
			else
			{
				pChar = pChar->branch[keyword[i] - 'a' + 10];
			}
		}
		else
		{
			return query_result;
		}
	}
	//if (pChar->isLeafNode())
	//{
	//	return query_result;
	//}
	SearchForPostfix(pChar);

	return query_result;
}

void SearchForPostfix(DictionaryTreeNode* endOfKeyword)
{
	if (endOfKeyword->isLeafNode())
	{
		query_result.push_back(pair<string, int>(endOfKeyword->word, endOfKeyword->frequency));
		//return;
	}
	for (int i = 0; i < 36; i++)
	{
		if (endOfKeyword->branch[i] != nullptr)
		{
			SearchForPostfix(endOfKeyword->branch[i]);
		}
	}
	return;
}

bool CompareStrings(pair<string, int> a, pair<string, int> b)
{
	if (a.second > b.second)
	{
		return true;
	}
	else if (a.second < b.second)
	{
		return false;
	}
	for (int i = 0; i < (int)min(a.first.size(), b.first.size()); i++)
	{
		if (a.first[i] < b.first[i])
		{
			return true;
		}
		else return false;
	}
	if (a.first.size() < b.first.size())
	{
		return true;
	}
	return false;
}