#include "matrix.h"

#include <vector>

/************
 * Diagonal *
 ************/
DiagnoalMatrix::DiagnoalMatrix(int n) { _values.assign(n, 0); }

void DiagnoalMatrix::Set(int i, int j, int val) {
  if (i == j && i >= 0 && i < _values.size()) {
    _values[i] = val;
  }
}

int DiagnoalMatrix::Get(int i, int j) const {
  if (i == j && i >= 0 && i < _values.size()) {
    return _values[i];
  }
  return 0;
}

/********************
 * Lower Triangular *
 ********************/
LowerTriangularMatrix::LowerTriangularMatrix(int n) : _n(n) {
  // (n/2) * (1 + n)
  int len = ((n) * (1 + n)) / 2;
  _values.assign(len, 0);
}

void LowerTriangularMatrix::Set(int i, int j, int val) {
  if (i < j || i < 0 || i >= _n || j < 0 || j >= _n) {
    return;
  }
  // printf("%d %d => %d\n", i, j, rowMajor(i, j));
  _values[rowMajor(i, j)] = val;
}

int LowerTriangularMatrix::Get(int i, int j) const {
  if (i < j || i < 0 || i >= _n || j < 0 || j >= _n) {
    return 0;
  }
  return _values[rowMajor(i, j)];
}

int LowerTriangularMatrix::rowMajor(int i, int j) const {
  // (i)/2 * (1 + i)
  int prev = (i * (1 + i)) / 2;
  return prev + j;
}

/********************
 * Upper Triangular *
 ********************/
UpperTriangularMatrix::UpperTriangularMatrix(int n) : _n(n) {
  // (n/2) * (1 + n)
  int len = ((n) * (1 + n)) / 2;
  _values.assign(len, 0);
}

void UpperTriangularMatrix::Set(int i, int j, int val) {
  if (i > j || i < 0 || i >= _n || j < 0 || j >= _n) {
    return;
  }
  // printf("%d %d => %d\n", i, j, rowMajor(i, j));
  _values[rowMajor(i, j)] = val;
}

int UpperTriangularMatrix::Get(int i, int j) const {
  if (i > j || i < 0 || i >= _n || j < 0 || j >= _n) {
    return 0;
  }
  return _values[rowMajor(i, j)];
}

int UpperTriangularMatrix::rowMajor(int i, int j) const {
  // (i/2) * (n + n-i+1)
  int prev = (i * (_n + _n - i + 1)) / 2;
  return prev + (j - i);
}

/*************
 * Symmetric *
 *************/
SymmetricMatrix::SymmetricMatrix(int n) { _ltmx = LowerTriangularMatrix(n); }

void SymmetricMatrix::Set(int i, int j, int val) {
  if (j > i) {
    std::swap(i, j);
  }
  _ltmx.Set(i, j, val);
}

int SymmetricMatrix::Get(int i, int j) const {
  if (j > i) {
    std::swap(i, j);
  }
  return _ltmx.Get(i, j);
}

/************
 * Toeplitz *
 ************/
ToeplitzMatrix::ToeplitzMatrix(int n) : _n(n) { _values.assign(n + n - 1, 0); }

void ToeplitzMatrix::Set(int i, int j, int val) {
  if (i < 0 || i >= _n || j < 0 || j >= _n) {
    return;
  }
  _values[rowMajor(i, j)] = val;
}

int ToeplitzMatrix::Get(int i, int j) const {
  if (i < 0 || i >= _n || j < 0 || j >= _n) {
    return 0;
  }
  return _values[rowMajor(i, j)];
}

int ToeplitzMatrix::rowMajor(int i, int j) const {
  if (j >= i) {
    return j - i;
  }
  return _n + (i - j) - 1;
}

/**********
 * Hankel *
 **********/
HankelMatrix::HankelMatrix(int n) : _n(n) { _values.assign(n + n - 1, 0); }

void HankelMatrix::Set(int i, int j, int val) {
  if (i < 0 || i >= _n || j < 0 || j >= _n) {
    return;
  }
  _values[rowMajor(i, j)] = val;
}

int HankelMatrix::Get(int i, int j) const {
  if (i < 0 || i >= _n || j < 0 || j >= _n) {
    return 0;
  }
  return _values[rowMajor(i, j)];
}

int HankelMatrix::rowMajor(int i, int j) const { return i + j; }

/*************
 * Traversal *
 *************/
std::vector<std::vector<int>> MatrixTraversal::DiagonalRising(
    const std::vector<std::vector<int>> &matrix) const {
  std::vector<std::vector<int>> ans;

  int n = matrix.size();
  int m = matrix[0].size();

  auto add_diag = [&](int x, int y) {
    std::vector<int> diag;
    while (x >= 0 && y >= 0) {
      diag.push_back(matrix[x--][y--]);
    }
    ans.push_back(diag);
  };

  // Starting from last row
  for (int col = 0; col < m; ++col) {
    add_diag(n - 1, col);
  }

  // Starting from last col
  for (int row = n - 2; row >= 0; --row) {
    add_diag(row, m - 1);
  }

  return ans;
}

std::vector<std::vector<int>> MatrixTraversal::DiagonalFalling(
    const std::vector<std::vector<int>> &matrix) const {
  std::vector<std::vector<int>> ans;

  int n = matrix.size();
  int m = matrix[0].size();

  auto add_diag = [&](int x, int y) {
    std::vector<int> diag;
    while (x < n && y < m) {
      diag.push_back(matrix[x++][y++]);
    }
    ans.push_back(diag);
  };

  // Starting from 1st col
  for (int row = n - 1; row >= 0; --row) {
    add_diag(row, 0);
  }

  // Starting from 1st row
  for (int col = 1; col < m; ++col) {
    add_diag(0, col);
  }
  return ans;
}

std::vector<std::vector<int>> MatrixTraversal::AntiDiagonalRising(
    const std::vector<std::vector<int>> &matrix) const {
  std::vector<std::vector<int>> ans;

  int n = matrix.size();
  int m = matrix[0].size();

  auto add_diag = [&](int x, int y) {
    std::vector<int> diag;
    while (x >= 0 && y < m) {
      diag.push_back(matrix[x--][y++]);
    }
    ans.push_back(diag);
  };

  // Starting from 1st column
  for (int row = 0; row < n; ++row) {
    add_diag(row, 0);
  }

  // Starting from last row
  for (int col = 1; col < m; ++col) {
    add_diag(n - 1, col);
  }
  return ans;
}

std::vector<std::vector<int>> MatrixTraversal::AntiDiagonalFalling(
    const std::vector<std::vector<int>> &matrix) const {
  std::vector<std::vector<int>> ans;

  int n = matrix.size();
  int m = matrix[0].size();

  auto add_diag = [&](int x, int y) {
    std::vector<int> diag;
    while (x < n && y >= 0) {
      diag.push_back(matrix[x++][y--]);
    }
    ans.push_back(diag);
  };

  // Starting from 1st row
  for (int col = 0; col < m; ++col) {
    add_diag(0, col);
  }

  // Starting from last col
  for (int row = 1; row < n; ++row) {
    add_diag(row, m - 1);
  }

  return ans;
}