#ifndef GRAPH_FILE_HANDLER_H
#define GRAPH_FILE_HANDLER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class GraphFileHandler {
 public:
  GraphFileHandler(std::string input_file_name,
                   std::string colorables_file_name, 
                   std::string non_colorables_file_name,
                   std::string time_limited_file_name);
                   
  void ProcessGraphs(long long time_limit);
  void OutputColoredGraphs(std::string graph6, 
                           std::vector<std::vector<int>> coloring, 
                           long long elapsed_time);

  void OutputTimeLimitedGraphs(std::string graph6);
  void OutputUncoloredGraphs(std::string graph6, long long elapsed_time);

 private:
   std::ifstream input_file_;
   std::fstream colorables_file;
   std::fstream non_colorables_file;
   std::fstream time_limited_file;
   std::string colorables_file_name_;
   std::string non_colorables_file_name_;
   std::string time_limited_file_name_;

};

#endif // GRAPH_FILE_HANDLER_H