/*Binary Heaps are a common data structure in the world
of computer science. Utilizing templates, this program
can create a "D-ary Heap". In a binary heap, each node has
2 children at most; in a D-ary Heap, each node has D children
at most.

This code constructs a MinHeap in particular.*/
#include <vector>
#include <iostream> //for debugging purposes

template <typename T>
 class MinHeap {
    public:
      MinHeap (int d);
      /* Constructor that builds a d-ary Min Heap
         This should work for any d >= 2,
         but doesn't have to do anything for smaller d.*/

      ~MinHeap ();

      int add (T item, int priority);
        /* adds the item to the heap, with the given priority.
           multiple identical items can be in the heap simultaneously.
           Returns the number of times add has been called prior to this
           call (for use with the update function).*/

      const T & peek () const;
        /* returns the element with smallest priority.
           If two elements have the same priority, use operator< on the
           T data, and return the one with smaller data.*/

      void remove ();
        /* removes the element with smallest priority, with the same tie-breaker
           as peek. */

      void update (int nth, int priority);
        /* finds the nth item (where nth is 0-based) that has ever been added
           to the heap (the node that was created on the nth call to add),
           and updates its priority accordingly. */

      bool isEmpty ();
        /* returns true iff there are no elements on the heap. */

  private:
     // whatever you need to naturally store things.
     // You may also add helper functions here.
     struct Node{
       Node(T& item, int pr);
       T item;
       int priority;
       int position;//the node's position in the heap
     };

     void bubble_up(int pos);/*organizes nodes after call to add*/
     void trickle_down(int pos);/*organizes nodes after call to remove*/


     int add_counter; //variable that tracks calls to add
     int d_ary; //variable that holds d-ary typing of graph
     std::vector<Node> d_heap; //vector that will help build initial heap structure
     std::vector<Node> order_added;//vector that keeps track of order nodes added
   };

     template<typename T>
     MinHeap<T>::Node::Node(T& item, int pr) : item(item), priority(pr){//Node constructor
       position = 0;
     }

     template<typename T>
     MinHeap<T>::MinHeap(int d){//Heap constructor
       if(d >= 2)
       {
       add_counter = 0;
       d_ary = d;
       }
     }

     template<typename T>
     bool MinHeap<T>::isEmpty(){
       if(d_heap.size() == 0)
       {
       return true;
       }
       return false;
     }

     template<typename T>
     void MinHeap<T>::bubble_up(int pos){ //handling sorting after add call
       if(pos > 0 && d_heap[pos].priority < d_heap[(pos-1)/d_ary].priority){//comparing item to parent
         //if item smaller, needs to be swapped with parent
         Node temp = d_heap[pos];
         d_heap[pos] = d_heap[(pos-1)/d_ary];
         d_heap[pos].position = pos;//resetting node's position tracking
         d_heap[(pos-1)/d_ary] = temp;
         d_heap[(pos-1)/d_ary].position = (pos-1)/d_ary;//resetting node's position tracking
         bubble_up((pos-1)/d_ary);//recursively calling bubble_up on parent
       }
       return;
     }

     template<typename T>
     void MinHeap<T>::trickle_down(int pos){ //handling sorting after remove
       int child = (d_ary * pos) + 1; //finding index for first of d child nodes
       if(child < (int)d_heap.size())
       {
         int min_child = child;
         for(int i = child; i <= child+(d_ary - 1); i++){
           if(i < (int)d_heap.size()){
           if(d_heap[i].priority < d_heap[min_child].priority){
             min_child = i;
           }
         }
         }
         child = min_child;
         if(d_heap[child].priority < d_heap[pos].priority){
           Node temp = d_heap[pos];
           d_heap[pos] = d_heap[child];
           d_heap[pos].position = pos;
           d_heap[child] = temp;
           d_heap[child].position = child;
           trickle_down(child);
         }
       }
     }

     template<typename T>
     int MinHeap<T>::add(T item, int priority){/*adding a node to heap;
         need to organize heap here as well*/
       ++add_counter;
       Node new_node(item,priority);
       d_heap.push_back(new_node);
       order_added.push_back(new_node);
       new_node.position = d_heap.size() - 1;
       bubble_up(d_heap.size() - 1);
       return add_counter;
     }

     template<typename T>
     void MinHeap<T>::remove(){/*removing top node from heap; need to organize
       heap here as well*/
       //swap top node with bottomost, then trickle_down
       //this code works with a heap of size 1 as well
         Node temp = d_heap[0];
         d_heap[0] = d_heap[d_heap.size() - 1];
         d_heap[d_heap.size() - 1] = temp;
         d_heap.pop_back();
         trickle_down(0);
     }

     template<typename T>
     const T & MinHeap<T>::peek() const{
       return d_heap[0].item;//returning pointer to item at top of heap
     }

     template<typename T>
     void MinHeap<T>::update(int nth, int priority){
       if(priority > order_added[nth - 1].priority){
         order_added[nth - 1].priority = priority;
         trickle_down(order_added[nth - 1].position);
       }else if(priority < order_added[nth - 1].priority){
         order_added[nth - 1].priority = priority;
         bubble_up(order_added[nth - 1].position);
       }
     }

     template<typename T>
     MinHeap<T>::~MinHeap(){

     }
