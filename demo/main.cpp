//
// Created by Chris on 17/3/20.
//

#include <cstdio>
#include <iostream>
//#include "gtest.h"
#include "mysql.h"
#include <stack>

using namespace std;


bool testMysqlAPI()
{
    mysql_library_init(NULL, 0, 0);
    MYSQL mysql;
    mysql_init(&mysql);

    if(0 == mysql_set_character_set(&mysql, "utf8")) {
        cout << "设置 utf-8 字符集成功!" << endl;
    }

    if(!mysql_real_connect(&mysql, "localhost",
                           "root","2718big.a", "Student_Info", 3306,
                           nullptr, CLIENT_MULTI_STATEMENTS)) {

        cout << "Cann't connect mysql." << endl;
    }

    else {
        cout << "welcome to mysql!" << endl;
    }

    mysql_query(&mysql, "SELECT Sno ID, Sname Name, Ssex Sex, Sbirth Birthday FROM Student;");
    MYSQL_RES *result = mysql_store_result(&mysql);
    int row_num = mysql_num_rows(result);
    unsigned int field_count = mysql_num_fields(result);

    MYSQL_FIELD *field = NULL;
    MYSQL_ROW row = NULL;
    while(row = mysql_fetch_row(result)) {
        for(int i=0; i < field_count; ++i) {
            field = mysql_fetch_field_direct(result, i);
            cout << field->name << ":" << row[i] << endl;
        }
    }

    mysql_free_result(result);
    mysql_close(&mysql);
    mysql_server_end();
    mysql_library_end();

    return 0;
}




//TEST(test, test_ahaha)
//{
//    EXPECT_EQ(1, 2) << '1 is not equal to 2";
//}



//
//
//int main(void)
//{
//    cout << "demo" << endl;
//    //testMysqlAPI();
////
////    auto int_ptr = make_shared<shared_ptr<nullptr>>();
////    cout << int_ptr.use_count() << endl;
////    cout << int_ptr << endl;
//
////    shared_ptr<int *> null_ptr;
////    cout << null_ptr.use_count() << endl;
////    cout << null_ptr << endl;
//
//    unique_ptr<stack<unique_ptr<int>>> st_ptr;
//    st_ptr.reset(new stack<unique_ptr<int>>);
//
//    unique_ptr<int> p(new int(3));
//
//    st_ptr->push(move(p));
//    cout << *st_ptr->top() << endl;
//
//    shared_ptr<int> int_ptr = move(st_ptr->top());
//
//    cout << *int_ptr << endl;
//    cout << st_ptr->top().get() << endl;
//    return 0;
//}