#ifndef MINI_STL_ALGORITHM_H
#define MINI_STL_ALGORITHM_H

#include <iterator>
#include <functional>
#include <algorithm>
#include <vector>

namespace mini_stl {

// Forward declarations
template<typename Iterator, typename Compare>
void sort(Iterator first, Iterator last, Compare comp);

template<typename Iterator>
void sort(Iterator first, Iterator last);

// Insertion sort implementation
template<typename Iterator, typename Compare>
void insertion_sort(Iterator first, Iterator last, Compare comp) {
    if (first == last) return;
    
    for (auto it = std::next(first); it != last; ++it) {
        auto key = *it;
        auto j = it;
        
        while (j != first && comp(key, *std::prev(j))) {
            *j = *std::prev(j);
            --j;
        }
        *j = key;
    }
}

// Quick sort implementation
template<typename Iterator, typename Compare>
void quick_sort(Iterator first, Iterator last, Compare comp) {
    if (first == last) return;
    
    auto distance = std::distance(first, last);
    if (distance <= 10) {
        insertion_sort(first, last, comp);
        return;
    }
    
    // Choose pivot (median of three)
    auto mid = std::next(first, distance / 2);
    auto end = std::prev(last);
    
    if (comp(*mid, *first)) std::swap(*first, *mid);
    if (comp(*end, *first)) std::swap(*first, *end);
    if (comp(*end, *mid)) std::swap(*mid, *end);
    
    auto pivot = *mid;
    
    // Partition
    auto i = first;
    auto j = std::prev(last);
    
    while (i <= j) {
        while (comp(*i, pivot)) ++i;
        while (comp(pivot, *j)) --j;
        
        if (i <= j) {
            std::swap(*i, *j);
            ++i;
            --j;
        }
    }
    
    // Recursively sort partitions
    if (std::distance(first, j) < std::distance(i, last)) {
        quick_sort(first, std::next(j), comp);
        quick_sort(i, last, comp);
    } else {
        quick_sort(i, last, comp);
        quick_sort(first, std::next(j), comp);
    }
}

// Heap sort implementation
template<typename Iterator, typename Compare>
void heap_sort(Iterator first, Iterator last, Compare comp) {
    auto distance = std::distance(first, last);
    if (distance <= 1) return;
    
    // Build heap
    for (auto i = std::next(first, distance / 2 - 1); i >= first; --i) {
        heapify(first, last, i, comp);
    }
    
    // Extract elements from heap
    for (auto i = std::prev(last); i != first; --i) {
        std::swap(*first, *i);
        heapify(first, i, first, comp);
    }
}

template<typename Iterator, typename Compare>
void heapify(Iterator first, Iterator last, Iterator root, Compare comp) {
    auto distance = std::distance(first, last);
    auto root_index = std::distance(first, root);
    auto largest = root_index;
    auto left = 2 * root_index + 1;
    auto right = 2 * root_index + 2;
    
    if (left < distance && comp(*std::next(first, largest), *std::next(first, left))) {
        largest = left;
    }
    
    if (right < distance && comp(*std::next(first, largest), *std::next(first, right))) {
        largest = right;
    }
    
    if (largest != root_index) {
        std::swap(*std::next(first, root_index), *std::next(first, largest));
        heapify(first, last, std::next(first, largest), comp);
    }
}

// Merge sort implementation
template<typename Iterator, typename Compare>
void merge_sort(Iterator first, Iterator last, Compare comp) {
    auto distance = std::distance(first, last);
    if (distance <= 1) return;
    
    auto mid = std::next(first, distance / 2);
    merge_sort(first, mid, comp);
    merge_sort(mid, last, comp);
    merge(first, mid, last, comp);
}

template<typename Iterator, typename Compare>
void merge(Iterator first, Iterator mid, Iterator last, Compare comp) {
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    
    std::vector<value_type> temp(std::distance(first, last));
    auto it1 = first;
    auto it2 = mid;
    auto temp_it = temp.begin();
    
    while (it1 != mid && it2 != last) {
        if (comp(*it1, *it2)) {
            *temp_it++ = *it1++;
        } else {
            *temp_it++ = *it2++;
        }
    }
    
    while (it1 != mid) {
        *temp_it++ = *it1++;
    }
    
    while (it2 != last) {
        *temp_it++ = *it2++;
    }
    
    std::copy(temp.begin(), temp.end(), first);
}

// Main sort function with strategy selection
template<typename Iterator, typename Compare>
void sort(Iterator first, Iterator last, Compare comp) {
    if (first == last) return;
    
    auto distance = std::distance(first, last);
    
    // Choose sorting algorithm based on size
    if (distance <= 10) {
        insertion_sort(first, last, comp);
    } else if (distance <= 100) {
        quick_sort(first, last, comp);
    } else {
        merge_sort(first, last, comp);
    }
}

template<typename Iterator>
void sort(Iterator first, Iterator last) {
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    sort(first, last, std::less<value_type>{});
}

// Stable sort implementation
template<typename Iterator, typename Compare>
void stable_sort(Iterator first, Iterator last, Compare comp) {
    merge_sort(first, last, comp);
}

template<typename Iterator>
void stable_sort(Iterator first, Iterator last) {
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    stable_sort(first, last, std::less<value_type>{});
}

// Partial sort implementation
template<typename Iterator, typename Compare>
void partial_sort(Iterator first, Iterator middle, Iterator last, Compare comp) {
    if (first == middle) return;
    
    // Build heap of first (middle - first) elements
    auto distance = std::distance(first, middle);
    for (auto i = std::next(first, distance / 2 - 1); i >= first; --i) {
        heapify(first, middle, i, comp);
    }
    
    // Process remaining elements
    for (auto it = middle; it != last; ++it) {
        if (comp(*it, *first)) {
            std::swap(*it, *first);
            heapify(first, middle, first, comp);
        }
    }
    
    // Sort the heap
    for (auto it = std::prev(middle); it != first; --it) {
        std::swap(*first, *it);
        heapify(first, it, first, comp);
    }
}

template<typename Iterator>
void partial_sort(Iterator first, Iterator middle, Iterator last) {
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    partial_sort(first, middle, last, std::less<value_type>{});
}

// Nth element implementation
template<typename Iterator, typename Compare>
void nth_element(Iterator first, Iterator nth, Iterator last, Compare comp) {
    if (first == last || nth == last) return;
    
    auto left = first;
    auto right = std::prev(last);
    
    while (left < right) {
        auto pivot = partition(left, right, comp);
        
        if (pivot == nth) {
            return;
        } else if (pivot < nth) {
            left = std::next(pivot);
        } else {
            right = std::prev(pivot);
        }
    }
}

template<typename Iterator>
void nth_element(Iterator first, Iterator nth, Iterator last) {
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    nth_element(first, nth, last, std::less<value_type>{});
}

template<typename Iterator, typename Compare>
Iterator partition(Iterator first, Iterator last, Compare comp) {
    auto pivot = *last;
    auto i = first;
    
    for (auto j = first; j != last; ++j) {
        if (comp(*j, pivot)) {
            std::swap(*i, *j);
            ++i;
        }
    }
    
    std::swap(*i, *last);
    return i;
}

// Find implementation
template<typename Iterator, typename T>
Iterator find(Iterator first, Iterator last, const T& value) {
    for (auto it = first; it != last; ++it) {
        if (*it == value) {
            return it;
        }
    }
    return last;
}

template<typename Iterator, typename Predicate>
Iterator find_if(Iterator first, Iterator last, Predicate pred) {
    for (auto it = first; it != last; ++it) {
        if (pred(*it)) {
            return it;
        }
    }
    return last;
}

template<typename Iterator, typename Predicate>
Iterator find_if_not(Iterator first, Iterator last, Predicate pred) {
    for (auto it = first; it != last; ++it) {
        if (!pred(*it)) {
            return it;
        }
    }
    return last;
}

// Count implementation
template<typename Iterator, typename T>
typename std::iterator_traits<Iterator>::difference_type
count(Iterator first, Iterator last, const T& value) {
    typename std::iterator_traits<Iterator>::difference_type result = 0;
    for (auto it = first; it != last; ++it) {
        if (*it == value) {
            ++result;
        }
    }
    return result;
}

template<typename Iterator, typename Predicate>
typename std::iterator_traits<Iterator>::difference_type
count_if(Iterator first, Iterator last, Predicate pred) {
    typename std::iterator_traits<Iterator>::difference_type result = 0;
    for (auto it = first; it != last; ++it) {
        if (pred(*it)) {
            ++result;
        }
    }
    return result;
}

// Transform implementation
template<typename InputIterator, typename OutputIterator, typename UnaryOperation>
OutputIterator transform(InputIterator first, InputIterator last, 
                        OutputIterator result, UnaryOperation op) {
    for (auto it = first; it != last; ++it, ++result) {
        *result = op(*it);
    }
    return result;
}

template<typename InputIterator1, typename InputIterator2, 
         typename OutputIterator, typename BinaryOperation>
OutputIterator transform(InputIterator1 first1, InputIterator1 last1,
                        InputIterator2 first2, OutputIterator result, 
                        BinaryOperation op) {
    for (auto it1 = first1, it2 = first2; it1 != last1; ++it1, ++it2, ++result) {
        *result = op(*it1, *it2);
    }
    return result;
}

// Accumulate implementation
template<typename InputIterator, typename T>
T accumulate(InputIterator first, InputIterator last, T init) {
    for (auto it = first; it != last; ++it) {
        init = init + *it;
    }
    return init;
}

template<typename InputIterator, typename T, typename BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation op) {
    for (auto it = first; it != last; ++it) {
        init = op(init, *it);
    }
    return init;
}

