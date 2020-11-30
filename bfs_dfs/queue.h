#include <iostream>
using namespace std;

char itoc(int num){
  return char(num)+'A';
}

int ctoi(char ch){
  if(isalpha(ch)){
    return toupper(ch)-'A';
  }
  return ch-'0';
}

struct Queue{
  int info;
  Queue *link;
};

void prettify(){
  cout << "\n***********************\n";
  return;
}

Queue *FRONT = NULL;
Queue *REAR = NULL;
void Enqueue(int vertex){
  Queue *ptr = new Queue;
  ptr->link = NULL; 
  ptr->info = vertex;
  if(FRONT == NULL){
    FRONT = ptr;
    REAR = ptr;
  }else{
    REAR->link = ptr;
    REAR = ptr;
  }
  return;
}

int Dequeue(){
  if(FRONT == NULL) {
    return -1;
  }else{
    int vertex;
    Queue *temp = new Queue;
    vertex = FRONT->info;
    temp = FRONT->link;
    FRONT->link = NULL;
    FRONT = temp;
    return vertex;
  }
}
