#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>

int main (int argc, char** argv) {
    // argv[1] - size matrix
    // argv[2] - determinant
    if (argc != 3) {
        return 1;
    }

    std::size_t size = atoi (argv[1]);
    double determinant = atof (argv[2]);
    std::vector<std::vector<double>> matrix(size, std::vector<double>(size, 0));

    matrix[0][0] = determinant;

    for (std::size_t i = 1; i < size; ++i) {
        matrix[i][i] = 1;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    std::random_device rd2;
    std::mt19937 gen2(rd2());
    std::uniform_int_distribution<int> dist2(0, size - 1);

    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < i; ++j) {
            matrix[j][i] = dist(gen);
        }
    }
    
    for (std::size_t i = 0; i < size; ++i) {
        int str = dist2(gen2); 
        while (str == i) {
            str = dist2 (gen2);
        }
        double coef = dist(gen);
        for (std::size_t j = 0; j < size; ++j) {
            matrix[str][j] += matrix[i][j] * coef;
        }
    }

    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size; ++j) {
            std::cout << matrix[j][i] << " ";
        }
        std::cout << "\n";
    }
}