// Min/Max implementation
template<typename T>
const T& min(const T& a, const T& b) {
    return (b < a) ? b : a;
}

template<typename T, typename Compare>
const T& min(const T& a, const T& b, Compare comp) {
    return comp(b, a) ? b : a;
}

template<typename T>
const T& max(const T& a, const T& b) {
    return (a < b) ? b : a;
}

template<typename T, typename Compare>
const T& max(const T& a, const T& b, Compare comp) {
    return comp(a, b) ? b : a;
}

template<typename Iterator>
Iterator min_element(Iterator first, Iterator last) {
    if (first == last) return last;
    
    Iterator min_it = first;
    for (auto it = std::next(first); it != last; ++it) {
        if (*it < *min_it) {
            min_it = it;
        }
    }
    return min_it;
}

template<typename Iterator, typename Compare>
Iterator min_element(Iterator first, Iterator last, Compare comp) {
    if (first == last) return last;
    
    Iterator min_it = first;
    for (auto it = std::next(first); it != last; ++it) {
        if (comp(*it, *min_it)) {
            min_it = it;
        }
    }
    return min_it;
}

template<typename Iterator>
Iterator max_element(Iterator first, Iterator last) {
    if (first == last) return last;
    
    Iterator max_it = first;
    for (auto it = std::next(first); it != last; ++it) {
        if (*max_it < *it) {
            max_it = it;
        }
    }
    return max_it;
}

