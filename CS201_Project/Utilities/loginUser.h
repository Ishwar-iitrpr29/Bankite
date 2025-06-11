#ifndef LOGIN_USER
#define LOGIN_USER

#include<bits/stdc++.h>
#include "../models/User.h"
#include "../models/transcation.h"
using namespace std;

User* checkUserExist(string accountNumber,string password){
    DIR *dr;
    struct dirent *en;
    dr = opendir("database"); 
    if (dr == nullptr) {
        cerr << "Could not open current directory" << endl;
        return NULL; // Use EXIT_FAILURE for error exit codes
    }
    if (dr) {
            string fileName="database/"+ accountNumber+".txt";
            ifstream inputFile(fileName);
            // Check if the file was opened successfully
            if (!inputFile) {
                cerr << "Please Enter the Valid Account Number" << endl;
                return NULL; // Exit with an error code
            }

            string line;

            map<string,string> keyValues;

            Transcation* transcation_history;
            
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

                    
                    value=decodeMessage(value,accountNumber);

                    keyValues[key]=value;

                }
            }
            User* loginedUser=new User(keyValues["Name"],keyValues["DOB"],keyValues["Phone Number"],keyValues["Address"]);
            loginedUser->account_balance=(stoi)(keyValues["Balance"]);
            loginedUser->Account_Number=keyValues["Account Number"];
            loginedUser->password=keyValues["Password"];

            
            if(keyValues["Account Number"]==accountNumber && keyValues["Password"]==password){
                return loginedUser;
            }
            else if(keyValues["Password"]!=password){
                for(int i=0;i<3;i++){
                    cout<<"Please enter the correct Password: ";
                    string password=getHiddenInput();
                    if(keyValues["Password"]==password){
                        return loginedUser;
                    }
                }
                return NULL;
            }
            inputFile.close(); // Close the file

        closedir(dr); 
    }
    return NULL;
}

User* loginUser(){
    string AccountNumber,password;
    cout<<"Enter your Account Number: ";
    cin>>AccountNumber;
    cout<<"Enter the Password: ";
    password=getHiddenInput();
    User* loginedUser=checkUserExist(AccountNumber,password);
    if(loginedUser!=NULL){
        return loginedUser;
    }
    else{
        return NULL;
    }

}


#endif // LOGIN_USER