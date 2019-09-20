#pragma once

///////////////////////////////////////////////////////////////////////////////
// DataStore.h -  Efficiently store file and path of each in Map             //
// Application:   Duplicates Project                                         //
// Platform:      Dell XPS 2720, Win 10.1, Visual Studio 2019                //
// Author:        Simuk Arya,  Syracuse University                           //
//                siarya@syr.edu                                             //
///////////////////////////////////////////////////////////////////////////////
/*
/*
* Package Operations:
* -------------------
* DataStore is a stand-alone package that has no dependencies.
* Its purpose is to efficiently store directory
* information.
* - Stores each filename and path only once.
*
* User Interface:
* save(file, path)  -->> This function is called by fileManager after each file is found
* DataStore::iterator iter = ds.begin();
* std::vector<std::string> paths = getPaths();  
* size_t nFiles = ds.numberOfFiles();  -->> These functions are used by Display
* size_t nPaths = ds.numberOfPaths();
*
* Required Files:
* ---------------
* DataStore.h, DataStore.cpp
*
* Build Process:
* --------------
* From the Visual Studio Developer's Command Prompt:
* devenv VSHelp.sln /rebuild debug
*
* Maintenance History:
* --------------------
* - Ver1.1 : 1 July 2019
	discarding usage of date
 * - Ver 1.0 : 1 Mar 2015(Dr. Jim Fawcett)
*/


#include<vector>
#include<string>
#include<set>
#include<list>
#include<map>
#include<iostream>
//#define  TEST_DATASTORE
class DataStore
{
public:
	//Data storeage elements
	using Date =std::string;
	using Path =std::string;
	using Paths =std::set <Path>;
	using PathIterator = Paths::iterator;                   //set of paths ka iterator 
	using ListOfIterators = std::list<PathIterator>;
	using Item = std::pair<PathIterator, Date>;
	using ListOfItems = std::list<Item>;
	using File=std::string;
	using Store= std::map<File,ListOfItems>;                 // Data is stored in this map
	using iterator = Store::iterator;
	using PathCollection = std::vector<Path>;

	// Functions that are used
	void save(const std::string &filename,const std::string &path);
	PathCollection getPaths(const File& file);
	size_t numberOfFiles();
	size_t numberOfPaths();
	iterator begin() { return store.begin(); }
	iterator end() { return store.end(); }

private:
	Store store;
	Paths paths;
};




inline size_t DataStore::numberOfFiles()
{ return store.size(); }

inline size_t DataStore::numberOfPaths() 
{ return paths.size(); }

//// xyz