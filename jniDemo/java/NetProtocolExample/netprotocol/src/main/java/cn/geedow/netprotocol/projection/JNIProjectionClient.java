package cn.geedow.netprotocol.projection;

import cn.geedow.netprotocol.JNICommType;

public class JNIProjectionClient {
    static {
        String strLoadCheck = System.getProperty("TestDllLoaded", "false");
        if (strLoadCheck.equals("false"))
        {
            strLoadCheck = System.setProperty("TestDllLoaded", "true");
            System.loadLibrary("NetProtocol");
        }
    }

    public native static int init();

    public native static int setIpv4Address(String ipv4Address);

    public native static int registerObserver(JNIProjectionClientObserver observer);

    public native static int startProject(String projectionCode, String name);

    public native static int finishProject();

    public native static int sendSdpOffer(String sdpOffer, JNICommType sdpAnswer);

    public native static int sendIceCandidate(String sdpMid, String sdpMLineIndex, String candidate);
}
