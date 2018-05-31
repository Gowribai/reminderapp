#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "reminder_dao.h"

void ReminderDAO::init() {
    sql::Driver *driver;
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "password");
    con->setSchema("reminder");
}

void ReminderDAO::create(Reminder *reminder){
    try {
        sql::PreparedStatement *pstmt = con->prepareStatement("INSERT INTO reminders(date, time, notes) VALUES (?, ?, ?)");
        pstmt->setDateTime(1, reminder->date);
        pstmt->setDateTime(2, reminder->time);
        pstmt->setString(3, reminder->notes);
        pstmt->executeUpdate();
        con->commit();
        delete pstmt;
    } catch (sql::SQLException &e) {
        print_logs(e);
    }
}

Reminder* ReminderDAO::getAll (int &count){
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery("SELECT * FROM reminders");
    count = res->rowsCount();
    int i=0;
    Reminder *reminders = new Reminder[count];
    while (res->next()) {
        reminders[i].id = res->getInt("id");
        reminders[i].date = res->getString("date");
        reminders[i].time = res->getString("time");
        reminders[i].notes = res->getString("notes");
        i++;
    }
    delete res;
    delete stmt;

    return reminders;
}
Reminder* ReminderDAO::get (int id) {
    sql::PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM reminders where id=?");
    pstmt->setInt(1,id);
    sql::ResultSet *res = pstmt->executeQuery();
    Reminder *reminder = NULL;
    if (res->next()) {
        reminder = new Reminder();
        reminder->id = res->getInt("id");
        reminder->date = res->getString("date");
        reminder->time = res->getString("time");
        reminder->notes = res->getString("notes");
    }
    delete res;
    delete pstmt;

    return reminder;
}
void ReminderDAO::update (int id, Reminder *reminder) {
try {
        sql::PreparedStatement *pstmt = con->prepareStatement("UPDATE reminders set date=?, time=?, notes=? where id=?");
        pstmt->setDateTime(1, reminder->date);
        pstmt->setDateTime(2, reminder->time);
        pstmt->setString(3, reminder->notes);
        pstmt->setInt(4, id);
        pstmt->executeUpdate();
        con->commit();
        delete pstmt;
    } catch (sql::SQLException &e) {
        print_logs(e);
    }
}
void ReminderDAO::close()  {
    delete con;
}