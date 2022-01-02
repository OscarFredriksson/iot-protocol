import React from 'react';
// import {createStackNavigator} from '@react-navigation/stack';

import {DashboardScreen} from '../screens/DashboardScreen';
// import {Platform} from 'react-native';
import Colors from '../constants/Colors';
import {
  createNativeStackNavigator,
  NativeStackNavigationOptions,
} from '@react-navigation/native-stack';
import ConnectingScreen from '../screens/ConnectingScreen';

// import DashboardScreen from '../screens/DashboardScreen';

const Stack = createNativeStackNavigator();

const defaultNavOptions: NativeStackNavigationOptions = {
  headerShadowVisible: false,
  headerStyle: {
    backgroundColor: Colors.primary,
  },
  headerTintColor: 'white',
};

export default function AppNavigator() {
  return (
    <Stack.Navigator screenOptions={defaultNavOptions}>
      <Stack.Screen
        name="Connecting"
        component={ConnectingScreen}
        options={{title: ''}}
      />
      <Stack.Screen
        name="Dashboard"
        component={DashboardScreen}
        options={{
          title: 'Dashboard',
          headerLargeTitle: true,
          headerBackVisible: false,
        }}
      />
    </Stack.Navigator>
  );
}
