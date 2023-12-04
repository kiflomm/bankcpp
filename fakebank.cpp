#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;
struct Customer{
    unsigned long customer_id;
    char customer_name[20];
    char customer_address[20];
    double customer_balance;
}; 
void group_members();
void menu();
void continue_or_exit();
void new_record();
void display_customer();
void withdraw_some();
void deposit_some();
void delete_customer();
void change_customer();
void display_all();
int main(){
    /* system("cls");
    group_members(); */
    system("cls");
    menu();
}
void menu()
{
    int choice;
    cout << "PRESS: 1. Enter new records into the file" << endl;
    cout << "PRESS: 2. Search for a particular customer's record and display it" << endl;
    cout << "PRESS: 3. Withdraw a specified amount from the customer account." << endl;
    cout << "PRESS: 4. Deposit a specified amount to the account." << endl;
    cout << "PRESS: 5. Search for a particular customer's record and delete it." << endl;
    cout << "PRESS: 6. Search for a particular customer's record and change it." << endl;
    cout << "PRESS: 7. Display the contents of the entire file." << endl;
    cout << "PRESS: 0. To exit the menu." << endl;
    cin >> choice;
    while (choice > 7 || choice < 0){
        cout << "Please try to enter again." << endl;
        cin >> choice;
    } 
    system("cls");
    switch (choice)
    {
    case 1: 
        new_record();
        break;
    case 2:
        display_customer();
        break;
    case 3:
        withdraw_some(); break;
    case 4:
        deposit_some(); break;
    case 5:
        delete_customer();break;
    case 6:
        change_customer(); break;
    case 7:
        display_all(); break; 
    }
    continue_or_exit();
}
void continue_or_exit(){
    cout << "\t\t\tDo you want to go back to the main menu. \n\t\tpress 1 to continue \n\t\tpress another key to exit" << endl;
    string hash;
    cin >> hash;
    system("cls");
    if (!hash.compare("1")){
        menu();
    }
}
void new_record()
{
    Customer new_customer,retrieve_customer;
    long tempid; 
    double tempbalance;
    ofstream write_file("customers.dat", ios::binary | ios::app);
    cout << "Enter customers id: ";
    cin >> tempid;
    while (cin.fail()||tempid <= 0){ // input validation
        cout << "non positive integer input is invaid try again: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> tempid;
    }
    ifstream read_file("customers.dat", ios::binary | ios::app);
    while (read_file.read(reinterpret_cast<char *>(&retrieve_customer), sizeof(retrieve_customer))){
        if (retrieve_customer.customer_id == tempid){
            cout << "a customer named " << retrieve_customer.customer_name <<" already existes in the database.please enter another Id."<<endl;
            cin >> tempid;
            while (cin.fail()||tempid <= 0){ // input validation
                cout << "non positive integer input is invaid try again: ";
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> tempid;
            }
        }
    }
    new_customer.customer_id = tempid;
    cout << "Enter customers name: ";
    cin >> new_customer.customer_name;
    cout << "Enter customer Address: ";
    cin >> new_customer.customer_address;
    cout << "Enter customer balance: ";
    cin >> tempbalance;
    while (cin.fail() || tempbalance < 25){ // input validation
        if(tempbalance<25) 
            cout << "initial balance cant be less than 25.deposit greater than 25: ";
        else
            cout << "non integer input is invaid try again: "; 
            
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> tempbalance;
    }
    new_customer.customer_balance = tempbalance;
    cout<<"\t********new customer successfuly added********"<<endl;
    write_file.write(reinterpret_cast<char *>(&new_customer), sizeof(new_customer));
    write_file.close();
}

void display_customer()
{
    long id,flag = 0;
    Customer retrieve_customer;
    reenter:
    cout << "Enter the Id number of the customer to display customer info: "; 
    cin >> id;
    while (cin.fail()||id <= 0){ // input validation
        cout << "non positive integer input is invaid try again: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> id;
    }
    ifstream read_file("customers.dat", ios::binary);
    while (read_file.read(reinterpret_cast<char *>(&retrieve_customer), sizeof(retrieve_customer)))
    {
        if (retrieve_customer.customer_id == id)
        {
            cout << "customer id = " << retrieve_customer.customer_id << endl;
            cout << "customer name = " << retrieve_customer.customer_name << endl;
            cout << "customer address = " << retrieve_customer.customer_address << endl;
            cout << "customer balance = " << retrieve_customer.customer_balance << endl;
            cout << "_____________________________________________________" << endl;
            flag = 1;
            break;
        }
    }
    read_file.close();
    if(!flag){
        string hash; 
        cout<<"\t\tA customer with that Id number doesnt exist.Do you want to try again?\n"
            <<"\t\t If yes 1 or another key to cancle"<<endl;
        cin >> hash;
        if(!hash.compare("1"))
            goto reenter;
    }
};

