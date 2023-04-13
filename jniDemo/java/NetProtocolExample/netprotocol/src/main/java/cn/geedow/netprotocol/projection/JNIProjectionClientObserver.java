package cn.geedow.netprotocol.projection;

import android.util.Log;

public class JNIProjectionClientObserver {
    private String tag = "ProjectionClientObserver";

    public JNIProjectionClientObserver() {
        Log.d(tag, "constructor");
    }

    public void onConnectionStatusChanged(int status, int errCode) {
        Log.d(tag, "onConnectionStatusChanged");
    }

    public void onProjectionReplied(int result, JNIProjectionInfo projectionInfo) {
        Log.d(tag, "onProjectionReplied");
    }

    public void onIceCandidate(String sdpMid, String sdpMLineIndex, String candidate) {
        Log.d(tag, "onIceCandidate");
    }
}
