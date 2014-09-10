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

int recurse_eval (int i, std::unordered_map<int,int>& cache){
    using namespace std;
    //cout<<"recursive call for " << i << endl;
    int temp = i;
    int cycles = 1;
    if(temp>1){
	if(cache[temp]&&cache[temp]!=-1){
	    //cout<<"cache hit for "<<temp<<endl;
   	    return cache[temp];
	}
        else if((temp%2)==0){
            temp = (temp/2);
            cycles+=recurse_eval(temp, cache);
        }
        else{
            temp = (temp*3)+1;
	    if(temp<i){ 
		cout << i << endl;
		assert(temp>i);
	    }
            cycles+=recurse_eval(temp, cache);
        }
    }
    cache[i] = cycles;
    //cout << "return " << cycles << " for "<< i << endl;
    return cycles;
}


int recurse_range(int i, int j, std::unordered_map<int,int>& cache) {

    using namespace std;
    int largest = 0;
    if(j<i){
	int temp = i;
	i = j;
	j = temp;
    }
    //cout<<start << " " << j << endl;
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

int collatz_eval (int i, int j, std::unordered_map<int,int>& map_cache) {

    using namespace std;
    bool cache_on = true;
    bool prints = false;
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
    
    time_t start;
    time(&start);
    using namespace std;
    unordered_map<int,int> cache;
    while (true) {
        const std::pair<int, int> p = collatz_read(r);
        if (p == std::make_pair(0, 0)){
	    time_t end;
    	    time(&end);
    	    cout<<difftime(end, start)<<endl;
            return;
	}
        const int i = p.first;
        const int j = p.second;
        //const int v = recurse_range(i, j,cache);
        const int v = collatz_eval(i, j,cache);
        if(v == -1)
	    cout << "overflow in range " << i << " " << j << endl;
	collatz_print(w, i, j, v);}
}
