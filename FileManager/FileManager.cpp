///////////////////////////////////////////////////////////////////////////////////////
// FileManager.h - Find all files on specified path or tree matching specified patt  //
//                                                                                   //
// Ver 1.0                                                                           //
// Application:   Duplicates Project                                                 //
// Platform:      Dell XPS 2720, Win 10.1, Visual Studio 2019                        //
// Author:        Simuk Arya,  Syracuse University                                   //
//                siarya@syr.edu                                                     //
///////////////////////////////////////////////////////////////////////////////////////

#include "FileManager.h"
#include"FileSystem.h"



bool FileManager::changePath(const std::string& path)
{
	if (FileSystem::Directory::exists(path))
	{
		path_ = path;
		return true;
	}
	return false;
}

FileManager::FileManager(std::string& path, DataStore& ds) :path_(path), store_(ds)
{

}

void FileManager::addPattern(const std::string& patt)
{
	patterns_.push_back(patt);
}


void FileManager::search(bool recurse)
{
	std::string fullPath = FileSystem::Path::getFullFileSpec(path_);
	if (recurse)
		find(fullPath);
	else
	{
		for (auto patt : patterns_)
		{
			std::vector<std::string> files = FileSystem::Directory::getFiles(fullPath, patt);
			for (auto file : files)
			{
				store_.save(file, fullPath);
			}
		}
	}

}

void FileManager::find(const std::string& path)
{
	for (auto patt : patterns_)
	{
		std::vector<std::string> files = FileSystem::Directory::getFiles(path, patt);
		for (auto f : files)
		{
			//std::cout << "\n  -- saving file: " << f << ", on path: " << path;
			std::string fileSpec = path + "\\" + f;
			FileSystem::FileInfo fi(fileSpec);
			std::string date = fi.date();
			store_.save(f, path);
			//std::cout << "/n" << f << "/n" << path << "\n";
		}
	}
	std::vector<std::string> subdirs = FileSystem::Directory::getDirectories(path);
	for (auto d : subdirs)
	{
		if (d != "." && d != "..")
		{
			//std::cout << "\n  -- found dir: " << d;
			find(path + "\\" + d);
		}
	}
}


#ifdef Test_FileManager

void main()
{
	DataStore ds;
	std::string path = "../..";
	FileManager fm(path,ds);

	fm.addPattern("*.h");
	fm.addPattern("*.cpp");

	std::cout << "Recursive search\n\n\n\n";
	fm.search(true);

	std::cout << "\n\n NonRecursive search\n\n\n\n";
	fm.search(false);
}

#endif

