/**
 * File:        Dictionary.cpp
 *
 * Author:      Mandy Noto
 * Semester:    Fall 2021
 * Course:      CSC340
 *
 * Summary of File:
 *  This file contains implemented methods and properties
 *  for data to be stored and utilized by its derived class,
 *  InteractiveDictionary.
 */

#include "Dictionary.h"
#include "CycleVector.h"

using std::cin;
using std::cout;
using std::ifstream;
using std::ios;
using std::istringstream;
using std::map;
using std::ostringstream;
using std::smatch;
using std::string;
using std::stringstream;
using std::toupper;
using std::vector;

/**
 * @brief Populate this dictionary with entries (words, part of speeches,
 *        and definitions) from a file.
 */
void Dictionary::populateWithData() {
  loadData(DEFAULT_FILE_PATH);
  cin.ignore();
}

/**
 * @brief Loads entries (words, part of speeches, and definitions) into this
 *        dictionary from a file.
 */
void Dictionary::loadData(string filePath) {
  ifstream inFile;
  openDataFile(inFile, filePath);

  cout << "! Loading data..."
       << "\n";
  parseData(inFile, entriesBatch);

  printLoadedDataPrompt(filePath);
}

/**
 * @brief Understand and gets the word-part, part of speech-part,
 *        and definition-part of a file's content.
 */
void Dictionary::parseData(ifstream &inFile,
                           map<string, vector<Entry>> &entries) {
  CycleVector delimiter(PRE_PART_OF_SPEECH_DELIMITER, PRE_DEFINITION_DELIMITER);
  string lineContent;
  std::cout << "lineConente=" << lineContent << std::endl;
  while (getline(inFile, lineContent)) {
    eraseCarriageReturnsOf(lineContent);
    eraseLeadingAndTrailingWhiteSpacesOf(lineContent);
    istringstream iss{lineContent};
    string content;
    ;
    string word;
    string partOfSpeech;
    string definition;
    word = getWordPartOf(lineContent, PRE_PART_OF_SPEECH_DELIMITER);
    delimiter.reset();

    while (!iss.eof()) {
      string validDelimiter = delimiter.check();
      iss >> content;
      if (hasDelimiter(content, validDelimiter)) {
        if (validDelimiter == PRE_PART_OF_SPEECH_DELIMITER) {
          if (delimiter.getCycles() != 0) {
            definition += ' ' + getDefinitionPartOf(content, validDelimiter);
            eraseLeadingAndTrailingWhiteSpacesOf(definition);
            capitalizeFirstLetterOf(definition);
            makeNewEntry(entries, word, partOfSpeech, definition);
            definition.clear();
          }
          partOfSpeech = getPartOfSpeechPartOf(content, validDelimiter);
          validDelimiter = delimiter.cycle();
          continue;
        }
        if (content == PRE_DEFINITION_DELIMITER) {
          validDelimiter = delimiter.cycle();
          continue;
        }
      }
      definition += ' ' + content;
    }
    eraseLeadingAndTrailingWhiteSpacesOf(definition);
    makeNewEntry(entries, word, partOfSpeech, definition);
  }
  uniqueKeywords = entries.size();
  inFile.close();
}

/** ---START:------ LOAD HELPER METHODS ------------------------- */

void Dictionary::openDataFile(ifstream &inFile, string &path) {
  // Ask for a file path
  std::cout << "Please enter relative path to data file to load\n> ";
  cin >> path;
  inFile.open(path);
  while (!inFile.is_open()) {
    printOpeningDataFile(path);
    printFileOpenError(path);
    printRequestForCorrectFilePath();
    cin >> path;
    inFile.open(path);
  }
}

void Dictionary::printFileOpenError(string &path) {
  cout << "<!>ERROR<!> ===>" << ' ' << "File could not be opened."
       << "\n";
  cout << "<!>ERROR<!> ===>" << ' ' << "Provided file path:" << ' ' << path
       << "\n";
}

