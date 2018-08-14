#pragma once

////////////////////////////////////////////////////////////////////////////
// Test.h - Provides the Package to run test cases                       //
// ver 1.0                                                                //
// Language:    C++, Visual Studio 2017                                  //
// Prasanna Dodwad, CSE687 - Object Oriented Design, Spring 2018          //
///////////////////////////////////////////////////////////////////////////

/*
Package Operations:
* -------------------
* This package consists of Test Class

  The public functions are :
    
	 ExecuteTest() : Runs a set of test cases
	 SetDBinTest() : Sets the Database for the Test Class , so that test functions can use Database for queries
* -

* Required Files:
* ---------------
* DbCore.h, DbCore.cpp
* Query.h, Query.cpp
  Persistance.h, Persistance.cpp
  PayloadStr.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 6 Feb 2018






*/


#include "../DbCore/DbCore.h"
#include "../Test/PayloadStr.h"


using namespace NoSqlDb;





class Test {
public:

	DbCore<PayloadStr> ExecuteTest();
	void SetDBinTest(DbCore<PayloadStr>);
};





