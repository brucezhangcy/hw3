#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  void trickleUp(size_t loc);
  void trickleDown(size_t loc);

  std::vector<T> data_;
  int m_;
  PComparator c_;
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) : m_(m), c_(c)
{
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  data_.push_back(item);
  trickleUp(data_.size() - 1);
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return data_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return data_.size();
}

// Move the item at loc up while it has priority over its parent.
// The parent of index i is (i-1)/m.
template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(size_t loc)
{
  while(loc > 0) {
    size_t parent = (loc - 1) / m_;
    if(c_(data_[loc], data_[parent])) {
      std::swap(data_[loc], data_[parent]);
      loc = parent;
    }
    else {
      break;
    }
  }
}

// Move the item at loc down while one of its children has priority over it.
// The children of index i are m*i+1 through m*i+m.
template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleDown(size_t loc)
{
  while(true) {
    size_t firstChild = m_ * loc + 1;
    if(firstChild >= data_.size()) {
      break; // loc is a leaf
    }

    // Find the child with the best priority
    size_t best = firstChild;
    for(size_t i = 1; i < (size_t) m_; i++) {
      size_t child = firstChild + i;
      if(child >= data_.size()) {
        break;
      }
      if(c_(data_[child], data_[best])) {
        best = child;
      }
    }

    if(c_(data_[best], data_[loc])) {
      std::swap(data_[best], data_[loc]);
      loc = best;
    }
    else {
      break;
    }
  }
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data_[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  // Move the last item to the root, remove the last slot, then fix the heap
  data_[0] = data_.back();
  data_.pop_back();
  if(!data_.empty()) {
    trickleDown(0);
  }
}



#endif

