#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

template <class T>
class MovieStat
{
private:
	T input, sum, max;
public:
	//CONSTRUCTOR
	MovieStat();
	//DESTRUCTOR
	~MovieStat();

	//GETTERS
	T getInput() const;	//GETS INPUT
	T getAverage(int) const;	// CALCULATES ANR RETURNS THE AVERAGE
	T getMedian(const T *, const int) const;	//CALCULATES MEDIAN
	T getSum() const;		//GETS SUM OF THE ARRAY
	T getMax() const;		//GETS LARGEST VALUE IN THE ARRAY

	//SETTERS
	void setInput(T);		//SETS INPUT FROM USER
	void setSum(T);		//SETS SUM VALUE OF ARRAY
	void setMax(const T *, const int);	//SETS LARGEST VALUE IN THE ARRAY
	void setMax(T);			//SETMAX OVERLOADING


	//ASK THE USER HOW MANY STUDENTS WERE SURVEYED.
	//AN ARRAY OF INTEGERS WITH THIS MANY ELEMENTS
	//SHOULD THEN BE DYNAMICALLY ALLOCATED.
	void questionA(ofstream&);


	//ALLOW THE USER TO ENTER THE NUMBER OF MOVIES
	//EACH STUDENT SAW INTO THE ARRAY.
	//CALCULATE AND DISPLAY THE AVERAGE, MEDIAN, AND
	//MODE OF THE VALUES ENTERED.
	void questionBandC(const int, ofstream&);

	//INPUT VALIDATION
	void inputValidation(char, T&, ofstream&);

	//DOES NOTHING ALMOST
	//ONLY TO LOAD THE FIRST QUESTION
	void loadScreen(ofstream&);

	//DISPLAYS ALL THE ELEMENTS IN THE ARRAY
	void displayArray(const T *, const int, ofstream&);

	//DISPLAYS THE MODE IN THE ARRAY
	void displayMode(const T *, const int, ofstream&);

	//A FUNCTION FOR CHECKING THE TEMP ARRAY IF A VALUE
	//HAS ALREADY BEEN COUNTED
	bool ifExists(const vector<T>, T);

	//THIS FUNCTION WILL BE USED FOR COMPARING THE INDEX OF AN ELEMENT
	//TO THE REST OF THE ELEMENT IF IT'S GREATER OR EQUAL.
	//IF TRUE, WILL TAKE THE CURRENT BOOL VARIABLE VALUE AND MULTIPLY TO TRUE
	//ELSE, TAKE CURRENT BOOL VARIABLE VALUE AND MULTIPLY TO FALSE
	bool ifGreaterOrEqual(const T, const T, bool&);
};



template <class T>
MovieStat<T>::MovieStat()
{
	//CONSTRUCTOR

	setMax(0);
}

template <class T>
MovieStat<T>::~MovieStat()
{
	//DESTRUCTOR
}

template <class T>
void MovieStat<T>::setInput(T input)
{
	//THIS FUNCTION SETS THE INPUT 
	//VARIABLE FROM THE USER
	this->input = input;
}

template <class T>
T MovieStat<T>::getInput() const
{
	//THIS FUNCTION RETURNS THE INPUT
	//TO THE USER
	return input;
}

template <class T>
void MovieStat<T>::setSum(T sum)
{
	//THIS FUNCTION SETS THE SUM
	//VARIABLE FROM THE ARRAY
	this->sum = sum;
}

template <class T>
T MovieStat<T>::getSum() const
{
	//THIS FUNCTION RETURNS THE SUM
	//VARIABLE VALUE FROM THE ARRAY
	return sum;
}

template <class T>
void MovieStat<T>::setMax(T max) {
	//THIS FUNCTIONS SETS THE MAX
	//VARIABLE. THIS COULD BE INITIALIZED
	//OR BE CALLED WHILE LOOKING FOR THE
	//LARGEST VALUE IN THE ARRAY
	this->max = max;
}

