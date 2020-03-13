#include "ResourceManager.h"

ResourceManager* ResourceManager::sInstance = NULL;

ResourceManager::ResourceManager(SDL_Renderer* renderer)
{
	ResourceManager::m_pRenderer = renderer;
}

ResourceManager::~ResourceManager()
{
}

BitMapPack ResourceManager::LoadBitMap(std::string filePath, bool transparency)
{

	BitMapPack returnPack;
	returnPack.texture = nullptr;
	returnPack.width = NULL;
	returnPack.height = NULL;

	// check if we have already loaded our texture, and then load it from the hashmap
	if (checkHashMap(filePath))
	{
		returnPack = m_textureHashMap[filePath];

		Log("Retrieved BitMapPack from textureHashMap", FILTHY_DEBUG);
	}
	// if we haven't loaded the texture, load it and add it to the hashmap
	else
	{
		SDL_Surface* m_pBitMapTempSurface = nullptr;
		SDL_Texture* m_pBitMapTempTexture = nullptr;

		// create bitmap surface
		m_pBitMapTempSurface = SDL_LoadBMP(filePath.c_str());
		// check bitmap surface was created successfully
		if (!m_pBitMapTempSurface) {
			// bitmap not loaded. Do the dirty shame
			std::cout << "SURFACE for bitmap " << filePath << " not loaded! \n";
			std::cout << SDL_GetError() << "\n";
		}
		else
		{
			// add to the BitMapPack
			returnPack.width = m_pBitMapTempSurface->w;
			returnPack.height = m_pBitMapTempSurface->h;

			// remove transparent pixels
			if (transparency)
			{
				// assume transparency colour is magenta (255,0,255)
				Uint32 colourKey = SDL_MapRGB(m_pBitMapTempSurface->format, 255, 0, 255);
				SDL_SetColorKey(m_pBitMapTempSurface, SDL_TRUE, colourKey);
			}
		}

		// create bitmap texture
		m_pBitMapTempTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pBitMapTempSurface);
		if (!m_pBitMapTempTexture)
		{
			// texture not loaded. Do the dirty shame
			std::cout << "TEXTURE for bitmap '%s' " << filePath << "not loaded! \n";
			std::cout << SDL_GetError() << "\n";
		}
		else
		{
			// add to the BitMapPack
			returnPack.texture = m_pBitMapTempTexture;
		}

		m_textureHashMap.insert(std::make_pair(filePath, returnPack));

		std::cout << "Added BitMapPack " << filePath << " to textureHashMap" << std::endl;

		// pointer cleaning
		if (m_pBitMapTempSurface)
		{
			SDL_FreeSurface(m_pBitMapTempSurface);
			m_pBitMapTempSurface = nullptr;
		}
		if (m_pBitMapTempTexture != nullptr)
		{
			// this texture pointer is freed but cannot be destroyed as it
			//  would also destroy the texture in the map
			m_pBitMapTempTexture = nullptr;
		}
	}

	// after we have loaded the texture/width/height, return the BitMapPack
	return returnPack;
}

std::vector<std::string> ResourceManager::LoadMap(std::string filePath)
{
	inFile.open(filePath);
	if (!inFile)
	{
		Logger::Instance()->LogString("Failed to load map from filepath " + filePath, DBERROR);
	}
	std::string line;
	std::vector<std::string> mapReturnVector;

	while (std::getline(inFile, line))
	{
		Log("Map Line " + line, DEBUG);
		mapReturnVector.push_back(line);
	}

	inFile.close();

	return mapReturnVector;
}

ResourceManager* ResourceManager::Instance()
{
	if (sInstance == NULL)
	{
		std::cout << "Resource Manager Singleton not initialized with renderer!\n";
		std::cout << "Please initialize with renderer before attempting to access.\n";
		return NULL;
	}
	return sInstance;
}

ResourceManager* ResourceManager::Instance(SDL_Renderer* renderer)
{
	if (sInstance == NULL)
	{
		Log("Initializing resource manager with a renderer.", DEBUG);
		sInstance = new ResourceManager(renderer);
	}
	return sInstance;
}

void ResourceManager::release()
{

}

bool ResourceManager::checkHashMap(std::string key)
{
	if (m_textureHashMap.find(key) == m_textureHashMap.end()) return false;
	return true;
}