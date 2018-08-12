/*
NOTES::
=======

Inheritance


compile-time binding A.K.A. static binding

runtime binding A.K.A. dynamic binding

"strongly-typed language"



*/





class Shape
{
	void move(double xnew, double ynew);
	virtual void draw() const;
	double m_x;
	double m_y;
};

class Warning Signal : public Shape
{

};

class Circle : public Shape //syntax to denote that this is a type of shape
{
	//void move(double xnew, double ynew);	// not needed, bc circle inherits move function from shape
	virtual void draw() const; // overrides shape::draw
	double m_r;
};

class Rectangle : public Shape //syntax to denote that this is a type of shape
{
	//void move(double xnew, double ynew);
	virtual void draw() const; // overrides shape::draw
	virtual double diag() const;
	double m_dy;
	double m_dy;
};

Shape * pic[100];		//Heterogeneous collections
pic[0] = new Circle;
pic[1] = new Recatangle;
pic[2] = new Circle;
for(int k=0; k<...; k++)
 	pic[k]->draw(); // with static binding, always calls shape::draw

void f(Shape& c)
{
	c.move(10,20);
	c.draw(); // with static binding, always calls shape::draw
}

// void f(Rectangle& r)
// {
// 	c.move(10,20);
// 	c.draw();
// }


void Shape::move(double xnew, double ynew)
{
	m_x = xnew;
	m_y = ynew;
}

void Shape::draw() const
{
	
}

double Rectangle::diag() const
{
	return sqrt(m_dx*m_dx + m_dy*m_dy)
}





//====================

Circle c;
f(c);





