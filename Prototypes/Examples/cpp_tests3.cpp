#include <iostream> 
using namespace std;

#define TEST_VIRTUAL 1


#ifndef TEST_VIRTUAL  
class Shape {
protected:
	int width, height;
public:
	Shape( int a=0, int b=0)
	{
		width = a;
		height = b;
	}
	int area()
	{
		cout << "Parent class area :" ;
		return (width);
	}
};
#else

//Interface class
class IfShape{
	public:
	virtual int area()=0;
	virtual ~IfShape(){}
};

//Base class
class Shape: public IfShape {
protected:
	int width, height;
public:
	Shape(int a=0, int b=0)
	{
		width = a;
		height = b;
	}
	virtual int area()
	{
		cout << "Parent class area : " ;
		return (width);
	}
};
#endif

//Derived class
class Rectangle: public Shape{
public:
	Rectangle( int a=0, int b=0):Shape(a, b) { }
	int area ()
	{ 
		cout << "Rectangle class area : " ;
		return (width * height); 
	}
};

//Derived class
class Triangle: public Shape{
public:
	Triangle( int a=0, int b=0):Shape(a, b) { }
	int area ()
	{ 
		cout << "Triangle class area : " ;
		return (width * height / 2); 
	}
};


/******************************************************************************
 * Tests callers
 *****************************************************************************/
int test_virtualClasses()
{
#ifdef TEST_VIRTUAL

	cout << "Testing virtual classes" << endl;
	Shape *shape;
	Rectangle rec(10,7);
	Triangle  tri(10,5);
	Shape dummy(5, 0);

	// store the address of Rectangle
	shape = &rec;
	// call rectangle area.
	cout << shape->area()  << endl;

	// store the address of Triangle
	shape = &tri;
	// call triangle area.
	cout << shape->area() << endl;

	//base class
	cout << dummy.area() << endl;

	cout << "Ou seja, sempre que for utilizar polimorfismo, utilizar \n"; 
	cout << "virtual nas funções com sobrecarga. Assim o objeto pode \n" ;
	cout << "ser declarado como um ponteiro para a classe base, e ser \n";
	cout << "alocado dinamicamente. Mesmo o ponteiro apontando para a \n";
	cout << "classe base, como foi utilizado polimorfismo pela palavra \n";
	cout << "virtual, o método correto será chamado. \n";
	cout << endl;
	
#endif   
	return 0;
}
int test_interfaces()
{
	cout << "Testing interfaces" << endl;
	IfShape *shape =  NULL;


	cout << "Rectangle(2, 3)" << endl;
	shape = new Rectangle(2, 3);
	cout << shape->area() << endl;
	delete shape;

	cout << "Triangle(2, 3)" << endl;
	shape = new Triangle(2, 3);
	cout << shape->area() << endl;
	delete shape;

	cout << "Shape(2, 3)" << endl;
	shape = new Shape(2, 3);
	cout << shape->area() << endl;
	delete shape;


	
	return 0;
}

// Main function for the program
int main( )
{
	test_virtualClasses();
	test_interfaces();	

	return 0;
}


