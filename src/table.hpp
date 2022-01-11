#include<string>
#include<vector>
#include "fort.hpp"

struct TaskRecord{
   int id;
   std::string name;
   std::string description;
   int complete;
   int priority; 
};

class RecordTable{
    public:
        int highlighted;
        std::vector<TaskRecord> records;
        std::vector<std::string> columns_names;
};