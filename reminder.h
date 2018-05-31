#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Reminder {
    public:
        int id;
        string date;
        string time;
        string notes;
        Reminder(){}
        void display(){
            cout << "Id: " << id << endl;
            cout << "Date: " << date << endl;
            cout << "Time: " << time << endl;
            cout << "notes: " << notes << endl;
        }
};
