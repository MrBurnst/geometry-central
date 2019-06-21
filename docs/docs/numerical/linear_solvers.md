This section covers the solvers available in geometry central for sparse linear algebra problems.

All solvers support real and complex matrices, and can be templated on a `#!cpp float`, `#!cpp double`, or `#!cpp std::complex<double>`.

`#!cpp #include "geometrycentral/numerical/linear_solvers.h"`

## Direct solvers

These solvers provide a simple interface for solving sparse linear $Ax = b$. 

A key feature is that these solvers abstract over the underlying numerical library. In their most basic form, [Eigen's sparse solvers](https://eigen.tuxfamily.org/dox/group__TopicSparseSystems.html) will be used, and are always available. However, if present, the more-powerful [Suitesprase solvers](http://faculty.cse.tamu.edu/davis/suitesparse.html) will be used intead. See the [dependencies section](../../build/dependencies/#suitesparse) for instruction to build with Suitesparse support.


### Quick solves

These are one-off routines for quick solves.

??? func "`#!cpp Vector<T> solve(SparseMatrix<T>& matrix, const Vector<T>& rhs)`"

    Solve a system with a general matrix. Uses a QR decomposition interally.


??? func "`#!cpp Vector<T> solveSquare(SparseMatrix<T>& matrix, const Vector<T>& rhs)`"
    
    Solve a system with a _square_ matrix. Uses an LU decomposition interally.


??? func "`#!cpp Vector<T> solvePositiveDefinite(SparseMatrix<T>& matrix, const Vector<T>& rhs)`"

    Solve a system with a _symmetric positive (semi-)definite_ matrix. Uses an LDLT decomposition interally.


### Retain factorizations

When solving many linear systems $Ax=b$ with the same matrix $A$ but different $b$, it is dramatically more efficient to retain and reuse the factorization of $A$. The following solver classes are stateful, storing the factorization to be re-used for may solves.

```cpp
SparseMatrix<double> A = /* ... some matrix ... */;

// Build the solver
Solver<double> solver(A);

// Solve a problem
Vector<double> rhs1 = /* ... */;
Vector<double> sol = solver.solve(rhs1);

// Solve another problem
Vector<double> rhs2 = /* ... */;
Vector<double> sol2 = solver.solve(rhs2);

// Can place solution in existing vector
Vector<double> rhs3 = /* ... */;
solver.solve(sol, rhs3);

// Some solvers have extra powers.
// Solver<> can compute matrix rank, since it uses QR under the hood.
std::cout << "matrix rank is " << solver.rank() << std::endl;
```

??? func "`#!cpp template <typename<T>> class Solver`"
    
    Solve a system with a general matrix. Uses a QR decomposition interally.

??? func "`#!cpp template <typename<T>> class SquareSolver`"
    
    Solve a system with a _square_ matrix. Uses an LU decomposition interally.

??? func "`#!cpp template <typename<T>> class PositiveDefiniteSolver`"
    
    Solve a system with a _symmetric positive (semi-)definite_ matrix. Uses an LDLT decomposition interally.



## Eigenproblem solvers

These routines build on top of the direct solvers to solve eigenvalue problems using power methods.

??? func "`#!cpp Vector<T> smallestEigenvectorPositiveDefinite(SparseMatrix<T>& energyMatrix, SparseMatrix<T>& massMatrix, size_t nIterations = 50)`"

    TODO.


??? func "`#!cpp std::vector<Vector<T>> smallestKEigenvectorsPositiveDefinite(SparseMatrix<T>& energyMatrix, SparseMatrix<T>& massMatrix, size_t kEigenvalues, size_t nIterations = 50)`"

    TODO.


??? func "`#!cpp Vector<T> smallestEigenvectorSquare(SparseMatrix<T>& energyMatrix, SparseMatrix<T>& massMatrix, size_t nIterations = 50)`"
    
    TODO.


??? func "`#!cpp Vector<T> largestEigenvector(SparseMatrix<T>& energyMatrix, SparseMatrix<T>& massMatrix, size_t nIterations = 50)`"

    TODO.


## Utilities

??? func "`#!cpp double residual(const SparseMatrix<T>& matrix, const Vector<T>& lhs, const Vector<T>& rhs)`"

    Measure the L2 residual of a linear system as $||Ax - b||_2$.

