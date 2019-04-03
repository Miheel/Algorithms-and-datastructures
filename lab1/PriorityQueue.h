#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <exception>

template<typename T>
class PriorityQueue
{
public:
	PriorityQueue();
	~PriorityQueue();
	void enqueue(T element);
	void dequeue();
	T peek() const;
	size_t size() const;
	bool isEmpty() const;

private:
	int nrOfElem;
	int cap;
	T *elem;
	void freemen();
	void expand();

	class exEmpty : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "Empty arr";
		}
	}empty;
};

template<typename T>
inline PriorityQueue<T>::PriorityQueue()
{
	this->cap = 1;
	this->nrOfElem = 0;
	this->elem = new T[this->cap];
}

template<typename T>
inline PriorityQueue<T>::~PriorityQueue()
{
	this->freemen();
}

template<typename T>
inline void PriorityQueue<T>::enqueue(T element)
{
	if (this->nrOfElem == this->cap)
	{
		this->expand();
	}

	this->elem[this->nrOfElem++] = element;
	for (int i = 0; i < this->size(); i++)
	{
		int temp = this->elem[i];
		int j = i - 1;
		for (; j >= 0 && temp < this->elem[j]; j--)
		{
			this->elem[j + 1] = this->elem[j];
		}
		this->elem[j + 1] = temp;
	}
	//perkulera up
}

template<typename T>
inline void PriorityQueue<T>::dequeue()
{
	if (this->isEmpty() == true)
	{
		throw this->empty;
	}

	for (int i = 0; i < this->size(); i++)
	{
		this->elem[i] = this->elem[i + 1];
	}
	this->nrOfElem--;
	//perkulera ner
}

template<typename T>
inline T PriorityQueue<T>::peek() const
{
	if (this->isEmpty() == true)
	{
		throw this->empty;
	}
	return this->elem[0];
}

template<typename T>
inline size_t PriorityQueue<T>::size() const
{
	return this->nrOfElem;
}

template<typename T>
inline bool PriorityQueue<T>::isEmpty() const
{
	bool check = true;
	if (this->nrOfElem != 0)
	{
		check = false;
	}
	return check;
}

template<typename T>
inline void PriorityQueue<T>::freemen()
{
	delete[] this->elem;
}

template<typename T>
inline void PriorityQueue<T>::expand()
{
	this->cap = this->cap * 2;
	T *temp = new T[this->cap];

	for (int i = 0; i < this->nrOfElem; i++)
	{
		temp[i] = this->elem[i];
	}
	this->freemen();
	this->elem = temp;
}

#endif // !PRIORITYQUEUE_H