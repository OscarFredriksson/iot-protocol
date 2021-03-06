import {
  NavigationRouteContext,
  useNavigation,
  useRoute,
} from '@react-navigation/native';
import {NativeStackScreenProps} from '@react-navigation/native-stack';
import React, {useCallback, useEffect, useReducer, useState} from 'react';
import {
  ActivityIndicator,
  Appearance,
  Platform,
  ScrollView,
  StyleSheet,
  Text,
  View,
} from 'react-native';
import {SafeAreaView} from 'react-native-safe-area-context';
import MQTT, {IMqttClient, QoS} from 'sp-react-native-mqtt';
import LampController from '../components/dashboard/LampController';
import Header from '../components/navigation/Header';
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

export default function DashboardScreen() {
  // const route = useRoute<any>();

  // const {mqttClient} = route;

  const navigation = useNavigation();

  const [mqttClient, setMqttClient] = useState<IMqttClient>();
  const [connected, setConnected] = useState(true);
  const [lamps, dispatchLamps] = useReducer(lampReducer, {
    lamp1: {values: {on: 1, warmth: 'warm', dim: 140}, isPublishing: false},
    lamp2: {values: {on: 1, warmth: 'white', dim: 40}, isPublishing: false},
  });

  useEffect(() => {
    MQTT.createClient({
      uri: 'mqtt://192.168.1.133:1883',
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
        client.subscribe('lamp2/status', 0);
        console.log('connected!');
      });

      client.on(
        'message',
        (msg: {data: string; qos: QoS; retain: boolean; topic: string}) => {
          if (msg.topic === 'lamp1/status') {
            dispatchLamps({lampId: 'lamp1', values: JSON.parse(msg.data)});
          } else if (msg.topic === 'lamp2/status') {
            dispatchLamps({lampId: 'lamp2', values: JSON.parse(msg.data)});
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

  useEffect(() => {
    if (!connected || !mqttClient) navigation.setOptions({title: ''});
    else navigation.setOptions({title: 'Dashboard'});
  }, [connected, mqttClient, navigation]);

  if (!connected || !mqttClient) {
    return (
      <View style={styles.centered}>
        <ActivityIndicator size="large" color="#fff" />
        <Text style={styles.connectingText}>Connecting...</Text>
      </View>
    );
  }

  return (
    <View style={styles.container}>
      <ScrollView>
        <Header />
        <SafeAreaView style={styles.content}>
          <LampController
            publish={publish}
            title="Sovrum"
            lampId="lamp1"
            isPublishing={lamps.lamp1?.isPublishing}
            on={lamps.lamp1?.values.on}
            warmth={lamps.lamp1?.values.warmth}
            dim={lamps.lamp1?.values.dim}
          />
          <LampController
            publish={publish}
            title="K??k"
            lampId="lamp2"
            isPublishing={lamps.lamp2?.isPublishing}
            on={lamps.lamp2?.values.on}
            warmth={lamps.lamp2?.values.warmth}
            dim={lamps.lamp2?.values.dim}
          />
          {/* <LampController
            publish={publish}
            title="Hall"
            lampId="lamp2"
            isPublishing={lamps.lamp2?.isPublishing}
            on={lamps.lamp2?.values.on}
            warmth={lamps.lamp2?.values.warmth}
            dim={lamps.lamp2?.values.dim}
          /> */}
        </SafeAreaView>
      </ScrollView>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    // backgroundColor: Appearance.getColorScheme() === 'dark' ? '#222' : '#eee',
    backgroundColor: '#eee',
    height: '100%',
  },
  content: {
    marginTop: Platform.OS === 'android' ? -50 : -100,
    paddingTop: 0,
    paddingHorizontal: '5%',
    alignContent: 'center',
    alignItems: 'center',
    justifyContent: 'flex-start',
    height: '100%',
    elevation: 3,
    zIndex: 2,
  },
  centered: {
    height: '100%',
    width: '100%',
    paddingBottom: 100,
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
