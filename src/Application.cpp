/**
 * File:        Appication.cpp
 *
 * Author:      Mandy Noto
 * Semester:    Fall 2021
 * Course:      CSC340
 *
 * Summary of File:
 *  This file allows clients to read an interactive dictionary.
 */

#include "Dictionary.h"
#include "InteractiveDictionary.h"

/**
 * @brief Use the interactive dictionary.
 */
int main() {
  InteractiveDictionary InteractiveDictionary;
  InteractiveDictionary.read();

  return 0;
}
