void h()
{
	String s("Hello");
	...
}

int main()
{
	String t;
	for(...)
		h();
	
}

===================================================================
===============================================================



class String
{
public:
	String(const char* value);
	~String();
	void cleanup();
private:
	// Class invariant:
	// m_text points to a dynamically allocated array of m_len+1 chars
	// m_len >=0
	// m_text[m_len] == '\0'
	char* m_text;
	int m_len;
};

String::String(const char* value)
{
	m_len = strlen(value);
	m_text = new chare[m_len+1];
	strcpy(m_text, value);
}

String::String()
{
	m_len = strlen("");
	m_text = new char[m_len+1];
	strcpy(m_text, "")
		
	// m_text[0] = '\0';
}

void String::~String()
{
	delete [] m_text;
}

int main()
{
	String x("Wow!");
	...verify x is Wow!...
	char buffer[1000];
	cin.getline(buffer,1000);
	
	String s (buffer);
	cin.getline(buffer,1000);
}
