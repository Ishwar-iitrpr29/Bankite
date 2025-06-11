#ifndef User_H
#define User_H

#include<bits/stdc++.h>
#include "../Utilities/ageCalculator.cpp"
#include "../Utilities/read_files.h"
#include <conio.h>
using namespace std;

string getHiddenInput() {
    string input;
    char ch;

    while ((ch = _getch()) != '\r') { // Read until Enter key is pressed
        if (ch == '\b') { // Handle backspace
            if (!input.empty()) {
                input.pop_back();
                cout << "\b \b"; // Move cursor back, overwrite with space, and move back again
            }
        } else {
            input += ch;
            cout << '*'; // Display asterisks for each character
        }
    }

    cout << endl; // Move to the next line after input
    return input;
}


class Transcation;

class User{
    public:
    string name="";
    string dob="";
    string phone_Number="";
    string Account_Number="";
    string Address="";
    int age=0;
    int account_balance=0; 
    tm* createdTime;
    Transcation* transcation_history=NULL;
    string password="";

    public:
    User(string name,string dob,string phone_Number,string Address){
        this->name=name;
        this->dob=dob;
        this->phone_Number=phone_Number;
        this->Address=Address;
        auto now = chrono::system_clock::now();
    
        // Convert to time_t for easy handling
        time_t now_c = chrono::system_clock::to_time_t(now);
        
        // Store the current date and time
        tm* local_time = localtime(&now_c);
        this->createdTime=local_time;
        this->age=ageCalculator(dob);


    }
    void generateAccountNumber(){
        string characters="0123456789";
        bool done=false;
        BTree* root=read_Data();
        while(done!=true){
            string accountNumber;
            for(int i=0;i<11;i++){
                char characterToPush=characters[rand()%characters.size()];
                accountNumber.push_back(characterToPush);
            }
            if(root->search(convertToLongLong(accountNumber))==false){
                this->Account_Number=accountNumber;
                done=true;
            }
        }
    }
    void setPassword(){
        cout<<"Enter the 6 digit password: ";
        string pasword;
        password=getHiddenInput();
        while(password.length()!=6){
            cout<<"Please enter the password of 6 digit."<<endl;
            password=getHiddenInput();
        }
        cout<<"Are you sure you want to add this password?"<<endl;
        cout<<"Enter Y for yes and N for no."<<endl;
        string confirmation;
        getline(cin,confirmation);
        if(confirmation=="Y" || confirmation=="y"){
            this->password=password;
        }
        else{
            setPassword();
        }

    }
    void changePhoneNumber(string newNumber){
        cout<<"Are you sure you want to change the Phone Number?"<<endl;
        cout<<"Enter Y for yes and N for no."<<endl;
        string confirmation;
        getline(cin,confirmation);
        if(confirmation=="Y" || confirmation=="y"){
            this->phone_Number=newNumber;
        }
    }
    void changePassword(string newPassword){
        cout<<"Are you sure you want to change the password?"<<endl;
        cout<<"Enter Y for yes and N for no."<<endl;
        string confirmation;
        getline(cin,confirmation);
        if(confirmation=="Y" || confirmation=="y"){
            this->password=newPassword;
        }
    }
    void depositMoney(int moneyToDeposit){
        this->account_balance=this->account_balance+moneyToDeposit;

    }
    void withdrawMoney(int moneyToWithDraw){
        if(this->account_balance<moneyToWithDraw){
            cout<<"You do not enough money to withdraw."<<endl;
            return ;
        }
        this->account_balance=this->account_balance-moneyToWithDraw;
        cout<<"Money withdrawed from your account."<<endl;
    }
};

#endif
