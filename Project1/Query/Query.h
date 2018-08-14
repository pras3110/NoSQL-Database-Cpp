#pragma once



////////////////////////////////////////////////////////////////////////////
// Query.h - Implements Query and Condtion classes for Database queries   //
// ver 1.0                                                                //
// Language:    C++, Visual Studio 2017                                  //
// Prasanna Dodwad, CSE687 - Object Oriented Design, Spring 2018          //
///////////////////////////////////////////////////////////////////////////


/*
Package Operations:
* -------------------
* This package provides 3 classes:
* 
   - DbProvider3 : Class used to share Database between Cascading queries

       

  

   - Query : Template Class used to perform queries on database

   Public Functions :
     
	 queryunion() :  Used to set the flag true for OR query
	 queryand() : Used to set the flag false for AND query

	 void PrintChildren(const std::string & key) :  Query to Select children of a particular key
	 void ValueofAKey(const std::string & key)  : Query to select the value of a particular key
	 void Datetime(Condition<T> c)  :               Query to select keys based on Datatime 
	 void PrintRegexpkey(std::string exp)  :     Query to select key based on a regular expression

	 

	 Query& selectop(Condition<T> c)  :   Query for cascading AND , OR queries
	 Query& selectpayload(Condition<T> c)  : Query for Payload
	 void show() :                          Shows the Database Keys
	 void ShowDbProvider()                  Shows the Query returned Database
	 void ShowDbKeys()                      Shows the database keys
	 void handle_name(const DbCore<T>& database,Condition<T> c)  :   Handler function for name attribute in selectop function
	 void handle_descrip(const DbCore<T>& database, Condition<T> c) :  Handler function for description attribute in selectop function

	 - Condition : Template Class used to set the query condition 
	        
			       Its public functions are just the getter and setter functions for each attribute
	 

   


* Required Files:
* ---------------
* DbCore.h, DbCore.cpp
  PayloadStr.h
  
* 
*
* Maintenance History:
* --------------------
* ver 1.0 : 6th Feb 2018

*/




#include "../DbCore/DbCore.h"
#include "../Test/PayloadStr.h"
#include <iostream>
#include<string>
#include<vector>
#include<regex>
#include <algorithm>


using namespace NoSqlDb;



// DbProvider3 : Class used to share Database between Cascading queries

class DbProvider3
{
public:
	DbCore<PayloadStr>& db() { return db_; }

private:
	static DbCore<PayloadStr> db_;
};

DbCore<PayloadStr> DbProvider3::db_;



// Template Class used to set the query condition 
template <typename T>
class Condition {

private:
	std::string Key;
	std::string Name;
	std::string Description;
	std::string sdate;
	std::string edate;
	T Payload;

public:

	// Sets the name attribute 
	 Condition& name(const std::string& s) {
		Name = s;
		return *this;

	}
	 // sets the key attribute
	 Condition& key(const std::string& s) {
		Key = s;
		return *this;

	}
	 // sets the description attribute
	Condition& description(const std::string& s) {
		Description = s;
		return *this;

	}

	// sets the payload attribute
	Condition<T>& payload(const T& payload_);

	// sets the start date attribute
	Condition& date_start(const std::string& start_date) {
		sdate = start_date;
		return *this;
	}


	// sets the end date attribute
	Condition& date_end(const std::string& end_date) {
		edate = end_date;
		return *this;
	}


	// returns the name attribute

	const std::string& getName() {

		return Name;
	}

	// returns the key attribute
	 std::string& getKey() {

		return Key;
	}

	 // returns the description attribute
	std::string& getDescription() {

		return Description;
	}

	// returns the start date attribute
	std::string& getstartdate() {

		return sdate;
	}

	// returns the end date attribute
	std::string& getenddate() {

		return edate;
	}

	// returns the Payload attribute
	T& getpayLoad() { return Payload; }

};




// Template Class used to perform queries on database

template <typename T>
class Query {

private:
	DbCore<T> Querydb;
	std::vector<std::string> Keys;
	bool union_;
	bool start;
	

public:
	
	void PrintChildren(const std::string & key);
	void ValueofAKey(const std::string & key);
	void Datetime(Condition<T> c);
	void PrintRegexpkey(std::string exp);
	Query(const DbCore<T>& db) {
		
		DbCore<T> tempdb;
		 Querydb = db;
		DbProvider3 dbp;
		dbp.db()=tempdb;
		 union_ = true;
		 start = true;
       }

	// Used to set the flag true for OR query
	Query& queryunion() { 
		 union_ = true;
		 return *this;
	 }

	// Used to set the flag false for AND query
	 Query& queryand() {
		 union_ = false;
		 return *this;
	 }

	Query& selectop(Condition<T> c);
	Query& selectpayload(Condition<T> c);
	void show();
	void ShowDbProvider();
	void ShowDbKeys();
	void handle_name(const DbCore<T>& database,Condition<T> c);
	void handle_descrip(const DbCore<T>& database, Condition<T> c);
};







//  Query to Select children of a particular key
template<typename T>
inline void Query<T>::PrintChildren(const std::string & key)
{
	// logic to print the Children of a particular key
	std::vector<std::string> vec = Querydb[key].children();
	std::cout << "\n\n The Children of the key "<< key<<" are" << std::endl;
	for (auto key : vec) {
		std::cout << key << std::endl;
	}

}


// Query to select the value of a particular key

template<typename T>
inline void Query<T>::ValueofAKey(const std::string & key)
{
	
	showElem(Querydb[key]);
}


