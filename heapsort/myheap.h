#include<vector>
#include<cmath>
#include<stdlib.h>
#include <limits>
using namespace std;


void print_tree(vector<double> &v){ //prints out binary heap int a tree-like format, helps to check if heaps are correct
    int height = int(log2(v.size() - 1)) + 1;
    int size = v.size() - 1;
    int n=1;
    int pos = 1;
    cout<<"tree start"<<endl;
    for(int i=0; i<height; i++){
        for(int j=0; j<n && pos<=size; j++){
            cout<<v[pos]<<" ";
            pos++;
        }
        cout<<endl;
        n *= 2;

    }
    cout<<"tree end"<<endl;


}

void heapify(vector<double> &v, int i){
    int size = v.size() - 1;
    int l = i * 2;
    int r = i * 2 + 1; 
    int smallest = i;
    if(l <= size && v[l] < v[i]){
        smallest = l;
    }
    else{
        smallest = i;
    }

    if(r <= size && v[r] < v[smallest]){
        smallest = r;
    }
    if(smallest != i){
        double temp = v[i];
        v[i] = v[smallest];
        v[smallest] = temp;
        heapify(v, smallest);
    }
}

void decrease_key(vector<double> &v, int i, double key){//decrase-key PQ operation
    if(key > v[i]){
        cerr<<"new key is bigger than current key \n";
        return;
    }

    v[i] = key;
    while (i>1 && v[i/2]>v[i]){ //i>0 since root's index is 0 and not 1, parent(i) = i/2 
        double temp = v[i];
        v[i] = v[i/2];
        v[i/2] = temp;
        i = i/2;
    }   
}

void insert(vector<double> &v, double key){//inser PQ operation
    
    v.push_back(numeric_limits<double>::max()); //inserting maximum possible number to make sure everything is smaller
    decrease_key(v, v.size()-1, key);
}

double heap_min(vector<double> &v){ //HEAP-MIN PQ operation
    return v[1];
}

void add_taxi(vector<double> &v, double distance){ //inserts new taxi
//since insert operation puts the element at correct place after inserting no more operations needed
    insert(v, distance);
}

double call_taxi(vector<double> &v){ //removes the closest taxi, works like extract-min
    if((v.size()-1) < 1){
        cerr<<"heap underflow"<<endl;
        return -1;
    }
    double taxi = heap_min(v);
    v[1] = v.size() - 1; //1'st node becomes last element
    v.pop_back(); //last element removed and size reduced by 1
    heapify(v, 1);
    return taxi; //returns the distance of called taxi
}

void update_taxi(vector<double> &v){ //almost same with decrease key operation but decreases by 0.01
    int i = (rand() % (v.size()-1)) + 1; //taxi choosen randomly
    v[i] -= 0.01;// update amount
    while (i>1 && v[i/2]>v[i]){ //i>0 since root's index is 0 and not 1, parent(i) = i/2 
        double temp = v[i];
        v[i] = v[i/2];
        v[i/2] = temp;
        i = i/2;
    }
}