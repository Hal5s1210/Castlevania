#pragma once

#include <vector>
#include "..\Dependencies\pugixml\src\pugixml.hpp"
#include "Objects/GameObject.h"

class Parser
{
public:
	static void Parse_Texture(pugi::xml_node node);
	static void Parse_Sprite(pugi::xml_node node);
	static void Parse_Animation(pugi::xml_node node);
	static void Parse_Sound(pugi::xml_node node);
	static void Parse_Object(pugi::xml_node node);
	static void Parse_AnimationSet(LPGAMEOBJECT obj, pugi::xml_node node);
	static void Parse_Grid(std::vector<std::vector<std::vector<LPGAMEOBJECT>>>* cells, pugi::xml_node root);
};

