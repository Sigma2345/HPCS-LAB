#include<bits/stdc++.h>
#include<omp.h>
using namespace std ;
#define NUM_THREADS 10
#define LEVEL 2

class TreeNode{
  
public: 
  TreeNode* left;
  TreeNode* right; 
  int val; 

  TreeNode(int v){
    left = right = NULL ;
    val = v; 
  }

};


// construct tree given certain number of levels
TreeNode* construct_tree(TreeNode* t,int level){
  if(level == LEVEL){
    return NULL ;
  }

  t->left = new TreeNode(rand()%100 + 1); 
  t->right = new TreeNode(rand()%100 + 1); 

  construct_tree(t->left, level+1); 
  construct_tree(t->right, level+1); 

  return t; 

}

void print_tree(TreeNode* t){
  if(!t) return;
  cout<<t->val<<' '; 
  print_tree(t->left); 
  print_tree(t->right); 
}

void traverse(TreeNode* root){
  
  if(root == NULL) return; 

#pragma omp task  untied
{
  traverse(root->left); 
}
#pragma omp task untied
{
  traverse(root->right); 
}
#pragma omp taskwait 

  #pragma omp critical
  {
    cout<<"("<<root->val<<","<<omp_get_thread_num()<<")"<<' '; 
  }
}


int main(){

  omp_set_num_threads(NUM_THREADS); 

  TreeNode* root = new TreeNode(rand()%100); 
  root = construct_tree(root, 0);

  // print_tree sequential
  double s1 = omp_get_wtime(); 
  print_tree(root); 
  double e1 = omp_get_wtime(); 
  cout<<endl<<e1-s1<<endl ;
  cout<<"----------------- PARALLEL TRAVERSAL --------------------------"<<endl ;
  double s2 = omp_get_wtime(); 
#pragma omp parallel 
{
  #pragma omp single
    // cout<<"EXECUTING THREAD: "<<omp_get_thread_num()<<"/"<<omp_get_num_threads()<<endl; 
    traverse(root); 
}
// #pragma omp taskwait
  double e2 = omp_get_wtime(); 

  cout<<endl<<e2-s2<<endl ;

  return 0; 
}
