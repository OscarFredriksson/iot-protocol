import React, {useCallback, useEffect, useRef, useState} from 'react';
import {
  ActivityIndicator,
  Appearance,
  StyleSheet,
  Text,
  View,
} from 'react-native';
import {QoS} from 'sp-react-native-mqtt';
import Colors from '../../constants/Colors';
import Dimmer from '../parts/Dimmer';
import OnOffButton from '../parts/OnOffButton';
import WarmthPicker, {getRgbFromWarmth, warmth} from '../parts/WarmthPicker';
import IonIcon from 'react-native-vector-icons/Ionicons';
import {TouchableOpacity} from 'react-native-gesture-handler';
import StatsModal from '../parts/StatsModal';

interface LampControllerProps {
  publish: (topic: string, payload: string, qos: QoS, retain: boolean) => void;
  title: string;
  lampId: string;
  style?: object;
  isPublishing: boolean;
  on: boolean;
  warmth: warmth;
  dim: number;
}

const DIM_SPEED = 5;

export default function LampController(props: LampControllerProps) {
  const [isPublishing, setIsPublishing] = useState(props.isPublishing);

  const [isOn, setIsOn] = useState<boolean>(props.on);
  const [dim, setDim] = useState<number>(props.dim);
  const [warmthValue, setWarmthValue] = useState<warmth>('warm');
  const prevValues = useRef({isOn, dim, warmthValue});

  const [rttTimer, setRttTimer] = useState<Date>();

  const [modalVisible, setModalVisible] = useState(false);

  const stopRttTimer = useCallback(() => {
    if (!rttTimer) return;

    console.log('Dim RTT:', new Date().getTime() - rttTimer?.getTime(), 'ms');
  }, [rttTimer]);

  useEffect(() => {
    setIsPublishing(props.isPublishing);
  }, [props.isPublishing]);

  useEffect(() => {
    if (props.on === prevValues.current.isOn) return;

    setIsPublishing(false);
    setIsOn(props.on);
    prevValues.current.isOn = props.on;

    stopRttTimer();
  }, [isOn, props.on, stopRttTimer]);

  useEffect(() => {
    if (props.dim === prevValues.current.dim) return;

    setIsPublishing(false);
    setDim(props.dim);
    prevValues.current.dim = props.dim;

    stopRttTimer();
  }, [dim, props.dim, stopRttTimer]);

  useEffect(() => {
    if (props.warmth === prevValues.current.warmthValue) return;

    setIsPublishing(false);
    setWarmthValue(props.warmth);
    prevValues.current.warmthValue = props.warmth;

    stopRttTimer();
  }, [props.warmth, stopRttTimer, warmthValue]);

  const publish = useCallback(
    (payload: object) => {
      setIsPublishing(true);

      setRttTimer(new Date());
      props.publish(props.lampId, JSON.stringify(payload), 0, true);
    },
    [props],
  );

  const mqttSendToggle = useCallback(() => {
    const payload = {
      '5850': isOn ? 0 : 1,
      '5706': getRgbFromWarmth(warmthValue),
      '5851': !isOn && dim === 0 ? 50 : dim,
      '5712': DIM_SPEED,
    };

    setIsOn(!isOn);
    publish(payload);
  }, [dim, isOn, publish, warmthValue]);

  const mqttSendDim = useCallback(
    (value: number) => {
      const payload = {
        '5850': value === 0 ? 0 : 1,
        // '5706': getRgbFromWarmth(warmthValue),
        '5851': value,
        '5712': DIM_SPEED,
      };

      setDim(value);
      publish(payload);
    },
    [publish],
  );

  const mqttSendWarmth = useCallback(
    (value: warmth) => {
      const payload = {
        '5850': isOn ? 1 : 0,
        '5706': getRgbFromWarmth(value),
        '5851': dim,
        '5712': DIM_SPEED,
      };

      setWarmthValue(value);
      publish(payload);
    },
    [dim, isOn, publish],
  );

  return (
    <View style={{...props.style, ...styles.container}}>
      <StatsModal visible={modalVisible} close={() => setModalVisible(false)} />
      <View style={[styles.row, styles.labelRow]}>
        <Text style={styles.label}>{props.title}</Text>
        <View style={styles.publishSpinner}>
          {isPublishing && (
            <ActivityIndicator size="small" color={Colors.primary} />
          )}
        </View>

        <TouchableOpacity onPress={() => setModalVisible(true)}>
          <IonIcon name="stats-chart" color={Colors.primary} size={20} />
        </TouchableOpacity>
      </View>
      <View style={styles.row}>
        <OnOffButton
          isLoading={isOn === undefined}
          onPress={() => mqttSendToggle()}
          isOn={isOn}
        />
        <WarmthPicker
          isLoading={warmthValue === undefined}
          style={styles.warmthPicker}
          value={warmthValue}
          onSelect={(value: warmth) => mqttSendWarmth(value)}
        />
      </View>
      <Dimmer
        isLoading={dim === undefined}
        style={styles.dimmer}
        value={!isOn ? 0 : dim}
        onChange={(value: number) => mqttSendDim(value)}
      />
    </View>
  );
}

const styles = StyleSheet.create({
  dimmer: {
    width: '100%',
    marginTop: 10,
  },
  warmthPicker: {
    marginLeft: 10,
    flex: 1,
  },
  container: {
    margin: 20,
    width: '100%',
    alignItems: 'center',
  },
  row: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    alignItems: 'center',
    alignContent: 'center',
    width: '100%',
  },
  labelRow: {
    width: '100%',
    marginBottom: 10,
    justifyContent: 'flex-start',
    paddingHorizontal: 15,
  },
  label: {
    marginRight: 20,
    color: Appearance.getColorScheme() === 'dark' ? '#fff' : '#222',
    textAlign: 'left',
    fontSize: 20,
    fontWeight: 'bold',
  },
  publishSpinner: {
    alignItems: 'flex-start',
    flex: 2,
  },
});
