//
// Created by Chris on 17/4/1.
//

#include "../db_connection_guard.h"
#include "../db_connection_pool.h"
#include "../db.h"
#include "test_init.h"
#include "gtest/gtest.h"

using namespace NaiNa;
using namespace std;

TEST(db_connection_guard_test, test_all)
{
    test_init init;
    init.init();

    db_connection_guard db_ptr(std::move(db_connection_pool::instance()->connection()));

    auto res = db_ptr().query("SELECT * FROM Student");


    while(auto row = db_ptr().fetch_row(res)) {

        string cout_str;
        for(int j=0; j < db_ptr().num_field(res); ++j) {
            auto field = db_ptr().fetch_field_direct(res, j);
            cout_str += field->name;
            if(row[j]) {
                cout_str += " ";
                cout_str += row[j];
                cout_str += " ";
            }

            else {
                cout_str += " NULL";
            }
        }
        cout << cout_str << endl << endl;
    }
}