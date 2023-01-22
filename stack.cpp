#include <iostream>
#include <stack>
#include <exception>
#include <string>

/**
 * @brief This file includes stack implemenation with some main methods
 * @warning The implementation of the stack is not thorough and meant for educational purposes
 *
 */

/**
 * @brief A custom exception class for when the stack is empty
 * it will throw an exception if stack is empty when push() and top()
 * methods are called on the instance of the class
 *
 */
class StackEmptyException : public std::exception
{
private:
    const char *_msg = "Stack is empty";

public:
    StackEmptyException() : std::exception() {}
    StackEmptyException(const char *message) : _msg(message) {}
    virtual const char *what() const noexcept
    {
        return _msg;
    }
};

/**
 * @brief A LIFO behavior data structure that allows the user to push item onto the stack
 * and pop off the item at the top of the stack
 *
 * @tparam T
 */
template <typename T>
class Stack
{
public:
    Stack();
    void push(T data);
    void pop();
    T &top();
    bool empty();

private:
    struct StackNode
    {
        T data;
        StackNode *top;
        StackNode(T data) : data(data), top(NULL){};
    };
    StackNode *_top;
};

/**
 * @brief Construct a new Stack< T>:: Stack object
 *
 * @tparam T
 */
template <typename T>
Stack<T>::Stack()
{
    _top = NULL;
}

/**
 * @brief Push an item onto the stack
 *
 * @tparam T
 * @param data
 */
template <typename T>
void Stack<T>::push(T data)
{
    StackNode *newNode = new StackNode(data);
    if (newNode == NULL)
        throw std::bad_alloc();
    newNode->top = _top;
    _top = newNode;
}

/**
 * @brief Returns true if the stack is empty
 *
 * @tparam T
 * @return true
 * @return false
 */
template <typename T>
bool Stack<T>::empty()
{
    return _top == NULL;
}

/**
 * @brief Pop the item at the top
 *
 * @tparam T
 */
template <typename T>
void Stack<T>::pop()
{
    if (empty())
    {
        throw StackEmptyException("Stack is empty");
    }

    StackNode *deleteNode = _top;
    _top = _top->top;
    delete deleteNode;
}

/**
 * @brief Returns the top item in the stack without removing it
 *
 * @tparam T
 * @return T
 */
template <typename T>
T &Stack<T>::top()
{
    if (empty())
    {
        throw StackEmptyException();
    }
    return _top->data;
}

int main()
{
    Stack<int> s;
    s.push(3);
    s.push(5);
    s.push(8);
    s.push(1);

    s.pop();
    s.pop();
    s.pop();
    s.pop();

    try
    {
        std::cout << s.top();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}