#include <algorithm>
#include<iostream>
// #include <cstdio>

using std::cout;
using std::cin;

template<typename T>

struct vector{
  explicit vector(int initialSize = 0) : size {initialSize} , capacity{initialSize + SPARE_CAPACITY}
  {
    objects = new T[capacity];
  }

  vector(const vector& other) : size{other.size}, capacity{other.capacity}, objects{nullptr}
  {
    objects = new T[capacity];
    for(size_t i{} ; i < size ; ++i)
      objects[i] = other.objects[i];
  }

  vector & operator = (const vector& other)
  {
    if(this == &other) return *this;
    vector copy = other;
    std::swap(*this,copy);
    return *this;
  }

  vector(vector && other) noexcept : size{other.size}, capacity{other.capacity},objects{other.objects}
  {
    other.objects = nullptr;
    other.size = 0;
    other.capacity = 0;
  }

  vector & operator = (vector&& other) noexcept {
    if(this == &other) return *this;
    std::swap(size,other.size);
    std::swap(capacity,other.capacity);
    std::swap(objects,other.objects);

    return *this;
  }
  ~vector() {delete[] objects;}

  void resize(int newSize){
    if(newSize > capacity) reserve(newSize * 2);
    size = newSize;
  }
  void reserve(int newCapacity){
    if(newCapacity < size) return;
    T* newArr = new T[newCapacity];
    for(size_t i{} ; i < size ; ++i)
      newArr[i] = std::move(objects[i]);
    capacity = newCapacity;
    std::swap(objects,newArr);
    delete[] newArr;
  }

  T& operator[](int index)
  {return objects[index];}
  const T& operator[](int index) const
  {return objects[index];}

  bool empty() const {return getSize() == 0;}
  int getSize() const {return size;}
  int getCapacity() const{return capacity;}

  void push_back(const T& x)
  {
    if(size == capacity) reserve(2 * capacity + 1);
    objects[size++] = x;
  }
  void push_back(T&& x)
  {
    if(size == capacity) reserve(2 * capacity + 1);
    // cout << size << " " << capacity << " ";
    objects[size++] = std::move(x);
  }
  void pop_back(){--size;}
  const T & back() const{return objects[size - 1];}
  typedef T* iterator;
  typedef const T * const_iterator;
  iterator begin()
  {return &objects[0];}
  const_iterator begin() const
  { return &objects[0];}
  iterator end()
  {return &objects[getSize()];}
  const_iterator end() const
  { return &objects[getSize()];}



  static const int SPARE_CAPACITY = 16;
private:
  int size;
  int capacity;
  T* objects;
};

int main(){
  vector<int> v{};
  v.push_back(3);
  v.push_back(10);
  v.push_back(20);
  // printf("%d",v[0]);

  cout << v[0] << " "<< v[1] << " " << v[2] << " ";
}
