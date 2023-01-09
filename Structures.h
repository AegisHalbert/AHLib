#pragma once

#ifdef _DEBUG
#include <iostream>
#endif 

#include <memory>

#include <vector>

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
	public:
		using ValueType = T;
		using Iterator = Diterate<Darray<T>>;
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

		constexpr size_t ArrayIsFull() const
		{
			return m_Count == m_Capacity;
		}

		void Add(T newObject)
		{
			if (ArrayIsFull())
			{
				m_Capacity = RecalculateCapacity();
				PointerMigration();
			}

			m_Data[m_Count] = newObject;
			m_Count++;
		}

		bool Remove(T targetObject)
		{
#ifdef _DEBUG
			std::cout << "The lookup of the object to be removes uses a basic equality operator. This might remove objects with overlapping values instead of the target instance" << std::endl;
			std::cout << "Consider creating a version that allows special assertions" << std::endl;
#endif
			for (int i = 0; i < m_Count; i++)
			{
				if (targetObject == m_Data[i])
				{
					RemoveAt(i);
					return true;
				}
			}
			return false;
		}
		void RemoveAt(size_t index)
		{
			for (int i = index; i < m_Count - 1; i++)
			{
				m_Data[i] = m_Data[i + 1];
			}
			PostRemovalOps(1);
		}

		void Clear(bool freeAllMemory = false)
		{
			m_Count = 0;
			if (freeAllMemory)
			{
				m_Capacity = 0;
				PostRemovalOps(0, true);
				PointerMigration();
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

		/* Iterator begin()
		{
			return Diterate(m_Data);
		}
		Iterator end()
		{
			return Diterate(m_Data + m_Size);
		} */

	private:
		size_t RecalculateCapacity()
		{
#ifdef _DEBUG
			std::cout << "Basic new capacity template on Darray. Resizing needs to be improved" << std::endl;
#endif

			size_t oldCapacity = m_Capacity;
			size_t newCapacity = m_Capacity;

			if (ArrayIsFull())
			{
				newCapacity = m_Count + 1;
			}

			return newCapacity;
		}

		void PointerMigration()
		{
			T* newPointer = new T[m_Capacity];
			memcpy(newPointer, m_Data, sizeof(T) * m_Count);

			delete[] m_Data;
			m_Data = newPointer;
		}

		void PostRemovalOps(size_t removalCount, bool forceResize = false)
		{
#ifdef _DEBUG
			std::cout << "Branch into counting several removals to optimize resizing" << std::endl;
#endif

			m_Count -= removalCount;

			if (!forceResize) return;
			RecalculateCapacity();
		}
	};

	template <typename Darray>
	class Diterate
	{
	public:
		using ObjectType = typename Darray::ValueType;
	private:
		ObjectType* m_Pointer;
	public:
		Diterate(ObjectType pointer) : m_Pointer(pointer)
		{
			//
		}

		ObjectType& operator++()
		{
			m_Pointer++;
			return *m_Pointer;
		}
		ObjectType& operator--()
		{
			m_Pointer--;
			return *m_Pointer;
		}
		ObjectType operator++(int postFix)
		{
			Diterate iterator = *this;
			++(*this);
			return iterator;
		}
		ObjectType operator--(int postFix)
		{
			Diterate iterator = *this;
			--(*this);
			return iterator;
		}

		ObjectType& operator[](int index)
		{
			return *(m_Pointer + index);
		}

		ObjectType* operator->()
		{
			return m_Pointer;
		}
		ObjectType& operator*()
		{
			return *m_Pointer;
		}

		bool operator==(const Diterate& other) const
		{
			return m_Pointer == other.m_Pointer;
		}
		bool operator!=(const Diterate& other) const
		{
			return !(*this == other);
		}
	};
}