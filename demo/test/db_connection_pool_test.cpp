//
// Created by Chris on 17/3/27.
//

#include "../db_connection_pool.h"
#include "../db.h"
#include "../../include/gtest/gtest.h"

using namespace NaiNa;
using namespace std;

TEST(db_connection_pool_test, test_connection)
{
    string _db = "Student_Info";
    string addr = "localhost";
    port_type port = 3306;
    string name = "root";
    string passwd = "root";

    int connect_num = 20;

    bool init_flag = db_connection_pool::instance()->init(_db, addr, port, name, passwd,2,connect_num);
    EXPECT_EQ(init_flag, true);


    for(int i=0; i < connect_num; ++i) {
        unique_ptr<db> db_ptr = move(db_connection_pool::instance()->connection());

        auto res = db_ptr->query("SELECT * FROM Student");

        while(auto row = db_ptr->fetch_row(res)) {
            for(int j=0; j < db_ptr->num_field(res); ++j) {
                auto field = db_ptr->fetch_field_direct(res, j);
                cout << field->name << " " << row[j] << " ";
            }
            cout << endl << endl;
        }


        db_connection_pool::instance()->release_connection(move(db_ptr));
    }

//    cout << db_connection_pool::instance()->max_connection_ << endl;
//    cout << db_connection_pool::instance()->min_connection_ << endl;
//    cout << db_connection_pool::instance()->current_connection_ << endl;

}