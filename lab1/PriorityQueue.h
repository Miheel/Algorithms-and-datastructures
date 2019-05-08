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
	size_t nrOfElem;
	size_t cap;
	T *elem;
	void siftDown(size_t index);
	void percUp(size_t size);
	void freemen();
	void expand();

	class exEmpty : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "Empty queue";
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
	++this->nrOfElem;
	if (this->size() == this->cap)
	{
		this->expand();
	}
	this->elem[this->size()] = element;
	this->percUp(this->size());
}

template<typename T>
inline void PriorityQueue<T>::dequeue()
{
	if (this->isEmpty() == true)
	{
		throw this->empty;
	}
	this->elem[1] = this->elem[this->size()];
	this->nrOfElem--;
	this->siftDown(1);
}

template<typename T>
inline T PriorityQueue<T>::peek() const
{
	if (this->isEmpty() == true)
	{
		throw this->empty;
	}
	else
	{
		return this->elem[1];
	}
}

template<typename T>
inline size_t PriorityQueue<T>::size() const
{
	return this->nrOfElem;
}

template<typename T>
inline bool PriorityQueue<T>::isEmpty() const
{
	bool check = false;
	if (this->size() == 0)
	{
		check = true;
	}
	return check;
}

template<typename T>
inline void PriorityQueue<T>::siftDown(size_t index)
{
	while (index * 2 <= this->size())
	{
		size_t	child = index * 2;
		if (child <= this->size() && this->elem[child + 1] < this->elem[child])
		{
			child++;
		}

		if (this->elem[child] < this->elem[index])
		{
			T temp = this->elem[index];
			this->elem[index] = this->elem[child];
			this->elem[child] = temp;
		}
		index = child;
	}
}

template<typename T>
inline void PriorityQueue<T>::percUp(size_t size)
{
	for (size = this->size(); size / 2 > 0; size = size / 2)
	{
		if (this->elem[size] < this->elem[size / 2])
		{
			T temp = this->elem[size];
			this->elem[size] = this->elem[size / 2];
			this->elem[size / 2] = temp;
		}
	}
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

	for (size_t i = 0; i < this->size(); i++)
	{
		temp[i] = this->elem[i];
	}
	this->freemen();
	this->elem = temp;
}
#endif // !PRIORITYQUEUE_H
