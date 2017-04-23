//
// Created by Chris on 17/3/28.
//

#include "user.h"
#include "db.h"
#include "db_connection_pool.h"
#include <memory>
#include <string>
#include <cstring>
#include <assert.h>
#include <iostream>
#include "db_connection_guard.h"

namespace NaiNa
{
    // 加锁操作， 因为返回用户等级过程中，有可能被修改。
    bool user::check_user_standard(const USER_STANDARD &ustd) {
        std::lock_guard<std::mutex> lock_guard(m_);
        if(!account_update_from_db_) {
            throw account_unset_exception();
        }

        return ustd == user_standard_;
    }

    // 加锁操作， 因为检查密码过程中，有可能被修改。
    bool user::check_passwd(const std::string& passwd) {
        std::lock_guard<std::mutex> lock(m_);
        if(!account_update_from_db_) {
            throw account_unset_exception();
        }

        return passwd == passwd_;
    }

    // 加锁操作， 返回用户等级过程中，有可能被修改
    const USER_STANDARD user::user_standard() {
        std::lock_guard<std::mutex> lock(m_);
        if(!account_update_from_db_) {
            throw account_unset_exception();
        }

        return user_standard_;
    }

    // 加锁操作， 返回用户id，有可能被修改
    const std::string& user::id() {
        std::lock_guard<std::mutex> lock(m_);
        if(!account_update_from_db_) {
            throw account_unset_exception();
        }

        return id_;
    }

    // 设置用户，从数据库中更新该用户，若更新失败，则抛出异常
    // 加锁操作，防止修改过程其他线程操作造成数据异常。
    void user::set(const std::string &id) {
        std::lock_guard<std::mutex> lock(m_);
        if(account_update_from_db_) {
            throw account_already_set_exception();
        }

        id_ = id;
        get_account_from_db_by_id();
        account_update_from_db_ = true;
        std::cout << "user::set::" << id_ << "  " << passwd_ << std::endl;
    }

    // 设置新账号，并且同步到数据库中，若数据库已存在该账户，则抛出异常。
    // 加锁操作，防止修改过程其他线程操作造成数据异常。
    void user::set_new_user(const std::string &id,
                            const std::string &passwd,
                            const USER_STANDARD &ustd) {
        std::lock_guard<std::mutex> lock(m_);

        if(account_update_from_db_) {
            throw account_already_set_exception();
        }

        id_ = id;
        passwd_ = passwd;
        user_standard_ = ustd;

        new_account_to_db();
        account_update_from_db_ = true;
    }


    // 更新密码，并且同步到数据库中。
    // 加锁操作，防止修改过程其他线程操作造成数据异常。
    bool user::update_passwd(const std::string &origin_passwd,
                             const std::string &changed_passwd) {
        std::lock_guard<std::mutex> lock(m_);

        // 检查账号是否从数据库中更新
        if(!account_update_from_db_) {
            throw account_unset_exception();
        }

        // 原密码不对，修改密码失败
        if(origin_passwd != passwd_) {
            return false;
        }

        passwd_ = changed_passwd;
        update_account_to_db();

        return true;
    }


    // 从数据库中获得该账号信息，多线程操作由上层函数调用保证，该函数并不能保证并发安全。
    void user::get_account_from_db_by_id() {
        db_connection_guard db_con_guard(std::move(db_connection_pool::instance()->connection()));

        std::string query_string = "SELECT Ano Id, Passwd, Prority FROM Account WHERE Ano=";
        query_string += "\"" + id() + "\";";


        auto res = db_con_guard().query(query_string);
        auto res_row = db_con_guard().fetch_row(res);


        if(res_row) {
            id_ = res_row[0];
            passwd_ = res_row[1];
            user_standard_ = db_account_prority_to_enum_USER_STANDARD(res_row[2]);
        }

        else {
            throw account_noexist_exception();
        }

    }

    // 将数据库中账号等级转换成用户等级。
    USER_STANDARD user::db_account_prority_to_enum_USER_STANDARD(char *pro) {
        int prority = 0;

        assert(pro && "the para is NULL");
        prority = atoi(pro);                // 转换字符串

        switch(prority) {
            case 0:
                return USER_STANDARD::ADMIN;

            case 1:
                return USER_STANDARD::TEANCHER;

            case 2:
                return USER_STANDARD::STUDENT;

            default:
                return USER_STANDARD::NONE;

        }
    }

    // 将用户等级 转换成数据库账号等级。
    std::string user::enum_USER_STANDARD_to_db_account_prority(const USER_STANDARD &ustd) {
        switch(ustd) {
            case USER_STANDARD::ADMIN:
                return "0";

            case USER_STANDARD::TEANCHER:
                return "1";

            case USER_STANDARD::STUDENT:
                return "2";

            case USER_STANDARD::NONE:
            default:
                throw USER_STANDARD_incorrect_exception();
        }
    }


    // 将存储的用户同步到数据库中去。
    // 该操作并不能保证并发操作安全，由上层函数调用保证。
    void user::new_account_to_db() {
        bool flag_already_exist_account = false;

        // 尝试账号是否存在， 若不存在则捕获异常， 写入账号
        try {
            get_account_from_db_by_id();
            flag_already_exist_account = true;
        }

        catch(account_noexist_exception &e) {
            db_connection_guard db_con_guard(std::move(db_connection_pool::instance()->connection()));

            std::string account_prority = enum_USER_STANDARD_to_db_account_prority(user_standard_);
            std::string query_str = "INSERT Account(Ano, Passwd, Prority) ";
            query_str += "VALUE(\"" + id_ + "\", \"" + passwd_ + "\", \"" + account_prority + "\");";
            db_con_guard().query(query_str);
            account_update_from_db_ = true;
        }


        if(flag_already_exist_account) {
            // 账号已经存在，直接抛出异常
            throw already_exist_account_exception();
        }
    }

    // 将存储的用户更新到数据库中去
    // 该操作并不能保证并发操作的安全，由上层函数调用保证。
    void user::update_account_to_db() {
        db_connection_guard db_con_guard(std::move(db_connection_pool::instance()->connection()));

        std::string account_prority = enum_USER_STANDARD_to_db_account_prority(user_standard_);
        std::string query_str = "UPDATE Account SET Passwd = ";
        query_str += "\"" + passwd_ + "\", Prority = \"" + account_prority + "\" WHERE Ano=\"";
        query_str += id_ + "\";";
        db_con_guard().query(query_str);
    }
}
