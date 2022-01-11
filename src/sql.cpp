#include "sql.hpp"


SQLWrapper::SQLWrapper(std::string db_path){
    this->path = db_path;
    int rc = sqlite3_open(db_path.c_str(),&db);
    if (rc){
        std::cout<< "db failed to open: "<<sqlite3_errmsg(db)<<"\n";
    }else{
        std::cout<<"db opened Succesfully\n";
    }
}

void SQLWrapper::create_table(std::string task_table_name){
    std::string query = "CREATE TABLE " + task_table_name + 
        "(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"\
        "NAME TEXT NOT NULL,"\
        "DESCRIPTION TEXT,"\
        "COMPLETE INT NOT NULL,"\
        "PRIORITY TEXT"\
        ");";    
    std::cout<<query<<"\n";
    //compile statement to binary
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db,query.c_str(),-1,&stmt,NULL) != SQLITE_OK){
        std::cout<<"ERROR: while compiling sql in create table: "<< sqlite3_errmsg(this->db)<<"\n";
        return;
    }

    char * error_msg;
    int rc= sqlite3_step(stmt);

    if (rc != SQLITE_DONE){
        std::cout<< "ERROR:" << error_msg<< "\n";
    }else{
        std::cout<< "Table created succesfully\n";
    }
}

void SQLWrapper::insert_task(std::string task_table_name, TaskRecord tc){
    std::stringstream ss;
    ss <<"INSERT INTO "<<task_table_name<< "(ID, NAME, DESCRIPTION,COMPLETE, PRIORITY)";
    ss<<" VALUES(NULL,'"<<tc.name<<"', '"<<tc.description<<"',"<<tc.complete<<","<<tc.priority<<");";

    std::string query(ss.str());
    char * error_msg;
    std::cout <<query<< "\n";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db,query.c_str(),-1,&stmt,NULL) != SQLITE_OK){
        std::cout<<"ERROR: while compiling sql in insert task: "<< sqlite3_errmsg(db)<<"\n";
        return;
    }
    std::cout<<"step insert\n";
    int rc = sqlite3_step(stmt);

    std::cout<<"done insert\n";
    if (rc != SQLITE_DONE){
        std::cout<< "ERROR from insert:" <<sqlite3_errmsg(db)<< "\n";
    }else{
        std::cout<< "record created succesfully\n";
    }
}

std::vector<TaskRecord> SQLWrapper::select_table(std::string table_name){
    //build query
    std::stringstream ss;
    ss <<"SELECT * FROM "<<table_name<<";";
    std::string query(ss.str());

    std::cout<<query<<"\n";
    std::vector<TaskRecord> tasks;
    //compile statement to binary
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db,query.c_str(),-1,&stmt,NULL) != SQLITE_OK){
        std::cout<<"ERROR: while compiling sql in select table: "<< sqlite3_errmsg(db)<<"\n";
        return tasks; 
    }

    int ret_code;

    while((ret_code = sqlite3_step(stmt))== SQLITE_ROW){
        TaskRecord tc;
        tc.id = sqlite3_column_int(stmt,0);
        tc.name= (char *)const_cast<unsigned char* >(sqlite3_column_text(stmt,1));
        tc.description= (char *)const_cast<unsigned char* >(sqlite3_column_text(stmt,2));
        tc.complete = sqlite3_column_int(stmt,3);
        tc.priority = sqlite3_column_int(stmt,4);
        tasks.push_back(tc);
    } 
    if(ret_code != SQLITE_DONE){

        std::cout<<"ERROR: when executing select: "<< sqlite3_errmsg(db)<<"\n";
        return tasks; 
    }

    return tasks;
}


SQLWrapper::~SQLWrapper(){
    sqlite3_close(this->db);
    std::cout<<"db closed\n";
}