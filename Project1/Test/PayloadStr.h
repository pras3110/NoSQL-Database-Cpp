#pragma once


////////////////////////////////////////////////////////////////////////////
// PayloadStr.h - Provides the Structure for Payload                      //
// ver 1.0                                                                //
// Language:    C++, Visual Studio 2017                                  //
// Prasanna Dodwad, CSE687 - Object Oriented Design, Spring 2018          //
///////////////////////////////////////////////////////////////////////////




/*

Package Operations:
* -------------------
* This package provides 1 class:


  PayloadStr : Class which defines the structure for the Payload portion of the DbElement

  Public functions are :

   getpath() : Returns the file path string
   getcategory() : Returns the vector of string category 
   setpath () : Sets the value for the path attribute of Payload
   setcategory() : Sets the value for the Category attribute of Payload


* Required Files:
* ---------------
* 
*
* Maintenance History:
* --------------------
* ver 1.0 : 6th Feb 2018













*/

#include<string>
#include<vector>
#include<iostream>
class PayloadStr {


private:
	std::string path;
	std::vector<std::string> category;

public:

	std::string& getpath() { return path; }
	std::string getpath() const { return path; };
	void setpath(const std::string& path_) { path = path_; }

	std::vector<std::string>& getcategory() { return category; };
	std::vector<std::string> getcategory() const { return category; };
	void setcategory(const std::vector<std::string>& category_) { category = category_; };

};

inline std::ostream & operator<<(std::ostream & out, const PayloadStr & p)
{
	out << p.getpath();
	std::vector<std::string> vec = p.getcategory();

	for (auto x : vec) {

		out << ";" << x;
	}
	return out;
	// TODO: insert return statement here
}