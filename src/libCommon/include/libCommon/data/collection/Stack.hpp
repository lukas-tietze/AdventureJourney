#pragma once

#include <algorithm>

namespace util
{
template <class TData, class TAllocator = std::allocator<TData>>
class Stack final
{
private:
    TData *bottom;
    u_int32_t count;
    u_int32_t capacity;

    void Realloc();

public:
    Stack(const Stack<TData> &);
    Stack(Stack<TData> &&);
    Stack(const std::initializer_list<TData> &);

    void Push(const TData &);
    void Push(TData &&);
    TData &Pop();
    TData &Peek();
    const TData &Peek() const;
    u_int32_t Size() const;
};
} // namespace util