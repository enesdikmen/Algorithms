//Enes Bedirhan Dikmen
//150180016
#include<iostream>
#include<string>
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
    int find_key(int k);
    int get_key(int i);
    int *get_pred(int in);
    int *get_succ(int in);   
    void merge(int in);
    void borrow_prev(int in);
    void borrow_next(int in);
    void remove_fromleaf(int in);
    void remove_fromNonleaf(int in);
    void fill(int in);
    void remove(int k);

    
};
Node::Node(bool nleaf, int t){
    leaf = nleaf;
    x = new int[2*t - 1];
    y = new int[2*t - 1];
    z = new char[2*t - 1];
    child = new Node*[2*t];
    n = 0;
}
int Node::find_key(int k){
    int in = 0;
    while(in < n && get_key(in) < k){
        ++in;
    }

    return in;
}

int t_g;

int Node::get_key(int i){//returns the correct key value depending 'ktype'
    int key = -1;
    if (ktype == 'x'){
        key = x[i];
    } else if(ktype == 'y'){
        key = y[i];
    } else if(ktype == 'z'){
        key = z[i];
    }
    return key;
}
int getKey(int x, int y, char z){
    int key = -1;
    if (ktype == 'x'){
        key = x;
    } else if(ktype == 'y'){
        key = y;
    } else if(ktype == 'z'){
        key = z;
    }
    return key;
}
int *Node::get_pred(int in){//gets predecessor of in'th key
    Node *temp = child[in];
    while(!temp->leaf){
        temp = temp->child[temp->n];
    }

    int *keys = new int[3];
    keys[0] = temp->x[temp->n-1];
    keys[1] = temp->y[temp->n-1];
    keys[2] = temp->z[temp->n-1];

    return keys;
}

int *Node::get_succ(int in){//gets successor of in'th key
    Node *temp = child[in+1];
    while(!temp->leaf){
        temp = temp->child[0];
    }

    int *keys =new int[3];
    keys[0] = temp->x[0];
    keys[1] = temp->y[0];
    keys[2] = temp->z[0];

    return keys;    
}

void Node::merge(int in){//merges in child with in+1
    Node *nchild = child[in];
    Node *sibling = child[in + 1];
    
    nchild->x[t_g-1] = x[in];
    nchild->y[t_g-1] = y[in];
    nchild->z[t_g-1] = z[in];

    for(int i=0; i<sibling->n; ++i){
        nchild->x[i+t_g] = sibling->x[i];
        nchild->y[i+t_g] = sibling->y[i];
        nchild->z[i+t_g] = sibling->z[i];
    }

    if(!nchild->leaf){
        for(int i=0; i<=sibling->n; ++i){
            nchild->child[i+t_g] = sibling->child[i];
        }
    }

    for(int i=in+1; i<n; ++i){
        x[i-1] = x[i];
        y[i-1] = y[i];
        z[i-1] = z[i];
    }

    for(int i=in+2; i<=n; ++i){
        child[i-1] = child[i];
    }

    nchild->n += sibling->n+1;
    n--;
    delete(sibling);
    return;

}

void Node::borrow_prev(int in){//borrows key from previous node and inserts it
    Node *nchild = child[in];
    Node *sibling = child[in-1];

    for(int i=nchild->n; i>=0; --i){
        nchild->x[i+1] = nchild->x[i];
        nchild->y[i+1] = nchild->y[i];
        nchild->z[i+1] = nchild->z[i];
    }


    if(!nchild->leaf){
        for(int i=nchild->n; i>=0; --i){
            nchild->child[i+1] = nchild->child[i];
        }
    }

    nchild->x[0] = x[in-1];
    nchild->y[0] = y[in-1];
    nchild->z[0] = z[in-1];

    if(!nchild->leaf){
        nchild->child[0] = sibling->child[sibling->n];
    }

    x[in-1] = sibling->x[sibling->n-1];
    y[in-1] = sibling->y[sibling->n-1];
    z[in-1] = sibling->z[sibling->n-1];

    nchild->n += 1;
    sibling-> n -= 1;

}

void Node::borrow_next(int in){//borrows key from next node and inserts it
    Node *nchild = child[in];
    Node *sibling = child[in+1];

    nchild->x[nchild->n] = x[in];
    nchild->y[nchild->n] = y[in];
    nchild->z[nchild->n] = z[in];

    if(!nchild->leaf){
        nchild->child[nchild->n+1] = sibling->child[0];
    }

    x[in] = sibling->x[0];
    y[in] = sibling->y[0];
    z[in] = sibling->z[0];

    for(int i=1; i<sibling->n; ++i){
        sibling->x[i-1] = sibling->x[i];
        sibling->y[i-1] = sibling->y[i];
        sibling->z[i-1] = sibling->z[i];
    }

    if(!sibling->leaf){
        for(int i=1; i<=sibling->n; ++i){
            sibling->child[i-1] = sibling->child[i];
        }
    }

    nchild->n += 1;
    sibling->n -= 1;


}

void Node::remove_fromleaf(int in){//removes in'th key from the node
    for(int i=in+1; i<n; ++i){
        x[i-1] = x[i];
        y[i-1] = y[i];
        z[i-1] = z[i];
    }
    n -= 1;
}

void Node::remove_fromNonleaf(int in){//removes in'th key from the node
    int k = get_key(in);

    if(child[in]->n >= t_g){
        int *pred = get_pred(in);
        x[in] = pred[0];
        y[in] = pred[1];
        z[in] = pred[2];

        child[in]->remove(getKey(pred[0], pred[1], pred[2]));

    }
    else if(child[in+1]->n >= t_g){
        int *succ = get_succ(in);
        x[in] = succ[0];
        y[in] = succ[1];
        z[in] = succ[2];

        child[in+1]->remove(getKey(succ[0], succ[1], succ[2]));
    } 
    else{
        merge(in);
        child[in]->remove(k);
    }
}

void Node::fill(int in){//fill the child[in] that has less than t-1 keys
    if(in!=0 && child[in-1]->n >= t_g){
        borrow_prev(in);
    }
    else if(in!=n && child[in+1]->n>=t_g){
        borrow_next(in);
    }
    else{
        if(in != n){
            merge(in);
        }
        else{
            merge(in-1);
        }
    }
}

void Node::remove(int k){//removes the key group with choosen key k
    int in = find_key(k);

    if(in < n && get_key(in) == k){
        if(leaf){
            remove_fromleaf(in);
        }
        else{
            remove_fromNonleaf(in);
        }
    }
    else{

        if(leaf){
            return;
        }

        bool flag = false;
        if(in == n){
            flag = true;
        }
        

        if(child[in]->n < t_g){
            fill(in);
        }

        if(flag && in>n){
            child[in-1]->remove(k);
        }
        else{
            child[in]->remove(k);
        }
    }

    
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
    void remove(int k);
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

void bTree::remove(int k){//removes given key from tree
    
    root->remove(k);
}


int main(){
    int nodenum;
    cin>>nodenum;
    int t;
    cin>>t;
    t_g = t;
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
    string to_delete;
    cin>>to_delete;
    if((int)to_delete[0] >= 65 && (int)to_delete[0] <= 122){//when to delete key is a character
        tree.remove(to_delete[0]);
    }
    else{//when its a number
        tree.remove(stoi(to_delete));
    }

    tree.prefix(tree.root);  
    return 0;
}