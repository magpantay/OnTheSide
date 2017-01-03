#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

void title();
void gettingInput();
void inputGot(string currentInput);
void play();
void outOfTurns(bool pantsOff);
void die (bool pantsOff);
void fart(bool isSoft, bool sittingOnToilet, bool pantsOff);
void poop(bool sittingOnToilet, bool pantsOff);
void checkForMastery();
void listAchievements();
void gameOver();
void quitGame();
void quitFromPrompt();
string stringToLower(string word);

/* Achievements variables */

bool a_play = false;
bool a_poopAtStart = false;
bool a_success = false;
bool a_success2 = false;
bool a_poopPants = false;
bool a_soClose = false;
bool a_oopsIFarted = false;
bool a_sepooku = false;
bool a_outOfTurns = false;
bool a_master = false;

/* end achievements */

int main ()
{
  title();
}

void title()
{
  cout << "Don't Poop Your Pants: The Horror Game About Not Pooping Your Pants" << endl;
  cout << "Type play to start" << endl;
  gettingInput();
}

void gettingInput()
{
  string currentInput = "";
  cout << "> ";
  getline (cin, currentInput);
  currentInput = stringToLower(currentInput);
  inputGot(currentInput);
}

void inputGot(string currentInput)
{
  if (!currentInput.compare("play"))
  {
    if (!a_play)
    {
      a_play = true;
      cout << "ACHIEVEMENT UNLOCKED: Realization" << endl;
    }
    play();
  }
  else if (!currentInput.compare("poop"))
  {
    cout << "The game hasn't even started yet and yet you have managed to poop your pants. I don't know what else to say." << endl;
    if (!a_poopAtStart)
    {
      a_poopAtStart = true;
      cout << "ACHIEVEMENT UNLOCKED: Off to a crappy start" << endl;
    }
    checkForMastery();
  }
  else if (!currentInput.compare("quit") || !currentInput.compare("exit"))
  {
    quitFromPrompt();
  }
  else
  {
    cout << "Invalid choice. Try again" << endl;
    gettingInput();
  }
}

void play()
{
  int turnsLeft = 10;
  string currentInput = "";
  bool seeToilet = false;
  bool sittingOnToilet = false;
  bool pantsOff = false;
  bool alreadyFarted = false;
  cout << "You are near a bathroom, but need to poop." << endl;
  while (turnsLeft > 0)
  {
    cout << "> ";
    getline (cin, currentInput);
    currentInput = stringToLower(currentInput);

    if (!currentInput.compare("quit") || !currentInput.compare("exit"))
    {
      quitFromPrompt();
    }

    else if (!currentInput.compare("pull door") || !currentInput.compare("pull open door"))
    {
      cout << "You pull open the door to see the toilet." << endl;
      seeToilet = true;
      cout << --turnsLeft << " turns left." << endl;
      continue;
    }

    else if (((!currentInput.compare("fart softly")) || (!currentInput.compare("fart lightly"))) && !alreadyFarted)
    {
      cout << "You lightly let out some gas, relief!" << endl;
      alreadyFarted = true;
      cout << ++turnsLeft << " turns left." << endl;
      continue;
    }

    else if (!currentInput.compare("open door"))
    {
      cout << "You try to push the door open, but fail." << endl;
      cout << --turnsLeft << " turns left." << endl;
      continue;
    }

    else if ((!currentInput.compare("take off pants") || !currentInput.compare("take pants off")) && !sittingOnToilet && !pantsOff)
    {
      cout << "You take off your pants." << endl;
      pantsOff = true;
      cout << --turnsLeft << " turns left." << endl;
      continue;
    }

    else if ((!currentInput.compare("take off pants") || !currentInput.compare("take pants off")) && sittingOnToilet && !pantsOff)
    {
      cout << "You try to take off your pants while sitting on the toilet, but are failing." << endl;
      cout << --turnsLeft << " turns left." << endl;
      continue;
    }

    else if ((!currentInput.compare("take off pants") || !currentInput.compare("take pants off")) && pantsOff)
    {
      cout << "Your pants are already off." << endl;
      cout << --turnsLeft << " turns left." << endl;
      continue;
    }

    else if ((!currentInput.compare("stand up") || !currentInput.compare("stand")) && !sittingOnToilet)
    {
      cout << "You're already standing." << endl;
      cout << --turnsLeft << " turns left." << endl;
      continue;
    }

    else if ((!currentInput.compare("stand up") || !currentInput.compare("stand")) && sittingOnToilet)
    {
      cout << "You get up from the toilet." << endl;
      sittingOnToilet = false;
      cout << --turnsLeft << " turns left." << endl;
      continue;
    }

    else if ((!currentInput.compare("sit on toilet") || !currentInput.compare("sit")) && seeToilet)
    {
      cout << "You sat on the toilet." << endl;
      sittingOnToilet = true;
      cout << --turnsLeft << " turns left." << endl;
      continue;
    }

    else if ((!currentInput.compare("sit on toilet") || !currentInput.compare("sit"))  && !seeToilet)
    {
      cout << "I think you're getting ahead of yourself." << endl;
      cout << --turnsLeft << " turns left." << endl;
      continue;
    }

    else if (!currentInput.compare("fart"))
    {
      fart(false, sittingOnToilet, pantsOff);
    }

    else if (((!currentInput.compare("fart softly")) || (!currentInput.compare("fart lightly"))) && alreadyFarted)
    {
      fart(true, sittingOnToilet, pantsOff);
    }

    else if (!currentInput.compare("poop"))
    {
      poop(sittingOnToilet, pantsOff);
    }

    else if (!currentInput.compare("die"))
    {
      if (!a_sepooku)
      {
        a_sepooku = true;
        cout << "ACHIEVEMENT UNLOCKED: Ending it all" << endl;
      }
      die(pantsOff);
    }

    else
    {
      cout << "I don't know how to " << currentInput << "." << endl;
      cout << --turnsLeft << " turns left." << endl;
      continue;
    }
  }
  if (!a_outOfTurns)
  {
    a_outOfTurns = true;
    cout << "ACHIEVEMENT UNLOCKED: ERROR 404" << endl;
  }
  outOfTurns(pantsOff);
}

