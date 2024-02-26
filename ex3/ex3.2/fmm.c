#include "fmm.h"

// Slow fmm :)
void fmm(int n, int* m1, int* m2, int* result) {
    int temp_sum_even = 0;
    int temp_sum_odd = 0;
    int temp_sum_even1 = 0;
    int temp_sum_odd1 = 0;
    int row_index = 0;
    int index = 0;
    // int col_index = 0;
    // int col_index2 = 0;
    // int limit = n-3;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp_sum_even = 0;
            temp_sum_odd = 0;
            temp_sum_even1 = 0;
            temp_sum_odd1 = 0;
            index = i * n + j;
            // result[i][j] = 0
            for (int k = 0; k < n; k+=4){
                row_index = index - (k- j);
                // col_index = k * n + j;
                // col_index2 = (k+1) * n + j;
                temp_sum_even += m1[row_index] * m2[k * n + j];  // result[i][j] += m1[i][k] * m2[k][j]
                temp_sum_odd += m1[row_index + 1] * m2[(k+1) * n + j];
                temp_sum_even1 += m1[row_index + 2] * m2[(k+2) * n + j];
                temp_sum_odd1 += m1[row_index + 3] * m2[(k+3) * n + j];
            } 
            result[index] = temp_sum_even+temp_sum_odd+temp_sum_even1+temp_sum_odd1;
        }
    
    }
}

