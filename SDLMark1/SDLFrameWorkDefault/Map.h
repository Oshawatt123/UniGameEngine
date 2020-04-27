#pragma once
#include <string>
#include <vector>

/*!
	The Map class is responsible for holding data about a "map".
	It will parse a text file that could look like the following

		ABBBBBBBBBC
		DJJJLJJJJJF
		DJLJJLKJJJF
		DJJKJLJJJJF
		DJJJJJJJKJF
		DJKLJKJJLJF
		DJJJJLJJJJF
		GHHHHHHHHHI

	Each line is stored as a string and all the lines are kept in a vector.
	Each character is used to index into a tileSet, and the corresponding tile is drawn into the world.
*/
class Map
{
public:

	std::vector<std::string> mapTileData; /*!< The tile data of this map. */
	/*!
		The collision data of the tile Map. Used to eliminate the need for creating seperate objects in the scene to do this.
		\note This was never implemented and is not used.
	*/
	std::vector<std::string> mapCollisionData;

	std::string filePath; /*!< The file path of the map file.*/

	std::string tileSet; /*!< The file path of the tileSet used by the map. This is set on Scene load.*/

	Map();	/*!< Nothing happens here.*/
	~Map();	/*!< Nothing happens here.*/

	/*!
		A QoL function to see if the map has already been loaded, to save needing to do this in ResourceManager.
	*/
	bool MapLoaded();
};