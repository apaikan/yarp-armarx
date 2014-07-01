#!/bin/bash

# set the head down
echo "set pos 0 -40" | yarp write ...  /icubSim/head/rpc:i

#clear the worls
echo "world del all" | yarp write ... /icubSim/world

# add objects to the world
echo "world mk model milk_box.x milk_box.bmp 0.1 0.7 0.4" | yarp write ... /icubSim/world 

