#!/bin/bash
clear
make clean
make
exec ./compiler test.imp out.mr
exec ./maszyna-wirtualna out.mr