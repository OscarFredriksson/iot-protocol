import React, {useState} from 'react';
import {StyleSheet, TouchableOpacity, View} from 'react-native';
import Colors from '../../constants/Colors';
import Card from '../ui/Card';
import LabelText from '../ui/LabelText';

export type warmth = 'white' | 'warm' | 'glow';

export function getRgbFromWarmth(warmth: warmth): string {
  return warmth === 'white'
    ? 'f5faf6'
    : warmth === 'warm'
    ? 'f1e0b5'
    : 'efd275';
}

interface WarmthOptionProps {
  current: boolean;
  warmth: warmth;
  onPress: (warmth: warmth) => void;
}

function WarmthOption(props: WarmthOptionProps) {
  return (
    <TouchableOpacity onPress={() => props.onPress(props.warmth)}>
      <View
        style={[
          styles.outline,
          props.current
            ? styles.warmthOptionSelected
            : styles.warmthOptionUnselected,
        ]}>
        <View
          style={[
            styles.warmthOption,
            // props.current
            //   ? styles.warmthOptionSelected
            //   : styles.warmthOptionUnselected,
            {backgroundColor: '#' + getRgbFromWarmth(props.warmth)},
          ]}
        />
      </View>
    </TouchableOpacity>
  );
}

interface WarmthPickerProps {
  initialValue: warmth;
  onSelect: (value: warmth) => void;
  style?: object;
}

export default function WarmthPicker(props: WarmthPickerProps) {
  const [currentWarmth, setCurrentWarmth] = useState<warmth>('glow');

  const warmthChangeHandler = (value: warmth) => {
    setCurrentWarmth(value);
    props.onSelect(value);
  };

  return (
    <Card style={{...props.style, ...styles.card}}>
      <LabelText>Warmth</LabelText>
      <View style={styles.row}>
        <WarmthOption
          current={currentWarmth === 'glow'}
          warmth="glow"
          onPress={warmthChangeHandler}
        />
        <WarmthOption
          current={currentWarmth === 'warm'}
          warmth="warm"
          onPress={warmthChangeHandler}
        />
        <WarmthOption
          current={currentWarmth === 'white'}
          warmth="white"
          onPress={warmthChangeHandler}
        />
      </View>
    </Card>
  );
}

const styles = StyleSheet.create({
  card: {
    height: 100,
    paddingHorizontal: 20,
    paddingBottom: 5,
  },
  row: {
    width: '100%',
    marginTop: 10,
    flexDirection: 'row',
    justifyContent: 'space-evenly',
  },
  warmthOption: {
    height: 32,
    width: 32,
    borderRadius: 16,
    borderWidth: 1,
    borderColor: Colors.inactive,
  },

  outline: {
    height: 42,
    width: 42,
    borderRadius: 21,
    justifyContent: 'center',
    alignItems: 'center',
    borderWidth: 2,
  },
  warmthOptionSelected: {
    // borderWidth: 2,
    borderColor: Colors.primary,
  },
  warmthOptionUnselected: {
    // borderWidth: 1,
    borderColor: 'transparent',
  },
});
