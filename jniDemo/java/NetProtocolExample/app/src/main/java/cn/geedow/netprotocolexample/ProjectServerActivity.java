package cn.geedow.netprotocolexample;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import cn.geedow.netprotocol.JNIBasicInfo;
import cn.geedow.netprotocol.JNILogObserver;
import cn.geedow.netprotocol.JNINetProtocol;
import cn.geedow.netprotocol.projection.JNIProjectionServer;
import cn.geedow.netprotocol.projection.JNIProjectionServerObserver;

public class ProjectServerActivity extends AppCompatActivity {

    private static final String TAG = "ProjectServer";
    private TextView textInformation;

    private static boolean isStart = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_projectserver);

        this.textInformation = findViewById(R.id.textInformation);

        init();

        findViewById(R.id.startProjectServer).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (isStart == true) {
                    return;
                }

                isStart = true;
                JNIProjectionServer.startProjectionService();
            }
        });

        findViewById(R.id.stopProjectServer).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (isStart == false) {
                    return;
                }

                JNIProjectionServer.stopProjectionService();
                isStart = false;
            }
        });

    }

    private void init() {
        JNINetProtocol.setLogObserver(new JNILogObserver() {
            @Override
            public void onPrintLog(int level, String log) {
                Log.e(TAG, log);
                textInformation.append(log);
            }
        });

        JNIBasicInfo basicInfo = new JNIBasicInfo();
        basicInfo.terminalType = 4;
        basicInfo.udid = "x0-xx-xx-xx-xx-xx";
        basicInfo.serialNumber = "serialNumber";
        JNINetProtocol.setParams(basicInfo);

        JNIProjectionServer.registerObserver(new JNIProjectionServerObserver());

        String ipv4Address = "172.25.27.217";
        String name = "server_name";
        String serialNumber = "server_serialNumber";
        JNIProjectionServer.applyForProjectionCodeDebug(ipv4Address, name, serialNumber);

        JNIProjectionServer.setIpv4Address(ipv4Address);
    }
}
