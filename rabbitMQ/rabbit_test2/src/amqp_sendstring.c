/* vim:set ft=c ts=2 sw=2 sts=2 et cindent: */
/*
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MIT
 *
 * Portions created by Alan Antonuk are Copyright (c) 2012-2013
 * Alan Antonuk. All Rights Reserved.
 *
 * Portions created by VMware are Copyright (c) 2007-2012 VMware, Inc.
 * All Rights Reserved.
 *
 * Portions created by Tony Garnock-Jones are Copyright (c) 2009-2010
 * VMware, Inc. and Tony Garnock-Jones. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * ***** END LICENSE BLOCK *****
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#include <amqp_tcp_socket.h>
#include <amqp.h>
#include <amqp_framing.h>

#include "utils.h"

/*#define NORMALSOCKET 1*/
/*#define AMQPSOCKET 1*/

int main(int argc, char const *const *argv)
{
  char const *hostname;
  int port, status;
  char const *vhost;
  char const *user;
  char const *password;
  char const *exchange;
  char const *routingkey;
  char const *messagebody;
  amqp_socket_t *our_amqp_socket = NULL;
  int value_our_amqp_socket;
  amqp_connection_state_t conn;
  amqp_rpc_reply_t rpc_reply;

  /* socket variables */
  int s;
  int optval;
  socklen_t optlen = sizeof(optval);
  int keepcnt=1;
  int keepcnt_ret=0;
  int keepcnt_ret2=0;
  int keepidle_ret2=0;
  int keepintvl_ret2=0;

  int numrepeat;
  int delay=5;

  if (argc < 10) {
    fprintf(stderr, "Usage: amqp_sendstring host port vhost user password exchange routingkey messagebody numberrepeat\n");
    return 1;
  }

  hostname = argv[1];
  port = atoi(argv[2]);
  vhost = argv[3];
  user  = argv[4];
  password = argv[5];
  exchange = argv[6];
  routingkey = argv[7];
  messagebody = argv[8];
  numrepeat = atoi(argv[9]);


  conn = amqp_new_connection();

  our_amqp_socket = amqp_tcp_socket_new(conn);
  if (!our_amqp_socket) {
    die("creating TCP socket");
  }

#if NORMALSOCKET
  /* Creating normal ordinary socket */
  s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  /* Check the status for the keepalive option */
  if(getsockopt(s, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
     perror("getsockopt()");
     close(s);
     exit(EXIT_FAILURE);
  }
  printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));

  /* Set the option active */
	optval = 1;
	optlen = sizeof(optval);
	if(setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
	perror("setsockopt()");
	close(s);
	exit(EXIT_FAILURE);
	}
	printf("SO_KEEPALIVE set on socket\n");

	/* Check the status again */
	if(getsockopt(s, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
	perror("getsockopt()");
	close(s);
	exit(EXIT_FAILURE);
	}
	printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));


	getsockopt(s, IPPROTO_TCP, TCP_KEEPCNT, &keepcnt_ret, &optlen);
	printf("TCP_KEEPCNT is %d\n", keepcnt_ret);
#endif

  status = amqp_socket_open(our_amqp_socket, hostname, port);
  if (status) {
    die("opening TCP socket");
  }

