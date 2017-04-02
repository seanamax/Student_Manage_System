//
// Created by Chris on 17/4/1.
//

#ifndef STUDENT_MANAGE_SYSTEM_DB_CONNECTION_GUARD_H
#define STUDENT_MANAGE_SYSTEM_DB_CONNECTION_GUARD_H


#include "db.h"
#include "db_connection_pool.h"
#include <memory>

namespace NaiNa
{
    class db_connection_guard {

    public:
        db_connection_guard(std::unique_ptr<db> db_ptr);

        db& operator()();

        ~db_connection_guard();

    private:
        std::unique_ptr<db> db_ptr_;
    };
}


#endif //STUDENT_MANAGE_SYSTEM_DB_CONNECTION_GUARD_H
