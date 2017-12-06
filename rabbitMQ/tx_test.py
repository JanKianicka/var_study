#!/usr/bin/env python
import sys
import pika

message = ' '.join(sys.argv[1:]) or "Hello World!"

credentials = pika.PlainCredentials('guest', 'guest')
parameters = pika.ConnectionParameters('192.168.50.129', 5672, '/', credentials)

connection = pika.BlockingConnection(parameters)

channel = connection.channel()

channel.queue_declare(queue='task_queue', durable=True)

channel.exchange_declare(exchange='test_exchange',
                         type='direct', )


print channel.tx_select()

for i in range(0,3):
    channel.basic_publish(exchange='',
                      routing_key='task_queue',
                      body=message,
                      properties=pika.BasicProperties(
                         delivery_mode = 2, # make message persistent
                      ))

#print channel.tx_commit()

print channel.tx_rollback()

print " [x] Sent %r" % (message,)

connection.close()