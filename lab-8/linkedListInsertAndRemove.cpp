#include<bits/stdc++.h>
#include<omp.h>
using namespace std; 
#define NUM_THREADS 4

class Node{
public:
    Node*next; 
    int val;
    omp_lock_t writeLock; 

    Node(int v){
        val = v; 
        omp_init_lock(&writeLock); 
    }
};

void print(Node* sup_head){
    Node* h = sup_head ;
    while(h){
        cout<<h->val<<' '; 
        h = h->next; 
    }
    cout<<endl;
    return;
}

Node* contain(Node* sup_head, int val){
    Node*h = sup_head ;
    Node*c = h->next ;
    omp_set_lock(&(h->writeLock)); 
    omp_set_lock(&(c->writeLock)); 
    while(c->val!=-1 && c->val != val){
        omp_set_lock(&(c->next->writeLock)); 
        omp_unset_lock(&(h->writeLock));
        c = c->next;
        h = h->next;
    }
    
    if(c->val == -1){
        omp_unset_lock(&(h->writeLock)); 
        omp_unset_lock(&(c->writeLock)); 
        return NULL; 
    }
    return h; 
    
}   

void remove(Node* sup_head, int val){
    #pragma omp critical 
    {
        cout<<"Inserting "<<val<<" by thread "<<omp_get_thread_num()<<endl ;
    }
    Node*n = new Node(val); 
    Node* h = contain(sup_head, val);  
    if(h==NULL){
        #pragma omp critical 
        {
            cout<<val<<" Not in list"<<endl ;
        }
        return ;
    }
    Node*c = h->next ;
    h->next = c->next; 
    c->next = NULL ;
    omp_unset_lock(&(h->writeLock)); 
    omp_unset_lock(&(c->writeLock)); 
    delete c; 
    #pragma omp critical 
    {
        print(sup_head); 
    }
}

Node* searchPos(Node* sup_head, int val){
    Node*h = sup_head ;
    Node*c = h->next ;
    // tail and pos not reached
    omp_set_lock(&(h->writeLock)); 
    omp_set_lock(&(c->writeLock)); 
    while(c->val!=-1 && c->val < val){
        omp_set_lock(&(c->next->writeLock)); 
        omp_unset_lock(&(h->writeLock));
        c = c->next;
        h = h->next;
    }
    return h;
}



void insert(Node* sup_head, int val){
    #pragma omp critical 
    {
        cout<<"Inserting "<<val<<" by thread "<<omp_get_thread_num()<<endl ;
    }
    Node*n = new Node(val); 
    Node* h = searchPos(sup_head, val);  
    Node*c = h->next; 
    n->next = c; 
    h->next = n; 

    omp_unset_lock(&(h->writeLock)); 
    omp_unset_lock(&(c->writeLock)); 

    #pragma omp critical 
    {
        print(sup_head); 
    }
}



int main(){


    // fill the linked list 
    Node* sup_head = new Node(-1), *sup_tail = new Node(-1); 
    sup_head->next = sup_tail; 

    int arr[] = {1, 5, 2, 3}; 
    #pragma omp parallel for
    for(int i = 0 ; i<4 ; i++){
        insert(sup_head, arr[i]); 
    }
    int arr1[] = {1,4,3,2}; 
    #pragma omp parallel for
    for(int i = 0 ; i<4 ; i++){
        remove(sup_head, arr1[i]); 
    }
    // print(sup_head); 

    return 0; 
}