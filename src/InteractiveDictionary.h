/**
 * File:    InteractiveDictionary.h
 *
 * Author:      Mandy Noto
 * Semester:    Fall 2021
 * Course:      CSC340
 *
 * Summary of File:
 *  This file contains to-be-implmeented methods and properties
 *  necessary to print entries from user-inputted
 *  words that can optionally be sorted and filtered
 *  from data in its base class, DictionaryData.
 */

#ifndef INTERACTIVEDICTIONARY_H
#define INTERACTIVEDICTIONARY_H

#include "Dictionary.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

class InteractiveDictionary : public Dictionary {
public:
  void read();

private:
  const std::string OFFSET{""};

  const std::string ERROR_PART_OF_SPEECH{"a part of speech"};
  const std::string ERROR_DISTINCT{"'distinct'"};
  const std::string ERROR_REVERSE{"'reverse'"};

  const std::string PART_OF_SPEECH{"partOfSpeech"};
  const std::string DISTINCT = {"distinct"};
  const std::string REVERSE = {"reverse"};

  void modifyEntries(std::vector<Entry> &, std::vector<std::string> &);

  void sortInOrder(std::vector<Entry> &);
  void sortInReverseOrder(std::vector<Entry> &);

  void filterByDistinctDefinitions(std::vector<Entry> &);
  void filterByDistinctEntries(std::vector<Entry> &);
  void filterByPartOfSpeech(std::vector<Entry> &, std::string &);

  void printIntroduction(int &, int &);
  void printSearchNumber(int &);
  void printManual();
  void printThankYou();
  void printNotFound();
  void printParameterErrors(std::deque<std::string> &modifiers,
                            std::string &parameter, int &parameterNumber);
  void printEntries(std::vector<Entry> &);

  bool isValid(std::size_t searchQueryCount);
  bool isValid(std::string &entryWord);
  bool isHelp(std::string &);
  bool isQuit(std::string &);
  bool isAvailableModifier(std::deque<std::string> &modifiers,
                           std::string &parameter, int &parameterNumber);
  bool isPartOfSpeech(std::string &);
  bool entriesHavePartOfSpeech(std::vector<Entry> &, std::string &);

  std::vector<std::string> getTokens(std::string &content);
  std::vector<std::string> parseSearchQuery(std::string &content);
  std::string getOrdinalNumber(int &);

  std::map<std::string, std::string> partOfSpeechMap{
      {"adjective", {PART_OF_SPEECH}},    {"adverb", {PART_OF_SPEECH}},
      {"noun", {PART_OF_SPEECH}},         {"conjuction", {PART_OF_SPEECH}},
      {"interjection", {PART_OF_SPEECH}}, {"preposition", {PART_OF_SPEECH}},
      {"pronoun", {PART_OF_SPEECH}},      {"verb", {PART_OF_SPEECH}}};

  std::map<int, std::string> ordinalNumberMap{
      {1, {"1st"}}, {2, {"2nd"}}, {3, {"3rd"}}, {4, {"4th"}}};
};

#endif // INTERACTIVEDICTIONARY_H
