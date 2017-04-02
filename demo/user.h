//
// Created by Chris on 17/3/28.
//

#ifndef STUDENT_MANAGE_SYSTEM_USER_H
#define STUDENT_MANAGE_SYSTEM_USER_H

#include <string>
#include <mutex>

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

    class account_unset_exception : public std::exception {
        const char* what() const noexcept {
            return "account_unset_exception";
        }
    };


    class account_already_set_exception : public std::exception {
        const char* what() const noexcept {
            return "account_already_set_exception";
        }
    };


    class USER_STANDARD_incorrect_exception : public std::exception {
        const char* what() const noexcept {
            return "USER_STANDARD_incorrect_exception";
        }
    };

    enum class USER_STANDARD {
        NONE = 0,
        ADMIN = 1,
        TEANCHER = 2,
        STUDENT = 3,
    };


    class user {
    // function
    public:

        user() :
                user_standard_(USER_STANDARD::NONE),
                account_update_from_db_(false)
        {}

        // 并发操作安全
        // 设置用户，从数据库中同步账号信息
        void set(const std::string& id);

        // 并发操作安全
        // 产生新用户，账号信息插入数据库中
        void set_new_user(const std::string& id, const std::string& passwd, const USER_STANDARD& ustd);

        // 并发操作安全
        // 检查密码
        bool check_passwd(const std::string& passwd) const;

        // 并发操作安全
        // 更新密码
        bool update_passwd(const std::string& origin_passwd, const std::string& changed_passwd);

        // 并发操作安全
        // 获得账号
        const std::string& id() const;

        // 并发操作安全
        // 检查用户等级
        bool check_user_standard(const USER_STANDARD& user_standard) const;

        // 并发操作安全
        // 返回用户等级
        const USER_STANDARD user_standard() const;


    private:
        void get_account_from_db_by_id();
        void update_account_to_db();

        // 插入新账号到数据库中去
        void new_account_to_db();

        // 数据库账号表账户等级转换成枚举用户类型。
        USER_STANDARD db_account_prority_to_enum_USER_STANDARD(char*);

        // 枚举类型用户等级转换成数据库账号表账号等级
        std::string enum_USER_STANDARD_to_db_account_prority(const USER_STANDARD& ustd);
    // data
    public:
    //private:
        USER_STANDARD user_standard_;
        std::string id_;
        std::string passwd_;
        std::mutex m_;
        bool account_update_from_db_;
    };
}

#endif //STUDENT_MANAGE_SYSTEM_USER_H
