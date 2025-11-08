#include "graph.h"
#include <vector>

// Implementation of powMatrix function
std::vector<std::vector<int>> powMatrix(std::vector<std::vector<int>> A, int p) {
    int n = A.size();
    std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));

    // Initialize identity matrix
    for(int i = 0; i < n; i++) result[i][i] = 1;

    while(p) {
        if(p % 2) {
            std::vector<std::vector<int>> temp(n, std::vector<int>(n, 0));
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    for(int k = 0; k < n; k++)
                        temp[i][j] += result[i][k] * A[k][j];
            result = temp;
        }

        std::vector<std::vector<int>> temp(n, std::vector<int>(n, 0));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                for(int k = 0; k < n; k++)
                    temp[i][j] += A[i][k] * A[k][j];
        A = temp;
        p /= 2;
    }

    return result;
}
