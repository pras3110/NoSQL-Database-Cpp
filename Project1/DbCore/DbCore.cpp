/////////////////////////////////////////////////////////////////////
// DbCore.cpp - Implements NoSql database prototype                //
// ver 1.0                                                         //
// Prasanna Dodwad, CSE687 - Object Oriented Design, Spring 2018   //
// Source : Jim Fawcett                                            //
/////////////////////////////////////////////////////////////////////

#include "DbCore.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/TestUtilities/TestUtilities.h"
#include <iostream>
#include <iomanip>
#include <functional>



using namespace NoSqlDb;

//----< reduce the number of characters to type >----------------------

auto putLine = [](size_t n=1, std::ostream& out = std::cout)
{
  Utilities::putline(n, out);
};

///////////////////////////////////////////////////////////////////////
// DbProvider class
// - provides mechanism to share a test database between test functions
//   without explicitly passing as a function argument.

class DbProvider
{
public:
  DbCore<std::string>& db() { return db_; }
  
private:
  static DbCore<std::string> db_;
};

DbCore<std::string> DbProvider::db_;

///////////////////////////////////////////////////////////////////////
// test functions

//----< demo requirement #1 >------------------------------------------




bool dbcoret1()
{
	Utilities::title("Demonstrating Requirement #1");
	std::cout << "\n  " << typeid(std::function<bool()>).name()
		<< ", declared in this function, "
		<< "\n  is only valid for C++11 and later versions.";
	putLine();

	Utilities::title("Demonstrating Requirement #2");
	std::cout << "\n  A visual examination of all the submitted code "
		<< "will show only\n  use of streams and operators new and delete.";
	putLine();

	Utilities::title("Demonstrating Requirement #3a - creating DbElement");
	std::cout << "\n  Creating a db element with key \"Fawcett\":";
	DbCore<std::string> db;
	DbProvider dbp;
	db = dbp.db();
	DbElement<std::string> demoElem;
	demoElem.name("Jim");
	demoElem.descrip("Instructor for CSE687");
	demoElem.dateTime(DateTime().now());
	demoElem.payLoad("hello........");
	if (demoElem.name() != "Jim")
		return false;
	if (demoElem.descrip() != "Instructor for CSE687")
		return false;
	if (demoElem.dateTime().now() != DateTime().now())
		return false;
	showHeader();
	showElem(demoElem);
	db["Fawcett"] = demoElem;
	showDb(db);
	dbp.db() = db;
	putLine();

	return true; // would not compile unless C++11
}


bool dbcoret2() {

	
		Utilities::title("Demonstrating Requirement #3b - creating DbCore");
		DbProvider dbp;
		DbCore<std::string> db = dbp.db();
		DbElement<std::string> demoElem = db["Fawcett"];
		demoElem.name("Ammar");
		demoElem.descrip("TA for CSE687");
		demoElem.dateTime(DateTime::makeTime(2017, 4, 5, 0, 0, 0));
		
		db["Salman"] = demoElem;
		if (!db.contains("Salman"))
			return false;
		demoElem.name("Jianan");
		demoElem.dateTime(DateTime::makeTime(2017, 6, 23, 0, 0, 0));
		db["Sun"] = demoElem;
		demoElem.name("Nikhil");
		db["Prashar"] = demoElem;
		demoElem.name("Pranjul");
		db["Arora"] = demoElem;
		demoElem.name("Akash");
		db["Anjanappa"] = demoElem;
		std::cout << "\n  after adding elements with keys: ";
		DbCore<std::string>::Keys keys = db.keys();
		showKeys(db);
		putLine();
		std::cout << "\n  make all the new elements children of element with key \"Fawcett\"";
		db["Fawcett"].children().push_back("Salman");
		db["Fawcett"].children().push_back("Sun");
		db["Fawcett"].children().push_back("Prashar");
		db["Fawcett"].children().push_back("Arora");
		db["Fawcett"].children().push_back("Anjanappa");
		showHeader();
		showElem(db["Fawcett"]);
		db["Salman"].children().push_back("Sun");
		db["Salman"].children().push_back("Prashar");
		db["Salman"].children().push_back("Arora");
		db["Salman"].children().push_back("Anjanappa");
		putLine();
		std::cout << "\n  showing all the database elements:";
		dbp.db() = db;    // added to keep DB updated
		showDb(db);
		putLine();
		std::cout << "\n  database keys are: ";
		showKeys(db);
		putLine();
		return true;
	
}


bool dbcoret3() {

	Utilities::title("Demonstrating Requirement #4a - adding and deleting Key-Value Pairs");

	DbProvider dbp;
	DbCore<std::string> db = dbp.db();
	DbElement<std::string> demoElem;
	Utilities::title("\n Before Insertion Database : ");
	showDb(db);

	demoElem.name("Prasanna");
	demoElem.descrip("Student for CSE687");
	demoElem.dateTime(DateTime().now());
	//demoElem.payLoad().payload_string("OOD is Tough ...");
	Utilities::title("\n\nInserting new DBElement with key \"Dodwad\" with name \"Prasanna \" into Database ");


	if (db.contains("Dodwad")) {
		std::cout << "\n\nKEY PRESENT....so updating data" << std::endl;
	}
	else {
		std::cout << "\n\nKEY NOT PRESENT....so inserting data into DB" << std::endl;

		db["Dodwad"] = demoElem;

	}





	std::cout << "\n  showing all the database elements:";
	showDb(db);

	Utilities::title("\n\n Deleting DBElement with key \"Dodwad\" with name \"Prasanna \" from Database ");
	Utilities::title("\n Before Deletion Database : ");
	showDb(db);


	db.dbStore().erase("Dodwad");
	Utilities::title("\n After Deletion Database : ");
	showDb(db);
	std::cout << "\n\n" << std::endl;
	dbp.db() = db;
	return true;

}


bool dbcoret4() {

	 


		

		DbProvider dbp;
		DbCore<std::string> db = dbp.db();

		

		showDb(db);
		Utilities::title("\n Removing child \"Arora \" key from Database:");

		Utilities::title("\n Before Removing child Database:");

		showDb(db);

		db.RemoveChild("Arora");

		Utilities::title("\n After Removing child Database:");
		showDb(db);
		std::cout << "\n\n" << std::endl;
		dbp.db() = db;
		return true;
	


}


//----< test stub >----------------------------------------------------

#ifdef TEST_DBCORE

using namespace Utilities;

int main()
{
  Utilities::Title("Testing DbCore - He said, she said database");
  putLine();

  TestExecutive ex;

  // define test structures with test function and message

  TestExecutive::TestStr ts1{ dbcoret1, "Use C++11" };
  TestExecutive::TestStr ts2{ dbcoret2, "Use streams and new and delete" };
  TestExecutive::TestStr ts3a{ dbcoret3, "Creating Db Core" };
  TestExecutive::TestStr ts4a{ dbcoret4, "Adding deleting key-value pairs" };

  


  // register test structures with TestExecutive instance, ex

  ex.registerTest(ts1);
  ex.registerTest(ts2);
  ex.registerTest(ts3a);
  ex.registerTest(ts4a);

 

  // run tests

  bool result = ex.doTests();
  if (result == true)
    std::cout << "\n  all tests passed";
  else
    std::cout << "\n  at least one test failed";

  putLine(2);
  std::getchar();
  return 0;
}
#endif


