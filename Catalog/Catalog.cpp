///////////////////////////////////////////////////////////////////////////////
// Catalog.cpp -  Builds catalog of files, show results                      //
// Application:   Duplicates Project                                         //
// Platform:      Dell XPS 2720, Win 10.1, Visual Studio 2019                //
// Author:        Simuk Arya,  Syracuse University                           //
//                siarya@syr.edu                                             //
///////////////////////////////////////////////////////////////////////////////

#include "Catalog.h"
#include"../FileManager/FileSystem.h"
//Jim
//JIM FAWCETT
bool Catalog::changePath(const std::string& path)
{
	if (!FileSystem::Directory::exists(path))
		return false;
	path_ == path;
	fileManager_.changePath(path);
	return true;
}

void Catalog::addPattern(const std::string& pattern)
{
	fileManager_.addPattern(pattern);
}

void Catalog::buildCatalog(bool recurse)
{
	fileManager_.search(recurse);
}

// Access the map to show its file and their paths.
void Catalog::showFiles()
{
	for (auto fs : store_)
	{
		std::string file = fs.first;
		std::cout << "\n " << file;
		DataStore::PathCollection paths = store_.getPaths(file);
		for (auto path : paths)
			std::cout << "\n    " << path;
	}
}
// if there are any duplicates, then it will show it
void Catalog::showDuplicates()
{
	std::cout << "\n\n============ DISPLAYING DUPLICATES =============\n\n";
	for (auto f : store_)
	{
		if (f.second.size() > 1)
		{
			DataStore::PathCollection paths = store_.getPaths(f.first);
			for (auto path : paths)
				std::cout << "\n " << path;
		}
	}
	std::cout << "\n\n===============DUPLICATES DISPLAY ENDS==================\N\N";
}

// Searches the string in a file using find algorithm
bool Catalog::textSearch(const std::string& filespec, const std::string& text)
{
	a1.erase();
	a2.erase();
	a3.erase();
	std::ifstream in(filespec);
	if (!in.good())
		return false;
	std::string abc;
	int i = 0;
	size_t pooos;
	while (std::getline(in, abc))
	{
		if (i == 1)
		{
			a3 = abc;
			return true;
		}
		a2 = abc;
		
		pooos = abc.find(text);
		if (pooos < abc.size())
		{
			i = 1;
			continue;
		}

		a1 = a2;
		
	}


	in.close();

	return false;

}

//
void Catalog::showSearchResults(const std::string& searchString)
{
	std::cout << "\n\n=============== Showing TEXTSEARCH RESULTS=======================\n\n";
	bool found=false;
	for (auto f : store_)
	{
		std::string file = f.first;
		DataStore::PathCollection paths = store_.getPaths(file);
		for (auto p : paths)
		{
			std::string fileSpec = p + "\\" + file;
			found = textSearch(fileSpec, searchString);
			if (found)
			{
				std::cout << "\n\n";
				std::cout << "\n  The FileName is========>>" << fileSpec;
				std::cout << "\nThe line before the text line is      ---->>>>>>>>>>  " <<a1;
				std::cout << "\nThe line in which the text is found is---->>>>>>>>>>  " << a2;
				std::cout << "\nThe line next to the text line is     ---->>>>>>>>>>  " << a3;
				std::cout << "\n\n";
			}
		}
	}
	
	std::cout << "\n\n=============== Ending TEXTSEARCH RESULTS=======================\n\n";

}



void Catalog::showSummary()
{
	std::cout << "\n  Found " << store_.numberOfFiles() << " files in "
		<< store_.numberOfPaths() << " directories" << "\n";
}






//++++++++++++++++ < TEST STUB> +++++++++++++++++++++
# ifdef TEST_CATALOG

void main()
{
	bool recurse = true;
	Catalog cat("../..");
	cat.addPattern("*.h");
	cat.addPattern("*.cpp");
	cat.buildCatalog(recurse);
	cat.showSummary();
	std::cout << "\n";
	std::cout<<"Files found:";
	cat.showFiles();
	std::cout<<"Duplicates found:";
	cat.showDuplicates();

	std::string text = "Simuk";
	std::cout<<"\n\nshow textsearch for \"" + text + "\"";
	std::cout << "\n\n";
	cat.showSearchResults(text);
	std::cout << "\n\n";

}
#endif