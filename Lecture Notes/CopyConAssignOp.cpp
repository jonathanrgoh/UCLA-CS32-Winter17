#include <iostream>
#include <string>
using namespace std;

class Car
{
public:
    Car(int numModels);
    Car(const Car &other);
    //Copy
    Car& operator= (const Car& src);
    //Assignment Operator
    ~Car();
    
    void addModel(string model);
    void printModels();
    
    
private:
    int m_numModels;
    string modelType;
    string* contents;
};

Car::Car(int numModels)
:m_numModels(numModels)
{
    
    contents = new string[m_numModels];
}

Car::Car(const Car &other)
{
    m_numModels=other.m_numModels;
    contents=new string[other.m_numModels];
    for (int i=0; i<other.m_numModels; i++)
    {
        contents[i]=other.contents[i];
    }
}

Car& Car::operator=(const Car &src)
{
    if (&src == this)
        return(*this); // do nothing
    
    m_numModels=src.m_numModels;
    delete [] contents;
    contents=new string[src.m_numModels];
    for (int i=0; i<src.m_numModels; i++)
    {
        contents[i]=src.contents[i];
    }
    return*this;
}

Car::~Car()
{
    delete [] contents;
}

void Car::addModel(string model)
{
    for(int i=0; i<m_numModels; i++)
    {
        if(contents[i]=="")
        {
            contents[i]=model;
            return;
        }
        
    }
}

void Car::printModels()
{
    for(int i=0; i<m_numModels; i++)
    {
            cout<<contents[i]<<endl;
    }
}

int main()
{
    string modelType;
    Car porsche(5);
    
    cout<<"Enter model type:: ";
    cin>>modelType;
    porsche.addModel(modelType);
    
    cout<<"Enter model type:: ";
    cin>>modelType;
    porsche.addModel(modelType);
    
    porsche.printModels();
    //Assignment
    Car toyota(5);
    Car honda(10);
    toyota=honda;
    
    //Copy Constructor
    Car ferrari(111);
    Car lamborghini(333);
    Car maserati=ferrari;
    Car jaguar(lamborghini);
    
    return 0;
}













