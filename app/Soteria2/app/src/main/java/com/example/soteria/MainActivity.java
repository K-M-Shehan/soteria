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
import java.net.HttpURLConnection;
import java.net.URL;

public class MainActivity extends AppCompatActivity {

    private static final String ARDUINO_IP = "192.168.1.100"; // Replace with your Arduino's IP address
    private static final int ARDUINO_PORT = 1234; // Replace with your Arduino's port number
    private static final String CHANNEL_ID = "notification_channel";
    private static final int DISTANCE_THRESHOLD = 5; // Adjust this threshold as per your sensor

    private SensorManager sensorManager;

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

        systemOnBtn.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @Override
            public void onClick(View v) {
                sendData("SYSTEM_ON");
                Toast.makeText(MainActivity.this, "System turned on", Toast.LENGTH_SHORT).show();
            }
        });

        systemOffBtn.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @Override
            public void onClick(View v) {
                sendData("SYSTEM_OFF");
                Toast.makeText(MainActivity.this, "System turned off", Toast.LENGTH_SHORT).show();
            }
        });

        buzzerOnBtn.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @Override
            public void onClick(View v) {
                sendData("BUZZER_ON");
                Toast.makeText(MainActivity.this, "Buzzer turned on", Toast.LENGTH_SHORT).show();
            }
        });

        buzzerOffBtn.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @Override
            public void onClick(View v) {
                sendData("BUZZER_OFF");
                Toast.makeText(MainActivity.this, "Buzzer turned off", Toast.LENGTH_SHORT).show();
            }
        });

        createNotificationChannel();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        // Unregister sensor event listener to avoid memory leaks
        sensorManager.unregisterListener(sensorEventListener);
    }

    /** @noinspection CallToPrintStackTrace*/
    private void sendData(final String data) {
        new Thread(() -> {
            try {
                HttpURLConnection connection = (HttpURLConnection) new URL("http://" + ARDUINO_IP + ":" + ARDUINO_PORT + "/").openConnection();
                connection.setRequestMethod("POST");
                connection.setDoOutput(true);
                OutputStream outputStream = connection.getOutputStream();
                outputStream.write(data.getBytes());
                outputStream.flush();
                connection.disconnect();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }).start();
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
}
