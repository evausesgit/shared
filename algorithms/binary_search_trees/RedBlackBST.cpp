#include <iostream>
#include <sstream>
#include <assert.h>
static bool RED   = true;
static bool BLACK = false;

template<class K, class V>
class Node
{
public:
  Node(K key, V value): key(key), value(value), left(NULL), right(NULL), color(RED) {}

  virtual ~Node()
  {
    delete left;
    delete right;
  }

  std::string print()
  {
    std::stringstream oss;

    oss << key <<"." << (color ? "R" : "" )<< " ";// << value << " ";
    if(left)
      oss << left->print();
    else
      oss << "null(" << key << ") ";
    if(right)
      oss << right->print();
    else
      oss << "null(" << key << ") ";

    return oss.str();
  }
  K key;
  V value;
  Node* left;
  Node* right;

  bool color;
};


template<class K, class V>
class RBBST
{
public:
  RBBST(): root_(NULL) {}
  virtual ~RBBST()
  {
    delete root_;
  }

  bool isRed(Node<K, V>* node)
  {
    if(!node)
      return BLACK;
    return node->color == RED;
  }

  void put(K key, V value)
  {
    root_ =  put(root_, key, value);
  }

  V get(K key)
  {

  }

  void deleteKey(K key)
  {
  }

  void print()
  {
    std::cout << root_->print() << std::endl;
  }

  Node<K, V>* rotateLeft(Node<K, V>* h)
  {
    assert(isRed(h->right));

    Node<K, V>* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    return x;
  }

  Node<K, V>* rotateRight(Node<K, V>* h)
  {
    assert(isRed(h->left));

    Node<K, V>* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
  }

  void flipColor(Node<K, V>* h)
  {
    //assert(!isRed(h));
    assert(isRed(h->right));
    assert(isRed(h->left));

    h->color = RED;
    h->left->color = BLACK;
    h->right->color = BLACK;
  }

private:
  
  Node<K, V>* put(Node<K, V>* x, K key, V value)
  {
    if(x == NULL) return new Node<K, V>(key, value);

    int cmp = key - x->key;
    if (cmp < 0)
      x->left = put(x->left, key, value);
    else if (cmp > 0)
      x->right = put(x->right, key, value);
    else
      x->value = value;

    if(isRed(x->right) && !isRed(x->left))          x = rotateLeft(x);
    if(isRed(x->left)  &&  isRed(x->left->left))    x = rotateRight(x);
    if(isRed(x->left)  &&  isRed(x->right))         flipColor(x);

    return x;
  }
private:

  Node<K, V>* root_;

};

int main()
{
  const int N = 13;
  int a[N] = {68,38,92,26,55,82,96,13,27,71, 12, 63, 80};

  RBBST<int, int> bst;

  for(int x : a)
  {
    bst.put(x, 0);
    bst.print();
  }
  
  return 0;
}
