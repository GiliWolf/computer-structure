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
    // calculate S and B
    int S= s == 0?1:2<<(s-1);
    int B= b == 0?1:2<<(b-1);
    // get struct parameters 
    cache_t cache_struct;
    cache_struct.s = s;
    cache_struct.t = t;
    cache_struct.b = b;
    cache_struct.E = E;


    // CHECK PARAMETERS??

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

/*
* converts the bits from binary_offset[i] - binary_offset[i+num_of_bits] to a decimal value
*/
int convert_bits_to_decimal(int* binary_offset, int num_of_bits, int i){
    int decimal_value = 0;
    for (int j = i; j < i + num_of_bits; j++) {
        decimal_value = (decimal_value << 1) | binary_offset[j];
    }
    return decimal_value;
}

/*
* finds line with least fraquancy and returns its index.
*/
int find_LFU(cache_line_t* set, int E){
    int temp_LFU = 0;
    int last_LFU_index;
    int first_flag = 1;
    for (int i = 0; i < E; i++){
        if (first_flag == 1){
            first_flag = 0;
            temp_LFU = set[i].frequency;
            last_LFU_index = 0;
            continue;
        }
        // of the frequency is smaller than the temp LFU, set as new temp LFU
        if (set[i].frequency < temp_LFU) {
            temp_LFU = set[i].frequency;
            last_LFU_index = i;
        }
        // // if both has the same frequency
        // else if (set[i].frequency == temp_LFU){
        //     // if the last 
        //     if (i < last_LFU_index){
        //         temp_LFU = set[i].frequency;
        //         last_LFU_index = i;
        //     }
        // }
    }
    return last_LFU_index;
}

int find_line(cache_t cache, uchar* start, long int off){
    uchar s1 =cache.s;
    // get adress values
    int s = (int) cache.s;
    int b = (int) cache.b;
    int t = (int) cache.t;
    int E = (int) cache.E;
    int B= b == 0?1:2<<(b-1);

    // calculate number of adress bits
    int m = s + b + t;

    // get binary representaion of the offset value (as 'bits' array)
    int binary_offset[m]; 
    for (int i = 0; i < m; i++) {
        binary_offset[m - 1 - i] = (off >> i) & 1;
    }
    
    // get adress values according to off value
    int set_index = convert_bits_to_decimal(binary_offset, s, t);
    long int decimal_tag = convert_bits_to_decimal(binary_offset, t, 0);
    int block_offset = convert_bits_to_decimal(binary_offset, b, t + s);

    // go to the right set using set values
    cache_line_t* temp_set = cache.cache[set_index];
    //iterate over each line - 
    int found_flag = 0;
    for (int i = 0; i < E; i++){
        // CACHE HIT    
        if (temp_set[i].valid == 1 && temp_set[i].tag == decimal_tag){
            // read byte
            found_flag = 1;
            temp_set[i].frequency += 1;
            break;
        }
    }
    //get least frequaent 
    int lfu_line = find_LFU(temp_set, E);
    // CACHE MISS: get data from 'RAM'
    if (found_flag == 0){
        uchar data = start[off];
        temp_set[lfu_line].valid = 1;
        temp_set[lfu_line].tag = decimal_tag;
        temp_set[lfu_line].frequency += 1;
        for (int j = 0; j < B; j++){
            temp_set[lfu_line].block[j] = start[off+j-block_offset];
        }
        // printf("%d",temp_set[lfu_line].block[0]);
        // printf("%d",temp_set[lfu_line].block[1]);
        int b1 = temp_set[lfu_line].block[0];
        int b2 = temp_set[lfu_line].block[1];
        int b3 = 0;
    }
    return start[off];

}

uchar read_byte(cache_t cache, uchar* start, long int off){
    uchar s1 =cache.s;
    // get adress values
    int s = (int) cache.s;
    int b = (int) cache.b;
    int t = (int) cache.t;
    int E = (int) cache.E;
    int B= b == 0?1:2<<(b-1);
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
    
    // get adress values according to off value
    int set_index = convert_bits_to_decimal(binary_offset, s, t);
    long int decimal_tag = convert_bits_to_decimal(binary_offset, t, 0);
    int block_offset = convert_bits_to_decimal(binary_offset, b, t + s);

    // go to the right set using set values
    cache_line_t* temp_set = cache.cache[set_index];
    //iterate over each line - 
    int found_flag = 0;
    for (int i = 0; i < E; i++){
        // CACHE HIT    
        if (temp_set[i].valid == 1 && temp_set[i].tag == decimal_tag){
            // read byte
            found_flag = 1;
            temp_set[i].frequency += 1;
            break;
        }
    }
    //get least frequaent 
    int lfu_line = find_LFU(temp_set, E);
    // CACHE MISS: get data from 'RAM'
    if (found_flag == 0){
        uchar data = start[off];
        temp_set[lfu_line].valid = 1;
        temp_set[lfu_line].tag = decimal_tag;
        temp_set[lfu_line].frequency += 1;
        for (int j = 0; j < B; j++){
            temp_set[lfu_line].block[j] = start[off+j-block_offset];
        }
        // printf("%d",temp_set[lfu_line].block[0]);
        // printf("%d",temp_set[lfu_line].block[1]);
        int b1 = temp_set[lfu_line].block[0];
        int b2 = temp_set[lfu_line].block[1];
        int b3 = 0;
    }
    return start[off];
}

void write_byte(cache_t cache, uchar* start, long int off, uchar new_){
    uchar data = read_byte(cache, start, off);

}
