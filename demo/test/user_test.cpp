//
// Created by Chris on 17/3/29.
//

#include "gtest/gtest.h"
#include "../user.h"
#include "test_init.h"
#include "../Types.h"
#include <string>
#include <cstdio>

using namespace std;
using namespace NaiNa;

TEST(user_test, test_set)
{
//    test_init init;
//    init.init();


    string _db = "Student_Info";
    string addr = "localhost";
    port_type port = 3306;
    string name = "root";
    string passwd = "2718big.a";


    bool init_flag = db_connection_pool::instance()->init(_db, addr, port, name, passwd,2,100);
    EXPECT_EQ(init_flag, true);

    user u;
    string id = "Admin";
    u.set(id);
//    cout << u.id() << endl;
//    cout << u.passwd_ << endl;
//    //cout << u.user_standard_ << endl;
//    printf("%u\n", u.user_standard_);
//    //EXPECT_EQ(2, 3);
}

TEST(user_test, test_new_account_set)
{

}