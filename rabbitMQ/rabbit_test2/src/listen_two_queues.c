#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdint.h>
#include <amqp_tcp_socket.h>
#include <amqp.h>
#include <amqp_framing.h>

#include <assert.h>

#include "utils.h"

// amqp_connection_state_t conn;

int main(int argc, char const *const *argv)
{
  char const *hostname;
  char const *vhost;
  int port, status;
  int channel=1;
  char const *queuename1;
  char const *queuename2;
  char const *user;
  char const *password;
  char *messagebody;
  char const *exchange;
  char const *dbRabbitQueue;
  char const *staProQueue;

//  amqp_socket_t *socket = NULL;
  amqp_connection_state_t conn;
  int reconnectAttempts = 3;
  int reconnectAttempt  = 1;
  int sleepTime = 8;
  int connReestablished = 0;

  amqp_rpc_reply_t res;
  amqp_envelope_t envelope;
  amqp_basic_properties_t props;

  if (argc < 11) {
    fprintf(stderr, "Usage: listen_two_queues host port vhost user password source_queue1 source_queue2 exchange db_rabbit_queue StaProqueue\n");
    return 1;
  }

  hostname = argv[1];
  port = atoi(argv[2]);
  vhost = argv[3];
  user = argv[4];
  password = argv[5];
  queuename1 = argv[6];
  queuename2 = argv[7];
  exchange 	 = argv[8];
  dbRabbitQueue = argv[9];
  staProQueue   = argv[10];

  /* auxiliary variables */
  int return_code = -20;

  /* protype control variables */
  int DFX_update_IPC_error = 0;
  int Interval_IPC_error   = 0;

  printf("hostname: %s \n", hostname);
  printf("port: %d \n", port);
  printf("vhost: %s \n",vhost);
  printf("user: %s \n", user);
  printf("password: %s \n", password);
  printf("queuename1: %s \n", queuename1);
  printf("queuename2: %s \n", queuename2);
  printf("exchange: %s \n", exchange);
  printf("dbRabbitQueue: %s \n", dbRabbitQueue);
  printf("staProQueue: %s \n", staProQueue);

  /* There is exit in connection opening, thus status is not handled here */
  status = createConnChannel(hostname, port, vhost, channel, user, password, &conn);

  /* limit prefetched size to one message only. */
  amqp_basic_qos(conn, channel, 0, 1, 0);

//  struct timeval *tv;
//  tv[0].tv_sec = 10;
//  tv[0].tv_usec = 0;
  // First thinking about setting up x-priority for the client. It was not compiled yet.

//  amqp_table_t queue_table;
//  amqp_table_entry_t  entry;
//  entry.key = amqp_cstring_bytes("x-priority");
//  entry.value.kind =  AMQP_FIELD_KIND_U32;
//  entry.value.value.u32 = 1;
//  queue_table.num_entries = 1;
//  queue_table.entries = &entry;

//  printf("queue2 %.*s", (char *) queue_table.entries->key.bytes);
//  printf(": %d \n", queue_table.entries->value.value);
  // Unfortunately when queue_table was used in amqp_basic_consume it did not work - socket error occurred.
//  queue_table = malloc(1*sizeof(amqp_table_t));
//  queue_table.num_entries = 1;
//  queue_table.entries[0].key = "x-priority";
//  queue_table.entries[0].value.kind = AMQP_FIELD_KIND_U8;
//  queue_table.entries[0].value.value = 1;

//  amqp_bytes_t encoded;
//  amqp_encode_table(encoded, amqp_empty_table);
  amqp_basic_consume(conn, channel, amqp_cstring_bytes(queuename1), amqp_empty_bytes, 0, 0, 0, amqp_empty_table);
  die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming");

  //amqp_basic_consume(conn, 1, amqp_cstring_bytes(queuename2), amqp_empty_bytes, 0, 0, 0, queue_table);
//  amqp_basic_consume(conn, channel, amqp_cstring_bytes(queuename2), amqp_empty_bytes, 0, 0, 0, amqp_empty_table);
//  die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming");

  amqp_tx_select(conn, channel);

  while (1) {

        props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
        props.content_type = amqp_cstring_bytes("text/plain");
        props.delivery_mode = 2; /* persistent delivery mode */

        amqp_maybe_release_buffers(conn);
        printf("Waiting for message.\n");
        res = amqp_consume_message(conn, &envelope, NULL, 0);

        if (AMQP_RESPONSE_LIBRARY_EXCEPTION == res.reply_type) {
          printf("Connection closed, return type: %d, library_error: %d \n",res.reply_type, res.library_error);
          printf("Connection closed code: %d \n", AMQP_STATUS_CONNECTION_CLOSED);
          printf("Unexpected state code: %d \n", AMQP_STATUS_UNEXPECTED_STATE);
          printf("Heartbeat time out code: %d \n", AMQP_STATUS_HEARTBEAT_TIMEOUT);
          /* Investigation of amqp_status_enum_ */
          if (AMQP_STATUS_UNEXPECTED_STATE == res.library_error){
        	  printf("Connection was closed from the broker.\n");
        	  printf("Start reconnect attempts.\n");
        	  reconnectAttempts = 3;
        	  connReestablished = 0;
        	  while(reconnectAttempts > 0){
        		  if(connReestablished<1){
        			  sleep(sleepTime);
        			  printf("Reconnect attempt %d.\n",reconnectAttempt);
        			  if(0 == createConnChannel(hostname, port, vhost, channel, user, password, &conn)){
        				  amqp_basic_qos(conn, channel, 0, 1, 0);

        				  amqp_basic_consume(conn, channel, amqp_cstring_bytes(queuename1), amqp_empty_bytes, 0, 0, 0, amqp_empty_table);
        				  die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming");

        				  //amqp_basic_consume(conn, 1, amqp_cstring_bytes(queuename2), amqp_empty_bytes, 0, 0, 0, queue_table);
        				  amqp_basic_consume(conn, channel, amqp_cstring_bytes(queuename2), amqp_empty_bytes, 0, 0, 0, amqp_empty_table);
        				  die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming");

        				  amqp_tx_select(conn, channel);

        				  connReestablished = 1;
        				  printf("Connection reestablished.\n");
        			  }
        		  }
        		  reconnectAttempt++;
        		  reconnectAttempts--;

        	  }
          }
        }


        if (AMQP_RESPONSE_NORMAL != res.reply_type && connReestablished != 1) {
          break;
        }
        if (AMQP_RESPONSE_NORMAL != res.reply_type && connReestablished == 1){
        	continue;
        }

        printf("Delivery %u, exchange %.*s routingkey %.*s\n",
               (unsigned) envelope.delivery_tag,
               (int) envelope.exchange.len, (char *) envelope.exchange.bytes,
               (int) envelope.routing_key.len, (char *) envelope.routing_key.bytes);

        if (envelope.message.properties._flags & AMQP_BASIC_CONTENT_TYPE_FLAG) {
          printf("Content-type: %.*s\n",
                 (int) envelope.message.properties.content_type.len,
                 (char *) envelope.message.properties.content_type.bytes);
      	amqp_dump(envelope.message.body.bytes,
      			envelope.message.body.len);
        }

		return_code = amqp_basic_publish(conn,
										channel,
										amqp_cstring_bytes(exchange),
										amqp_cstring_bytes(dbRabbitQueue),
										0,
										0,
										&props,
										amqp_cstring_bytes("DFX started update"));
		if(0 == DFX_update_IPC_error){
			amqp_tx_commit(conn, channel);
			printf("Published and commited DFX-started update.\n");
			printf("Expected state: one message in the db_rabbit queue and consumed not acked message in DFXqueue.\n");
			sleep(15);

		}
		else{
			/* Here requeing of the consumed message was reached only by closing the channel, not commit, no reject method was successfull.*/
			/* The correct implementation is - publish, rollback, recover (this closes the channel) and goto close(conn), reestablish connection/channel by retries. */
			printf("Envelop channel: %d, delivery_tag: %d \n",envelope.channel, envelope.delivery_tag);
//			amqp_basic_ack(conn, envelope.channel, envelope.delivery_tag, 0);
//			amqp_basic_ack(conn, envelope.channel, envelope.delivery_tag, 0);
//			amqp_destroy_envelope(&envelope);
			amqp_tx_rollback(conn, channel);

//			amqp_basic_reject(conn, envelope.channel, envelope.delivery_tag, 1);
//			amqp_basic_nack(conn, envelope.channel, envelope.delivery_tag, 1, 1);
//			printf("I am after rollback.\n");
//			sleep(10);
			amqp_basic_recover(conn, channel, 0); //Basic recover closes the channel, so the message is really redelivered back to the queue.
//			amqp_destroy_envelope(&envelope);
//			amqp_tx_commit(conn, envelope.channel);
//			die_on_amqp_error(amqp_channel_close(conn, channel, AMQP_REPLY_SUCCESS), "Closing channel");
			printf("DFX-started update error.\n");
			printf("Expected state: nacked message to DFXqueue and no message uplished to db_rabbit queue.\n");
			sleep(20);
			break;
		}

		amqp_basic_ack(conn, envelope.channel, envelope.delivery_tag, 0);
		printf("Consumed message acknowledged.\n");
		printf("Expected state: DFX-started in db_rabbit queue and consumed not acked message in DFXqueue because there was no tx commit yet.\n");
		sleep(15);


        printf("Processing message: running child function \n");
        fflush(stdout);
        sleep(5);
        printf("Processing done\n");
        fflush(stdout);

		return_code = amqp_basic_publish(conn,
										channel,
										amqp_cstring_bytes(exchange),
										amqp_cstring_bytes(dbRabbitQueue),
										0,
										0,
										&props,
										amqp_cstring_bytes("DFX done update"));

		return_code = amqp_basic_publish(conn,
										channel,
										amqp_cstring_bytes(exchange),
										amqp_cstring_bytes(staProQueue),
										0,
										0,
										&props,
										amqp_cstring_bytes("DO"));

		printf("Published DFX-done update and Interval message into StaPro queue.\n");
		printf("Expected state: Consumed not acknowledged message in DFXqueue and only one message in db_rabbit queue, there was not commit yet.\n");
		sleep(15);
		if(0 == Interval_IPC_error){
			amqp_tx_commit(conn, channel);
			printf("Commited DFX-done update, Interval message, and acknowledged message in DFXqueue.\n");
			printf("Expected state: two messages in the db_rabbit queue, one interval message in StaProQueue and consumed removed message from DFXqueue.\n");
			sleep(15);

		}
		else{
			/* In this stage there is different behaviour than for first rollback, here the message is really unacked together with tx_rollback. */
			//amqp_basic_ack(conn, envelope.channel, envelope.delivery_tag, 0);
			amqp_destroy_envelope(&envelope);
			amqp_tx_rollback(conn, channel);
			printf("DFX-done update or StePro publish error.\n");
			printf("Expected state: nacked message to DFXqueue and one message published (DFX-started) to db_rabbit queue.\n");
			sleep(20);
			break;
		}
        //break;
  }
  die_on_amqp_error(amqp_channel_close(conn, channel, AMQP_REPLY_SUCCESS), "Closing channel");
  die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
  die_on_error(amqp_destroy_connection(conn), "Ending connection");

  return 0;

}

int createConnChannel(char *hostname,
		int port, char *vhost, int channel, char *user,
		char *password, amqp_connection_state_t *conn_out)
{
	amqp_socket_t *socket = NULL;
	amqp_connection_state_t conn;
	int status;
	conn = *conn_out;
	conn = amqp_new_connection();

	socket = amqp_tcp_socket_new(conn);
	if (!socket) {
	status = error_return("creating TCP socket");
	return (status);
	}

	status = amqp_socket_open(socket, hostname, port);
	if (status) {
	status = error_return("opening TCP socket");
	return (status);
	}

	die_on_amqp_error(amqp_login(conn, vhost, 0, 131072, 10, AMQP_SASL_METHOD_PLAIN, user, password),
					"Logging in");
	amqp_channel_open(conn, channel);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");

	*conn_out = conn;
	return (status);
}
