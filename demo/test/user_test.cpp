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
    shared_ptr<test_init> init(new test_init);
    init->init();

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
    test_init init;
    init.init();

    user u;
    string id = "nihao";
    string passwd = "ahaha";
    USER_STANDARD ustd = USER_STANDARD::STUDENT;

    u.set_new_user(id, passwd, ustd);
}

TEST(user_test, test_update_passwd)
{
    test_init init;
    init.init();

    user u,v;
    string id="nihaoa";
    string origin_passwd = "ahaha";
    string changed_passwd = "nihao";
    u.set_new_user(id, origin_passwd, USER_STANDARD::TEANCHER);

    u.update_passwd(origin_passwd, changed_passwd);
    v.set("Admin");
}

TEST(user_test, test_check_passwd)
{
    test_init init;
    init.init();

    user u;
    string id="Admin";
    u.set(id);

    bool update_passwd_flag = u.update_passwd("0", "buhao");
    EXPECT_EQ(update_passwd_flag, true);

//    user v;
//    v.update_passwd("ni", "w");
}