void withdraw_some(){
    long id;
    int flag = 0;
    double withdraw_amount;
    Customer retrieve_customer;
    reenter:
    cout << "Enter the Id number of the customer to withdraw : ";
    cin >> id; 
    while (cin.fail()||id <= 0){ // input validation
        cout << "non positive integer input is invaid try again: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> id;
    }
    cout << "Enter the amount to be withdrawn: ";
    cin >> withdraw_amount;
    while (cin.fail()|| withdraw_amount <= 0){ // input validation
        cout << "non positive number input is invaid try again: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> withdraw_amount;
    }
    fstream read_write_file("customers.dat", ios::binary | ios::in | ios::out);
    int target_record_index = 0;
    while (read_write_file.read(reinterpret_cast<char *>(&retrieve_customer), sizeof(retrieve_customer))){
        if (retrieve_customer.customer_id == id){
            flag = 1;
            break;
        }
        target_record_index++;
    }
    if(!flag){
        string hash; 
        cout<<"\t\tA customer with that Id number doesnt exist.Do you want to try again?\n"
            <<"\t\t If yes 1 or another key to cancle"<<endl;
        cin >> hash;
        if(!hash.compare("1"))
            goto reenter;
    }
    double new_balance = retrieve_customer.customer_balance - withdraw_amount;
    if(new_balance>= 25){
        cout << "You have successfuly withdrawn "<< withdraw_amount <<" from "<< retrieve_customer.customer_name 
        <<".\nThe customers current balance  is "<<new_balance<< endl;
        retrieve_customer.customer_balance = new_balance;
    } 
    else{
        string hash; 
        cout<<"\t\tThe customers balance after withdrawal is less than 25 .Do you want to withdraw less amount\n"
            <<"\t\t If yes 1 or another key to cancle"<<endl;
        cin >> hash;
        if(!hash.compare("1"))
        goto reenter;
    }
    read_write_file.seekp(target_record_index * sizeof(Customer));
    read_write_file.write(reinterpret_cast<char *>(&retrieve_customer), sizeof(retrieve_customer));
    read_write_file.close();
};

