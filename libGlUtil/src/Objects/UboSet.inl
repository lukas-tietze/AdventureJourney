#include "Objects.hpp"

template <class TData, class TAccessor, class TConstAccessor>
TAccessor glutil::UboSet<TData, TAccessor, TConstAccessor>::Add()
{
    this->data.push_back(TData());

    return TAccessor(&this->data, this->data.size() - 1);
}

template <class TData, class TAccessor, class TConstAccessor>
void glutil::UboSet<TData, TAccessor, TConstAccessor>::Clear()
{
    this->data.clear();
}

template <class TData, class TAccessor, class TConstAccessor>
TAccessor glutil::UboSet<TData, TAccessor, TConstAccessor>::operator[](size_t index)
{
    return TAccessor(&this->data, index);
}

template <class TData, class TAccessor, class TConstAccessor>
TConstAccessor glutil::UboSet<TData, TAccessor, TConstAccessor>::operator[](size_t index) const
{
    return TConstAccessor(&this->data, index);
}
