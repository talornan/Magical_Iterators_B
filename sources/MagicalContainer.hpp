#ifndef MAGICAL_CONTAINER_HPP
#define MAGICAL_CONTAINER_HPP

#include <vector>
#include <set>
#include <stdexcept>
#include <cstdlib>
#include <memory>
#include <algorithm>
#include <cmath>

namespace ariel
{
    /*
     * @brief A magical container that stores a set of integers and provides iterators for different traversal modes.
     */
    class MagicalContainer
    {
    private:
        std::set<int> elements;                     // Set to store the unique elements
        std::vector<const int*> elementsAsc;         // Vector to store pointers to the elements in ascending order
        std::vector<const int*> elementsSide;        // Vector to store pointers to the elements in a side-to-side manner
        std::vector<const int*> elementsP;           // Vector to store pointers to the prime elements

        /*
         * @brief Checks if a number is prime.
         * 
         * @param num The number to check.
         * @return True if the number is prime, false otherwise.
         */
        static bool isPrime(int num);

    public:
        /*
         * @brief Adds an element to the container.
         * 
         * @param element The element to add.
         */
        void addElement(int element);

        /*
         * @brief Removes an element from the container.
         * 
         * @param element The element to remove.
         */
        void removeElement(int element);

        /*
         * @brief Returns the number of elements in the container.
         * 
         * @return The number of elements in the container.
         */
        size_t size() const;

        /*
         * @brief Iterator for traversing the elements in ascending order.
         */
        class AscendingIterator
        {
        public:
            /*
             * @brief Constructs an AscendingIterator object.
             * 
             * @param container Reference to the MagicalContainer object.
             * @param index Starting index of the iterator.
             */
            AscendingIterator(MagicalContainer& container, size_t index);

            /*
             * @brief Constructs an AscendingIterator object that points to the first element.
             * 
             * @param container Reference to the MagicalContainer object.
             */
            AscendingIterator(MagicalContainer& container);

            /*
             * @brief Copy constructor for AscendingIterator.
             * 
             * @param other The AscendingIterator to copy.
             */
            AscendingIterator(const AscendingIterator& other);

            /*
             * @brief Move constructor for AscendingIterator.
             * 
             * @param other The AscendingIterator to move.
             */
            AscendingIterator(AscendingIterator&& other) noexcept;

            /*
             * @brief Destructor for AscendingIterator.
             */
            ~AscendingIterator();

            /*
             * @brief Move assignment operator for AscendingIterator.
             * 
             * @param other The AscendingIterator to move.
             * @return A reference to the moved AscendingIterator.
             */
            AscendingIterator& operator=(AscendingIterator&& other) noexcept;

            /*
             * @brief Copy assignment operator for AscendingIterator.
             * 
             * @param other The AscendingIterator to copy.
             * @return A reference to the copied AscendingIterator.
             */
            AscendingIterator& operator=(const AscendingIterator& other);

            /*
             * @brief Equality operator for AscendingIterator.
             * 
             * @param other The AscendingIterator to compare.
             * @return True if the iterators are equal, false otherwise.
             */
            bool operator==(const AscendingIterator& other) const;

            /*
             * @brief Inequality operator for AscendingIterator.
             * 
             * @param other The AscendingIterator to compare.
             * @return True if the iterators are not equal, false otherwise.
             */
            bool operator!=(const AscendingIterator& other) const;

            /*
             * @brief Less than operator for AscendingIterator.
             * 
             * @param other The AscendingIterator to compare.
             * @return True if this iterator is less than the other iterator, false otherwise.
             */
            bool operator<(const AscendingIterator& other) const;

            /*
             * @brief Greater than operator for AscendingIterator.
             * 
             * @param other The AscendingIterator to compare.
             * @return True if this iterator is greater than the other iterator, false otherwise.
             */
            bool operator>(const AscendingIterator& other) const;

