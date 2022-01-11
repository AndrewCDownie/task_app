#include "table.hpp"
#include<iostream>
#include<algorithm>
void RecordTable::draw_table(){

    fort::char_table table;
    table << fort::header<< "ID"<<"NAME"<<"DESCRIPTION"<<"COMPLETE"<<"PRIORITY"<<fort::endr;

    for(auto tc: records){
        table<<tc.id<<tc.name<<tc.description<<tc.complete<<tc.priority<<fort::endr;
    }
    std::cout<<table.to_string()<<std::endl;
}

bool compare_by_priority(const TaskRecord tc1, const TaskRecord tc2){
    return tc1.priority < tc2.priority;
}

void RecordTable::sort_by_priority(){
    std::cout<<"sorting\n";
    std::sort(this->records.begin(),this->records.end(),compare_by_priority);
}