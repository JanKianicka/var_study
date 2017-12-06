#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdint.h>
#include <amqp_tcp_socket.h>
#include <amqp.h>
#include <amqp_framing.h>

#include <assert.h>

#include "utils.h"

int main(int argc, char const *const *argv)
{
  char const *hostname;
  int port, status;
  char const *queuename;
  char const *user;
  char const *password;
  char const *exchange;
  char const *routingkey;
  char *messagebody;
  amqp_socket_t *socket = NULL;
  amqp_connection_state_t conn;

  if (argc < 8) {
    fprintf(stderr, "Usage: amqp_listenq host port user password source_queue target_exchange routingkey \n");
    return 1;
  }

  hostname = argv[1];
  port = atoi(argv[2]);
  user = argv[3];
  password = argv[4];
  queuename = argv[5];
  exchange	= argv[6];
  routingkey	= argv[7];

  printf("hostname: %s \n", hostname);
  printf("port: %d \n", port);
  printf("user: %s \n", user);
  printf("password: %s \n", password);
  printf("exchange: %s \n", exchange);
  printf("routingkey: %s \n", routingkey);

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

  /* limit prefetched size to one message only. */
  amqp_basic_qos(conn, 1, 0, 1, 0);

  amqp_basic_consume(conn, 1, amqp_cstring_bytes(queuename), amqp_empty_bytes, 0, 0, 0, amqp_empty_table);
    die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming");

    {
      while (1) {
        amqp_rpc_reply_t res;
        amqp_envelope_t envelope;

        amqp_maybe_release_buffers(conn);

        res = amqp_consume_message(conn, &envelope, NULL, 0);

        if (AMQP_RESPONSE_NORMAL != res.reply_type) {
          break;
        }

        printf("Delivery %u, exchange %.*s routingkey %.*s\n",
               (unsigned) envelope.delivery_tag,
               (int) envelope.exchange.len, (char *) envelope.exchange.bytes,
               (int) envelope.routing_key.len, (char *) envelope.routing_key.bytes);

        if (envelope.message.properties._flags & AMQP_BASIC_CONTENT_TYPE_FLAG) {
          printf("Content-type: %.*s\n",
                 (int) envelope.message.properties.content_type.len,
                 (char *) envelope.message.properties.content_type.bytes);
          printf("Message-id: %.*s\n",
                           (int) envelope.message.properties.message_id.len,
                           (char *) envelope.message.properties.message_id.bytes);

      	amqp_dump(envelope.message.body.bytes,
      			envelope.message.body.len);
        }
        messagebody = malloc((envelope.message.body.len+1)*sizeof(char));

        memcpy(messagebody, envelope.message.body.bytes,
        		envelope.message.body.len);
        messagebody[envelope.message.body.len] = '\0';
        printf("messagebody: %s\n", messagebody);

        fflush(stdout);

        printf("Processing message: ...\n");
        fflush(stdout);
        sleep(10);
        printf("Done\n");
        fflush(stdout);

        amqp_basic_ack(conn, 1, envelope.delivery_tag, 0);

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
                                          //amqp_cstring_bytes(envelope.message.body.bytes)),

                       "Publishing");
        }

        amqp_destroy_envelope(&envelope);
        free(messagebody);
      }/* while(1)*/
    }
    die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
    die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
    die_on_error(amqp_destroy_connection(conn), "Ending connection");

    return 0;
  }
