/**
 * File:        InteractiveDictionary.cpp
 *
 * Author:      Mandy Noto
 * Semester:    Fall 2021
 * Course:      CSC340
 *
 * Summary of File:
 *  This file contains implemented methods and properties
 *  necessary to print entries from user-inputted
 *  words that can optionally be sorted and filtered
 *  from data in its base class, DictionaryData.
 */

#include "InteractiveDictionary.h"
#include "Dictionary.h"

using std::cin;
using std::cout;
using std::deque;
using std::istream_iterator;
using std::istringstream;
using std::map;
using std::ostringstream;
using std::sort;
using std::string;
using std::vector;

/**
 * @brief Serves the client.
 */
void InteractiveDictionary::read() {
  populateWithData();
  printIntroduction(uniqueKeywords, definitions);

  int searchCount{0};
  string searchQuery{};
  while (true) {
    ++searchCount;
    printSearchNumber(searchCount);

    getline(cin, searchQuery);

    vector<string> parsedSearchQuery = parseSearchQuery(searchQuery);

    if (!isValid(parsedSearchQuery.size())) {
      printManual();
      continue;
    }

    string entryWord = parsedSearchQuery.front();
    if (isQuit(entryWord)) {
      printThankYou();
      break;
    }
    if (isHelp(entryWord)) {
      printManual();
      continue;
    }
    if (!isValid(entryWord)) {
      printNotFound();
      printManual();
      continue;
    }

    vector<Entry> entries = entriesBatch.at(entryWord);

    modifyEntries(entries, parsedSearchQuery);

    printEntries(entries);

    continue;
  }
}

/**
 * @brief Modifies entries by filtering and sorting entries with given queries,
 *        and prints errors if the queries are not any of the modifiers.
 */
void InteractiveDictionary::modifyEntries(vector<Entry> &entries,
                                          vector<string> &parsedSearchQuery) {
  sortInOrder(entries);
  if (parsedSearchQuery.size() == 1) {
    return;
  }

  deque<string> errorModifierMessage{OFFSET, ERROR_PART_OF_SPEECH,
                                     ERROR_DISTINCT, ERROR_REVERSE};
  deque<string> modifiers{OFFSET, PART_OF_SPEECH, DISTINCT, REVERSE};
  for (int parameterIndex = 1; parameterIndex < parsedSearchQuery.size();
       parameterIndex++) {
    modifiers.pop_front();
    errorModifierMessage.pop_front();

    string parameter = parsedSearchQuery.at(parameterIndex);
    int parameterNumber = parameterIndex + 1;
    if (!isAvailableModifier(modifiers, parameter, parameterNumber)) {
      printParameterErrors(errorModifierMessage, parameter, parameterNumber);
      continue;
    }
    if (parameter == REVERSE) {
      sortInReverseOrder(entries);
    } else if (parameter == DISTINCT) {
      filterByDistinctEntries(entries);
    } else if (isPartOfSpeech(parameter)) {
      if (!entriesHavePartOfSpeech(entries, parameter)) {
        entries.front().exists = false;
        continue;
      }
      filterByPartOfSpeech(entries, parameter);
    }
  }
}

/** ---START:----- MODIFY ENTRIES - FILTER/SORTING HELPER METHODS ------------*/

/**
 * @brief Sorts the specified entries in alphabetical order,
 *        first by part of speech then by definition.
 */
void InteractiveDictionary::sortInOrder(vector<Entry> &entries) {
  sort(entries.begin(), entries.end(), [](Entry &s1, Entry &s2) {
    return ((s1.partOfSpeech + s1.definition) <
            (s2.partOfSpeech + s2.definition));
  });
}

/**
 * @brief Removes the entries' part of speech that doesn't match the
 *        specifed part of speech.
 */
void InteractiveDictionary::filterByPartOfSpeech(vector<Entry> &entries,
                                                 string &partOfSpeech) {
  for (int i = entries.size() - 1; i >= 0; i--) {
    if (!(entries.at(i).partOfSpeech == partOfSpeech)) {
      entries.erase(entries.begin() + i);
    }
  }
}

/**
 * @brief Gets rid of duplicate entries.
 */
void InteractiveDictionary::filterByDistinctEntries(vector<Entry> &entries) {
  map<string, int> visitedEntry;

  for (int i = entries.size() - 1; i >= 0; i--) {
    if (visitedEntry.find(entries.at(i).toString()) != visitedEntry.end()) {
      entries.erase(entries.begin() + i);
    }
    visitedEntry[entries.at(i).toString()] = 1;
  }
}

/**
 * @brief Sorts the specified entries in reverse-alphabetical order,
 *        first by part of speech then by definition.
 */
void InteractiveDictionary::sortInReverseOrder(vector<Entry> &entries) {
  sort(entries.begin(), entries.end(), [](Entry &s1, Entry &s2) {
    return ((s1.partOfSpeech + s1.definition) >
            (s2.partOfSpeech + s2.definition));
  });
}

/** ---END:------- MODIFY ENTRIES - FILTER/SORTING HELPER METHODS --- -*/

/** ---START:----- READ - PARSING HELPER METHODS ---------------------*/

/**
 * @brief Returns a string vector out of the search query's white-space
 *        separated values.
 */
