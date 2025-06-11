#ifndef EMPLOYEE
#define EMPLOYEE

#include<bits/stdc++.h>
#include<chrono>
#include<ctime>
#include "User.h"
#include "../Utilities/encryptDecrypt.h"
#include "../Utilities/fetchUser.h"
using namespace std;


void displayMinor(){
    DIR *dr;
    struct dirent *en;
    dr = opendir("database"); 
    if (dr == nullptr) {
        cerr << "Could not open current directory" << endl;
        return ; // Use EXIT_FAILURE for error exit codes
    }
    if (dr) {
      while ((en = readdir(dr)) != NULL) {
        if((string)(en->d_name)!="." && (string)(en->d_name)!=".."){
            string fileName="database/";
            fileName+=en->d_name;
            ifstream inputFile(fileName);
            // Check if the file was opened successfully
            if (!inputFile) {
                cerr << "Unable to open file" << endl;
                return ; // Exit with an error code
            }

            string line;

            map<string,string> keyValues;
            
            // Read the file line by line
            while (getline(inputFile, line)) {
                if (line.empty() || line[0] == '#') {
                    continue;
                }
                size_t delimiterPos = line.find(':');
                if (delimiterPos != std::string::npos) {
                    // Extract key and value
                    string key = line.substr(0, delimiterPos);
                    string value = line.substr(delimiterPos + 1);

                    // Trim whitespace (optional)
                    key.erase(key.find_last_not_of(" \n\r\t") + 1);
                    value.erase(0, value.find_first_not_of(" \n\r\t"));

                    value=decodeMessage(value,en->d_name);
                    keyValues[key]=value;
                    if(key=="Age"){
                        int age=stoi(value);
                        if(age<18){
                            cout<<keyValues["Account Number"]<<" ";
                        }
                    }
                }
            }


            inputFile.close(); // Close the file

        }
      }
      closedir(dr); 
    }
    cout<<endl;
}

void displayAccounts(){
    BTree* root=read_Data();
    root->inOrderTraverse();
    cout<<endl;
}

bool loginEmployee(){
    string password;
    cout<<"Please Enter the password: ";
    for(int i=0;i<3;i++){
        password=getHiddenInput();
        if(password=="admin"){
            return true;
        }
        else{
            cout<<"Please Enter only valid Password."<<endl;
        }
    }
    return false;
}


#endif