//
// Created by Chris on 17/3/26.
//

#include "gtest/gtest.h"
#include "../db.h"
//#include <string>

using namespace std;
using namespace NaiNa;


TEST(db_test, test_init)
{
    db d;

    string db = "Student_Info";
    string address = "localhost";
    port_type port = 3306;
    string name = "root";
    string passwd = "2718big.a";

    bool success_init = d.init(db, address, port, name, passwd);

    EXPECT_EQ(success_init, true);

}


TEST(db_test, test_)
{
    db d;

    string db = "Student_Info";
    string addr = "localhost";
    port_type port = 3306;
    string name = "root";
    string passwd = "2718big.a";

    bool success_init = d.init(db, addr, port, name, passwd);

    EXPECT_EQ(success_init, true);

    auto res = d.query("SELECT * FROM Student;");
    auto row_count = d.num_rows(res);
    auto field_count = d.num_field(res);

    MYSQL_ROW row = nullptr;
    MYSQL_FIELD* field = nullptr;
    while(row = d.fetch_row(res)) {
        for(int i=0; i < field_count; ++i) {
            field = d.fetch_field_direct(res, i);
            cout << field->name << " " << row[i] << " ";
        }
        cout << endl;
    }
}