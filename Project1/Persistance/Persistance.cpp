/////////////////////////////////////////////////////////////////////////////////////
// Persistance.cpp - Test Stud for Persistance package                            //
// ver 1.0                                                                         //
// Language:    C++, Visual Studio 2017                                           //
// Prasanna Dodwad, CSE687 - Object Oriented Design, Spring 2017                  //
////////////////////////////////////////////////////////////////////////////////////








#include "Persistance.h"
#include "../DbCore/DbCore.h"
#include<string>
#include "../Test/PayloadStr.h"
#include "../../XmlDocument/XmlParser/XmlParser.h"
#include "../../XmlDocument/XmlDocument/XmlDocument.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/TestUtilities/TestUtilities.h"
#include <fstream>
#include<iostream>


using namespace NoSqlDb;
using namespace XmlProcessing;
using namespace Utilities;


#ifdef TEST_PERSISTANCE

int main() {
	
	

	DbCore<PayloadStr> db;
	DbElement<PayloadStr> demoelem;
	demoelem.name("Swapnil");
	demoelem.descrip("Lives in Syracuse");
	demoelem.dateTime(DateTime().now());
	demoelem.payLoad().setpath("437 Clarendon");
	db["Borse"] = demoelem;
	
	Persistance<PayloadStr> p;
	p.CreateXML(db,"Hello.xml");
	Utilities::title("Storing database in Hello.xml file in Project 1 current folder");

	Utilities::title("The contents of db.xml are :\n\n");
	DbCore<PayloadStr> dbxml = p.ReadXML("db.xml");
	

	std::getchar();
	return 0;
}

#endif
