#include "FileManager.h"
FileManager* FileManager::pInstance = NULL;

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

bool FileManager::writeScore(std::string* ptrInput)
{
	std::fstream handler;
	handler.open("ExtraFiles/score.txt", std::ios::app);
	if (!handler.is_open())
	{
		return false;
	}
	handler << Player::PlayerInstance()->getScore() << ";" << *ptrInput;
	handler << "\n";
	return true;
}

bool FileManager::scoreComp(std::vector<ScoreUser>* ptrVectScores)
{
	std::fstream handler;
	std::string text;
	handler.open("ExtraFiles/score.txt", std::ios::in);
	if (!handler.is_open())
	{
		return false;
	}
	else
	{
		while (std::getline(handler, text))
		{
			if (text == "" || text.length() < 2)
			{
				continue;
			}
			int stopPos = text.find(";");
			std::string score = text.substr(0, stopPos);
			std::string user = text.substr(stopPos + 1, text.length());
			ptrVectScores->push_back({ std::stoi(score),user });			//stoi = String to int
		}
		for (int i = 1; i < (int)ptrVectScores->size(); i++) //Sorts Vect of structs by taking to account _score and performins Bubble Sort
		{
			for (int j = 0; j < (int)ptrVectScores->size() - i; j++)
			{
				if ((ptrVectScores->at(j)._score < ptrVectScores->at(j + 1)._score))
				{
					ScoreUser tempScore = ptrVectScores->at(j);
					ptrVectScores->at(j) = ptrVectScores->at(j + 1);
					ptrVectScores->at(j + 1) = tempScore;
				}
			}
		}
		handler.close();
	}
	return true;
}

FileManager* FileManager::getInstance()
{
	if (pInstance == NULL)
		pInstance = new FileManager();

	return pInstance;
}
