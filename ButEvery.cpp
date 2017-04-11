#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
   bool checkCase(char letter)
   {
        return (letter >= 'A' && letter <= 'Z');
   }

   void changeCase(char & letter)
   {
        letter = (letter + 'A');
   }
 */

void removeSpaces(string & fileOutName)
{
        for (int i = 0; i < fileOutName.length(); i++)
        {
                if (fileOutName[i] == ' ') { fileOutName[i] = '_'; }
        }
}

bool checkExtension(string filename)
{
        return (filename.substr(filename.length()-4, 4) == ".txt");
}

void outsideFile(string filename, string & finalProduct)
{
        ifstream IRWFN; //Is Replaced With File Name
        string buffer;
        IRWFN.open(filename.c_str());

        finalProduct = "";
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
        //bool firstLetterIsUpper = false;
        int counter = 0;
        int CI_letter_traversal = 0;
        int BE_traversal = 0;
        char currentLetterInInput, currentLetterInButEvery; //so it doesn't create an instance of these variables with every loop
        for (int CI_word_traversal = 0; CI_word_traversal < currentInput.size(); CI_word_traversal++)
        {
                if (currentInput[CI_word_traversal].length() < butEvery.length()) { continue; }//pointless to run current iteration, as the length of butEvery exceeds length of input string
                else if (currentInput[CI_word_traversal] == butEvery)
                {
                        currentInput[CI_word_traversal] = isReplacedWith;
                        counter++;
                        continue;
                }
                else
                {
                        while (CI_letter_traversal <= currentInput[CI_word_traversal].length()) //while it's not the end of currentInput[CI_word_traversal]
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
                                //currentLetterIsUpper = checkCase(currentInput[CI_word_traversal][CI_letter_traversal]);

                                currentLetterInInput = tolower(currentInput[CI_word_traversal][CI_letter_traversal]);
                                currentLetterInButEvery = tolower(butEvery[BE_traversal]); //lowercase each letter to check if each word matches, even with variances

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
                        //currentLetterIsUpper = false;
                }
        }
        return counter;
}

void output(vector <string> & inputs, string filename)
{
        ofstream fileOut;
        fileOut.open(filename.c_str());
        for (int i = 0; i < inputs.size(); i++)
        {
                fileOut << inputs[i]; //might as well output to file as well, needs endl here since '\n' doesn't translate well into text files
                cout << inputs[i]; //no need for endl here, since there are '\n' in the string vector
        }
        fileOut << endl;
        cout << endl;
        fileOut.close();
}

bool checkIfFileExists(string file)
{
        bool ret_val = false;
        ifstream in;
        in.open(file.c_str());
        ret_val = in;
        in.close();
        return ret_val;
}

bool prompts_and_inputs(string & filename, string & except, string & replaced, bool commandLine)
{
        if (commandLine)
        {
                if (!(checkIfFileExists(filename))) { throw 4; }
                else if (!(checkExtension(filename))) { throw 5; }
                else
                {
                        if (checkIfFileExists(replaced))
                        {
                                if (!(checkExtension(replaced))) { throw 5; }
                                return true;
                        }
                        else if (!(checkIfFileExists(replaced)) && checkExtension(replaced)) { throw 6; } //the file ends in a .txt, but it does not exist
                        else { return false; }
                }
        }

        else
        {
                cout << "Enter the first file for input: ";
                getline(cin, filename);

                if (!(checkIfFileExists(filename))) { throw 1; }
                else if (!(checkExtension(filename))) { throw 3; }
                else
                {
                        cout << "Enter the phrase you want to replace: ";
                        getline(cin, except);

                        cout << "Enter the phrase or second file that you want to replace \"" << except << "\" with: ";
                        getline(cin, replaced);

                        if (checkIfFileExists(replaced))
                        {
                                if (!(checkExtension(replaced))) { throw 3; }
                                return true;
                        }
                        else if (!(checkIfFileExists(replaced)) && checkExtension(replaced)) { throw 2; }//the file ends in a .txt, but it does not exist
                        else { return false; }
                }
        }
}

