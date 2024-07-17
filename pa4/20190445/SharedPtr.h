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
	//function that releases memory
	void reset(){
		if(m_ref_counter != nullptr){//when counter is not zero
			(*m_ref_counter)--;
			if((*m_ref_counter) == 0){//when counter becomes zero
				Dealloc(m_object);
				delete m_ref_counter;
			}
		}
	}
				
public:
	////////////////////////////////////////////
	// Constructors & destructor
	////////////////////////////////////////////
	//explicit constructor with default argument.
	explicit SharedPtr(ObjectType* ptr = nullptr) : m_object(ptr), m_ref_counter(nullptr){
		if (ptr != nullptr)//if argument is not default
			m_ref_counter = new int(1);
	}
	
	//copy constructor for SharedPtr
	SharedPtr(const SharedPtr<ObjectType>& other) : m_object(other.m_object), m_ref_counter(other.m_ref_counter){
		if(m_ref_counter != nullptr){
			(*m_ref_counter)++;//count up when counter was not zero.
		}
	}

	//copy constructor for SharedArray
	SharedPtr(const SharedPtr<ObjectType, ArrayDeallocator<ObjectType>>& other) : m_object(other.m_object), m_ref_counter(other.m_ref_counter){
		if(m_ref_counter != nullptr){
			(*m_ref_counter)++;
		}
	}

	//deconstructor
	~SharedPtr(){reset();}//calls memory release function.
	// ======= ADD CODE HERE IF NEEDED =========

	////////////////////////////////////////////
	// Assignment operator
	////////////////////////////////////////////
	//assignment operator for SharedPtr.
	SharedPtr<ObjectType>& operator=(const SharedPtr<ObjectType>& other){
		if(this != &other){//when the two operands are different
			reset();//call memory realease function
			m_object = other.m_object;
			m_ref_counter = other.m_ref_counter;
			if(m_ref_counter != nullptr)
				(*m_ref_counter)++;
		}
		return *this;
	}

	//assignment operator for SharedArray
	SharedPtr<ObjectType, ArrayDeallocator<ObjectType>>& operator=(const SharedPtr<ObjectType, ArrayDeallocator<ObjectType>>& other){
		if(this != &other){
			reset();
			m_object = other.m_object;
			m_ref_counter = other.m_ref_counter;
			if(m_ref_counter != nullptr)
				(*m_ref_counter)++;
		}
		return *this;
	}

	// ======= ADD CODE HERE IF NEEDED =========
	
	////////////////////////////////////////////
	// Pointer operators
	////////////////////////////////////////////
	// operator->
	ObjectType* operator->(){
		return m_object;//return data
	}
	//operator-> for const object
	const ObjectType* operator->() const{
		return m_object;
	}

	// operator*
	ObjectType& operator*(){
		return *m_object;//return pointer for data
	}
	//operator-> for const object
	const ObjectType& operator*() const{
		return *m_object;
	}


	// ======= ADD CODE HERE IF NEEDED =========
	
	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	//bracket operator for SharedArray
	ObjectType& operator[](int index){
		return m_object[index];
	}
	// ======= ADD CODE HERE IF NEEDED =========

	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	//bracket operator for const SharedArray
	const ObjectType& operator[](int index) const{
		return m_object[index];
	}
	
	////////////////////////////////////////////
	// Type casting operators
	////////////////////////////////////////////
	//Typecasting operator for const object
	operator ObjectType const*() const{
		return m_object;
	}
	//typecasting operator
	operator ObjectType*(){
		return m_object;
	}
	
	// ======= ADD CODE HERE IF NEEDED =========
};

template<typename T>
using SharedArray = SharedPtr<T, ArrayDeallocator<T> >;

#endif
