#pragma once
//#define TEST_DISPLAY

///////////////////////////////////////////////////////////////////////////////
// Display.h - Build catalog of files, show results                          //
//                                                                           //
// Ver 1.0                                                                   //
// Application:   Duplicates Project                                         //
// Platform:      Dell XPS 2720, Win 10.1, Visual Studio 2019                 //
// Author:        Simuk Arya,  Syracuse University                           //
//                siarya@syr.edu                                             //
///////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* Display uses the services of Catalog and FileSystem directly and also indirectly
* depends on DataStore, FileMgr.
* - Parses commandline, passed by Executive, and sets patterns and path in Catalog.
* - Builds a catalog of file information from a directory tree rooted at a specified path,
*   using the Catalog package.
* - Displays filenames and paths of duplicate files found in the catalog.
* - Finds all files in the catalog containing a specified text string.
* - Supports repeated queries for files containing specified text after building catalog.
*
* User Interface:
* - Display.exe path [/s][/a][/d][/f<text>][/q][/c][/h][/?]
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
* Display.h, Display.cpp, Catalog.h, Catalog.cpp, FileSystem.h, FileSystem.cpp
* DataStore.h, DataStore.cpp, FileManager.h, FileManager.cpp,
*
* Build Process:
* --------------
* From the Visual Studio Developer's Command Prompt:
* devenv VSHelp.sln /rebuild debug
*
* Maintenance History:
* --------------------
* - Ver1.1 : 1 July 2019
	modified functions searchText and showResults
 * - Ver 1.0 : 1 Mar 2015(Dr. Jim Fawcett)
*   first release
*/
#include"../Catalog/Catalog.h"
#include"../FileManager/FileSystem.h"
class Display
{
public:
	enum Option {
		s, // recurse into subdirectories
		a, // show all files
		d, // report duplicates
		f, // find text
		q, // query for text at end of execution
		c, // display commandline arguments - used for testing
		h  // display usage message
	};

	// Constructor
	Display(int argc, char* argv[], Catalog& cat) : argc_(argc), argv_(argv), cat_ (cat){}


	//Other public functions
	void showCommandLine(bool vertical = true);
	bool parseCommandLine();
	void showResults();
	void showUsage();
	bool optionEnabled(enum Option opt);
	void textQuery(const std::string& query);
	std::string& searchText();
	std::vector<std::string> getPatterns();




private:
	bool parseError;
	int argc_;
	char** argv_;
	
	// Still to be implemented
	Catalog& cat_;
	std::map<Option, bool> optionState_;
	std::vector<std::string> patterns_;
	std::string path_;
	std::string searchText_;
};

