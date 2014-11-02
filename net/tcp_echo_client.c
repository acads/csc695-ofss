/*
 * Simple echo TCP client.
 *
 * Author: Aravindhan Dhanasekaran <adhanas@ncsu.edu>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE    512

const char *g_quit_msg = "quit";

static void
print_usage(const char *prog_name)
{
    printf("Usage: %s <Server-Name> <Server-Listen-Port>\n", prog_name);
    return;
}

int
main(int argc, char **argv)
{
    int                 cli_sock = 0;
    int                 serv_sock = 0;
    uint16_t            quit_msg_len = 0;
    uint32_t            nbytes = 0;
    char                buf[BUF_SIZE + 1] = "";
    struct hostent      *serv_entry = NULL;
    struct sockaddr_in  serv_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));

    if (3 != argc) {
        printf("ERROR: Incorrect usage. See usage help.\n");
        print_usage(argv[0]);
        goto error_exit;
    }

    quit_msg_len = strlen(g_quit_msg);

    /* Create client-side TCP socket */
    if (-1 == (cli_sock = socket(AF_INET, SOCK_STREAM, 0))) {
        perror("ERROR: Socket creation failed");
        goto error_exit;
    }

    /* Fill in server address/port data */
    if (NULL == (serv_entry = gethostbyname(argv[1]))) {
        perror("ERROR: gethostbyname failed");
        goto error_exit;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr = *((struct in_addr *) serv_entry->h_addr);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (-1 == (serv_sock = connect(cli_sock, (struct sockaddr*) &serv_addr,
                    sizeof(serv_addr)))) {
        perror("ERROR: connect failed");
        goto error_exit;

    } else {
        printf("Sucessfully connected to server socket %d.\n", serv_sock);
    }

    while (1) {
        printf("YOU: ");
        fgets(buf, BUF_SIZE, stdin);
        buf[strlen(buf) - 1] = '\0';

        if (!strncmp(buf, g_quit_msg, quit_msg_len))
            break;

        if (-1 == (nbytes = send(cli_sock, buf, BUF_SIZE, 0))) {
            perror("ERROR: send failed");
            goto error_exit;
        }
        nbytes = 0;
        memset(&buf, 0, sizeof(buf));

        if (-1 == (nbytes = recv(cli_sock, buf, BUF_SIZE, 0))) {
            perror("ERROR: recv failed");
            goto error_exit;
        }
        buf[nbytes] = '\0';
        printf("SERVER: %s\n", buf);
        
        nbytes = 0;
        memset(&buf, 0, sizeof(buf));
    }

    close(cli_sock);

    return 0;

error_exit:
    exit(-1);
}

