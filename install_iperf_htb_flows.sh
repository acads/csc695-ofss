sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=0 eth_type=0x0806 goto:1
sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=0 eth_type=0x0800,ip_proto=1 goto:2
sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=0 eth_type=0x0800,ip_proto=6 meta:0x6 goto:3
sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=0 eth_type=0x0800,ip_proto=17 meta:0x11 goto:4

sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=1 in_port=1 apply:output:2
sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=1 in_port=2 apply:output:1

sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=2 in_port=1 apply:output:2
sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=2 in_port=2 apply:output:1

sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=3 meta=0x6,in_port=1 apply:output:2
sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=3 meta=0x6,in_port=2 apply:output:1

sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=4 meta=0x11,in_port=1 apply:output:2
sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=4 meta=0x11,in_port=2 apply:output:1
