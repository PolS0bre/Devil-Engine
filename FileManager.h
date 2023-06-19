#pragma once
#include <string>
#include "Player.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
class FileManager
{
public:
	FileManager();
	~FileManager();

	bool writeScore(std::string* ptrInput);
	bool scoreComp(std::vector <ScoreUser>* ptrVectScores);

	static FileManager* getInstance();
private:

	static FileManager* pInstance;
};

