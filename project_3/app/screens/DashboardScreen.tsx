import React, {useEffect, useState} from 'react';
import {ActivityIndicator, StyleSheet, Text, View} from 'react-native';
import MQTT, {IMqttClient} from 'sp-react-native-mqtt';
import LampController from '../components/dashboard/LampController';
import Colors from '../constants/Colors';

export function DashboardScreen() {
  const [mqttClient, setMqttClient] = useState<IMqttClient>();
  const [connected, setConnected] = useState(false);

  useEffect(() => {
    MQTT.createClient({
      uri: 'mqtt://192.168.183.189:1883',
      clientId: 'light-controller-app',
    }).then((client: any) => {
      setMqttClient(client);
      client.on('closed', () => {
        setConnected(false);
        console.log('mqtt.event.closed');
      });

      client.on('error', (msg: string) => {
        console.log('mqtt.event.error', msg);
      });

      client.on('message', (msg: string) => {
        console.log('mqtt.event.message', msg);
      });

      client.on('connect', function () {
        setConnected(true);
        console.log('connected!');
      });
      client.connect();
    });
  }, [setConnected, setMqttClient]);

  if (!connected || !mqttClient) {
    return (
      <View style={styles.centered}>
        <ActivityIndicator size="large" color={Colors.primary} />
        <Text style={styles.connectingText}>Connecting to broker...</Text>
      </View>
    );
  }

  return (
    <View style={styles.container}>
      <LampController mqttClient={mqttClient} title="Bedroom" lampId="lamp1" />
      <LampController mqttClient={mqttClient} title="Kitchen" lampId="lamp2" />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    paddingTop: 20,
    paddingHorizontal: '10%',
    alignContent: 'center',
    alignItems: 'center',
    justifyContent: 'flex-start',
  },
  centered: {
    height: '100%',
    width: '100%',
    alignContent: 'center',
    alignItems: 'center',
    justifyContent: 'center',
  },
  connectingText: {
    marginTop: 10,
    fontSize: 15,
  },
});
