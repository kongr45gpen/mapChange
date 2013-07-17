This is the mapChange plugin.

It lets server owners specify a number of maps
available for players to choose from, allowing
them to create a rotational server.
It is currently in alpha stage.

Installation
------------
After compiling the plugin, you can include it in your
BZFS Server using the following command:

    -loadplugin mapChange,maps.list

`maps.list` represents the location of the file which
contains paths to all the map files you want your
users to play on.

An [example `maps.list` file](maps.list) is provided in
the repository. The first column should contain the name
of the map (the unique identifier of the map that players
can see), while the second column should be the path to
the map file. Each map goes to a separate line.

Usage
-----
The `/map` command should display a list of all maps. To
change the map, a user should type `/map alias`, where `alias`
is the name of the map as shown on the map list.
