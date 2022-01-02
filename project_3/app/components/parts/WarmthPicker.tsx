import React from 'react';
import {
  ActivityIndicator,
  StyleSheet,
  TouchableOpacity,
  View,
} from 'react-native';
import Colors from '../../constants/Colors';
import ColoredCard from '../ui/ColoredCard';
import LabelText from '../ui/LabelText';

export type warmth = 'white' | 'warm' | 'glow';

export function getRgbFromWarmth(warmth: warmth): string {
  return warmth === 'white'
    ? 'f5faf6'
    : warmth === 'warm'
    ? 'f1e0b5'
    : 'efd275';
}

export function getWarmthFromRgb(rgb: string): warmth {
  return rgb === 'f5faf6' ? 'white' : rgb === 'f1e0b5' ? 'warm' : 'glow';
}

interface WarmthOptionProps {
  isCurrent: boolean;
  warmth: warmth;
  onPress: (warmth: warmth) => void;
}

function WarmthOption(props: WarmthOptionProps) {
  return (
    <TouchableOpacity onPress={() => props.onPress(props.warmth)}>
      <View
        style={[
          styles.outline,
          props.isCurrent
            ? styles.warmthOptionSelected
            : styles.warmthOptionUnselected,
        ]}>
        <View
          style={[
            styles.warmthOption,
            {backgroundColor: '#' + getRgbFromWarmth(props.warmth)},
          ]}
        />
      </View>
    </TouchableOpacity>
  );
}

interface WarmthPickerProps {
  isLoading?: boolean;
  value: warmth;
  onSelect: (value: warmth) => void;
  style?: object;
}

export default function WarmthPicker(props: WarmthPickerProps) {
  return (
    <ColoredCard style={{...props.style, ...styles.card}}>
      {props.isLoading ? (
        <View style={styles.centered}>
          <ActivityIndicator size="large" color={Colors.primary} />
        </View>
      ) : (
        <>
          <LabelText>Warmth</LabelText>
          <View style={styles.row}>
            <WarmthOption
              isCurrent={props.value === 'glow'}
              warmth="glow"
              onPress={props.onSelect}
            />
            <WarmthOption
              isCurrent={props.value === 'warm'}
              warmth="warm"
              onPress={props.onSelect}
            />
            <WarmthOption
              isCurrent={props.value === 'white'}
              warmth="white"
              onPress={props.onSelect}
            />
          </View>
        </>
      )}
    </ColoredCard>
  );
}

const styles = StyleSheet.create({
  card: {
    height: 100,
    paddingHorizontal: 20,
    justifyContent: 'flex-start',
  },
  centered: {
    width: '100%',
    height: '100%',
    justifyContent: 'center',
    alignItems: 'center',
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
    borderColor: Colors.primary, //Colors.inactive,
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
