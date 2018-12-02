#include "MovieStat.h"

int main()
{

	MovieStat<int> mv;
	ofstream outFile;

	try
	{
		outFile.open("Homework6p2-2-2.txt");
		mv.loadScreen(outFile);
		outFile.close();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

	system("Pause");
	return 0;
}