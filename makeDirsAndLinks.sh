#!/bin/bash
mkdir -p ${B2HH_STORAGE}
mkdir -p ${B2HH_STORAGE}/out
mkdir -p ${B2HH_STORAGE}/log
ln -s ${B2HH_STORAGE}/out ${B2HH_HOME}/out
ln -s ${B2HH_STORAGE}/log ${B2HH_HOME}/log


