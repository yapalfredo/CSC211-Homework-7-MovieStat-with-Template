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