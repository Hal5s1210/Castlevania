#pragma once

#include "..\Dependencies\pugixml\src\pugixml.hpp"

class Parser
{
public:
	static void Parse_Texture(pugi::xml_node node);
	static void Parse_Sprite(pugi::xml_node node);
	static void Parse_Animation(pugi::xml_node node);
	static void Parse_Sound(pugi::xml_node node);
	static void Parse_Object(pugi::xml_node node);
};

