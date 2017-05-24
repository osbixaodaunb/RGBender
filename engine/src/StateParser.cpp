#include "StateParser.h"

#include "GameObject.h"
#include "tinyxml.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameObjectFactory.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

TiXmlElement* findValue(TiXmlElement* root, string value){
	TiXmlElement* elem = 0;

	for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
		if(e->Value() == value){
			elem = e;
		}
	}

	return elem;
}

bool StateParser::parseState(string stateFile, string stateID, vector<GameObject*> *pObjects, vector<string> *pTextureIDs){
	// create the xml document
	TiXmlDocument xmlDoc;
		
	stateFile = "assets/xml/" + stateFile;

	// load the state file
	if(!xmlDoc.LoadFile(stateFile.c_str())){
		cerr << xmlDoc.ErrorDesc() << endl;
		return false;
	}

	// get the root element
	TiXmlElement* pRoot = xmlDoc.RootElement();

	TiXmlElement* pStateRoot = findValue(pRoot, stateID);

	TiXmlElement* pTextureRoot = findValue(pStateRoot, "TEXTURES");
	
	// now parse the textures
	parseTextures(pTextureRoot, pTextureIDs);

	TiXmlElement* pObjectRoot = findValue(pStateRoot, "OBJECTS");

	parseObjects(pObjectRoot, pObjects);

	return true;
}

void StateParser::parseTextures(TiXmlElement* root, vector<string> *pTextureIDs){
	for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
		string filenameAttribute = e->Attribute("filename");
		string idAttribute = e->Attribute("ID");
		pTextureIDs->push_back(idAttribute);

		TextureManager::Instance().load(filenameAttribute, idAttribute, Game::Instance().getRenderer());
	}
}

void StateParser::parseObjects(TiXmlElement* root, vector<GameObject*> *pObjects){
	for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
		int x, y, width, height, numFrames, callbackID, animSpeed;
		string textureID;

		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width",&width);
		e->Attribute("height", &height);
		e->Attribute("numFrames", &numFrames);
		e->Attribute("callbackID", &callbackID);
		e->Attribute("animSpeed", &animSpeed);

		textureID = e->Attribute("textureID");

		GameObject* pGameObject = GameObjectFactory::Instance().create(e->Attribute("type"));
		pGameObject->load(new LoaderParams(x,y,width,height,textureID,numFrames,callbackID, animSpeed));
		pObjects->push_back(pGameObject);
	}
}
