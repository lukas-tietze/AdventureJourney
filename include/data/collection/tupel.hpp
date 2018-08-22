#ifndef TUPEL_HPP
#define TUPEL_HPP

namespace util
{
template <class T1, class T2>
class tupel2
{
  private:
    T1 item1;
    T2 item2;

  public:
    tupel2(const T1 &item1, const T2 &item2) : item1(item1),
                                               item2(item2)
    {
    }

    T1 &item_1() { return this->item1; }
    const T1 &item_1() const { return this->item1; }

    T2 &item_2() { return this->item2; }
    const T2 &item_2() const { return this->item2; }
};

template <class T1, class T2, class T3>
class tupel3
{
  private:
    T1 item1;
    T2 item2;
    T3 item3;

  public:
    tupel3(const T1 &item1, const T2 &item2, const T3 &item3) : item1(item1),
                                                                item2(item2),
                                                                item3(item3)
    {
    }

    T1 &item_1() { return this->item1; }
    const T1 &item_1() const { return this->item1; }

    T2 &item_2() { return this->item2; }
    const T2 &item_2() const { return this->item2; }

    T3 &item_3() { return this->item3; }
    const T3 &item_3() const { return this->item3; }
};

template <class T1, class T2, class T3, class T4>
class tupel4
{
  private:
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;

  public:
    tupel4(const T1 &item1, const T2 &item2, const T3 &item3, const T4 &item4) : item1(item1),
                                                                                 item2(item2),
                                                                                 item3(item3),
                                                                                 item4(item4)
    {
    }

    T1 &item_1() { return this->item1; }
    const T1 &item_1() const { return this->item1; }

    T2 &item_2() { return this->item2; }
    const T2 &item_2() const { return this->item2; }

    T3 &item_3() { return this->item3; }
    const T3 &item_3() const { return this->item3; }

    T4 &item_4() { return this->item4; }
    const T4 &item_4() const { return this->item4; }
};

template <class T1, class T2, class T3, class T4, class T5>
class tupel5
{
  private:
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;
    T5 item5;

  public:
    tupel5(const T1 &item1, const T2 &item2, const T3 &item3, const T4 &item4, const T5 &item5) : item1(item1),
                                                                                                  item2(item2),
                                                                                                  item3(item3),
                                                                                                  item4(item4),
                                                                                                  item5(item5)
    {
    }

    T1 &item_1() { return this->item1; }
    const T1 &item_1() const { return this->item1; }

    T2 &item_2() { return this->item2; }
    const T2 &item_2() const { return this->item2; }

    T3 &item_3() { return this->item3; }
    const T3 &item_3() const { return this->item3; }

    T4 &item_4() { return this->item4; }
    const T4 &item_4() const { return this->item4; }

    T5 &item_5() { return this->item5; }
    const T5 &item_5() const { return this->item5; }
};

template <class T1, class T2>
tupel2<T1, T2> make_tupel(const T1 &item1, const T2 &item2)
{
    return tupel2<T1, T2>(item1, item2);
}

template <class T1, class T2, class T3>
tupel3<T1, T2, T3> make_tupel(const T1 &item1, const T2 &item2, const T3 &item3)
{
    return tupel3<T1, T2, T3>(item1, item2, item3);
}

template <class T1, class T2, class T3, class T4>
tupel4<T1, T2, T3, T4> make_tupel(const T1 &item1, const T2 &item2, const T3 &item3, const T4 &item4)
{
    return tupel4<T1, T2, T3, T4>(item1, item2, item3, item4);
}

template <class T1, class T2, class T3, class T4, class T5>
tupel5<T1, T2, T3, T4, T5> make_tupel(const T1 &item1, const T2 &item2, const T3 &item3, const T4 &item4, const T5 &item5)
{
    return tupel5<T1, T2, T3, T4, T5>(item1, item2, item3, item4, item5);
}
} // namespace util

#endif /*TUPEL_HPP*/