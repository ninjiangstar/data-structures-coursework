#ifndef MINHEAP_H
#define MINHEAP_H

#include <utility>
#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class MinHeap {
public:
    MinHeap (int d, T init);
    ~MinHeap (){};

    void add (const T & item, const double & priority); // add item to heap, with priority
    const T & peek () const; // returns element with smallest priority
    void remove (); // removes element with smallest priority
    bool isEmpty () const; // returns true iff no elements in heap

private:
    vector<pair<double, T> > heap;
    int ary;

    void trickleUp(int i);
    void trickleDown(int i);
};

template<typename T>
MinHeap<T>::MinHeap (int d, T init) : ary(d)
{
    heap.push_back(pair<double, T>(NULL, init)); // init should be null
}

template <typename T>
void MinHeap<T>::add(const T & item, const double & priority)
{
    this->heap.push_back(pair<double, T>(priority, item)); // add item
    this->trickleUp(this->heap.size() - 1); // sort
}

template <typename T>
const T & MinHeap<T>::peek () const
{
    return this->heap[1].second;
}

template <typename T>
void MinHeap<T>::remove()
{
    this->heap[1] = this->heap.back();
    this->heap.pop_back(); // move last item to top
    this->trickleDown(1); // sort
}

template <typename T>
bool MinHeap<T>::isEmpty() const
{
    return this->heap.size() <= 1;
}

template <typename T>
void MinHeap<T>::trickleUp(int i)
{
    if(i < 1) return; // at the top

    int step = (i - 2) / this->ary + 1;

    // parent is bigger? swap.
    if(this->heap[step].first > this->heap[i].first){ 
        this->heap[step].swap(this->heap[i]);
        trickleUp(step);
    }
}

template <typename T>
void MinHeap<T>::trickleDown(int i)
{
    if(isEmpty()) return; // is empty, can't trickle down

    int beforeChild = this->ary * (i - 1) + 1;
    int bestChild = beforeChild + 1;

    if(bestChild >= (int)this->heap.size()) return; // out of range

    // find smallest priority among children
    for(int child = 1; child <= this->ary; child++){
        if(beforeChild + child >= (int)this->heap.size()) break; // out of range
        if(this->heap[bestChild].first > this->heap[beforeChild + child].first)
            bestChild = beforeChild + child;
    }
    
    // if child is smaller than parent, swap
    if(this->heap[bestChild].first < this->heap[i].first){
        this->heap[bestChild].swap(this->heap[i]);
        trickleDown(bestChild);
    }
}

#endif