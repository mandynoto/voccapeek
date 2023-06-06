/**
 * File:    CycleVector.cpp
 *
 * Author:      Mandy Noto
 * Semester:    Fall 2021
 * Course:      CSC340
 *
 * Summary of File:
 *  This file contains implemented methods and properties
 *  that allow strings to be cycled (visited) over and over again.
 */

#include "CycleVector.h"

using std::string;
/**
 * @brief Constructs an empty cycle vector.
 */
CycleVector::CycleVector() {}

/**
 * @brief Constructs this cycle vector with two items.
 */
CycleVector::CycleVector(string &s1, string &s2) {
  container.push_back(s1);
  container.push_back(s2);
  size = container.size();
}

/**
 * @brief Constructs this cycle vector with three items.
 */
CycleVector::CycleVector(const string &s1, const string &s2, const string &s3) {
  container.push_back(s1);
  container.push_back(s2);
  container.push_back(s3);
  size = container.size();
}

/**
 * @brief Returns the item after the current one then cycles.
 */
string &CycleVector::cycle() {
  index += 1;
  cycles += 1;
  if (index == size) {
    index = 0;
  }
  return container.at(index);
}

/**
 * @brief Returns the item that this cycle vector is in at t this time.
 */
string &CycleVector::check() {
  return (index == 0) ? container.at(0) : container.at(index);
}

/**
 * @brief Returns how many cycles this vector has undergone.
 */
int CycleVector::getCycles() { return cycles; }

/**
 * @brief Adds a new item to this cycle vector
 */
void CycleVector::push(string s) { container.push_back(s); };

/**
 * @brief Makes the current item the first item, and sets the
 *        cycles to 0.
 */
void CycleVector::reset() {
  index = 0;
  cycles = 0;
}
