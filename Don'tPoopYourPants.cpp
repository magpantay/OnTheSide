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
void gameOver();
string stringToLower(string word);

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
    play();
  }
  else if (!currentInput.compare("poop"))
  {
    cout << "The game hasn't even started yet and yet you have managed to poop your pants. I don't know what else to say." << endl;
    gameOver();
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

    if (!currentInput.compare("pull door") || !currentInput.compare("pull open door"))
    {
      cout << "You pull open the door to see the toilet." << endl;
      seeToilet = true;
      cout << --turnsLeft << " turns left." << endl;
      continue;
    }

    else if (!currentInput.compare("fart softly") && !alreadyFarted)
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

    else if (!currentInput.compare("fart softly") && alreadyFarted)
    {
      fart(true, sittingOnToilet, pantsOff);
    }

    else if (!currentInput.compare("poop"))
    {
      poop(sittingOnToilet, pantsOff);
    }

    else if (!currentInput.compare("die"))
    {
      die(pantsOff);
    }

    else
    {
      cout << "I don't know how to " << currentInput << "." << endl;
      cout << --turnsLeft << " turns left." << endl;
      continue;
    }
  }
  outOfTurns(pantsOff);
}

void die(bool pantsOff)
{
  if (!pantsOff)
  {
    cout << "You died. But not before you feel yourself pooping your pants." << endl;
    gameOver();
  }

  else
  {
    cout << "You died. But you didn't poop your pants, so I guess that's a victory?" << endl;
    gameOver();
  }
}

void poop(bool sittingOnToilet, bool pantsOff)
{
  if (!sittingOnToilet && !pantsOff)
  {
    cout << "You pooped your pants." << endl;
    gameOver();
  }

  else if (!sittingOnToilet && pantsOff)
  {
    cout << "You pooped on the floor, but I guess that's a victory since you didn't poop your pants!" << endl;
    gameOver();
  }

  else if (sittingOnToilet && !pantsOff)
  {
    cout << "You were so close, but yet so far. You forgot to remove your pants before pooping. Whoops." << endl;
    gameOver();
  }

  else
  {
    cout << "Hooray! Congratulations, you've successfully avoided pooping your pants!" << endl;
    gameOver();
  }
}

void outOfTurns(bool pantsOff)
{
  if (pantsOff)
  {
    cout << "You've run out of turns to try to save yourself, but your pants were off. I guess that's a semi-win?" << endl;
    gameOver();
  }
  else
  {
    cout << "You've run out of turns to try to save yourself. You ended up pooping your pants." << endl;
    gameOver();
  }
}

void fart(bool isSoft, bool sittingOnToilet, bool pantsOff)
{
  if (isSoft)
  {
    if (pantsOff && sittingOnToilet)
    {
      cout << "You had already farted, so another fart made you end up pooping. But you still managed to correctly poop in the correct place." << endl;
      gameOver();
    }

    else if (pantsOff && !sittingOnToilet)
    {
      cout << "You had already farted, so another fart made you end up pooping. But at least your pants were off." << endl;
      gameOver();
    }

    else if (!pantsOff && sittingOnToilet)
    {
      cout << "You had already farted, but ended up /almost/ doing what you were supposed to be doing. The only exception was that your pants were still on. Whoops." << endl;
      gameOver();
    }

    else
    {
      cout << "You had already farted, so another fart made you end up pooping your pants." << endl;
      gameOver();
    }
  }

  else
  {
    if (pantsOff && sittingOnToilet)
    {
      cout << "You pushed too hard, but ended up doing what you were supposed to be doing. And on the toilet too! Congrats." << endl;
      gameOver();
    }

    else if (pantsOff && !sittingOnToilet)
    {
      cout << "You pushed too hard, but ended up not pooping your pants. Hooray?" << endl;
      gameOver();
    }

    else if (!pantsOff && sittingOnToilet)
    {
      cout << "You pushed too hard, and /almost/ ended up meeting your goal. The only problem was that your pants were still on. Try taking them off next time." << endl;
      gameOver();
    }

    else
    {
      cout << "You pushed too hard, and ended up pooping your pants." << endl;
      gameOver();
    }
  }
}

void gameOver()
{
  char choice = 'N';
  cout << "Game over." << endl;
  cout << "Play again? (Y/N): ";
  cin >> choice;

  if (choice == 'Y' || choice == 'y')
  {
    cin.ignore();
    cout << "\n\n";
    title();
  }
  else
  {
    exit(0);
  }
}

string stringToLower(string word)
{
	transform(word.begin(), word.end(), word.begin(), ::tolower);
	return word;
}
