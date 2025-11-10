#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql/QSqlDatabase>

class Connection
{
public:
    static Connection* instance();
    bool createConnect();
    void closeConnect();

private:
    Connection(); // Private constructor to prevent external instantiation
    ~Connection(); // Private destructor
    Connection(const Connection&) = delete; // Delete the copy constructor
    Connection& operator=(const Connection&) = delete; // Delete the assignment operator
    
    static Connection *p_instance; // Pointer to the unique instance
    QSqlDatabase db; // Database instance
};

#endif // CONNECTION_H
