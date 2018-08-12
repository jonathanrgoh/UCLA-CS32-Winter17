#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class DecrypterImpl
{
public:
    DecrypterImpl();
    ~DecrypterImpl();
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
    
private:
    Translator* m_translator;
    Tokenizer* m_tokenizer;
    WordList* m_wList;
};

DecrypterImpl::DecrypterImpl()
{
    m_translator=new Translator();
    m_tokenizer=new Tokenizer(" ,;:.!()[]{}-\"#$%^&");
    m_wList=new WordList();
}

DecrypterImpl::~DecrypterImpl()
{
    delete m_tokenizer;
    delete m_wList;
    delete m_translator;
}

bool DecrypterImpl::load(string filename)
{
    return m_wList->loadWordList(filename);
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    return vector<string>();  // This compiles, but may not be correct
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
    return m_impl->crack(ciphertext);
}

