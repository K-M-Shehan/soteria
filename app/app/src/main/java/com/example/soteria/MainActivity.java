import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

public class MainActivity extends AppCompatActivity {

    private Button systemOnBtn, systemOffBtn, buzzerOnBtn, buzzerOffBtn;
    private TCPClient tcpClient;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize buttons
        systemOnBtn = findViewById(R.id.systemOnBtn);
        systemOffBtn = findViewById(R.id.systemOffBtn);
        buzzerOnBtn = findViewById(R.id.buzzerOnBtn);
        buzzerOffBtn = findViewById(R.id.buzzerOffBtn);

        // Initialize TCP client
        tcpClient = new TCPClient();

        // Set click listeners for each button
        systemOnBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Add your functionality for turning the system on
                sendDataToServer("Data to send for turning system ON");
                showToast("System turned ON");
            }
        });

        systemOffBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Add your functionality for turning the system off
                sendDataToServer("Data to send for turning system OFF");
                showToast("System turned OFF");
            }
        });

        buzzerOnBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Add your functionality for turning the buzzer on
                sendDataToServer("Data to send for turning buzzer ON");
                showToast("Buzzer turned ON");
            }
        });

        buzzerOffBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Add your functionality for turning the buzzer off
                sendDataToServer("Data to send for turning buzzer OFF");
                showToast("Buzzer turned OFF");
            }
        });

        // Connect to the TCP server
        tcpClient.execute();
    }

    // Helper method to show a toast message
    private void showToast(String message) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

    // Method to send data to the server
    private void sendDataToServer(final String dataToSend) {
        if (tcpClient != null && tcpClient.isConnected()) {
            tcpClient.sendData(dataToSend);
        }
    }

    // TCP Client AsyncTask
    private class TCPClient extends AsyncTask<Void, Void, Boolean> {

        private Socket socket;
        private DataOutputStream outputStream;

        @Override
        protected Boolean doInBackground(Void... params) {
            try {
                socket = new Socket("192.168.193.77", 1050);
                outputStream = new DataOutputStream(socket.getOutputStream());
                return true;
            } catch (UnknownHostException e) {
                e.printStackTrace();
                return false;
            } catch (IOException e) {
                e.printStackTrace();
                return false;
            }
        }

        public boolean isConnected() {
            return socket != null && socket.isConnected();
        }

        public void sendData(String data) {
            if (outputStream != null) {
                try {
                    outputStream.writeBytes(data + "\n");
                    outputStream.flush();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        @Override
        protected void onPostExecute(Boolean connected) {
            if (!connected) {
                showToast("Failed to connect to server");
            }
        }

        @Override
        protected void onCancelled() {
            try {
                if (socket != null) {
                    socket.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}