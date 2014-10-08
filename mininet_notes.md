mininet notes
=============

Installation
------------
1. Get the lateset stable source code from Git tree.
    git clone git://github.com/mininet/mininet

2. Install using util/install.sh script
    mininet/util/install.sh -n      (for minimal installation)  
    mininet/util/install.sh -a      (for full installation)  
    mininet/util/install.sh -3f     (to install OF 1.3 soft switch)  
    mininet/util/install.sh -h      (for all possible install options)  

3. Test the installation
    sudo mn --test pingall

Topology Creation
-----------------
To start a simple topology with ofsoftswitch and 2 nodes,

```
click@vm-click:~/695/mininet$ sudo mn --topo single,2 --mac --switch user --controller remote
*** Creating network
*** Adding controller
Unable to contact the remote controller at 127.0.0.1:6633
*** Adding hosts:
h1 h2 
*** Adding switches:
s1 
*** Adding links:
(h1, s1) (h2, s1) 
*** Configuring hosts
h1 h2 
*** Starting controller
*** Starting 1 switches
s1 
*** Starting CLI:
mininet> 

mininet> h1 ifconfig
h1-eth0   Link encap:Ethernet  HWaddr 00:00:00:00:00:01  
          inet addr:10.0.0.1  Bcast:10.255.255.255  Mask:255.0.0.0
          inet6 addr: fe80::200:ff:fe00:1/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
          RX packets:27 errors:0 dropped:0 overruns:0 frame:0
          TX packets:12 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:4778 (4.7 KB)  TX bytes:864 (864.0 B)

lo        Link encap:Local Loopback  
          inet addr:127.0.0.1  Mask:255.0.0.0
          inet6 addr: ::1/128 Scope:Host
          UP LOOPBACK RUNNING  MTU:65536  Metric:1
          RX packets:3 errors:0 dropped:0 overruns:0 frame:0
          TX packets:3 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:0 
          RX bytes:336 (336.0 B)  TX bytes:336 (336.0 B)

mininet> h2 ifconfig
h2-eth0   Link encap:Ethernet  HWaddr 00:00:00:00:00:02  
          inet addr:10.0.0.2  Bcast:10.255.255.255  Mask:255.0.0.0
          inet6 addr: fe80::200:ff:fe00:2/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
          RX packets:28 errors:0 dropped:0 overruns:0 frame:0
          TX packets:9 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:4879 (4.8 KB)  TX bytes:738 (738.0 B)

lo        Link encap:Local Loopback  
          inet addr:127.0.0.1  Mask:255.0.0.0
          inet6 addr: ::1/128 Scope:Host
          UP LOOPBACK RUNNING  MTU:65536  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:0 
          RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)

mininet> s1 ifconfig
eth0      Link encap:Ethernet  HWaddr 08:00:27:be:4c:a0  
          inet addr:10.0.2.15  Bcast:10.0.2.255  Mask:255.255.255.0
          inet6 addr: fe80::a00:27ff:febe:4ca0/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
          RX packets:26390 errors:0 dropped:0 overruns:0 frame:0
          TX packets:11222 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:28173765 (28.1 MB)  TX bytes:6447114 (6.4 MB)

eth1      Link encap:Ethernet  HWaddr 08:00:27:4b:00:4e  
          inet addr:192.168.56.101  Bcast:192.168.56.255  Mask:255.255.255.0
          inet6 addr: fe80::a00:27ff:fe4b:4e/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
          RX packets:532259 errors:0 dropped:0 overruns:0 frame:0
          TX packets:398759 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:460823492 (460.8 MB)  TX bytes:650034173 (650.0 MB)

lo        Link encap:Local Loopback  
          inet addr:127.0.0.1  Mask:255.0.0.0
          inet6 addr: ::1/128 Scope:Host
          UP LOOPBACK RUNNING  MTU:65536  Metric:1
          RX packets:112137 errors:0 dropped:0 overruns:0 frame:0
          TX packets:112137 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:0 
          RX bytes:857523467 (857.5 MB)  TX bytes:857523467 (857.5 MB)

s1-eth1   Link encap:Ethernet  HWaddr 9e:23:f2:70:d5:8e  
          inet6 addr: fe80::9c23:f2ff:fe70:d58e/64 Scope:Link
          UP BROADCAST RUNNING PROMISC MULTICAST  MTU:1500  Metric:1
          RX packets:12 errors:0 dropped:0 overruns:0 frame:0
          TX packets:28 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:864 (864.0 B)  TX bytes:4879 (4.8 KB)

s1-eth2   Link encap:Ethernet  HWaddr 52:93:a1:6c:e6:aa  
          inet6 addr: fe80::5093:a1ff:fe6c:e6aa/64 Scope:Link
          UP BROADCAST RUNNING PROMISC MULTICAST  MTU:1500  Metric:1
          RX packets:9 errors:0 dropped:0 overruns:0 frame:0
          TX packets:28 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:738 (738.0 B)  TX bytes:4879 (4.8 KB)

tap0      Link encap:Ethernet  HWaddr 00:00:00:00:00:01  
          inet6 addr: fe80::200:ff:fe00:1/64 Scope:Link
          UP BROADCAST RUNNING PROMISC MULTICAST  MTU:1500  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:28 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:500 
          RX bytes:0 (0.0 B)  TX bytes:4879 (4.8 KB)
```

