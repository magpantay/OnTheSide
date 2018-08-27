#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class pokemon
{
    public:
    bool doesHave;
    int dexNum;
    string pokemonName;
    int amountInv;

    string specialRemarks;

    pokemon()
    {
        doesHave = false;
        dexNum = 0;
        pokemonName = " ";
        amountInv = 0;
        specialRemarks = "none";
    }

    pokemon(int dexNum, string pokemonName)
    {
        this->doesHave = false;
        this->dexNum = dexNum;
        this->pokemonName = pokemonName;
        this->amountInv = 0;
        this->specialRemarks = "none";
    }

    ~pokemon() { }
};

void destroyVector(vector<pokemon*>&mons)
{
    while (!mons.empty())
    {
        delete mons.back();
        mons.pop_back();
    }
}

int main()
{
    vector <pokemon*> mons;
    ifstream inFile;

    string temp_pokemonName = " ";
    int temp_dexNum = 0;

    inFile.open("pokemon.txt");
    while (!inFile.eof())
    {
        inFile >> temp_dexNum >> temp_pokemonName;
        pokemon * temp_poke = new pokemon (temp_dexNum, temp_pokemonName);
        mons.push_back(temp_poke);
    }
    inFile.close();

    char answer = 'N';
    string answer2 = "none";

    for (int i = 0; i < mons.size(); i++)
    {
        cout << mons[i]->dexNum << " - " << mons[i]->pokemonName << " (Y/N): ";
        cin >> answer;

        if (answer == 'Y' || answer == 'y')
        {
            mons[i]->doesHave = true;
            cout << "How many?: ";
            cin >> mons[i]->amountInv;
            cout << "Special Remarks?: ";
            cin >> answer2;
            if (answer2 != "no" || answer2 != "NO" || answer2 != "n" || answer2 != "N") mons[i]->specialRemarks = answer2;
        }
    }

    ofstream outFile;
    outFile.open("inventory.csv");
    outFile << "Number,Name,Owned,Amount,Remarks" << endl;
    for (int i = 0; i < mons.size(); i++)
    {
        outFile << mons[i]->dexNum << "," << mons[i]->pokemonName << ",";

        if (mons[i]->doesHave) outFile << "y,";
        else outFile << "n,";

        outFile << mons[i]->amountInv << "," << mons[i]->specialRemarks << endl;
    }

    outFile.close();

    destroyVector(mons);
}
