#include <chrono>

#include "../include/graph_file_handler.h"
#include "../include/interval_edge_coloring.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " input-file\n";
        return 1;
    }
    GraphFileHandler file_handler(argv[1]);
    std::chrono::time_point<std::chrono::steady_clock> start_time = std::chrono::steady_clock::now();
    file_handler.ProcessGraphs();
    std::chrono::time_point<std::chrono::steady_clock> end_time = std::chrono::steady_clock::now();
    auto duration_in_sec =  std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
    auto duration_in_ms =  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Execution time: " << duration_in_sec << " seconds" << std::endl;
    std::cout << "Execution time: " << duration_in_ms << " ms" << std::endl;
}
