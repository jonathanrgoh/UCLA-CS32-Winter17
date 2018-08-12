/*

How an object is destroyed:
---------------------------
1) Execute the body in the function
2) Destroy each data member (If not explicitly written, the default destructor follows as below)
	- Built-in type, do nothing
	- Class type, call its destructor

3) (FOR THE FUTURE)




Class vs. Struct:
-----------------

Class x
{
	<--------- default private
};

Class x
{
	<--------- default public
};




Initialization is not the same as assignment


String s1;			//Initialization (using the default constructor)
String s2("Hello");	//Initialization (using the constructor that takes a const char*)
String s3(s2);		//Initialization (using the copy constructor)

String s4 = s3;		//Initialization (using the copy constructor)
String s5 = "Hello";//Initialization (using the constructor) [effectively]

s1=s2;				//Assignment

*/





class String
{
public:
	String(const char* value = "");
	String(const String& other); //Copy Constructor! called when a copy is made
	????? operator=(const String& rhs);
	~String();
	
private:
	char* m_text;
	int m_len;
};

????? String::operator=(const String& rhs)
{
	delete [] m_text;
	m_len = rhs.m_len;
	m_text = new char[m_len+1];
	strcpy(m_text, rhs.m_text);
	
}


String::String(const String& other)
{
	//m_len = other.m_len;
	//m_text = new char[m_len+1];
	//strcpy(m_text, other.m_text);
	
	m_len = other.size;
	m_text = new char[m_len+1];
	for(int k=0; k!=m_len; k++)
		m_text[k] = other.charAt(k);
	m_text[m_len] = '\0';
}

String::String(const char* value = "")
{
	if (value==nullptr)
	{
		value = "";
	}
	m_len = strlen(value);
	m_text = new char[m_len+1];
	strcpy(m_text, value);
	int i = 17;
	int j = i * 29;
}

String::~String()
{
	delete [] m_text;
}


void f(String t)
{
	String u("Wow");
	
	u=t; // u.operator=(t);
}

void g()
{
	String s("Hello");
	f(s);
}

char* somefunc();

int main()
{
	String x(somefunc());
	String y;
	g();
}



====================================

Employee:: ~Employee()
{
	delete [] name.????;
}

struct Employee
{
	string name;
	double salary;
	int age;
};


