//
// Created by Eden_ on 24-9-5.
//


#include <DataStructure/data_structure.h>

template <typename T>
LinkedList<T>::LinkedList(){
    head_node->next = tail_node;
    tail_node->previous = tail_node;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other)
{
    LinkedList();

    Node<T> * temp = other.head_node;
    while (temp->next!=other.tail_node)
    {
        temp=temp->next;
        add(temp->data);
    }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept {
    head_node = other.head_node;
    other.head_node = nullptr;
    tail_node = other.tail_node;
    other.tail_node = nullptr;
    size = other.size;
    other.size = 0;
}

template <typename T>
LinkedList<T>::LinkedList(T* other, size_t size)
{
    LinkedList();
    for (size_t i = 0; i < size; i++)
    {
        add(other[i]);
    }
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
    head_node = nullptr;
    tail_node = nullptr;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList &other)
{
    if (this != &other)
    {
        clear();
        Node<T> * temp = other.head_node;
        while (temp->next!=other.tail_node)
        {
            temp=temp->next;
            add(temp->data);
        }
    }

    return *this;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList &&other) noexcept
{
    if (this != &other)
    {
        clear();
        head_node = other.head_node;
        other.head_node = nullptr;
        tail_node = other.tail_node;
        other.tail_node = nullptr;
        size = other.size;
        other.size = 0;
    }

    return *this;
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList &other)
{
    if (this->size != other.size)
    {
        return false;
    }

    Node<T> * self_temp = head_node->next;
    Node<T> * other_temp = other.head_node->next;
    while (self_temp!=tail_node)
    {
        if (self_temp->data != other_temp->data)
        {
            return false;
        }
    }
    return true;
}

template <typename T>
void LinkedList<T>::add(T value)
{
    tail_node->previous->next = new Node<T>(value, tail_node,tail_node->last);
    tail_node->previous = tail_node->previous->next;
}

template <typename T>
void LinkedList<T>::add(int index, T value)
{
}

template <typename T>
T &LinkedList<T>::get(int index) const
{
}

template <typename T>
void LinkedList<T>::set(int index, T value)
{
}

template <typename T>
void LinkedList<T>::remove(int index)
{
}

template <typename T>
void LinkedList<T>::remove(T value)
{
}

template <typename T>
bool LinkedList<T>::contains(T value)
{
}

template <typename T>
size_t LinkedList<T>::get_size() const
{
}

template <typename T>
bool LinkedList<T>::is_empty() const
{
}

template <typename T>
void LinkedList<T>::add_first(T value)
{
}

template <typename T>
void LinkedList<T>::add_last(T value)
{
}

template <typename T>
void LinkedList<T>::remove_first()
{
}

template <typename T>
void LinkedList<T>::remove_last()
{
}

template <typename T>
T &LinkedList<T>::peek_first() const
{
}

template <typename T>
T &LinkedList<T>::peek_last() const
{
}

template <typename T>
T LinkedList<T>::pop_first()
{
}

template <typename T>
T LinkedList<T>::pop_last()
{
}

template <typename T>
void LinkedList<T>::clear()
{
}

template <typename T>
typename LinkedList<T>::template Node<T> * LinkedList<T>::get_node_pointer(size_t index)
{
    if(index > size)
    {
        std::cerr << "Index out of range! " << __FILE__ << " at line " << __LINE__ << std::endl;
        return nullptr;
    }//In this situation, index equals to size is valid

    Node<T> * temp = nullptr;
    if(index<size/2)
    {
        temp = head_node->next;
        for(size_t i = 0; i < index; i++)
        {
            temp = temp->next;
        }
    }
    else {
        temp = tail_node;
        for(size_t i = size;i > index; i--)
        {
            temp = temp->previous;
        }
    }
    return temp;
}
