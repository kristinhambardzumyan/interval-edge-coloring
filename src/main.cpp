#include <chrono>

#include "../include/graph_file_handler.h"
#include "../include/interval_edge_coloring.h"

int main(int argc, char* argv[]) {
    if (argc != 6) {
        std::cerr << "Usage: " << argv[0] << " input-file colorables-file non-colorables-file time-limited-file time_limit in ms\n";
        return 1;
    }
    std::string input_file = argv[1];
    std::string colorables_file = argv[2];
    std::string non_colorables_file = argv[3];
    std::string time_limited_file = argv[4];
    long long time_limit = std::stol(argv[5]);

    GraphFileHandler file_handler(input_file,colorables_file, non_colorables_file, time_limited_file);
    
    // std::chrono::time_point<std::chrono::steady_clock> start_time = std::chrono::steady_clock::now();
    file_handler.ProcessGraphs(time_limit);
    // std::chrono::time_point<std::chrono::steady_clock> end_time = std::chrono::steady_clock::now();
    // auto duration_in_sec =  std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
    // auto duration_in_ms =  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    // std::cout << "Coloring time: " << duration_in_sec << " sec/" << duration_in_ms << " ms" << std::endl;
}