*******************************************************************************

dpctl examples
==============
```
click@vm-click:~/695/csc695-ofss-dev$ dpctl --help
dpctl: OpenFlow switch management utility
usage: dpctl [OPTIONS] SWITCH COMMAND [ARG...]
  SWITCH ping [N] [B]                    latency of B-byte echos N times
  SWITCH monitor                         monitors packets from the switch

  SWITCH features                        show basic information
  SWITCH get-config                      get switch configuration
  SWITCH port-desc                       print port description and status
  SWITCH meter-config [METER]            get meter configuration
  SWITCH stats-desc                      print switch description
  SWITCH stats-flow [ARG [MATCH]]        print flow stats
  SWITCH stats-aggr [ARG [MATCH]]        print flow aggregate stats
  SWITCH stats-table                     print table stats
  SWITCH stats-port [PORT]               print port statistics
  SWITCH stats-queue [PORT [QUEUE]]      print queue statistics
  SWITCH stats-group [GROUP]             print group statistics
  SWITCH stats-meter [METER]             print meter statistics
  SWITCH stats-group-desc [GROUP]        print group desc statistics

  SWITCH set-config ARG                  set switch configuration
  SWITCH flow-mod ARG [MATCH [INST...]]  send flow_mod message
  SWITCH group-mod ARG [BUCARG ACT...]   send group_mod message
  SWITCH meter-mod ARG [BANDARG ...]     send meter_mod message
  SWITCH port-mod ARG                    send port_mod message
  SWITCH table-mod ARG                   send table_mod message
  SWITCH queue-get-config PORT           send queue_get_config message

OpenFlow extensions
  SWITCH set-desc DESC                   sets the DP description
  SWITCH queue-mod PORT QUEUE BW         adds/modifies queue
  SWITCH queue-del PORT QUEUE            deletes queue


Active OpenFlow connection methods:
  tcp:HOST[:PORT]         PORT (default: 6653) on remote TCP HOST
  unix:FILE               Unix domain socket named FILE
  fd:N                    File descriptor N

Logging options:
  -v, --verbose=MODULE[:FACILITY[:LEVEL]]  set logging levels
  -v, --verbose           set maximum verbosity level
  --log-file[=FILE]       enable logging to specified FILE
                          (default: /usr/local/var/log/openflow/dpctl.log)

Other options:
  --strict                    use strict match for flow commands
  -t, --timeout=SECS          give up after SECS seconds
  -h, --help                  display this help message
  -V, --version               display version information


click@vm-click:~/695/csc695-ofss-dev$ sudo dpctl unix:/tmp/s1 stats-flow table=0

SENDING (xid=0xF0FF00F0):
stat_req{type="flow", flags="0x0", table="0", oport="any", ogrp="any", cookie=0x0", mask=0x0", match=oxm{all match}}


RECEIVED (xid=0xF0FF00F0):
stat_repl{type="flow", flags="0x0", stats=[]}

click@vm-click:~/695/csc695-ofss-dev$ sudo dpctl unix:/tmp/s1 features

SENDING (xid=0xF0FF00F0):
feat_req


RECEIVED (xid=0xF0FF00F0):
feat_repl{dpid="0x0000000000000001", buffs="256", tabs="64", aux_id="0", caps="0x4f"]}

click@vm-click:~/695/csc695-ofss-dev$ sudo dpctl  unix:/tmp/s1 stats-desc

SENDING (xid=0xF0FF00F0):
stat_req{type="desc", flags="0x0"}


RECEIVED (xid=0xF0FF00F0):
stat_repl{type="desc", flags="0x0", mfr="Stanford University, Ericsson Research and CPqD Research", hw="OpenFlow 1.3 Reference Userspace Switch", sw="Sep 17 2014 05:47:29", sn="1", dp="OpenFlow 1.3 Reference Userspace Switch Datapath"}

click@vm-click:~/695/csc695-ofss-dev$ sudo dpctl  unix:/tmp/s1 stats-table

SENDING (xid=0xF0FF00F0):
stat_req{type="table", flags="0x0"}


RECEIVED (xid=0xF0FF00F0):
stat_repl{type="table", flags="0x0", stats=[{table="0", active="0", lookup="110", match="0", {table="1", active="0", lookup="0", match="0", {table="2", active="0", lookup="0", match="0", {table="3", active="0", lookup="0", match="0", {table="4", active="0", lookup="0", match="0", {table="5", active="0", lookup="0", match="0", {table="6", active="0", lookup="0", match="0", {table="7", active="0", lookup="0", match="0", {table="8", active="0", lookup="0", match="0", {table="9", active="0", lookup="0", match="0", {table="10", active="0", lookup="0", match="0", {table="11", active="0", lookup="0", match="0", {table="12", active="0", lookup="0", match="0", {table="13", active="0", lookup="0", match="0", {table="14", active="0", lookup="0", match="0", {table="15", active="0", lookup="0", match="0", {table="16", active="0", lookup="0", match="0", {table="17", active="0", lookup="0", match="0", {table="18", active="0", lookup="0", match="0", {table="19", active="0", lookup="0", match="0", {table="20", active="0", lookup="0", match="0", {table="21", active="0", lookup="0", match="0", {table="22", active="0", lookup="0", match="0", {table="23", active="0", lookup="0", match="0", {table="24", active="0", lookup="0", match="0", {table="25", active="0", lookup="0", match="0", {table="26", active="0", lookup="0", match="0", {table="27", active="0", lookup="0", match="0", {table="28", active="0", lookup="0", match="0", {table="29", active="0", lookup="0", match="0", {table="30", active="0", lookup="0", match="0", {table="31", active="0", lookup="0", match="0", {table="32", active="0", lookup="0", match="0", {table="33", active="0", lookup="0", match="0", {table="34", active="0", lookup="0", match="0", {table="35", active="0", lookup="0", match="0", {table="36", active="0", lookup="0", match="0", {table="37", active="0", lookup="0", match="0", {table="38", active="0", lookup="0", match="0", {table="39", active="0", lookup="0", match="0", {table="40", active="0", lookup="0", match="0", {table="41", active="0", lookup="0", match="0", {table="42", active="0", lookup="0", match="0", {table="43", active="0", lookup="0", match="0", {table="44", active="0", lookup="0", match="0", {table="45", active="0", lookup="0", match="0", {table="46", active="0", lookup="0", match="0", {table="47", active="0", lookup="0", match="0", {table="48", active="0", lookup="0", match="0", {table="49", active="0", lookup="0", match="0", {table="50", active="0", lookup="0", match="0", {table="51", active="0", lookup="0", match="0", {table="52", active="0", lookup="0", match="0", {table="53", active="0", lookup="0", match="0", {table="54", active="0", lookup="0", match="0", {table="55", active="0", lookup="0", match="0", {table="56", active="0", lookup="0", match="0", {table="57", active="0", lookup="0", match="0", {table="58", active="0", lookup="0", match="0", {table="59", active="0", lookup="0", match="0", {table="60", active="0", lookup="0", match="0", {table="61", active="0", lookup="0", match="0", {table="62", active="0", lookup="0", match="0", {table="63", active="0", lookup="0", match="0"]}


click@vm-click:~/695/csc695-ofss-dev$ sudo dpctl  unix:/tmp/s1 port-desc

SENDING (xid=0xF0FF00F0):
stat_req{type="port-desc", flags="0x0"}


RECEIVED (xid=0xF0FF00F0):
stat_repl{type="port-desc", flags="0x0"{no="1", hw_addr="9e:23:f2:70:d5:8e", name="s1-eth1", config="0x0", state="0x4", curr="0x840", adv="0x0", supp="0x0", peer="0x0", curr_spd="10485760kbps", max_spd="0kbps"}, {no="2", hw_addr="52:93:a1:6c:e6:aa", name="s1-eth2", config="0x0", state="0x4", curr="0x840", adv="0x0", supp="0x0", peer="0x0", curr_spd="10485760kbps", max_spd="0kbps"}, {no="local", hw_addr="00:00:00:00:00:01", name="tap:", config="0x0", state="0x4", curr="0x802", adv="0x0", supp="0x0", peer="0x0", curr_spd="10240kbps", max_spd="0kbps"}}}
```

