#ifndef CACHE
#define CACHE

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
typedef unsigned char uchar;
 
typedef struct cache_line_s {
uchar valid; // valid bit
uchar frequency; // for the LFU wrtiting method. min = 1
long int tag; // tag bits
uchar* block; // block of data
} cache_line_t;

// C(size of cache) = B X E X S
typedef struct cache_s {
uchar s; // num of set index bits -> S(num of sets = 2^s)
uchar t; // num of tag bits
uchar b; // num of block offset bits -> B(size of block) = 2^b
uchar E; // num of lines in each set
cache_line_t** cache; // array of arrays of lines (each array of line is a set, overall cache = array of sets)
} cache_t;

/* CHANGE NEW_ -> NEW? */
int initialize_line(cache_line_t* line, unsigned int B);
cache_t initialize_cache(uchar s, uchar t, uchar b, uchar E);
int find_LFU(cache_line_t* set, int E);
int convert_bits_to_decimal(int* binary_offset, int num_of_bits, int i);
uchar read_byte(cache_t cache, uchar* start, long int off);
void write_byte(cache_t cache, uchar* start, long int off, uchar new_);
void print_cache(cache_t cache);

#endif