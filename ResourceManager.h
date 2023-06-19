#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include <vector>
#include <iostream>	
#include "Video.h"

using namespace std;
//! ResourceManager class
/*!
	Handles the load and management of the graphics in the game.
*/
class ResourceManager
{
public:

	//DONE!!!
	~ResourceManager();

	//DONE!!!
	void removeGraphic(const char* file);


	//DONE!!!
	Sint32 loadAndGetGraphicID(const char* file);


	//DONE!!!
	string getGraphicPathByID(Sint32 ID);


	//DONE!!!
	void getGraphicSize(Sint32 img, int& width, int& height);

	//DONE!!!
	Uint16 getGraphicWidth(Sint32 img);

	//DONE!!!
	Uint16 getGraphicHeight(Sint32 img);

	//DONE!!!
	SDL_Texture* getGraphicByID(Sint32 ID);

	//! Change general Alpha value to paint a concrete surface
	/*!
		\param ID ID of the graphic
		\param alpha_value From SDL_ALPHA_TRANSPARENT(0) to SDL_ALPHA_OPAQUE(255)
	*/
	void setAlphaGraphic(Sint32 ID, Uint8 alpha_value);

	//! Prints the path to loaded graphics
	void printLoadedGraphics();

	//! Create a new surface graphic to the ResourceManager
	/*!
		\param name for the graphic
		\param width Width for the graphic
		\param height Height for the graphic
		\return -1 if there's an error when loading
	*/
	Sint32 createGraphic(const char* name, Uint16 width, Uint16 height);

	//DONE!!!
	static ResourceManager* getInstance();

protected:
	//DONE!!!
	ResourceManager();

private:

	//DONE!!!
	Sint32 addGraphic(const char* file);

	//DONE!!!
	Uint32 updateFirstFreeSlotGraphic();

	vector<SDL_Texture*>	mGraphicsVector;	/*!<  Vector that stores Textures. Useful in render methods and sequential access*/
	map<string, Sint32>	mIDMap;			/*!<  Map that stores ID. Links strings to ID, Useful for check if graphic is has been loaded previously*/
	Uint32				mFirstFreeSlot;		/*!<  First free slot in the mGraphicsVector*/
	static ResourceManager* pInstance;		/*!<  Singleton instance*/
};

#endif