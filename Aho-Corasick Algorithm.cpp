#include <iostream>
#include <cstring>
using namespace std;

int const patt_num = 5;
int const max_patt_size = 5;
//char** patt = new char*[max_patt_size];
char patt[patt_num][max_patt_size] = {"AGA","AA","AAG","GAAG","TCG"};
int text_size = 23;
char* text = new char[text_size];


int*  CharToInt = new int[256];

void InitializeTables()
{
    CharToInt['A']=0;

    CharToInt['C']=1;

    CharToInt['G']=2;

    CharToInt['T']=3;

}

struct Node
{
    Node* child[4];
    int id;
    int index;
    Node* fl;
};


Node* root;

Node* CreatTrieNode()
{
    Node* node = new Node;
    for (int i = 0; i < 4; i++)
    {
        node->child[i] = 0;
    }
    return node;
}


void InsertInTrie()
{
    root = CreatTrieNode();
    root->fl = NULL;
    root->id = 0;
    int ind = 0;
    //int len;
    for (int i = 0; i < 5; i++) /// loop on each pattern
    {
        Node* curr_node = root;
        for (int j = 0; j < strlen(patt[i]); j++) /// loop on each character in a pattern[i]
        {
            if( !curr_node->child[patt[i][j]] ) /// if there is no child carry the new character creat new node for that character
            {/// else go to the next child
                curr_node->child[patt[i][j]] = CreatTrieNode();
                curr_node = curr_node->child[patt[i][j]];
                //curr_node->index = ind;
                //ind++;
            }
            else curr_node = curr_node->child[patt[i][j]];
            curr_node->index = ind; /// store the index of each node in tha trie that will help while getting the failure links
            ind++;
            curr_node->id = -1; /// id of node that is not an end of a pattern
            //len++;
        }
        curr_node->id = i;
    }


}

void GetFL(Node* node)
{/// move on each node in the trie and search for matching between the passed node and any other node in the trie

    Node* currnode = root;

    /// failer links of the child node of the root equal to zero as there's no proper suffix for them
    for (int i = 0; i < 4; i++) currnode->child[i]->fl = 0;

    /// want to loop on each node in the trie and get the prefix of this node
    ///then get the proper suffix of this prefix
    /// then search on it in the trie node if there's match currnode fl will carry the index of this node in the trie

    ///---------------------------------------------------------------------------------------------------------------------

    /// " i tried a lot to get a way to creat a failure link for each node in the trie , but i couldn't reach how to get
    /// actually the proper suffix to compare with it"
    /// i thought about making something like temp node that carry the proper suffix of the prefix i have.
    /// but each time i try something i stuck at point of how to get it. "

    ///----------------------------------------------------------------------------------------------------------------------
    //for ()


}


void TravirseOnTrie(Node* node)
{/// function move on each node by node and get it's failure link by calling get failure link function

    for(int i  = 0; i < 4; i++)
    {
        if (node->child[i])
        {
            TravirseOnTrie(node->child[i]);
            GetFL(node->child[i]);
        }
    }


}


void AhoCoSearch()
{ /// function that search for the patterns in the text character array and return it's report it's location in the text if found

    InitializeTables(); /// function is build to convert the character to int

    Node* currnode = root;
    int i = 0;
    while (i < text_size)
    {
        if( (int)currnode->child[CharToInt[text[i]]] == CharToInt[text[i]]) /// if the character of the current node equals to that in the text
        {
            currnode = currnode->child[CharToInt[text[i]]]; /// move to the child
            if(currnode->id != -1) cout << currnode->index; /// check if the current node carry an id that represent an pattern ot not
            else
            {
                Node* tempnode = currnode; /// temp node caarry the current note that is used to iterate on it till reach the root
                /// to check on the failure links of the current node without losing it
                while(tempnode != root) /// will loop till reaching the root and check
                {/// if the failure link of the current note carry an id or not
                    if (tempnode ->fl->id != -1)
                    {
                        cout << tempnode->id;
                    }
                    tempnode = tempnode->fl;
                }
            }
            i++;
        }
        else
        {
            if (currnode == root && currnode->child[CharToInt[text[i]]] == NULL) /// if i reach the root node and i didn't find a match for the pattern
            {/// in the text , loop on the text and and the node of the pattern in the trie will remain the same
                i++;
            }
            else currnode = currnode->fl;
        }
    }
}

void DeleteTrie(Node* node)
{/// function move on each node by node and get it's failure link by calling get failure link function

    for(int i  = 0; i < 4; i++)
    {
        if (node->child[i]) DeleteTrie(node->child[i]);
    }
    delete node;


}

void DeleteTrie()
{
    DeleteTrie(root);
}

int main() {

    text = "GAACAAGTGAAGTGAGAAGAAGT";
    //patt[patt_num][max_patt_size] = {"AGA","AA","AAG","GAAG","TCG"};
    InsertInTrie();
    AhoCoSearch();
    return 0;
}