*******************************************************************************
To enable ARP resoulution between h1 & h2
=========================================

1. Verify ping doesn't go through between h1 & h2

```
mininet> h1 ping h2
PING 10.0.0.2 (10.0.0.2) 56(84) bytes of data.
From 10.0.0.1 icmp_seq=1 Destination Host Unreachable
From 10.0.0.1 icmp_seq=2 Destination Host Unreachable
From 10.0.0.1 icmp_seq=3 Destination Host Unreachable
```

2. Verify ARP table of hosts. It should either be incomplete or empty.
```
mininet> h1 arp -n
Address                  HWtype  HWaddress           Flags Mask            Iface
10.0.0.2                         (incomplete)                              h1-eth0
```

3. Install pair of ARP flows to let ofss forward traffic between the nodes.

```
click@vm-click:~/695/csc695-ofss-dev$ sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=0 in_port=1,eth_type=0x0806 apply:output:2

SENDING (xid=0xF0FF00F0):
flow_mod{table="0", cmd="add", cookie="0x0", mask="0x0", idle="0", hard="0", prio="32768", buf="none", port="any", group="any", flags="0x0", match=oxm{in_port="1", eth_type="0x806"}, insts=[apply{acts=[out{port="2"}]}]}

OK.

click@vm-click:~/695/csc695-ofss-dev$ sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=0 in_port=2,eth_type=0x0806 apply:output:1

SENDING (xid=0xF0FF00F0):
flow_mod{table="0", cmd="add", cookie="0x0", mask="0x0", idle="0", hard="0", prio="32768", buf="none", port="any", group="any", flags="0x0", match=oxm{in_port="2", eth_type="0x806"}, insts=[apply{acts=[out{port="1"}]}]}

OK.

click@vm-click:~/695/csc695-ofss-dev$ sudo dpctl unix:/tmp/s1 stats-flow table=0
SENDING (xid=0xF0FF00F0):
stat_req{type="flow", flags="0x0", table="0", oport="any", ogrp="any", cookie=0x0", mask=0x0", match=oxm{all match}}


RECEIVED (xid=0xF0FF00F0):
stat_repl{type="flow", flags="0x0", stats=[{table="0", match="oxm{in_port="1", eth_type="0x806"}", dur_s="59", dur_ns="996000", prio="32768", idle_to="0", hard_to="0", cookie="0x0", pkt_cnt="6", byte_cnt="252", insts=[apply{acts=[out{port="2"}]}]}, {table="0", match="oxm{in_port="2", eth_type="0x806"}", dur_s="2", dur_ns="765000", prio="32768", idle_to="0", hard_to="0", cookie="0x0", pkt_cnt="0", byte_cnt="0", insts=[apply{acts=[out{port="1"}]}]}]}
```

