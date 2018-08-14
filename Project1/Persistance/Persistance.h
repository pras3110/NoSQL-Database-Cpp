#pragma once


/*
/////////////////////////////////////////////////////////////////////////////////////
// Persistance.h - represents XML Creation, Reading and Augmentation operation     //
// ver 1.0                                                                         //
// Language:    C++, Visual Studio 2017                                           //
// Prasanna Dodwad, CSE687 - Object Oriented Design, Spring 2017                  //
////////////////////////////////////////////////////////////////////////////////////


/*
Package Operations: 
* -------------------
* This package provides 1 class:
*
   - Persistance : Template class to demonstrate XML operations 
     The member functions are :

	 1) CreateXML(DbCore<T> db,std::string filename) : Creates a new XML file , with Database content 'db' and 
	                                                   Filename 'filename'

	 2) ReadXML(std::string filename) : Reads the XML file 

	 3) WriteDBtoFile(std::string xml,std::string filename) :  Writes the xml string into file specified

	 4) handlerForReadXML(std::shared_ptr<AbstractXmlElement> x) : handler function for ReadXML

	 5) handlerforpayload(std::shared_ptr<AbstractXmlElement> y,DbElement<T>& demoElem) : handler function for payload


* Required Files:
* ---------------
* DbCore.h, DbCore.cpp
* XmlParser.h , XmlParser.cpp
* PayloadStr.h
* Maintenance History:
* --------------------
* ver 1.0 : 6th Feb 2018






*/



#include "../DbCore/DbCore.h"
#include<string>
#include "../Test/PayloadStr.h"
#include "../../XmlDocument/XmlParser/XmlParser.h"

#include "../../XmlDocument/XmlDocument/XmlDocument.h"
#include <fstream>
#include<iostream>

using namespace NoSqlDb;
using namespace XmlProcessing;


template <typename T>
class Persistance {

private:

public:
	void CreateXML(DbCore<T> db,std::string filename);
	DbCore<T> ReadXML(std::string filename);
	void WriteDBtoFile(std::string xml,std::string filename);
	void AugmentXML(DbCore<T>& db);

	DbElement<T> handlerForReadXML(std::shared_ptr<AbstractXmlElement> x);

	void handlerforpayload(std::shared_ptr<AbstractXmlElement> y,DbElement<T>& demoElem);

};

template<typename T>
inline void Persistance<T>::CreateXML(DbCore<T> db,std::string filename)
{
	typename DbCore<T>::DbStore map = db.dbStore();
	using sPtr = std::shared_ptr <AbstractXmlElement>;
	sPtr root = makeTaggedElement("DB");
	for (auto element : map) {
		sPtr dbstore = makeTaggedElement("DBStore");
		sPtr key = makeTaggedElement("key");
		sPtr name = makeTaggedElement("name");
		sPtr description = makeTaggedElement("description");
		sPtr datetime = makeTaggedElement("dtime");
		sPtr payload = makeTaggedElement("payload");
		sPtr payload_filepath = makeTaggedElement("filepath");
		sPtr payload_category = makeTaggedElement("category");
		sPtr children = makeTaggedElement("children");
		key->addChild(makeTextElement(element.first));
		name->addChild(makeTextElement(element.second.name()));
		description->addChild(makeTextElement(element.second.descrip()));
		datetime->addChild(makeTextElement(element.second.dateTime()));
		payload_filepath->addChild(makeTextElement(element.second.payLoad().getpath()));
		payload->addChild(payload_filepath);
		for (auto cate : element.second.payLoad().getcategory()) {
			sPtr payload_category_type = makeTaggedElement("categorytype");
			payload_category_type->addChild(makeTextElement(cate));
			payload_category->addChild(payload_category_type);

		}
		payload->addChild(payload_category);
		for (auto child : element.second.children()) {
			sPtr childkey = makeTaggedElement("childkey");
			childkey->addChild(makeTextElement(child));
			children->addChild(childkey);
		}
		dbstore->addChild(key);
		dbstore->addChild(name);
		dbstore->addChild(description);
		dbstore->addChild(datetime);
		dbstore->addChild(payload);
		dbstore->addChild(children);
		root->addChild(dbstore);
	}
	sPtr docEl = makeDocElement(root);
	//std::cout << "  " << docEl->toString();
	WriteDBtoFile(docEl->toString(),filename);
}




