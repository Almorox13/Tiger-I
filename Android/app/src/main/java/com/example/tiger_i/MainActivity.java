package com.example.tiger_i;

import androidx.appcompat.app.AppCompatActivity;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.InputDevice;
import android.view.MotionEvent;
import android.widget.Toast;

import java.io.IOException;
import java.util.Set;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    private UUID BTMODULEUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private BluetoothAdapter btAdapter;
    private BluetoothSocket btSocket;
    private Bluetooth bt;
    private String address;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        VerificarEstadoBT();
    }

    public void onResume() {
        super.onResume();
        BluetoothDevice device = btAdapter.getRemoteDevice(address);

        try {
            btSocket = createBluetoothSocket(device);
            btSocket.connect();
        } catch (IOException e) {
            Toast.makeText(this, "Conexion con MODULO fallida", Toast.LENGTH_SHORT);
        }

        bt = new Bluetooth(btSocket);
    }

    private BluetoothSocket createBluetoothSocket(BluetoothDevice device) throws IOException {

        return device.createInsecureRfcommSocketToServiceRecord(BTMODULEUUID);
    }

    private void VerificarEstadoBT() {
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        if (btAdapter == null) {
            Toast.makeText(getBaseContext(), "No hay soporte Bluetooth", Toast.LENGTH_SHORT);
        } else {
            if (btAdapter.isEnabled()) {
                Toast.makeText(getBaseContext(), "Bluetooth encendido", Toast.LENGTH_SHORT);
            } else {
                Intent enablebtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(enablebtIntent, 1);
            }
        }
        Set<BluetoothDevice> pairedDevices = btAdapter.getBondedDevices();

        if (pairedDevices.size() > 0) {
            for (BluetoothDevice device : pairedDevices) {
                if (device.getName().equals("MODULO")) {
                    address = device.getAddress();
                }
            }
        }
    }

    public boolean onGenericMotionEvent(MotionEvent event) {

        // Check that the event came from a game controller
        if ((event.getSource() & InputDevice.SOURCE_JOYSTICK) ==
                InputDevice.SOURCE_JOYSTICK &&
                event.getAction() == MotionEvent.ACTION_MOVE) {

            // Process all historical movement samples in the batch
            final int historySize = event.getHistorySize();

            // Process the movements starting from the
            // earliest historical position in the batch
            for (int i = 0; i < historySize; i++) {
                // Process the event at historical position i
                processJoystickInput(event, i);
            }

            // Process the current movement sample in the batch (position -1)
            processJoystickInput(event, -1);
            return true;
        }
        return super.onGenericMotionEvent(event);
    }

    private static float getCenteredAxis(MotionEvent event,
                                         InputDevice device, int axis, int historyPos) {
        final InputDevice.MotionRange range =
                device.getMotionRange(axis, event.getSource());

        // A joystick at rest does not always report an absolute position of
        // (0,0). Use the getFlat() method to determine the range of values
        // bounding the joystick axis center.
        if (range != null) {
            final float flat = range.getFlat();
            final float value =
                    historyPos < 0 ? event.getAxisValue(axis) :
                            event.getHistoricalAxisValue(axis, historyPos);

            // Ignore axis values that are within the 'flat' region of the
            // joystick axis center.
            if (Math.abs(value) > flat) {
                return value;
            }
        }
        return 0;
    }

    private void processJoystickInput(MotionEvent event, int historyPos) {

        InputDevice mInputDevice = event.getDevice();

        // Calculate the horizontal distance to move by
        // using the input value from one of these physical controls:
        // the left control stick, hat axis, or the right control stick.
        float x = getCenteredAxis(event, mInputDevice,
                MotionEvent.AXIS_RTRIGGER, historyPos);


        if (x == 0) {
            x = getCenteredAxis(event, mInputDevice,
                    MotionEvent.AXIS_RTRIGGER, historyPos);
            bt.write("0");
        }
        // Calculate the vertical distance to move by
        // using the input value from one of these physical controls:
        // the left control stick, hat switch, or the right control stick.
        float y = getCenteredAxis(event, mInputDevice,
                MotionEvent.AXIS_LTRIGGER, historyPos);

        traducirGatillos(y, x);

        if (y == 0) {
            y = getCenteredAxis(event, mInputDevice,
                    MotionEvent.AXIS_LTRIGGER, historyPos);
            bt.write("1");
        }
    }

    public void traducirGatillos(float y, float x) {

        if (x <= 0.1) {
            if (y <= 0.1) {
                Log.d("xycoord", "y:" + y + "           x:" + x);  //  0  0
                bt.write("a");
            } else {
                if (y <= 0.3) {
                    Log.d("xycoord", "y:" + y + "           x:" + x);  //  0  1
                    bt.write("b");
                } else {
                    if (y <= 0.55) {
                        Log.d("xycoord", "y:" + y + "           x:" + x);  //  0  2
                        bt.write("c");
                    } else {
                        if (y <= 0.75) {
                            Log.d("xycoord", "y:" + y + "           x:" + x);  //  0  3
                            bt.write("d");
                        } else {
                            Log.d("xycoord", "y:" + y + "           x:" + x);  //  0  4
                            bt.write("e");
                        }
                    }
                }
            }
        } else {
            if (x <= 0.3) {
                if (y <= 0.1) {
                    Log.d("xycoord", "y:" + y + "           x:" + x);  //  1  0
                    bt.write("f");
                } else {
                    if (y <= 0.3) {
                        Log.d("xycoord", "y:" + y + "           x:" + x);  //  1  1
                        bt.write("g");
                    } else {
                        if (y <= 0.55) {
                            Log.d("xycoord", "y:" + y + "           x:" + x);  //  1  2
                            bt.write("h");
                        } else {
                            if (y <= 0.75) {
                                Log.d("xycoord", "y:" + y + "           x:" + x);  //  1  3
                                bt.write("i");
                            } else {
                                Log.d("xycoord", "y:" + y + "           x:" + x);  //  1  4
                                bt.write("j");
                            }
                        }
                    }
                }
            } else {
                if (x <= 0.55) {
                    if (y <= 0.1) {
                        Log.d("xycoord", "y:" + y + "           x:" + x);  //  2  0
                        bt.write("k");
                    } else {
                        if (y <= 0.3) {
                            Log.d("xycoord", "y:" + y + "           x:" + x);  //  2  1
                            bt.write("l");
                        } else {
                            if (y <= 0.55) {
                                Log.d("xycoord", "y:" + y + "           x:" + x);  //  2  2
                                bt.write("m");
                            } else {
                                if (y <= 0.75) {
                                    Log.d("xycoord", "y:" + y + "           x:" + x);  //  2  3
                                    bt.write("n");
                                } else {
                                    Log.d("xycoord", "y:" + y + "           x:" + x);  //  2  4
                                    bt.write("o");
                                }
                            }
                        }
                    }
                } else {
                    if (x <= 0.75) {
                        if (y <= 0.1) {
                            Log.d("xycoord", "y:" + y + "           x:" + x);  //  3  0
                            bt.write("p");
                        } else {
                            if (y <= 0.3) {
                                Log.d("xycoord", "y:" + y + "           x:" + x);  //  3  1
                                bt.write("q");
                            } else {
                                if (y <= 0.55) {
                                    Log.d("xycoord", "y:" + y + "           x:" + x);  //  3  2
                                    bt.write("r");
                                } else {
                                    if (y <= 0.75) {
                                        Log.d("xycoord", "y:" + y + "           x:" + x);  //  3  3
                                        bt.write("s");
                                    } else {
                                        Log.d("xycoord", "y:" + y + "           x:" + x);  //  3  4
                                        bt.write("t");
                                    }
                                }
                            }
                        }
                    } else {
                        if (y <= 0.1) {
                            Log.d("xycoord", "y:" + y + "           x:" + x);  //  4  0
                            bt.write("u");
                        } else {
                            if (y <= 0.3) {
                                Log.d("xycoord", "y:" + y + "           x:" + x);  //  4  1
                                bt.write("v");
                            } else {
                                if (y <= 0.55) {
                                    Log.d("xycoord", "y:" + y + "           x:" + x);  //  4  2
                                    bt.write("w");
                                } else {
                                    if (y <= 0.75) {
                                        Log.d("xycoord", "y:" + y + "           x:" + x);  //  4  3
                                        bt.write("x");
                                    } else {
                                        Log.d("xycoord", "y:" + y + "           x:" + x);  //  4  4
                                        bt.write("y");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}