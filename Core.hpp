#pragma once

#include "Model.hpp"
#include "Apollo.hpp"
#include <ctime>
#include <iostream>
#include <list>
#include <ctime>
using namespace std;

int8 GodBranch[GodNum + 1][StateLen];
int8 GodGene[GodNum + 1];

list<list<int8>> Solu;

bool God(int8 Depth)
{
	bool isFound = false;
	int8 ptr = 0;
	do
	{
		if (ptr < Depth)
		{
			bool remain = false;
			for (int8 gene = GodGene[ptr + 1] + 1; gene < nGene; gene++)
			{
				if (isAllow(gene, GodGene[ptr]))
				{
					Transform(GodBranch[ptr], gene, GodBranch[ptr + 1]);
					if (ptr + 1 + Map[Convert(GodBranch[ptr + 1])] > GodNum) 
						continue; // A*
					remain = true;
					ptr++;
					GodGene[ptr] = gene;
					break;
				}
			}
			if (!remain)
			{
				GodGene[ptr + 1] = -1;
				ptr--;
				if (ptr == -1) return isFound;
			}
		}
		else
		{
			if (Found(GodBranch[ptr]))
			{
				isFound = true;
				list<int8> solu;
				for (int8 i = 0; i < Depth; i++)
					solu.push_back(GodGene[i + 1]);
				Solu.push_back(solu);
			}
			ptr--;
		}
	} while (true);
}

int8 Search(int8 State[StateLen])
{
	// INITIALIZE
	GodGene[0] = nGene;
	for (int8 i = 1; i < GodNum + 1; i++)
		GodGene[i] = -1;
	for (int8 i = 0; i < StateLen; i++)
		GodBranch[0][i] = State[i];
	Solu.clear();

	// SEARCH
	clock_t start_t, end_t;
	start_t = clock();
	int8 StartDepth = Map[Convert(State)]; // A*
	for (int8 Depth = StartDepth; Depth <= GodNum; Depth++)
	{
		if (God(Depth))
		{
			end_t = clock();
			cout << "time: " << end_t - start_t << "ms" << endl;
			return Depth;
		}
	}
	return -1;
}