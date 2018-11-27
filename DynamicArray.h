#pragma once
#include <iostream>
using namespace std;


template <typename T>
class DynamicArray
{
private:
    T *data; //a pointer to the data we are storing
    unsigned int currSize = 0; //number of objects being stored currently.
    unsigned int maxCapacity = 0; //The number of objects that COULD be stored. This is not the same as the size.

public:
    /*=====Accessors=====*/
    unsigned int GetCapacity() const;
    unsigned int GetSize() const;
    const T* GetData() const;

    //Returns a specific element from the internal array
    const T &operator[](unsigned int index) const;
    T &operator[](unsigned int index);

    //Just like the bracket operator but with a function
    const T &At(unsigned int index) const;
    T &At(unsigned int index);

    /*=====Mutators=====*/
    //Adds an item onto the end of the array if there is room.
    // If there is no room, the array is re-sized to make room for it
    void Add(const T &dataElement);
    //This is the function that will be doing any resizing of the array
    void Resize(unsigned int newSize);
    //This is the function that removes elements from the array, and then shrinks the array to fill the new gap
    void Remove(unsigned int index);

    /*=====Constructors=====*/
    DynamicArray();
    DynamicArray(unsigned int);

    /*=====Trilogy of Evil=====*/
    DynamicArray(const DynamicArray &origArray);
    DynamicArray &operator=(const DynamicArray &origArray);
    ~DynamicArray();

}; //End DynamicArray Class

template <typename T> //RETURNS ARRAY'S CAPACITY
unsigned int DynamicArray<T>::GetCapacity() const
{
    return maxCapacity;
}

template <typename T> //RETURNS ARRAY'S CURRENT SIZE
unsigned int DynamicArray<T>::GetSize() const
{
    return currSize;
}

template <typename T> //RETURNS A POINTER TO THE ARRAY
const T* DynamicArray<T>::GetData() const
{
    return  data;
}

template <typename T> //OPERATOR OfVERLOAD FOR BRACES
const T& DynamicArray<T>::operator[](unsigned int index) const
{
    if (index < currSize)
        return data[index];
    else
        throw ("Error: Invalid index");
}

template <typename T> //OPERATOR OVERLOAD FOR BRACES
T& DynamicArray<T>::operator[](unsigned int index)
{
    if(index < currSize)
        return data[index];
    else
        throw ("Error: Invalid index");
}

template <typename T> //PERFORMS FUNCTION SIMILAR TO VECTOR.AT
const T& DynamicArray<T>::At(unsigned int index) const
{
    if (index < currSize)
        return data[index];
    else
        throw ("Error! Invalid index");
}


template <typename T> //PERFORMS FUNCTION SIMILAR TO VECTOR.AT
T& DynamicArray<T>::At(unsigned int index)
{
    if(index < currSize)
        return data[index];
    else
        throw ("Error! Invalid index");

}


template <typename T> //ADDS ELEMENTS TO THE ARRAY
void DynamicArray<T>::Add(const T &dataElement)
{

    //if you have room add to current array
    if(currSize == maxCapacity)
    {
        Resize(maxCapacity + 1);
    }

    data[currSize] = dataElement;
    currSize++;

}


template <typename T> //RE-SIZES ARRAY
void DynamicArray<T>::Resize(unsigned int newSize)
{

    cout << "Resizing... old capacity: " << maxCapacity << " New capacity: " << newSize << endl;

    T *newArray = new T[newSize]; //Declare a new array to resize the old one
    maxCapacity = newSize;

    if(newSize < currSize)
    {
        currSize = newSize;
    }

    //used to copy already present data in the old array
    for (unsigned int i = 0; i < currSize; i++)
    {
        newArray[i] = data[i];
    }

    //need to delete the old array correctly here
    if(data != nullptr)
    {
        delete[] data;
    }

    data = newArray;

}

template <typename T> //REMOVES ELEMENTS FROM ARRAY
void DynamicArray<T>::Remove(unsigned int index)
{
    if(currSize == 0)
    {
        throw ("Error! Invalid index");
    }

    if(index < 0 || index > maxCapacity)
    {
        throw ("Error! Invalid index");
    }



    //start the for loop from where you delete
    for (unsigned int i = index; i < currSize - 1; i++)
    {
        data[i] = data[i + 1];
    }

    currSize--;
}

template <typename T> //DEFAULT CONSTRUCTOR
DynamicArray<T>::DynamicArray()
{
    currSize = 0;
    maxCapacity = 0;
    data = nullptr;
}


template <typename T> //NORMAL CONSTRUCTOR
DynamicArray<T>::DynamicArray(unsigned int maxCapacity)
{
    this->maxCapacity = maxCapacity;
    currSize = 0;
    data = new T[maxCapacity];

}

template <typename T> //COPY CONSTRUCTOR
DynamicArray<T>::DynamicArray(const DynamicArray &origArray)
{
    if(data != nullptr)
    {
        //delete[] data;
    }

    currSize = origArray.currSize;
    maxCapacity = origArray.maxCapacity;

    data = new T[maxCapacity];

    for (unsigned int i = 0; i < currSize; i++)
    {
        data[i] = origArray.data[i];
    }
}

template <typename T> //OPERATOR OVERLOAD FOR =
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray &origArray)
{
    if(data != nullptr)
    {
        //delete[] data;
    }

    currSize = origArray.currSize;
    maxCapacity = origArray.maxCapacity;

    data = new T[maxCapacity];

    for (unsigned int i = 0; i < currSize; i++)
    {
        data[i] = origArray.data[i];
    }

    return *this;
}

template <typename T> //DESTRUCTOR
DynamicArray<T>::~DynamicArray()
{
    if (data != nullptr)
    {
        delete[] data;
        data = nullptr;
    }

}
