#include "UniquePtr.h"

#include <cassert>
#include <utility>
#include <iostream>

int main() {
    // Test empty constructor
    UniquePtr<int> empty;
    assert(!empty);
    assert(empty.get() == nullptr);

    // Test constructor with pointer
    UniquePtr<int> p(new int(5));
    assert(p);
    // Test dereference operator
    assert(*(p.operator->()) == 5);
    // Test get
    assert(*(p.get()) == 5);
    // Test if the addresses are the same
    assert(p.operator->() == p.get());

    // Test equality operator
    UniquePtr<int> empty2;
    assert(empty == empty2);
    assert(!(p == empty));

    // Test move constructor
    UniquePtr<int> moved(std::move(p));
    assert(*moved == 5);
    assert(!p);

    // Test move assignment operator
    UniquePtr<int> assigned(new int(10));
    assigned = std::move(moved);
    assert(*assigned == 5);

    // Test move constructor for different types
    UniquePtr<int> n(new int(7));
    UniquePtr<const int> cn(std::move(n));
    assert(*cn == 7);

    // Test release
    int* raw = assigned.release();
    assert(*raw == 5);
    delete raw;

    // Test reset
    UniquePtr<int> r(new int(1));
    r.reset(new int(2));
    assert(*r == 2);
    r.reset();
    assert(!r);

    // Test swap
    UniquePtr<int> a(new int(1));
    UniquePtr<int> b(new int(2));
    a.swap(b);
    assert(*a == 2);
    assert(*b == 1);

    // Test makeUnique
    auto m = makeUnique<int>(42);
    assert(*m == 42);

    std::cout << "All tests passed" << std::endl;
    return 0;
}
