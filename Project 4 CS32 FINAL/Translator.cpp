#include "provided.h"
#include <string>
#include <iostream>
#include <cctype>
#include <unordered_map>
using namespace std;

class TranslatorImpl
{
public:
    TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslationlation(const string& ciphertext) const;
    
private:
    
    unordered_map<char, char> m_currentMappings;
    vector<unordered_map<char, char>> m_charMappings;
    int m_top=0;
};

TranslatorImpl::TranslatorImpl()
{
    unordered_map<char, char> temp;
    
    for (int j = 0; j < 26; j++)
    {
        temp.insert(pair<char, char>(65 + j, '\?'));
    }
    
    m_charMappings.push_back(temp);
    m_currentMappings = m_charMappings[m_top];
    m_top++;
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    if (ciphertext.size() != plaintext.size())
    {
        return false;
    }
    
    unordered_map<char, char> temp;
    temp = m_charMappings[m_top - 1];
    

    for (int i=0; i<ciphertext.size(); i++)
    {
        if (!isalpha(ciphertext[i]) || !isalpha(plaintext[i]))
        {
            return false;
        }
        
        if (temp[toupper(ciphertext[i])] != '\?' && temp[toupper(ciphertext[i])] != toupper(plaintext[i]))
        {
            return false;
        }
        
        else if(temp[toupper(ciphertext[i])] == '\?' || temp[toupper(ciphertext[i])] == toupper(plaintext[i]))
        {
            temp[toupper(ciphertext[i])] = toupper(plaintext[i]);
        }
    }
    

    
    for (char c=65; c<91; c++)
    {
        char plaintextLetter1 = temp[c];
        for (char j = c; j < 91; j++)
        {
            char plaintextLetter2 = temp[j];
            if (plaintextLetter1 == plaintextLetter2 && c != j && plaintextLetter1 != '\?' && plaintextLetter2 != '\?')
            {
                //value is repeated
                return false;
            }
        }
    }
    
    
    m_charMappings.push_back(temp);
    m_currentMappings = m_charMappings.back();
    m_top++;
    return true;
}

bool TranslatorImpl::popMapping()
{
    if (m_charMappings.size() <= 1)
        return false;
    else
    {
        m_charMappings.pop_back();
        m_top--;
        m_currentMappings = m_charMappings.back();
        //test: print out values of latest map
        /*for (char c = 'A'; c <= 'Z'; c++)
         {
         cout << c << " " << m_currentMappings[c] << endl;
         }
         */
        return true;
    }
}

string TranslatorImpl::getTranslationlation(const string& ciphertext) const
{
    string translation = "";
    for (int i=0; i<ciphertext.size(); i++)
    {
        if (isalpha(ciphertext[i]))
        {
            char cipher=toupper(ciphertext[i]);
            unordered_map<char,char>::const_iterator it = m_currentMappings.find(cipher);

            if (get<1>(*it) == '\?')
            {
                translation += "?";
            }
            
            else
            {
                if (isupper(ciphertext[i]))
                {
                    translation += toupper(get<1>(*it));
                }
                
                else
                {
                    translation += tolower(get<1>(*it));
                }
            }
        }
        else
        {
            translation += ciphertext[i];
        }
    }
    return translation;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslationlation(ciphertext);
}
