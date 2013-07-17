#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "bzfsAPI.h"
#include "plugin_utils.h"

using namespace std;

class mapChange: public bz_Plugin, public bz_CustomSlashCommandHandler
{
public:
  virtual const char* Name () {return "Map Change";}
  virtual void Init ( const char* config);

  void Cleanup();
  void Event ( bz_EventData *data);

  bool SlashCommand (int playerID, bz_ApiString command, bz_ApiString message, bz_APIStringList *params);

private:
  map<string,string> mapmap; // A map of maps
  string cmap; // Current map
  int restartTicks; // Number of ticks left until the server should restart
};

BZ_PLUGIN(mapChange)

void mapChange::Init ( const char* commandLine )
{
  Register ( bz_eTickEvent );
  Register ( bz_eGetWorldEvent );

  bz_registerCustomSlashCommand("map", this);
  restartTicks = -1;

  // Populate the mapmap by reading from the file the user gave us
  ifstream file(commandLine);

  std::string a,b;
  bool first = true;
  while (file >> a >> b) {
    if (first) { cmap = a; first = false; }
    mapmap[a] = b;
  }

}

void mapChange::Cleanup() {
  bz_removeCustomSlashCommand("map");
  Flush();
}


void mapChange::Event(bz_EventData *data) {
switch(data->eventType) {
case bz_eTickEvent: {

  if (restartTicks > 0) restartTicks--;
  if (restartTicks == 0) {
    restartTicks = -1;
    bz_restart();
  }

}break;

case bz_eGetWorldEvent: {
  bz_GetWorldEventData_V1* worldData = (bz_GetWorldEventData_V1*)data;
  worldData->worldFile = mapmap[cmap];
}break;

}}

bool mapChange::SlashCommand (int playerID, bz_ApiString command, bz_ApiString message, bz_APIStringList *params) {
  command.tolower();
  if (command == "map") {
    if (params->size() == 0) {
	// Announce the current map and iterate through all maps
       bz_sendTextMessagef(BZ_SERVER, playerID, "The current map is %s",cmap.c_str());
       bz_sendTextMessage(BZ_SERVER, playerID, "Other possible maps:");
       for (auto i = mapmap.begin();i != mapmap.end(); i++) {
		const char* message;
		// Indicate the current map
		if (i->first == cmap) 	message = "[* %s]";
		else			message = " * %s";
		bz_sendTextMessagef(BZ_SERVER, playerID, message, i->first.c_str());
       }
    } else {
       const char* newMap = params->get(0).c_str();
       if(mapmap[newMap] == "") {
          bz_sendTextMessagef(BZ_SERVER, playerID,"The %s map doesn't exist.", newMap);
          return true;
       }
       bz_sendTextMessagef(BZ_SERVER, playerID,"Changing map to %s...", newMap);
       bz_sendTextMessagef(BZ_SERVER, BZ_ALLUSERS, "%s wishes to change the map to %s, restarting...",bz_getPlayerCallsign(playerID), newMap);
       restartTicks = 5;
       cmap = newMap;
    }


    return true;
  }
  return false;
}

