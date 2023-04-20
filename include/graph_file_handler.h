#ifndef GRAPH_FILE_HANDLER_H
#define GRAPH_FILE_HANDLER_H

#include <fstream>
#include <iostream>
#include <string>

class GraphFileHandler {
 public:
   GraphFileHandler(const std::string file_name);
   void ProcessGraphs();

 private:
   std::ifstream input_file_;
};

#endif // GRAPH_FILE_HANDLER_H