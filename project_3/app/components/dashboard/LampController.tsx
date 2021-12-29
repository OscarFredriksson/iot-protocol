import React, {useCallback, useState} from 'react';
import {StyleSheet, Text, View} from 'react-native';
import {IMqttClient} from 'sp-react-native-mqtt';
import Dimmer from '../parts/Dimmer';
import OnOffButton from '../parts/OnOffButton';
import WarmthPicker from '../parts/WarmthPicker';

interface LampControllerProps {
  mqttClient: IMqttClient;
  title: string;
  lampId: string;
  style?: object;
}

export default function LampController(props: LampControllerProps) {
  const [isOn, setIsOn] = useState(true);
  const [dimValue, setDimValue] = useState<number>(50);

  const mqttSendToggle = useCallback(() => {
    const payload = {
      '5850': isOn ? 0 : 1,
    };
    props.mqttClient.publish('lamp1', JSON.stringify(payload), 0, false);
    setIsOn(!isOn);

    if (isOn && dimValue === 0) {
      setDimValue(50);
    }
  }, [isOn, props.mqttClient, dimValue]);

  const mqttSendDim = useCallback(
    (value: number) => {
      const dimSpeed = 5;

      const payload = {
        '5851': value,
        '5712': dimSpeed,
      };
      setIsOn(value === 0 ? false : true);
      props.mqttClient.publish(props.lampId, JSON.stringify(payload), 0, false);
    },
    [props.mqttClient, props.lampId],
  );

  return (
    <View style={{...props.style, ...styles.container}}>
      <Text style={styles.label}>{props.title}</Text>
      <View style={styles.row}>
        <OnOffButton onPress={() => mqttSendToggle()} isOn={isOn} />
        <WarmthPicker
          style={styles.warmthPicker}
          initialValue="warm"
          onSelect={() => {}}
        />
      </View>
      <Dimmer
        style={styles.dimmer}
        initialValue={!isOn ? 0 : dimValue}
        onChange={(value: number) => {
          console.log('value', value);
          setDimValue(value);
          mqttSendDim(value);
        }}
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
    width: '100%',
  },
  label: {
    width: '100%',
    textAlign: 'left',
    fontSize: 20,
    marginBottom: 10,
    fontWeight: '600',
  },
});
