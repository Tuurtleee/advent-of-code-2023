#!/bin/bash

day=$(date +%d)
folder="day$day"
mkdir $folder
cp -r template/* $folder/