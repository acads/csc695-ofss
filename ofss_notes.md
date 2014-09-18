OpenFlow Soft Switch - Dev Notes
================================
This dev notes should be helpful to browse the source code of ofsoftswitch13 
while develpoment.


Datapath Design
==============
This is verbatim text from the email sent by Zoltan Lajos, Ericsson Research.

----------------Email Snip Start----------------
```
The switch is using regular packet/raw sockets. See this for an explanation: 
http://yusufonlinux.blogspot.hu/2010/11/data-link-access-and-zero-copy.html. 
This is essentially similar to using the libpcap library. But we already got 
this code (from the 1.0 switch), so we sticked with it. The netbee library is 
only used for parsing the packets: we give it a packet, it gives us back the 
list of fields/values in it; it is not used for the actual packet 
capture/sending.

The port creation in the in switch this is implemented here: 
https://github.com/CPqD/ofsoftswitch13/blob/master/lib/netdev.c#L720, the only 
difference is that in the switch we originally wanted to have an abstraction 
on top of native ports, that's why everything is being converted to the 
"netdev" structure. But under the hood these are just simple linux sockets.

Once the ports are up the switch goes into an infinite loop here: 
https://github.com/CPqD/ofsoftswitch13/blob/master/udatapath/udatapath.c#L177. 
This periodically calls dp_run, which in turn calls dp_ports_run: 
https://github.com/CPqD/ofsoftswitch13/blob/master/udatapath/datapath.c#L199. 
In this function we iterate over ports, and for each call the poll function: 
https://github.com/CPqD/ofsoftswitch13/blob/master/udatapath/dp_ports.c#L275. 
Again, netdev is just an abstraction on top of regular linux sockets, so here 
we simply call the recvfrom system function: 
https://github.com/CPqD/ofsoftswitch13/blob/master/lib/netdev.c#L976

By now we have the raw packet in a simple byte buffer (ofpbuf structure). If 
you follow the chain of calls, we will eventually call the packet_create 
function, to wrap this buffer with a packet structure that contains all the 
metadata. This calls into packet_handle_std_create, which in turn calls 
nblink_packet_parse to parse the packet for us: 
https://github.com/CPqD/ofsoftswitch13/blob/master/udatapath/packet_handle_std.c#L62

When this is all finished, we have received the packet from a port, parsed it, 
and created a packet structure that contains the original packet and the 
metadata fields. Then this is passed to the pipeline_process_packet function 
(https://github.com/CPqD/ofsoftswitch13/blob/master/udatapath/dp_ports.c#L225), 
which is basically all the OpenFlow magic...
```
----------------Email Snip End----------------


Main Functions
==============
```
ofsoftswitch13-master/utilities/dpctl.c
    Most of the functionality of the dpctl utility is implemented in this file.

    parse_match
    Parses the incoming flow mod args in dpctl and puts them in a ofl_match 
    structure as OXM TLVs

    flow_mod
    Handles the flow-mod command in dpctl. Prepares the ofl_msg_flow_mod msg 
    and sends it over the vconn.


    
ofsoftswitch13-master/udatapath/pipeline.c
    Most of the datapath implementation is contained within this file.

    pipeline_handle_flow_mod
    Called in ofss upon receiving a flow_mod msg. Validates the action set
    and installs a flow in the flow table.

    flow_entry_create
    Processes the flow_mod message and returns a flow_entry entry which is
    then inserted into the flow table.


    pipeline_process_packet
    The datapath pipeline starts here. The netdev recveives a packet from one
    of the many dp ports and does some initial processing. It then adds bunch
    of metatdata on top of the received packet and the final packet is
    handed over to this function. It's responsible to initiate pipeline
    processing (i.e., table lookups) for the received packet.

```


Main Data Structures
====================
```
struct ofl_msg_flow_mod
    Represents the flow_mod message. It contains the msg header, cookie, idle
    & hard timeouts, priority, match fields and instructions.

struct flow_table
    Represents the flow table. It's present in every table. It contains the
    table features, statistics, a list for match, hard and idle entries. 
    i.e., the flows are classified into 3 categories: idle, hard and regular
    match entries. This facilitates correct aging.

struct flow_entry
    Represents the actual flow. It contains pointers to the dp, table, stats, 
    instructions and match fields.

```