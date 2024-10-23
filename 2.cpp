#include <iostream>
#include <vector>
#include <string>

using namespace std;

class database{
    string name;
    int age;
    int rn;
    int phn;
    int dob;
    char div;
    static int count;

    public:
    database(){
    this->name="";
    this->age=0;
    this->rn=0;
    this->phn=0;
    this->dob=0;
    this->div=' ';
    }

    datain(const database& d){
        name = d.name;
        age = d.age;
        dob = d.dob;
        div = d.div;
    }

    void input(){
        cout<<"Enter name: ";
        cin.ignore();
        getline(cin,name);
        cout<<"Enter age: ";
        cin>>age;
        cout<<"Enter phn: ";
       cin>>phn;
        cout<<"Enter rn: ";
        cin>>rn;
        cout<<"Enter dob: ";
        cin>>dob;
        cout<<"Enter div: ";
        cin>>div;
    count++;
    }
    string getname(){return name;}
    int getrn(){return rn;}
    int getphn(){return phn;}
    int getdob(){return dob;}
    char getdiv(){return div;}

    inline void setname(const string &newname){    this->name = newname;}
    inline void setdob(int newDob) { this->dob = newDob; }
    inline void setdiv(char newDiv) { this->div = newDiv; }
    inline void setphn(int newphn) { this->phn = newphn; }

    static void countStudents(){
        cout<<"Total number of count of students is "<<count<<endl;
    }
    friend class stored;
    friend class menu;
};

class stored{
vector<database* >dt;
public:
void get(){
    int n;
    cout<<"Students in your database: ";
    cin>>n;
    for(int i=0;i<n;i++){
        database* st = new database;
        st->input();
        dt.push_back(st);
    }
}
void output(){
    for(database* student:dt){
        cout << "Name of student is:"<<student->name << "\nRoll number of student is: " << student->rn << " \nAge of student is:"
                 << student->age << "\nDivision of student is: " << student->div   << "\nPhone number of student is: "
                 << student->phn << "\nDate of birth of student is: "<<student->dob<<endl;
        }
}
database* findStudent(int rn){
    for(database* st:dt)
    if(st->getrn()==rn)
    return st;

return NULL;
}
void deleteStudent(int rn) {
    for(auto it = dt.begin(); it != dt.end(); ++it) {
        if((*it)->getrn() == rn) {
            delete *it;  
            dt.erase(it);  
            return;  
        }
    }
}
friend class menu;
};

int database ::count = 0 ;

class menu{
    int choice;
    stored st;
    public:
  void choose(){
 while(true)
   { 
    
        cout << "\nWhich operation do you want to perform?";
        cout << "\n1. Input students \n2. Output students \n3. Delete student \n4. Count number of students \n5. Update data of student \n6. Exit" << endl;
        cin >> choice;
        switch(choice){
            case 1:
            st.get();
            break;

            case 2:
            st.output();
            break; 

            case 3:
            int rn;
            cout<<"Enter rn to be deleted: ";
            cin>>rn;
           
            st.deleteStudent(rn) ;
            break ;


            case 4:
            database::countStudents();
            break;
        }
    }}


};

int main(){
menu menudriven;
menudriven.choose();


}
