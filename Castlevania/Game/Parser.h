#pragma once

#include <vector>
#include "..\Dependencies\pugixml\src\pugixml.hpp"
#include "Objects\Simon.h"
#include "Objects\Weapons\Whip.h"
#include "Objects\Weapons\SubWeapon.h"
#include "Map\Grid.h"
#include "Map\Tilemap.h"

class Parser
{
private:
	static std::vector<int> split(const std::string& s, char delimiter);
	static void Parse_Whip(Whip* whip, pugi::xml_node root);
	static void Parse_SubWeapon(SubWeapon* sub, pugi::xml_node root);
	static void Parse_AnimationSet(LPGAMEOBJECT obj, pugi::xml_node node);
	static void Parse_TilemapMatrix(std::vector<std::vector<int>>* matrix, pugi::xml_node root);
	static void Parse_Cell(std::vector<std::vector<std::vector<LPGAMEOBJECT>>>* cells, pugi::xml_node root);

public:
	static void Parse_Texture(pugi::xml_node node);
	static void Parse_Sprite(pugi::xml_node node);
	static void Parse_Animation(pugi::xml_node node);
	static void Parse_Sound(pugi::xml_node node);

	static void Parse_Object(pugi::xml_node node);

	static void Parse_Player(Simon** player, pugi::xml_node root);
	static void Parse_Tileset(pugi::xml_node root);
	static void Parse_Tilemap(Tilemap** tilemap, pugi::xml_node root);
	static void Parse_Grid(Grid** grid, pugi::xml_node root);
};

