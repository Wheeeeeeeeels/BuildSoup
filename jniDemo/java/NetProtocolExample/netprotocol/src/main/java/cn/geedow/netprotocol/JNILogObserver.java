package cn.geedow.netprotocol;

import android.util.Log;

public class JNILogObserver {
    private static final String TAG = "JNILogObserver";

    public int logLevel;

    public void onPrintLog(int level, String log) {
        Log.d(TAG, level + " " + log);
    }

    public void onPrintBinaryLog(int level, byte[] log) {
        // print log in binary streams        
    }
}
