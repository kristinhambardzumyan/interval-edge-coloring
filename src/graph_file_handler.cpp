#include <chrono>
#include <iostream>

#include "../include/graph_file_handler.h"
#include "../include/interval_edge_coloring.h"

GraphFileHandler::GraphFileHandler(std::string input_file_name,
                                   std::string colorables_file_name,
                                   std::string non_colorables_file_name,
                                   std::string time_limited_file_name) {
    input_file_.open(input_file_name);
    if (!input_file_) {
        std::cerr << "Error: Could not open file!" << std::endl;
        exit(1);
    }
    colorables_file_name_ = colorables_file_name;
    non_colorables_file_name_ = non_colorables_file_name;
    time_limited_file_name_ = time_limited_file_name;
}

void GraphFileHandler::ProcessGraphs(int time_limit) {
    IntervalEdgeColoring graph_iec;
    graph_iec.SetTimeLimit(time_limit);
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
            OutputColoredGraphs(graph6, graph_iec.GetColoring(), graph_iec.GetElapsedTime());
        } else if (graph_iec.IsTimeLimited()) {
            OutputTimeLimitedGraphs(graph6);
        } else {
            OutputUncoloredGraphs(graph6, graph_iec.GetElapsedTime());
        }
    }
    input_file_.close();
}

void GraphFileHandler::OutputColoredGraphs(std::string graph6, 
                                           std::vector<std::vector<int>> coloring, 
                                           long long elapsed_time) {
    std::ofstream output_file;
    output_file.open(colorables_file_name_, std::ios::app);
    output_file << '<' << graph6 << "> <";
    for (std::size_t row = 0; row < coloring.size(); ++row) {
        for (std::size_t column = 0; column < coloring[row].size(); ++column) {
            output_file << static_cast<char>((coloring[row][column] + 94));
        }
    }
    output_file << "> <" << elapsed_time << '>' << std::endl;
    output_file.close();
}

void GraphFileHandler::OutputTimeLimitedGraphs(std::string graph6) {
    std::ofstream output_file;
    output_file.open(time_limited_file_name_, std::ios::app);
    output_file << graph6 << std::endl;
    output_file.close();
}

void GraphFileHandler::OutputUncoloredGraphs(std::string graph6, long long elapsed_time) {
    std::ofstream output_file;
    output_file.open(non_colorables_file_name_, std::ios::app);
    output_file << '<' << graph6 << "> <" << elapsed_time << '>' << std::endl;
    output_file.close();
}