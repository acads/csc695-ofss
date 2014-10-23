flow-mod processing
===================
This document explains how a flow-mod msg is received, processed and installed
in a flow table in ofss datapath.

Extracting match paramters from flow_mod
----------------------------------------
The below chain of functions are used to extract the flow match data from a 
flow_mod request.

remote_rconn_run @ udatapath/datapath.c
    Peridically the control channel (rconn) is cheked for msgs.

ofl_msg_unpack @ oflib/ofl-messages-unpack.c
    All rxd msgs on rconn will be first unpacked here.

ofl_msg_unpack_flow_mod @ oflib/ofl-messages-unpack.c
    Unpack routine for flow-mod msgs. New buffer is allocated to store the 
    flow-mod details on the dp from the incoming msg.

ofl_structs_match_unpack @ oflib/ofl-structs-unpack.c
    
ofl_structs_oxm_match_unpack oflib/ofl-structs-unpack.c
oxm_pull_match @ oflib/oxm-match.c
parse_oxm_entry @ oflib/oxm-match.c

Installing a flow
------------------
remote_rconn_run @ udatapath/datapath.c
handle_control_msg @ udatapath/dp_control.c
pipeline_handle_flow_mod @ udatapath/pipeline.c
flow_table_flow_mod @ udatapath/flow_table.c
flow_table_add @ udatapath/flow_table.c
flow_entry_create @ udatapath/flow_entry.c