4. Now ping h2 from h1. Ping should fail, but the ARPs should be resolved.

```
mininet> h1 arp -n
Address                  HWtype  HWaddress           Flags Mask            Iface
10.0.0.2                 ether   00:00:00:00:00:02   C                     h1-eth0

mininet> h2 arp -n
Address                  HWtype  HWaddress           Flags Mask            Iface
10.0.0.1                 ether   00:00:00:00:00:01   C                     h2-eth0
```

5. Now, install flows to enable ping traffic to pass thru for exactly 10 seconds. 
Do a continuos ping. Pings should fail after 10 seconds.

```
click@vm-click:~/695/csc695-ofss-dev$ sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=0 in_port=1,eth_type=0x0800,ip_proto=1,ip_src=10.0.0.1,ip_dst=10.0.0.2 apply:output:2

SENDING (xid=0xF0FF00F0):
flow_mod{table="0", cmd="add", cookie="0x0", mask="0x0", idle="0", hard="0", prio="32768", buf="none", port="any", group="any", flags="0x0", match=oxm{in_port="1", eth_type="0x800", ipv4_src="10.0.0.1", ipv4_dst="10.0.0.2", ip_proto="1"}, insts=[apply{acts=[out{port="2"}]}]}

OK.

click@vm-click:~/695/csc695-ofss-dev$ sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=0 in_port=2,eth_type=0x0800,ip_proto=1,ip_src=10.0.0.2,ip_dst=10.0.0.1 apply:output:1

SENDING (xid=0xF0FF00F0):
flow_mod{table="0", cmd="add", cookie="0x0", mask="0x0", idle="0", hard="0", prio="32768", buf="none", port="any", group="any", flags="0x0", match=oxm{in_port="2", eth_type="0x800", ipv4_src="10.0.0.2", ipv4_dst="10.0.0.1", ip_proto="1"}, insts=[apply{acts=[out{port="1"}]}]}

OK.

click@vm-click:~/695/csc695-ofss-dev$ sudo dpctl unix:/tmp/s1 stats-flow table=0
SENDING (xid=0xF0FF00F0):
stat_req{type="flow", flags="0x0", table="0", oport="any", ogrp="any", cookie=0x0", mask=0x0", match=oxm{all match}}


RECEIVED (xid=0xF0FF00F0):
stat_repl{type="flow", flags="0x0", stats=[{table="0", match="oxm{in_port="1", eth_type="0x806"}", dur_s="1694", dur_ns="523000", prio="32768", idle_to="0", hard_to="0", cookie="0x0", pkt_cnt="14", byte_cnt="588", insts=[apply{acts=[out{port="2"}]}]}, {table="0", match="oxm{in_port="2", eth_type="0x806"}", dur_s="1637", dur_ns="292000", prio="32768", idle_to="0", hard_to="0", cookie="0x0", pkt_cnt="8", byte_cnt="336", insts=[apply{acts=[out{port="1"}]}]}, {table="0", match="oxm{in_port="1", eth_type="0x800", ipv4_src="10.0.0.1", ipv4_dst="10.0.0.2", ip_proto="1"}", dur_s="158", dur_ns="444000", prio="32768", idle_to="0", hard_to="0", cookie="0x0", pkt_cnt="7", byte_cnt="686", insts=[apply{acts=[out{port="2"}]}]}, {table="0", match="oxm{in_port="2", eth_type="0x800", ipv4_src="10.0.0.2", ipv4_dst="10.0.0.1", ip_proto="1"}", dur_s="18", dur_ns="611000", prio="32768", idle_to="0", hard_to="0", cookie="0x0", pkt_cnt="0", byte_cnt="0", insts=[apply{acts=[out{port="1"}]}]}]}

mininet> h1 ping h2 -c 5
PING 10.0.0.2 (10.0.0.2) 56(84) bytes of data.
64 bytes from 10.0.0.2: icmp_req=1 ttl=64 time=0.138 ms
64 bytes from 10.0.0.2: icmp_req=2 ttl=64 time=0.175 ms
64 bytes from 10.0.0.2: icmp_req=3 ttl=64 time=0.198 ms
64 bytes from 10.0.0.2: icmp_req=4 ttl=64 time=0.172 ms
64 bytes from 10.0.0.2: icmp_req=5 ttl=64 time=0.190 ms

--- 10.0.0.2 ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4005ms
rtt min/avg/max/mdev = 0.138/0.174/0.198/0.025 ms
mininet> h2 ping h1 -c 5
PING 10.0.0.1 (10.0.0.1) 56(84) bytes of data.
64 bytes from 10.0.0.1: icmp_req=1 ttl=64 time=0.157 ms
64 bytes from 10.0.0.1: icmp_req=2 ttl=64 time=0.584 ms
64 bytes from 10.0.0.1: icmp_req=3 ttl=64 time=0.518 ms
64 bytes from 10.0.0.1: icmp_req=4 ttl=64 time=0.606 ms
64 bytes from 10.0.0.1: icmp_req=5 ttl=64 time=0.256 ms

--- 10.0.0.1 ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4006ms
rtt min/avg/max/mdev = 0.157/0.424/0.606/0.183 ms
```

