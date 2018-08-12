//
//  eval.cpp
//  eval
//
//  Created by Jonathan Goh on 2/6/18.
//  Copyright © 2018 Jonathan Goh. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include "Map.h"
#include <cctype>
#include <cassert>
using namespace std;

int evaluate(string infix, const Map& values, string& postfix, int& result);
bool isValidInfix(string infix);
bool allOperandsInMap(string infix, const Map& values);
bool isGreaterOrEqual(char c, char other);
string convertExpression(string infix);

//int evaluate(string infix, const Map& values, string& postfix, int& result);
//// Evaluates an integer arithmetic expression
////   If infix is a syntactically valid infix integer expression whose
////   only operands are single lower case letters (whether or not they
////   appear in the values map), then postfix is set to the postfix
////   form of the expression; otherwise postfix may or may not be
////   changed, result is unchanged, and the function returns 1.  If
////   infix is syntactically valid but contains at least one lower
////   case letter operand that does not appear in the values map, then
////   result is unchanged and the function returns 2.  If infix is
////   syntactically valid and all its lower case operand letters
////   appear in the values map, then if evaluating the expression
////   (using for each letter in the expression the value in the map
////   that corresponds to it) attempts to divide by zero, then result
////   is unchanged and the function returns 3; otherwise, result is
////   set to the value of the expression and the function returns 0.

//Functions
bool isValidInfix(string infix)
{
    string empty = "";
    char previous;
    char next;
    
    string empty2="";
    char previous2;
    char next2;
    
    int letterC=0;
    int operatorC=0;
    char character = ' ';
    int rightC=0;
    int leftC=0;
    
    if (infix.size()==0)
    {
        return false;
    }
    
    if (infix.size() == 1 && isalpha(infix[0]) && islower(infix[0]))
    {
        return true;
    }
    
    for (int i=0; i<infix.size(); i++)
    {
        character = infix[i];
        if (!isalpha(character) && character!='(' && character!=')' && character!='+' && character!='-' && character!='*' && character!='/' && character!=' ')
        {
            return false;
        }
        
        if (isalpha(character) && !islower(character))
        {
            return false;
        }
        
        
        if (character=='(')
        {
            rightC++;
        }
        
        if (character==')')
        {
            leftC++;
        }
        
        if (character == '+' || character == '-' || character == '*' || character == '/')
        {
            operatorC++;
        }
        
        if (isalpha(character))
        {
            letterC++;
        }
    }
    
    if (rightC!=leftC)
    {
        return false;
    }
    
    if (letterC-operatorC != 1)
    {
        return false;
    }
    
    if (rightC>=1 && leftC>=1 && letterC==0)
    {
        return false;
    }
    
    for (int i=0; i<infix.size(); i++)
    {
        char c = infix[i];
        
        if (isalpha(c) || c=='+' || c=='-' || c=='*' || c=='/')
        {
            empty+=c;
        }
    }
    
    if (empty.size()==0)
    {
        return false;
    }
    
    for (int i = 0; i < empty.size() - 1; i++)
    {
        previous = empty[i];
        next = empty[i + 1];
        if (isalpha(previous) && isalpha(next))
        {
            return false;
        }
        
        if (!isalpha(previous) && !isalpha(next))
        {
            return false;
        }
    }
    
    if (!isalpha(empty[0]) && character != '(')
    {
        return false;
    }
    
    if (!isalpha(empty[empty.size() - 1]) && character != ')')
    {
        return false;
    }
    
    for (int i = 0; i < infix.size(); i++)
    {
        char c = infix[i];
        
        if (isalpha(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
        {
            empty2 += c;
        }
    }
    
    for (int i = 0; i < empty2.size() - 1; i++)
    {
        previous2 = empty2[i];
        next2 = empty2[i + 1];
        if (previous2=='(' && next2==')')
        {
            return false;
        }
    }
    
    return true;
}

bool allOperandsInMap(string infix, const Map& values)
{
    for (int i=0; i<infix.size(); i++)
    {
        char c=infix[i];
        
        if (isalpha(c) && !values.contains(c))
        {
            return false;
        }
    }
    
    return true;
}

bool isGreaterOrEqual(char c, char other)
{
    if ((c == '*' || c == '/') && (other == '+' || other == '-'))
        return false;
    return true;
}

string convertExpression(string infix)
{
    string postFix = "";
    stack<char> postStack;
    
    for (int i = 0; i < infix.size(); i++)
    {
        char c = infix[i];
        
        if (isalpha(c))
        {
            postFix += c;
            continue;
        }
        
        if (c == ' ')
        {
            continue;
        }
        
        //checking cases
        if (c=='(')
        {
            postStack.push(c);
        }
        
        else if(c=='+' || c=='-' || c=='*' || c=='/')
        {
            while (!postStack.empty() && postStack.top() != '(' && isGreaterOrEqual(c, postStack.top()))
            {
                postFix += postStack.top();
                postStack.pop();
            }
            
            postStack.push(c);
        }
        
        else if (c==')')
        {
            while (!postStack.empty() && postStack.top() != '(')
            {
                postFix += postStack.top();
                postStack.pop();
            }
            postStack.pop();
        }
    }
    
    while (!postStack.empty())
    {
        postFix += postStack.top();
        postStack.pop();
    }
    
    return postFix;
}


//evaluate implementation
int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    if (!isValidInfix(infix))
    {
        return 1;
    }
    
    postfix = convertExpression(infix);
    
    if (!allOperandsInMap(infix, values))
    {
        return 2;
    }
    
    stack<int> valStack;
    int answer=0;
    
    for (int i=0; i<postfix.size(); i++)
    {
        char c=postfix[i];
        
        if(isalpha(c))
        {
            int temp = 0;
            values.get(c, temp);
            valStack.push(temp);
        }
        
        else
        {
            int v2 = valStack.top();
            valStack.pop();
            int v1 = valStack.top();
            valStack.pop();
            
            switch(c)
            {
                case '+':
                    answer = v1 + v2;
                    break;
                    
                case '-':
                    answer = v1 - v2;
                    break;
                    
                case '*':
                    answer = v1*v2;
                    break;
                    
                case '/':
                    if (v2 == 0)
                    {
                        return 3;
                    }
                    
                    answer = v1 / v2;
                    break;
            }
            
            valStack.push(answer);
        }
    }
    result=valStack.top();
    
    return 0;
}

//int main()
//{
//    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
//    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
//    Map m;
//    for (int k = 0; vars[k] != '#'; k++)
//        m.insert(vars[k], vals[k]);
//    string pf;
//    int answer;
//    assert(evaluate("a+ e", m, pf, answer) == 0  &&
//           pf == "ae+"  &&  answer == -6);
//    answer = 999;
//    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
//    // unary operators not allowed:
//    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
//    assert(evaluate("a*b", m, pf, answer) == 2  &&
//           pf == "ab*"  &&  answer == 999);
//    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
//           pf == "yoau-*+"  &&  answer == -1);
//    answer = 999;
//    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
//           pf == "oyy-/"  &&  answer == 999);
//    assert(evaluate(" a  ", m, pf, answer) == 0  &&
//           pf == "a"  &&  answer == 3);
//    assert(evaluate("((a))", m, pf, answer) == 0  &&
//           pf == "a"  &&  answer == 3);
//    cout << "Passed all tests" << endl;
//}

