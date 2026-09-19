#include <iostream>
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
    bool is_sorted;
    int frequency;
    string word;
    vector<pair<int, string>> query;
    DictionaryTreeNode *branch[36];
    DictionaryTreeNode();
    DictionaryTreeNode(char ch);
    DictionaryTreeNode(char ch, int freq);
    bool isLeafNode();
};

DictionaryTreeNode *BuildDictionary(vector<string> &words, vector<int> &freq);
void SearchForDictionary(DictionaryTreeNode *root, string &keyword);
bool CompareStrings(pair<int, string> &a, pair<int, string> &b);
int getIndex(char ch);
char indexToChar(int index);
vector<pair<int, string>> PostOrder(DictionaryTreeNode *root);
void CutQuery(DictionaryTreeNode *root);
void PrintResult(vector<pair<int, string>> &query_result);
vector<string> words;
vector<string> keywords;
vector<int> freq;
int count_of_words, count_of_queries, k;
string temp_string;
int temp_freq;

int main(void)
{
    cin >> count_of_words >> count_of_queries >> k;
    for (int i = 0; i < count_of_words; i++)
    {
        cin >> temp_freq >> temp_string;
        words.push_back(temp_string);
        freq.push_back(temp_freq);
    }
    for (int i = 0; i < count_of_queries; i++)
    {
        cin >> temp_string;
        keywords.push_back(temp_string);
    }
    DictionaryTreeNode *root_of_dictionary = BuildDictionary(words, freq);
    PostOrder(root_of_dictionary);
    CutQuery(root_of_dictionary);
    for (int i = 0; i < count_of_queries; i++)
    {
        SearchForDictionary(root_of_dictionary, keywords[i]);
        if (i < count_of_queries - 1)
        {
            putchar(10);
        }
    }

    return 0;
}

DictionaryTreeNode::DictionaryTreeNode()
{
    val = 0;
    frequency = 0;
    memset(branch, 0x00, sizeof(DictionaryTreeNode *) * 36);
    is_sorted = false;
    return;
}

DictionaryTreeNode::DictionaryTreeNode(char ch)
{
    val = ch;
    frequency = 0;
    memset(branch, 0x00, sizeof(DictionaryTreeNode *) * 36);
    is_sorted = false;
    return;
}

DictionaryTreeNode::DictionaryTreeNode(char ch, int freq)
{
    val = ch;
    frequency = freq;
    memset(branch, 0x00, sizeof(DictionaryTreeNode *) * 36);
    is_sorted = false;
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

DictionaryTreeNode *BuildDictionary(vector<string> &words, vector<int> &freq)
{
    DictionaryTreeNode *pChar, *pRoot;
    int index = 0;
    pRoot = new DictionaryTreeNode;
    pChar = pRoot;
    for (int i = 0; i < count_of_words; i++)
    {
        int word_length = (int)words[i].size();
        for (int j = 0; j < word_length; j++)
        {
            index = getIndex(words[i][j]);
            if (pChar->branch[index] == nullptr)
            {
                pChar->branch[index] = new DictionaryTreeNode(words[i][j]);
            }
            pChar = pChar->branch[index];
        }
        pChar->frequency = max(freq[i], pChar->frequency);
        pChar->word = words[i];
        pChar = pRoot;
    }

    return pRoot;
}

//'root' for the root of the dictionary tree
void SearchForDictionary(DictionaryTreeNode *root, string &keyword)
{
    DictionaryTreeNode *pChar = root;
    int keyword_length = (int)keyword.size(), index = 0;
    for (int i = 0; i < keyword_length; i++)
    {
        index = getIndex(keyword[i]);
        if (pChar->branch[index] == nullptr)
        {
            cout << "no suggestion" << endl;
            return;
        }
        else
        {
            pChar = pChar->branch[index];
        }
    }
    PrintResult(pChar->query);
    return;
}

bool CompareStrings(pair<int, string> &a, pair<int, string> &b)
{
    if (a.first > b.first)
    {
        return true;
    }
    else if (a.first < b.first)
    {
        return false;
    }

    return a.second <= b.second;
}

int getIndex(char ch)
{
    return (ch >= '0' && ch <= '9') ? ch - '0' : ch - 'a' + 10;
}

char indexToChar(int index)
{
    return (index >= 0 && index <= 9) ? index + '0' : index - 10 + 'a';
}

vector<pair<int, string>> PostOrder(DictionaryTreeNode *root)
{
    vector<pair<int, string>> ans, temp;
    if (!root)
    {
        return ans;
    }
    for (int i = 0; i < 36; i++)
    {
        temp = PostOrder(root->branch[i]);
        root->query.insert(root->query.end(), temp.begin(), temp.end());
    }
    ans = root->query;
    if (root->isLeafNode())
    {
        ans.push_back(make_pair(root->frequency, root->word));
    }
    return ans;
}

void PrintResult(vector<pair<int, string>> &query_result)
{
    int print_limit = min(k, (int)query_result.size());
    if (print_limit <= 0)
    {
        cout << "no suggestion";
        putchar(10);
        return;
    }
    for (int i = 0; i < print_limit; i++)
    {
        cout << query_result[i].second;
        putchar(10);
    }
    return;
}

void CutQuery(DictionaryTreeNode *root)
{
    if (!root)
    {
        return;
    }
    sort(root->query.begin(), root->query.end(), CompareStrings);
    while (root->query.size() > k)
    {
        root->query.pop_back();
    }
    for (int i = 0; i < 36; i++)
    {
        CutQuery(root->branch[i]);
    }
    return;
}