void Dictionary::printOpeningDataFile(string &path) {
  cout << "! Opening data file..." << ' ' << path << "\n";
}

void Dictionary::printLoadedDataPrompt(string &path) {
  cout << "! Loading completed..."
       << "\n";
  cout << "! Closing data file..." << ' ' << path << "\n\n";
}

void Dictionary::printRequestForCorrectFilePath() {
  cout << "<!>Enter the CORRECT data file path\n> ";
}

/** ---END:----   PARSE - LOAD HELPER METHODS ------------------------- */

/** ---START:---- PARSE - DATA HELPER METHODS ------------------------- */

/**
 * @brief Capitalizes all letters of a word that begins
 *        with csc.
 */
void Dictionary::standardizeWord(string &lineContent) {
  std::regex cscRegex("(^\\s*[cC][sS][cC])");
  lineContent = std::regex_replace(lineContent, cscRegex, "CSC");
}

/**
 * @brief Replaces the last part of a definition
 *        that has two periods with one period.
 */
void Dictionary::standardizeDefinition(string &definition) {
  std::regex twoPeriodsFromEndRegex("\\.\\.\\s*$");
  definition = std::regex_replace(definition, twoPeriodsFromEndRegex, ".");
}

/**
 * @brief Return true if a given string s1 has a delimiter s2.
 */
bool Dictionary::hasDelimiter(string &s1, string &s2) {
  return (s1.find(s2) != std::string::npos) ? true : false;
}

string Dictionary::getDefinitionPartOf(string &content, string &delimiter) {
  int delimiterIndex = content.find(delimiter);
  string word = content.substr(0, delimiterIndex);
  return word;
}

string Dictionary::getWordPartOf(string &content, string &delimiter) {
  int delimiterIndex = content.find(delimiter);
  string word = content.substr(0, delimiterIndex);
  capitalizeFirstLetterOf(word);
  return word;
}

string Dictionary::getPartOfSpeechPartOf(string &content, string delimiter) {
  int delimiterIndex = content.find(delimiter);
  string partOfSpeech = content.substr(delimiterIndex + 1, content.size());
  lowerCaseFirstLetterOf(partOfSpeech);
  return partOfSpeech;
}

void Dictionary::eraseCarriageReturnsOf(string &content) {
  content.erase(std::remove(content.begin(), content.end(), '\r'),
                content.end());
}

void Dictionary::eraseLeadingAndTrailingWhiteSpacesOf(string &content) {
  content = std::regex_replace(content, std::regex("^ +| +$|( ) +"), "$1");
}

void Dictionary::capitalizeFirstLetterOf(string &word) {
  word[0] = toupper(word[0]);
}

void Dictionary::capitalizeAllLettersOf(string &word) {
  for_each(word.begin(), word.end(), [](char &c) { c = ::toupper(c); });
}

void Dictionary::lowerCaseFirstLetterOf(string &word) {
  word[0] = tolower(word[0]);
}

void Dictionary::lowerCaseAllLettersOf(string &content) {
  std::for_each(content.begin(), content.end(),
                [](char &c) { c = ::tolower(c); });
}

/**
 * @brief Make a new Entry out of out of the given entries and word properties.
 *        Words and definitions are also standardized,that is, all entry words
 *        should be capitalized, and that image definitions should only
 *        end with one period.
 */
void Dictionary::makeNewEntry(map<string, vector<Entry>> &entriesBatch,
                              string &word, string &partOfSpeech,
                              string &definition) {
  definitions += 1;
  Entry newEntry = {word, partOfSpeech, definition, true};
  standardizeWord(newEntry.word);
  standardizeDefinition(newEntry.definition);
  if (!(entriesBatch.find(word) == entriesBatch.end())) {
    entriesBatch.find(word)->second.push_back(newEntry);
    return;
  }
  vector<Entry> emptyEntryVector{newEntry};
  entriesBatch[word] = emptyEntryVector;
}

/** ---END:---- PARSE - DATA HELPER METHODS ------------------------- */
