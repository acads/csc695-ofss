# 
# Automates mininet installation on Debian based machines.
#
# Author: Aravindhan Dhanasekaran <adhanas@ncsu.edu>
#

#!/bin/bash

# Install required build tools
sudo apt-get update
sudo apt-get install -y git make gcc cscope ctags

# Download latest mininet repo from Git
mkdir mininet_test && cd mininet_test
git clone git://github.com/mininet/mininet

# Install mininet with all options
mininet/util/install.sh
mininet/util/install.sh -3f

sudo mn --test pingall

