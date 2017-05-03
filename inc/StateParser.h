#ifndef STATE_PARSER_H
#define STATE_PARSER_H

#include "tinyxml.h"
#include "GameObject.h"

#include <vector>
#include <string>

class StateParser{
public:
	bool parseState(std::string stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);

private:
	void parseObjects(TiXmlElement* root, std::vector<GameObject*> *pObjects);
	void parseTextures(TiXmlElement* root, std::vector<std::string> *pTextureIDs);
};

#endif
