//
// Created by Chris on 17/3/23.
//

#ifndef STUDENT_MANAGE_SYSTEM_TEST_DEMO_H
#define STUDENT_MANAGE_SYSTEM_TEST_DEMO_H

#include <string>
#include <memory>
#include "Types.h"


namespace manage_stduent_info
{


    class user
    {
    public:
        user();
        ~user();

        bool login();

        ///
        /// set id and passwd to user,
        ///
        void set_user_id_passwd(std::string id, std::string passwd);

        // 注销
        void sign_out();

        // 注册
        void sign_in(string );

        bool check_passwd(std::string);
        bool update_passwd(std::string, std::string);
        bool update_passed(std::string);

    private:

        void update_passwd_to_db();

        bool check_out_id_and_passwd_from_db();



        std::string id_;
        std::string passwd_;
        counttime count_login_time_;
        bool success_login_flag_;

    protected:

    };



    class teacher : public user
    {

    };


    class stduent : public user
    {

    };

    class admin : public user
    {

    };

}


#endif //STUDENT_MANAGE_SYSTEM_TEST_DEMO_H
