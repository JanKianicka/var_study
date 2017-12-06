#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdint.h>
#include <amqp_tcp_socket.h>
#include <amqp.h>
#include <amqp_framing.h>

#include "utils.h"

char *usage = "Usage: 192.168.50.129 5672 guest guest dacs4Exchange DFXRoutingkey \"Interval 1\" tx_commit/tx_rollback\n";

int main(int argc, char const *const *argv)
{
  char const *hostname;
  int port, status;
  char const *user;
  char const *password;
  char const *exchange;
  char const *routingkey;
  char const *messagebody;
  char const *tx_trans;

  amqp_socket_t *socket = NULL;
  amqp_connection_state_t conn;

  if (argc < 9) {
    fprintf(stderr, "Usage: tis_poc_sender host port user password exchange routingkey messagebody commit/rollback\n");
    fprintf(stderr, usage);
    return 1;
  }

  hostname 	= argv[1];
  port 		= atoi(argv[2]);
  user		= argv[3];
  password	= argv[4];
  exchange 	= argv[5];
  routingkey = argv[6];
  messagebody = argv[7];
  tx_trans	= argv[8];

  printf("hostname: %s \n", hostname);
  printf("port: %d \n", port);
  printf("exchange: %s \n", exchange);
  printf("routingkey: %s \n", routingkey);
  printf("messagebody: %s \n", messagebody);

  conn = amqp_new_connection();

  socket = amqp_tcp_socket_new(conn);
  if (!socket) {
    die("creating TCP socket");
  }

  status = amqp_socket_open(socket, hostname, port);
  if (status) {
    die("opening TCP socket");
  }

  die_on_amqp_error(amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, user, password),
                    "Logging in");
  amqp_channel_open(conn, 1);
  die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");

  amqp_tx_select(conn, 1);

  {
    amqp_basic_properties_t props;
    props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
    props.content_type = amqp_cstring_bytes("text/plain");
    props.delivery_mode = 2; /* persistent delivery mode */
    die_on_error(amqp_basic_publish(conn,
                                    1,
                                    amqp_cstring_bytes(exchange),
                                    amqp_cstring_bytes(routingkey),
                                    0,
                                    0,
                                    &props,
                                    amqp_cstring_bytes(messagebody)),
                 "Publishing");
  }

  printf("%s\n",tx_trans);
  if (strcmp(tx_trans,"tx_commit")==0){

	  amqp_tx_commit(conn, 1);
  }
  else{
	  amqp_tx_rollback(conn, 1);
  }

  die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
  die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
  die_on_error(amqp_destroy_connection(conn), "Ending connection");
  printf("End of procedure.\n");
  return 0;

}
