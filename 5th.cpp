#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class database{
    string name;
    int rn;
    
    public:
    
    database(){
        this->name = "";
        this->rn = 0;
    }
    
    void input(string file_path = ""){
        fstream of(file_path,ios::out|ios::in|ios::app|ios::binary);
        int n;
        cout<<"\nHow many students you want in your database ? ";
        cin>>n;
        int i =0;
        database *db ;
        db = new database[n];

        while (i<n)
        {   cout<<"\nEnter name of student: ";
            cin.ignore();
            getline(cin,name);
            of<<"Name is: "<<name;

            cout<<"\nEnter roll number of student: ";
            cin>>rn;
            of<<"     Roll number is: "<<rn<<endl;
            i++;
        }
        of.close();   
    }

    void output(string file_path = ""){
        ifstream ifs(file_path,ios::binary);
        if(!ifs){
        cout<<"\nError opening the file";
        return;}
        string line;
        while(getline(ifs,line)){
            cout<<line<<endl;
        }
        ifs.close();
    }

    void write(string file_path = ""){
        ofstream myfile(file_path,ios::app|ios::binary);

        if(!myfile) {
        cout << "Error: Unable to open the file." << endl;
        return ; 
        }
        cout<<"\nEnter if you want to add additional text!";
        string mytxt;
        cin.ignore();
        getline(cin,mytxt);
        myfile<<mytxt<<endl;
    }

    void add_text_update(string file_path=""){
        int find;
        cout<<"\nWhat line number do you want to update";
        cin>>find;

        fstream file(file_path,ios::in|ios::out|ios::app|ios::binary);
        if(!file)
        {
            cout<<"\nCould not open the file: ";
            return;
        }
        string line;
        int current_line = 1;
        int position = 0;

        while(current_line<find && getline(file,line)){
            position = file.tellg();
            current_line++;
        }

        cout<<"\nCurrent line: "<<line <<endl;
        cout << "\nEnter new content for line " << find << ": ";
        cin.ignore();
        string new_line;
        getline(cin,new_line);

        file.seekp(position - line.length()-1);
        file<<endl<<new_line<<endl;

        cout << "Line " << find << " updated successfully!" << endl;

        file.close();
    }

    void update_details(string file_path=""){
        int target_rn ;
        cout << "\nEnter the roll number of the student you want to update: ";
        cin>>target_rn;

        fstream file(file_path,ios::in|ios::out|ios::app|ios::binary);
        if (!file) {
            cout << "\nCould not open the file.";
            return;
        }
        vector<string> lines;
        string line;
        int position;
        bool found = false;

        while(getline(file,line)){
            if (line.find("Roll number is: " + to_string(target_rn)) != string::npos) {
                found = true;

                cout << "\nEnter the updated name: ";
                cin.ignore();
                string new_name;
                getline(cin, new_name);

                cout << "\nEnter the updated roll number: ";
                int new_rn;
                cin >> new_rn;

                lines.push_back("Name is: " + new_name + "     Roll number is: " + to_string(new_rn));
            } else {
                lines.push_back(line);
            }
        }
        if (found) {
            ofstream file_out(file_path, ios::trunc);
            for (const auto& updated_line : lines) {
                file_out << updated_line << endl;
            }
            file_out.close();

            cout << "\nDetails updated successfully.";
        } else {
            cout << "\nStudent with roll number " << target_rn << " not found.";
        }
    }

};

class choice{
    int x;
    public:
    void choose(){
        database db;
        string file_path = "database.txt";
        cout<<"\nWhich operation you want to perform on the file: \n1. Write to the file \n 2.Write student to the file \n 3.Read the file \n 4. Update the file \n5.Update details of student \n6.Exit";
        cin>>x;
        switch(x){
            case 1:{
                db.write(file_path);
                break;
            }
            case 2:{
                db.input(file_path);
                break;
            }
            case 3:{
                db.output(file_path);
                break;
            }
            case 4:{
                db.add_text_update(file_path);
                break;
            }
            case 5:{
                db.update_details(file_path);
                break;
            }
            case 6:{
                cout<<"\n\nProcess ended";
                return;
            }

        }
    }

};

int main(){
    
    choice ch;
    ch.choose();

    char chx;
    cout<<"\nDo you want to continue this process y or n? ";
    cin>>chx;
    if(chx=='y')
    ch.choose();
    else
    return 0;
    }
