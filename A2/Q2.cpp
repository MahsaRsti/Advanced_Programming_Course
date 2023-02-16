#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool determine_interleaving(string word1, string word2, string interleaved_word)
{
    if(word1=="" && word2=="" && interleaved_word=="")
        return true;
    else
    {
        if(word1[0]==interleaved_word[0])
            return determine_interleaving(word1.substr(1),
                                          word2,interleaved_word.substr(1));
        else if(word2[0]==interleaved_word[0])
            return determine_interleaving(word1,
                                          word2.substr(1),interleaved_word.substr(1));
        else
            return false;
    }
}

int main()
{
    string word_1;
    string word_2;
    string interleaved_word;

    cin >>word_1 >>word_2 >>interleaved_word;

    if (determine_interleaving(word_1,word_2,interleaved_word))
        cout <<"Interleaving"<<'\n';
    else
         cout <<"Not Interleaving"<<'\n';
    return 0;
}