import React from 'react';
import {
  Dimensions,
  Modal,
  StyleSheet,
  Text,
  TouchableOpacity,
  TouchableWithoutFeedback,
  View,
} from 'react-native';
import {SafeAreaView} from 'react-native-safe-area-context';
import Card from '../ui/Card';
import IonIcon from 'react-native-vector-icons/Ionicons';
import Colors from '../../constants/Colors';
import {LineChart} from 'react-native-chart-kit';
import {ChartConfig} from 'react-native-chart-kit/dist/HelperTypes';

function getStandardDeviation(array: Array<number>) {
  const mean = array.reduce((a, b) => a + b) / array.length;
  return Math.sqrt(
    array.map(x => Math.pow(x - mean, 2)).reduce((a, b) => a + b) /
      array.length,
  );
}

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
          <TouchableOpacity activeOpacity={1.0}>
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
                <View style={[styles.row, styles.subtitleRow]}>
                  <View style={styles.infoIcon}>
                    <IonIcon name="information" size={18} color="#666" />
                  </View>
                  <Text style={styles.subtitle}>
                    This graph shows the round trip time of each request sent to
                    the Trådfri gateway.
                  </Text>
                </View>
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
                      width={
                        Dimensions.get('window').width * 0.8 < 300
                          ? Dimensions.get('window').width * 0.8
                          : 300
                      }
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
                      <View style={styles.statsTitle}>
                        <Text style={styles.statsText}>
                          Metrics for a total of{' '}
                          <Text style={styles.accent}>
                            {props.stats.length}
                          </Text>{' '}
                          requests:
                        </Text>
                      </View>
                      <View style={styles.statsRow}>
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
                        <Text style={styles.statsText}>
                          Dev:{' '}
                          <Text style={styles.accent}>
                            {Math.round(
                              getStandardDeviation(
                                props.stats.map(
                                  (value: {rtt: number}) => value.rtt,
                                ),
                              ),
                            )}
                            ms
                          </Text>
                        </Text>
                      </View>
                      <View style={styles.statsRow}>
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
                      </View>
                    </View>
                  </>
                )}
              </View>
            </Card>
          </TouchableOpacity>
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
  fillShadowGradientOpacity: 0.2,
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
    alignItems: 'center',
    width: '100%',
  },
  modalContainer: {
    width: '95%',
    maxWidth: 380,
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
  infoIcon: {
    width: 26,
    height: 26,
    borderRadius: 13,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#eee',
  },
  title: {
    marginLeft: -20,
    marginTop: -10,
    marginBottom: 15,
    fontSize: 20,
    fontWeight: 'bold',
    color: '#222',
    textAlign: 'left',
    width: '100%',
  },
  subtitleRow: {
    marginBottom: 10,
    justifyContent: 'center',
  },
  subtitle: {
    textAlign: 'left',
    color: '#666',
    fontSize: 14,
    marginLeft: 15,
    lineHeight: 20,
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
    justifyContent: 'center',
  },
  statsTitle: {
    marginBottom: 10,
    marginLeft: 10,
    alignSelf: 'flex-start',
    textAlign: 'left',
  },
  statsRow: {
    marginBottom: 10,
    width: '90%',
    alignItems: 'center',
    justifyContent: 'space-around',
    flexDirection: 'row',
  },
  statsText: {
    color: '#444',
    fontSize: 14,
    lineHeight: 20,
    alignSelf: 'center',
  },
  accent: {
    color: Colors.primary,
    fontWeight: '500',
  },
});
