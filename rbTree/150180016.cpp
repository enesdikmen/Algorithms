//Enes Bedirhan Dikmen 150180016

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

struct Node{
    
    bool color = false; //true = red, false = black; 
    string Name;
    //setting default values for variables
    int rebound = 0;    
    int assist = 0;
    int point = 0;

    Node *parent = NULL;
    Node *left = NULL;
    Node *right = NULL;

};

class RBT{
    private:
    Node *root;
    Node *max_rebounds;
    Node *max_assists;
    Node *max_points;

    public:
    RBT(){ root = NULL; max_rebounds=NULL; max_assists=NULL; max_points=NULL; }
    Node *get_root(){ return root; }
    void rbt_insert(Node*);
    void leftRotate(Node*);
    void rightRotate(Node*);

    void printPreorder(Node*, int);//prints rbt
    void fixInsertion(Node*);
    void find_max_points(Node*); //finds the player with the max points and set max_points as the player
    void find_max_rebounds(Node*);//finds the player with the max rebounds and set max_rebounds as the player
    void find_max_assists(Node*);//finds the player with the max assists and set max_assists as the player

    Node* get_max_points(){ return max_points; }
    Node* get_max_rebounds(){ return max_rebounds; }
    Node* get_max_assists(){ return max_assists; }
   
};

void RBT::printPreorder(Node *iter, int depth = 0){
    if(iter != NULL){
        for(int i=0; i<depth; i++){//this prints "-" characters according to depth of the node
            cout<<"-";
        }
        
        if(iter->color){
            cout<<"(RED) ";
        }
        else
        {
            cout<<"(BLACK) "; 
        }
        cout<<iter->Name<<endl;
        
    }
    else{
        return;
    }

    depth++;
    printPreorder(iter->left, depth);
    printPreorder(iter->right, depth);
}

void RBT::leftRotate(Node *node){ //rotates passed node to left.
    Node *node_right = node->right; 
    node_right->parent = node-> parent;
    
    if(node->parent != NULL ){ //when node to be rotated is not the root we need to reassing its parents child pointer
        if(node == node->parent->left){//when node is the left child
            node->parent->left = node_right;
        }
        else{//when node is the right child
            node->parent->right = node_right;
        }
    }
    else{//when node to be rotated's parent is null(this means it is root), right node is the new root.
        root = node_right;
    }
    node->parent = node_right;
    node->right = node_right->left;

    if(node_right->left != NULL){//reassigns node_right's left child's parent when its not null
        node_right->left->parent = node;
    }
    node_right->left = node;   
}

void RBT::rightRotate(Node *node){
    Node *node_left = node->left;
    node_left->parent = node->parent;
    if(node->parent != NULL ){ //when node to be rotated is not the root we need to reassing its parents child pointer
        if(node == node->parent->left){//when node is the left child
            node->parent->left = node_left;
        }
        else{//when node is the right child
            node->parent->right = node_left;
        }
    }
    else{//when node to be rotated's parent is null(this means it is root), left node is the new root.
        root = node_left;
    }

    node->parent = node_left;
    node->left = node_left->right;
    if(node_left->right != NULL){//reassigns node_left's right child's parent when its not null
        node_left->right->parent = node;
    }
    node_left->right = node;
}

void RBT::rbt_insert(Node *new_node){ //does regular binary search tree insertion and fixes rbt violations at the end with fixInsertion().
    Node *to_add = new Node;
    to_add->Name = new_node->Name;
    to_add->rebound = new_node->rebound;
    to_add->assist = new_node->assist;
    to_add->point = new_node->point;
    
    if(root == NULL){
        root = to_add;
        to_add->color = false; //setting color as black when its root
        return;
    }

    Node *iter = root;
    while( iter != NULL){
        if(iter->Name > to_add->Name){
            if(iter->left == NULL){
                iter->left = to_add;
                to_add->parent = iter;
                to_add->color = true; //setting color as red when inserted
                break;              
            }
            else{
                iter = iter->left;
            }
        }
        else if(iter->Name < to_add->Name){
            if(iter->right == NULL){
                iter->right = to_add;
                to_add->parent = iter;
                
                to_add->color = true; //setting color as red when inserted
                break;
            }
            else{
                iter = iter->right;
            }
        }
        else{//iter->Name == to_add->Name. when a player that already exists in tree
            iter->rebound += to_add->rebound;
            iter->assist += to_add->assist;
            iter->point += to_add->point;
            return;
        }
    }
   fixInsertion(to_add);  
}

