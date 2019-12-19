#pragma once

#include "Model.hpp"
#define nState 3674160

int8* Map;

int Convert(int8* State)
{
	int state = 0;
	int temp = 1;
	for (int8 i = 0; i < StateLen; i++)
	{
		state += State[i] * temp;
		temp *= 21;
	}
	return state;
}

void CreateMap()
{
	// INITIALIZE
	const int MapSize = 21 * 21 * 21 * 21 * 21 * 21;
	Map = new int8[MapSize];
	for (int i = 0; i < MapSize; i++)
		Map[i] = -1;
	int8** State = new int8*[nState + 1];
	for (int i = 0; i < nState + 1; i++)
		State[i] = new int8[StateLen];
	for (int8 i = 0; i < StateLen; i++)
		State[0][i] = JesusCube[i];
	Map[Convert(State[0])] = 0;

	// CREATE
	int head = 0, end = 0;
	int _end = end;
	for (int8 step = 1; step <= GodNum; step++)
	{
		for (int ptr = head; ptr <= end; ptr++)
		{
			for (int8 gene = 0; gene < nGene; gene++)
			{
				Transform(State[ptr], gene, State[_end + 1]);
				int state = Convert(State[_end + 1]);
				if (Map[state] == -1)
				{
					Map[state] = step;
					_end++;
				}
			}
		}
		head = end + 1; end = _end;
	}
}