template <class T>
void MovieStat<T>::setMax(const T * movieArr, const int SIZE)
{
	//THIS FUNCTION WILL SET THE MAX VARIABLE VALUE
	//DEPENDING ON THE LARGEST VALUE OF THE ELEMENT
	//IN THE ARRAY
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (movieArr[i] > movieArr[j] && movieArr[i] > max)
			{
				setMax(movieArr[i]);
			}
			else if (movieArr[i] < movieArr[j] && movieArr[j] > max)
			{
				setMax(movieArr[j]);
			}
		}
	}
}

template <class T>
T MovieStat<T>::getMax() const
{
	//RETURNS THE MAX VARIABLE VALUE
	return max;
}

template <class T>
void MovieStat<T>::loadScreen(ofstream& outFile)
{
	//CALLS questionA()
	questionA(outFile);
}

template <class T>
void MovieStat<T>::questionA(ofstream& outFile)
{
	//FUNCTION CALLS INPUT VALIDATION
	outFile.seekp(outFile.tellp());
	inputValidation('A', input, outFile);

	setInput(input);
	const int SIZE = getInput();

	cout << endl;
	questionBandC(SIZE, outFile);
}

template <class T>
void MovieStat<T>::questionBandC(const int SIZE, ofstream& outFile)
{
	const char * c1 = "The average of the array is: ";
	const char * c2 = "The median of the array is: ";
	//FOR DYNAMIC ALLOCATION	
	int * movieArr = new int[SIZE];

	for (size_t i = 0; i < SIZE; i++)
	{
		outFile.seekp(outFile.tellp());
		cout << "For student " << i + 1 << ": ";
		outFile << "For student " << i + 1 << ": ";
		inputValidation('B', input, outFile);
		movieArr[i] = getInput();
	}

	cout << endl;
	displayArray(movieArr, SIZE, outFile);

	outFile.seekp(outFile.tellp());
	cout << endl << endl << c1 << getAverage(SIZE) << endl << endl;
	outFile << endl << endl << c1 << getAverage(SIZE) << endl << endl;
	cout << c2 << getMedian(movieArr, SIZE) << endl;
	outFile << c2 << getMedian(movieArr, SIZE) << endl;
	setMax(movieArr, SIZE);
	displayMode(movieArr, SIZE, outFile); cout << endl;

	delete movieArr;
	movieArr = nullptr;
}

template <class T>
void MovieStat<T>::inputValidation(char caseChar, T& input, ofstream& outFile)
{
	//THIS FUNCTION VALIDATIONS THE INPUT
	//IT WILL ONLY ACCEPT INPUTS GREATER THAN OR EQUAL TO ZERO

	const char * c1 = "How many students were surveyed?: ";
	const char * c2 = "Please enter the number of movies: ";
	do {
		switch (caseChar)
		{
		case 'A':	//QUESTION A
			cout << c1;
			cin >> input;
			outFile << c1 << input << endl << endl;
			break;
		case 'B':
			cout << c2;
			cin >> input;
			outFile << c2 << input << endl;
			break;
		default:
			break;
		}

		if (input <= 0)
		{
			cout << "Only positive integers are accepted. Please try again!" << endl;
		}
	} while (input <= 0);
}

template <class T>
void MovieStat<T>::displayArray(const T* movieArr, const int SIZE, ofstream& outFile)
{
	const char * c1 = "Your array of inputs are: ";
	//THIS FUNCTION DISPLAY THE VALUES IN THE ARRAY

	int sum = 0;	//THIS VARIABLE WILL HOLD
					//THE SUM OF THE ARRAY
	outFile.seekp(outFile.tellp());
	cout << c1;
	outFile << endl << c1;
	for (int i = 0; i < SIZE; i++)
	{
		cout << movieArr[i] << " ";
		outFile << movieArr[i] << " ";
		sum += movieArr[i];
	}

	setSum(sum);
}

template <class T>
T MovieStat<T>::getAverage(int SIZE) const
{
	//THIS FUNCTION CALCULATES THE AVERAGE VALUE OF THE ARRAY
	return ((double)getSum() / (double)SIZE);
}

