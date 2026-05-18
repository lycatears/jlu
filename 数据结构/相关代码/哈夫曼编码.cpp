#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

struct HuffmanNode
{
	char data;
	int weight;
	HuffmanNode* left;
	HuffmanNode* right;
	HuffmanNode();
	HuffmanNode(char data);
	HuffmanNode(char data, int weight);
};

vector<HuffmanNode*> nodes;
int frequence[30] = { 0 };
vector<char> ch;
string text, compressed1, compressed2;
string current_code;
string codes[30];

void BuildFreq(string& text, int freq[], vector<char>& ch);
bool isCharExist(vector<char>& ch, char target);
void BuildNodes(vector<HuffmanNode*>& nodes, vector<char>& ch, int freq[]);
void InsertSort(vector<HuffmanNode*>& nodes);
HuffmanNode* BuildHuffmanTree(vector<HuffmanNode*>& nodes);
void PreOrder(HuffmanNode* root, char explore_stage, char father_char);
void BubbleSort(vector<char>& ch, int frequence[]);
void ShowHuffmanCodes(vector<char>& ch, string codes[]);
void Decode(string& compressed, string codes[]);
void GetCompressedSize(string& text, string codes[]);

int main(void)
{
	cin >> text;
	BuildFreq(text, frequence, ch);
	BuildNodes(nodes, ch, frequence);
	HuffmanNode* root = BuildHuffmanTree(nodes);
	PreOrder(root, 0, 0);
	cin >> compressed1 >> compressed2;
	GetCompressedSize(text, codes);
	ShowHuffmanCodes(ch, codes);
	Decode(compressed1, codes);
	Decode(compressed2, codes);
	return 0;
}

HuffmanNode::HuffmanNode() :data(0), weight(0), left(nullptr), right(nullptr) {};
HuffmanNode::HuffmanNode(char data) :data(data), weight(0), left(nullptr), right(nullptr) {};
HuffmanNode::HuffmanNode(char data, int weight) :data(data), weight(weight), left(nullptr), right(nullptr) {};

void BuildFreq(string& text, int freq[], vector<char>& ch)
{
	for (int i = 0; i < (int)text.size(); i++)
	{
		if (!isCharExist(ch, text[i]))
		{
			ch.push_back(text[i]);
		}
		freq[text[i] - 'a']++;
	}
	return;
}

bool isCharExist(vector<char>& ch, char target)
{
	for (int i = 0; i < (int)ch.size(); i++)
	{
		if (ch[i] == target)
		{
			return true;
		}
	}
	return false;
}

void BuildNodes(vector<HuffmanNode*>& nodes, vector<char>& ch, int freq[])
{
	for (int i = 0; i < (int)ch.size(); i++)
	{
		nodes.push_back(new HuffmanNode(ch[i], freq[ch[i] - 'a']));
	}
	InsertSort(nodes);
	BubbleSort(ch, freq);
	return;
}

void InsertSort(vector<HuffmanNode*>& nodes)
{
	int n = (int)nodes.size();
	for (int i = 1; i < n; i++)
	{
		int k = nodes[i]->weight, j = i - 1;
		while (j >= 0 && k < nodes[j]->weight)
		{
			swap(nodes[j + 1], nodes[j]);
			j--;
		}
		nodes[j + 1]->weight = k;
	}
	return;
}

HuffmanNode* BuildHuffmanTree(vector<HuffmanNode*>& nodes)
{
	int n = (int)nodes.size();
	for (int i = 0; i < n - 1; i++)
	{
		HuffmanNode* t = new HuffmanNode('\0', nodes[i]->weight + nodes[i + 1]->weight);
		t->left = nodes[i];
		t->right = nodes[i + 1];
		for (int j = i + 2; j <= n; j++)
		{
			if (j >= n || nodes[j]->weight > t->weight)
			{
				nodes[j - 1] = t;
				break;
			}
			nodes[j - 1] = nodes[j];
		}
	}
	return nodes[n - 1];
}

void PreOrder(HuffmanNode* root, char explore_stage, char father_char)
{
	if (!root)
	{
		if (explore_stage == '1')
		{
			codes[father_char - 'a'] = current_code;
		}
		return;
	}
	if (explore_stage != 0)
	{
		current_code.push_back(explore_stage);
	}
	PreOrder(root->left, '0', root->data);
	PreOrder(root->right, '1', root->data);
	if (!current_code.empty())
	{
		current_code.pop_back();
	}
	return;
}

void BubbleSort(vector<char>& ch, int frequence[])
{
	int bound = (int)ch.size() - 1;
	while (bound > 0)
	{
		int t = 0;
		for (int i = 0; i < bound; i++)
		{
			if (frequence[ch[i] - 'a'] > frequence[ch[i + 1] - 'a'])
			{
				swap(ch[i], ch[i + 1]);
				t = i;
			}
		}
		bound = t;
	}
}

void ShowHuffmanCodes(vector<char>& ch, string codes[])
{
	for (int i = 0; i < (int)ch.size(); i++)
	{
		printf("%c:%s\n", ch[i], codes[ch[i] - 'a'].c_str());
	}
	return;
}

void Decode(string& compressed, string codes[])
{
	string temp, decoded;
	for (int i = 0; i < compressed.size(); i++)
	{
		temp.push_back(compressed[i]);
		for (int j = 0; j < 30; j++)
		{
			if (temp == codes[j] && !temp.empty())
			{
				temp.clear();
				decoded.push_back('a' + j);
			}
		}
	}
	if (temp.empty())
	{
		cout << decoded << endl;
	}
	else
	{
		cout << "INVALID" << endl;
	}
	return;
}

void GetCompressedSize(string& text, string codes[])
{
	int temp = 0;
	for (int i = 0; i < text.size(); i++)
	{
		temp += (int)codes[text[i] - 'a'].size();
	}
	if (temp % 8)
	{
		temp /= 8;
		temp++;
	}
	else
	{
		temp /= 8;
	}
	printf("%d %d\n", (int)text.size(), temp);
	return;
}