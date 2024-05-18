#pragma once
#include <vector>


enum Wave_kind
{
	Wave_Endless,
	Wave_Normal
};
typedef int Wavekind;





class Wave
{
	Wavekind wavekind;
public:
	Wave()
	{

	}
};


class WaveManager
{
std::vector<Wave> waves;
public:



};