void die(bool pantsOff)
{
  if (!pantsOff)
  {
    cout << "You died. But not before you feel yourself pooping your pants." << endl;
    checkForMastery();
  }

  else
  {
    cout << "You died. But you didn't poop your pants, so I guess that's a victory?" << endl;
    checkForMastery();
  }
}

void poop(bool sittingOnToilet, bool pantsOff)
{
  if (!sittingOnToilet && !pantsOff)
  {
    if (!a_poopPants)
    {
      a_poopPants = true;
      cout << "ACHIEVEMENT UNLOCKED: Failure" << endl; //poop your pants
    }
    cout << "You pooped your pants." << endl;
    checkForMastery();
  }

  else if (!sittingOnToilet && pantsOff)
  {
    if (!a_success)
    {
      a_success = true;
      cout << "ACHIEVEMENT UNLOCKED: Don't Poop Your Pants" << endl;
    }
    cout << "You pooped on the floor, but I guess that's a victory since you didn't poop your pants!" << endl;
    checkForMastery();
  }

  else if (sittingOnToilet && !pantsOff)
  {
    if (!a_soClose)
    {
      a_soClose = true;
      cout << "ACHIEVEMENT UNLOCKED: So close..." << endl;
    }
    cout << "You were so close, but yet so far. You forgot to remove your pants before pooping. Whoops." << endl;
    checkForMastery();
  }

  else
  {
    if (!a_success)
    {
      a_success = true;
      cout << "ACHIEVEMENT UNLOCKED: Don't Poop Your Pants" << endl;
    }

    if (!a_success2)
    {
      a_success2 = true;
      cout << "ACHIEVEMENT UNLOCKED: While in the correct place" << endl;
    }
    cout << "Hooray! Congratulations, you've successfully avoided pooping your pants!" << endl;
    checkForMastery();
  }
}

void outOfTurns(bool pantsOff)
{
  if (pantsOff)
  {
    cout << "You've run out of turns to try to save yourself, but your pants were off. I guess that's a semi-win?" << endl;
    checkForMastery();
  }
  else
  {
    cout << "You've run out of turns to try to save yourself. You ended up pooping your pants." << endl;
    checkForMastery();
  }
}

