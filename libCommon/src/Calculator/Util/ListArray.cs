namespace Matheparser.Util
{
    using System.Collections;
    using System.Collections.Generic;
    using Matheparser.Exceptions;
    using Matheparser.Values;

    class ListArray : IArray
    {
        private List<IValue> data;

        public ListArray()
        {
            this.data = new List<IValue>();
        }

        public ListArray(IEnumerable<IValue> items) :
            this()
        {
            this.data.AddRange(items);
        }

        public ListArray(IValue item) :
            this()
        {
            this.data.Add(item);
        }

        public int Count
        {
            get
            {
                return this.data.Count;
            }
        }

        public bool Contains(IValue item)
        {
            return this.data.Contains(item);
        }

        public IArray Combine(IArray other)
        {
            var res = new List<IValue>();

            res.AddRange(this.data);
            res.AddRange(other);

            return new ListArray() { data = res };
        }

        public void Add(IValue value)
        {
            this.data.Add(value);
        }

        public IValue At(int index)
        {
            if (index < 0 || index > this.data.Count)
            {
                throw new IndexOutOfBoundsException();
            }

            return this.AtUnsafe(index);
        }

        public IValue AtUnsafe(int index)
        {
            return this.data[index];
        }

        public IArray Cut(IArray other)
        {
            var res = new List<IValue>();

            foreach (var item in this.data)
            {
                if (other.Contains(item))
                {
                    res.Add(item);
                }
            }

            return new ListArray() { data = res };
        }

        public IArray Except(IArray other)
        {
            var res = new List<IValue>();

            foreach (var item in this.data)
            {
                if (!other.Contains(item))
                {
                    res.Add(item);
                }
            }

            return new ListArray() { data = res };
        }

        public IArray Union(IArray other)
        {
            var res = new List<IValue>(this.data);

            foreach (var item in other)
            {
                if (!res.Contains(item))
                {
                    res.Add(item);
                }
            }

            return new ListArray() { data = res };
        }

        public IEnumerator<IValue> GetEnumerator()
        {
            return this.data.GetEnumerator();
        }

        public IArray Range(int start, int end)
        {
            if (start < 0 || end > this.data.Count || start > end)
            {
                throw new IndexOutOfBoundsException();
            }

            return this.RangeUnsafe(start, end);
        }

        public IArray RangeUnsafe(int start, int end)
        {
            return new ListArray() { data = this.data.GetRange(start, end - start) };
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
    }
}
