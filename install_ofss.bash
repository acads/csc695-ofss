#!/bin/bash

# Automates the build and installation of ofsoftswitch13 along with
# required build tools and libraries.
# 
# Author: Aravindhan Dhanasekaran <adhanas@ncsu.edu>

red_bold='\e[91m \e[1m'
no_color='\e[0m'

# Install required build tools first
echo -e ${red_bold}
echo "#########################################################"
echo "#   Installing requird build tools for ofsoftswitch13   #"
echo "#########################################################"
echo -e ${no_color}
pwd
sudo apt-get install cmake libpcap-dev libxerces-c2-dev libpcre3-dev flex \
         bison pkg-config autoconf libtool libboost-dev


# Build NetBee libraries; ofsoftswitch uses them to parse packets.
echo -e ${red_bold}
echo "################################################"
echo "#   Building NetBee packet parsing libraries   #"
echo "################################################"
echo -e ${no_color}
pwd
unzip nbeesrc-jan-10-2013.zip
cd nbeesrc-jan-10-2013/src 
pwd
cmake .
make
sudo cp ../bin/libn*.so /usr/local/lib
sudo ldconfig
sudo cp -R ../include/* /usr/include/


# Build and install ofsoftswitch
echo -e ${red_bold}
echo "############################################"
echo "#   Building and installing ofsoftswitch   #"
echo "############################################"
echo -e ${no_color}
cd ../../ && cd ofsoftswitch13-master/
pwd
./boot.sh
./configure
make
sudo make install

