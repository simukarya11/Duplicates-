#include "Display.h"
///////////////////////////////////////////////////////////////////////////////
// Display.cpp - Build catalog of files, show results                        //
//                                                                           //
// Ver 1.0                                                                   //
// Application:   Duplicates Project                                         //
// Platform:      Dell XPS 2720, Win 10.1, Visual Studio 2019                 //
// Author:        Simuk Arya,  Syracuse University                           //
//                siarya@syr.edu                                             //
///////////////////////////////////////////////////////////////////////////////


void Display::showUsage()
{
	std::cout << "\n  FileAnalyzer:";
	std::cout << "\n ---------------";
	std::cout << "\n  Expected commandline arguments:";
	std::cout << "\n    Path - directory or root of directory tree to search - default \".\"";
	std::cout << "\n    File patterns - zero or more strings of the form \"*.h\"";
	std::cout << "\n    Options - zero or more of the following:";
	std::cout << "\n       /s - traverse the directory tree rooted at path";
	std::cout << "\n       /a - show all files";
	std::cout << "\n       /d - display names and paths of files appearing more than once";
	std::cout << "\n       /f<text> - find all files containing <text>";
	std::cout << "\n       /q - query for text search at the end of execution";
	std::cout << "\n       /c - display commandline arguments";
	std::cout << "\n       /h - display this message";
	std::cout << "\n    The path argument must come first.  The other arguments may be";
	std::cout << "\n    supplied in any order.";
	std::cout << "\n\n";
}

std::string& Display::searchText()
{
	return searchText_;
}

bool Display::optionEnabled(Option opt)
{
	return optionState_[opt];
}


void Display::showCommandLine(bool vertical)
{
	std::cout << "\n\n=============== Command line arguments below================\n\n";
	for (int i = 1; i < argc_; i++)
	{
		std::cout << argv_[i] << " ";
		if (i = argc_ - 1)
			std::cout << "\n";
	}
}

bool Display::parseCommandLine()
{
	parseError = false;
	if (argc_ < 2)
	{
		parseError = true;
		showUsage();
		return false;
	}
	if (argv_[1][0] == '/')
	{
		showUsage();
		return 1;
	}
	path_ = argv_[1];
	if (!FileSystem::Directory::exists(path_))
	{
		std::cout << "\n  can't find directory \"" << path_ << "\"";
		parseError = true;
		return false;
	}
	// find options and patterns,
	// ignore unrecognized options, accept all patterns

	optionState_[s] = false;
	optionState_[a] = false;
	optionState_[d] = false;
	optionState_[f] = false;
	optionState_[q] = false;
	optionState_[c] = false;

	for (int i = 2; i < argc_; ++i)
	{
		if (argv_[i][0] == '/')
		{
			switch (argv_[i][1])
			{
			case 's': optionState_[s] = true; break;
			case 'a': optionState_[a] = true; break;
			case 'd': optionState_[d] = true; break;
			case 'f':
				optionState_[f] = true;
				searchText_ = std::string(argv_[i]).substr(2);  // This is only done for test stub
				break;                                          // for rest
			case 'q': optionState_[q] = true; break;
			case 'c': optionState_[c] = true; break;
			case 'h': optionState_[h] = true; break;
			case '?': optionState_[h] = true; break;
			default: break;
			}
		}
		else
		{
			patterns_.push_back(argv_[i]);
			cat_.addPattern(argv_[i]);
		}
	}
	return true;
}

void Display::showResults()
{
	/*
   s, // recurse into subdirectories
   a, // show all files
   d, // report duplicates
   f, // find text
   q, // query for text at end of execution
   c  // display commandline arguments - used for testing
   h  // show usage
 */
	if (optionEnabled(h))
	{
		showUsage();
}
	if (optionEnabled(c))
	{
		std::cout<<"Commandline arguments:";
		showCommandLine();
		std::cout << "\n";
	}
	cat_.showSummary();
	if (optionEnabled(a))
	{
		std::cout << "Show all files found:";
		cat_.showFiles();
		std::cout << "\n";
	}
	if (optionEnabled(f))
	{
		std::cout << "Show text search results:";
		std::cout << "\n  search text = \"" << searchText() << "\"";
		cat_.showSearchResults(searchText());
		std::cout << "\n";
	}
	if (optionEnabled(d))
	{
		std::cout << "Show duplicate files:";
		cat_.showDuplicates();
		std::cout << "\n";
	}
	if (optionEnabled(q))
	{
		std::cout << "Text queries:";
		std::string input;
		while (true)
		{
			std::cout << "\n  enter text string (return to quit): ";
			std::getline(std::cin, input);
			if (input.size() == 0)
				break;
			cat_.showSearchResults(input);
		}
	}
}





#ifdef TEST_DISPLAY

int main(int argc, char* argv[])
{
	std::cout<<"Testing Display package", '=';
	std::cout << "\n";

	Catalog cat;  // defaults to path = ".";
	if (argc >= 2)
	{
		cat.changePath(argv[1]);
  }
	Display display(argc, argv, cat);
	display.showCommandLine(false);
	if (display.parseCommandLine())
		std::cout << "\n  commandline parse succeeded";

	if (display.optionEnabled(display.s))
		std::cout << "\n  s option enabled";
	if (display.optionEnabled(display.a))
		std::cout << "\n  a option enabled";
	if (display.optionEnabled(display.d))
		std::cout << "\n  d option enabled";
	if (display.optionEnabled(display.f))
		std::cout << "\n  f option enabled with search text \"" << display.searchText() << "\"";
	if (display.optionEnabled(display.q))
		std::cout << "\n  q option enabled";
	if (display.optionEnabled(display.c))
		std::cout << "\n  c option enabled";
	if (display.optionEnabled(display.h))
		std::cout << "\n  h option enabled";
	std::cout << "\n";

	cat.buildCatalog(display.optionEnabled(display.s));
	std::cout << "Showing results based on commandline arguments";
	display.showResults();

	std::cout << "\n\n";
	return 0;
}

#endif