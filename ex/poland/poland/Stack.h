#pragma once


using namespace std;

template<typename T>
class List
{
public:
	List();
	~List();

	T get_front();
	void push_front(T data);
	/*void push_back(T date);*/
	int getSize() { return this->size; }
	void pop_front();
	void clear();
	void insert(T value, int index);
	void removeAt(int index);
	void pop_back();
	T top();
	T& operator[](const size_t index);

private:
	template<typename T>
	class Node
	{
	public:

		Node* pNext;
		T data;
		Node(T data = T(), Node* pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;

		}
	};

	Node<T>* head;
	int size;


};
template<typename T>
List<T>::List()
{
	this->size = 0;
	head = nullptr;

}
template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
inline T List<T>::get_front()
{
	Node<T>* temp = head;

	head = head->pNext;
	this->size--;

	auto data = temp->data;
	delete temp;
	return data;

	
}

template<typename T>
void List<T>::push_front(T data)
{

	head = new Node<T>(data, head);
	this->size++;
}

//template<typename T>
//void List<T>::push_back(T data)
//{
//	if (head == nullptr)
//	{
//		head = new Node<T>(data);
//	}
//	else
//	{
//		Node <T>* current = this->head;
//		while (current->pNext != nullptr)
//		{
//			current = current->pNext;
//		}
//		current->pNext = new Node<T>(data);
//	}
//	this->size++;
//}

template<typename T>
void List<T>::pop_front()
{
	Node<T>* temp = head;
	head = head->pNext;

	delete temp;

	this->size--;
}

template<typename T>
void List<T>::clear()
{
	while (this->size)
	{
		pop_front();
	}
}

template<typename T>
void List<T>::insert(T data, int index)
{
	if (index == 0)
	{
		push_front(data);
	}
	else
	{
		Node<T>* previous = this->head;

		for (size_t i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		previous->pNext = new Node<T>(data, previous->pNext);

		this->size++;
	}



}

template<typename T>
void List<T>::removeAt(int index)
{

	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* previous = this->head;

		for (size_t i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* current = previous->pNext;

		previous->pNext = current->pNext;

		delete current;

		this->size--;
	}

}

//template<typename T>
//void List<T>::pop_back()
//{
//	removeAt(this->size - 1);
//}

template<typename T>
inline T List<T>::top()
{
	if (head)
	return head->data;
	return NULL;
}

//template<typename T>
//T& List<T>::operator[](const size_t index)
//{
//	int counter = 0;
//	Node <T>* current = this->head;
//
//	while (current != nullptr)
//	{
//		if (counter == index)
//		{
//			return current->data;
//
//		}
//		current = current->pNext;
//		counter++;
//	}
//
//
//}
//

