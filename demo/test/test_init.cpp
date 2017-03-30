//
// Created by Chris on 17/3/30.
//

#include "test_init.h"


namespace NaiNa {
    void test_init::init() {
        init_db_connection_pool();
    }


    void test_init::init_db_connection_pool() {
        db_connection_pool::instance()->init(db_name_, db_addr_, db_port_, db_user_name_, db_passwd_);
        //db_connection_pool::instance()->init(_db, addr, port, name, passwd,2,200);
    }

    test_init::test_init() {

        // init db_connection_pool parameter.
        db_name_ = "Stduent_Info";
        db_addr_= "localhost";
        db_port_ = 3306;
        db_user_name_ = "root";
        db_passwd_ = "2718big.a";

    }
}

