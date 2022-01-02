import React from 'react';
import {ActivityIndicator, StyleSheet, View} from 'react-native';
import {Slider} from 'react-native-elements/dist/slider/Slider';
import Colors from '../../constants/Colors';
import ColoredCard from '../ui/ColoredCard';
import LabelText from '../ui/LabelText';

interface DimmerProps {
  isLoading?: boolean;
  value: number;
  onChange: (value: number) => void;
  style?: object;
}

export default function Dimmer(props: DimmerProps) {
  return (
    <ColoredCard style={{...props.style, ...styles.card}}>
      {props.isLoading ? (
        <View style={styles.centered}>
          <ActivityIndicator size="large" color={Colors.primary} />
        </View>
      ) : (
        <>
          <LabelText>Brightness</LabelText>
          <Slider
            style={styles.slider}
            thumbStyle={styles.thumb}
            thumbTintColor={Colors.primary}
            minimumTrackTintColor={Colors.primary}
            maximumTrackTintColor="#fff"
            minimumValue={0}
            maximumValue={254}
            step={1}
            value={props.value}
            onSlidingComplete={(value: number) => props.onChange(value)}
          />
        </>
      )}
    </ColoredCard>
  );
}

const styles = StyleSheet.create({
  card: {
    height: 80,
    paddingHorizontal: 20,
    justifyContent: 'flex-start',
  },
  centered: {
    width: '100%',
    height: '100%',
    justifyContent: 'center',
    alignItems: 'center',
  },
  slider: {
    width: '100%',
  },
  thumb: {
    width: 20,
    height: 20,
  },
});
