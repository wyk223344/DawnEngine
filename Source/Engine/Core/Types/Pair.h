#pragma once


namespace DawnEngine
{
	template<typename T, typename U>
	class Pair
	{
    public:

        /// <summary>
        /// The first element.
        /// </summary>
        T First;

        /// <summary>
        /// The second element.
        /// </summary>
        U Second;

    public:

        /// <summary>
        /// Initializes a new instance of the <see cref="Pair"/> class.
        /// </summary>
        Pair()
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Pair"/> class.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <param name="value">The value.</param>
        Pair(const T& key, const U& value)
            : First(key)
            , Second(value)
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Pair"/> class.
        /// </summary>
        /// <param name="key">The key.</param>
        Pair(const T& key)
            : First(key)
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Pair"/> class.
        /// </summary>
        /// <param name="p">The other pair.</param>
        Pair(const Pair& p)
            : First(p.First)
            , Second(p.Second)
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Pair"/> class.
        /// </summary>
        /// <param name="p">The other pair.</param>
        Pair(Pair* p)
            : First(p->First)
            , Second(p->Second)
        {
        }

        /// <summary>
        /// Finalizes an instance of the <see cref="Pair"/> class.
        /// </summary>
        ~Pair()
        {
        }

    public:

        friend bool operator==(const Pair& a, const Pair& b)
        {
            return a.First == b.First && a.Second == b.Second;
        }

        friend bool operator!=(const Pair& a, const Pair& b)
        {
            return a.First != b.First || a.Second != b.Second;
        }
	};
}