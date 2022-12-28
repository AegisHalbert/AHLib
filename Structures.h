#pragma once

#ifdef _DEBUG
#include <iostream>
#endif 

#include <memory>

namespace AHLib
{
	template<typename T,size_t S>
	class Array
	{
	private:
		T m_Data[S];

	public:
		constexpr size_t Size() const
		{
			return S;
		}

		T& operator[] (size_t index)
		{
			return m_Data[index];
		}
		const T& operator[] (size_t index) const
		{
			return m_Data[index];
		}

		T* Data() 
		{ 
			return m_Data;
		}
		const T* Data() const 
		{ 
			return m_Data;
		}
	};

	template<typename T> 
	class Darray
	{
	private:
		T* m_Data;
		size_t m_Capacity;
		size_t m_Count;

	public:
		Darray() : m_Capacity(0), m_Count(0)
		{
			m_Data = new T[0];
		}
		~Darray()
		{
			delete[] m_Data;
		}

		constexpr size_t Count() const
		{
			return m_Count;
		}

		void Add(T newObject)
		{
			if (m_Count == m_Capacity)
			{
				m_Capacity = IncreaseCapacity();

				T* newPointer = new T[m_Capacity];
				memcpy(newPointer, m_Data, sizeof(T) * m_Count);
				
				delete[] m_Data;
				m_Data = newPointer;
			}

			m_Data[m_Count] = newObject;
			m_Count++;
		}

		void Remove(T targetObject)
		{
#ifdef _DEBUG
			std::cout << "The lookup of the object to be removes uses a basic equality operator. This might remove objects with overlapping values instead of the target instance" << std::endl;
#endif
			bool removedEntry = false;
			for (int i = 0; i < m_Count; i++)
			{
				if (targetObject == m_Data[i])
				{
					// NOT SCIENTIFICALLY POSSIBLE
					delete m_Data[i];
					removedEntry = true;
				}
			}
		}

		T& operator[] (size_t index)
		{
			return m_Data[index];
		}
		const T& operator[] (size_t index) const
		{
			return m_Data[index];
		}

		T* Data()
		{
			return m_Data;
		}
		const T* Data() const
		{
			return m_Data;
		}

	private:
		size_t IncreaseCapacity()
		{
#ifdef _DEBUG
			std::cout << "Basic new capacity template on Darray. Resizing needs to be improved" << std::endl;
#endif

			return ++m_Capacity;
		}
	};
}