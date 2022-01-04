import {NativeStackScreenProps} from '@react-navigation/native-stack';
import React, {useEffect} from 'react';
import {
  ActivityIndicator,
  Button,
  Platform,
  StyleSheet,
  View,
} from 'react-native';
import {Text} from 'react-native-elements';
import MQTT, {IMqttClient} from 'sp-react-native-mqtt';
import Colors from '../constants/Colors';

export default function ConnectingScreen(props: NativeStackScreenProps<any>) {
  useEffect(() => {
    MQTT.createClient({
      uri: 'mqtt://192.168.1.133:1883',
      clientId: 'light-controller-app',
    }).then((client: IMqttClient) => {
      client.on('connect', function () {
        props.navigation.navigate('Dashboard', {mqttClient: client});
      });
      client.connect();
    });
  }, [props.navigation]);

  return (
    <View style={styles.container}>
      <ActivityIndicator size="large" color="#fff" />
      <Text style={styles.connectingText}>Connecting...</Text>
      {/* <Button
        color={Platform.OS === 'ios' ? 'white' : undefined}
        title="skip"
        onPress={() =>
          props.navigation.navigate('Dashboard', {mqttClient: undefined})
        }
      /> */}
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
    marginBottom: 20,
  },
});