#if AMQPSOCKET
  /* Keep alive settings for our amqp socket  */
  value_our_amqp_socket = amqp_get_sockfd(conn);



  printf("Value of our amqp socket (amqp_get_sockfd): %d \n", value_our_amqp_socket);

  value_our_amqp_socket = amqp_socket_get_sockfd(our_amqp_socket);
  printf("Value of our amqp socket (amqp_socket_get_sockfd): %d \n", value_our_amqp_socket);

  /* This does not work, there is wrong argument and does not return real values */
  getsockopt(value_our_amqp_socket, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen);
  printf("SO_KEEPALIVE for our_amqp_socket is %s\n", (optval ? "ON" : "OFF"));

  optval = 1;
  optlen = sizeof(optval);
  setsockopt(value_our_amqp_socket, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen);
  printf("SO_KEEPALIVE for our_amqp_socket is %s\n", (optval ? "ON" : "OFF"));

  getsockopt(value_our_amqp_socket, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen);
  printf("SO_KEEPALIVE for our_amqp_socket is %s\n", (optval ? "ON" : "OFF"));

  getsockopt(value_our_amqp_socket, IPPROTO_TCP, TCP_KEEPCNT, &keepcnt_ret2, &optlen);
  getsockopt(value_our_amqp_socket, IPPROTO_TCP, TCP_KEEPIDLE, &keepidle_ret2, &optlen);
  getsockopt(value_our_amqp_socket, IPPROTO_TCP, TCP_KEEPINTVL, &keepintvl_ret2, &optlen);

  setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE, &keepidle, sizeof(int));
  setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL, &keepintvl, sizeof(int));
  printf("TCP_KEEPCNT for our_amqp_socket is %d\n", keepcnt_ret2);
  printf("TCP_KEEPIDLE for our_amqp_socket is %d\n", keepidle_ret2);
  printf("TCP_KEEPINTVL for our_amqp_socket is %d\n", keepintvl_ret2);
  int keepidle_new = 10;
  int keepcnt_new  = 5;
  int keepintvl_new = 10;
  setsockopt(value_our_amqp_socket, IPPROTO_TCP, TCP_KEEPIDLE, &keepidle_new, sizeof(int));
  setsockopt(value_our_amqp_socket, IPPROTO_TCP, TCP_KEEPCNT, &keepcnt_new, sizeof(int));
  setsockopt(value_our_amqp_socket, IPPROTO_TCP, TCP_KEEPINTVL, &keepintvl_new, sizeof(int));

  getsockopt(value_our_amqp_socket, IPPROTO_TCP, TCP_KEEPCNT, &keepcnt_ret2, &optlen);
  getsockopt(value_our_amqp_socket, IPPROTO_TCP, TCP_KEEPIDLE, &keepidle_ret2, &optlen);
  getsockopt(value_our_amqp_socket, IPPROTO_TCP, TCP_KEEPINTVL, &keepintvl_ret2, &optlen);

  printf("TCP_KEEPCNT after reset for our_amqp_socket is %d\n", keepcnt_ret2);
  printf("TCP_KEEPIDLE after reset for our_amqp_socket is %d\n", keepidle_ret2);
  printf("TCP_KEEPINTVL after reset for our_amqp_socket is %d\n", keepintvl_ret2);

 #endif

  die_on_amqp_error(amqp_login(conn, vhost, 0, 131072, 5, AMQP_SASL_METHOD_PLAIN, "guest", "guest"),
                    "Logging in");
  amqp_channel_open(conn, 1);
  die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");

  int i;
  int return_code = -20;
  int frame_return = -10;
  amqp_frame_t frame;
  struct timeval waitTime;
  amqp_tx_commit_ok_t *commit_ret;
  waitTime.tv_sec = 0.5;
  waitTime.tv_usec = 0;


  {
    amqp_basic_properties_t props;
    props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
    props.content_type = amqp_cstring_bytes("text/plain");
    props.delivery_mode = 2; /* persistent delivery mode */
    printf("Publishing\n");

    amqp_tx_select(conn, 1);
    for(i=0; i<numrepeat;i++){
		return_code = amqp_basic_publish(conn,
											1,
											amqp_cstring_bytes(exchange),
											amqp_cstring_bytes(routingkey),
											0,
											0,
											&props,
											amqp_cstring_bytes(messagebody));
		printf("return code of publish: %d \n", return_code);
		commit_ret = amqp_tx_commit(conn, 1);
		rpc_reply = amqp_get_rpc_reply(conn);
		printf("rpc_reply.library_error: %d \n", rpc_reply.library_error);
		printf("rpc_reply.reply_type:%d \n", rpc_reply.reply_type);
		printf("rpc_reply.reply.id: %d \n", rpc_reply.reply.id);

		printf("AMQP_RESPONSE_LIBRARY_EXCEPTION: %d \n",AMQP_RESPONSE_LIBRARY_EXCEPTION);
		printf("%s \n",amqp_error_string2(rpc_reply.library_error));

		if(commit_ret == NULL)
			printf("commit_ret is NULL \n");
		else
			printf("commit_ret is not NULL \n");

    frame_return = amqp_simple_wait_frame_noblock(conn, &frame, &waitTime);

    printf("return code of frames: %d \n", frame_return);
    printf("Frame type: %d \n", frame.frame_type);
    if(AMQP_BASIC_RETURN_METHOD == frame.payload.method.id){
    	printf("AMQP_BASIC_RETURN_METHOD \n");
    }
    printf("Frame method returned: %d \n", frame.payload.method.id);
    printf("\n\n\n");
    sleep(delay);
    }
  }
  sleep(delay);
  die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
  die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
  die_on_error(amqp_destroy_connection(conn), "Ending connection");
  return 0;
}

