#include "Model.hpp"
#include "Apollo.hpp"
#include "Core.hpp"
#include <iostream>
#include <list>
using namespace std;

int main()
{
	cout << "Creating Map ...";
	CreateMap();
	cout << " Done!" << endl;

Start:

	// input state
	int8 State[StateLen];
	cout << "State (6 blocks): ";
	for (int i = 0; i < StateLen; i++)
	{
		int state;
		cin >> state;
		State[i] = state;
	}
	if (Map[Convert(State)] == -1 || Found(State)) goto Start;

	// solve
	int8 nStep = Search(State);
	cout << "nStep: " << (int)nStep << endl;
	list<list<int8>>::iterator itri = Solu.begin();
	for (int i = 0; i < Solu.size(); i++)
	{
		printf("Solu%3d: ", i);
		list<int8>::iterator itrj = (*itri).begin();
		for (int j = 1; j <= nStep; j++)
		{
			cout << (int)*itrj << ' ';
			itrj++;
		}
		itri++;
		cout << endl;
	}
	cout << endl;

	goto Start;

	system("pause");
}