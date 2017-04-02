//
// Created by Chris on 17/4/1.
//

#include "db_connection_guard.h"
#include <iostream>

namespace NaiNa
{
    db_connection_guard::db_connection_guard(std::unique_ptr<db> db_ptr) {
        db_ptr_ = std::move(db_ptr);
    }

    db& db_connection_guard::operator()() {
        return *db_ptr_;
    }

    db_connection_guard::~db_connection_guard() {
        db_connection_pool::instance()->release_connection(std::move(db_ptr_));
    }
}