#include <iostream>
#include <ctype.h>
#include <string.h>
#define MAXSIZE 1000
#define ERROR_STATUS -1
using namespace std;

class HEAP{
  private: 
    int heap[MAXSIZE];
    int current_node;
  public: 
    HEAP(): current_node{-1} {}
    void insert_heap(int key);
    int delete_heap(int);
    int get_parent(int i) { return (i%2 == 0) ? i/2-1 : i/2; }
    int get_no_of_nodes() { return current_node+1; }
    void swap_heap(int i, int j){
      int temp;
      temp = heap[i], heap[i]  = heap[j], heap[j]  = temp;
      return;
    }
    void print_heap(int arr[], int, string);
};

// PRINT ARRAY WITH MSG
void HEAP::print_heap(int arr[], int size, string msg){
  cout << msg;
  for(int i = 0; i < size; i++){
    cout << arr[i];
    if(i != size-1) cout << ", ";
  }
  cout << endl;
}

// INSERT ELEMENTS AT APPROPRIATE POSITION IN HEAP
void HEAP::insert_heap(int key){
  if(++current_node >= MAXSIZE) {
    cout << "Segmentation Fault";
    return;
  }
  int ptr = current_node;
  heap[ptr] = key;
  int parent;
  if((parent = get_parent(ptr)) == ERROR_STATUS) { return; }
  while(heap[ptr] > heap[parent]){
    swap_heap(ptr, parent);
    parent = get_parent(ptr = parent);
    if(parent == ERROR_STATUS) { break; }
  }
  print_heap(heap, current_node+1, "current heap is: ");
  return;
}

// DELETE HEAP ELEMENT
int HEAP::delete_heap(int loc){
  if(loc > current_node || loc < 0) {
    cout << "Segmentation Fault";
    return ERROR_STATUS;
  }
  int save = heap[loc];
  int key = heap[loc] = heap[current_node];
  heap[current_node--] = ERROR_STATUS;
  if(current_node == -1) { return key; }
  int left = 2*loc+1;
  int right = 2*loc+2;
  while(right <= current_node){
    if(key < heap[left] || key < heap[right]){
      if(heap[left] < heap[right]){
        swap_heap(loc, right);
        loc = right;
      }else{
        swap_heap(loc, left);
        loc = left;
      }
    }else{
      break;
    }
    left = 2*loc + 1;
    right = 2*loc + 2;
    key = heap[loc];
  }
  if(left == current_node) {
    if(heap[loc] < heap[left]){
      swap_heap(loc, left);
    }
  }
  print_heap(heap, current_node+1, "Updated Heap is: "); 
  return save;
}

int main(){
  HEAP H;
  int num;
  while(cin >> num && num != ERROR_STATUS){
    H.insert_heap(num);
  }
  // PART A
  cout << "Enter loc to be deleted: ";
  while(cin >> num){
    if(num < 0) { break; }
    cout << H.delete_heap(num);
    cout << "Enter loc to be deleted: ";
  }
  return 0;
}
