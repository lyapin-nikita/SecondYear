/////// MAIN FUNCTION FOR TESTING
// 
// 
// 
// 

#include "stack.h"
#include <iostream>
using namespace std;



int main(void)
{
	//manual testing of stack

	TStack test1(4);
	cout << test1.isEmpty() << "\n";
	cout << test1.isFull() << "\n\n\n";


	test1.put(5);
	test1.put(10);
	test1.put(12);
	test1.put(15);
	test1.showStack();
	cout << "\n\n\n";

	test1.put(4);
	test1.put(11);
	test1.showStack();
	cout << "\n\n\n";

	cout << test1.get() << endl;
	cout << test1.get() << endl;
	cout << "\n";
	test1.showStack();

}