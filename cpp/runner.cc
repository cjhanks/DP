#include "levenshtein.hh"
#include "knapsack.hh"
#include "floyd_warshall.hh"
#include "matrix_chain_order.hh"
#include "sparse_matrix.hh"
#include "max_path_sum.hh"
#include "djikstra.hh"
#include "largest_all_k.hh"
#include "lcs.hh"
#include "scs.hh"
#include "submatrix.hh"

#include <iomanip>
#include <iostream>

int
main() {
  // ------------------------------------------
  {
  std::cerr << "-------------------------\n";
  using LSolver = Levenshtein<char>;
  std::string a = "abcd";
  std::string b = "dabc";

  std::cerr << LSolver::Solve(a, b) << "\n";
  }

  // ------------------------------------------
  {
  std::cerr << "-------------------------\n";
  struct Element {
    double value;
    double weight;
  };

  std::vector<Element> elems = {
    { 10, 2 },
    {  9, 3 },
    {  4, 1 },
    {  4, 1 },
    {  4, 1 },
  };
  using KSolver = Knapsack<Element>;
  std::cerr << KSolver::Solve(7, elems) << "\n";
  }

  // ------------------------------------------
  {
  std::cerr << "-------------------------\n";
  Matrix2D<float> mat(4, 4, std::numeric_limits<float>::infinity());

  for (std::size_t r = 0; r < mat.Rows(); ++r)
    mat.At(r, r) = 0.f;

  mat.At(0, 1) =  5.0;
  mat.At(0, 3) = 10.0;
  mat.At(1, 2) =  3.0;
  mat.At(2, 3) =  1.0;

  FloydWarshall<float>::Solve(mat);

  for (std::size_t r = 0; r < mat.Rows(); ++r) {
    for (std::size_t c = 0; c < mat.Cols(); ++c) {
      std::cerr << std::setw(4) << mat.At(r, c) << " ";
    }

    std::cerr << "\n";
  }
  }

  // ------------------------------------------
  {
  std::cerr << "-------------------------\n";
  using DGraph  = Graph<std::size_t, double>;
  using DSolver = Djikstra<DGraph>;

  DGraph graph;
  graph.AddEdge(0, 1, 1.0);
  graph.AddEdge(1, 2, 4.0);
  graph.AddEdge(0, 3, 3.0);
  graph.AddEdge(3, 2, 8.0);

  // 0 -> 0
  // 1 -> 1
  // 2 -> inf
  // 3 -> 3

  auto solution = DSolver::Solve(graph, 0);
  for (std::size_t n = 0; n < solution.size(); ++n) {
    std::cerr << n << " -> " << solution[n] << "\n";
  }
  }

  // ------------------------------------------
  {
  std::cerr << "-------------------------\n";
  using LCSSolver = LongestCommonSubsequence<char>;

  std::string a = "RGBGAARGA";
  std::string b = "RGBRGBQ";
  Matrix2D<unsigned> mat;
  std::size_t n = LCSSolver::Solve(a, b, mat);
  std::cerr << n << "\n";

  std::cerr << Backtrack<char>(a, b, mat, true) << "\n";
  }

  // ------------------------------------------
  {
  std::cerr << "-------------------------\n";
  using SCSSolver = ShortestCommonSubsequence<char>;

  std::cerr << SCSSolver::Solve("AGGTAB", "GXTXAYB") << "\n";
  std::cerr << SCSSolver::Solve("abac", "cab") << "\n";
  }

  // ------------------------------------------
  {
  std::cerr << "-------------------------\n";
  std::vector<unsigned> data;
  for (std::size_t n = 1; n < 6; ++n)
    data.push_back(n);

  clock_t head;
  head = clock();
  std::size_t j = MatrixChainOrder<unsigned>::SolveRecursive(data);
  std::cerr << (1000.0 * (clock() - head) / CLOCKS_PER_SEC)
            << ": j = " << j << "\n";

  head = clock();
  std::size_t k = MatrixChainOrder<unsigned>::Solve(data);
  std::cerr << (1000.0 * (clock() - head) / CLOCKS_PER_SEC)
            << ": k = " << k << "\n";
  }

  // ------------------------------------------
  {
  std::cerr << "-------------------------\n";

  Matrix2D<unsigned> mat(5, 4, 0U);
  mat.At(0,0) = 1;
  mat.At(0,2) = 2;
  mat.At(1,1) = 3;
  mat.At(3,0) = 4;
  mat.At(3,1) = 5;
  mat.At(4,1) = 6;
  mat.At(4,2) = 7;
  mat.At(4,3) = 8;
  COOMatrix<unsigned> new_mat0(mat);
  CSRMatrix<unsigned, ColSparse::ROW> new_mat1(mat);
  CSRMatrix<unsigned, ColSparse::COL> new_mat2(mat);
  std::cerr << "========\n";

  std::cerr << 0 << ", " << 0 << " = " << new_mat1.At(0, 0) << "\n";
  std::cerr << 3 << ", " << 0 << " = " << new_mat1.At(3, 0) << "\n";
  std::cerr << 4 << ", " << 1 << " = " << new_mat1.At(4, 1) << "\n";
  std::cerr << "~~~~~~~~\n";
  std::cerr << 0 << ", " << 0 << " = " << new_mat2.At(0, 0) << "\n";
  std::cerr << 3 << ", " << 0 << " = " << new_mat2.At(3, 0) << "\n";
  std::cerr << 4 << ", " << 1 << " = " << new_mat2.At(4, 1) << "\n";
  }

  // ------------------------------------------
  {
  std::cerr << "-------------------------\n";
  Matrix2D<unsigned> mat(4, 6, 0U);
  mat.At(0, 0) = 1;
  mat.At(0, 1) = 2;
  mat.At(1, 1) = 3;

  mat.At(0, 4) = 4;
  mat.At(1, 5) = 5;

  mat.At(2, 2) = 6;
  mat.At(2, 3) = 7;
  mat.At(3, 3) = 8;


  BSRMatrix<unsigned> new_mat(mat, 2);
  }

  // ------------------------------------------
  {
  std::cerr << "-------------------------\n";
  Matrix2D<unsigned> mat(4, 4);

  mat.At(0, 0) = 3;
  mat.At(0, 1) = 2;
  mat.At(0, 2) = 1;
  mat.At(0, 3) = 8;

  mat.At(1, 0) = 9;
  mat.At(1, 1) = 11;
  mat.At(1, 2) = 15;
  mat.At(1, 3) = 0;

  mat.At(2, 0) = 8;
  mat.At(2, 1) = 4;
  mat.At(2, 2) = 7;
  mat.At(2, 3) = 6;

  mat.At(3, 0) = 12;
  mat.At(3, 1) = 8;
  mat.At(3, 2) = 7;
  mat.At(3, 3) = 3;


  //for (std::size_t r = 0; r < mat.Rows(); ++r)
  //for (std::size_t c = 0; c < mat.Rows(); ++c)
  //  mat.At(r, c) = 2 ;

  Submatrix<unsigned>::Solve(mat, 6);
  }

  {
  std::cerr << "-------------------------\n";
  Matrix2D<unsigned> mat(6, 6);
  mat.At(0, 0) = 1;
  mat.At(0, 1) = 9;
  mat.At(0, 2) = 10;

  mat.At(1, 1) = 8;

  mat.At(1, 0) = 4;
  mat.At(2, 0) = 5;
  mat.At(2, 1) = 7;


  std::cerr << mat << "\n";
  std::cerr << MaxPathSum<unsigned>::Solve(mat, 0, 0)
            << "\n";
  }

  {
  std::cerr << "-------------------------\n";
  Matrix2D<unsigned> mat(8, 8, 0);

  mat.At(0, 1) = 1;
  mat.At(0, 2) = 1;
  mat.At(1, 1) = 1;
  mat.At(1, 2) = 1;
  mat.At(2, 2) = 1;
  mat.At(3, 2) = 1;
  mat.At(4, 2) = 1;
  mat.At(5, 2) = 1;
  mat.At(5, 3) = 1;
  mat.At(5, 4) = 1;
  mat.At(5, 5) = 1;
  mat.At(6, 3) = 1;
  mat.At(6, 4) = 1;
  mat.At(6, 5) = 1;
  mat.At(7, 3) = 1;
  mat.At(7, 4) = 1;
  mat.At(7, 5) = 1;

  std::cerr << mat << "\n";

  std::cerr << LargestAllK<unsigned>::Solve(mat, 1)
            << "\n";
  }
}
