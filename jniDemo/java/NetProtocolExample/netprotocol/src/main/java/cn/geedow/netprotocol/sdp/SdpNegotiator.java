package cn.geedow.netprotocol.sdp;

import java.util.ArrayList;

import cn.geedow.netprotocol.JNICommType;

public class SdpNegotiator {
    static {
        String strLoadCheck = System.getProperty("TestDllLoaded", "false");
        if (strLoadCheck.equals("false"))
        {
            strLoadCheck = System.setProperty("TestDllLoaded", "true");
            System.loadLibrary("NetProtocol");
        }
    }

    private long nativeSdpNegotiator;

    public SdpNegotiator() {
        nativeSdpNegotiator = nativeCreate();
    }

    public void dispose() {
        checkSdpNegotiatorExists();
        nativeDestroy(nativeSdpNegotiator);
        nativeSdpNegotiator = 0L;
    }

    public void setLocalSdpOffer(String sdpOffer) {
        if (sdpOffer == null) {
            return;
        }
        checkSdpNegotiatorExists();
        nativeSetLocalSdpOffer(nativeSdpNegotiator, sdpOffer);
    }

    public String getLocalSdpOffer() {
        return getLocalSdpOffer("", "");
    }

    public String getLocalSdpOffer(String vcodecSelected,
                                   String acodecSelected) {
        checkSdpNegotiatorExists();
        JNICommType outSdpOffer = new JNICommType();
        nativeGetLocalSdpOffer(nativeSdpNegotiator, vcodecSelected, acodecSelected, outSdpOffer);
        return outSdpOffer.str;
    }

    public String getLocalJsonOffer(boolean transportNeed, ArrayList<String> midList) {
        checkSdpNegotiatorExists();
        if (midList == null) {
            midList = new ArrayList<>();
        }
        JNICommType outJsonOffer = new JNICommType();
        nativeGetLocalJsonOffer(nativeSdpNegotiator, transportNeed, midList, outJsonOffer);
        return outJsonOffer.str;
    }

    public void addRemoteJsonAnswer(String sdpAnswer) {
        if (sdpAnswer == null) {
            return;
        }
        checkSdpNegotiatorExists();
        nativeAddRemoteJsonAnswer(nativeSdpNegotiator, sdpAnswer);
    }

    public void removeRemoteJsonAnswer(String mid) {
        if (mid == null) {
            return;
        }
        ArrayList<String> midList = new ArrayList<>();
        midList.add(mid);
        removeRemoteJsonAnswer(midList);
    }

    public void removeRemoteJsonAnswer(ArrayList<String> midList) {
        if (midList == null || midList.isEmpty()) {
            return;
        }
        checkSdpNegotiatorExists();
        nativeRemoveRemoteJsonAnswer(nativeSdpNegotiator, midList);
    }

    public String createRemoteSdpAnswer() {
        checkSdpNegotiatorExists();
        JNICommType outSdpAnswer = new JNICommType();
        nativeCreateRemoteSdpAnswer(nativeSdpNegotiator, outSdpAnswer);
        return outSdpAnswer.str;
    }

    private void checkSdpNegotiatorExists() {
        if (nativeSdpNegotiator == 0L) {
            throw new IllegalStateException("SdpNegotiator has been disposed.");
        }
    }

    private native static long nativeCreate();

    private native static int nativeDestroy(long negotiator);

    private native static int nativeSetLocalSdpOffer(long negotiator, String sdpOffer);

    private native static int nativeGetLocalSdpOffer(long negotiator, String vcodecSelected,
                                                     String acodecSelected, JNICommType outSdpOffer);

    private native static int nativeGetLocalJsonOffer(long negotiator, boolean transportNeed,
                                                      ArrayList<String> midList,
                                                      JNICommType outJsonOffer);

    private native static int nativeAddRemoteJsonAnswer(long negotiator, String sdpAnswer);

    private native static int nativeRemoveRemoteJsonAnswer(long negotiator, ArrayList<String> midList);

    private native static int nativeCreateRemoteSdpAnswer(long negotiator, JNICommType outSdpAnswer);
}
