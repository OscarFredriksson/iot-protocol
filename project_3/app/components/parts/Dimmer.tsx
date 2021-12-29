import React from 'react';
import {StyleSheet} from 'react-native';
import {Slider} from 'react-native-elements/dist/slider/Slider';
import Colors from '../../constants/Colors';
import Card from '../ui/Card';
import LabelText from '../ui/LabelText';

interface DimmerProps {
  initialValue: number;
  onChange: (value: number) => void;
  style?: object;
}

export default function Dimmer(props: DimmerProps) {
  return (
    <Card style={{...props.style, ...styles.card}}>
      <LabelText>Brightness</LabelText>
      <Slider
        style={styles.slider}
        thumbStyle={styles.thumb}
        thumbTintColor={Colors.primary}
        minimumTrackTintColor={Colors.primary}
        maximumTrackTintColor={Colors.inactive}
        minimumValue={0}
        maximumValue={254}
        step={1}
        value={props.initialValue}
        onSlidingComplete={props.onChange}
      />
    </Card>
  );
}

const styles = StyleSheet.create({
  card: {
    height: 75,
    paddingTop: 5,
    paddingHorizontal: 20,
  },
  slider: {
    width: '100%',
  },
  thumb: {
    width: 20,
    height: 20,
  },
});
