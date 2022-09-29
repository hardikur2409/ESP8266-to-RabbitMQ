import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print("Connected to broker")
 
def on_message(client, userdata, message):
    message.payload = message.payload.decode("utf-8")
    print ("Message received: "  + message.payload)

client = mqtt.Client()
client.username_pw_set("TMDG2022", password='TMDG2022')
client.connect("rmq2.pptik.id", 1883) 

client.on_connect = on_connect       #attach function to callback
client.on_message = on_message       #attach function to callback

client.subscribe("mq2_mqtt") 
client.loop_forever()                 #start the loop