#include "../include/RadixSort.h"


/**
 * Computes the base 10 logarithm of a number.
 * @param x The number to compute the log for.
 * @return The logarithm base 10 of x.
 */
inline double logBase10(double x) {
    return log(x) / log(10);
}


/**
 * Calculates 10 raised to the power of 'n'.
 * @param n The power to which 10 is raised.
 * @return The result of 10^n.
 */
inline int powerOfTen(int n) {
    int result = 1;
    for (int i = 0; i < n; ++i) {
        result *= 10;
    }
    return result;
}


/**
 * Sorts the elements using the Radix Sort algorithm.
 */
template<typename T>
void RadixSort<T>::sort() {
    int maxDigitCount = getMaxDigitCount();

    // Do counting sort for every digit. Note that instead of passing digit number,
    // the exponent is passed. exp is 10^i where i is current digit number
    for (int digit = 0; digit < maxDigitCount; digit++) {
        countingSort(digit);
    }
}


/**
 * Determines the maximum number of digits in any element.
 * @return The maximum number of digits found.
 */
template<typename T>
int RadixSort<T>::getMaxDigitCount() {
    int maxDigits = 0;

    for (const T& element : elements_) {
        int currentDigits = getDigitCount(getKeyFunction_(element));
        if (currentDigits > maxDigits) {
            maxDigits = currentDigits;
        }
    }
    return maxDigits;
}


/**
 * Counts the number of digits in an integer.
 * @param number The integer to count digits of.
 * @return The number of digits in 'number'.
 */
template<typename T>
int RadixSort<T>::getDigitCount(int number) {
    if (number == 0) return 1;
    return (int)(logBase10(number) + 1);
}


/**
 * Performs counting sort on the digits at the specified place value.
 * @param digit The current digit index to perform the counting sort on.
 */
template<typename T>
void RadixSort<T>::countingSort(int digit) {
    std::vector<T> output(elements_.size());
    std::vector<int> count(10, 0);

    // Store the count of occurrences of each digit
    for (const T& element : elements_) {
        int digitValue = getDigitValue(getKeyFunction_(element), digit);
        count[digitValue]++;
    }

    // Change count[i] so that it now contains the actual
    // position of this digit in the output array
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = elements_.size() - 1; i >= 0; i--) {
        int digitValue = getDigitValue(getKeyFunction_(elements_[i]), digit);
        output[count[digitValue] - 1] = elements_[i];
        count[digitValue]--;
    }

    // Copy the output array to elements_, so that elements_ now
    // contains sorted numbers according to the current digit
    auto it = elements_.begin();
    for (const auto& item : output) {
        *it = item;
        ++it;
    }
}


/**
 * Retrieves the value of the digit at the specified place value in 'number'.
 * @param number The number to extract the digit from.
 * @param digit The digit's place value index.
 * @return The digit at the specified place value in 'number'.
 */
template<typename T>
int RadixSort<T>::getDigitValue(int number, int digit) {
    return (number / powerOfTen(digit)) % 10;
}
