import pika
import time

def callback(ch, method, properties, body):
    print " [x] Received %r" % (body,)
    time.sleep( body.count('.') )
    print " [x] Done"
    ch.basic_ack(delivery_tag = method.delivery_tag)

credentials = pika.PlainCredentials('guest', 'guest')
parameters = pika.ConnectionParameters('192.168.50.129', 5672, '/', credentials)
connection = pika.BlockingConnection(parameters)

channel = connection.channel()


# It is good practise to declare queue again.
channel.queue_declare(queue='task_queue', durable=True)

channel.basic_qos(prefetch_count=1)

channel.basic_consume(callback,
                      queue='task_queue')

print ' [*] Waiting for messages. To exit press CTRL+C'
channel.start_consuming()
