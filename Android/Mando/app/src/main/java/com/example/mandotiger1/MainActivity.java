package com.example.mandotiger1;

import androidx.appcompat.app.AppCompatActivity;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.InputDevice;
import android.view.InputEvent;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    private Button z;
    private BluetoothAdapter BtAdapter;
    Handler bluetoothIn;
    private final int handlerState = 0;
    private BluetoothSocket btSocket = null;
    private StringBuilder DataStringIN = new StringBuilder();
    private ConnectedThread MyConexionBT;
    private static final UUID BTMODULEUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private static String address = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        z = findViewById(R.id.z);
        z.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                MyConexionBT.write("i");
            }
        });
        VerificarEstadoBT();

        bluetoothIn = new Handler(){
            public void handleMessage(android.os.Message msg){
                if(msg.what == handlerState) {

                }
            }
        };
    }

    public void onResume() {
        super.onResume();

        BluetoothDevice device = BtAdapter.getRemoteDevice(address);

        try {
            btSocket = createBluetoothSocket(device);
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            btSocket.connect();
        } catch (IOException e) {
            e.printStackTrace();
        }

        MyConexionBT = new ConnectedThread(btSocket);
        MyConexionBT.start();
    }

     private BluetoothSocket createBluetoothSocket(BluetoothDevice device) throws IOException {

        return device.createInsecureRfcommSocketToServiceRecord(BTMODULEUUID);
     }

    private void VerificarEstadoBT() {
        BtAdapter = BluetoothAdapter.getDefaultAdapter();
        if(BtAdapter == null){
            Toast.makeText(getBaseContext(), "No hay soporte Bluetooth", Toast.LENGTH_SHORT);
        }else{
            if(BtAdapter.isEnabled()){
                Log.d("", "...Bluetooth Activado...");
            }else{
                Intent enablebtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(enablebtIntent, 1);
            }
        }
        Set<BluetoothDevice> pairedDevices = BtAdapter.getBondedDevices();

        if (pairedDevices.size() > 0) {
            // There are paired devices. Get the name and address of each paired device.
            for (BluetoothDevice device : pairedDevices) {
                if(device.getName().equals("MODULO")){
                    address = device.getAddress();
                }
            }
        }
    }

    private class ConnectedThread extends Thread{

        private final InputStream Instream;
        private final OutputStream OutStream;

        public ConnectedThread(BluetoothSocket socket){
            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            try {
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
            } catch (IOException e) {
                e.printStackTrace();
            }
            Instream = tmpIn;
            OutStream = tmpOut;
        }
        public void run(){
            byte[] byte_in = new byte[1];

            while(true){

                try {
                    Instream.read(byte_in);
                    char ch = (char) byte_in[0];
                    bluetoothIn.obtainMessage(handlerState, ch).sendToTarget();
                } catch (IOException e) {
                    break;
                }
            }
        }
        public void write(String input){

            try {
                OutStream.write(input.getBytes());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public class Dpad {
        final static int UP       = 0;
        final static int LEFT     = 1;
        final static int RIGHT    = 2;
        final static int DOWN     = 3;
        final static int CENTER   = 4;

        int directionPressed = -1; // initialized to -1

        public int getDirectionPressed(InputEvent event) {
            if (!isDpadDevice(event)) {
                return -1;
            }

            // If the input event is a MotionEvent, check its hat axis values.
            if (event instanceof MotionEvent) {

                // Use the hat axis value to find the D-pad direction
                MotionEvent motionEvent = (MotionEvent) event;
                float xaxis = motionEvent.getAxisValue(MotionEvent.AXIS_HAT_X);
                float yaxis = motionEvent.getAxisValue(MotionEvent.AXIS_HAT_Y);

                // Check if the AXIS_HAT_X value is -1 or 1, and set the D-pad
                // LEFT and RIGHT direction accordingly.
                if (Float.compare(xaxis, -1.0f) == 0) {
                    directionPressed =  Dpad.LEFT;
                } else if (Float.compare(xaxis, 1.0f) == 0) {
                    directionPressed =  Dpad.RIGHT;
                }
                // Check if the AXIS_HAT_Y value is -1 or 1, and set the D-pad
                // UP and DOWN direction accordingly.
                else if (Float.compare(yaxis, -1.0f) == 0) {
                    directionPressed =  Dpad.UP;
                } else if (Float.compare(yaxis, 1.0f) == 0) {
                    directionPressed =  Dpad.DOWN;
                }
            }

            // If the input event is a KeyEvent, check its key code.
            else if (event instanceof KeyEvent) {

                // Use the key code to find the D-pad direction.
                KeyEvent keyEvent = (KeyEvent) event;
                if (keyEvent.getKeyCode() == KeyEvent.KEYCODE_DPAD_LEFT) {
                    directionPressed = Dpad.LEFT;
                } else if (keyEvent.getKeyCode() == KeyEvent.KEYCODE_DPAD_RIGHT) {
                    directionPressed = Dpad.RIGHT;
                } else if (keyEvent.getKeyCode() == KeyEvent.KEYCODE_DPAD_UP) {
                    directionPressed = Dpad.UP;
                } else if (keyEvent.getKeyCode() == KeyEvent.KEYCODE_DPAD_DOWN) {
                    directionPressed = Dpad.DOWN;
                } else if (keyEvent.getKeyCode() == KeyEvent.KEYCODE_DPAD_CENTER) {
                    directionPressed = Dpad.CENTER;
                }
            }
            return directionPressed;
        }

        public boolean isDpadDevice(InputEvent event) {
            // Check that input comes from a device with directional pads.
            if ((event.getSource() & InputDevice.SOURCE_DPAD)
                    != InputDevice.SOURCE_DPAD) {
                return true;
            } else {
                return false;
            }
        }
    }
}