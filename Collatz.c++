// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair
#include <unordered_map> //hashmap
#include <time.h>
#include <limits.h>
#include "Collatz.h"

// ------------
// collatz_read
// ------------

std::pair<int, int> collatz_read (std::istream& r) {
    int i;
    r >> i;
    if (!r)
        return std::make_pair(0, 0);
    int j;
    r >> j;
    return std::make_pair(i, j);}

// ------------
// recurse_eval
// ------------

int recurse_eval (int i, std::unordered_map<int,int>& cache){ //do collatz recursively to try to get a higher quality lazy cache
    using namespace std;
    int temp = i;
    int cycles = 1;
    if(temp>1){
	if(cache[temp]){ //Cache Hit
   	    return cache[temp];
	}
        else if((temp%2)==0){
            temp = (temp/2);
            cycles+=recurse_eval(temp, cache); //recursive step
        }
        else{
            temp = (temp*3)+1;
            cycles+=recurse_eval(temp, cache); //alternate recursive step
        }
    }
    cache[i] = cycles; //store in cache
    return cycles;
}


int recurse_range(int i, int j, std::unordered_map<int,int>& cache) {//harness to run recurse_eval in a range

    using namespace std;
    int largest = 0;
    if(j<i){
	    int temp = i;
	    i = j;
	    j = temp;
    }
    int start = j/2 +1;
    if(start<i) start = i;
    while(start<=j){
        int temp = recurse_eval(start,cache);
	    if(temp>largest)
	    largest = temp;
	start++;
    }
    return largest; 
}


// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j, std::unordered_map<int,int>& map_cache) { //reference to map to make the cache persistent between calls

    using namespace std;
    bool cache_on = true;//Added switch for cache
    bool prints = false; //Added switch for debug print statements
    int start = i;
    int largest = 0;
    if(j<i){
	    int temp;
	    temp = i;
	    i = j;
	    j = temp;
    }
    while(i<=j){
	int original = i;
	int temp = i;
	int cycles = 1;
	if(prints) cout <<cycles<<" "<<temp<<endl;
	while(temp > 1){
	    if(cache_on){
	    if(temp>=start && temp <=j && map_cache[temp]){
		if(prints) cout << "hit for key " << temp << " value "<< map_cache[temp] << endl;
		cycles += (map_cache[temp] - 1);
		temp = 1;
	    }
	    else if((temp%2)==0){
	    	temp = (temp/2);
	 	cycles++;
	    }
	    else{
		    int overflow = temp;
		    temp = (temp*3)+1;
		    if(overflow>temp){
		        cout<< i << ",";
		        return -1;
		    }
		cycles++;
	    }}
	    else{
	    if((temp%2)==0){
                temp = (temp/2);
                cycles++;
            }
            else{
                temp = (temp*3)+1;
                cycles++;

		}
	    }
	    if(prints) cout << cycles << " " << temp << endl;
	}
	if(cache_on) map_cache[original] = cycles;
	if (prints) cout << cycles << endl << endl;
	if(cycles>largest)
	    largest = cycles;
	i++;
    }
    return largest;}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {
    
    using namespace std;
    unordered_map<int,int> cache;
    while (true) {
        const std::pair<int, int> p = collatz_read(r);
        if (p == std::make_pair(0, 0)){
            return;
	}
    const int i = p.first;
    const int j = p.second;
    //const int v = recurse_range(i, j,cache);
    const int v = collatz_eval(i, j,cache);

	collatz_print(w, i, j, v);}
}