template <class T>
T MovieStat<T>::getMedian(const T * movieArr, const int SIZE) const
{
	//THIS FUNCTION WILL GET THE MEDIAN IN THE ARRAY
	double result;
	int medianSize = SIZE / 2;

	if (SIZE % 2 == 0)
	{
		//IF THE SIZE OF THE ARRAY IS EVEN. GET THE TWO MIDDLE VALUES
		//AND COMPUTE THE AVERAGE
		result = (double)(movieArr[medianSize] + movieArr[medianSize - 1] / 2);
	}
	else if (SIZE % 2 == 1)
	{
		//ELSE, JUST GET THE MIDDLE ELEMENT
		result = movieArr[medianSize];
	}

	return result;
}

template <class T>
void MovieStat<T>::displayMode(const T* movieArr, const int SIZE, ofstream& outFile)
{
	const char * c1 = " occured ";
	const char * c2 = " times ";
	const char * c3 = " time ";
	const char * c4 = "The mode(s) is/are: ";

	outFile.seekp(outFile.tellp());
	//THIS FUNCTION WILL LOOK FOR AND DISPLAY THE MODE IN THE ARRAY
	vector<int> tempMovieArr(getMax(), 0);

	int counter = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (movieArr[i] == movieArr[j])
			{
				counter++;
			}
		}
		if (!ifExists(tempMovieArr, movieArr[i] - 1))
		{
			tempMovieArr.at(movieArr[i] - 1) = counter;
		}
		counter = 0;
	}
	cout << endl; outFile << endl;
	//////////////////////////////////////////////////////////////
	//DISPLAY THE OCCURENCE OF EACH GENERATED VALUE IN THE ARRAY
	for (int i = 0; i < tempMovieArr.size(); i++)
	{
		if (tempMovieArr.at(i) > 0)
		{
			cout << i + 1 << c1 << tempMovieArr.at(i);
			outFile << i + 1 << c1 << tempMovieArr.at(i);
			if (tempMovieArr.at(i) > 1)
			{
				cout << c2 << endl;
				outFile << c2 << endl;
			}
			else
			{
				cout << c3 << endl;
				outFile << c3 << endl;
			}
		}
	}
	//////////////////////////////////////////////////////////////
	//SET MODE(S)
	cout << endl << c4 << endl;
	outFile << endl << c4 << endl;
	bool greaterOrEqual;
	for (int i = 0; i < tempMovieArr.size(); i++)
	{
		greaterOrEqual = true;

		for (int j = 0; j < tempMovieArr.size(); j++)
		{
			ifGreaterOrEqual(tempMovieArr.at(i), tempMovieArr.at(j), greaterOrEqual);
		}

		if (!greaterOrEqual)
		{
			tempMovieArr.at(i) = 0;	//SET TO ZERO IF IT'S NOT A MODE
		}

		if (tempMovieArr.at(i) > 1) //WILL ONLY DISPLAY OCCURENCE GREATER THAN 1
		{
			cout << i + 1 << "    ";
			outFile << i + 1 << "    ";
		}
	}
	////////////////////////////////////////////////////////////////
	cout << endl;
	tempMovieArr.clear();
	tempMovieArr.resize(0);
}

template <class T>
bool MovieStat<T>::ifExists(const vector<T> tempMovieArr, T val)
{
	//THIS FUNCTION WILL RETURN TRUE IF THE NUMBER HAS ALREADY BEEN COUNTED
	//OR FALSE OTHERWISE
	bool result = false;

	if (tempMovieArr.at(val) <= 0)
	{
		result = false;
	}
	else
	{
		result = true;
	}
	return result;
}

template <class T>
bool MovieStat<T>::ifGreaterOrEqual(const T a, const T b, bool &greaterOrEqual)
{
	//THIS FUNCTION WILL BE USED TO DETERMINE THE MODE(S)
	//IT HAS 3 ARGUMENTS, BOTH INTS WILL BE COMPARED, THEN
	//SETS THE BOOL VARIABLE TO 'MULTIPLY EQUALS' DEPENDING
	//RESULT OF THE CONDITION. THEN IT WILL RETURN THAT BOOL
	//VARIABLE
	if (a >= b)
	{
		greaterOrEqual *= true;
	}
	else
	{
		greaterOrEqual *= false;
	}

	return greaterOrEqual;
}