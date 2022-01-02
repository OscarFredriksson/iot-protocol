import {NativeStackScreenProps} from '@react-navigation/native-stack';
import React, {useEffect} from 'react';
import {ActivityIndicator, Button, StyleSheet, View} from 'react-native';
import {Text} from 'react-native-elements';
import MQTT, {IMqttClient} from 'sp-react-native-mqtt';
import Colors from '../constants/Colors';

export default function ConnectingScreen(props: NativeStackScreenProps<any>) {
  useEffect(() => {
    MQTT.createClient({
      uri: 'mqtt://192.168.183.189:1883',
      clientId: 'light-controller-app',
    }).then((client: IMqttClient) => {
      client.on('connect', function () {
        props.navigation.navigate('Dashboard', {mqttClient: client});
      });
    });
  }, [props.navigation]);

  return (
    <View style={styles.container}>
      <ActivityIndicator size="large" color="#fff" />
      <Text style={styles.connectingText}>Connecting...</Text>
      <Button
        title="connect"
        onPress={() =>
          props.navigation.navigate('Dashboard', {mqttClient: undefined})
        }
      />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    height: '100%',
    width: '100%',
    alignContent: 'center',
    alignItems: 'center',
    justifyContent: 'center',
    backgroundColor: Colors.primary,
  },
  connectingText: {
    color: '#fff',
    marginTop: 10,
    fontSize: 15,
  },
});
