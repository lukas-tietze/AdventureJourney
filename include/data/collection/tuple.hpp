#pragma once

namespace util
{
template <class T1, class T2>
class tuple2
{
  private:
    T1 item1;
    T2 item2;

  public:
    tuple2() : item1(),
               item2()
    {
    }

    tuple2(const T1 &item1, const T2 &item2) : item1(item1),
                                               item2(item2)
    {
    }

    T1 &item_1() { return this->item1; }
    const T1 &item_1() const { return this->item1; }

    T2 &item_2() { return this->item2; }
    const T2 &item_2() const { return this->item2; }
};

template <class T1, class T2, class T3>
class tuple3
{
  private:
    T1 item1;
    T2 item2;
    T3 item3;

  public:
    tuple3() : item1(),
               item2(),
               item3()
    {
    }

    tuple3(const T1 &item1, const T2 &item2, const T3 &item3) : item1(item1),
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
class tuple4
{
  private:
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;

  public:
    tuple4() : item1(),
               item2(),
               item3(),
               item4()
    {
    }

    tuple4(const T1 &item1, const T2 &item2, const T3 &item3, const T4 &item4) : item1(item1),
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
class tuple5
{
  private:
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;
    T5 item5;

  public:
    tuple5() : item1(),
               item2(),
               item3(),
               item4(),
               item5()
    {
    }

    tuple5(const T1 &item1, const T2 &item2, const T3 &item3, const T4 &item4, const T5 &item5) : item1(item1),
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
tuple2<T1, T2> make_tuple(const T1 &item1, const T2 &item2)
{
    return tuple2<T1, T2>(item1, item2);
}

template <class T1, class T2, class T3>
tuple3<T1, T2, T3> make_tuple(const T1 &item1, const T2 &item2, const T3 &item3)
{
    return tuple3<T1, T2, T3>(item1, item2, item3);
}

template <class T1, class T2, class T3, class T4>
tuple4<T1, T2, T3, T4> make_tuple(const T1 &item1, const T2 &item2, const T3 &item3, const T4 &item4)
{
    return tuple4<T1, T2, T3, T4>(item1, item2, item3, item4);
}

template <class T1, class T2, class T3, class T4, class T5>
tuple5<T1, T2, T3, T4, T5> make_tuple(const T1 &item1, const T2 &item2, const T3 &item3, const T4 &item4, const T5 &item5)
{
    return tuple5<T1, T2, T3, T4, T5>(item1, item2, item3, item4, item5);
}
} // namespace util