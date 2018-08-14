


////////////////////////////////////////////////////////////////////////////
// Executive.cpp - Provides the entry point for execution                 //
// ver 1.0                                                                //
// Language:    C++, Visual Studio 2017                                  //
// Prasanna Dodwad, CSE687 - Object Oriented Design, Spring 2018          //
///////////////////////////////////////////////////////////////////////////

/*

Class DbProvider : helps to share the Database between functions

Required Files:
* ---------------
* Test.h, Test.cpp
*
* Maintenance History:
* --------------------
* ver 1.0 : 6 Feb 2018




*/




#include<iostream>
#include "../Test/Test.h"
#include "../DbCore/DbCore.h"
#include <fstream>
#include <vector>
#include "../Test/PayloadStr.h"
#include<string>


using namespace NoSqlDb;



class DbProviderSecond
{
public:
	DbCore<PayloadStr>& db() { return db_; }

private:
	static DbCore<PayloadStr> db_;
};

DbCore<PayloadStr> DbProviderSecond::db_;


int main() {

	Test t;
    DbCore<PayloadStr> db;
	DbProviderSecond dbp;
	dbp.db() = db;

	DbElement<PayloadStr> demoElem;

	demoElem.name("Parag");
	demoElem.descrip("Student for CSE687");
	demoElem.dateTime(DateTime::makeTime(2018,6,23,0,0,0));
	

	db["Taneja"] = demoElem;
	demoElem.name("Himank");
	db["Sharma"] = demoElem;
	dbp.db() = db;
	

	t.SetDBinTest(db);
	dbp.db() = t.ExecuteTest();

	std::cout << "\n\n";
	std::getchar();
	return 0;
}