template<typename T>
inline DbCore<T> Persistance<T>::ReadXML(std::string filename)
{   
	std::string src = "../../"+filename;
	Utilities::title("Reading from file "+filename +" stored in \"OODProject1_PrasannaDodwad\" folder  \n ");
	XmlParser parser(src);
	std::cout << "\n" << src << "\n";
	XmlDocument* pDoc = parser.buildDocument();
	std::string keyname;
	using sptr = std::shared_ptr<AbstractXmlElement>;
	std::vector<sptr> vec = pDoc->elements("DB").select();
	DbCore<T> db;
	for (auto x : vec) {
		
		DbElement<T> d;
		

		d = handlerForReadXML(x);
		db[x->children()[0]->children()[0]->value()] = d;
	
	}
	showDb(db);
	return db;
}

template<typename T>
inline void Persistance<T>::WriteDBtoFile(std::string xml,std::string filename)
{
	std::fstream file;
	std::string xmltopline = "<?xml version=\"1.0\" encoding=\"utf - 8\"?>\n";
	xmltopline = xmltopline + xml;
	std::string filenamecontent = "../../"+filename;
	std::ofstream outfile(filenamecontent);
	outfile << xmltopline << std::endl;
	Utilities::title("Writing to file :"+filename+ " Stored in \"OODProject1_PrasannaDodwad\" folder\n ");

	outfile.close();
}

template<typename T>
inline void Persistance<T>::AugmentXML(DbCore<T>& db)
{
	DbCore<T> dbxml = ReadXML("db.xml");
	
	Utilities::title("Database which is read from XML is :");
	showDb(dbxml);

	Utilities::title("\nDatabase which is to be augmented to the XML is :");
	showDb(db);
	

	for (auto x : db.dbStore()) {

		if (dbxml.contains(x.first)) {

			// do nothing
		}
		else {

			dbxml[x.first] = x.second;
		}

	}

	Utilities::title("\n After augmentation Database is :");

	showDb(dbxml);
	Utilities::title("Storing Augmented Database in \"AugmentedDB.xml\"");
	CreateXML(dbxml,"AugmentedDB.xml");
}

template<typename T>
inline DbElement<T> Persistance<T>::handlerForReadXML(std::shared_ptr<AbstractXmlElement> x)
{
	DbElement<T> demoElem;
	for (auto y : x->children()) {
		if (y->value() == "children" && y->children().size()>0) {
			
			
			for (auto z : y->children()) {
				demoElem.children().push_back(z->children()[0]->value());
			}
		}
		else if (y->value() == "payload") {
			
			
			handlerforpayload(y,demoElem);
		}
		else {
			if (y->value() == "name") {
				demoElem.name(y->children()[0]->value());
			}
			if (y->value() == "description") {
				demoElem.descrip(y->children()[0]->value());
			}
			if (y->value() == "dtime") {
				demoElem.dateTime(DateTime().now());
			}
			if (y->value() == "key") {
				//keyname = y->children()[0]->value();
			}
		}
	}

	return demoElem;

}

template<typename T>
inline void Persistance<T>::handlerforpayload(std::shared_ptr<AbstractXmlElement> y, DbElement<T>& demoElem)
{
	if (y->children()[0]->children().size() > 0) {
		demoElem.payLoad().setpath(y->children()[0]->children()[0]->value());
	}
	if (y->children()[1]->children().size() > 0) {
		for (auto z : y->children()[1]->children()) {
			demoElem.payLoad().getcategory().push_back(z->children()[0]->value());
		}
	}

}


