#include "llistint.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>
using namespace std;

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

void LListInt::insert(int loc, const int& val)
{

  // create new item
  Item* newItem = new Item;
  newItem->val = val;
  newItem->prev = NULL;
  newItem->next = NULL;

  // if list empty, insert item as only item in list
  if(empty() && loc == 0){
    head_ = newItem;
    tail_ = newItem;
  }
  else {

    Item* curr = getNodeAt(loc);

    if(curr != NULL){ // within linkedlist range
    
      if(loc == 0)  // is first item
        head_ = newItem;
      else // is not first item
        curr->prev->next = newItem;

      newItem->next = curr;
      newItem->prev = curr->prev;
      curr->prev = newItem;

    }
    else { // out of range? check if loc == size
      if(loc == size_){
        newItem->prev = tail_;
        tail_->next = newItem;
        tail_ = newItem;
      }
      else {
        delete newItem;
        return;
      } // otherwise deallocate and do nothing
    }
  }

  size_++;

}

void LListInt::remove(int loc)
{

  Item* curr = getNodeAt(loc);
  if(curr != NULL){

    if(curr->prev == NULL) // HEAD
      head_ = curr->next;
    else curr->prev->next = curr->next;

    if(curr->next == NULL) // TAIL
      tail_ = curr->prev;
    else curr->next->prev = curr->prev;

    delete curr;
    size_--;

  }

}

void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int & LListInt::get(int loc) 
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

LListInt::Item* LListInt::getNodeAt(int loc) const
{
  if(loc < size_ && loc >= 0){
    Item* curr = head_;
    for(int i=1; i<=loc; i++){
      curr = curr->next;
    }
    return curr;
  }
  return NULL;
}
