# 
# Automates the isntallation of OpenFlow softswitch on Deban machines
#
# Author: Aravindhan Dhanasekaran <adhanas@ncsu.edu>
#

#!/usr/bin/bash

# Install required packages
apt-get update
apt-get install -y cmake gcc make libpcap-dev libxerces-c2-dev libpcre3-dev flex bison pkg-config autoconf libtool libboost-dev unzip git 

# Download, compile and install netbee libraries
wget http://www.nbee.org/download/nbeesrc-jan-10-2013.php
mv nbeesrc-jan-10-2013.php nbeesrc-jan-10-2013.zip
unzip nbeesrc-jan-10-2013.zip
cd nbeesrc-jan-10-2013/src
cmake .
make
sudo cp ../bin/libn*.so /usr/local/lib/
sudo cp -R ../include/* /usr/include/


# Download, compile and install ofsoftswitch
cd ..
git clone https://github.com/CPqD/ofsoftswitch13.git
cd ofsoftswitch13/
./boot.sh
./configure
make
sudo make install

