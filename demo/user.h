//
// Created by Chris on 17/3/28.
//

#ifndef STUDENT_MANAGE_SYSTEM_USER_H
#define STUDENT_MANAGE_SYSTEM_USER_H

#include <string>
#include <mutex>

namespace NaiNa
{
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

        void set(const std::string& id);
//        void set_new_user(const std::string& id, const std::string& passwd, const USER_STANDARD& ustd);
//        bool check_passwd(const std::string& passwd) const;
//        bool update_passwd(const std::string& origin_passwd, const std::string& changed_passwd);
        const std::string id() const;
//        bool check_user_standard(const USER_STANDARD& user_standard) const;
//        const USER_STANDARD user_standard() const;


    private:
        void get_account_from_db_by_id();
//        void update_account_to_db();
        USER_STANDARD db_account_prority_to_enum_USER_STANDARD(char*);

    // data
    //public:
    private:
        USER_STANDARD user_standard_;
        std::string id_;
        std::string passwd_;
        std::mutex m_;
        bool account_update_from_db_;
    };
}

#endif //STUDENT_MANAGE_SYSTEM_USER_H
