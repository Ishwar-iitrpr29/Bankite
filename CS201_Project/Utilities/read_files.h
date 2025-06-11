#ifndef Read_file
#define Read_file


#include<bits/stdc++.h>
#include <dirent.h>
#include <sys/types.h>
#include "../Utilities/BTree.h"
using namespace std;


long long convertToLongLong(const string& str) {
    try {
        // Convert the string to long long
        return stoll(str);
    } catch (const invalid_argument&) {
        cerr << "Invalid input: Not a valid number." << endl;
        throw; // Rethrow the exception if you want to handle it later
    } catch (const out_of_range&) {
        cerr << "Invalid input: Number out of range for long long." << endl;
        throw; // Rethrow the exception if you want to handle it later
    }
}

BTree* read_Data() {
   DIR *dr;
   struct dirent *en;
   BTree* root=new BTree();
   dr = opendir("database"); 
    if (dr == nullptr) {
        cerr << "Could not open current directory" << endl;
        return NULL; // Use EXIT_FAILURE for error exit codes
    }
    if (dr) {
      while ((en = readdir(dr)) != NULL) {
        if((string)(en->d_name)!="." && (string)(en->d_name)!=".."){
            string fileName=en->d_name;
            fileName.erase(11,14);
            long long number=convertToLongLong(fileName);
            root->insert(number);
        }
      }
      closedir(dr); 
    }
    return root;
}


#endif
