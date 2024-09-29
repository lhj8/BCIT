#include "../include/MergeSort.h"


/**
 * @brief Sorts the elements in the vector 'arr' using the merge sort algorithm.
 *
 * This function starts the merge sort process by dividing the input vector into
 * two halves, sorting each half recursively, and then merging the sorted halves
 * into a fully sorted vector.
 *
 * @param arr Reference to a vector of elements to be sorted.
 */
template<typename T>
void MergeSort<T>::sort(std::vector<T> &arr) {
    size_t arrSize = arr.size();
    size_t arrSizeMid = arrSize / 2;

    if (arrSize < 2) return;

    std::vector<T> left(arr.begin(), arr.begin() + arrSizeMid);
    std::vector<T> right(arr.begin() + arrSizeMid, arr.begin() + arrSize);

    sort(left);  // Recursively sort the left part
    sort(right); // Recursively sort the right part

    merge(arr, left, right);
}


/**
 * @brief Merges two sorted subvectors into a single sorted vector.
 *
 * This helper function is used during the merge sort process. It takes two sorted
 * subvectors ('left' and 'right') and merges them into a single sorted vector by
 * comparing the elements of each and inserting the smaller element into the 'arr'.
 *
 * @param arr Reference to the vector where the merged result is stored.
 * @param left The left subvector to be merged.
 * @param right The right subvector to be merged.
 */
template<typename T>
void MergeSort<T>::merge(std::vector<T> &arr, const std::vector<T> &left, const std::vector<T> &right) {
    size_t leftIndex = 0, rightIndex = 0, mergeIndex = 0;

    // Merge the two vectors until one is empty
    while (leftIndex < left.size() && rightIndex < right.size()) {
        if (compare(left[leftIndex], right[rightIndex])) {
            arr[mergeIndex++] = left[leftIndex++];
        } else {
            arr[mergeIndex++] = right[rightIndex++];
        }
    }

    // Copy any remaining elements from the left vector
    while (leftIndex < left.size()) {
        arr[mergeIndex++] = left[leftIndex++];
    }

    // Copy any remaining elements from the right vector
    while (rightIndex < right.size()) {
        arr[mergeIndex++] = right[rightIndex++];
    }
}
