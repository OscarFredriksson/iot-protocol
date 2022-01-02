import React from 'react';

import Colors from '../constants/Colors';
import {
  createNativeStackNavigator,
  NativeStackNavigationOptions,
} from '@react-navigation/native-stack';
import ConnectingScreen from '../screens/ConnectingScreen';

import DashboardScreen from '../screens/DashboardScreen';

const Stack = createNativeStackNavigator();

const defaultNavOptions: NativeStackNavigationOptions = {
  headerShadowVisible: false,
  headerStyle: {
    backgroundColor: Colors.primary,
  },
  headerTintColor: 'white',
  presentation: 'fullScreenModal',
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
