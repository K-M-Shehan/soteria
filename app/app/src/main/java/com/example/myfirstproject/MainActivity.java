package com.example.myfirstproject;

import android.os.Bundle;
import android.widget.Button;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btnTurnOnSystem = findViewById(R.id.btnTurnOnSystem);
        Button btnTurnOffSystem = findViewById(R.id.btnTurnOffSystem);
        Button btnTurnOnBuzzer = findViewById(R.id.btnTurnOnBuzzer);
        Button btnTurnOffBuzzer = findViewById(R.id.btnTurnOffBuzzer);

        btnTurnOnSystem.setOnClickListener(v -> {
            // Code to turn on the system
            // You can add your logic here
            Toast.makeText(MainActivity.this, "System turned ON", Toast.LENGTH_SHORT).show();
        });

        btnTurnOffSystem.setOnClickListener(v -> {
            // Code to turn off the system
            // You can add your logic here
            Toast.makeText(MainActivity.this, "System turned OFF", Toast.LENGTH_SHORT).show();
        });

        btnTurnOnBuzzer.setOnClickListener(v -> {
            // Code to turn on the buzzer
            // You can add your logic here
            Toast.makeText(MainActivity.this, "Buzzer turned ON", Toast.LENGTH_SHORT).show();
        });

        btnTurnOffBuzzer.setOnClickListener(v -> {
            // Code to turn off the buzzer
            // You can add your logic here
            Toast.makeText(MainActivity.this, "Buzzer turned OFF", Toast.LENGTH_SHORT).show();
        });
    }
}
