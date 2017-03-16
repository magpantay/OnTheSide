#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void outsideFile(string filename, string & finalProduct)
{
  ifstream IRWFN; //Is Replaced With File Name
  string buffer;
  IRWFN.open(filename.c_str());

  if (!IRWFN)
  {
    throw "Non-existent file! Try again.\n";
  }

  while (!(IRWFN.eof()))
  {
    getline(IRWFN, buffer);
    finalProduct += buffer;
    finalProduct += "\n";
  }
  IRWFN.close();
}

int matching (vector <string> & currentInput, string & butEvery, string & isReplacedWith)
{
  int counter = 0;
  int CI_letter_traversal = 0;
  int BE_traversal = 0;
  for (int CI_word_traversal = 0; CI_word_traversal < currentInput.size(); CI_word_traversal++)
  {
      if (currentInput[CI_word_traversal].length() < butEvery.length())
      {
          continue; //pointless to run current iteration, as the length of butEvery exceeds length of input string
      }
      if (currentInput[CI_word_traversal] == butEvery)
      {
        currentInput[CI_word_traversal] = isReplacedWith;
        counter++;
        continue;
      }
      while (CI_letter_traversal < currentInput[CI_word_traversal].length()) //while it's not the end of currentInput[CI_word_traversal]
      {
            if (BE_traversal == butEvery.length()) //if the BE traversal variable matches the length of the butEvery string
            {
                counter++; //counting matches

                string complete;
                string substring_before = currentInput[CI_word_traversal].substr(0,CI_letter_traversal-butEvery.length());
                string substring_after = currentInput[CI_word_traversal].substr(CI_letter_traversal, currentInput[CI_word_traversal].length()-CI_letter_traversal-1);

                complete.append(substring_before);
                complete.append(isReplacedWith);
                complete.append(substring_after);

                currentInput[CI_word_traversal] = complete;
                break;
                //make substring from 0 to before all of the characters matched
                //make a string of the isReplacedWith replace last butEvery.length() characters with isReplacedWith
                //make a string of the rest of the characters after the match (thus removing the match)
                //append substring1 and isReplacedWith
                //append that with substring2
            }

            char currentLetterInInput = tolower(currentInput[CI_word_traversal][CI_letter_traversal]);
            char currentLetterInButEvery = tolower(butEvery[BE_traversal]); //lowercase each letter to check if each word matches, even with variances

            if (currentLetterInInput == currentLetterInButEvery) //basic character matching
            {
                CI_letter_traversal++; //next character in currentInput[][]
                BE_traversal++; //next character in butEvery
            }
            else
            {
                BE_traversal = 0; //start over butEvery again
                CI_letter_traversal++; //but continue traversing currentInput[][]
            }
      }
      CI_letter_traversal = 0; // reset for next iteration
      BE_traversal = 0; //reset for next iteration
  }
  return counter;
}

void output(vector <string> & inputs, string filename)
{
  ofstream fileOut;
  fileOut.open(filename.c_str());
  for (int i = 0; i < inputs.size(); i++)
  {
      fileOut << inputs[i] << endl; //might as well output to file as well, needs endl here since '\n' doesn't translate well into text files
      cout << inputs[i]; //no need for endl here, since there are '\n' in the string vector
  }
  fileOut << endl;
  cout << endl;
  fileOut.close();
}

void prompts_and_inputs(string & filename, string & except, string & replaced, bool & isAFile)
{
  cout << "Enter the file for input: ";
  getline(cin, filename);

  ifstream fileIn;
  fileIn.open(filename.c_str()); //need to convert it into a C string to have a variable open a file
  if (!fileIn) //check if file is possible to open
  {
    throw "Non-existent file! Try again.\n";
  }

  cout << "Enter the phrase you want to replace: ";
  getline(cin, except);

  cout << "Enter the phrase you want to replace \"" << except << "\" with (Enter \"FILENAME\" for file): ";
  getline(cin, replaced);

  if (replaced == "FILENAME")
  {
      isAFile = true;
  }

  fileIn.close();
}

int main ()
{
  string fileInName = "";
  string fileOutName = "";
  string butEvery = "";
  string isReplacedWith = "";
  bool replacedIsAFile = false;

  int retry_count = 0;
  bool success = false;
  while (!success && retry_count <= 3) //if the user enters a wrong file, it will try again three times.
  {
    try
    {
        prompts_and_inputs(fileInName, butEvery, isReplacedWith, replacedIsAFile);
        success = true;
    }

    catch(const char * exception)
    {
        retry_count++;
        if (retry_count < 3)
        {
            cout << exception;
        }

        else
        {
            cout << "Non-existent file!" << endl;
            return 1;
        }
    }
  }

  if (replacedIsAFile)
  {
      string isReplacedWithFN;
      success = false;
      retry_count = 0;
      while (!success && retry_count <= 3) //if the user enters a wrong file, it will try agian three times.
      {
        try
        {
            cout << "What is the text file name?: ";
            getline(cin, isReplacedWithFN);
            outsideFile(isReplacedWithFN, isReplacedWith);
            success = true;
        }

        catch(const char * exception)
        {
            retry_count++;
            if (retry_count < 3)
            {
                cout << exception;
            }

            else
            {
                cout << "Non-existent file!" << endl;
                return 1;
            }
        }
      }
      fileOutName = fileInName.substr(0, fileInName.length()-4) + "_only_every_" + butEvery + "_is_replaced_with_" + isReplacedWithFN.substr(0, isReplacedWithFN.length()-4) + ".txt";
      //necessary to create a substring to remove the extension (assuming it is a three character extension)
  }

  ifstream fileIn;
  fileIn.open(fileInName.c_str());

  vector <string> currentInput; //because dynamically allocated string arrays couldn't cut it

  string temp;

  while (!(fileIn.eof()))
  {
      getline(fileIn, temp);
      currentInput.push_back(temp);
      currentInput.push_back("\n");
  } //gets all of the words from the file

  fileIn.close(); //no need for the file anymore

  int match_count = matching(currentInput, butEvery, isReplacedWith);

  if (!replacedIsAFile)
  {
      fileOutName = fileInName.substr(0, fileInName.length()-4) + "_only_every_" + butEvery + "_is_replaced_with_" + isReplacedWith + ".txt";
      //necessary to create a substring to remove the extension (assuming it is a three character extension)
  }

  output(currentInput, fileOutName);

  cout << "There were a total of " << match_count << " \"" << butEvery << "\" found in " << fileInName << endl;

  return 0;
}