template<typename Iterator, typename Compare>
Iterator max_element(Iterator first, Iterator last, Compare comp) {
    if (first == last) return last;
    
    Iterator max_it = first;
    for (auto it = std::next(first); it != last; ++it) {
        if (comp(*max_it, *it)) {
            max_it = it;
        }
    }
    return max_it;
}

// Binary search implementation
template<typename Iterator, typename T>
bool binary_search(Iterator first, Iterator last, const T& value) {
    auto it = std::lower_bound(first, last, value);
    return (it != last && !(value < *it));
}

template<typename Iterator, typename T, typename Compare>
bool binary_search(Iterator first, Iterator last, const T& value, Compare comp) {
    auto it = std::lower_bound(first, last, value, comp);
    return (it != last && !comp(value, *it));
}

template<typename Iterator, typename T>
Iterator lower_bound(Iterator first, Iterator last, const T& value) {
    auto count = std::distance(first, last);
    
    while (count > 0) {
        auto it = first;
        auto step = count / 2;
        std::advance(it, step);
        
        if (*it < value) {
            first = ++it;
            count -= step + 1;
        } else {
            count = step;
        }
    }
    
    return first;
}

template<typename Iterator, typename T, typename Compare>
Iterator lower_bound(Iterator first, Iterator last, const T& value, Compare comp) {
    auto count = std::distance(first, last);
    
    while (count > 0) {
        auto it = first;
        auto step = count / 2;
        std::advance(it, step);
        
        if (comp(*it, value)) {
            first = ++it;
            count -= step + 1;
        } else {
            count = step;
        }
    }
    
    return first;
}

template<typename Iterator, typename T>
Iterator upper_bound(Iterator first, Iterator last, const T& value) {
    auto count = std::distance(first, last);
    
    while (count > 0) {
        auto it = first;
        auto step = count / 2;
        std::advance(it, step);
        
        if (!(value < *it)) {
            first = ++it;
            count -= step + 1;
        } else {
            count = step;
        }
    }
    
    return first;
}

template<typename Iterator, typename T, typename Compare>
Iterator upper_bound(Iterator first, Iterator last, const T& value, Compare comp) {
    auto count = std::distance(first, last);
    
    while (count > 0) {
        auto it = first;
        auto step = count / 2;
        std::advance(it, step);
        
        if (!comp(value, *it)) {
            first = ++it;
            count -= step + 1;
        } else {
            count = step;
        }
    }
    
    return first;
}

} // namespace mini_stl

#endif // MINI_STL_ALGORITHM_H
