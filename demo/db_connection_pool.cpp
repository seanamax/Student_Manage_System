//
// Created by Chris on 17/3/25.
//

#include "db_connection_pool.h"
#include "db.h"
#include <exception>
#include <iostream>

namespace NaiNa {

    db_connection_pool* db_connection_pool::instance() {
        static db_connection_pool db_con_pool;
        return &db_con_pool;
    }

    bool db_connection_pool::init(std::string _db, std::string addr, port_type port, std::string name,
                                  std::string passwd, connection_count_type min_connection,
                                  connection_count_type max_connection) {

        db_ = _db;
        address_ = addr;
        port_ = port;
        name_ = name;
        passwd_ = passwd;
        min_connection_ = min_connection;
        max_connection_ = max_connection;
        current_connection_ = 0;

        std::unique_ptr<db> p;
        for(int i=0; i < min_connection_; ++i) {
            p.reset(new db());
            if(!p->init(db_,address_,port_,name_,passwd)) {
                return false;
            }
            db_ptr_stack_.push(std::move(p));
        }

        return true;
    }

    std::unique_ptr<db> db_connection_pool::connection() {

        std::lock_guard<std::mutex> lock(m_);

        std::unique_ptr<db> db_ptr;
        try {
            db_ptr = std::move(*db_ptr_stack_.pop());
            ++ current_connection_;
        }
        catch (stack_empty& e) {

            std::cout << e.what() << std::endl;

            if(current_connection_ < max_connection_) {
                db_ptr.reset(new db());
                if(!db_ptr->init(db_,address_,port_,name_,passwd_)) {
                    throw db_connection_pool_no_connection_exception();
                }
                else {
                    ++ current_connection_;
                    //return db_ptr;
                }

            }

            else {
                throw db_connection_pool_no_connection_exception();
            }
        }
        return db_ptr;
    }

    void db_connection_pool::release_connection(std::unique_ptr<db> db_ptr) {

        std::lock_guard<std::mutex> lock(m_);

        db_ptr_stack_.push(std::move(db_ptr));
        -- current_connection_;
    }
}