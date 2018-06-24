#!/bin/bash

current_dir=$PWD

trap ctrl_c INT

function ctrl_c {
	cd $current_dir
}

cd Modules/AI/Python/
./zappy_ai $@
cd $current_dir