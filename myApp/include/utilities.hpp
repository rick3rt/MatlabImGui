/**
 * @file utilities.hpp
 * @author Rick Waasdorp (r.waasdorp@tudelft.nl)
 * @brief
 * @version 0.1
 * @date 2022-11-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef UTILITIES_HPP_
#define UTILITIES_HPP_

#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <numeric>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

// Fill the zipped vector with pairs consisting of the
// corresponding elements of a and b. (This assumes
// that the vectors have equal length)
template <typename A, typename B>
void zip(const std::vector<A> &a, const std::vector<B> &b, std::vector<std::pair<A, B>> &zipped)
{
    for (size_t i = 0; i < a.size(); ++i)
    {
        zipped.push_back(std::make_pair(a[i], b[i]));
    }
}

// Write the first and second element of the pairs in
// the given zipped vector into a and b. (This assumes
// that the vectors have equal length)
template <typename A, typename B>
void unzip(const std::vector<std::pair<A, B>> &zipped, std::vector<A> &a, std::vector<B> &b)
{
    for (size_t i = 0; i < a.size(); i++)
    {
        a[i] = zipped[i].first;
        b[i] = zipped[i].second;
    }
}

/**
 * @brief sort vector x and y, by sorting x in ascending order. See:
 * https://stackoverflow.com/questions/37368787/c-sort-one-vector-based-on-another-one
 *
 * @param x xdata
 * @param y ydata
 */
template <typename A, typename B>
void sort_by_x(std::vector<A> &x, std::vector<B> &y)
{
    // Zip the vectors together
    std::vector<std::pair<B, A>> zipped;
    zip(y, x, zipped);
    // Sort the vector of pairs
    std::sort(std::begin(zipped), std::end(zipped),
              [&](const auto &a, const auto &b) { return a.second > b.second; });
    // Write the sorted pairs back to the original vectors
    unzip(zipped, y, x);
}

/**
 * @brief Fixed size stack, for undo history. Inspired by:
 * https://stackoverflow.com/questions/56334492/c-create-fixed-size-queue
 *
 * @tparam T
 * @tparam MaxLen
 */
template <typename T, int MaxLen>
class UndoStack
{
  private:
    std::deque<T> d;

  public:
    void push(const T &value)
    {
        if (this->d.size() == MaxLen) { this->d.pop_front(); }
        d.push_back(value);
    }
    T pop()
    {
        T tmp = this->d.back();
        this->d.pop_back();
        return tmp;
    }
    size_t size() { return this->d.size(); }
};

#endif //! UTILITIES_HPP_
