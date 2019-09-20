#pragma once
///////////////////////////////////////////////////////////////////////////////
// Catalog.h -    Builds catalog of files, show results                      //
// Application:   Duplicates Project                                         //
// Platform:      Dell XPS 2720, Win 10.1, Visual Studio 2019                //
// Author:        Simuk Arya,  Syracuse University                           //
//                siarya@syr.edu                                             //
///////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 -->> Basically catalog plays with the data stored in Map Store
 * Catalog uses the services of DataStore, FileMgr, and FileSystem to efficiently
 * build a catalog of file and directory information.
 * - Builds a catalog of file information from a directory tree rooted at a specified path.
 * - Stores each filename and path only once.
 * - Displays filenames and paths of duplicate files found in the catalog.
 * - Finds all files in the catalog containing a specified text string.
 * - Supports repeated queries for files containing specified text after building catalog.
 *
 * User Interface:
 * - Catalog.exe path [/s][/a][/d][/f<text>][/q][/c][/h][/?]
 *   s, // recurse into subdirectories
 *   a, // show all files
 *   d, // report duplicates
 *   f, // find text
 *   q, // query for text at end of execution
 *   c, // display commandline arguments - used for testing
 *   h  // display usage message
 *   ?  // display usage message
 *
 * Required Files:
 * ---------------
 * Catalog.h, Catalog.cpp, DataStore.h, DataStore.cpp,
 * FileManager.h, FileManager.cpp, FileSystem.h, FileSystem.cpp,
 *
 * Build Process:
 * --------------
 * From the Visual Studio Developer's Command Prompt:
 * devenv VSHelp.sln /rebuild debug
 *
 * Maintenance History:
 * --------------------
 * - Ver1.1 : 1 July 2019
	modified functions showDupliactes and showFiles
 * - Ver 1.0 : 1 Mar 2015(Dr. Jim Fawcett)
 * - first release
 */



#include"..//FileManager/FileManager.h"
#include"../DataStore/DataStore.h"
#include<fstream>
#include<iostream>
#include<vector>
//#define TEST_CATALOG
class Catalog
{
public:
	std::string a1{};
	std::string a2{};
	std::string a3{};
	Catalog(const std::string& path=".") : path_(path), store_(DataStore()), fileManager_(path_, store_){}
	bool changePath(const std::string& path);
	void addPattern(const std::string& pattern);
	void buildCatalog(bool recurse = false);
	void showFiles();
	void showDuplicates();
	void showSearchResults(const std::string& searchString);
	void showSummary();

private:
	bool textSearch(const std::string& filespec, const std::string& text);
	std::string path_;
	DataStore store_;
	FileManager fileManager_;
};