*******************************************************************************
Simple iperf testing in Mininet
===============================

1. Start the simple topology using:
```
sudo mn --topo single,2 --mac --switch user,protocols=OpenFlow13 --controller remote
```

2. See the ports in ofss.
```
$ sudo dpctl unix:/tmp/s1 features
RECEIVED (xid=0xF0FF00F0):
feat_repl{dpid="0x0000000000000001", buffs="256", tabs="64", aux_id="0", caps="0x4f"]}

$ sudo dpctl unix:/tmp/s1 port-desc
RECEIVED (xid=0xF0FF00F0):
stat_repl{type="port-desc", flags="0x0"{no="1", hw_addr="8a:ef:d0:d9:e8:35", name="s1-eth1", config="0x0", state="0x4", curr="0x840", adv="0x0", supp="0x0", peer="0x0", curr_spd="10485760kbps", max_spd="0kbps"}, {no="2", hw_addr="fa:b4:3e:47:82:b3", name="s1-eth2", config="0x0", state="0x4", curr="0x840", adv="0x0", supp="0x0", peer="0x0", curr_spd="10485760kbps", max_spd="0kbps"}, {no="local", hw_addr="00:00:00:00:00:01", name="tap:", config="0x0", state="0x4", curr="0x802", adv="0x0", supp="0x0", peer="0x0", curr_spd="10240kbps", max_spd="0kbps"}}}
```

