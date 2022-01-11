#include<sqlite3.h>
#include<iostream>
#include<vector>
#include<sstream>
#include"table.hpp"

class SQLWrapper{
    public:
        std::string path;
        sqlite3 * db;
        SQLWrapper(std::string db_path);
        ~SQLWrapper();  
        void create_table(std::string task_table_name);
        void insert_task(std::string task_table_name, TaskRecord tc);
        std::vector<TaskRecord> select_table(std::string name); 
};