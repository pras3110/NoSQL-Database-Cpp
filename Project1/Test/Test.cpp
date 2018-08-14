

///////////////////////////////////////////////////////////////////////////////////
// Test.cpp - Provides the Package to run test cases and define test functions   //
// ver 1.0                                                                       //
// Language:    C++, Visual Studio 2017                                          //
// Prasanna Dodwad, CSE687 - Object Oriented Design, Spring 2018                 //
///////////////////////////////////////////////////////////////////////////////////



#include "Test.h"
#include "../DbCore/DbCore.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/TestUtilities/TestUtilities.h"
#include "../Query/Query.h"
#include "../Persistance/Persistance.h"
#include "../Test/PayloadStr.h"
#include <iostream>
#include <iomanip>
#include <functional>
#include <filesystem>
#include <stdlib.h>

using namespace NoSqlDb;
namespace fs = std::experimental::filesystem;


//----< reduce the number of characters to type >----------------------

auto putLine = [](size_t n = 1, std::ostream& out = std::cout)
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
	DbCore<PayloadStr>& db() { return db_; }

private:
	static DbCore<PayloadStr> db_;
};

DbCore<PayloadStr> DbProvider::db_;

///////////////////////////////////////////////////////////////////////
// test functions

//----< demo requirement #1 >------------------------------------------

bool testR1()
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
	DbCore<PayloadStr> db;
	DbProvider dbp;
	db = dbp.db();
	DbElement<PayloadStr> demoElem;
	demoElem.name("Jim");
	demoElem.descrip("Instructor for CSE687");
	demoElem.dateTime(DateTime().now());
	demoElem.payLoad().setpath("CST-001");
	demoElem.payLoad().getcategory().push_back("OOD");
	demoElem.payLoad().getcategory().push_back("SMA");
	demoElem.payLoad().getcategory().push_back("DP");
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

//----< demo requirement #2 >------------------------------------------

bool testR2()
{
	Utilities::title("Demonstrating Requirement #2");
	std::cout << "\n  A visual examination of all the submitted code "
		<< "will show only\n  use of streams and operators new and delete.";
	putLine();
	return true;
}

//----< demo first part of requirement #3 >----------------------------

bool testR3a()
{
	Utilities::title("Demonstrating Requirement #3a - creating DbElement");
	std::cout << "\n  Creating a db element with key \"Fawcett\":";

	// create database to hold std::string payload

	DbCore<PayloadStr> db;
	DbProvider dbp;
	db = dbp.db();

	// create some demo elements and insert into db

	DbElement<PayloadStr> demoElem;

	demoElem.name("Jim");
	demoElem.descrip("Instructor for CSE687");
	demoElem.dateTime(DateTime().now());
	demoElem.payLoad().setpath("CST-001");
	demoElem.payLoad().getcategory().push_back("OOD");
	demoElem.payLoad().getcategory().push_back("SMA");
	demoElem.payLoad().getcategory().push_back("DP");

	//demoElem.payLoad("The good news is ...");

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
	return true;
}
//----< demo second part of requirement #3 >---------------------------

