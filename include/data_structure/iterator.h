//
// Created by Eden_ on 2024/9/11.
//

#ifndef ITERATOR_H
#define ITERATOR_H

namespace iterator
{
    enum type
    {
        BASIC,
        FORWARD,
        BIDIRECTIONAL,
        RANDOM_ACCESS
    };

    template<typename T>
    class BasicIterator
    {
    public:
        BasicIterator() = delete;
        virtual ~BasicIterator() = default;

        virtual explicit operator BasicIterator<const T>() const =0;

        /**
         * This method allows you to access and modify the value at the current position of the iterator.
         * @return A reference to the Pair pointed to by the iterator
         */
        virtual T &operator*() const =0;

        /**
         * This method provides access to the value pointed to by the iterator, similar to dereferencing the iterator.
         * @return A pointer to the Pair pointed to by the iterator.
         */
        virtual T *operator->() const =0;

        /**
         * This method checks if two iterators are pointing to the same element.
         * @param other other iterator
         * @return true if the current iterator is equal to the other iterator (i.e., they point to the same position);
         * otherwise, false.
         */
        virtual bool operator==(const BasicIterator &other) const =0;

        /**
         * This method checks if two iterators are pointing to different elements.
         * @param other other iterator
         * @return true if the current iterator is not equal to the other iterator (i.e., they point to different
         * positions); otherwise, false.
         */
        virtual bool operator!=(const BasicIterator &other) const =0;
    };

    template<typename T>
    class ForwardIterator : public BasicIterator<T>
    {
    public:
        ForwardIterator() = delete;
        ~ForwardIterator() override = default;

        /**
         * This is the pre-increment operator. It advances the iterator by one position and returns a reference to the
         * modified iterator itself.
         * @return A reference to the updated iterator after it has been incremented.
         */
        virtual ForwardIterator &operator++() =0;
    };

    template<typename T>
    class BidirectionalIterator : public ForwardIterator<T>
    {
    public:
        BidirectionalIterator() = delete;
        ~BidirectionalIterator() override = default;

        /**
         * This method moves the iterator backward by one position (pre-decrement) and returns the iterator itself.
         * @return  A reference to the updated iterator after it has been decremented.
         */
        virtual BidirectionalIterator &operator--() =0;
    };

    template<typename T>
    class RandomAccessIterator : public BidirectionalIterator<T>
    {
    public:
        RandomAccessIterator() = delete;
        ~RandomAccessIterator() override = default;

        /**
         * This method advances the iterator by 'n' positions and returns the iterator itself.
         * Complexity: O(1)
         * @param n moving distance
         * @return A reference to the updated iterator after advancing it by 'n' positions.
         */
        virtual RandomAccessIterator& operator+=(size_t n) =0;

        /**
         * This method moves the iterator backward by 'n' positions and returns the iterator itself.
         * Complexity: O(1)
         * @param n moving distance
         * @return A reference to the updated iterator after moving it back by 'n' positions.
         */
        virtual RandomAccessIterator& operator-=(size_t n) =0;

        /**
         * This method creates a copy of the iterator advanced by 'n' positions.
         * Complexity: O(1)
         * @param n moving distance
         * @return An iterator pointing to the position 'n' steps ahead of the current iterator.
         */
        virtual std::unique_ptr<RandomAccessIterator> operator+(size_t n) const =0;

        /**
         * This method creates a copy of the iterator moved back by 'n' positions.
         * Complexity: O(1)
         * @param n moving distance
         * @return An iterator pointing to the position 'n' steps behind the current iterator.
         */
        virtual std::unique_ptr<RandomAccessIterator> operator-(size_t n) const =0;

        /**
         * This method compares if the current iterator is before the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is less than the other iterator; otherwise, false.
         */
        virtual bool operator<(const RandomAccessIterator& other) const =0;

        /**
         * This method compares if the current iterator is after the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is greater than the other iterator; otherwise, false.
         */
        virtual bool operator>(const RandomAccessIterator& other) const =0;

        /**
         * This method checks if the current iterator is before or at the same position as the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is less than or equal to the other iterator; otherwise, false.
         */
        virtual bool operator<=(const RandomAccessIterator& other) const =0;

        /**
         * This method checks if the current iterator is after or at the same position as the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is greater than or equal to the other iterator; otherwise, false.
         */
        virtual bool operator>=(const RandomAccessIterator& other) const =0;

        /**
         * This method calculates the distance between the current iterator and the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return The number of positions between the current iterator and the other iterator.
         */
        virtual size_t operator-(const RandomAccessIterator& other) const =0;
    };
}

#endif //ITERATOR_H
