//
// Created by Chris on 17/3/23.
//

#ifndef STUDENT_MANAGE_SYSTEM_DB_H
#define STUDENT_MANAGE_SYSTEM_DB_H

#include "Types.h"
#include <string>
#include <memory>
#include "mysql.h"

namespace NaiNa
{

    class db_SQL_query_error_exception : public std::exception {
        const char* what() const noexcept { return "db_SQL_query_error_exception"; };
    };

    class db
    {
    // function
    public:
        bool init(const std::string& db,
                  const std::string& address,
                  const port_type& port,
                  const std::string& name,
                  const std::string& passwd);

        db() noexcept :
                port_(0),
                db_(""),
                address_(""),
                name_(""),
                passwd_(""),
                closed_(true)
        {}

        std::shared_ptr<MYSQL_RES> query(const std::string& que);
        std::shared_ptr<MYSQL_RES> query(const std::string& que, const std::string& para);

        void clear() noexcept;

        bool reset_and_init(const std::string& db,
                            const std::string& address,
                            const port_type& port,
                            const std::string& name,
                            const std::string& passwd);


        unsigned int num_field(std::shared_ptr<MYSQL_RES>&);

        my_ulonglong num_rows(std::shared_ptr<MYSQL_RES>&);

        MYSQL_ROW fetch_row(std::shared_ptr<MYSQL_RES>&);

        MYSQL_FIELD* fetch_field_direct(std::shared_ptr<MYSQL_RES>&, int&);

        ~db() noexcept;

        //
        //
        //
        db(const db&) = delete;
        db(db &&) = delete;
        db& operator=(const db&) = delete;


    // data
    private:
        port_type port_;
        std::string db_;
        std::string address_;
        std::string name_;
        std::string passwd_;
        bool closed_;

        MYSQL mysql_;

        typedef unsigned int char_buffer_type;
        const char_buffer_type char_buffer_length = 1024;
    };

}


#endif //STUDENT_MANAGE_SYSTEM_DB_H
