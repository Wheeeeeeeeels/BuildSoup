package cn.geedow.netprotocolexample.projection;

import android.util.Log;

import cn.geedow.netprotocol.projection.JNIProjectionServerObserver;

public class ProjectionServerObserver extends JNIProjectionServerObserver {
    private String tag = "ProjectionServerObserver";
    @Override
    public void onClientStartProject(String s, String s1) {
        Log.d(tag,
                "projectionCode: " + s + "\t" +
                "name: " + s1);
    }
}
