#include "provided.h"
#include "MyHash.h"
#include <string>
#include <list>
#include <iostream>
#include <fstream>
using namespace std;

class WordListImpl
{
public:
    WordListImpl();
    ~WordListImpl();
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currtrans) const;
    
private:
    MyHash<string, list<string>>* m_wList;
    string patterns(string s) const;
};

WordListImpl::WordListImpl()
{
    m_wList = new MyHash<string, list<string>>;
}

WordListImpl::~WordListImpl()
{
    delete m_wList;
}

string WordListImpl::patterns(string s) const
{
    string pattern = "";
    MyHash<char, char> tempPatternMap;
    int counter = 0;
    for (int i = 0; i < s.size(); i++)
    {
        s[i] = toupper(s[i]);
        if (!isalpha(s[i]))
        {
            tempPatternMap.associate(s[i], s[i]);
        }
        else if (tempPatternMap.find(s[i]) == nullptr)
        {
            tempPatternMap.associate(s[i], 65 + counter);
            counter++;
        }
    }
    
    for (int i = 0; i < s.size(); i++)
    {
        pattern += *tempPatternMap.find(s[i]);
    }
    return pattern;
}

bool WordListImpl::loadWordList(string filename)
{
    m_wList->reset();
    ifstream infile(filename);    // infile is a name of our choosing
    if (!infile)                // Did opening the file fail?
    {
        return false;
    }
    
    while (infile)
    {
        string input;
        infile >> input;
        //cout << input << endl;
        //puts all letters in input to lower case
        for (int i = 0; i < input.size(); i++)
            input[i] = tolower(input[i]);
        
        string pattern = patterns(input);
        
        if (m_wList->find(pattern) == nullptr)
        {
            list<string> l;
            l.push_back(input);
            m_wList->associate(pattern, l);
        }
        else
        {
            m_wList->find(pattern)->push_back(input);
        }
        
    }
    return true;
}

bool WordListImpl::contains(string word) const
{
    for (int i = 0; i < word.size(); i++)
    {
        word[i] = tolower(word[i]);
    }
    //cout << patterns(word) << endl;
    const list<string>* p = m_wList->find(patterns(word));
    list<string>::const_iterator it;
    if (p != nullptr)
        it = p->begin();
    else
        return false;
    
    while (it != p->end())
    {
        if ((*it) == word)
        {
            return true;
        }
        it++;
    }
    return false;
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currtrans) const
{
    vector<string> candidates;
    if (cipherWord.size() != currtrans.size())
    {
        return candidates;
    }
    
    //check parameters
    for (int i = 0; i < cipherWord.size(); i++)
    {
        //cipherword
        if (!isalpha(cipherWord[i]) && cipherWord[i] != '\'')
            return candidates;
        
        //currtrans
        if (!isalpha(currtrans[i]) && currtrans[i] != '\?' && currtrans[i] != '\'')
            return candidates;
    }
    
    list<string> l;
    if (m_wList->find(patterns(cipherWord)) != nullptr)
        l = *m_wList->find(patterns(cipherWord));
    else
        return candidates;
    
    list<string>::iterator it = l.begin();
    while (it != l.end())
    {
        bool erasedSomething = false;
        //loop through the letters of the currtrans, cipherword and the selected word in the list
        for (int i = 0; i < currtrans.size(); i++)
        {
            char ctLetter = tolower(currtrans[i]);
            char cipherLetter = tolower(cipherWord[i]);
            if (isalpha(ctLetter))
            {
                if (!isalpha(cipherLetter))
                {
                    candidates.clear();
                    return candidates;
                }
                else if (ctLetter != (*it)[i])
                {
                    erasedSomething = true;
                    it = l.erase(it);
                    break;
                }
            }
            else if (ctLetter == '\?')
            {
                if (!isalpha(cipherLetter))
                {
                    candidates.clear();
                    return candidates;
                }
                else if (!isalpha((*it)[i]))
                {
                    erasedSomething = true;
                    it = l.erase(it);
                    break;
                }
            }
            else if (ctLetter == '\'')
            {
                if (cipherLetter != '\'')
                {
                    candidates.clear();
                    return candidates;
                }
                else if ((*it)[i] != '\'')
                {
                    erasedSomething = true;
                    it = l.erase(it);
                    break;
                }
            }
        }
        if (!erasedSomething)
        {
            candidates.push_back(*it);
            it++;
        }
    }
    
    
    return candidates;
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currtrans) const
{
    return m_impl->findCandidates(cipherWord, currtrans);
}