// Query to select keys based on Datatime 
template<typename T>
inline void Query<T>::Datetime(Condition<T> c)
{
	DateTime start(c.getstartdate());
	
	int count = 0;
	
	if (c.getenddate() == "") {
		
		count = 0;
	}
	else {
		
		count = 1;
	}



	if (count == 0) {

		DateTime end(DateTime().now());
		typename DbCore<T>::DbStore map = Querydb.dbStore();
		std::cout << "\n\n";
		for (auto key : map) {
			if (key.second.dateTime() > start && key.second.dateTime() <= end) {

				std::cout << key.first << std::endl;
			}
		}
		

	}
	else {
		DateTime end(c.getenddate());

		typename DbCore<T>::DbStore map = Querydb.dbStore();
		std::cout << "\n\n";
		for (auto key : map) {
			if (key.second.dateTime() > start && key.second.dateTime() < end) {

				std::cout << key.first << std::endl;
			}
		}

	}
	

}

// Query to select key based on a regular expression
template<typename T>
inline void Query<T>::PrintRegexpkey(std::string exp)
{
	
	std::regex b(exp);

	std::vector<std::string> keys = Querydb.keys();
	std::cout << "Regular exp matcching" << std::endl;
	for (auto x : keys) {
		if (std::regex_match(x, b)) {
			std::cout << x << std::endl;
		}
	}
}



// Query for cascading AND , OR queries
template<typename T>
inline Query<T>& Query<T>::selectop(Condition<T> c) {
	DbProvider3 dbp;
	DbCore<T> db_P = dbp.db();

	DbCore<T> Dbcommon;

	
	if (union_ == true) {
		Dbcommon = Querydb;
     }
	else
	{
		Dbcommon = dbp.db();
	}


	if (c.getKey() != "") {
		std::regex b(c.getKey());

			for (auto entry : Dbcommon.dbStore()) {

				if (std::regex_match(entry.first, b)) {
					db_P[entry.first] = entry.second;

				}
			}
	}

		if (c.getName() != "") {
			handle_name(Dbcommon,c);
			db_P = dbp.db();
		}

		if (c.getDescription() != "") {
			handle_descrip(Dbcommon, c);
			db_P = dbp.db();
		}
	
	dbp.db() = db_P;

	return *this;

}




// Query to select based on the payload
template<typename T>
inline Query<T> & Query<T>::selectpayload(Condition<T> c)
{

	return *this;
	// TODO: insert return statement here
}

// Template specialized to select payload where payload is of type PayloadStr
template<>
inline Query<PayloadStr>& Query<PayloadStr>::selectpayload(Condition<PayloadStr> c) {

	DbCore<PayloadStr> tempdb;
	//std::cout << c.getpayLoad().getpath() << std::endl;
	std::vector<std::string> vec = c.getpayLoad().getcategory();
	for (auto x : vec) {

		for (auto y : Querydb.dbStore()) {

			std::vector<std::string>::iterator it;
			it = std::find(y.second.payLoad().getcategory().begin(),y.second.payLoad().getcategory().end(), x);
			if (it != y.second.payLoad().getcategory().end()) {
			//	std::cout << x << " is present in the db row..!" << std::endl;
				tempdb[y.first] = y.second;
				
			}
			else {
				//std::cout << x << " is not present...." << std::endl;
			}
		}
	}
	showDb(tempdb);

	return *this;
}





// Display the DBelement of the Query Database
template<typename T>
inline void Query<T>::show()
{
	for (auto x : Keys) {
		std::cout << "\n -------------------------------------------------------------------------" << std::endl;
		showElem(Querydb[x]);
	}
}

// Display the Database after query is finished
template<typename T>
inline void Query<T>::ShowDbProvider() {
	DbProvider3 dbp;
	
	showDb(dbp.db());

}


// Displays the keys of the query database
template<typename T>
inline void Query<T>::ShowDbKeys()
{
	DbProvider3 dbp;
	DbCore<T> db = dbp.db();
	typename DbCore<T>::Keys key = db.keys();
	std::cout << "\n\nThe keys are : " << std::endl;
	std::cout << "----------------------" << std::endl;
	for (auto x : key) {

		std::cout << x << std::endl;
	}
	

}

// Handler function of selectop , which handles the name attribute selection
template<typename T>
inline void Query<T>::handle_name(const DbCore<T>& database, Condition<T> c)
{
	DbProvider3 dbp;
	DbCore<T> db_P = dbp.db();
	DbCore<T> tempdb = database;

	for (auto entry : tempdb.dbStore()) {
		std::regex b(c.getName());

		if (std::regex_match(entry.second.name(), b)) {
			if (!db_P.contains(entry.first))
			{
				db_P[entry.first] = entry.second;
				
			}
		}
		else
		{
			if (union_ == false && db_P.contains(entry.first)) {

				db_P.dbStore().erase(entry.first);
			}
		}
	}

	dbp.db() = db_P;

}

// Handler function of selectop, which handles the description attribute selection
template<typename T>
inline void Query<T>::handle_descrip(const DbCore<T>& database, Condition<T> c)
{
	DbProvider3 dbp;
	DbCore<T> db_P = dbp.db();
	DbCore<T> tempdb = database;

	for (auto entry : tempdb.dbStore()) {
		std::regex b(c.getDescription());

		if (std::regex_match(entry.second.descrip(), b)) {

			if (!db_P.contains(entry.first))
			{
				db_P[entry.first] = entry.second;
			}
		}
		else {

			if (union_ == false && db_P.contains(entry.first)) {

				db_P.dbStore().erase(entry.first);
			}

		}
	}

	dbp.db() = db_P;
}

// Returns the Payload member from Condtion Class
template<typename T>
inline Condition<T>& Condition<T>::payload(const T & payload_)
{
	Payload = payload_;
	return *this;
	// TODO: insert return statement here
}
