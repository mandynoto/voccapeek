/**
 * File:        Dictionary.h
 *
 * Author:      Mandy Noto
 * Semester:    Fall 2021
 * Course:      CSC340
 *
 * Summary of File:
 *  This file contains to-be-implemented methods and properties
 *  for data to be stored and utilized by its derived class,
 *  InteractiveDictionary.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "CycleVector.h"

class Dictionary {
public:
  void populateWithData();

protected:
  int uniqueKeywords{0};
  int definitions{0};

  struct Entry {
    std::string word;
    std::string partOfSpeech;
    std::string definition;
    bool exists;

    std::string toString() {
      return "        " + word + " [" + partOfSpeech + "] : " + definition;
    }
  };

  std::map<std::string, std::vector<Entry>> entriesBatch;

  void eraseCarriageReturnsOf(std::string &content);
  void eraseLeadingAndTrailingWhiteSpacesOf(std::string &);
  void capitalizeFirstLetterOf(std::string &);
  void capitalizeAllLettersOf(std::string &);
  void lowerCaseAllLettersOf(std::string &word);
  void lowerCaseFirstLetterOf(std::string &word);

private:
  std::string DEFAULT_FILE_PATH{
      "C:\\Users\\MickeyMouse\\AbsolutePath\\DB\\Data.CS.SFSU.txt"};
  std::string PRE_DEFINITION_DELIMITER{"-=>>"};
  std::string PRE_PART_OF_SPEECH_DELIMITER{"|"};

  void loadData(std::string);
  void openDataFile(std::ifstream &, std::string &);

  void printOpeningDataFile(std::string &);
  void printLoadedDataPrompt(std::string &);
  void printFileOpenError(std::string &);
  void printRequestForCorrectFilePath();

  void parseData(std::ifstream &, std::map<std::string, std::vector<Entry>> &);
  void makeNewEntry(std::map<std::string, std::vector<Entry>> &,
                    std::string &word, std::string &partOfSpeech,
                    std::string &definition);
  void standardizeDefinition(std::string &definition);

  void standardizeWord(std::string &word); /** TODO: */

  bool hasDelimiter(std::string &, std::string &);
  bool shoudlOnlyHaveOnePeriod(std::string &); /** TODO: */

  std::vector<std::string> words;
  std::vector<std::map<std::string, std::string>> definition;

  std::string getDefinitionPartOf(std::string &content, std::string &delimiter);
  std::string getWordPartOf(std::string &content, std::string &delimiter);
  std::string getPartOfSpeechPartOf(std::string &content,
                                    std::string delimiter);
};

#endif // DICTIONARY_H
