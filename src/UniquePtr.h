#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <cassert>
#include <utility>

template <typename T>
class UniquePtr;

template <typename T>
class UniquePtr {
public:
    // Constructors
    UniquePtr() : mPtr(nullptr) {}
    UniquePtr(T* ptr) : mPtr(ptr) {}

    // Destructor
    ~UniquePtr() { 
        delete mPtr;
    }

    // Prevents copying
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Move constructor
    // Moves ownership of the pointer from other to this
    UniquePtr(UniquePtr&& other) : mPtr(other.mPtr) {
        other.mPtr = nullptr;
    }

    // Move assignment operator
    // Moves ownership of the pointer from other to this
    UniquePtr& operator=(UniquePtr&& other) {
        if (this != &other) {
            std::swap(mPtr, other.mPtr);
        }
        return *this;
    }

    // Move constructor for different types
    // other.release() returns a pointer to the object
    template <typename U>
    UniquePtr(UniquePtr<U>&& other) : mPtr(other.release()) {}

    // Dereference operator
    // Returns a reference to the object
    T& operator*() const {
        assert(mPtr != nullptr);
        return *mPtr;
    }

    // Arrow operator
    // Returns a pointer to the object
    T* operator->() const {
        return mPtr;
    }
    T* get() const { return mPtr; }

    bool operator==(const UniquePtr& other) const { return mPtr == other.mPtr; }

    T* release() {
        T* tempPtr = mPtr;
        mPtr = nullptr;
        return tempPtr;
    }

    void reset(T* newPtr = nullptr) {
        T* oldPtr = mPtr;
        mPtr = newPtr;
        delete oldPtr;
    }

    void swap(UniquePtr& other) {
        std::swap(mPtr, other.mPtr);
    }

    operator bool() const { return mPtr != nullptr; }

private:
    T* mPtr;
};

template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif
