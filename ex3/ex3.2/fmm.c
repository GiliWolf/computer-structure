#include "fmm.h"

// // int size = 4 bytes, block size = 64 bytes -> 64/4=16
// void fmm(int n, int* m1, int* m2, int* result) {
//     int temp_sum_even = 0;
//     int temp_sum_odd = 0;
//     int temp_sum_even1 = 0;
//     int temp_sum_odd1 = 0;
//     int row_index = 0;
//     int index = 0;
//     // int col_index = 0;
//     // int col_index2 = 0;
//     // int limit = n-3;
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             temp_sum_even = 0;
//             temp_sum_odd = 0;
//             temp_sum_even1 = 0;
//             temp_sum_odd1 = 0;
//             index = i * n + j;
//             // result[i][j] = 0
//             for (int k = 0; k < n; k+=4){
//                 row_index = index - (k- j);
//                 // col_index = k * n + j;
//                 // col_index2 = (k+1) * n + j;
//                 temp_sum_even += m1[row_index] * m2[k * n + j];  // result[i][j] += m1[i][k] * m2[k][j]
//                 temp_sum_odd += m1[row_index + 1] * m2[(k+1) * n + j];
//                 temp_sum_even1 += m1[row_index + 2] * m2[(k+2) * n + j];
//                 temp_sum_odd1 += m1[row_index + 3] * m2[(k+3) * n + j];
//             } 
//             result[index] = temp_sum_even+temp_sum_odd+temp_sum_even1+temp_sum_odd1;
//         }
    
//     }
// }

// // int size = 4 bytes, block size = 64 bytes -> 64/4=16
// void fmm(int n, int* m1, int* m2, int* result) {
//     int row_index = 0;
//     int index = 0;
//     int chunks = 16; // int size = 4 bytes, block size = 64 bytes, chunck -> 64/4=16
//     int chunk_sum = 0;
//     int index_sum = 0;
//     for (int i = 0; i < n; i+=chunks) {
//         for (int j = 0; j < n; j+=chunks) {
//                 index_sum = 0;
//                 for(int r_c = i; r_c < i + chunks && r_c < n; r_c++){
//                     for(int c_c = j; c_c < j + chunks && c_c < n; c_c++){
//                         for(int k = 0; k < n; k+=chunks){
//                             chunk_sum = 0;
//                             for (int k_c = k; k_c < k + chunks && k_c < n; k_c++){
//                                 int m1_i = r_c * n;
//                                 int m1_j = k_c;
//                                 int m2_i = k_c * n;
//                                 int m2_j = c_c;
//                                 chunk_sum += m1[r_c * n + k_c] * m2[k_c * n + c_c];
//                             }
//                             index_sum += chunk_sum;
//                         }
//                         result[i * n + j] = index_sum;
//                     }
//                 }
//         }
//     }
// }

// // int size = 4 bytes, block size = 64 bytes -> 64/4=16
// void fmm(int n, int* m1, int* m2, int* result) {
//     int row_index = 0;
//     int index = 0;
//     int chunks = 16; // int size = 4 bytes, block size = 64 bytes, chunck -> 64/4=16
//     int chunk_sum = 0;
//     int index_sum = 0;
//     for(int r_c = 0; r_c < n; r_c++){
//         for(int c_c = 0; c_c < n; c_c++){
//             index_sum = 0;
//             for(int k = 0; k < n; k+=chunks){
//                 chunk_sum = 0;
//                 for (int k_c = k; k_c < k + chunks && k_c < n; k_c++){
//                     int m1_i = r_c * n;
//                     int m1_j = k_c;
//                     int m2_i = k_c * n;
//                     int m2_j = c_c;
//                     chunk_sum += m1[r_c * n + k_c] * m2[k_c * n + c_c];
//                 }
//                     index_sum += chunk_sum;
//             }
//                 result[r_c * n + c_c] = index_sum;
//         }
//     }
// }

// //LAST
// void fmm(int n, int* m1, int* m2, int* result) {
//     int chunks = 16; // int size = 4 bytes, block size = 64 bytes, chunk -> 64/4=16
//     int chunk_even_sum = 0;
//     int chunk_odd_sum = 0;
//     for (int r_c = 0; r_c < n; r_c++) {
//         for (int c_c = 0; c_c < n; c_c++) {
//             int index_sum = 0;
//             for (int k = 0; k < n; k += chunks) {
//                 chunk_even_sum = 0;
//                 chunk_odd_sum = 0; 
//                 for (int k_c = k; k_c < k + chunks && k_c < n; k_c+=2) {
//                     int temp_m1_index = r_c * n + k_c;
//                     chunk_even_sum += m1[temp_m1_index] * m2[k_c * n + c_c];
//                     chunk_odd_sum += m1[temp_m1_index + 1] * m2[(k_c + 1) * n + c_c];
//                 }
//                 index_sum += chunk_even_sum + chunk_odd_sum;
//             }
//             result[r_c * n + c_c] = index_sum;
//         }