bool testR3b()
{
	Utilities::title("Demonstrating Requirement #3b - creating DbCore");
	DbProvider dbp;
	DbCore<PayloadStr> db = dbp.db();
	DbElement<PayloadStr> demoElem = db["Fawcett"];
	demoElem.name("Ammar");
	demoElem.descrip("TA for CSE687");
	demoElem.dateTime(DateTime::makeTime(2017,4,5,0,0,0));
	demoElem.payLoad().setpath("CST-401");
	demoElem.payLoad().getcategory().clear();
	demoElem.payLoad().getcategory().push_back("OOD");
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


bool test4a() {

	Utilities::title("Demonstrating Requirement #4a - adding and deleting Key-Value Pairs");

	DbProvider dbp;
	DbCore<PayloadStr> db = dbp.db();
	DbElement<PayloadStr> demoElem;
	Utilities::title("\n Before Insertion Database : ");
	showDb(db);

	demoElem.name("Prasanna");
	demoElem.descrip("Student for CSE687");
	demoElem.dateTime(DateTime().now());
	
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

	Utilities::title("\n\n Deleting DBElement with key \"Sharma\" with name \"Himank \" from Database ");
	Utilities::title("\n Before Deletion Database : ");
	showDb(db);


	db.dbStore().erase("Sharma");
	Utilities::title("\n After Deletion Database : ");
	showDb(db);
	std::cout << "\n\n" << std::endl;
	dbp.db() = db;
	return true;

}

bool test5a() {

	Utilities::title("Demonstrating Requirement #5 - Editing metadata , Replacing existing value instance with new instance");

	DbProvider dbp;
	DbCore<PayloadStr> db = dbp.db();
	
	Utilities::title("\nBefore editing metadata Database :");
	showDb(db);
	if (db.contains("Dodwad")) {

		Utilities::title("\n\nChanging description of key \" Dodwad\" to \"Completed Project1 \" ");
		
		
		db["Dodwad"].descrip("Completed Project1");

	}
	Utilities::title("\nAfter editing metadata Database :");
	showDb(db);

	Utilities::title("\nBefore replacing key \"Dodwad \" with new instance database :");
	showDb(db);
	Utilities::title("\nNew instance has name \" Anmol\" and description \"Lives in Hubli \" :");


	DbElement<PayloadStr> demoElem;
	demoElem.name("Anmol");
	demoElem.descrip("Lives in Hubli");
	demoElem.dateTime(DateTime().now());
	db["Dodwad"] = demoElem;

	Utilities::title("\nAfter replacing key \"Dodwad \" with new instance :");
	showDb(db);
	std::cout << "\n\n" << std::endl;
	

	
	dbp.db() = db;


	return true;
}



bool removechild() {


	Utilities::title("Demonstrating Requirement #5 - Adding and Removing Child Relationships");

	DbProvider dbp;
	DbCore<PayloadStr> db = dbp.db();

	Utilities::title("\nAdding Key \"Dodwad \" as Child of key \"Fawcett \" ");
	Utilities::title("\n Before adding child key Database:");
	
	showDb(db);
	db["Fawcett"].children().push_back("Dodwad");

	Utilities::title("\n After adding child key Database:");


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



bool Test6a() {
	Utilities::title("Demonstrating Requirement #6a - Value of a specified key");
	Utilities::title("Query Database :");
	DbProvider dbp;
	showDb(dbp.db());
	Utilities::title("\n\nQuery : Return the value of the key \"Salman \"");
	Query<PayloadStr> q(dbp.db());
	q.ValueofAKey("Salman");
	std::cout << "\n\n" << std::endl;
	Utilities::title("Demonstrating Requirement #6b - Children of a specified key");
	Utilities::title("Query Database :");
	showDb(dbp.db());
	Utilities::title("\n\nQuery : Return the value of the key \"Fawcett\"");
	q.PrintChildren("Fawcett");
	std::cout << "\n\n" << std::endl;
	Utilities::title("Demonstrating Requirement #6c - Return set of keys matching Regular Expression");
	Utilities::title("Query Database :");
	showDb(dbp.db());
	Utilities::title("\n\n Query : Return keys where description is strings ending with 687 (.*687)  :");
	Condition<PayloadStr> c;
	c.description(".*687");
	q.selectop(c).ShowDbKeys();
	std::cout << "\n\n" << std::endl;
	Utilities::title("Demonstrating Requirement #6d - Return set of keys matching Regular Expression");
	Utilities::title("\nQuery Database :");
	showDb(dbp.db());
	Utilities::title("\n\n Query : Return keys where description is (TA.*)  :");
	Condition<PayloadStr> c2;
	c2.description("(TA)(.*)");
	q.selectop(c2).ShowDbKeys();
	std::cout << "\n\n" << std::endl;
    return true;
}

bool Test6b() {
	Utilities::title("Demonstrating Requirement #6b - Children of a specified key");
	Utilities::title("Query Database :");
	

	DbProvider dbp;
	showDb(dbp.db());

	Utilities::title("\n\nQuery : Return the value of the key \"Fawcett\"");

	Query<PayloadStr> q(dbp.db());

	q.PrintChildren("Fawcett");
	std::cout << "\n\n" << std::endl;



	return true;
}

bool Test6c() {

	Utilities::title("Demonstrating Requirement #6c - Return set of keys matching Regular Expression");
	Utilities::title("Query Database :");

	DbProvider dbp;
	showDb(dbp.db());
	Query<PayloadStr> q(dbp.db());
	
	Utilities::title("\n\n Query : Return keys where description is strings ending with 687 (.*687)  :");
	Condition<PayloadStr> c;
	c.description(".*687");
	q.selectop(c).ShowDbKeys();
	std::cout << "\n\n" << std::endl;

	return true;
}

bool Test6d() {
	Utilities::title("Demonstrating Requirement #6d - Return set of keys matching Regular Expression");
	Utilities::title("\nQuery Database :");

	DbProvider dbp;
	showDb(dbp.db());
	Query<PayloadStr> q(dbp.db());
	
	Utilities::title("\n\n Query : Return keys where description is (TA.*)  :");
	Condition<PayloadStr> c;
	c.description("(TA)(.*)");
	q.selectop(c).ShowDbKeys();
	std::cout << "\n\n" << std::endl;

	return true;
}

bool Test6e() {

	Utilities::title("Demonstrating Requirement #6e - Query on Datetime , where endtime is specified");
	Utilities::title("Query Database :");

	DbProvider dbp;
	showDb(dbp.db());
	Utilities::title("Query : Start date is \" 2015:Apr:3rd:9hrs:7mins:6secs\"");

	Utilities::title("\nQuery : End date is \" 2018:Jan:9th:9hrs:7mins:6secs\"");
	Condition<PayloadStr> c;
	DateTime start(DateTime::makeTime(2015, 4, 3, 9, 7, 6));
	c.date_start(start.time());
	DateTime end(DateTime::makeTime(2018, 1, 3, 9, 7, 6));
	c.date_end(end.time());
	
	Query<PayloadStr> q(dbp.db());
	Utilities::title("\n The keys are :");
	q.Datetime(c);
	std::cout << "\n\n" << std::endl;


	Utilities::title("Demonstrating Requirement #6e - Query on Datetime , where endtime is not specified");
	Utilities::title("Query Database :");

	//DbProvider dbp;
	showDb(dbp.db());
	Utilities::title("Query : Start date is \" 2015:Apr:3rd:9hrs:7mins:6secs\"");


	Condition<PayloadStr> c2;
	DateTime start2(DateTime::makeTime(2015, 4, 3, 9, 7, 6));
	c2.date_start(start2.time());

	c2.date_end("");

	//Query<PayloadStr> q(dbp.db());
	Utilities::title("\n The keys are :");
	q.Datetime(c2);

	std::cout << "\n\n" << std::endl;

	return true;

}

bool Test6ea() {

	Utilities::title("Demonstrating Requirement #6e - Query on Datetime , where endtime is not specified");
	Utilities::title("Query Database :");

	DbProvider dbp;
	showDb(dbp.db());
	Utilities::title("Query : Start date is \" 2015:Apr:3rd:9hrs:7mins:6secs\"");

	
	Condition<PayloadStr> c2;
	DateTime start(DateTime::makeTime(2015, 4, 3, 9, 7, 6));
	c2.date_start(start.time());
	
	c2.date_end("");

	Query<PayloadStr> q(dbp.db());
	Utilities::title("\n The keys are :");
	q.Datetime(c2);

	std::cout << "\n\n" << std::endl;
	return true;
}

bool Test7a() {

	Utilities::title("Demonstrating Requirement #7 - AND-ing of two queries");
	Utilities::title("Query Database :");
	DbProvider dbp;
	showDb(dbp.db());
	Query<PayloadStr> q(dbp.db());
	Utilities::title("\n\nQuery : Select where name = \"Nikhil\" AND description = (TA.*)");
	Condition<PayloadStr> c;
	c.description("(TA)(.*)");

	Condition<PayloadStr> c3;
	Utilities::title("\n\nThe Database after query is :");
	c3.name("Nikhil");
	q.selectop(c).queryand().selectop(c3).ShowDbProvider();
	std::cout << "\n\n" << std::endl;


	Utilities::title("Demonstrating Requirement #7 - OR-ing of two queries");
	Utilities::title("Query Database :");
	//DbProvider dbp;
	showDb(dbp.db());
	Query<PayloadStr> q2(dbp.db());
	Utilities::title("\n\nQuery : Select where name = \"Jim\" OR description= (TA.*)");
	Condition<PayloadStr> c2;
	c2.name("Jim");

	Condition<PayloadStr> c4;
	Utilities::title("\n\nThe Database after query is :");
	c4.description("(TA)(.*)");
	q2.selectop(c2).queryunion().selectop(c4).ShowDbProvider();
	std::cout << "\n\n" << std::endl;

	return true;
}

bool Test7b() {

	Utilities::title("Demonstrating Requirement #7 - OR-ing of two queries");
	Utilities::title("Query Database :");
	DbProvider dbp;
	showDb(dbp.db());
	Query<PayloadStr> q(dbp.db());
	Utilities::title("\n\nQuery : Select where name = \"Jim\" AND description = (TA.*)");
	Condition<PayloadStr> c2;
	c2.description("(TA)(.*)");

	Condition<PayloadStr> c4;
	Utilities::title("\n\nThe Database after query is :");
	c4.name("Jim");
	q.selectop(c2).queryunion().selectop(c4).ShowDbProvider();
	std::cout << "\n\n" << std::endl;
	return true;



	return true;
}

bool TestSavedbtoXML() {
	Utilities::title("Demonstrating Requirement #8 - Writing Database to XML file");
	Utilities::title("Query Database :");
	Persistance<PayloadStr> p;
	DbProvider dbp;
	showDb(dbp.db());
	
	Utilities::title("The XML structure for this database is :");
	p.CreateXML(dbp.db(),"TestDBpras.xml");

	std::cout << "\n\n" << std::endl;

	Utilities::title("Demonstrating Requirement #8 - Augment Database");
	Persistance<PayloadStr> p2;
	p2.AugmentXML(dbp.db());
	std::cout << "\n\n" << std::endl;

	Utilities::title("Demonstrating Requirement #6 - Query on Payload Category");
	
	Utilities::title(" Condition Payload Categories : (1) SMA (2) OOD");
	Utilities::title("Query Database :");
	showDb(dbp.db());
	Utilities::title("\n\n Query : Select rows , where Payload category of DB matches with atleast one Condition payload categories ");
	Condition<PayloadStr> c4;
	PayloadStr p4;
	p4.getcategory().push_back("SMA");
	p4.getcategory().push_back("OOD");
	c4.payload(p4);
	Query<PayloadStr> q(dbp.db());
	q.selectpayload(c4);
	std::cout << "\n\n" << std::endl;
	Utilities::title("Demonstrating Requirement # 10- Have created atleast the 4 packages 1) Executive 2) DBCore 3) Query 4)Test\n\n");
	Utilities::title("Demonstrating Requirement # 11- Project Structure and Dependency Relationships");
	Utilities::title("\n\n Name specifies Packages , and Children specify the Dependencies\n\n");
	Persistance<PayloadStr> p10;
	DbCore<PayloadStr> db45 = p10.ReadXML("ProjectStructure.xml");

	return true;
}

bool testAugment() {
	Utilities::title("Demonstrating Requirement #8 - Augment Database");
	Persistance<PayloadStr> p2;
	
	DbProvider dbp;
	p2.AugmentXML(dbp.db());
	std::cout << "\n\n" << std::endl;
	return true;
}

bool testPayload() {
	Utilities::title("Demonstrating Requirement #6 - Query on Payload Category");
	DbProvider dbp;
	Utilities::title(" Condition Payload Categories : (1) SMA (2) OOD");
	Utilities::title("Query Database :");
	showDb(dbp.db());
	Utilities::title("\n\n Query : Select rows , where Payload category of DB matches with atleast one Condition payload categories ");
	Condition<PayloadStr> c4;
	PayloadStr p4;
	p4.getcategory().push_back("SMA");
	p4.getcategory().push_back("OOD");
	c4.payload(p4);
	Query<PayloadStr> q(dbp.db());
	q.selectpayload(c4);
	std::cout << "\n\n" << std::endl;
	return true;
}

bool test11() {

	Utilities::title("Demonstrating Requirement # 11- Project Structure and Dependency Relationships");
	Persistance<PayloadStr> p10;
	DbCore<PayloadStr> db45=p10.ReadXML("ProjectStructure.xml");
	//showDb(db);
	return true;
}











//----< test stub >----------------------------------------------------




using namespace Utilities;

DbCore<PayloadStr> Test::ExecuteTest()
{
	
	Utilities::Title("Testing DbCore - He said, she said database");
	putLine();

	TestExecutive ex;
	DbProvider dbp;
	TestExecutive::TestStr ts1{ testR1, "Use C++11" };
	TestExecutive::TestStr ts3b{ testR3b, "Create DbCore<std::string>" };
	TestExecutive::TestStr ts4a{ test4a, "Addition and deletion of key-value pairs" };
	TestExecutive::TestStr ts5a{ test5a, "Editing Metadata and Replace instance" };
	TestExecutive::TestStr remove{ removechild, "removing child" };
	TestExecutive::TestStr ts6a{ Test6a, "Value of a key" };
	TestExecutive::TestStr ts6e{ Test6e, "Datetime query " };
	TestExecutive::TestStr ts7a{ Test7a, "AND of queries" };
	TestExecutive::TestStr tssavexml{ TestSavedbtoXML, "Saving Database to XML" };
	ex.registerTest(ts1);
	ex.registerTest(ts3b);
	ex.registerTest(ts4a);
	ex.registerTest(ts5a);
	ex.registerTest(remove);
	ex.registerTest(ts6a);
	ex.registerTest(ts6e);
	ex.registerTest(ts7a);
	ex.registerTest(tssavexml);
	bool result = ex.doTests();
	if (result == true)
		std::cout << "\n  all tests passed";
	else
		std::cout << "\n  at least one test failed";

	putLine(2);
	return dbp.db();
}



void Test::SetDBinTest(DbCore<PayloadStr> db)
{
	
	DbProvider dbp;
	dbp.db() = db;
	showDb(db);
}




