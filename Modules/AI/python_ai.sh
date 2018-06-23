#!/bin/bash

trap ctrl_c INT

function ctrl_c {
	cd ../../..
}

cd Modules/AI/Python/
./zappy_ai $@