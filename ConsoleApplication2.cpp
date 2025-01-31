#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
#include<stdio.h>
using namespace std;
struct contact {
    char name[200];
    char num[200];
    char email[200];


    string getName() { return name; }
   
    string getNum() { return num ; }
    string getEmail() { return email; }
    void getdata() {
        cout << " *CREATE NEW PHONE RECORD*" << endl;
        cout << "Enter Contact Name: ";
        cin.ignore();
        cin.getline(name, 200);

        cout << "Enter mobile number: ";
        cin.getline(num , 200);

        cout << "Enter E-mail ID:  ";
        cin.getline(email, 200);
    }
    void showdata() {
        cout << "PHONE BOOK RECORD" << endl;
        cout << "Name       : " << name << endl;
        cout << "phone Num. : " << num << endl;
        cout << "Email add   : " << email << endl;

    }


}ph;
void menu();
void addnumber();
void displayrecords();
void search();
void deleterecord();
void modifyrecord();
void deleteall();


void addnumber()
{

    ofstream save;
    ph.getdata();
    save.open("content.dat", ios::out | ios::binary | ios::app);
    save.write((char*)&ph, sizeof(ph));
    save.close();
    
}
void displayrecords()
{
    cout << "**********" << endl;
    ifstream f1;
    f1.open("content.dat", ios::out | ios::binary | ios::app);
    while (f1.read((char*)&ph, sizeof(ph))) { ph.showdata(); }

    f1.close();


}
void search()
{
    int x, y, z;

    ifstream f1;
    string search;
    cout << "**SEARCH FOR CONTACTS**" << endl;
    cout << "Enter Name/num/email: ";
    cin.ignore(); getline(cin, search);
    int flag{ 0 };
    f1.open("content.dat");
    while (f1.read((char*)&ph, sizeof(ph))) {
        x = ph.getName().find(search);
        y = ph.getNum().find(search);
        z = ph.getEmail().find(search);
        if (x > -1 || y > -1 || z > -1) {
            ph.showdata();
            flag++;

        }
    }
    f1.close();
    if (flag == 0)
        cout << "No Contact Found";

}
void deleterecord()
{

    ifstream f1;
    ofstream f2;
    string name;
    int x = 0;
    f1.open("content.dat", ios::binary | ios::out | ios::app);
    f2.open("file.dat", ios::out | ios::binary);
    cout << "Enter Contact Name To Delete : " << endl;
    cin.ignore(); getline(cin, name);

    while (f1.read((char*)&ph, sizeof(ph))) {
        if (name == ph.getName()) {

            cout << "The Following Contact is Deleted..." << endl;
            ph.showdata();
            x++;
        }
        else
            f2.write((char*)&ph, sizeof(ph));
    }
    f1.close();
    f2.close();
    if (x == 0) {

        cout << "The Contact Of  " << name << " not Found";
    }



    remove("content.dat");
    rename("file.dat", "content.dat");
}
void deleteall() {
    remove("content.dat");
    cout << "All contacts deleted" << endl;
    cout << "*********" << endl;

}

void modifyrecord()
{
    ifstream f1;
    ofstream f2;
    string search;
    int x = 0, counter = 0;
    int i, j, k; //for searching on contact
    char choice;
    f1.open("content.dat", ios::binary | ios::out | ios::app);
    f2.open("file.dat", ios::binary | ios::out | ios::binary);
    cout << "Enter Contact Name/Num/email To Modify : " << endl;
    cin.ignore(); getline(cin, search);

    while (f1.read((char*)&ph, sizeof(ph))) {
        i = ph.getName().find(search);
        j = ph.getNum().find(search);
        k = ph.getEmail().find(search);
        if (i > -1 || j > -1 || k > -1) {


            ph.showdata();
            x++;
            cout << "Do you want to modify it?(Y/N)" << endl;
            cin >> choice;
            if (choice == 'N' || choice == 'n') {
                f2.write((char*)&ph, sizeof(ph));
            }
            else if (choice == 'y' || choice == 'Y') {
                counter++;

            }

        }
        else {
            f2.write((char*)&ph, sizeof(ph));
        }
    }
    f1.close();
    f2.close();
    if (x == 0) {

        cout << search << " not Found";
    }


    remove("content.dat");
    rename("file.dat", "content.dat");
    if (x > 0 && choice != 'n' || x > 0 && choice != 'N') {
        for (int l = 0; l < counter; l++) {
            addnumber();
        }
    }
}
void menu()
{
    int z;
    do {
        cout << "*****************\n\n";
        cout << "******Enter Your Choice******\n";
        cout << "0. Exit \n";
        cout << "1. Save New Phone Record\n";
        cout << "2. Display All Saved Reecord\n";
        cout << "3. Search Specific Record\n";
        cout << "4. Delete Specific Record\n";
        cout << "5. Modify Existing Record\n";
        cout << "6. delete all Records\n";
        cout << "Enter Your Choice : ";
        cin >> z;

        switch (z)
        {
        case 1: addnumber(); break;
        case 2:displayrecords(); break;
        case 3: search(); break;
        case 4: deleterecord(); break;
        case 5:modifyrecord(); break;
        case 6:deleteall(); break;
        default:return;

        }
        _getch();

    } while (z);

}
int main() {
    menu();

}
