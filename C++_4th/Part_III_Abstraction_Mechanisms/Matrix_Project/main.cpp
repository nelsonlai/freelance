#include "matrix.h"
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

using namespace matrix;

// Demonstrates the Matrix Project
int main() {
    std::cout << "Matrix Project Demonstration" << std::endl;
    std::cout << "============================" << std::endl;
    
    try {
        // 1. 1D Matrix (Vector)
        std::cout << "\n1. 1D MATRIX (VECTOR):" << std::endl;
        
        Vector<int> vector1({1, 2, 3, 4, 5});
        std::cout << "Vector1: " << vector1 << std::endl;
        
        Vector<double> vector2(5, 2.5);
        std::cout << "Vector2: " << vector2 << std::endl;
        
        // Vector operations
        vector1[0] = 10;
        vector1[1] = 20;
        std::cout << "Modified vector1: " << vector1 << std::endl;
        
        std::cout << "Vector1 sum: " << vector1.sum() << std::endl;
        std::cout << "Vector1 mean: " << vector1.mean() << std::endl;
        std::cout << "Vector1 min: " << vector1.min() << std::endl;
        std::cout << "Vector1 max: " << vector1.max() << std::endl;
        
        // 2. 2D Matrix
        std::cout << "\n2. 2D MATRIX:" << std::endl;
        
        Matrix2D<int> matrix2d({3, 4}, 0);
        
        // Fill matrix with values
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                matrix2d(i, j) = i * 4 + j + 1;
            }
        }
        
        std::cout << "2D Matrix:" << std::endl;
        matrix2d.display();
        
        std::cout << "Matrix sum: " << matrix2d.sum() << std::endl;
        std::cout << "Matrix mean: " << matrix2d.mean() << std::endl;
        
        // 3. 3D Matrix
        std::cout << "\n3. 3D MATRIX:" << std::endl;
        
        Matrix3D<int> matrix3d({2, 3, 4}, 0);
        
        // Fill 3D matrix with values
        for (size_t x = 0; x < 2; ++x) {
            for (size_t y = 0; y < 3; ++y) {
                for (size_t z = 0; z < 4; ++z) {
                    matrix3d(x, y, z) = x * 12 + y * 4 + z + 1;
                }
            }
        }
        
        std::cout << "3D Matrix dimensions: ";
        for (size_t i = 0; i < 3; ++i) {
            std::cout << matrix3d.dimension(i);
            if (i < 2) std::cout << " x ";
        }
        std::cout << std::endl;
        
        std::cout << "3D Matrix sum: " << matrix3d.sum() << std::endl;
        std::cout << "3D Matrix mean: " << matrix3d.mean() << std::endl;
        
        // 4. Matrix arithmetic operations
        std::cout << "\n4. MATRIX ARITHMETIC OPERATIONS:" << std::endl;
        
        Matrix2D<int> matrix_a({2, 3}, 0);
        Matrix2D<int> matrix_b({2, 3}, 0);
        
        // Fill matrices
        for (size_t i = 0; i < 2; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                matrix_a(i, j) = i * 3 + j + 1;
                matrix_b(i, j) = (i * 3 + j + 1) * 2;
            }
        }
        
        std::cout << "Matrix A:" << std::endl;
        matrix_a.display();
        
        std::cout << "Matrix B:" << std::endl;
        matrix_b.display();
        
        // Addition
        Matrix2D<int> matrix_c = matrix_a + matrix_b;
        std::cout << "Matrix C = A + B:" << std::endl;
        matrix_c.display();
        
        // Subtraction
        Matrix2D<int> matrix_d = matrix_b - matrix_a;
        std::cout << "Matrix D = B - A:" << std::endl;
        matrix_d.display();
        
        // Scalar multiplication
        Matrix2D<int> matrix_e = matrix_a * 3;
        std::cout << "Matrix E = A * 3:" << std::endl;
        matrix_e.display();
        
        // Scalar division
        Matrix2D<int> matrix_f = matrix_b / 2;
        std::cout << "Matrix F = B / 2:" << std::endl;
        matrix_f.display();
        
        // 5. Matrix comparison
        std::cout << "\n5. MATRIX COMPARISON:" << std::endl;
        
        Matrix2D<int> matrix_g = matrix_a;
        std::cout << "Matrix A == Matrix G: " << std::boolalpha << (matrix_a == matrix_g) << std::endl;
        std::cout << "Matrix A == Matrix B: " << std::boolalpha << (matrix_a == matrix_b) << std::endl;
        std::cout << "Matrix A != Matrix B: " << std::boolalpha << (matrix_a != matrix_b) << std::endl;
        
        // 6. Iterator usage
        std::cout << "\n6. ITERATOR USAGE:" << std::endl;
        
        Vector<int> vector3({10, 20, 30, 40, 50});
        
        std::cout << "Vector3 using iterators: ";
        for (auto it = vector3.begin(); it != vector3.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        std::cout << "Vector3 using range-based for: ";
        for (const auto& value : vector3) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        
        // Find maximum using iterator
        auto max_it = std::max_element(vector3.begin(), vector3.end());
        std::cout << "Maximum element: " << *max_it << std::endl;
        
        // 7. Matrix operations with different types
        std::cout << "\n7. MATRIX OPERATIONS WITH DIFFERENT TYPES:" << std::endl;
        
        Matrix2D<double> matrix_double({2, 2}, 0.0);
        matrix_double(0, 0) = 1.5;
        matrix_double(0, 1) = 2.5;
        matrix_double(1, 0) = 3.5;
        matrix_double(1, 1) = 4.5;
        
        std::cout << "Double matrix:" << std::endl;
        matrix_double.display();
        
        Matrix2D<double> matrix_double_scaled = matrix_double * 2.0;
        std::cout << "Scaled double matrix:" << std::endl;
        matrix_double_scaled.display();
        
        // 8. Matrix with strings
        std::cout << "\n8. MATRIX WITH STRINGS:" << std::endl;
        
        Matrix2D<std::string> matrix_string({2, 3}, "");
        matrix_string(0, 0) = "Hello";
        matrix_string(0, 1) = "World";
        matrix_string(0, 2) = "C++";
        matrix_string(1, 0) = "Matrix";
        matrix_string(1, 1) = "Project";
        matrix_string(1, 2) = "Demo";
        
        std::cout << "String matrix:" << std::endl;
        matrix_string.display();
        
        // 9. Performance test
        std::cout << "\n9. PERFORMANCE TEST:" << std::endl;
        
        const size_t size = 1000;
        Matrix2D<int> large_matrix({size, size}, 0);
        
        // Fill with random values
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                large_matrix(i, j) = dis(gen);
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << "Filled " << size << "x" << size << " matrix in " 
                  << duration.count() << " ms" << std::endl;
        
        // Calculate sum
        start = std::chrono::high_resolution_clock::now();
        int sum = large_matrix.sum();
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << "Calculated sum: " << sum << " in " << duration.count() << " ms" << std::endl;
        
        // 10. Matrix operations with STL algorithms
        std::cout << "\n10. MATRIX OPERATIONS WITH STL ALGORITHMS:" << std::endl;
        
        Vector<int> vector4({5, 2, 8, 1, 9, 3, 7, 4, 6});
        std::cout << "Original vector: " << vector4 << std::endl;
        
        // Sort using STL algorithm
        std::sort(vector4.begin(), vector4.end());
        std::cout << "Sorted vector: " << vector4 << std::endl;
        
        // Reverse using STL algorithm
        std::reverse(vector4.begin(), vector4.end());
        std::cout << "Reversed vector: " << vector4 << std::endl;
        
        // Count elements greater than 5
        int count = std::count_if(vector4.begin(), vector4.end(), 
                                 [](int value) { return value > 5; });
        std::cout << "Count of elements > 5: " << count << std::endl;
        
        // 11. Matrix copy and move semantics
        std::cout << "\n11. MATRIX COPY AND MOVE SEMANTICS:" << std::endl;
        
        Matrix2D<int> original({2, 3}, 0);
        for (size_t i = 0; i < 2; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                original(i, j) = i * 3 + j + 1;
            }
        }
        
        std::cout << "Original matrix:" << std::endl;
        original.display();
        
        // Copy constructor
        Matrix2D<int> copied = original;
        std::cout << "Copied matrix:" << std::endl;
        copied.display();
        
        // Move constructor
        Matrix2D<int> moved = std::move(original);
        std::cout << "Moved matrix:" << std::endl;
        moved.display();
        
        // 12. Matrix with custom type
        std::cout << "\n12. MATRIX WITH CUSTOM TYPE:" << std::endl;
        
        struct Point {
            int x, y;
            
            Point(int x = 0, int y = 0) : x(x), y(y) {}
            
            friend std::ostream& operator<<(std::ostream& os, const Point& p) {
                os << "(" << p.x << "," << p.y << ")";
                return os;
            }
        };
        
        Matrix2D<Point> point_matrix({2, 2}, Point(0, 0));
        point_matrix(0, 0) = Point(1, 2);
        point_matrix(0, 1) = Point(3, 4);
        point_matrix(1, 0) = Point(5, 6);
        point_matrix(1, 1) = Point(7, 8);
        
        std::cout << "Point matrix:" << std::endl;
        point_matrix.display();
        
        // 13. Matrix resize and fill
        std::cout << "\n13. MATRIX RESIZE AND FILL:" << std::endl;
        
        Matrix2D<int> resize_matrix({2, 2}, 1);
        std::cout << "Original 2x2 matrix:" << std::endl;
        resize_matrix.display();
        
        resize_matrix.resize({3, 4}, 5);
        std::cout << "Resized to 3x4 matrix:" << std::endl;
        resize_matrix.display();
        
        resize_matrix.fill(10);
        std::cout << "Filled with 10:" << std::endl;
        resize_matrix.display();
        
        // 14. Matrix swap
        std::cout << "\n14. MATRIX SWAP:" << std::endl;
        
        Matrix2D<int> matrix_swap1({2, 2}, 1);
        Matrix2D<int> matrix_swap2({2, 2}, 2);
        
        std::cout << "Before swap:" << std::endl;
        std::cout << "Matrix 1:" << std::endl;
        matrix_swap1.display();
        std::cout << "Matrix 2:" << std::endl;
        matrix_swap2.display();
        
        matrix_swap1.swap(matrix_swap2);
        
        std::cout << "After swap:" << std::endl;
        std::cout << "Matrix 1:" << std::endl;
        matrix_swap1.display();
        std::cout << "Matrix 2:" << std::endl;
        matrix_swap2.display();
        
        // 15. Matrix with different dimensions
        std::cout << "\n15. MATRIX WITH DIFFERENT DIMENSIONS:" << std::endl;
        
        Matrix<int, 4> matrix_4d({2, 3, 4, 5}, 0);
        
        // Fill with values
        int value = 1;
        for (size_t i = 0; i < 2; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                for (size_t k = 0; k < 4; ++k) {
                    for (size_t l = 0; l < 5; ++l) {
                        matrix_4d({i, j, k, l}) = value++;
                    }
                }
            }
        }
        
        std::cout << "4D Matrix dimensions: ";
        for (size_t i = 0; i < 4; ++i) {
            std::cout << matrix_4d.dimension(i);
            if (i < 3) std::cout << " x ";
        }
        std::cout << std::endl;
        
        std::cout << "4D Matrix size: " << matrix_4d.size() << std::endl;
        std::cout << "4D Matrix sum: " << matrix_4d.sum() << std::endl;
        
        std::cout << "\nMatrix Project demonstration completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
