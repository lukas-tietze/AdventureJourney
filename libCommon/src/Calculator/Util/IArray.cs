namespace Matheparser.Util
{
    using System.Collections.Generic;
    using Matheparser.Values;

    public interface IArray : IEnumerable<IValue>
    {
        /// <summary>
        /// Holt die Anzahl der Elemente in der Menge.
        /// </summary>
        int Count
        {
            get;
        }

        void Add(IValue value);

        bool Contains(IValue value);

        IValue At(int index);

        IValue AtUnsafe(int index);

        IArray Range(int start, int end);

        IArray RangeUnsafe(int start, int end);
        
        IArray Combine(IArray setB);

        /// <summary>
        /// Erzeugt die Vereinigung der aktuellen Menge mit der gegebenen Menge <paramref name="other"/>.
        /// Die erzeugter Menge enthält alle Elemente, die in der aktuellen Menge oder in <paramref name="other"/> vorkommen.
        /// </summary>
        /// <param name="other">Die Menge, mit der die Vereinigung gebildet werden soll.</param>
        /// <returns>Die Vereinigung beider Mengen.</returns>
        IArray Union(IArray other);

        /// <summary>
        /// Erzeugt die Schnittmenge der aktuellen Menge mit der gegebenen Menge <paramref name="other"/>.
        /// Die erzeugte Menge enthält alle Elemente, die in der aktuellen Menge und in <paramref name="other"/> vorkommen.
        /// </summary>
        /// <param name="other">Die Menge, mit der die Schnittmenge gebildet werden soll.</param>
        /// <returns>Die Schnittmenge beider Mengen.</returns>
        IArray Cut(IArray other);

        /// <summary>
        /// Erzeugt die Differenzmenge der aktuellen Menge mit der gegebenen Menge  <paramref name="other"/>.
        /// Die erzeugte Menge erhält alle Elemente, die in der aktuellen Menge vorkommen, aber nicht in <paramref name="other"/>.
        /// </summary>
        /// <param name="other">Die Menge, mit der die Differenz gebildet werden soll.</param>
        /// <returns>Die Differenzmenge beider Mengen.</returns>
        IArray Except(IArray other);
    }
}