//     }
// }
//BOOK
// void fmm(int n, int* m1, int* m2, int* result) {
//     int temp = 0;
//     for (int i = 0; i < n; i++) {
//         for (int k = 0; k < n; k++){
//             temp = m1[i * n + k];
//             for (int j = 0; j < n; j++) {
//                 int temp_m2 = m2[k * n + j];
//                 result[i * n + j]=0;
//                 int mult = temp * temp_m2;
//                 result[i * n + j] += mult; // result[i][j] += m1[i][k] * m2[k][j]
//             }
//             temp = 0;
//         }
//         temp = 0;
//     }
// }
void fmm(int n, int* m1, int* m2, int* result) {

    int k_mul_n = 0; // k *n 
    int limit = n-1;
    for (int k = 0; k < n; k++){
        int i_mul_n = 0; // i * n 
        for (int i = 0; i < n; i++) {
            int temp = m1[i_mul_n + k];
            int i_n_j = i_mul_n; // i * n + j 
            int* result_ptr = result + i_mul_n; // result + i * n 
            int* m2_ptr = m2 + k_mul_n;
            int* limit_ptr = result + i_n_j + limit;
            for (int j = 0; j < limit; j+=2) {
                if (k == 0){
                    result[i_n_j] = 0;
                    result[i_n_j + 1] = 0;
                    // *result_ptr = 0;
                    // *(result_ptr + 1) =0;
                } 
                //works
                // result[i_n_j] += temp * m2[k_mul_n + j]; // i *n + j  = [i * n + k] * [k * n + j]
                // result[i_n_j + 1] += temp * m2[k_mul_n + j +1]; // i *n + j + 1 = [i * n + k] * [k * n + j +1]

                //works
                // result[i_n_j] += temp * (*m2_ptr++); // i *n + j  = [i * n + k] * [k * n + j]
                // result[i_n_j + 1] += temp * (*m2_ptr++); // i *n + j + 1 = [i * n + k] * [k * n + j +1]

                //works
                (*result_ptr++) += temp * (*m2_ptr++); // i *n + j  = [i * n + k] * [k * n + j]
                (*result_ptr++) += temp * (*m2_ptr++); // i *n + j + 1 = [i * n + k] * [k * n + j +1]

                //doest work
                // *result_ptr++ = temp * m2[k_mul_n + j];
                // *result_ptr++ = temp * m2[k_mul_n + j +1];

                i_n_j+=2;
                // result_ptr +=2;; // i * n + j + 2
            }
            i_mul_n += n; // i * n + n == (i + 1) * n 
        }
        k_mul_n += n; // k * n + n == (k + 1) * n
        // printf("kth matrix: \n");
        // print_matrix(result, n);
        // printf("\n");
    }
}


void slow_fmm(int n, int* m1, int* m2, int* result) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i * n + j] = 0;  // result[i][j] = 0
            for (int k = 0; k < n; k++) 
                result[i * n + j] += m1[i * n + k] * m2[k * n + j];  // result[i][j] += m1[i][k] * m2[k][j]
        }
    }
}



// // Slow fmm :)
// void fmm(int n, int* m1, int* m2, int* result) {
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             result[i * n + j] = 0;  // result[i][j] = 0
//             for (int k = 0; k < n; k++) 
//                 result[i * n + j] += m1[i * n + k] * m2[k * n + j];  // result[i][j] += m1[i][k] * m2[k][j]
//         }
//     }
// }

// #include "fmm.h"

// // Slow fmm :)
// void fmm(int n, int* m1, int* m2, int* result) {
//     int temp_sum_even = 0;
//     int temp_sum_odd = 0;
//     // int temp_sum_even1 = 0;
//     // int temp_sum_odd1 = 0;
//     int row_index = 0;
//     int index = 0;
//     // int col_index = 0;
//     // int col_index2 = 0;
//     // int limit = n-3;
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             temp_sum_even = 0;
//             temp_sum_odd = 0;
//             // temp_sum_even1 = 0;
//             // temp_sum_odd1 = 0;
//             index = i * n + j;
//             // result[i][j] = 0
//             for (int k = 0; k < n; k+=2){
//                 row_index = index - (k- j);
//                 // col_index = k * n + j;
//                 // col_index2 = (k+1) * n + j;
//                 temp_sum_even += m1[row_index] * m2[k * n + j];  // result[i][j] += m1[i][k] * m2[k][j]
//                 temp_sum_odd += m1[row_index + 1] * m2[(k+1) * n + j];
//                 // temp_sum_even1 += m1[row_index + 2] * m2[(k+2) * n + j];
//                 // temp_sum_odd1 += m1[row_index + 3] * m2[(k+3) * n + j];
//             } 
//             result[index] = temp_sum_even+temp_sum_odd;
//         }
    
//     }
// }

// void fmm(int n, int* m1, int* m2, int* result) {
//     const int blockSize = 64; // Adjust the block size based on your CPU cache size

//     // Iterate over blocks of size blockSize in each dimension
//     for (int bi = 0; bi < n; bi += blockSize) {   // Iterate over blocks in rows
//         for (int bj = 0; bj < n; bj += blockSize) {   // Iterate over blocks in columns
//             for (int bk = 0; bk < n; bk += blockSize) {   // Iterate over blocks in depth
//                 // Process block (bi, bj)
//                 // Iterate over elements within the block
//                 for (int i = bi; i < bi + blockSize && i < n; ++i) {   // Iterate over rows in the block
//                     for (int j = bj; j < bj + blockSize && j < n; ++j) {   // Iterate over columns in the block
//                         int sum = 0;
//                         // Iterate over elements in the depth dimension
//                         for (int k = bk; k < bk + blockSize && k < n; ++k) {   // Iterate over depth in the block
//                             sum += m1[i * n + k] * m2[k * n + j];   // Perform matrix multiplication
//                         }
//                         result[i * n + j] += sum;   // Accumulate the result
//                     }
//                 }
//             }
//         }
//     }
// }
