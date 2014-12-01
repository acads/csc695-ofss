/* 
 * Module:  udp_echo_server.c
 * Desc:    A simple UDP echo server
 *
 * Author:  Aravindhan Dhanasekaran <adhanas@ncsu.edu>
 */

#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* Constants */
#define BUF_SIZE    512

/* Globals */
int g_serv_sock = 0;    /* server socket */

void error(char *msg) {
  perror(msg);
  exit(1);
}

static void
handle_cleanup(void)
{
    close(g_serv_sock);
    return;
}

static void
handle_signals(int signum)
{
    switch (signum) {
    case SIGPIPE:
        printf("ERROR: Received SIGPIPE.. exiting now\n");
        handle_cleanup();
        break;

    default:
        break;
    }
    return;
}

static void
print_usage(char *prog_name)
{
    printf("Usage: %s <Server-Listen-Port>\n", prog_name);
    return;
}

int
main(int argc, char **argv) {
    int                 opt = 0;
    int                 nbytes = 0;
    int                 cli_len = 0;
    char                buf[BUF_SIZE] = "";
    struct sockaddr_in  serv_addr;
    struct sockaddr_in  cli_addr;
    struct hostent      *cli_host;

    if (2 != argc) {
        printf("ERROR: Incorrect usage. See help.\n");
        print_usage(argv[0]);
        goto error_exit;
    }
    signal(SIGPIPE, handle_signals);

    /* Create server socket. */
    g_serv_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (g_serv_sock < 0) {
        error("ERROR: socket failed");
        goto error_exit;
    }

    /* Set sockopt to resue socket imm'ly after the process quits. */
    opt = 1;
    setsockopt(g_serv_sock, SOL_SOCKET, SO_REUSEADDR, 
            (const void *) &opt , sizeof(int));

    /* Fill-in server details. */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    /* Bind the socket to the addr. */
    if (bind(g_serv_sock, (struct sockaddr *) &serv_addr,
                sizeof(serv_addr)) < 0) {
        perror("ERROR: bind failed on binding");
        goto error_exit;
    }

    /* Data transfer starts here. */
    cli_len = sizeof(cli_addr);
    printf("Waiting for clients to connect..\n");
    while (1) {
        nbytes = 0;
        memset(&buf, 0, sizeof(buf));
        nbytes = recvfrom(g_serv_sock, buf, sizeof(buf), 0,
                (struct sockaddr *) &cli_addr, &cli_len);
        if (nbytes < 0) {
            perror("ERROR: recvfrom failed");
            goto error_exit;
        }
        buf[nbytes] = '\0';
        printf("CLIENT: %s", buf);

        /* Echo the data back to client. */
        nbytes = sendto(g_serv_sock, buf, strlen(buf), 0, 
	       (struct sockaddr *) &cli_addr, cli_len);
        if (nbytes < 0) {
            perror("ERROR: sendto failed");
            goto error_exit;
        }
    }

    handle_cleanup();
    return 0;

error_exit:
    handle_cleanup();
    return -1;
}

