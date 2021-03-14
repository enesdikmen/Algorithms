#include<iostream>
#include<string>
#include<fstream>
#include"myheap.h"
#include<time.h>
#include <chrono> //to measure time more precisely


int main(int argc, char *argv[]){
    int m = stoi(argv[1]);
    double p = stod(argv[2]);
    if(m < 0 || p > 1){
        cerr<<"Invalid inputs"<<endl;
        return -1;
    }

    ifstream file("locations.txt");
    if (!file){
		cerr << "File cannot be opened!";
		exit(1);
	}
    
    vector<double> binary_heap;
    binary_heap.push_back(-1);

    double longitude = 33.40819, latitude =  39.19001;
    
    srand(time(0));
    int prob = int(p*10);//prob variable determines the probability of operations
    
    int addition = 0; //initalizing variables that will hold output data
    int update = 0;
    double distance = 0;
    int oper;
    string line;
    getline(file, line); //takes the first redundant line
    double x, y;

    auto begin = chrono::high_resolution_clock::now(); //starts timer

    for(int i=1; i<=m; i++){

        oper = rand()%10 + 1; 

        if(oper <= prob){ //update distance operation
            if(binary_heap.size() > 1 ){
                update_taxi(binary_heap);
                update++;
            }
        } 
        else{ //add new taxi operation
            
            file>>line;
            x = abs(longitude - stod(line)); // making sure values are positive

            file>>line;
            y = abs(latitude - stod(line));
            
            insert(binary_heap, hypot(x, y)); //cmath's hypot calculates euclidian distance
            addition++;

            getline(file, line, '\n');
        
        }
        if(i%100 == 0){
            distance += call_taxi(binary_heap);
        }
    }
	auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);//timer ends and elapsed time calculated.

    cout<<"Total distance: "<<distance<<", updates: "<<update<<", additions: "<<addition<<endl;
	cout << "Measured run-time: " << elapsed.count()*1e-7 << " milliseconds "<<endl;
    file.close();
    return 0;
}