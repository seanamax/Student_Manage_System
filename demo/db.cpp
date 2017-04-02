//
// Created by Chris on 17/3/23.
//

#include "db.h"
#include <iostream>


namespace NaiNa
{

    bool db::init(const std::string& db,
                  const std::string& address,
                  const port_type& port,
                  const std::string& name,
                  const std::string& passwd) {
        db_ = db;
        address_ = address;
        port_ = port;
        name_ = name;
        passwd_ = passwd;

        mysql_library_init(NULL, 0, 0);

        mysql_init(&mysql_);

        if(0 == mysql_set_character_set(&mysql_, "utf8")) {
            std::cout << "设置 utf-8 字符集成功!" << std::endl;
        }

        if(!mysql_real_connect(&mysql_, address_.c_str(),
                               name_.c_str(),passwd_.c_str(),
                               db_.c_str(), port_,
                               nullptr, CLIENT_MULTI_STATEMENTS)) {

            std::cout << "Cann't connect mysql." << std::endl;
            closed_ = true;
        }

        else {
            std::cout << "welcome to mysql!" << std::endl;
            closed_ = false;
        }

        return !closed_;
    }


    void db::clear() noexcept {
        if(!closed_) {
            mysql_close(&mysql_);
            mysql_server_end();
            mysql_library_end();

            db_ = "";
            address_ = "";
            name_ = "";
            passwd_ = "";
            port_ = 0;

            closed_ = true;
        }
    }


    db::~db() noexcept {
        clear();
    }


    bool db::reset_and_init(const std::string& db,
                            const std::string& address,
                            const port_type& port,
                            const std::string& name,
                            const std::string& passwd) {
        clear();
        return init(db, address, port, name, passwd);
    }


    std::shared_ptr<MYSQL_RES> db::query(const std::string& que) {

        // mysql_query() 返回值非 零， 查询失败， 抛出异常
        if(mysql_query(&mysql_, que.c_str())) {
            throw db_SQL_query_error_exception();

        }
        std::shared_ptr<MYSQL_RES> res(mysql_store_result(&mysql_), mysql_free_result);
        return res;
    }

    std::shared_ptr<MYSQL_RES> db::query(const std::string& que, const std::string& para) {
        std::shared_ptr<char> str(new char[char_buffer_length], [](char *p){delete[] p;});
        sprintf(str.get(), que.c_str(), para.c_str());

        //  my_query() 返回值非 零， 查询失败， 抛出异常
        if(mysql_query(&mysql_, str.get())) {
            throw db_SQL_query_error_exception();
        }

        std::shared_ptr<MYSQL_RES> res(mysql_store_result(&mysql_), mysql_free_result);
        return res;
    }


    unsigned int db::num_field(std::shared_ptr<MYSQL_RES>& ptr) {
        return mysql_num_fields(ptr.get());
    }

    my_ulonglong db::num_rows(std::shared_ptr<MYSQL_RES>& ptr) {
        return mysql_num_rows(ptr.get());
    }

    MYSQL_ROW db::fetch_row(std::shared_ptr<MYSQL_RES>& ptr) {
        return mysql_fetch_row(ptr.get());
    }

    MYSQL_FIELD* db::fetch_field_direct(std::shared_ptr<MYSQL_RES>& ptr, int& column) {
        return mysql_fetch_field_direct(ptr.get(), column);
    }
}