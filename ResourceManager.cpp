#include "ResourceManager.h"

ResourceManager* ResourceManager::pInstance = NULL;

//DONE
ResourceManager::~ResourceManager()
{
	SDL_Quit();
}

//DONE
void ResourceManager::removeGraphic(const char* file)
{
	map<string, Sint32>::iterator it;
	int ID = -1;

	for (it = mIDMap.begin(); it != mIDMap.end(); it++)
	{
		if (it->first == file)
		{
			ID = it->second;
		}
	}
	if (ID != -1) {
		mIDMap.erase(file);
		SDL_DestroyTexture(mGraphicsVector.at(ID));
	}
}

//DONE
Sint32 ResourceManager::loadAndGetGraphicID(const char* file)
{
	map<string, Sint32>::iterator it;

	for (it = mIDMap.begin(); it != mIDMap.end(); it++)
	{
		if (it->first == file)
		{
			return it->second;
		}
	}
	return addGraphic(file);
}

//CHECK--!
string ResourceManager::getGraphicPathByID(Sint32 ID)
{
	map<string, Sint32>::iterator it;

	for (it = mIDMap.begin(); it != mIDMap.end(); it++)
	{
		if (it->second == ID)
		{
			return it->first;
		}
	}
	cout << "La imagen que buscas no esta disponible o no existe" << endl;
}

//DONE
void ResourceManager::getGraphicSize(Sint32 img, int& width, int& height)
{
	Uint16 SizeVect = mGraphicsVector.size();
	if (img >= 0 || img < SizeVect)
	{
		SDL_Point size;
		SDL_QueryTexture(mGraphicsVector[img], NULL, NULL, &size.x, &size.y);
		width = size.x;
		height = size.y;
	}
	else
	{
		cout << "La imagen que buscas no esta disponible o no existe" << endl;
	}
}

//DONE
Uint16 ResourceManager::getGraphicWidth(Sint32 img)
{
	Uint16 SizeVect = mGraphicsVector.size();
	if (img >= 0 || img < SizeVect)
	{
		SDL_Point size;
		SDL_QueryTexture(mGraphicsVector[img], NULL, NULL, &size.x, &size.y);
		return size.x;
	}
	else
	{
		cout << "La imagen que buscas no esta disponible o no existe" << endl;
	}
}

//DONE
Uint16 ResourceManager::getGraphicHeight(Sint32 img)
{
	Uint16 SizeVect = mGraphicsVector.size();
	if (img >= 0 || img < SizeVect)
	{
		SDL_Point size;
		SDL_QueryTexture(mGraphicsVector[img], NULL, NULL, &size.x, &size.y);
		return size.y;
	}
	else
	{
		cout << "La imagen que buscas no esta disponible o no existe" << endl;
	}
}

//DONE
SDL_Texture* ResourceManager::getGraphicByID(Sint32 ID)
{
	Uint16 SizeVect = mGraphicsVector.size();

	if (mGraphicsVector[ID] != NULL)
	{
		return mGraphicsVector[ID];
	}
	else
	{
		cout << "La imagen que buscas no esta disponible o no existe" << endl;
	}
}

void ResourceManager::setAlphaGraphic(Sint32 ID, Uint8 alpha_value)
{
}

void ResourceManager::printLoadedGraphics()
{
}

Sint32 ResourceManager::createGraphic(const char* name, Uint16 width, Uint16 height)
{
	return Sint32();
}

//DONE
ResourceManager* ResourceManager::getInstance()
{
	if (pInstance == NULL)
		pInstance = new ResourceManager();

	return pInstance;
}

//DONE
ResourceManager::ResourceManager()
{
	mFirstFreeSlot = 0;
	mGraphicsVector.clear();
	mIDMap.clear();
}

//DONE
Sint32 ResourceManager::addGraphic(const char* file)
{
	SDL_Texture* newImage = Video::getInstace()->LoadImage(file);

	if (newImage == NULL)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return -1;
	}
	else
	{
		mGraphicsVector.push_back(newImage);
		Sint32 ID = updateFirstFreeSlotGraphic();
		mIDMap.insert(pair<string, Sint32>(file, ID));
		return ID;
	}
}

//DONE
Uint32 ResourceManager::updateFirstFreeSlotGraphic()
{
	int FreeSlot;
	for (size_t i = 0; i < mGraphicsVector.size(); i++)
	{
		if (mGraphicsVector.at(i) == NULL) {
			FreeSlot = i;
			return FreeSlot;
		}
	}
	FreeSlot = mGraphicsVector.size() - 1;
	return FreeSlot;
}