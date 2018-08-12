#include <iostream>
#include <string>
using namespace std;

//Your declarations and implementations would go here

class Investment
{
public:
    Investment(string name)
        :m_name(name)
    {
        
    }
    
    virtual ~Investment()
    {
        
    }
    
    virtual bool fungible() const
    {
        return false;
    }
    
    virtual string description() const = 0;
    
    virtual int purchasePrice() const = 0;
    
    string name() const
    {
        return m_name;
    }
    
private:
    string m_name;
};

///

class Painting: public Investment
{
public:
    Painting(string name, int value)
        :Investment(name), m_value(value)
    {
    }
    
    virtual bool fungible() const
    {
        return false;
    }
    
    virtual ~Painting()
    {
        cout << "Destroying " << name() << ", a painting" << endl;
    }
    
    virtual string description() const
    {
        return "painting";
    }
    
    virtual int purchasePrice() const
    {
        return m_value;
    }
    
private:
    int m_value;
};

///

class Stock: public Investment
{
public:
    Stock(string name, int value, string ticker)
        :Investment(name), m_value(value), m_ticker(ticker)
    {
    }
    
    virtual bool fungible() const
    {
        return true;
    }
    
    virtual ~Stock()
    {
        cout << "Destroying " << name() << ", a stock holding" << endl;
    }
    
    virtual string description() const
    {
        string s = "stock trading as ";
        s+=m_ticker;
        return s;
    }
    
    virtual int purchasePrice() const
    {
        return m_value;
    }
    
private:
    int m_value;
    string m_ticker;
};

///

class House: public Investment
{
public:
    House(string name, int value)
        :Investment(name), m_value(value)
    {
        
    }
    
    virtual bool fungible() const
    {
        return false;
    }
    
    virtual ~House()
    {
        cout<<"Destroying the house " << name() << endl;
    }
    
    virtual string description() const
    {
        return "house";
    }
    
    virtual int purchasePrice() const
    {
        return m_value;
    }
    
private:
    int m_value;
};

///




void display(const Investment* inv)
{
    cout << inv->name();
    if (inv->fungible())
        cout << " (fungible)";
    cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
}

int main()
{
    Investment* portfolio[4];
    portfolio[0] = new Painting("Salvator Mundi", 450300000);
    // Stock holdings have a name, value, and ticker symbol
    portfolio[1] = new Stock("Alphabet", 100000, "GOOGL");
    portfolio[2] = new Stock("Symantec", 50000, "SYMC");
    portfolio[3] = new House("4 Privet Drive", 660000);
    
    for (int k = 0; k < 4; k++)
        display(portfolio[k]);
    
    // Clean up the investments before exiting
    cout << "Cleaning up" << endl;
    for (int k = 0; k < 4; k++)
        delete portfolio[k];
}

/*
Output produced:

Salvator Mundi: painting bought for $450300000
Alphabet (fungible): stock trading as GOOGL bought for $100000
Symantec (fungible): stock trading as SYMC bought for $50000
4 Privet Drive: house bought for $660000
Cleaning up
Destroying Salvator Mundi, a painting
Destroying Alphabet, a stock holding
Destroying Symantec, a stock holding
Destroying the house 4 Privet Drive
*/
