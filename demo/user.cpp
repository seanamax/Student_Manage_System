//
// Created by Chris on 17/3/28.
//

#include "user.h"
#include "db.h"
#include "db_connection_pool.h"
#include <memory>
#include <string>
#include <assert.h>

namespace NaiNa
{
    class already_exist_account_exception : public std::exception {
        const char* what() const noexcept {
            return "already_exist_account_exception";
        }
    };

    class account_noexist_exception : public std::exception {
        const char* what() const noexcept {
            return "account_noexist_exception";
        }
    };

    class account_uncheck_exception : public std::exception {
        const char* what() const noexcept {
            return "account_uncheck_exception";
        }
    };

    class account_passwd_incorrection_exception : public std::exception {
        const char* what() const noexcept {
            return "account_passwd_incorrection_exception";
        }
    };

    class account_already_set_exception : public std::exception {
        const char* what() const noexcept {
            return "account_already_set_exception";
        }
    };
//
//    bool user::check_user_standard(const USER_STANDARD &ustd) const {
//        if(!account_update_from_db_) {
//            return account_update_from_db_();
//        }
//
//        return ustd == user_standard_;
//    }
//
//    const USER_STANDARD user::user_standard() const {
//        if(!account_update_from_db_) {
//            throw account_uncheck_exception();
//        }
//
//        return user_standard_;
//    }
//
//    bool user::check_passwd(const std::string& passwd) const {
//        if(!account_update_from_db_) {
//            throw account_uncheck_exception();
//        }
//
//        return passwd == passwd_;
//    }

    void user::set(const std::string &id) {
        std::lock_guard<std::mutex> lock(m_);
        if(account_update_from_db_) {
            throw account_already_set_exception();
        }

        id_ = id;
        get_account_from_db_by_id();
        account_update_from_db_ = true;
    }



    void user::get_account_from_db_by_id() {

        std::unique_ptr<db> db_ptr = std::move(db_connection_pool::instance()->connection());

        std::string query_string = "SELECT Ano Id, Passwd, Prority FROM Account WHERE Ano=";
        query_string += "\"" + id() + "\";";

        auto res = db_ptr->query(query_string);
        auto res_row = db_ptr->fetch_row(res);
        if(res_row) {
            id_ = res_row[0];
            passwd_ = res_row[1];
            user_standard_ = db_account_prority_to_enum_USER_STANDARD(res_row[2]);
        }

        else {
            db_connection_pool::instance()->release_connection(std::move(db_ptr));
            throw account_noexist_exception();
        }

        db_connection_pool::instance()->release_connection(std::move(db_ptr));
    }


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

    const std::string user::id() const {
        return id_;
    }
}
