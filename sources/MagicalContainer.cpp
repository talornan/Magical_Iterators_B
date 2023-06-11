#include "MagicalContainer.hpp"

using namespace std;


namespace ariel{
bool MagicalContainer::isPrime(int num)
{
    if (num < 0)
        num = -num;

    if (num <= 1)
    {
        return false;
    }

    for (int i = 2; i <= sqrt(num); ++i)
    {
        if (num % i == 0)
        {
            return false;
        }
    }

    return true;
}

void MagicalContainer::addElement(int element)
{
    auto in = elements.insert(element);

    if (in.second)
    {
        const int *address = &(*in.first);

        elementsAsc.insert(upper_bound(elementsAsc.begin(), elementsAsc.end(), address, [](const int* a, const int* b) { return *a<*b;}), address);

        elementsSide.clear();
        elementsSide.reserve(elementsAsc.size());

        size_t start = 0, end = elementsAsc.size() - 1;

        if (isPrime(element))
        {
            elementsP.insert(upper_bound(elementsP.begin(), elementsP.end(), address, [](const int* a, const int* b) { return *a<*b;}), address);
        }

        if (size() == 1)
        {
            elementsSide.push_back(elementsAsc.front());
            return;
        }

        while (start <= end && end != 0)
        {
            elementsSide.push_back(elementsAsc.at(start));

            if (start != end)
            {
                elementsSide.push_back(elementsAsc.at(end));
            }

            start++;
            end--;
        }
    }
}


void MagicalContainer::removeElement(int element)
{
    auto it = elements.find(element);

    if (it == elements.end())
    {
        throw runtime_error("Error: element not found");
    }

    const int *address = &(*it);
    elements.erase(it);

    if (isPrime(element))
    {
        auto it_prime = find(elementsP.begin(), elementsP.end(), address);
        if (it_prime != elementsP.end())
        {
            elementsP.erase(it_prime);
        }
    }

    auto it_ascending = find(elementsAsc.begin(), elementsAsc.end(), address);
    if (it_ascending != elementsAsc.end())
    {
        elementsAsc.erase(it_ascending);
    }

    elementsSide.clear();
    elementsSide.reserve(elementsAsc.size());

    if (size() == 0)
        return;

    else if (size() == 1)
    {
        elementsSide.push_back(elementsAsc.front());
        return;
    }

    size_t start = 0, end = elementsAsc.size() - 1;

    while (start <= end && end != 0)
    {
        elementsSide.push_back(elementsAsc.at(start));

        if (start != end)
        {
            elementsSide.push_back(elementsAsc.at(end));
        }

        start++;
        end--;
    }
}

size_t MagicalContainer::size() const
{
    return elements.size();
}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, size_t index)
    : container(container), index(index) {}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container)
    : container(container), index(0) {}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
    : container(other.container), index(other.index) {}

MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator &&other) noexcept
    : container(other.container), index(other.index) {}
MagicalContainer::AscendingIterator::~AscendingIterator(){}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
{
    if (this != &other)
    {
        if (&other.container != &container)
        {
            throw runtime_error("Iterators are not from the same container");
        }
        index = other.index;
    }

    return *this;
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(AscendingIterator &&other) noexcept
{
    if (this != &other)
    {
        container = move(other.container);
        index = move(other.index);
    }

    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
{
    if (&other.container != &container)
    {
        throw runtime_error("Iterators are not from the same container");
    }
    return index == other.index;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
{
    if (&other.container != &container)
    {
        throw runtime_error("Iterators are not from the same container");
    }
    return index != other.index;
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
{
    if (&other.container != &container)
    {
        throw runtime_error("Iterators are not from the same container");
    }
    return index > other.index;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
{
    if (&other.container != &container)
    {
        throw runtime_error("Iterators are not from the same container");
    }
    return index < other.index;
}

int MagicalContainer::AscendingIterator::operator*() const
{
    if (index >= container.elementsAsc.size())
    {
        throw out_of_range("Iterator out of range");
    }

    return *(container.elementsAsc.at(index));
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    if (index >= container.elementsAsc.size())
    {
        throw runtime_error("Iterator out of range");
    }

    ++index;
    return *this;
}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, size_t index)
    : container(container), index(index) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container)
    : container(container), index(0) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
    : container(other.container), index(other.index) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator &&other) noexcept
    : container(other.container), index(other.index) {}
MagicalContainer::SideCrossIterator::~SideCrossIterator(){}
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
{
    if (this != &other)
    {
        if (&other.container != &container)
        {
            throw runtime_error("Iterators are not from the same container");
        }
        index = other.index;
    }

    return *this;
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(SideCrossIterator &&other) noexcept
{
    if (this != &other)
    {
        container = move(other.container);
        index = move(other.index);
    }

    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
{
    if (&other.container != &container)
    {
        throw runtime_error("Iterators are not from the same container");
    }
    return index == other.index;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
{
    if (&other.container != &container)
    {
        throw runtime_error("Iterators are not from the same container");
    }
    return index != other.index;
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
{
    if (&other.container != &container)
    {
        throw runtime_error("Iterators are not from the same container");
    }
    return index > other.index;
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
{
    if (&other.container != &container)
    {
        throw runtime_error("Iterators are not from the same container");
    }
    return index < other.index;
}

int MagicalContainer::SideCrossIterator::operator*() const
{
    if (index >= container.elementsSide.size())
    {
        throw out_of_range("Iterator out of range");
    }

    return *(container.elementsSide.at(index));
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    if (index >= container.elementsSide.size())
    {
        throw runtime_error("Iterator out of range");
    }

    ++index;
    return *this;
}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container, size_t index)
    : container(container), index(index) {}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container)
    : container(container), index(0) {}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
    : container(other.container), index(other.index) {}

MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator &&other) noexcept
    : container(other.container), index(other.index) {}
MagicalContainer::PrimeIterator::~PrimeIterator(){}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    if (this != &other)
    {
        if (&other.container != &container)
        {
            throw runtime_error("Iterators are not from the same container");
        }
        index = other.index;
    }

    return *this;
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(PrimeIterator &&other) noexcept
{
    if (this != &other)
    {
        container = move(other.container);
        index = move(other.index);
    }

    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
{
    if (&other.container != &container)
    {
        throw runtime_error("Iterators are not from the same container");
    }
    return index == other.index;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
{
    if (&other.container != &container)
    {
        throw runtime_error("Iterators are not from the same container");
    }

    return index != other.index;
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
{
    if (&other.container != &container)
    {
        throw runtime_error("Iterators are not from the same container");
    }

    return index > other.index;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
{
    if (&other.container != &container)
    {
        throw runtime_error("Iterators are not from the same container");
    }

    return index < other.index;
}

int MagicalContainer::PrimeIterator::operator*() const
{
    if (index >= container.elementsP.size())
    {
        throw out_of_range("Iterator out of range");
    }

    return *(container.elementsP.at(index));
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    if (index >= container.elementsP.size())
    {
        throw runtime_error("Iterator out of range");
    }

    ++index;
    return *this;
}
}