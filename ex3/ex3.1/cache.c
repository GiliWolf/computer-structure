#include "cache.h"

void print_cache(cache_t cache){
    int S=cache.s==0?1:2<<(cache.s-1);
    int B=cache.b==0?1:2<<(cache.b-1);

    for(int i = 0; i<S; i++){
        printf("Set %d\n", i);
        for(int j = 0; j < cache.E; j++){
            printf("%1d %d 0x%0*lx ",cache.cache[i][j].valid,
                cache.cache[i][j].frequency, cache.t,cache.cache[i][j].tag);
            for(int k = 0; k < B; k++){
                printf("%02x ",cache.cache[i][j].block[k]);
            }
            puts("");
        }
    }
}

int initialize_line(cache_line_t* line, unsigned int B) {
    line->valid = 0;
    line->frequency = 0;
    line->tag = 0;

    // assign each line with B blocks
    line->block = (uchar*)malloc(B * sizeof(uchar));
    // if malooc did not succeed
    if (line->block == NULL) {
        return -1;
    }
    // Initialize block with zeros
    for (int i = 0; i < B; i++) {
        line->block[i] = 0;
    }
    return 0;
}
    /*
    ** builds a cache with S=2^s number of sets, each contains E lines, in each line there is t bits of tag
    ** and B= 2^b bits of data block
    */
cache_t initialize_cache(uchar s, uchar t, uchar b, uchar E){
    // // calculate S
    // unsigned int S = 1 << (s-1);
    // // calculate B
    // unsigned int B = 1 << (b-1);
    int S= s == 0?1:2<<(s-1);
    int B= b == 0?1:2<<(b-1);
    cache_t cache_struct;
    cache_struct.s = s;
    cache_struct.t = t;
    cache_struct.b = b;
    cache_struct.E = E;

    // assign S arrays of line pointer
    cache_struct.cache = (cache_line_t**)malloc(S * sizeof(cache_line_t*));
    // allocation fail
    if (cache_struct.cache == NULL) {
        return cache_struct;
    }
    for (int i = 0; i < S; i++) {
        // for each array, assign E lines
        cache_struct.cache[i] = (cache_line_t*)malloc(E * sizeof(cache_line_t));
         // free previouse assigned memory in case of allocation fail
        if (cache_struct.cache[i] == NULL) {
            free(cache_struct.cache);
            for (int k = 0; k < i; k++) {
                free(cache_struct.cache[k]);
            }
            free(cache_struct.cache);
            return cache_struct;
        }
        for (int j = 0; j < E; j++){
            // initilize each line
            int result = initialize_line(&cache_struct.cache[i][j], B);
            // free previouse assigned memory in case of allocation fail
            if (result == -1){
                for (int m = 0; m < j; m++){
                    free(cache_struct.cache[i][m].block);
                }
                for (int k = 0; k < i; k++) {
                    free(cache_struct.cache[k]);
                }
                    free(cache_struct.cache);
            return cache_struct;
            }
        }
    }
    return cache_struct;

}

int convert_bits_to_decimal(int* binary_offset, int num_of_bits, int i){
    int decimal_value = 0;
    for (i; i < i + num_of_bits; i++) {
        decimal_value = (decimal_value << 1) | binary_offset[i];
    }
    return decimal_value;
}

uchar read_byte(cache_t cache, uchar* start, long int off){
    uchar s1 =cache.s;
    // get adress values
    int s = (int) cache.s;
    int b = (int) cache.b;
    int t = (int) cache.t;
    // change offset to binary number (array of "bits")
    int m = s + b + t;
    printf("m: %d", m);
    // int size_of_long_int = sizeof(long int);
    int binary_offset[m]; 
    for (int i = 0; i < m; i++) {
        binary_offset[m - 1 - i] = (off >> i) & 1;
    }

    printf("Bit array representation of %ld:\n", off);
    for (int i = 0; i < m; i++) {
        printf("%d", binary_offset[i]);
    }
    printf("\n");
    
    int decimal_s = convert_bits_to_decimal(binary_offset, s, t - 1);

}

void write_byte(cache_t cache, uchar* start, long int off, uchar new_){

}
