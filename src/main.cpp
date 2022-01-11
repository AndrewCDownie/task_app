#include <iostream>
#include "fort.hpp"

#include<sqlite3.h>
#include<vector>
#include<sstream>
#include "sql.hpp"
#include "table.hpp"


int main(){
    std::cout<< "starting..."<<std::endl;
    SQLWrapper * db = new SQLWrapper("data/test.db");

    std::string table_name = "MYTASKS";

    db->create_table(table_name);
    
    TaskRecord tc1;
    tc1.name = "build cli";
    tc1.description = "Build out the main CLI for the applications including controls";
    tc1.complete = 0;
    tc1.priority = 2;

    TaskRecord tc2;
    tc2.name = "build out table class";
    tc2.description = "create table class which handles printing as well as sorting and managing the tables";
    tc2.complete = 0;
    tc2.priority = 1;
    
    db->insert_task(table_name,tc1);

    db->insert_task(table_name,tc2);

    std::vector<TaskRecord> tasks = db->select_table(table_name);

    RecordTable rt;
    rt.records = tasks;

    rt.draw_table();
    rt.sort_by_priority();
    rt.draw_table();



    delete db;




    return 0;
}
