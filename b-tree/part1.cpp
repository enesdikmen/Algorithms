//Enes Bedirhan Dikmen
//150180016
#include<iostream>
using namespace std;

char ktype;
class Node{
    public:
    int *x;
    int *y;
    char *z;
    Node **child;
    int n;
    bool leaf;

    Node(bool leaf, int t);
    int get_key(int i);   
};
Node::Node(bool nleaf, int t){
    leaf = nleaf;
    x = new int[2*t - 1];
    y = new int[2*t - 1];
    z = new char[2*t - 1];
    child = new Node*[2*t];
    n = 0;
}

int Node::get_key(int i){//returns the correct key value depending 'ktype'
    int key = 0;
    if (ktype == 'x'){
        key = x[i];
    } else if(ktype == 'y'){
        key = y[i];
    } else if(ktype == 'z'){
        key = z[i];
    }
    return key;
}
void printNode(Node *node){
    for(int i=0; i<node->n; i++){
        cout<<"("<<node->x[i]<<","<<node->y[i]<<","<<node->z[i]<<")";
    }
    cout<<endl;
}
class bTree{
    public:
    Node *root;
    int t;

    bTree(int nt){
        root = NULL;
        t = nt;
    }
    void insert(int x, int y, char z);
    void split_child(Node *x, int i, Node *y);
    void insert_nonfull(Node *nx, int x, int y, char z);
    void prefix(Node *node);
};

void bTree::prefix(Node *node){//print the tree in prefix order
    printNode(node);
    if(!node->leaf){
        for(int i=0; i<node->n+1; i++){
            prefix(node->child[i]);
        }
    }
}

void bTree::split_child(Node *x, int i, Node *y){
    Node *z = new Node(y->leaf, t);
    z->n = t - 1;
    for(int j=0; j<t-1; j++){
        z->x[j] = y->x[j+t];
        z->y[j] = y->y[j+t];
        z->z[j] = y->z[j+t];
    }
    if(!y->leaf){
        for(int j=0; j<t; j++){
            z->child[j] = y->child[j+t];  
        }
    }

    //reducing number of keys in y
    y->n = t-1;
    
    for(int j=x->n; j>=i+1; j--){//creating space for the new child
        x->child[j+1] = x->child[j];
    }

    x->child[i+1] = z;

    for(int j=x->n - 1; j>=i; j--){
        x->x[j+1] = x->x[j];
        x->y[j+1] = x->y[j];
        x->z[j+1] = x->z[j];
    }
    
    x->x[i] = y->x[t-1];
    x->y[i] = y->y[t-1];
    x->z[i] = y->z[t-1];

    x->n = x->n+1;  
}

void bTree::insert_nonfull(Node *nx, int x, int y, char z){
    int i = nx->n - 1;  
    int key = -1;
    if (ktype == 'x'){
        key = x;
    } else if(ktype == 'y'){
        key = y;
    } else if(ktype == 'z'){
        key = z;
    }
    if(nx->leaf){ //When node is a leaf node
        
        while(i >= 0 && key < nx->get_key(i)){//iterates until correct place for keys to be inserted
            //greater keys moves to next index
            
            nx->x[i+1] = nx->x[i];
            nx->y[i+1] = nx->y[i];
            nx->z[i+1] = nx->z[i];
            i--;
        }
        nx->x[i+1] = x;
        nx->y[i+1] = y;
        nx->z[i+1] = z;
        nx->n = nx->n + 1;
    }
    else{//Node is not leaf
        while(i >= 0 && key < nx->get_key(i)){//iterate until the child that wil have the key   
            i--;
        }
 
        i = i +1;  
       
        if(nx->child[i]->n == 2*t-1){ //checks if the child is full
            split_child(nx, i, nx->child[i]);
            
            if(key > nx->get_key(i)){
                i++;
            }
        }
        insert_nonfull(nx->child[i], x,y,z);
    }
}

void bTree::insert(int x, int y, char z){
    Node *r = root;
    if(root == NULL){
        root = new Node(true, t);
        root->x[0] = x;
        root->y[0] = y;
        root->z[0] = z;
        root->n = 1;
    }
    else if(r->n == 2*t-1){//when root is full

        Node *s = new Node(false, t);
        root = s;
        
        s->n = 0;
        s->child[0] = r;   
        split_child(s, 0, r);           
        insert_nonfull(s, x, y, z);
    }
    else{
        insert_nonfull(r, x, y, z);
    }
}

int main(){
    int nodenum;
    cin>>nodenum;
    int t;
    cin>>t;
    cin>>ktype;

    bTree tree(t);
    int x;
    int y;
    char z;
    for(int i=0; i<nodenum; i++){
    
        cin>>x;
        cin>>y;
        cin>>z;
        
        tree.insert(x, y, z);
    }

    tree.prefix(tree.root);  
    return 0;
}