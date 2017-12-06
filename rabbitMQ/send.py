#!/usr/bin/env python
import pika

credentials = pika.PlainCredentials('guest', 'guest')
parameters = pika.ConnectionParameters('192.168.50.129', 5672, '/', credentials)

connection = pika.BlockingConnection(parameters)

channel = connection.channel()

channel.queue_declare(queue='hello')

channel.basic_publish(exchange='',
                      routing_key='hello',
                      body='Hello World!')
# Test for binnary buffer in the message.
'''import numpy
A = numpy.empty([20,100], dtype='float64')
print A
B = numpy.getbuffer(A) 
channel.basic_publish(exchange='',
                      routing_key='hello',
                      body=B)

'''
print " [x] Sent 'Hello World!'"

connection.close()
