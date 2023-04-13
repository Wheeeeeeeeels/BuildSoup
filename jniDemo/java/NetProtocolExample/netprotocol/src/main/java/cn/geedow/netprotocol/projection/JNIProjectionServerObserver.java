package cn.geedow.netprotocol.projection;

import android.util.Log;

/**
 * 投屏服务端事件回调类
 */
public class JNIProjectionServerObserver {
    private String tag = "ProjectionServerObserver";

    public JNIProjectionServerObserver() {
        Log.d(tag, "constructor");
    }

    public void onClientStartProject(String uniqueIdentityCode, String name) {
        Log.d(tag, "onClientStartProject");
    }

    public void onClientFinishProject(String uniqueIdentityCode, String name) {
        Log.d(tag, "onClientFinishProject");
    }

    public void onSdpOffer(String uniqueIdentityCode, int msgId, String sdpOffer) {
        Log.d(tag, "onSdpOffer");
    }

    public void onIceCandidate(String uniqueIdentityCode, String sdpMid, int sdpMLineIndex, String candidate) {
        Log.d(tag, "onIceCandidate");
    }
}
