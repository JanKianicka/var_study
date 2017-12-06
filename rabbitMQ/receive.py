import pika
import numpy

def callback(ch, method, properties, body):
    print " [x] Received %r" % (body,)

# Version for reading binnary matrixes.
'''def callback(ch, method, properties, body):
    B = numpy.frombuffer(body)
    print " [x] Received %s" % (B,)
'''

credentials = pika.PlainCredentials('guest', 'guest')
parameters = pika.ConnectionParameters('192.168.50.129', 5672, '/', credentials)

connection = pika.BlockingConnection(parameters)

channel = connection.channel()


# It is good practise to declare queue again.
channel.queue_declare(queue='hello')

channel.basic_consume(callback,
                      queue='hello',
                      no_ack=True)

print ' [*] Waiting for messages. To exit press CTRL+C'
channel.start_consuming()