int main (int argc, char * argv[])
{
        string fileInName = "", fileOutName = "", butEvery = "", isReplacedWith = "";
        bool replacedIsAFile = false, commandLineArguments = false;

        if (argc > 1 && (argc < 4 || argc > 4))
        {
                cout << "This is not enough or too many arguments!" << endl;
                cout << "Correct usage is: " << argv[0] << " \"[FILENAME]\" \"[CHOICE OF WORD(S) TO REPLACE]\" \"[CHOICE OF WORD(S)/FILENAME TO REPLACE THIS WITH]\"" << endl;
                return 1;
        }

        if (argc == 4)
        {
                fileInName = argv[1];
                butEvery = argv[2];
                isReplacedWith = argv[3];
                commandLineArguments = true;
        }

        int retry_count_1 = 0 /*used for exception 1*/, retry_count_2 = 0; /*used for exception 2 */
        bool success = false;
        while (!success && (retry_count_1 <= 3 && retry_count_2 <= 3)) //if the user enters a wrong file, it will try again three times.
        {
                try
                {
                        replacedIsAFile = prompts_and_inputs(fileInName, butEvery, isReplacedWith, commandLineArguments);
                        success = true;
                }

                catch(int exception)
                {
                        if (exception == 1)
                        {
                                retry_count_1++;
                                if (retry_count_1 < 3)
                                {
                                        cout << "WARNING " << exception << "." << retry_count_1 << ": Non-existent file! Try again.\n";
                                }

                                else
                                {
                                        cout << "ERROR: " << exception << ": Non-existent file!" << endl;
                                        return exception;
                                }
                        }
                        else if (exception == 2)
                        {
                                retry_count_2++;
                                if (retry_count_2 < 3)
                                {
                                        cout << "WARNING " << exception << "." << retry_count_2 << ": You seem to want a file input, but the file does not exist. Try again.\n";
                                }
                                else
                                {
                                        cout << "ERROR: " << exception << ": You seem to want a file input, but the file does not exist!\n";
                                        return exception;
                                }
                        }
                        else if (exception == 3) //no idea why I skipped 2
                        {
                                cout << "ERROR " << exception << ": Filetype not supported. Accepted file types are: .txt" << endl;
                                return exception;
                        }
                        else if (exception >= 4 && exception <= 6)
                        {
                                cout << "ERROR " << exception << ": Command line arugment #" << (exception-3) << " invalid!" << endl;
                                return exception;
                        }
                        else
                        {
                                cout << "ERROR " << exception << ": UNKNOWN ERROR" << endl;
                                return exception;
                        }
                }
        }

        if (replacedIsAFile)
        {
                string isReplacedWithFN = isReplacedWith; //since isReplacedWith contains the filename
                isReplacedWith = ""; //blank out the string
                outsideFile(isReplacedWithFN, isReplacedWith);

                fileOutName = fileInName.substr(0, fileInName.length()-4) + "_only_every_" + butEvery + "_is_replaced_with_" + isReplacedWithFN.substr(0, isReplacedWithFN.length()-4) + ".txt";
                removeSpaces(fileOutName); //removes the spaces, replaces them with underscores
                //necessary to create a substring to remove the extension (assuming it is a three character extension)
        }

        ifstream fileIn;
        fileIn.open(fileInName.c_str());

        vector <string> currentInput; //because dynamically allocated string arrays couldn't cut it

        string buffer;

        while (!(fileIn.eof()))
        {
                getline(fileIn, buffer);
                currentInput.push_back(buffer);
                currentInput.push_back("\n");
        } //gets all of the words from the file

        fileIn.close(); //no need for the file anymore

        int match_count = matching(currentInput, butEvery, isReplacedWith);

        if (!replacedIsAFile)
        {
                fileOutName = fileInName.substr(0, fileInName.length()-4) + "_only_every_" + butEvery + "_is_replaced_with_" + isReplacedWith + ".txt";
                removeSpaces(fileOutName); //removes any spaces, leaves underscores instead
                //necessary to create a substring to remove the extension (assuming it is a three character extension)
        }

        output(currentInput, fileOutName);

        cout << "There were a total of " << match_count << " \"" << butEvery << "\" found in " << fileInName << endl;

        return 0;
}
