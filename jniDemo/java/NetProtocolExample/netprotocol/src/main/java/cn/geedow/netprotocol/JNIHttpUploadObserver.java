package cn.geedow.netprotocol;

import android.util.Log;

public class JNIHttpUploadObserver {
    private static final String TAG = "JNIHttpUploadObserver";

    public void onFailed(int requestCode, int errorCode, String extraInfo) {
        Log.d(TAG, "JAVA onFailed, requestCode[" + requestCode + "] errorCode[" + errorCode + "]");
    }

    public void onCompleted(int requestCode, String url) {
        Log.d(TAG, "JAVA onCompleted, requestCode[" + requestCode + "]");
    }
}
