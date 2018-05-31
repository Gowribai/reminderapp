#include <stdlib.h>
#include <iostream>

#include "reminder_dao.h"

using namespace std;

Reminder* get_reminder(){
      Reminder *reminder = new Reminder();
      cout << "Enter the date in yyyy-mm-dd format (Ex: 2018-05-29) ";
      cin >> reminder->date;
      cin.ignore();

      cout << "Enter the time in HH:MM:SS (24 hr) format (Ex: 13:13:00) ";
      cin >> reminder->time;
      cin.ignore();

      cout << "Enter notes ";
      getline(cin, reminder->notes);
      return reminder;
} 

int main(void)
{

cout << endl;

ReminderDAO *reminderdao = new ReminderDAO();
reminderdao->init();

while(true) {
  cout << "Reminder Application" << endl;
  cout << "1. Create Reminder"  << endl;
  cout << "2. Show All Reminders"  << endl;
  cout << "3. Show Reminder"  << endl;
  cout << "4. Update Reminder"  << endl;
  cout << "5. Quit"  << endl;

  int option;
  cout << "Enter your option ";
  cin >> option;
  cin.ignore(); 
  if(option == 5) break;  
  
  switch(option){
    case 1: {
      reminderdao->create(get_reminder());
      cout << "Reminder created"; 
      break;
    }
    case 2: {
      int count=0;
      Reminder* reminders = reminderdao->getAll(count);
      for(int i=0;i<count;i++){
        reminders->display();
        cout << endl;
        reminders++;
      }
      break;
    }
    case 3: {
      cout << "Enter id ";
      int id;
      cin >> id;
      Reminder* reminder = reminderdao->get(id);
      if(reminder != NULL) reminder->display();
    break;
    }
    case 4: {
      cout << "Enter id ";
      int id;
      cin >> id;
      reminderdao->update(id, get_reminder());
      cout << "Reminder updated"; 
      break;
    }

    default: cout << "Wrong option, try again!!!";
  }
  cout << endl;
  cout << endl;
}

reminderdao->close();
delete reminderdao;

cout << "Exiting Application" << endl;

return EXIT_SUCCESS;
}