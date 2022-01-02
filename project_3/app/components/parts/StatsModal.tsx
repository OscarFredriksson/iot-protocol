import React from 'react';
import {Dimensions, Modal, StyleSheet, Text, View} from 'react-native';
import {SafeAreaView} from 'react-native-safe-area-context';
import Card from '../ui/Card';

import IonIcon from 'react-native-vector-icons/Ionicons';
import {
  TouchableOpacity,
  TouchableWithoutFeedback,
} from 'react-native-gesture-handler';
import Colors from '../../constants/Colors';
import {LineChart} from 'react-native-chart-kit';
import {ChartConfig} from 'react-native-chart-kit/dist/HelperTypes';

interface StatsModalProps {
  visible: boolean;
  close: () => void;
  stats: Array<{rtt: number}>;
}

export default function StatsModal(props: StatsModalProps) {
  return (
    <Modal
      animationType="fade"
      transparent={true}
      visible={props.visible}
      onRequestClose={() => props.close()}>
      <TouchableOpacity onPress={() => props.close()}>
        <SafeAreaView style={styles.container}>
          <TouchableWithoutFeedback>
            <Card style={styles.modalContainer}>
              <View style={styles.row}>
                <TouchableOpacity onPress={() => props.close()}>
                  <View style={styles.closeButton}>
                    <IonIcon name="close" size={20} color={Colors.primary} />
                  </View>
                </TouchableOpacity>
              </View>
              <View style={styles.content}>
                <Text style={styles.title}>Round Trip Time History</Text>
                {props.stats.length === 0 ? (
                  <Text style={styles.emptyText}>
                    No stats data, send some requests!
                  </Text>
                ) : (
                  <>
                    <LineChart
                      data={{
                        labels: [],
                        datasets: [
                          {
                            data: props.stats.map(value => value.rtt),
                          },
                        ],
                      }}
                      width={Dimensions.get('window').width * 0.8}
                      height={200}
                      yAxisSuffix="ms"
                      chartConfig={chartConfig}
                      bezier
                      style={styles.chartStyle}
                      withInnerLines={false}
                      withHorizontalLines={false}
                      withVerticalLines={false}
                    />
                    <View style={styles.stats}>
                      <Text style={styles.statsText}>
                        Max:{' '}
                        <Text style={styles.accent}>
                          {Math.max(...props.stats.map(value => value.rtt))}ms
                        </Text>
                      </Text>
                      <Text style={styles.statsText}>
                        Min:{' '}
                        <Text style={styles.accent}>
                          {Math.min(...props.stats.map(value => value.rtt))}ms
                        </Text>
                      </Text>
                      <Text style={styles.statsText}>
                        Avg:{' '}
                        <Text style={styles.accent}>
                          {Math.round(
                            props.stats
                              .map((value: {rtt: number}) => value.rtt)
                              .reduce((prev, curr) => prev + curr) /
                              props.stats.length,
                          )}
                          ms
                        </Text>
                      </Text>
                    </View>
                  </>
                )}
              </View>
            </Card>
          </TouchableWithoutFeedback>
        </SafeAreaView>
      </TouchableOpacity>
    </Modal>
  );
}

const chartConfig: ChartConfig = {
  backgroundGradientFrom: 'white',
  backgroundGradientTo: 'white',
  decimalPlaces: 0,
  color: () => Colors.primaryOpacityDarker,
  labelColor: () => Colors.primary,
  fillShadowGradient: Colors.accent,
  fillShadowGradientOpacity: 0.1,
  style: {
    borderRadius: 16,
  },
  propsForDots: {
    r: '3',
    strokeWidth: '6',
    stroke: Colors.primaryOpacity,
    fill: Colors.primary,
  },
};

const styles = StyleSheet.create({
  container: {
    width: '100%',
    height: '100%',
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#222222aa',
  },
  row: {
    flexDirection: 'row',
    justifyContent: 'flex-end',
    width: '100%',
  },
  modalContainer: {
    width: '95%',
    justifyContent: 'flex-start',
    alignSelf: 'center',
    alignItems: 'center',
  },
  content: {
    // paddingHorizontal: 30,
    paddingBottom: 20,
    width: '80%',
    alignItems: 'center',
    justifyContent: 'flex-start',
  },
  closeButton: {
    backgroundColor: Colors.primaryOpacity,
    width: 30,
    height: 30,
    borderRadius: 15,
    justifyContent: 'center',
    alignItems: 'center',
    marginTop: 10,
    marginRight: 10,
  },
  title: {
    // marginLeft: 0,
    marginTop: -10,
    marginBottom: 20,
    fontSize: 18,
    fontWeight: 'bold',
    color: '#222',
    textAlign: 'left',
    width: '100%',
  },
  emptyText: {
    marginVertical: 90,
    fontSize: 15,
  },
  chartStyle: {
    marginVertical: 15,
    borderRadius: 16,
  },
  textStyle: {
    color: 'white',
    fontWeight: 'bold',
    textAlign: 'center',
  },
  modalText: {
    marginBottom: 15,
    textAlign: 'center',
  },
  stats: {
    marginTop: -20,
    width: '100%',
    alignItems: 'center',
    justifyContent: 'space-between',
    flexDirection: 'row',
  },
  statsText: {
    color: '#444',
    fontSize: 14,
    alignSelf: 'center',
  },
  accent: {
    color: Colors.primary,
  },
});
