#include <iostream>
#include "fort.hpp"

#include<sqlite3.h>
#include<vector>
#include<sstream>
#include "sql.hpp"


int main(){
    std::cout<< "starting..."<<std::endl;
    SQLWrapper * db = new SQLWrapper("data/test.db");

    std::string table_name = "MYTASKS";

    db->create_table(table_name);
    
    task_record tc1;
    tc1.name = "build cli";
    tc1.description = "Build out the main CLI for the applications including controls";
    tc1.complete = 0;
    tc1.priority = 2;

    task_record tc2;
    tc2.name = "build out table class";
    tc2.description = "create table class which handles printing as well as sorting and managing the tables";
    tc2.complete = 0;
    tc2.priority = 1;
    
    db->insert_task(table_name,tc1);

    db->insert_task(table_name,tc2);

    std::vector<task_record> tasks = db->select_table(table_name);
    fort::char_table table;
    table << fort::header<< "ID"<<"NAME"<<"DESCRIPTION"<<"COMPLETE"<<"PRIORITY"<<fort::endr;

    for(auto tc: tasks){
        table<<tc.id<<tc.name<<tc.description<<tc.complete<<tc.priority<<fort::endr;
    }

    std::cout<< table.to_string()<<std::endl;

    delete db;




    return 0;
}
