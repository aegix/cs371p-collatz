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
// collatz_eval
// ------------

int collatz_eval (int i, int j, std::unordered_map<int,int>& map_cache) {

    using namespace std;
    //unordered_map<int,int> map_cache;
    bool cache_on = true;
    bool prints = false;
    int start = i;
    int largest = 0;
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
		temp = (temp*3)+1;
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
        if (p == std::make_pair(0, 0))
            return;
        const int i = p.first;
        const int j = p.second;
        const int v = collatz_eval(i, j,cache);
        collatz_print(w, i, j, v);}}
