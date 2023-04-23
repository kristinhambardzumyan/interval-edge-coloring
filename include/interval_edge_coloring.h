#ifndef INTERVAL_EDGE_COLORING_H
#define INTERVAL_EDGE_COLORING_H

#include <chrono>
#include <cstddef>
#include <string>
#include <vector>

class IntervalEdgeColoring {
 public:
  
  void AdjacencyFromGraph6(const std::string graph6);

  void BiadjacencyFromAdjacency();

  // Determines the bipartition of a graph.
  void SetBipartition();

  // Resets all member variables to their initial state.
  void Reset();

  // Sets a color to the 1st cell of coloring_ matrix.
  // Calls RecursiveColoring() for coloring the rest of the cells.
  bool SearchIntervalColoring(int color);

  // Backtracking algorithm for coloring the matrix such that each row and column contains a unique 
  // consecutive sequence of numbers, with 0s being excluded.
  bool RecursiveColoring(int row, int column);

  // Determines the possible color set for a given matrix cell.
  void DeterminePossibleColors(int row, int column, std::vector<int>& possible_colors);
  
  void SetColor(int row, int column, int color);

  void ClearColor(int row, int column);

  // Get the min/max used color in a particular row/column.
  int GetMinUsedColor(int n);
  int GetMaxUsedColor(int n);

  void OutputColoredGraphs(std::string graph6);
  void OutputUncoloredGraphs(std::string graph6);
  void OutputTimeLimitedGraphs(std::string graph6);

  bool IsTimeLimited();

  bool IsValidColoring();

  // Get the min used color in a given row/column of a graph coloring.
  // Used by IsValidColoring().
  int GetMinColorInRow(int row);
  int GetMinColorInColumn(int column);

  void SetStartTime();
  void SetElapsedTime();
  long long TimeElapsed();
  
 private:
  int vertices_;
  int rows_;
  int columns_;
  std::vector<std::vector<int>> adj_matrix_;
  std::vector<std::vector<int>> biadj_matrix_;

  // The coloring is represented as a biadjacency matrix.
  // coloring_[i][j] is the color of the edge joining the i-th vertex of the 1st bipartition 
  // and the j-th vertex of the 2nd, if the edge exists, and is set to 0 otherwise.
  std::vector<std::vector<int>> coloring_;

  // Store the colors used in rows/columns.
  std::vector<std::vector<uint32_t>> arr_row_;
  std::vector<std::vector<uint32_t>> arr_col_;

  // Store the degrees of the row/column vertices.
  std::vector<int> deg_row_;
  std::vector<int> deg_col_;

  std::chrono::time_point<std::chrono::steady_clock> start_time_;
  long long elapsed_time_ = 0;
  int time_limit_ = 1000; // in milliseconds (1min)
  bool time_limited = false;
};

#endif // INTERVAL_EDGE_COLORING_H
