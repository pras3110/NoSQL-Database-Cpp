
/////////////////////////////////////////////////////////////////////
// Query.cpp -   Test stub for Query package                       //
// ver 1.0                                                         //
// Language:    C++, Visual Studio 2017                            //
// Prasanna Dodwad, CSE687 - Object Oriented Design, Spring 2018   //
/////////////////////////////////////////////////////////////////////




#include "Query.h"
#include <iostream>

using namespace NoSqlDb;


#ifdef TEST_QUERY



int main() {

	Condition<PayloadStr> c;
	c.description("(Liv)().*");
	
	
	
	DbCore<PayloadStr> db;
	DbElement<PayloadStr> demoelem;
	demoelem.name("Swapnil");
	demoelem.descrip("Lives in Syracuse");
	demoelem.dateTime(DateTime().now());
	demoelem.payLoad().setpath("437 Clarendon");

	db["Borse"] = demoelem;

	demoelem.name("Omkar");
	demoelem.descrip("Table Tennis Champion");
	demoelem.dateTime(DateTime().now());
	demoelem.payLoad().setpath("Westcott");
	db["Chogle"] = demoelem;
	std::cout << "Query Database is :\n\n";
	showDb(db);

	Query<PayloadStr> q(db);
	std::cout << "\n\nThe condtion is on description = (Liv.*)" << std::endl;
	std::cout << "\n The Database after the query is executed is : \n\n" << std::endl;
	q.selectop(c).ShowDbProvider();
	
	std::getchar();
	return 0;
}

#endif 


