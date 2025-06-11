#ifndef Transcation_H
#define Transcation_H

#include<bits/stdc++.h>
#include <regex>
#include <chrono>
#include <ctime> 
#include "../Utilities/write_file.h"
using namespace std;


pair<string,string> formatDateTime(const tm &timeinfo) {
    ostringstream oss;
    
    // Format date
    oss << put_time(&timeinfo, "%d/%m/%Y");
    string date = oss.str(); // Get formatted date string
    oss.str(""); // Clear the stream for the next use
    oss.clear(); // Clear any flags
    
    // Format time
    oss << put_time(&timeinfo, "%H:%M:%S");
    string time = oss.str(); // Get formatted time string
    
    // Combine date and time into a single string
    pair<string,string> ans=make_pair(date,time);
    return ans;
}






class Transcation_Node{
    public:
    int money=0;
    User* fromUser;
    User* ToUser;
    string Transcation_Id;
    tm date_and_time;
    Transcation_Node* previousNode=NULL;
    Transcation_Node* nextNode=NULL;
    public:
    Transcation_Node(int money, User* from_user, User* to_user){
        // Adding Information
        this->money=money;
        this->fromUser=from_user;
        this->ToUser=to_user;
    }
    void generateTranscationId(){
        string transcation_id;
        tm dateTime=this->date_and_time;
        transcation_id+=(to_string)(dateTime.tm_year+1900);
        transcation_id+=(to_string)(dateTime.tm_mon+1);
        transcation_id+=(to_string)(dateTime.tm_mday);
        transcation_id+=(to_string)(dateTime.tm_hour);
        transcation_id+=(to_string)(dateTime.tm_min);
        transcation_id+=(to_string)(dateTime.tm_sec);
        for(int i=0;i<5;i++){
            transcation_id+=fromUser->Account_Number[i];
            transcation_id+=ToUser->Account_Number[i];
        }
        this->Transcation_Id=transcation_id;

    }
};


class Transcation{
    public:
    Transcation_Node* head;
    Transcation_Node* tail;
    
    Transcation(){
        head=NULL;
        tail=NULL;
    }
    void insertTranscation(Transcation_Node* newTranscation){
        if(head==NULL){
            head=newTranscation;
            tail=newTranscation;
        }
        tail->nextNode=newTranscation;
        newTranscation->previousNode=tail;
        newTranscation->nextNode=NULL;
        tail=newTranscation;
    }
    void displayTranscation(){
        Transcation_Node* curr=head;
        while(curr){
                cout<<"Transcation Id: "<<curr->Transcation_Id<<endl;
                cout<<"Money: "<<curr->money<<endl;
                cout<<"From User: "<<curr->fromUser->Account_Number<<endl;
                cout<<"To User: "<<curr->ToUser->Account_Number<<endl;
                cout<<"Date: "<<put_time(&curr->date_and_time,"%d/%m/%Y")<<endl;
                cout<<"Time: "<<put_time(&curr->date_and_time,"%H:%M:%S")<<endl;
                cout<<endl;
                curr=curr->nextNode;
        }
    }

};

void writeTranscationInFile(User* new_user){
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
        outputFile << "Transcation: ";
        Transcation_Node* curr=new_user->transcation_history->head;
        while(curr){
            pair<string,string> dateAndTime=formatDateTime(curr->date_and_time);
            outputFile <<endl;
            outputFile <<"Transcation Id: "<<encodeMessage(curr->Transcation_Id,new_user->Account_Number)<<endl;
            outputFile <<"Money: "<<encodeMessage((to_string)(curr->money),new_user->Account_Number)<<endl;
            outputFile <<"From User: "<<encodeMessage(curr->fromUser->Account_Number,new_user->Account_Number)<<endl;
            outputFile <<"To User: "<<encodeMessage(curr->ToUser->Account_Number,new_user->Account_Number)<<endl;
            outputFile <<"Date: "<<encodeMessage(dateAndTime.first,new_user->Account_Number)<<endl;
            outputFile <<"Time: "<<encodeMessage(dateAndTime.second,new_user->Account_Number)<<endl;
            outputFile <<endl;
            curr=curr->nextNode;
        }
        outputFile.close();
    } else {
        cerr << "Unable to open file\n";
    }
}

void do_Transcation(int money,User* from_user,User* to_user){
    from_user->account_balance = from_user->account_balance - money;
    to_user->account_balance = to_user->account_balance + money;

    Transcation_Node* newTranscation =new Transcation_Node(money,from_user,to_user);
    
    auto now = chrono::system_clock::now();
    time_t now_time_t = chrono::system_clock::to_time_t(now);
    tm local_tm = *localtime(&now_time_t);
    newTranscation->date_and_time=local_tm;

    newTranscation->generateTranscationId();
    from_user->transcation_history->insertTranscation(newTranscation);
    to_user->transcation_history->insertTranscation(newTranscation);

    writeTranscationInFile(from_user);
    writeTranscationInFile(to_user);
}

#endif 
