// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2014
// Glenn P. Downing
// --------------------------

#ifndef Collatz_h
#define Collatz_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <utility>  // pair
#include <unordered_map> //hashmap


int recurse_eval (int i, std::unordered_map<int,int>& cache);


int recurse_range(int i, int j, std::unordered_map<int,int>& cache);

// ------------
// collatz_read
// ------------

/**
 * read two ints
 * @param r an std::istream
 * @return a pair of ints, representing the beginning and end of a range, [i, j]
 */
std::pair<int, int> collatz_read (std::istream& r);

// ------------
// collatz_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length of the range [i, j]
 */
int collatz_eval (int i, int j,std::unordered_map<int,int>& map_cache);

// -------------
// collatz_print
// -------------

/**
 * print three ints
 * @param w an std::ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void collatz_print (std::ostream& w, int i, int j, int v);

// -------------
// collatz_solve
// -------------

/**
 * @param r an std::istream
 * @param w an std::ostream
 */
void collatz_solve (std::istream& r, std::ostream& w);

#endif // Collatz_h
