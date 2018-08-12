//interface (“what”) vs. implementation (“how”)


#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

const double PI = 4 * atan(1.0);

class Circle
{
	public:
		Circle(double x, double y, double r);
		bool scale(double factor);
		void draw();
		double radius();
			//class invariant
			//*m_r > 0* or m_r >= 0
	private:
		double m_x;
		double m_y;
		double m_r;
};

double area(Circle x);

int main()
{
	Circle blah(6, -5, 3);
	Circle c(2, 5, 10);
	c.scale(2);
    
    int f;
    cin >> f;
    if(! c.scale)
    {
        ...
    }
    
	c.draw();
	cout << area(c);
	cout << 2 * 3.14159 * m_r; 
	
}

double area(Circle x)
{
	return 3.14159 * x.radius() * x.radius();
}

Circle::Circle(double x, double y, double r)
//member initialization list. Initializes first
: m_x(x), m_y(y), m_r(r)
{
	if ( r <= 0)
	{
		cout << "Cannot create a circle with radius " << r << endl;
		exit(1);
	}

	/*
	m_x = x;
	m_y = y;
	m_r = r;
	*/
}

bool Circle::scale(double factor)
{
	if ( factor <= 0)
	{
		false;
	}
	m_r *= factor;
	return true;
}

double Circle::radius()
{
    return m_r;
}

double area(Circle x)
{
    return PI * x.radius() * x.radius();
}