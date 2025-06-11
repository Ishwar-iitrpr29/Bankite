#ifndef FETCH_USER
#define FETCH_USER

#include <bits/stdc++.h>
#include "../models/User.h"
#include "../models/transcation.h"
using namespace std;


User* getUserDetails(string accountNumber){
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
                cerr << "Please Enter the Valid Account Number: " <<accountNumber<< endl;
                return NULL; // Exit with an error code
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

                    if(key=="Transcation"){
                        break;
                    }
                    value=decodeMessage(value,accountNumber);

                    keyValues[key]=value;


                }
            }
            User* loginedUser=new User(keyValues["Name"],keyValues["DOB"],keyValues["Phone Number"],keyValues["Address"]);
            loginedUser->account_balance=convertToLongLong(keyValues["Balance"]);
            loginedUser->Account_Number=keyValues["Account Number"];
            loginedUser->password=keyValues["Password"];

            return loginedUser;
            inputFile.close(); // Close the file

        closedir(dr); 
    }
    return NULL;
}

tm* convertDateAndTime(const string& dateString,const string& timeString) {
    static struct tm tmDate = {};  // Static to return a pointer

    // Parse the date string
    istringstream dateStream(dateString);
    dateStream >> get_time(&tmDate, "%d/%m/%Y");
    if (dateStream.fail()) {
        std::cerr << "Error parsing date." << std::endl;
        return nullptr;
    }

    // Parse the time string
    std::istringstream timeStream(timeString);
    timeStream >> std::get_time(&tmDate, "%H:%M:%S");
    if (timeStream.fail()) {
        std::cerr << "Error parsing time." << std::endl;
        return nullptr;
    }

    // Normalize the tm structure
    mktime(&tmDate);

    return &tmDate;  // Return a pointer to the tm structure
}


void getUserTranscation(User* user){
    DIR *dr;
    struct dirent *en;
    dr = opendir("database"); 
    if (dr == nullptr) {
        cerr << "Could not open current directory" << endl;
        return ; // Use EXIT_FAILURE for error exit codes
    }
    if (dr) {
        string fileName="database/"+ user->Account_Number + ".txt";
        ifstream inputFile(fileName);
        if (!inputFile) {
            cerr << "Please Enter the Valid Account Number" << endl;
            return ; // Exit with an error code
        }
        string line;

        map<string,string> keyValues;

        Transcation* transcation_hist=new Transcation();
        
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

                value=decodeMessage(value,user->Account_Number);

                keyValues[key]=value;


                if(key=="Time"){
                    User* fromUser=getUserDetails(keyValues["From User"]);
                    User* toUser=getUserDetails(keyValues["To User"]);
                    int money=convertToLongLong(keyValues["Money"]);
                    string date=keyValues["Date"];
                    string time=keyValues["Time"];
                    tm* dateAndTime=convertDateAndTime(date,time);
                    Transcation_Node* node=new Transcation_Node(money,fromUser,toUser);
                    node->Transcation_Id=keyValues["Transcation Id"];
                    node->date_and_time=*dateAndTime;

                    transcation_hist->insertTranscation(node);
                }
            }
        }
        user->transcation_history=transcation_hist;

        inputFile.close(); // Close the file

        closedir(dr); 
    }

}


User* getUser(string accountNumber){
    User* user=getUserDetails(accountNumber);
    getUserTranscation(user);
    return user;
}

#endif // FETCH_USER
