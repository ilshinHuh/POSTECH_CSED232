#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include <iostream>
#include <cassert>

template<typename ObjectType>
void Deallocator(ObjectType* ptr)
{
	std::cout << "Dealloc Object" << std::endl;
	delete ptr;
}

template<typename ObjectType>
void ArrayDeallocator(ObjectType* ptr)
{
	std::cout << "Dealloc Array" << std::endl;
	delete[] ptr;
}

template<typename T>
using DeallocatorFuncType = void (T*);

// SharedPtr
template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc = Deallocator<ObjectType> >
class SharedPtr
{
private:
	ObjectType* m_object;
	int* m_ref_counter;

	// ======= ADD CODE HERE IF NEEDED =========
				
public:
	////////////////////////////////////////////
	// Constructors & destructor
	////////////////////////////////////////////
	
	// ======= ADD CODE HERE IF NEEDED =========

	////////////////////////////////////////////
	// Assignment operator
	////////////////////////////////////////////
	
	// ======= ADD CODE HERE IF NEEDED =========
	
	////////////////////////////////////////////
	// Pointer operators
	////////////////////////////////////////////
	// operator->
	// operator*

	// ======= ADD CODE HERE IF NEEDED =========
	
	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]
	
	// ======= ADD CODE HERE IF NEEDED =========

	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]
	
	////////////////////////////////////////////
	// Type casting operators
	////////////////////////////////////////////
	// operator ObjectType const*() const
	// operator ObjectType*()
	
	// ======= ADD CODE HERE IF NEEDED =========
};

template<typename T>
using SharedArray = SharedPtr<T, ArrayDeallocator<T> >;

#endif
