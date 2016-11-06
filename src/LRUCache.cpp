#include <unordered_map>
#include <algorithm>
#include <iostream>
// LRU CACHE IMPLEMENTATION
template<class K, class V>
class LRUCache {

private:
  template <class NV, class I>
  class Node {
  public:
    typedef Node<NV, I> * pNode;

    I hashIter;
    NV value;
    pNode prev;
    pNode next;


    Node(): prev(nullptr), next(nullptr) {}
    Node(NV value): value(std::move(value)), prev(nullptr), next(nullptr) {}

    void swap(Node & other) {
      using std::swap;
      swap(this->hashIter, other.hashIter);
      swap(this->value, other.value);
      swap(this->prev, other.prev);
      swap(this->next, other.next);
    }

    // move constructor
    Node(Node && other) : Node() {
        swap(other);
        other.prev = other.next = nullptr;
    }

    Node& operator=(Node other) {
        swap(other);
        return *this;
    }
  };

private:
  typedef typename std::unordered_map<K, int>::iterator HashIterator;
  typedef Node<V, HashIterator> CacheElement;
  typedef typename CacheElement::pNode CacheElementPointer;

public:
  typedef V * DataIterator;
private:
  CacheElementPointer _head;
  CacheElementPointer _tail;

  std::unordered_map<K, int> _tags;
  std::unique_ptr<CacheElement[]> elements;

  int _capacity;
  int _size;
private:
  void setHeader(CacheElementPointer newHead) {
    newHead->next = _head;
    _head->prev = newHead;
    _head = newHead;
  }

public:
  LRUCache(int capacity): _head(nullptr), _tail(nullptr), _capacity(capacity), _size(0)  {
    // rehash
    _tags.rehash(capacity / _tags.max_load_factor());
    // reserve memory for nodes
    elements = std::unique_ptr<CacheElement[]>( new CacheElement[capacity] );
  }

  void push(K key, V value) {
    auto search = _tags.find(key);

    if (search != _tags.end()) {
      throw std::invalid_argument("This key already exists");
    }

    auto newElementPos = _size;
    if (_size == _capacity) {
        newElementPos = _tail->hashIter->second;
        _tags.erase(_tail->hashIter);
        _tail = _tail->prev;
        _size--;
    }

    // create tag
    auto pair = _tags.emplace(std::move(key), newElementPos);
    elements[newElementPos] = std::move(CacheElement(std::move(value)));

    auto cacheElementPointer = &elements[newElementPos];
    cacheElementPointer->hashIter = pair.first;

    if (_size == 0) {
      _tail = _head = cacheElementPointer;
    } else {
      this->setHeader(cacheElementPointer);
    }

    _size ++;
  }

  std::pair<DataIterator, bool> get(K key) {
    auto search = _tags.find(key);

    if (search == _tags.end()) {
      return std::make_pair(nullptr, false);
    }

    auto pointerGetElement = &elements[search->second];

    if (_head == pointerGetElement) {
      return std::make_pair(&(pointerGetElement->value), true);
    }

    if (_tail == pointerGetElement) {
      _tail = _tail->prev;
    }

    this->setHeader(pointerGetElement);

    return std::make_pair(&(_head->value), true);
  }

  void debug() {
    for (int i = 0; i < _size; i++) {
      elements[i].value.debug();
    }
  }
};
