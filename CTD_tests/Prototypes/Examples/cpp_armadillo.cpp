#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{
	mat A = randu<mat>(4,5);
	mat B = randu<mat>(4,5);
	mat C = {1, 2, 3, 4, 5, 6};
	C = C.t();
	double d = 0.0;
	d = pow( double(A(0, 0)*B(0.0)), 2) ;

	mat D = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}};
	mat D1 = D.col(0);
	vec V1 = {1, 2, 3, 4, 5, 6};
	//mat V2 = D1.col(1);
	
  
	cout << A*B.t() << endl;
	cout << "A.size() = "  << A.size() << endl;
	cout << "d = " << d << endl;
	C.print("C = "); 
	
	D.print("D = ");
	D1.print("D0 = ");
	V1.print("V1 = ");
	//V2.print("V2 = ");

	V1 = 1.0 + V1;
	V1.print("V1 = ");
	V1 = log(V1);
	V1.print("V1 = ");

  return 0;
}


