
#include "reminder.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class ReminderDAO {
    private:
        sql::Connection *con;
        void print_logs(sql::SQLException e){
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line "  << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }
    public: 
        ReminderDAO(){};
        virtual ~ReminderDAO(){};
        void init();
        void create(Reminder *reminder);
        Reminder* getAll (int &count);
        Reminder* get (int id);
        void update (int id, Reminder *reminder);
        void close(); 
};
