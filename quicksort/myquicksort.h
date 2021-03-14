//Enes Bedirhan Dikmen
//150180016
#include<string>
using namespace std;

struct element{
    string country;
    string item_type;
    string order_id;
    int units_sold;
    double total_profit;
};

bool is_smaller(int x, int y, element list[]){  //returns true if first parameters element need to come before second parameter   
    if(list[x].country > list[y].country){
        return false;
    }
    else if(list[x].country < list[y].country){
        return true;
    }
    else{
        if(list[x].total_profit >= list[y].total_profit){
            return true;
        }
        else
        {
            return false;
        }  
    }        
}

//helper print functions
void print_list(element list[], int size){
    cout<<"List:"<<endl;
    for(int i=0; i<size; i++){
        cout<<list[i].country<<" "<<list[i].item_type<<" "
        <<list[i].order_id<<" "<<list[i].units_sold<<" "<<list[i].total_profit<<endl;
    }
}

void print_element(element list[], int i){
    cout<<"Element:"<<endl<<list[i].country<<" "<<list[i].item_type<<" "
    <<list[i].order_id<<" "<<list[i].units_sold<<" "<<list[i].total_profit<<endl;
}

int get_pivot(int left, int right){ //Getting pivot index form a seperate fucntion to be able to change the approach of choosing pivot easily
//this sets the last element as the pivot for a deterministic approach
    return right; 
}

void swap(element list[], int x, int y){
    element temp = list[x];
    list[x] = list[y];
    list[y] = temp;
}

int partition(element list[], int left, int right, int pivot){ //partitioning is done in-place with iteration of two bars, so no extra memory needed.
    //and returns the corrected pivot position.
     //puts the pivot to rightmost index
    int blue_bar = left;
    int red_bar = left;
    
    while(true){
        
        while(is_smaller(right, blue_bar, list) && blue_bar < right){ //blue bar iterates untill an element smaller than pivot
            blue_bar++;
        }
        if (blue_bar >= right)
        {
            swap(list, red_bar, right); //after partitioning replaces the pivot to the correct place
            return red_bar; //returns the place of the pivot
        }
        swap(list, blue_bar, red_bar); 
        blue_bar++;
        red_bar++;  
    }
}

void quick_sort(element list[], int left, int right){//quicksorts indexes between left and right
    if(right <= left){
        return;
    }
    int pivot_position = partition(list, left, right, get_pivot(left, right));
    quick_sort(list, left, pivot_position - 1);
    quick_sort(list, pivot_position + 1, right);
}