3. Install couple of basic flows to get traffic flowing b/w the switch ports.
```
$ sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=0 in_port=1 apply:output:2

SENDING (xid=0xF0FF00F0):
flow_mod{table="0", cmd="add", cookie="0x0", mask="0x0", idle="0", hard="0", prio="32768", buf="none", port="any", group="any", flags="0x0", match=oxm{in_port="1"}, insts=[apply{acts=[out{port="2"}]}]}

OK.

$ sudo dpctl unix:/tmp/s1 flow-mod cmd=add,table=0 in_port=2 apply:output:1
SENDING (xid=0xF0FF00F0):
flow_mod{table="0", cmd="add", cookie="0x0", mask="0x0", idle="0", hard="0", prio="32768", buf="none", port="any", group="any", flags="0x0", match=oxm{in_port="2"}, insts=[apply{acts=[out{port="1"}]}]}

OK.

$ sudo dpctl unix:/tmp/s1 stats-flow
SENDING (xid=0xF0FF00F0):
stat_req{type="flow", flags="0x0", table="all", oport="any", ogrp="any", cookie=0x0", mask=0x0", match=oxm{all match}}

RECEIVED (xid=0xF0FF00F0):
stat_repl{type="flow", flags="0x0", stats=[{table="0", match="oxm{in_port="1"}", dur_s="17", dur_ns="63000", prio="32768", idle_to="0", hard_to="0", cookie="0x0", pkt_cnt="0", byte_cnt="0", insts=[apply{acts=[out{port="2"}]}]}, {table="0", match="oxm{in_port="2"}", dur_s="12", dur_ns="357000", prio="32768", idle_to="0", hard_to="0", cookie="0x0", pkt_cnt="0", byte_cnt="0", insts=[apply{acts=[out{port="1"}]}]}]}
```

