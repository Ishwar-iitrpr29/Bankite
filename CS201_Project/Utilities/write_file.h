#ifndef Write_file
#define Write_file

#include<bits/stdc++.h>
#include "../models/User.h"
#include "../Utilities/encryptDecrypt.h"
using namespace std;

void writeInFile(User* new_user){
    //) Adding the user to the database.
    string fileName="database/"+ new_user->Account_Number + ".txt";
    ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        outputFile << "Name: " << encodeMessage(new_user->name,new_user->Account_Number) << "\n";
        outputFile << "DOB: " << encodeMessage(new_user->dob,new_user->Account_Number) << "\n";
        outputFile << "Phone Number: " << encodeMessage(new_user->phone_Number,new_user->Account_Number) << "\n";
        outputFile << "Address: " << encodeMessage(new_user->Address,new_user->Account_Number) << "\n";
        outputFile << "Account Number: " << encodeMessage(new_user->Account_Number,new_user->Account_Number) << "\n";
        outputFile << "Age: "<<encodeMessage((to_string)(new_user->age),new_user->Account_Number)<<endl;
        outputFile << "Password: "<<encodeMessage(new_user->password,new_user->Account_Number)<<endl;
        outputFile << "Balance: "<<encodeMessage((to_string)(new_user->account_balance),new_user->Account_Number)<<endl;

        outputFile.close();
    } else {
        cerr << "Unable to open file\n";
    }
}

#endif
