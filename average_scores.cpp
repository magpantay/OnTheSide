#include <iostream>
#include <string>
using namespace std;

int main()
{
	int competitors = 0;
	cout << "Number of competitors: ";
	cin >> competitors;
	string * competitorNames = new string[competitors];

	cin.ignore(); //so getline will work

	for (int i = 0; i < competitors; i++)
	{
		cout << "Enter the name of competitor #" << (i+1) << ": ";
		getline (cin, competitorNames[i]);
	}

	int numberOfElements = 0;
	cout << "Enter number of reviews: ";
	cin >> numberOfElements;

 	double **elements;
	// Allocate memory
  	elements = new double * [competitors];

  	for (int i = 0; i < competitors; i++)
	{
   		elements[i] = new double[numberOfElements];
	}

	for (int i = 0; i < competitors; i++)
	{
		for (int j = 0; j < numberOfElements; j++)
		{
			cout << "Enter score " << j+1 << " for competitor '" << competitorNames[i] << "': ";
			cin >> elements[i][j];
		}
		cout << endl;
	}

	double * minimum = new double[competitors];
	double * maximum = new double[competitors];
	double absMax = elements[0][0];
	double absMin = elements[0][0];
	int absMaxLoc = 0;
	int absMinLoc = 0;
	int absMaxComp = 0;
	int absMinComp = 0;

	for (int i = 0; i < competitors; i++)
	{
		minimum[i] = elements[i][0];
		maximum[i] = elements[i][0];
		for (int j = 0; j < numberOfElements; j++)
		{
			if (elements[i][j] < absMin)
			{
				absMin = elements[i][j];
				absMinLoc = j;
				absMinComp = i;
			}
			if (elements[i][j] > absMax)
			{
				absMax = elements[i][j];
				absMaxLoc = j;
				absMinComp = i;
			}
			if (elements[i][j] < minimum[i])
			{
				minimum[i] = elements[i][j];
			}
			if (maximum[i] < elements[i][j])
			{
				maximum[i] = elements[i][j];
			}
		}
	}
	double * sums = new double[numberOfElements];
	double * average = new double[competitors];
	for (int i = 0; i < competitors; i++)
	{
		for (int j = 0; j < numberOfElements; j++)
		{
			sums[i] += elements[i][j];
		}
	}

	for (int i = 0; i < competitors; i++)
	{
		average[i] = (sums[i]/numberOfElements);
	}

	cout << "Absolute maximum was " << absMax << " from competitor '" << competitorNames[absMaxComp] << "' at " << absMaxLoc << endl;
	cout << "Absolute minimum was " << absMin << " from competitor '" << competitorNames[absMinComp] << "' at " << absMinLoc << endl;
	cout << endl;
	
	for (int i = 0; i < competitors; i++)
	{
		cout << "Competitor '" << competitorNames[i] << "': " << endl;
		cout << "Minimum: " << minimum[i] << endl;
		cout << "Maximum: "<< maximum[i] << endl;
		cout << "Average score: " << average[i] << endl;
		cout << endl;
	}

	delete [] minimum;
	delete [] maximum;
	delete [] competitorNames;
	for (int i = 0; i < competitors; i++)
	{
		delete [] elements[i];
	}
	delete [] elements;

	return 0;
}