4. h1 will be the server and h2 will act as a client. Start iperf on the nodes.
```
root@vclv99-158:~# iperf -s -p 9990 -f k -i 1
------------------------------------------------------------
Server listening on TCP port 9990
TCP window size: 85.3 KByte (default)
------------------------------------------------------------
[ 13] local 10.0.0.1 port 9990 connected with 10.0.0.2 port 34359
[ ID] Interval       Transfer     Bandwidth
[ 13]  0.0- 1.0 sec  66.5 KBytes   544 Kbits/sec
[ 13]  1.0- 2.0 sec  26791 KBytes  219470 Kbits/sec
[ 13]  2.0- 3.0 sec  27277 KBytes  223455 Kbits/sec
[ 13]  3.0- 4.0 sec  27180 KBytes  222656 Kbits/sec
[ 13]  4.0- 5.0 sec  27212 KBytes  222922 Kbits/sec
[ 13]  5.0- 6.0 sec  27153 KBytes  222436 Kbits/sec
[ 13]  6.0- 7.0 sec  27201 KBytes  222830 Kbits/sec
[ 13]  7.0- 8.0 sec  27143 KBytes  222355 Kbits/sec
[ 13]  8.0- 9.0 sec  27219 KBytes  222980 Kbits/sec
[ 13]  9.0-10.0 sec  27181 KBytes  222668 Kbits/sec
[ 13] 10.0-11.0 sec  27300 KBytes  223641 Kbits/sec
[ 13] 11.0-12.0 sec  27240 KBytes  223154 Kbits/sec
[ 13] 12.0-13.0 sec  27250 KBytes  223235 Kbits/sec
[ 13] 13.0-14.0 sec  27267 KBytes  223374 Kbits/sec
[ 13] 14.0-15.0 sec  27303 KBytes  223664 Kbits/sec
[ 13] 15.0-16.0 sec  27231 KBytes  223073 Kbits/sec
[ 13] 16.0-17.0 sec  27307 KBytes  223699 Kbits/sec
[ 13] 17.0-18.0 sec  27243 KBytes  223177 Kbits/sec
[ 13] 18.0-19.0 sec  27270 KBytes  223397 Kbits/sec
[ 13] 19.0-20.0 sec  27232 KBytes  223085 Kbits/sec
[ 13] 20.0-21.0 sec  27289 KBytes  223548 Kbits/sec
[ 13] 21.0-22.0 sec  27240 KBytes  223154 Kbits/sec
[ 13] 22.0-23.0 sec  27290 KBytes  223560 Kbits/sec
[ 13] 23.0-24.0 sec  27330 KBytes  223884 Kbits/sec
[ 13] 24.0-25.0 sec  27327 KBytes  223861 Kbits/sec
[ 13] 25.0-26.0 sec  27303 KBytes  223664 Kbits/sec
[ 13] 26.0-27.0 sec  27298 KBytes  223629 Kbits/sec
[ 13] 27.0-28.0 sec  27202 KBytes  222841 Kbits/sec
[ 13] 28.0-29.0 sec  27218 KBytes  222969 Kbits/sec
[ 13] 29.0-30.0 sec  27204 KBytes  222853 Kbits/sec
[ 13]  0.0-30.0 sec  790016 KBytes  215637 Kbits/sec


root@vclv99-158:~# iperf -c 10.0.0.1 -p 9990 -f k -i 1 -t 30
------------------------------------------------------------
Client connecting to 10.0.0.1, TCP port 9990
TCP window size: 85.3 KByte (default)
------------------------------------------------------------
[ 12] local 10.0.0.2 port 34359 connected with 10.0.0.1 port 9990
[ ID] Interval       Transfer     Bandwidth
[ 12]  0.0- 1.0 sec   256 KBytes  2097 Kbits/sec
[ 12]  1.0- 2.0 sec  26752 KBytes  219152 Kbits/sec
[ 12]  2.0- 3.0 sec  27264 KBytes  223347 Kbits/sec
[ 12]  3.0- 4.0 sec  27136 KBytes  222298 Kbits/sec
[ 12]  4.0- 5.0 sec  27264 KBytes  223347 Kbits/sec
[ 12]  5.0- 6.0 sec  27136 KBytes  222298 Kbits/sec
[ 12]  6.0- 7.0 sec  27136 KBytes  222298 Kbits/sec
[ 12]  7.0- 8.0 sec  27136 KBytes  222298 Kbits/sec
[ 12]  8.0- 9.0 sec  27264 KBytes  223347 Kbits/sec
[ 12]  9.0-10.0 sec  27136 KBytes  222298 Kbits/sec
[ 12] 10.0-11.0 sec  27392 KBytes  224395 Kbits/sec
[ 12] 11.0-12.0 sec  27136 KBytes  222298 Kbits/sec
[ 12] 12.0-13.0 sec  27264 KBytes  223347 Kbits/sec
[ 12] 13.0-14.0 sec  27264 KBytes  223347 Kbits/sec
[ 12] 14.0-15.0 sec  27264 KBytes  223347 Kbits/sec
[ 12] 15.0-16.0 sec  27264 KBytes  223347 Kbits/sec
[ 12] 16.0-17.0 sec  27392 KBytes  224395 Kbits/sec
[ 12] 17.0-18.0 sec  27264 KBytes  223347 Kbits/sec
[ 12] 18.0-19.0 sec  27136 KBytes  222298 Kbits/sec
[ 12] 19.0-20.0 sec  27264 KBytes  223347 Kbits/sec
[ 12] 20.0-21.0 sec  27392 KBytes  224395 Kbits/sec
[ 12] 21.0-22.0 sec  27136 KBytes  222298 Kbits/sec
[ 12] 22.0-23.0 sec  27264 KBytes  223347 Kbits/sec
[ 12] 23.0-24.0 sec  27392 KBytes  224395 Kbits/sec
[ 12] 24.0-25.0 sec  27392 KBytes  224395 Kbits/sec
[ 12] 25.0-26.0 sec  27264 KBytes  223347 Kbits/sec
[ 12] 26.0-27.0 sec  27264 KBytes  223347 Kbits/sec
[ 12] 27.0-28.0 sec  27264 KBytes  223347 Kbits/sec
[ 12] 28.0-29.0 sec  27136 KBytes  222298 Kbits/sec
[ 12] 29.0-30.0 sec  27264 KBytes  223347 Kbits/sec
[ 12]  0.0-30.0 sec  790016 KBytes  215672 Kbits/sec
```

5. Check the flow stats on the switch. The counters should be updated.
```
root@vclv99-158:~# dpctl dump-flows unix:/tmp/s1
stats_reply (xid=0x486f2fb3): flags=none type=1(flow)
   cookie=0, duration_sec=1065s, duration_nsec=179000000s, table_id=1, priority=32768, n_packets=640716, n_bytes=970264590, idle_timeout=0,hard_timeout=0,in_port=2,actions=output:1
   cookie=0, duration_sec=1089s, duration_nsec=963000000s, table_id=1, priority=32768, n_packets=560307, n_bytes=40822238, idle_timeout=0,hard_timeout=0,in_port=1,actions=output:2
```

*******************************************************************************

