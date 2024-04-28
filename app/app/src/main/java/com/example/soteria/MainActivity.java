package com.example.soteria;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Context;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;

/** @noinspection ALL*/
public class MainActivity extends AppCompatActivity {

    private static final String ARDUINO_IP = "192.168.193.77"; // Replace with your Arduino's IP address
    private static final int ARDUINO_PORT = 1050; // Replace with your Arduino's port number
    private static final String CHANNEL_ID = "notification_channel";
    private static final int DISTANCE_THRESHOLD = 5; // Adjust this threshold as per your sensor

    private Socket socket;
    private OutputStream outputStream;
    private SensorManager sensorManager;

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button systemOnBtn = findViewById(R.id.systemOnBtn);
        Button systemOffBtn = findViewById(R.id.systemOffBtn);
        Button buzzerOnBtn = findViewById(R.id.buzzerOnBtn);
        Button buzzerOffBtn = findViewById(R.id.buzzerOffBtn);

        // Initialize sensor manager and register IR sensor
        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        Sensor irSensor = sensorManager.getDefaultSensor(Sensor.TYPE_PROXIMITY);

        // Register sensor event listener
        sensorManager.registerListener(sensorEventListener, irSensor, SensorManager.SENSOR_DELAY_NORMAL);

        // Connect to the TCP server
        connectToServer();

        systemOnBtn.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @Override
            public void onClick(View v) {
                sendData("11111");
                Toast.makeText(MainActivity.this, "System turned on", Toast.LENGTH_SHORT).show();
            }
        });

        systemOffBtn.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @Override
            public void onClick(View v) {
                sendData("22222");
                Toast.makeText(MainActivity.this, "System turned off", Toast.LENGTH_SHORT).show();
            }
        });

        buzzerOnBtn.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @Override
            public void onClick(View v) {
                sendData("33333");
                Toast.makeText(MainActivity.this, "Buzzer turned on", Toast.LENGTH_SHORT).show();
            }
        });

        buzzerOffBtn.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @Override
            public void onClick(View v) {
                sendData("44444");
                Toast.makeText(MainActivity.this, "Buzzer turned off", Toast.LENGTH_SHORT).show();
            }
        });

        createNotificationChannel();
    }

    private void sendData(String data) {
        sendDataToTCPServer(ARDUINO_IP, ARDUINO_PORT, data);
    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    protected void onDestroy() {
        super.onDestroy();
        // Close the socket when the activity is destroyed
        closeSocket();

        // Unregister sensor event listener to avoid memory leaks
        sensorManager.unregisterListener(sensorEventListener);
    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    private void connectToServer() {
        new Thread(() -> {
            try {
                socket = new Socket(ARDUINO_IP, ARDUINO_PORT);
                outputStream = socket.getOutputStream();
                // Notify when connected
                showNotification("Connected to Server", "Connected to the server.");
            } catch (IOException e) {
                e.printStackTrace();
                // Handle connection error
                showToast("Failed to connect to server");
            }
        }).start();
    }

    private void sendDataToTCPServer(final String serverAddress, final int serverPort, final String data) {
        new Thread(() -> {
            Socket socket = null;
            OutputStream outputStream = null;
            try {
                // Establish a socket connection to the server
                socket = new Socket(serverAddress, serverPort);
                outputStream = socket.getOutputStream();

                // Write the data to the output stream
                outputStream.write(data.getBytes());
                outputStream.flush();
            } catch (IOException e) {
                e.printStackTrace();
                // Handle connection or data transmission errors here
            } finally {
                try {
                    // Close the output stream and socket
                    if (outputStream != null) outputStream.close();
                    if (socket != null) socket.close();
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        }).start();
    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    private void closeSocket() {
        try {
            if (socket != null) {
                socket.close();
                // Notify when disconnected
                showNotification("Disconnected from Server", "Disconnected from the server.");
            }
        } catch (IOException e) {
            e.printStackTrace();
            // Handle socket closure error
        }
    }

    private final SensorEventListener sensorEventListener = new SensorEventListener() {
        @RequiresApi(api = Build.VERSION_CODES.O)
        @Override
        public void onSensorChanged(SensorEvent event) {
            if (event.sensor.getType() == Sensor.TYPE_PROXIMITY) {
                float distance = event.values[0];
                boolean sensorDetected = (distance < DISTANCE_THRESHOLD);
                if (sensorDetected) {
                    triggerNotification();
                }
            }
        }

        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
            // Handle accuracy changes if needed
        }
    };

    @RequiresApi(api = Build.VERSION_CODES.O)
    private void triggerNotification() {
        NotificationManager notificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        Notification.Builder builder = new Notification.Builder(this, CHANNEL_ID)
                .setContentTitle("Motion Detected")
                .setContentText("Motion detected near the sensor")
                .setSmallIcon(R.drawable.ic_notification)
                .setAutoCancel(true);

        notificationManager.notify(0, builder.build());
    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    private void showNotification(String title, String message) {
        NotificationManager notificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        Notification.Builder builder = new Notification.Builder(this, CHANNEL_ID)
                .setContentTitle(title)
                .setContentText(message)
                .setSmallIcon(R.drawable.ic_notification)
                .setAutoCancel(true);

        notificationManager.notify(1, builder.build());
    }

    private void createNotificationChannel() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            NotificationChannel channel = new NotificationChannel(CHANNEL_ID, "Channel Name", NotificationManager.IMPORTANCE_HIGH);
            channel.setDescription("Channel Description");
            channel.enableLights(true);
            channel.setLightColor(Color.RED);
            channel.enableVibration(true);
            NotificationManager notificationManager = getSystemService(NotificationManager.class);
            notificationManager.createNotificationChannel(channel);
        }
    }

    private void showToast(String message) {
        runOnUiThread(() -> Toast.makeText(MainActivity.this, message, Toast.LENGTH_SHORT).show());
    }

    public OutputStream getOutputStream() {
        return outputStream;
    }

    public void setOutputStream(OutputStream outputStream) {
        this.outputStream = outputStream;
    }
}