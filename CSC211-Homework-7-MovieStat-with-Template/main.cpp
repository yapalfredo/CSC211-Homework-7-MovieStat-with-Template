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
		//DO NOTHING
	}

	system("Pause");
	return 0;
}