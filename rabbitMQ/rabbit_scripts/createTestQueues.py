import pika

# Initializaition of connection variables

ConnectionPars = {"host":  '192.168.50.129', 
                  "port":  5672, 
                  "vhost": '/', 
                  "user":  "guest",
                  "password": "guest"
                  }

Exchanges = {"dacs4Exchange":{"name": "dacs4Exchange",
                          "type": "direct",
                          "durable": True
                          }
             }

Queues = {"DFXqueue":{"name":     "DFXqueue",
                    "durable":  "True"
                    },
          "StaProQueue":{"name":     "StaProQueue",
                    "durable":  "True"
                    },
          "DoneQueue":{"name":     "DoneQueue",
                    "durable":  "True"
                    }
          }

Bindings = {"DFXBinding":{"exchange":       Exchanges["dacs4Exchange"]["name"],
                          "queue"   :       Queues["DFXqueue"]["name"],
                          "routing_key":    "DFXRoutingkey"
                          },
            "StaProBinding":{"exchange":    Exchanges["dacs4Exchange"]["name"],
                           "queue"   :      Queues["StaProQueue"]["name"],
                           "routing_key":    "StaProRoutingkey"
                           },
            "DoneBinding":{"exchange":      Exchanges["dacs4Exchange"]["name"],
                           "queue"   :      Queues["DoneQueue"]["name"],
                           "routing_key":    "DoneRoutingkey"
                           },
            }

# creating artifacts
credentials = pika.PlainCredentials(ConnectionPars["user"], ConnectionPars["password"])
parameters = pika.ConnectionParameters(ConnectionPars["host"],
                                       ConnectionPars["port"],
                                       ConnectionPars["vhost"],
                                       credentials)
connection = pika.BlockingConnection(parameters)

channel = connection.channel(1)

channelRes = channel.exchange_declare(exchange = Exchanges["dacs4Exchange"]["name"],
                         type = Exchanges["dacs4Exchange"]["type"],
                         durable = Exchanges["dacs4Exchange"]["durable"])
print("Created exchange:", channelRes)
print("Created queues:")
for queueDict in Queues.itervalues():

    queueResult = channel.queue_declare(queue=queueDict["name"], 
                                        durable=queueDict["durable"])

    print queueResult
    
print("Created bindings:")
for bingingDict in Bindings.itervalues():
    
    bingingRes  =  channel.queue_bind(exchange  = bingingDict["exchange"],
                                      queue     = bingingDict["queue"],
                                      routing_key = bingingDict["routing_key"])
    print bingingRes

connection.close()



