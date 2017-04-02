//
// Created by Chris on 17/3/30.
//

#ifndef STUDENT_MANAGE_SYSTEM_TEST_INIT_H
#define STUDENT_MANAGE_SYSTEM_TEST_INIT_H

#include "../db_connection_pool.h"
#include "../Types.h"
#include <string>

namespace NaiNa {

    class test_init {

    // function
    public:
        void init();
        void init_db_connection_pool();
        test_init();

    // data
    private:

        // init db_connection_pool parameter.
        std::string db_name_;
        std::string db_addr_;
        port_type db_port_;
        std::string db_user_name_;
        std::string db_passwd_;

    };

}


#endif //STUDENT_MANAGE_SYSTEM_TEST_INIT_H
