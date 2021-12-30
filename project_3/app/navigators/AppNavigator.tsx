import React from 'react';
import {createStackNavigator} from '@react-navigation/stack';

import {DashboardScreen} from '../screens/DashboardScreen';
// import {Platform} from 'react-native';
import Colors from '../constants/Colors';

// import DashboardScreen from '../screens/DashboardScreen';

const Stack = createStackNavigator();

const defaultNavOptions = {
  headerStyle: {
    // backgroundColor: Platform.OS === 'android' ? Colors.primary : '',
    backgroundColor: Colors.primary,
    // borderBottomColor: Platform.OS === 'ios' ? '#888' : '',
    // borderBottomWidth: Platform.OS === 'ios' ? 1 : 0,
  },
  // headerTintColor: Platform.OS === 'android' ? 'white' : '#000',
  headerTintColor: 'white',
};

export default function AppNavigator() {
  return (
    <Stack.Navigator screenOptions={defaultNavOptions}>
      <Stack.Screen name="Dashboard" component={DashboardScreen} />
    </Stack.Navigator>
  );
}
