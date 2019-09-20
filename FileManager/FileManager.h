#pragma once
///////////////////////////////////////////////////////////////////////////////////////
// FileManager.h - Find all files on specified path or tree matching specified patt  //
//                                                                                   //
// Ver 1.0                                                                           //
// Application:   Duplicates Project                                                 //
// Platform:      Dell XPS 2720, Win 10.1, Visual Studio 2019                        //
// Author:        Simuk Arya,  Syracuse University                                   //
//                siarya@syr.edu                                                     //
///////////////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * FileManager uses the services of FileSystem to find files and stores its findings
 * efficiently in DataStore.
 * - Finds all files, matching a set of patterns, along with their paths.
 * - Stores each filename and path only once, using DataStore.
 *
 * User Interface:
 * changePath("/aPath");
 * addPattern("*.h");
 * search();
 *
 * Required Files:
 * ---------------
 * FileManager.h, FileManager.cpp, FileSystem.h, FileSystem.cpp,
 * DataStore.h, DataStore.cpp.
 *
 * Build Process:
 * --------------
 * From the Visual Studio Developer's Command Prompt:
 * devenv VSHelp.sln /rebuild debug
 *
 * Maintenance History:
 * --------------------
 * - Ver1.1 : 1 July 2019
	modified functions addpattern and changePath
 * - Ver 1.0 : 1 Mar 2015(Dr. Jim Fawcett)
 *   first release
 */

#include<string>
#include<iostream>
#include<vector>
#include"../DataStore/DataStore.h"

//#define Test_FileManager

class FileManager
{public:
	bool changePath(const std::string& path);
	FileManager(std::string& path, DataStore &ds);
	void search(bool recurse = false);
	void find(const std::string& path);
	void addPattern(const std::string& patt);
private:
	DataStore& store_;
	std::string path_;
	std::vector <std::string> patterns_ ;
};

