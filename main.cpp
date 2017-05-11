#include "Test.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> heapify(vector<int> min_heap, int index);
vector<int> swap(vector<int> min_heap, int i, int pos)
{
    int t_pos = 0;
    t_pos = min_heap[i];
    min_heap[i] = min_heap[pos];
    min_heap[pos] = t_pos;
    return min_heap;
}

int get_last_children_pos(vector<int> min_heap, int index){
    return (index*2 + 1) < (index*2 + 2) ? (index*2 + 1) : (index*2 + 2);
}

bool less_than_father(vector<int> min_heap, int index){
    if((index % 2) == 0 && min_heap[index] < min_heap[(index - 2) / 2]) return true;
    else if((index % 2) != 0 && min_heap[index] < min_heap[(index - 1) / 2]) return true;
    return false;
}

bool is_this_leaf(vector<int> min_heap, int index){
    return (index*2 + 1) > min_heap.size() - 1 ? true : false;
}

int get_heap_pos(vector<int> min_heap, int search_value){
    return std::find(min_heap.begin(), min_heap.end(), search_value) - min_heap.begin();
}

vector<int> get_heap_fixed_children(vector<int> min_heap, int index){
  if(is_this_leaf(min_heap, index)) return min_heap;
  int i = get_last_children_pos(min_heap, index);
  vector<int> swapped_heap = swap(min_heap, index, i);
  if(min_heap[index] > min_heap[i])
      return heapify(swapped_heap, i);
  return min_heap;
}

vector<int> heapify(vector<int> min_heap, int index){
    if(index <= 0) return get_heap_fixed_children(min_heap, index);
    else{
      if(less_than_father(min_heap, index)){
          int pos = (index % 2) != 0 ? (index - 1) / 2 : (index - 2) / 2;
          return heapify(swap(min_heap, index, pos), pos);
      }
      else return get_heap_fixed_children(min_heap, index);
    }
}

vector<int> replace(vector<int> min_heap, int search_value, int replacement){
    int index = get_heap_pos(min_heap, search_value);
    min_heap[index] = replacement;
    return heapify(min_heap, index);
}

int main (){
    test();
    return 0;
}
