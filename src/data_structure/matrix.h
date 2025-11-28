
#pragma once

#include <cstddef>
#include <vector>

// Diagonal matrix: stores only the diagonal values
class DiagnoalMatrix {
public:
  explicit DiagnoalMatrix(int n);
  void Set(int i, int j, int val);
  int Get(int i, int j) const;

private:
  std::vector<int> _values;
};

// Lower triangular matrix stored in compact row-major fashion
class LowerTriangularMatrix {
public:
  explicit LowerTriangularMatrix(int n);
  void Set(int i, int j, int val);
  int Get(int i, int j) const;
  int rowMajor(int i, int j) const;

private:
  int _n{0};
  std::vector<int> _values;
};

// Upper triangular matrix stored in compact layout
class UpperTriangularMatrix {
public:
  explicit UpperTriangularMatrix(int n);
  void Set(int i, int j, int val);
  int Get(int i, int j) const;
  int rowMajor(int i, int j) const;

private:
  int _n{0};
  std::vector<int> _values;
};

// Symmetric matrix implemented using LowerTriangularMatrix
class SymmetricMatrix {
public:
  explicit SymmetricMatrix(int n);
  void Set(int i, int j, int val);
  int Get(int i, int j) const;

private:
  LowerTriangularMatrix _ltmx{0};
};

// Toeplitz and Hankel (diagonally-constant) matrices
class ToeplitzMatrix {
public:
  explicit ToeplitzMatrix(int n);
  void Set(int i, int j, int val);
  int Get(int i, int j) const;
  int rowMajor(int i, int j) const;

private:
  int _n{0};
  std::vector<int> _values;
};

class HankelMatrix {
public:
  explicit HankelMatrix(int n);
  void Set(int i, int j, int val);
  int Get(int i, int j) const;
  int rowMajor(int i, int j) const;

private:
  int _n{0};
  std::vector<int> _values;
};

// Traversal helpers for matrices
class MatrixTraversal {
public:
  std::vector<std::vector<int>>
  DiagonalRising(const std::vector<std::vector<int>> &matrix) const;
  std::vector<std::vector<int>>
  DiagonalFalling(const std::vector<std::vector<int>> &matrix) const;
  std::vector<std::vector<int>>
  AntiDiagonalRising(const std::vector<std::vector<int>> &matrix) const;
  std::vector<std::vector<int>>
  AntiDiagonalFalling(const std::vector<std::vector<int>> &matrix) const;
};
