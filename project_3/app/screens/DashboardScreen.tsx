import React, {useCallback, useEffect, useReducer, useState} from 'react';
import {
  ActivityIndicator,
  Appearance,
  StyleSheet,
  Text,
  View,
} from 'react-native';
import MQTT, {IMqttClient, QoS} from 'sp-react-native-mqtt';
import LampController from '../components/dashboard/LampController';
import {getWarmthFromRgb, warmth} from '../components/parts/WarmthPicker';
import Colors from '../constants/Colors';

interface LampSetting {
  on?: boolean;
  warmth?: warmth;
  dim?: number;
}

function lampReducer(state: any, action: any) {
  let newValues: LampSetting = state[action.lampId]
    ? state[action.lampId].values
    : {};

  for (const key in action.values) {
    if (key === '5850') {
      newValues.on = action.values[key];
    } else if (key === '5706') {
      newValues.warmth = getWarmthFromRgb(action.values[key]);
    } else if (key === '5851') {
      newValues.dim = action.values[key];
    }
  }

  return {
    ...state,
    [action.lampId]: {
      values: newValues,
      isPublishing: false,
    },
  };
}

export function DashboardScreen() {
  const [mqttClient, setMqttClient] = useState<IMqttClient>();
  const [connected, setConnected] = useState(false);
  const [lamps, dispatchLamps] = useReducer(lampReducer, {});

  useEffect(() => {
    MQTT.createClient({
      uri: 'mqtt://192.168.183.189:1883',
      clientId: 'light-controller-app',
    }).then((client: IMqttClient) => {
      client.on('closed', () => {
        setConnected(false);
      });

      client.on('error', () => {
        setConnected(false);
      });

      client.on('connect', function () {
        setConnected(true);
        client.subscribe('lamp1/status', 0);
        console.log('connected!');
      });

      client.on(
        'message',
        (msg: {data: string; qos: QoS; retain: boolean; topic: string}) => {
          if (msg.topic === 'lamp1/status') {
            dispatchLamps({lampId: 'lamp1', values: JSON.parse(msg.data)});
          }
        },
      );
      client.connect();
      setMqttClient(client);
    });
  }, []);

  const publish = useCallback(
    (topic: string, payload: string, qos: QoS, retain: boolean) => {
      mqttClient?.publish(topic, payload, qos, retain);
    },
    [mqttClient],
  );

  if (!connected || !mqttClient) {
    return (
      <View style={styles.centered}>
        <ActivityIndicator size="large" color={Colors.primary} />
        <Text style={styles.connectingText}>Connecting...</Text>
      </View>
    );
  }

  return (
    <View style={styles.container}>
      <LampController
        publish={publish}
        title="Bedroom"
        lampId="lamp1"
        isPublishing={lamps.lamp1?.isPublishing}
        on={lamps.lamp1?.values.on}
        warmth={lamps.lamp1?.values.warmth}
        dim={lamps.lamp1?.values.dim}
      />
      <LampController
        publish={publish}
        title="Kitchen"
        lampId="lamp2"
        isPublishing={lamps.lamp2?.isPublishing}
        on={lamps.lamp2?.values.on}
        warmth={lamps.lamp2?.values.warmth}
        dim={lamps.lamp2?.values.dim}
      />
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
    backgroundColor: Appearance.getColorScheme() === 'dark' ? '#222' : '#eee',
    height: '100%',
  },
  centered: {
    height: '100%',
    width: '100%',
    alignContent: 'center',
    alignItems: 'center',
    justifyContent: 'center',
  },
  connectingText: {
    color: '#222',
    marginTop: 10,
    fontSize: 15,
  },
});