vector<string> InteractiveDictionary::parseSearchQuery(string &seachQuery) {
  vector<string> tokens = getTokens(seachQuery);

  for (string &token : tokens) {
    lowerCaseAllLettersOf(token);
  }

  if (!tokens.empty()) {
    capitalizeFirstLetterOf(tokens.front());
  }

  return tokens;
}

/**
 * @brief Returns true if the specified parameter is a search query that
 *        can be used to filter or sort entries.
 */
bool InteractiveDictionary::isAvailableModifier(deque<string> &modifiers,
                                                string &parameter,
                                                int &parameterNumber) {
  for (string modifier : modifiers) {
    if (parameter == modifier) {
      return true;
    }
  }

  if (parameterNumber == 2) {
    return isPartOfSpeech(parameter);
  }

  return false;
}

bool InteractiveDictionary::entriesHavePartOfSpeech(vector<Entry> &entries,
                                                    string &partOfSpeech) {
  for (Entry entry : entries) {
    if (entry.partOfSpeech == partOfSpeech) {
      return true;
    }
  }

  return false;
}

bool InteractiveDictionary::isPartOfSpeech(string &parameter) {
  return (partOfSpeechMap.find(parameter) != partOfSpeechMap.end());
}

/**
 * @brief Creates vector elements out of the specified search query's
 *        white-space separated elements
 */
vector<string> InteractiveDictionary::getTokens(string &searchQuery) {
  istringstream iss(searchQuery);
  vector<string> tokens{istream_iterator<string>{iss},
                        istream_iterator<string>{}};
  return tokens;
}

bool InteractiveDictionary::isHelp(string &entryWord) {
  return entryWord == "!help";
}

/**
 * @brief Returns true if the entry word exists in this dictionary.
 */
bool InteractiveDictionary::isValid(string &entryWord) {
  return (entriesBatch.find(entryWord) != entriesBatch.end());
}

/**
 * @brief Returns true if the number of search queries is 1, 2, 3, or 4.
 */
bool InteractiveDictionary::isValid(size_t searchQuerySize) {
  return (searchQuerySize > 0 && searchQuerySize < 5);
}

bool InteractiveDictionary::isQuit(string &entryWord) {
  return (entryWord == "!q");
}

/**
 * @brief Returns what a number's given position is in a series,
 *        for example: 1 is 1st, 2 is 2nd, etc.
 */
string InteractiveDictionary::getOrdinalNumber(int &number) {
  return ordinalNumberMap.at(number);
}

/** ---END:------ READ - PARSING HELPER METHODS ---------------------*/

/** ---START:---- READ - PRINTING HELPER METHODS ------------------- **/

/**
 * @brief Prints the position of the incorrect search query the user typed
 *        in trying to modify entries, with help in what they should have been.
 */
void InteractiveDictionary::printParameterErrors(deque<string> &modifiers,
                                                 string &parameter,
                                                 int &parameterNumber) {
  ostringstream oss;
  string ordinalNumber{getOrdinalNumber(parameterNumber)};
  cout << "       |\n";
  int orTimes = modifiers.size();

  for (string modifier : modifiers) {
    cout << "        <The entered " << ordinalNumber << " parameter "
         << "'" << parameter << "' is NOT " << modifier << ".>\n";

    oss << modifier << ((orTimes-- > 1) ? " or " : "");
  }
  cout << "        <The entered " << ordinalNumber << " parameter "
       << "'" << parameter << "' was disregarded.>\n";
  cout << "        <The " << ordinalNumber << " parameter should be "
       << oss.str() << ".>\n";
  cout << "       |\n";
}

/**
 * @brief Prints the contents of the specified entries if it exists,
 *        otherwise tells user that it wasn't found and
 *        how to use this dictionary.
 */
void InteractiveDictionary::printEntries(vector<Entry> &entries) {
  if (!entries.front().exists) {
    printNotFound();
    printManual();
    return;
  }

  cout << "       |\n";
  ostringstream oss;
  for (Entry entry : entries) {
    cout << entry.toString() << "\n";
  }
  cout << "       |\n";
}

void InteractiveDictionary::printIntroduction(int &keyWords, int &definitions) {
  cout << "====== DICTIONARY 340 C++ =====\n";
  cout << "------ Keywords: " << keyWords << "\n";
  cout << "------ Definitions: " << definitions << "\n\n";
}

void InteractiveDictionary::printManual() {
  cout << "       |\n";
  cout << "        PARAMETER HOW-TO,  please enter:\n";
  cout << "        1. A search key -then 2. An optional part of speech -then\n";
  cout << "        3. An optional 'distinct' -then 4. An optional 'reverse'\n";
  cout << "       |\n";
}

void InteractiveDictionary::printSearchNumber(int &searchCount) {
  cout << "Search [" << searchCount << "]: ";
}

void InteractiveDictionary::printNotFound() {
  cout << "       |\n";
  cout << "        <NOT FOUND> To be considered for the next release. Thank "
          "you.\n";
  cout << "       |\n";
}

void InteractiveDictionary::printThankYou() {
  cout << "\n-----THANK YOU-----\n";
}

/** ---END:---- READ - PRINTING HELPER METHODS ------------------- **/
