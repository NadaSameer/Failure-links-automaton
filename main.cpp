#include <iostream>
#include <cstring>
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////

int text_size = 23;
int pattern_size = 7;

char* text = new char[text_size];
char* patterntxt  = new char[pattern_size];

//char text [] = "AGAGAAGAGGAGAAGAGAAGAGA";
//char patterntxt [] = "AGAAGAG";
//int pattern_size = strlen(patterntxt);
//int text_size = strlen(text);


struct Pattern
{
    int Id; /// node index
    char p; /// character of small string
    int fl; /// failure link
};

Pattern* pattern = new Pattern[pattern_size+1];

void ProcessFLA()
{/// function build in it the pattern and get the failure links of each suffix

    pattern[0].Id = 0;
    pattern[0].p = 'n'; /// index of first character node is null
    pattern[0].fl = -1; /// the failure link of the node zero
    pattern[1].fl = 0; /// failure link of the first node (character) alwyas point to zero


    for(int i = 1, j = 0; i <= pattern_size; i++, j++) /// build the pattern without failure links first
    {
        pattern[i].Id = i;
        pattern[i].p = patterntxt[j];
    }

    for (int i = 0; i < pattern_size; i++) /// to get all failure links of all prefixes
    {
        char* prefix = new char[pattern_size];
        int prefix_size = 0;
        for(int j = 0; j <= i+1; j++) ///construct the prefix
        {
            prefix[j] = pattern[j+1].p;
            prefix_size++;
        }

        for (int k = 1; k < prefix_size; k++) /// get failure link of each prefix
        {
            int failure_index = 0; ///index to get the failure link of prefix
            int comp = 0; /// used to get back to first element in prefix in each iteration
            int c = k; /// point to the longest proper suffix
            while(comp < prefix_size-k) /// loop on each proper suffix
            {
                if(prefix[c] == prefix[comp]) {failure_index++;}
                else {break;}
                comp++; c++;
            }
            if (comp == 0) pattern[prefix_size].fl = 0; /// if no match with any character point to the node zero
            else if(comp >= prefix_size - k) /// when comp exceed the size of prefeix - k , means there's match with the proper suffix and prefix
            {/// thus the failure link equals the number we reached after finishing the while loop
                pattern[prefix_size].fl = failure_index;
                break;
            }
        }
    }
    /*for(int i = 0; i <= pattern_size; i++)
    {
        cout << pattern[i].Id << " ";
    }
    cout << endl;
    for(int i = 0; i <= pattern_size; i++)
    {
        cout << pattern[i].p << " ";
    }
    cout << endl;
    for(int i = 0; i <= pattern_size; i++)
    {
        cout << pattern[i].fl << " ";
    }
    cout << endl;*/
}

void KMPSearch()
{/// in this function we search on a small string in large string
/// loop on both character stings till it match and print where it matched
    ProcessFLA();
    int i = 0; /// txt iterator
    int j = 0; /// pattern iterator

    while(i < text_size)/// loop till the end of the text size and get all places where the the pattern matches
    {
        if(text[i] == patterntxt[j])
        {
            i++; j++;
            if(j == pattern_size) /// when j is equal to the pattern size that means all characters in pattern
            {///matched with part in the text
                int rep = i - j;
                cout << "(t" << i << " , " << "p" << j << ")" << " , ";
                cout  << "Rep(" << rep << ")" <<endl;
                j = pattern[j].fl; /// back to the fl of the last node 'character' in the pattern
            }
        }
        else if (text[i] != patterntxt[j])
        {
            if (j == 0) i++; /// if not match and it points at the beginning of the pattern and can't fall back
            else j = pattern[j].fl;
        }
    }
}

int main() {

    text = "AGAGAAGAGGAGAAGAGAAGAGA";
    text_size = strlen(text);
    patterntxt = "AGAAGAG";

    for (int i = 0; i < pattern_size; i++)
    {
        pattern[i].p = patterntxt[i];
    }

    KMPSearch();
    //ProcessFLA(patterntxt);
    delete[] pattern;

    return 0;
}
