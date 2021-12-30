/* eslint-disable @typescript-eslint/no-shadow */
import React, {useCallback, useEffect, useState} from 'react';
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

export default function LampController(props: LampControllerProps) {
  const [isPublishing, setIsPublishing] = useState(props.isPublishing);

  const [isOn, setIsOn] = useState<boolean>(props.on);
  const [dim, setDim] = useState<number>(props.dim);
  const [warmth, setWarmth] = useState<warmth>(props.warmth);

  useEffect(() => {
    setIsPublishing(props.isPublishing);
  }, [props.isPublishing]);

  useEffect(() => {
    setIsPublishing(false);
    setIsOn(props.on);
  }, [props.on]);

  useEffect(() => {
    setIsPublishing(false);
    setDim(props.dim);
  }, [props.dim]);

  useEffect(() => {
    setIsPublishing(false);
    setWarmth(props.warmth);
  }, [props.warmth]);

  const dimSpeed = 5;

  const mqttSendToggle = useCallback(() => {
    const payload = {
      '5850': isOn ? 0 : 1,
      '5706': getRgbFromWarmth(warmth),
      '5851': !isOn && dim === 0 ? 50 : dim,
      '5712': dimSpeed,
    };

    console.log(payload);

    setIsOn(!isOn);
    setIsPublishing(true);
    props.publish(props.lampId, JSON.stringify(payload), 0, true);
  }, [dim, isOn, props, warmth]);

  const mqttSendDim = useCallback(
    (value: number) => {
      const payload = {
        '5850': value === 0 ? 0 : 1,
        '5706': getRgbFromWarmth(warmth),
        '5851': value,
        '5712': dimSpeed,
      };

      console.log(payload);

      setDim(value);
      setIsPublishing(true);
      props.publish(props.lampId, JSON.stringify(payload), 0, true);
    },
    [props, warmth],
  );

  const mqttSendWarmth = useCallback(
    (value: warmth) => {
      const payload = {
        '5850': isOn ? 1 : 0,
        '5706': getRgbFromWarmth(value),
        '5851': dim,
        '5712': dimSpeed,
      };

      setWarmth(value);
      setIsPublishing(true);
      props.publish(props.lampId, JSON.stringify(payload), 0, true);
    },
    [dim, isOn, props],
  );

  return (
    <View style={{...props.style, ...styles.container}}>
      <View style={[styles.row, styles.labelRow]}>
        <Text style={styles.label}>{props.title}</Text>
        {isPublishing && (
          <ActivityIndicator size="small" color={Colors.primary} />
        )}
      </View>
      <View style={styles.row}>
        <OnOffButton
          isLoading={isOn === undefined}
          onPress={() => mqttSendToggle()}
          isOn={isOn}
        />
        <WarmthPicker
          isLoading={warmth === undefined}
          style={styles.warmthPicker}
          value={warmth}
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
  },
  label: {
    marginLeft: 10,
    marginRight: 20,
    color: Appearance.getColorScheme() === 'dark' ? '#fff' : '#222',
    textAlign: 'left',
    fontSize: 20,
    fontWeight: '600',
  },
});