void deposit_some(){
    long id; 
    double deposit_amount;
    Customer retrieve_customer;
    reenter:
    cout << "Enter the Id number of the customer to deposit : ";
    cin >> id;
    while (cin.fail()||id <= 0){ // input validation
            cout << "non positive integer input is invaid try again: ";
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> id;
        }
    cout << "Enter the amount to deposit: ";
    cin >> deposit_amount;
    while (cin.fail()|| deposit_amount <= 0){ // input validation
        cout << "non positive number input is invaid try again: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> deposit_amount;
    }
    fstream read_write_file("customers.dat", ios::binary | ios::in | ios::out);
    int target_record_index = 0,flag=0;
    while (read_write_file.read(reinterpret_cast<char *>(&retrieve_customer), sizeof(retrieve_customer))){
        if (retrieve_customer.customer_id == id){
            flag = 1;
            break;
        }
        target_record_index++;
    }
    if(flag){
        retrieve_customer.customer_balance += deposit_amount;
        cout << "You have successfuly deposited "<< deposit_amount <<" to "<< retrieve_customer.customer_name 
        <<"The current balance is"<<retrieve_customer.customer_balance<< endl;
        
    }else{
        string hash; 
        cout<<"\t\tA customer with that Id number doesnt exist.Do you want to try again?\n"
            <<"\t\t If yes 1 or another key to cancle"<<endl;
        cin >> hash;
        if(!hash.compare("1"))
        goto reenter;
    }
    read_write_file.seekp(target_record_index * sizeof(Customer));
    read_write_file.write(reinterpret_cast<char *>(&retrieve_customer), sizeof(retrieve_customer));
    read_write_file.close();
};
void delete_customer()
{
    long id;
    reenter:
    cout << "Enter the ID number of the customer to delete: ";
    cin >> id;
    while (cin.fail()||id <= 0){ // input validation
        cout << "non positive integer input is invaid try again: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> id;
    }
    ifstream read_file("customers.dat", ios::binary);
    ofstream temp_file("temp.dat", ios::binary | ios::out);

    Customer retrieve_customer;
    bool found = false;

    while (read_file.read(reinterpret_cast<char *>(&retrieve_customer), sizeof(retrieve_customer)))
    {
        if (retrieve_customer.customer_id == id)
        {
            found = true;
            continue;
        }

        temp_file.write(reinterpret_cast<char *>(&retrieve_customer), sizeof(retrieve_customer));
    }

    read_file.close();
    temp_file.close();

    if (found)
    {
        remove("customers.dat");
        rename("temp.dat", "customers.dat");
        cout << "Customer record with ID " << id << " has been deleted." << endl;
    }
    else
    {
        string hash; 
        cout<<"\t\tA customer with that Id number doesnt exist.Do you want to try again?\n"
            <<"\t\t If yes 1 or another key to cancle"<<endl;
        cin >> hash;
        if(!hash.compare("1"))
        goto reenter;
    }
}
void change_customer()
{
    long id;
    reenter:
    cout << "Enter the ID number of the customer to change: ";
    cin >> id;
    while (cin.fail()||id <= 0){ // input validation
        cout << "non positive integer input is invaid try again: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> id;
    }
    fstream read_write_file("customers.dat", ios::binary | ios::in | ios::out);

    Customer retrieve_customer;
    bool found = false;

    while (read_write_file.read(reinterpret_cast<char *>(&retrieve_customer), sizeof(retrieve_customer)))
    {
        if (retrieve_customer.customer_id == id)
        {
            found = true;

            cout << "Enter the new name: ";
            cin >> retrieve_customer.customer_name;

            cout << "Enter the new address: ";
            cin >> retrieve_customer.customer_address;

            cout << "Enter the new balance: ";
            cin >> retrieve_customer.customer_balance;

            read_write_file.seekp(-sizeof(retrieve_customer), ios::cur);
            read_write_file.write(reinterpret_cast<char *>(&retrieve_customer), sizeof(retrieve_customer));

            break;
        }
    }

    read_write_file.close();

    if (found)
    {
        cout << "Customer record with ID " << id << " has been changed." << endl;
    }
    else
    {
        string hash; 
        cout<<"\t\tA customer with that Id number doesnt exist.Do you want to try again?\n"
            <<"\t\t If yes 1 or another key to cancle"<<endl;
        cin >> hash;
        if(!hash.compare("1"))
        goto reenter;
    }
}
void display_all(){
    int count = 0;
    Customer retrieve_customer;
    ifstream read_file("customers.dat", ios::binary);
    system("cls");
    while (read_file.read(reinterpret_cast<char *>(&retrieve_customer), sizeof(retrieve_customer)))
    {
        cout << "_____________________________________________________" << endl;
        cout << "customer id = " << retrieve_customer.customer_id << endl;
        cout << "customer name = " << retrieve_customer.customer_name << endl;
        cout << "customer address = " << retrieve_customer.customer_address << endl;
        cout << "customer balance = " << retrieve_customer.customer_balance << endl;
        cout << "_____________________________________________________" << endl;
        count++;
    }
    read_file.close();
    cout<<"A total of "<<count<<" customers  have already been registerd!"<<endl;
};

void group_members(){
    cout << "\t\t\t\t\tC++ GROUP ASSIGNMENT" << endl;
    cout << "__________________________________________________________________________________________" << endl;
    cout << "|                                                                                          |" << endl;
    cout << "|\t\t\t\t\t LIST OF GROUP MEMBERS \t\t\t\t   |" << endl;
    cout << "|__________________________________________________________________________________________|" << endl;
    cout << "|                                                                                          |" << endl;
    cout << "|\tNo.\t\t\tFull Name\t\t\t\t Id-Number\t   |" << endl;
    cout << "|__________________________________________________________________________________________|" << endl;
    cout << "|                                                                                          |" << endl;
    cout << "|\t1.\t\t\tKiflom Berihu Abay\t\t\t Eitm\\ur170302\\12  |" << endl;
    cout << "|                                                                                          |" << endl;
    cout << "|\t1.\t\t\tKiflom Berihu Abay\t\t\t Eitm\\ur170302\\12  |" << endl;
    cout << "|                                                                                          |" << endl;
    cout << "|\t1.\t\t\tKiflom Berihu Abay\t\t\t Eitm\\ur170302\\12  |" << endl;
    cout << "|                                                                                          |" << endl;
    cout << "|\t1.\t\t\tKiflom Berihu Abay\t\t\t Eitm\\ur170302\\12  |" << endl;
    cout << "|                                                                                          |" << endl;
    cout << "|__________________________________________________________________________________________|" << endl;
    string hash;
    cout << "Press 1 key to continue to the project: " << endl;
    cin >> hash;
    while (hash.compare("1")){
        cout << "please try again!" << endl;
        cin >> hash;
    }
}
