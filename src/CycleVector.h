/**
 * File:    CycleVector.h
 *
 * Author:      Mandy Noto
 * Semester:    Fall 2021
 * Course:      CSC340
 *
 * Summary of File:
 *  This file contains to-be-implemented methods and properties
 *  that allow strings to be cycled (visited) over and over again.
 */

#ifndef CYCLEVECTOR_H
#define CYCLEVECTOR_H

#include <string>
#include <vector>

/**
 * @brief   A container that  Implements the vector standard container
 *          which allows cycling of strings elements.
 */
class CycleVector {
public:
  CycleVector();
  CycleVector(std::string &s1, std::string &s2);
  CycleVector(const std::string &s1, const std::string &s2,
              const std::string &s3);

  std::string &cycle();
  std::string &check();

  int getCycles();

  void push(std::string s);
  void reset();

private:
  std::vector<std::string> container;
  int size;
  int cycles = 0;
  int index = 0;
};

#endif // CycleArray.h
