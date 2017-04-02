//
// Created by Chris on 17/3/25.
//

#ifndef STUDENT_MANAGE_SYSTEM_DB_CONNECTION_POOL_H
#define STUDENT_MANAGE_SYSTEM_DB_CONNECTION_POOL_H

#include "Types.h"
#include "db.h"
#include "threadsafe_stack.h"
#include <mutex>

namespace NaiNa {

    class db_init_exception : public std::exception {
        const char* what() const noexcept { return "db_init_exception\n"; }
        //explicit db_init_exception() {}
        //explicit db_init_exception(char* str) {}
    };

    class db_connection_pool_no_connection_exception : public std::exception {
        const char* what() const noexcept { return "db_connection_pool_no_connection_exception\n"; };
    };

    class db_connection_pool {

    // functions
    public:

        // delete copy constructor, reference construtor and copy function.
        db_connection_pool(const db_connection_pool&) = delete;
        db_connection_pool(db_connection_pool&&) = delete;
        db_connection_pool& operator=(const db_connection_pool&) = delete;

        // get the instance of db_connection_pool class.
        static db_connection_pool* instance();

        // initilize function which called once by get_instance function.
        bool init(std::string db, std::string addr,
                  port_type port, std::string name,
                  std::string passwd,
                  connection_count_type min_connection = 2,
                  connection_count_type max_connection = 20);

        // get the connection of db in the db_connection_pool.
        std::unique_ptr<db> connection();

        // release the connection of db to the db_connection_poo.
        void release_connection(std::unique_ptr<db>);


        // functions
    private:

        // constructor
        db_connection_pool() noexcept :
                min_connection_(2),
                max_connection_(5),
                current_connection_(0),
                port_(3306),
                db_(),
                address_(),
                name_(),
                passwd_()
        {}

        ~db_connection_pool() noexcept = default;

        // data
    private:
        // set db_connection_pool element of connection.
        connection_count_type min_connection_;
        connection_count_type max_connection_;
        connection_count_type current_connection_;


        // db config file.
        port_type port_;
        std::string db_;
        std::string address_;
        std::string name_;
        std::string passwd_;

        // mutex.
        std::mutex m_;

        threadsafe_stack<std::unique_ptr<db>> db_ptr_stack_;
    };


}

#endif //STUDENT_MANAGE_SYSTEM_DB_CONNECTION_POOL_H
