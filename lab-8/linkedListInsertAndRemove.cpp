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

// void remove(Node* sup_head){

// }

// Node* contain(Node* sup_head){

// }

pair<Node*, Node*> searchPos(Node* sup_head, int val){
    Node*h = sup_head ;
    Node*c = h->next ;
    // tail and pos not reached
    while(c->val != -1 && c->val < val){
        h = h->next; 
        c = c->next; 
    }   

    omp_set_lock(&(h->writeLock)); 
    omp_set_lock(&(c->writeLock)); 
    return {h,c}; 
}

void print(Node* sup_head){
    Node* h = sup_head ;
    while(h){
        cout<<h->val<<' '; 
        h = h->next; 
    }
    cout<<endl;
    return;
}

void insert(Node* sup_head, int val){
    #pragma omp critical 
    {
        cout<<"Inserting "<<val<<" by thread "<<omp_get_thread_num()<<endl ;
    }
    //search for pos

    auto x = searchPos(sup_head, val); 
    Node*pos = x.first, pos1 = x.second; 

    #pragma omp critical 
    {
        if(pos->next != pos1){
            omp_unset_lock(&(pos->writeLock)); 
            omp_unset_lock(&(pos1->writeLock));      
                   
        }

    }

    // lock pos and nextpos
    // omp_set_lock(&(pos->writeLock)); 
    // omp_set_lock(&(next_pos->writeLock)); 

    #pragma omp critical 
    {
        cout<<"Inserting "<<val<<" by thread "<<omp_get_thread_num()<<" Acquired lock on values"<<endl ;
    }

    Node* n = new Node(val); 
    pos->next = n; 
    n->next = next_pos; 

    // unlock pos and nextpos
    omp_unset_lock(&(pos->writeLock)); 
    omp_unset_lock(&(next_pos->writeLock)); 

    #pragma omp critical 
    {
        cout<<"Freed locks by thread "<<omp_get_thread_num()<<endl ;
        print(sup_head); 
    }

}



int main(){


    // fill the linked list 
    Node* sup_head = new Node(-1), *sup_tail = new Node(-1); 
    sup_head->next = sup_tail; 

    int arr[] = {1, 2, 3}; 
    #pragma omp parallel for
    for(int i = 0 ; i<3 ; i++){
        insert(sup_head, arr[i]); 
    }

    print(sup_head); 

    return 0; 
}