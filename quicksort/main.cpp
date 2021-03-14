//Enes Bedirhan Dikmen
//150180016

#include<iostream>
#include<fstream>
#include<string>
#include "myquicksort.h"
#include<iomanip> //to manipulate output text file float precision
#include <chrono> //to measure time more precisely
int main(int argc, char *argv[]){
	
	int N = stoi(argv[1]); //you should read value of N from command line
	if(!(N<=1000000 && N >= 0)){
	cerr<<"Argument not in file range!";
	return -1;
	}

	ifstream file;
	file.open("sales.txt");
	if (!file){
		cerr << "File cannot be opened!";
		exit(1);
	}
	
	element *list = new element[N]; //initilizes an array of element struct to hold data
	
    string line;
	getline(file, line); //this is the header line
    string header_line = line;
	for(int i = 0; i<N; i++){
		
		getline(file, line, '\t'); //country (string)
		list[i].country = line;
		getline(file, line, '\t'); //item type (string)
		list[i].item_type = line;
		getline(file, line, '\t'); //order id (string)
		list[i].order_id = line;
		file >> line; //units sold (integer)
		list[i].units_sold = stoi(line);
		file >> line; //total profit (float)
		list[i].total_profit = stod(line);
	    getline(file, line, '\n'); //this is for reading the \n character into dummy variable.
	}
	file.close();
    auto begin = chrono::high_resolution_clock::now(); //starts timer
	
	quick_sort(list, 0, N-1);
	
	auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);//timer ends and elapsed time calculated.
    //Writing sorted list into sorted.txt file
    ofstream ofile("sorted.txt");
    ofile<<header_line<<'\n';
	ofile<<setprecision(12);
    for(int i = 0; i<N; i++){
        ofile
        <<list[i].country<<'\t'
        <<list[i].item_type<<'\t'
        <<list[i].order_id<<'\t'
        <<list[i].units_sold<<'\t'
        <<list[i].total_profit<<'\n';
    }
    ofile.close();

	cout.precision(7);
	cout << "Quicksort took " << elapsed.count() << " nanoseconds, "<< elapsed.count()*1e-7 << " milliseconds, "<< elapsed.count()*1e-9 << " seconds"<<endl;
	

    delete[] list;
	return 0;
}
