#
# Module: Makefile
# 
# Description: Makefile to build TCP/UDP server and client.
#
# Author: Aravindhan Dhanasekaran <adhanas@ncsu.edu>
#

TS = tserver
TC = tclient
US = userver
UC = uclient

TS_SRCS = tcp_echo_server.c
TC_SRCS = tcp_echo_client.c
US_SRCS = udp_echo_server.c
UC_SRCS = udp_echo_client.c
TS_OBJS = tcp_echo_server.o
TC_OBJS = tcp_echo_client.o
US_OBJS = udp_echo_server.o
UC_OBJS = udp_echo_client.o
CLEAN_FILES = $(TS_OBJS) $(TC_OBJS) $(US_OBJS) $(UC_OBJS)
#CLEAN_FILES = $(TS) $(TC) $(US) $(UC) $(TS_OBJS) $(TC_OBJS) $(US_OBJS) $(UC_OBJS)

CC = gcc
DEBUG = -g
OPTIMIZER = -O5
WARN = -Wno-unused-but-set-variable -Wall
CFLAGS = -c -Wall $(DEBUG) $(WARN) $(OPTIMIZER)
LFLAGS = -Wall $(DEBUG) $(WARN) $(OPTIMIZER) $(INCLS)

all: $(TS) $(TC) $(US) $(UC)

$(TS): $(TS_OBJS)
	$(CC) $(LFLAGS) -o $(TS) $(TS_OBJS)

$(TC): $(TC_OBJS)
	$(CC) $(LFLAGS) -o $(TC) $(TC_OBJS)

$(TS_OBJS): $(TS_SRCS)
	$(CC) $(CFLAGS) -c $(TS_SRCS)

$(TC_OBJS): $(TC_SRCS)
	$(CC) $(CFLAGS) -c $(TC_SRCS)

$(US): $(US_OBJS)
	$(CC) $(LFLAGS) -o $(US) $(US_OBJS)

$(UC): $(UC_OBJS)
	$(CC) $(LFLAGS) -o $(UC) $(UC_OBJS)

$(US_OBJS): $(US_SRCS)
	$(CC) $(CFLAGS) -c $(US_SRCS)

$(UC_OBJS): $(UC_SRCS)
	$(CC) $(CFLAGS) -c $(UC_SRCS)


clean:
	\rm -f $(CLEAN_FILES)