            /*
             * @brief Dereference operator for AscendingIterator.
             * 
             * @return The value pointed to by the iterator.
             */
            int operator*() const;

            /*
             * @brief Pre-increment operator for AscendingIterator.
             * 
             * @return A reference to the incremented iterator.
             */
            AscendingIterator& operator++();

            /*
             * @brief Returns the beginning iterator for traversing the elements in ascending order.
             * 
             * @return An AscendingIterator pointing to the first element.
             */
            AscendingIterator begin()
            {
                return AscendingIterator(container, 0);
            }

            /*
             * @brief Returns the end iterator for traversing the elements in ascending order.
             * 
             * @return An AscendingIterator pointing to the end position.
             */
            AscendingIterator end()
            {
                return AscendingIterator(container, container.elementsAsc.size());
            }

        private:
            MagicalContainer& container;    // Reference to the MagicalContainer object
            size_t index;                   // Current index of the iterator
        };

        /*
         * @brief Iterator for traversing the elements in a side-to-side manner.
         */

        class SideCrossIterator
        {
        public:
            /*
             * @brief Constructs a SideCrossIterator object.
             * 
             * @param container Reference to the MagicalContainer object.
             * @param index Starting index of the iterator.
             */
            SideCrossIterator(MagicalContainer& container, size_t index);
         
            /*
             * @brief Constructs a SideCrossIterator object that points to the first element.
             * 
             * @param container Reference to the MagicalContainer object.
             */
            SideCrossIterator(MagicalContainer& container);

            /*
             * @brief Copy constructor for SideCrossIterator.
             * 
             * @param other The SideCrossIterator to copy.
             */
            SideCrossIterator(const SideCrossIterator& other);

            /*
             * @brief Move constructor for SideCrossIterator.
             * 
             * @param other The SideCrossIterator to move.
             */
            SideCrossIterator(SideCrossIterator&& other) noexcept;

            /*
             * @brief Destructor for SideCrossIterator.
             */
            ~SideCrossIterator();

            /*
             * @brief Move assignment operator for SideCrossIterator.
             * 
             * @param other The SideCrossIterator to move.
             * @return A reference to the moved SideCrossIterator.
             */
            SideCrossIterator& operator=(SideCrossIterator&& other) noexcept;

            /*
             * @brief Copy assignment operator for SideCrossIterator.
             * 
             * @param other The SideCrossIterator to copy.
             * @return A reference to the copied SideCrossIterator.
             */
            SideCrossIterator& operator=(const SideCrossIterator& other);

            /*
             * @brief Equality operator for SideCrossIterator.
             * 
             * @param other The SideCrossIterator to compare.
             * @return True if the iterators are equal, false otherwise.
             */
            bool operator==(const SideCrossIterator& other) const;

            /*
             * @brief Inequality operator for SideCrossIterator.
             * 
             * @param other The SideCrossIterator to compare.
             * @return True if the iterators are not equal, false otherwise.
             */
            bool operator!=(const SideCrossIterator& other) const;

            /*
             * @brief Less than operator for SideCrossIterator.
             * 
             * @param other The SideCrossIterator to compare.
             * @return True if this iterator is less than the other iterator, false otherwise.
             */
            bool operator<(const SideCrossIterator& other) const;

            /*
             * @brief Greater than operator for SideCrossIterator.
             * 
             * @param other The SideCrossIterator to compare.
             * @return True if this iterator is greater than the other iterator, false otherwise.
             */
            bool operator>(const SideCrossIterator& other) const;

            /*
             * @brief Dereference operator for SideCrossIterator.
             * 
             * @return The value pointed to by the iterator.
             */
            int operator*() const;

            /*
             * @brief Pre-increment operator for SideCrossIterator.
             * 
             * @return A reference to the incremented iterator.
             */
            SideCrossIterator& operator++();

