sudp apt-get update
sudo apt-get install -y autoconf libtool

wget http://openvswitch.org/releases/openvswitch-2.3.0.tar.gz
tar xzf openvswitch-2.3.0.tar.gz
cd openvswitch-2.3.0


./boot.sh
./configure
make
sudo make install
