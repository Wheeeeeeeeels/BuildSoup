package cn.geedow.netprotocol;

import android.util.Log;

import cn.geedow.netprotocol.basicDataStructure.JNIHardTerminalDeviceInfo;

public class JNIObserver {
    private static final String TAG = "JNIObserver";

    // 0 unkonwn, 1 connected, 2 disconnect
    public int onFetchDeviceNetState() {
        return 0;
    }

    public void onTokenBecameInvalid() {
        Log.d(TAG, "JAVA onTokenBecameInvalid");
    }

    public void onOthersLogin() {
        Log.d(TAG, "JAVA onOthersLogin");
    }

    
    public void onServiceAvailableChange(boolean available, int code, String message) {
        Log.e(TAG, "JAVA onServiceAvailableChange: " + String.valueOf(available));
    }

    public void onNetworkConnectStatusChange(int state, int code, String message) {
        Log.e(TAG, "JAVA onNetworkConnectStatusChange: " + String.valueOf(state));
    }

    public void onOnlineStateChange(boolean online) {
        Log.e(TAG, "JAVA onOnlineStateChange: " + String.valueOf(online));
    }

    public void onVersionUpgrade(boolean foreStatus, String downLoadUrl, String version, String details) {
        Log.e(TAG, "JAVA onVersionUpgrade: " + String.valueOf(foreStatus) + downLoadUrl + version + details);
    }

    public void onVersionUpgrade(String serialNumber, boolean foreStatus, String downLoadUrl, String version, String details) {
        Log.e(TAG, "JAVA onVersionUpgrade: " + String.valueOf(foreStatus) + downLoadUrl + version + details);
    }

    public void onPushLog(){Log.d(TAG, "JAVA onPushLog");}

    public void onPushLogResult(boolean result) { Log.d(TAG, "JAVA onPushLogResult"); }

    public void onServiceExpired(boolean isExpired, String expiredDate, int daysToExpiredDate) { Log.d(TAG, "JAVA onServiceExpired"); }

    public void onConversationDurationStatus(int status, int hours, int minutes) { Log.d(TAG, "JAVA onConversationDurationStatus"); }

    public void onTimeSynchronization(long serverTimestamp) {
        Log.d(TAG, "JAVA onTimeSynchronization: " + serverTimestamp);
    }

    public void onEvictedByCorp() {
        Log.d(TAG, "JAVA onEvictedByCorp");
    }
    
    public void onHardTerminalDeviceInfoChanged(JNIHardTerminalDeviceInfo deviceInfo) {
        Log.d(TAG, "JAVA onHardTerminalDeviceInfoChanged: " + deviceInfo.nickName);
    }

    public void onConferenceToBegin(String username, String subject, long startTime, long endTime) {
        Log.d(TAG, "onConferenceToBegin");
    }

    public void onConferenceCreated(String username, String subject, long startTime, long endTime) {
        Log.d(TAG, "onConferenceCreated");
    }

    public void onConferenceCanceled(String username, String ruid, String subject, int reason) {
        Log.d(TAG, "onConferenceCanceled");
    }
}