            /*
             * @brief Returns the beginning iterator for traversing the elements in a side-to-side manner.
             * 
             * @return A SideCrossIterator pointing to the first element.
             */
            SideCrossIterator begin()
            {
                return SideCrossIterator(container, 0);
            }

            /*
             * @brief Returns the end iterator for traversing the elements in a side-to-side manner.
             * 
             * @return A SideCrossIterator pointing to the end position.
             */
            SideCrossIterator end()
            {
                return SideCrossIterator(container, container.elementsSide.size());
            }

        private:
            MagicalContainer& container;    // Reference to the MagicalContainer object
            size_t index;                   // Current index of the iterator
        };

        /*
         * @brief Iterator for traversing the prime elements in the container.
         */
        class PrimeIterator
        {
        public:
            /*
             * @brief Constructs a PrimeIterator object.
             * 
             * @param container Reference to the MagicalContainer object.
             * @param index Starting index of the iterator.
             */
            PrimeIterator(MagicalContainer& container, size_t index);

            /*
             * @brief Constructs a PrimeIterator object that points to the first prime element.
             * 
             * @param container Reference to the MagicalContainer object.
             */
            PrimeIterator(MagicalContainer& container);

            /*
             * @brief Copy constructor for PrimeIterator.
             * 
             * @param other The PrimeIterator to copy.
             */
            PrimeIterator(const PrimeIterator& other);

            /*
             * @brief Destructor for PrimeIterator.
             */
            ~PrimeIterator();

            PrimeIterator(PrimeIterator &&other) noexcept;

            /*
             * @brief Move assignment operator for PrimeIterator.
             * 
             * @param other The PrimeIterator to move.
             * @return A reference to the moved PrimeIterator.
             */
            PrimeIterator& operator=(PrimeIterator&& other) noexcept;

            /*
             * @brief Copy assignment operator for PrimeIterator.
             * 
             * @param other The PrimeIterator to copy.
             * @return A reference to the copied PrimeIterator.
             */
            PrimeIterator& operator=(const PrimeIterator& other);

            

            /*
             * @brief Equality operator for PrimeIterator.
             * 
             * @param other The PrimeIterator to compare.
             * @return True if the iterators are equal, false otherwise.
             */
            bool operator==(const PrimeIterator& other) const;

            /*
             * @brief Inequality operator for PrimeIterator.
             * 
             * @param other The PrimeIterator to compare.
             * @return True if the iterators are not equal, false otherwise.
             */
            bool operator!=(const PrimeIterator& other) const;

            /*
             * @brief Less than operator for PrimeIterator.
             * 
             * @param other The PrimeIterator to compare.
             * @return True if this iterator is less than the other iterator, false otherwise.
             */
            bool operator<(const PrimeIterator& other) const;

            /*
             * @brief Greater than operator for PrimeIterator.
             * 
             * @param other The PrimeIterator to compare.
             * @return True if this iterator is greater than the other iterator, false otherwise.
             */
            bool operator>(const PrimeIterator& other) const;

            /*
             * @brief Dereference operator for PrimeIterator.
             * 
             * @return The value pointed to by the iterator.
             */
            int operator*() const;

            /*
             * @brief Pre-increment operator for PrimeIterator.
             * 
             * @return A reference to the incremented iterator.
             */
            PrimeIterator& operator++();

            /*
             * @brief Returns the beginning iterator for traversing the prime elements in the container.
             * 
             * @return A PrimeIterator pointing to the first prime element.
             */
            PrimeIterator begin()
            {
                return PrimeIterator(container, 0);
            }

            /*
             * @brief Returns the end iterator for traversing the prime elements in the container.
             * 
             * @return A PrimeIterator pointing to the end position.
             */
            PrimeIterator end()         
            {
                return PrimeIterator(container, container.elementsP.size());
            }

        private:
            MagicalContainer& container;    // Reference to the MagicalContainer object
            size_t index;                   // Current index of the iterator
        };
    };


#endif 

}