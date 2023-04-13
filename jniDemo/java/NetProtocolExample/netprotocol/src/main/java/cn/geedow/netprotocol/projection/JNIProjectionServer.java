package cn.geedow.netprotocol.projection;

import cn.geedow.netprotocol.JNICommType;

/**
 * 投屏服务端类
 */
public class JNIProjectionServer {
    static {
        String strLoadCheck = System.getProperty("TestDllLoaded", "false");
        if (strLoadCheck.equals("false"))
        {
            strLoadCheck = System.setProperty("TestDllLoaded", "true");
            System.loadLibrary("NetProtocol");
        }
    }

    public native static int init();

    public native static int test();

    public native static int registerObserver(JNIProjectionServerObserver observer);

    public native static int setIpv4Address(String ipv4Address);

    public native static int startProjectionService();

    public native static int stopProjectionService();

    public native static int sendSdpAnswer(String uniqueIdentityCode, int msgId, String sdpAnswer);

    public native static int sendIceCandidate(String uniqueIdentityCode, String sdpMid, int sdpMLineIndex, String iceCandidate);

    public native static int replyProjectionRequest(String uniqueIdentityCode, int result);

    public native static int stopProjectingFromClient(String uniqueIdentityCode);

    public native static int setProjectPropertiesByApp(String name, String serialNumber, String projectionCode, String wsAddress);

    public native static int applyForProjectionCode(String ipv4Address, String name, String serialNumber, JNICommType projectionCode);

    public native static int applyForProjectionCodeDebug(String ipv4Address, String name, String serialNumber);

    public native static int debugStartHttpServer(int port);

    public native static int debugStopHttpServer();

}
