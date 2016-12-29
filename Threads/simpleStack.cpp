#include <strings.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>

#define N 10000
class Node
{
public:
  Node* next;
  int item;
};

class SimpleStack
{
public:
  SimpleStack()
  {
    head = new Node(); 
  }

  ~SimpleStack()
  {
    if(head) delete head;
  }

  void push(int item)
  {
    Node* node = new Node();
    node->item = item;
    do {
      node->next = head->next;
      //      head->next = node;//critical if multi threaded
    } while(!__sync_bool_compare_and_swap (&head->next, node->next, node));
    //std::cout << "push " << item << " in stack" << std::endl;
  }

  int pop()
  {
    Node *node = NULL;
    do {
      node = head->next;
      if(node == NULL)
        return 0; //nothing to return, default value of int
    } while(!__sync_bool_compare_and_swap (&head->next, node, node->next));
    //    head->next = node->next;
    return node->item;
  }
private:
  Node* head;
};

class PusherEngine
{
public:
  PusherEngine(SimpleStack* instack){stack = instack;}
  ~PusherEngine(){}//do not delete stack, not mine
  static void* execute(void *arg)
  {
    if(stack == NULL) return NULL;

    for(int i=1; i<=N; i++)
    {
      stack->push(i);
    }
    return NULL;
  }
private:
  static SimpleStack* stack;//ugly!!!
};

class PopperEngine
{
public:
  PopperEngine(SimpleStack* instack, pthread_t* inthreadpush)
  { 
    stack      = instack;
    threadpush = inthreadpush; 
  }

  ~PopperEngine(){}//do not delete stack, not mine

  static void* execute(void* arg)
  {
    if(stack == NULL)
    {
      std::cout << "no stack! error! exit " << std::endl;
      exit(1);
    }
    if(threadpush == NULL)
    {
      std::cout << "no thread push! error! exit " << std::endl;
      exit(1);
    }

    bool* poppedValues = new bool[N+1];
    bzero(poppedValues, sizeof(bool)*N);//init all to false

    int poppedInt = 0;

    do {
      poppedInt = stack->pop();
      //std::cout << "1 - " << poppedInt << " popped " << std::endl;
      if(poppedInt != 0)
      {
        if(poppedValues[poppedInt])
          std::cout << poppedInt << " has been popped before!" << std::endl;
        poppedValues[poppedInt] = true;
      }
    } while(poppedInt != N);

    void*retval;
    int ret = 0;
    if((ret = pthread_join(*threadpush, &retval)))
    {
      std::cout << "error during synchonization with thread push. exit. [ " << ret << " ]"<< std::endl;
      exit(1);
    }
    std::cout << "thread push has finished" << std::endl;

    poppedInt = stack->pop();
    while(poppedInt != 0)
    {
      if(poppedValues[poppedInt])
        std::cout << poppedInt << " has been popped before!" << std::endl;
      poppedValues[poppedInt] = true;
      poppedInt = stack->pop();
      //std::cout << "2 - " << poppedInt << " popped " << std::endl;
    }      
    std::cout << "check output" << std::endl;

    for(int i=1; i<=N; i++)
    {
      if(!poppedValues[i])
        std::cout << i << " is missing!" << std::endl;
    }

    delete[] poppedValues;
    return NULL;
  }

private:
  static SimpleStack* stack;
  static pthread_t*   threadpush; 
};

SimpleStack* PusherEngine::stack      = NULL;

SimpleStack* PopperEngine::stack      = NULL;
pthread_t*   PopperEngine::threadpush = NULL;

int main()
{
  std::cout << "create the shared stack" << std::endl;
  SimpleStack*  stack         = new SimpleStack();

 
  pthread_t threadpush;
  pthread_t threadpop;

  PusherEngine* pusherEngine  = new PusherEngine(stack);
  PopperEngine*  popperEngine = new PopperEngine(stack, &threadpush);

  std::cout << "create pusher thread" << std::endl;
  if(pthread_create(&threadpush, NULL, pusherEngine->execute, NULL))
  {
    std::cout << "cannot create thread to push. exit" << std::endl;
    exit(1);
  }

  std::cout << "create popper thread" << std::endl;
  if(pthread_create(&threadpop, NULL, popperEngine->execute, NULL))
  {
    std::cout << "cannot create thread to pop. exit" << std::endl;
    exit(1);
  }

  void* retval;
  if(pthread_join(threadpop, &retval))
  {
    std::cout << "cannot synchronyse thread correctly. exit" << std::endl;
    exit(1);
  }

  delete pusherEngine;  
  delete popperEngine;  
  delete stack;

  std::cout << "Done." << std::endl;
  return 0;
}
