#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <iterator>
#include <memory>

//#undef new
//
//#include "MemoryLeakChecker.hpp"

/********************************linearSearch********************************/

template<typename ForwIt>
class LinearSearch
{
public:

	LinearSearch(ForwIt first, ForwIt last) :
		first(first), last(last) {}

	ForwIt search(int value)
	{
		for (auto It = this->first; It != this->last; It++)
		{
			if (*It == value)
			{
				return It;
			}
		}
		return this->last;
	}

private:
	ForwIt first;
	ForwIt last;
};





/********************************binarySearch********************************/


template<typename RandomIt>
class BinarySearch
{
public:

	BinarySearch(RandomIt first, RandomIt last) :
		first(first), last(last) {}

	RandomIt search(int value)
	{
		auto low = this->first, high = this->last;
		while (low <= high)
		{
			auto mid = low + std::distance(low, high) / 2;

			if (value > *mid)
			{
				low = mid + 1;
			}
			else if (value < *mid)
			{
				high = mid - 1;
			}
			else
			{
				return mid;
			}
		}
		return this->last;
	}

private:
	RandomIt first;
	RandomIt last;
};




/********************************binaryTreeSearch********************************/

template<typename T>
class BTS
{
private:
	struct Node {

		Node(const T& data) :
			data(data), left(nullptr), right(nullptr) {}

		T data;
		Node* left;
		Node* right;
	};
	Node* root;

	template<typename RandomIt>
	void makeBST(RandomIt first, RandomIt last, Node*& node)
	{
		if (first >= last)
			return;

		auto mid = first + (std::distance(first, last) / 2);

		node = new Node(*mid);

		this->makeBST(first, mid, node->left);
		this->makeBST(mid + 1, last, node->right);
	}

	void destroyBST(Node*& node) {
		if (node != nullptr)
		{
			this->destroyBST(node->left);
			this->destroyBST(node->right);
			delete node;
		}
	}

public:
	template<typename RandomIt>
	BTS(RandomIt first, RandomIt last) {
		this->makeBST(first, last, this->root);
	}
	~BTS() {
		this->destroyBST(this->root);
	}

	Node* search(T value)
	{
		auto curr = this->root;
		while (curr != nullptr && (curr->right != nullptr && curr->left != nullptr))
		{
			if (curr->data == value)
			{
				return curr;
			}
			if (value > curr->data && curr->right != nullptr)
			{
				curr = curr->right;
			}
			if (value < curr->data && curr->left != nullptr)
			{
				curr = curr->left;
			}
		}
		return 0;
	}

	Node* getTree() {
		return this->root;
	}

	void print(Node*& node, int & id)
	{
		if (node == nullptr) return;

		this->print(node->left, id);

		id++;
		std::cout << id << ' ' << node->data << std::endl;

		this->print(node->right, id);
	}

};





/********************************hashTabelSearch********************************/

class Hashtabel
{
private:
	struct Node
	{
		Node(int data) :
			data(data) {}
		//~Node() 
		//{
		//		delete this->next;
		//}

		int data;
		std::unique_ptr<Node> next = nullptr;
	};

	std::vector<std::unique_ptr<Node>> hashTable;

	template<typename T>
	int hashFunk(T key)
	{
		return key % this->hashTable.size();
	}

public:
	template<typename RandomIt>
	Hashtabel(RandomIt first, RandomIt last, size_t size)
	{
		auto newSize = std::floor(size / 0.5);
		this->hashTable.resize(int(newSize));
		for (auto it = first; it != last; it++)
		{
			this->insert(*it);
		}
	}
	Hashtabel(const Hashtabel&) = delete;

	//~Hashtabel() 
	//{
		//for (auto &e : this->hashTable)
		//{
		//	delete e;
		//}
	//}

	template<typename T>
	Node* search(T key)
	{
		int index = this->hashFunk(key);

		auto node = this->hashTable.at(index).get();
		
		while (node != nullptr)
		{			
			if (node->data == key)
			{
				return node;
			}
			node = node->next.get();
		}

		return nullptr;
	}


	template<typename T>
	void insert(T key)
	{
		auto newNode = std::make_unique<Node>(key);

		int index = this->hashFunk(key);

		if (this->hashTable[index] == nullptr)
		{
			this->hashTable[index] = std::move(newNode);
		}
		else
		{
			auto curr = this->hashTable[index].get();
			while (curr->next != nullptr)
			{
				curr = curr->next.get();
			}
			curr->next = std::move(newNode);
		}

	}

	Node* deleteItem() {}


	void print() 
	{
		//for (auto &node : this->hashTable)
		//{
		//	if (node == nullptr)
		//	{
		//		std::cout << "null\n";
		//	}
		//	else if (node->next == nullptr)
		//	{
		//		std::cout << node->data << "-> null\n";
		//	}
		//	else {

		//		while (node->next != nullptr)
		//		{
		//			std::cout << node->data << " -> ";
		//			node = node->next;
		//		}
		//		std::cout << node->data << "-> null\n";
		//	}
		//}
	}
};


#endif // !SEARCH_HPP
