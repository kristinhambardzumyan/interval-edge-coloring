#include <chrono>

#include "../include/graph_file_handler.h"
#include "../include/interval_edge_coloring.h"

GraphFileHandler::GraphFileHandler(std::string file_name) {
    input_file_.open(file_name);
        if (!input_file_) {
            std::cerr << "Error: Could not open file!" << std::endl;
            exit(1);
        }
}

void GraphFileHandler::ProcessGraphs() {
    IntervalEdgeColoring graph_iec;
    std::string graph6;
    bool is_colorable;
    while (std::getline(input_file_, graph6)) {
        graph_iec.SetStartTime();
        graph_iec.Reset();
        graph_iec.AdjacencyFromGraph6(graph6);
        graph_iec.BiadjacencyFromAdjacency();
        is_colorable = graph_iec.SearchIntervalColoring(20);
        graph_iec.SetElapsedTime();

        if (is_colorable && graph_iec.IsValidColoring()) {
            graph_iec.OutputColoredGraphs(graph6);
        } else if (graph_iec.IsTimeLimited()) {
            graph_iec.OutputTimeLimitedGraphs(graph6);
        } else {
            graph_iec.OutputUncoloredGraphs(graph6);
        }
    }
    input_file_.close();
}

