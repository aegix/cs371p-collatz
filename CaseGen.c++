
#include <cstdlib>
#include <ctime>
#include <iostream>

int main(){

    using namespace std;
    int r1, r2;
    for(int i = 0; i < 1000; i++){
	r1 = (rand()%1000)+1;
	r2 = (rand()%1000)+1+r1;
	cout << r1 << " " << r2 << endl;
    }




}