void RBT::fixInsertion(Node *node){//checks for violations of rbt rules and fixes them
   
    Node *uncle;
    while(node != root && node->parent->color == 1){//if added node's parent color is black ther is no need to fix anything
        if(node->parent == node->parent->parent->left){//when parent node is left child of grandparent
            uncle = node->parent->parent->right;
           
             
            if(uncle != NULL && uncle->color == 1){ //checking uncle color if red
                
                //when uncle is red too we fix the tree just by recoloring parent and uncle to black and grandparet to red
                uncle->color = false;
                node->parent->color = false;
                node->parent->parent->color = true;

                node = node->parent->parent;

            }
            
            else{//when uncle is not red(NULL or BLACK)
                if(node == node->parent->right){//when grandparent is left child and parent is right child
                //in this case wee need to rotate the parent to left
                    node = node->parent; 
                    leftRotate(node);
                }
                //if node is left child of the parent we do right rotation and recolor parent and sibling nodes
                node->parent->color = false;
                node->parent->parent->color = true;
                rightRotate(node->parent->parent);
            }       
        }
        else{//when parent node is right child of grandparent
            uncle = node->parent->parent->left; 
            if(uncle != NULL && uncle->color == 1){
                //when uncle is red too we fix the tree just by recoloring parent and uncle to black and grandparet to red

                uncle->color = false;
                node->parent->color = false;
                node->parent->parent->color = true;

                node = node->parent->parent;

            }
            else{//when uncle is not red(NULL or BLACK)
                if(node == node->parent->left){//when grandparent is right child and parent is left child
                //in this case wee need to rotate the parent to right
                    node = node->parent; 
                    rightRotate(node);
                }
                //if node is right child of the parent we do left rotation and recolor parent and sibling nodes
                node->parent->color = false;
                node->parent->parent->color = true;
                leftRotate(node->parent->parent);

            }

        } 
    }
    root->color = false;//set the root as black since root node might be changed
}

void RBT::find_max_points(Node *iter){
    if(iter == NULL){
        return;
    }
    if(iter == get_root()){ //at the first recursion of the search sets the plyer with max points as the root
        max_points = iter;
    }
    
    if(iter->point > max_points->point){
        max_points = iter;
    }
    find_max_points(iter->left);
    find_max_points(iter->right);
}

void RBT::find_max_rebounds(Node *iter){
    if(iter == NULL){
        return;
    }
    if(iter == get_root()){ //at the first recursion of the search sets the player with max rebounds as the root
        max_rebounds = iter;
    }
    
    if(iter->rebound > max_rebounds->rebound){
        max_rebounds = iter;
    }
    find_max_rebounds(iter->left);
    find_max_rebounds(iter->right);
}

void RBT::find_max_assists(Node *iter){
    if(iter == NULL){
        return;
    }
    if(iter == get_root()){ //at the first recursion of the search sets the plyer with max assists as the root
        max_assists = iter;
    }
    
    if(iter->assist > max_assists->assist){
        max_assists = iter;
    }
    find_max_assists(iter->left);
    find_max_assists(iter->right);
}


int main(int argc, char *argv[]){
    
    
    ifstream file;
    file.open((string)argv[1]);
    if (!file){
		cerr << "File cannot be opened!";
		exit(1);
	}
    
    RBT rbt;
    Node *new_node = new Node;
    string season;
    int seasons = 0;
    Node *to_print;

    string line;
    getline(file, line); //reads the header line 
    while(!file.eof()){ //reads a line
        getline(file, line, ','); //reads the season
        //cout<<"season: "<<line;
        if(seasons == 0){ //beginning of the first season
            season = line;
            seasons++; 
        }
        else if(line != season){//beginning of the other seasons
            cout<<"End of "<<season<<" Season"<<endl;
            
            rbt.find_max_points(rbt.get_root());
            to_print = rbt.get_max_points();
            cout<<"Max Points: "<<to_print->point<<" - Player Name: "<<to_print->Name<<endl;

            rbt.find_max_assists(rbt.get_root());
            to_print = rbt.get_max_assists();
            cout<<"Max Assists: "<<to_print->assist<<" - Player Name: "<<to_print->Name<<endl;

            rbt.find_max_rebounds(rbt.get_root());
            to_print = rbt.get_max_rebounds();
            cout<<"Max Rebs: "<<to_print->rebound<<" - Player Name: "<<to_print->Name<<endl;

            if(seasons == 1){//print red black tree at the end of the first season
                rbt.printPreorder(rbt.get_root());
            }
            season = line;
            seasons++;
        }
        getline(file, line, ','); //reads the name
        new_node->Name = line;

        getline(file, line, ','); //reads the team
        
        
        getline(file, line, ','); //reads the rebound
        new_node->rebound = stoi(line);

        getline(file, line, ','); //reads the assist
        new_node->assist = stoi(line);
        
        getline(file, line, '\n'); //reads the point
        new_node->point = stoi(line);
        rbt.rbt_insert(new_node);
        
    }

    //prints the season information for the last season
    cout<<"End of "<<season<<" Season"<<endl;
                 
    rbt.find_max_points(rbt.get_root());
    to_print = rbt.get_max_points();
    cout<<"Max Points: "<<to_print->point<<" - Player Name: "<<to_print->Name<<endl;

    rbt.find_max_assists(rbt.get_root());
    to_print = rbt.get_max_assists();
    cout<<"Max Assists: "<<to_print->assist<<" - Player Name: "<<to_print->Name<<endl;

    rbt.find_max_rebounds(rbt.get_root());
    to_print = rbt.get_max_rebounds();
    cout<<"Max Rebs: "<<to_print->rebound<<" - Player Name: "<<to_print->Name<<endl;
    
    file.close();
    return 0;
}