import sys
import pika
import time

SEND_QTY = 10

def send_message(mesId):
    global channel
    message = "Hello World #%i" % mesId
    print 'demo_send: Sending "%s"' % message
    channel.basic_publish(exchange='',
                          routing_key="test",
                          body=message,
                          properties=pika.BasicProperties(timestamp=time.time(),
                                                     app_id=__file__,
                                                     user_id='guest',
                                                     content_type="text/plain",
                                                     delivery_mode=1))


def on_delivered(frame):
    global message_id
    print "demo_send: Received delivery confirmation %r" % frame.method
    message_id += 1
    if message_id > SEND_QTY:
        connection.close()
    send_message(message_id)


def on_queue_declared(frame):
    print "demo_send: Queue Declared"
    channel.confirm_delivery(on_delivered)
    

message = ' '.join(sys.argv[1:]) or "Hello World!"

credentials = pika.PlainCredentials('guest', 'guest')
parameters = pika.ConnectionParameters('192.168.50.129', 5672, '/', credentials)

connection = pika.BlockingConnection(parameters)

channel = connection.channel()

channel.queue_declare(on_queue_declared, queue="testqueue")

#channel.confirm_delivery()
print "I am publishing"




# res = channel.basic_publish(exchange='',
#                       routing_key='task_queue',
#                       body=message,
#                       properties=pika.BasicProperties(
#                          delivery_mode = 2, # make message persistent
#                       ))
# print res
# print " [x] Sent %r" % (message,)

connection.close()