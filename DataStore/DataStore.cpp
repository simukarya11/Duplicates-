///////////////////////////////////////////////////////////////////////////////
// DataStore.cpp -  Efficiently store file and path of each in Map           //
// Application:   Duplicates Project                                         //
// Platform:      Dell XPS 2720, Win 10.1, Visual Studio 2019                //
// Author:        Simuk Arya,  Syracuse University                           //
//                siarya@syr.edu                                             //
///////////////////////////////////////////////////////////////////////////////



#include "DataStore.h"
#include"../FileManager/FileSystem.h"

 void DataStore::save(const std::string& filename, const std::string& path)
{
	 PathIterator iter = paths.find(path);
	 if (iter == paths.end())
		 iter = paths.insert(path).first;                  // inserted path in set of paths.

	 std::string fileSpec = path + "\\" + filename;
	 FileSystem::FileInfo fi(fileSpec);
	 std::string date = fi.date();
	 Item item = { iter,date };

	 if (store.find(filename) != store.end())
	 {
		 store[filename].push_back(item);

	 }
	 else
	 {
		 ListOfItems list;
		 list.push_back(item);
		 store[filename] = list;
	 }

}
// Return the set of paths from the map if a specific filename is pa
 DataStore::PathCollection DataStore::getPaths(const File& file)
{
	 PathCollection paths;

	 DataStore::iterator iter = store.find(file);
	 if (iter == store.end())
		 return paths;
	 ListOfItems items = store[file];
	 for (auto item : items)
		 paths.push_back(*item.first);


	 return paths;
}

 // ========< TEST STUB> =================

#ifdef TEST_DATASTORE

 
 void main()
 {
	 std::cout << "\n--------------------Testing DATASTORE----------------------\n";

	 DataStore ds;
	 ds.save("firstFile", "firstPath");
	 ds.save("secondFile", "fiirstPath");
	 ds.save("secondFile", "secondPath");
	 ds.save("secondFile", "thirdPath");

	 std::cout << "\n  " << ds.numberOfFiles() << " Files in " << ds.numberOfPaths() << " directories\n";

	 for (auto item : ds)
	 {
		 std::cout << "aa";
		 std::cout << "\n  " << (item).first.c_str()/* << " on " << (item).second.c_str()*/;
		 DataStore::PathCollection paths = ds.getPaths(item.first);
		 for (auto path : paths)
			 std::cout << "\n    " << path;
	 }
	 std::cout << "\n\n";
 
 }


#endif