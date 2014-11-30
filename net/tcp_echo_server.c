/*
 * Module:  tcp_echo_server.c
 * Desc:    Simple TCP echo server.
 *
 * Author:  Aravindhan Dhanasekaran <adhanas@ncsu.edu>
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE        512
#define NUM_CLIENTS     1

int g_serv_sock = 0;
int g_conn_sock = 0;

static void
handle_cleanup(void)
{
    close(g_conn_sock);
    close(g_serv_sock);
    exit(0);
}

static void
handle_signals(int signum)
{
    switch (signum) {
    case SIGPIPE:
        printf("ERROR: Received SIGPIPE.. exiting now.\n");
        handle_cleanup();
        exit(-1);

    default:
        break;
    }

    return;
}

static void
print_usage(const char *prog_name)
{
    printf("Usage: %s <Server-Listen-Port>\n", prog_name);
    return;
}

int
main(int argc, char **argv)
{
    uint32_t            nbytes = 0;
    char                buf[BUF_SIZE + 1] = "";
    struct sockaddr_in  serv_addr;

    if (2 != argc) {
        printf("ERROR: Incorrect usage. See help.\n");
        print_usage(argv[0]);
        goto error_exit;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));

    /* Register signal handlers */
    signal(SIGPIPE, handle_signals);

    /* Create server listening socket */
    if (-1 == (g_serv_sock = socket(AF_INET, SOCK_STREAM, 0))) {
        perror("ERROR: socket failed");
        goto error_exit;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    /* Bind the listener socket */
    if (bind(g_serv_sock, (struct sockaddr *) &serv_addr, 
                sizeof(serv_addr)) < 0) {
        perror("ERROR: bind failed");
        goto error_exit;
    }

    /* Now, wait for clients to connect. */
    if (listen(g_serv_sock, NUM_CLIENTS) < 0) {
        perror("ERROR: listen failed");
        goto error_exit;
    }
    printf("Waiting for clients to connect..\n");

    /* A client has been connected. */
    while (1) {
        if (-1 == (g_conn_sock = accept(g_serv_sock, NULL, NULL))) {
            perror("ERROR: accept failed");
            goto error_exit;
        }
        printf("CLIENT connected..\n");

        while (1) {
            if (-1 == (nbytes = recv(g_conn_sock, buf, BUF_SIZE, 0))) {
                perror("ERROR: recv failed");
                goto error_exit;
            }
            buf[nbytes] = '\0';
            printf("CLIENT: %s\n", buf);

            if (-1 == (send(g_conn_sock, buf, BUF_SIZE, 0))) {
                perror("ERROR: send failed");
                goto error_exit;
            }

            nbytes = 0;
            memset(&buf, 0, sizeof(buf));
        }
    }

    handle_cleanup();
    return 0;

error_exit:
    handle_cleanup();
    exit(-1);
}