void fart(bool isSoft, bool sittingOnToilet, bool pantsOff)
{
  if (isSoft)
  {
    if (pantsOff && sittingOnToilet)
    {

      cout << "You had already farted, so another fart made you end up pooping. But you still managed to correctly poop in the correct place." << endl;
      checkForMastery();
    }

    else if (pantsOff && !sittingOnToilet)
    {
      cout << "You had already farted, so another fart made you end up pooping. But at least your pants were off." << endl;
      checkForMastery();
    }

    else if (!pantsOff && sittingOnToilet)
    {
      if (!a_soClose)
      {
        a_soClose = true;
        cout << "ACHIEVEMENT UNLOCKED: So close..." << endl;
      }
      cout << "You had already farted, but ended up /almost/ doing what you were supposed to be doing. The only exception was that your pants were still on. Whoops." << endl;
      checkForMastery();
    }

    else
    {
      cout << "You had already farted, so another fart made you end up pooping your pants." << endl;
      checkForMastery();
    }
  }

  else
  {
    if (pantsOff && sittingOnToilet)
    {
      cout << "You pushed too hard, but ended up doing what you were supposed to be doing. And on the toilet too! Congrats." << endl;
      checkForMastery();
    }

    else if (pantsOff && !sittingOnToilet)
    {
      cout << "You pushed too hard, but ended up not pooping your pants. Hooray?" << endl;
      checkForMastery();
    }

    else if (!pantsOff && sittingOnToilet)
    {
      if (!a_soClose)
      {
        a_soClose = true;
        cout << "ACHIEVEMENT UNLOCKED: So close..." << endl;
      }
      cout << "You pushed too hard, and /almost/ ended up meeting your goal. The only problem was that your pants were still on. Try taking them off next time." << endl;
      checkForMastery();
    }

    else
    {
      if (!a_oopsIFarted)
      {
        a_oopsIFarted = true;
        cout << "ACHIEVEMENT UNLOCKED: Too hard of a push" << endl;
      }
      cout << "You pushed too hard, and ended up pooping your pants." << endl;
      checkForMastery();
    }
  }
}

void checkForMastery()
{
  if (a_play && a_poopAtStart && a_success && a_success2 && a_poopPants && a_soClose && a_oopsIFarted && a_sepooku && a_outOfTurns)
  {
    a_master = true;
    cout << endl << "ACHIEVEMENT UNLOCKED: Pooping Mastery" << endl;
  }
  listAchievements();
}

void listAchievements()
{
  cout << endl << "Press enter key to continue...";
  cin.ignore();

  cout << endl;

  cout << "Achievements:" << endl;

  a_play ? cout << "[UNLOCKED] \tRealization: Realize that you're playing a game about preventing yourself from pooping your pants." << endl : cout << "\t\tRealization: ???" << endl;

  a_poopAtStart ? cout << "[UNLOCKED] \tOff to a crappy start: The game didn't even start..." << endl : cout << "\t\tOff to a crappy start: ???" << endl;

  a_success ? cout << "[UNLOCKED] " : cout << "\t";
  cout << "\tDon't Poop Your Pants: Successfully prevent yourself from pooping your pants." << endl;

  a_success2 ? cout << "[UNLOCKED] " : cout << "\t";
  cout << "\tWhile in the correct place: Self-descriptive achievement is self-descriptive." << endl;

  a_poopPants ? cout << "[UNLOCKED] " : cout << "\t";
  cout << "\tFailure: Pooped your pants." << endl;

  a_soClose ? cout << "[UNLOCKED] " : cout << "\t";
  cout << "\tSo close...: ...but yet so far." << endl;

  a_oopsIFarted ? cout << "[UNLOCKED] " : cout << "\t";
  cout << "\tToo hard of a push: Applying less pressure should help the next time around." << endl;

  a_sepooku ? cout << "[UNLOCKED] " : cout << "\t";
  cout << "\tEnding it all: Was it really necessary to do this to avoid the embarassment?" << endl;

  a_outOfTurns ? cout << "[UNLOCKED] \tERROR 404: Brain power not found" << endl : cout << "\t\tERROR 404: ???" << endl;

  a_master ? cout << "[UNLOCKED] \tPooping Mastery: You are truly a pooping master." << endl : cout << "\t\tSecret Achievement: ???" << endl;

  cout << endl;
  gameOver();
}

void gameOver()
{
  cout << "Game over." << endl;
  quitGame();
}

void quitGame()
{
  char choice = 'N';
  cout << "Play again? (Y/N): ";
  cin >> choice;

  if (choice == 'Y' || choice == 'y')
  {
    cin.ignore();
    cout << "\n\n";
    title();
  }
  else if (choice == 'N' || choice == 'n')
  {
    cout << "If you exit, you will lose your achievements. Are you certain? (Y/N): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y')
    {
      exit(0);
    }
    else if (choice == 'N' || choice == 'n')
    {
      quitGame();
    }
    else
    {
      cout << "Invalid choice. Try again." << endl;
      quitGame();
    }
  }
  else
  {
    cout << "Invalid choice. Try again." << endl;
    quitGame();
  }
}

void quitFromPrompt()
{
  char choice = 'N';
  cout << "If you exit, you will lose your achievements. Are you certain? (Y/N): ";
  cin >> choice;
  if (choice == 'Y' || choice == 'y')
  {
    exit(0);
  }
  else if (choice == 'N' || choice == 'n')
  {
    cin.ignore();
    cout << "\n\n";
    title();
  }
  else
  {
    cout << "Invalid choice. Try again." << endl;
    quitFromPrompt();
  }
}

string stringToLower(string word)
{
	transform(word.begin(), word.end(), word.begin(), ::tolower);
	return word;
}
