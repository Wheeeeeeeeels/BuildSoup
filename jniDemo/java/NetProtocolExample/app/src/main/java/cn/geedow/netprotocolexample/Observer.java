package cn.geedow.netprotocolexample;

import cn.geedow.netprotocol.JNIPushLogParams;
import cn.geedow.netprotocol.JNIObserver;

public class Observer extends JNIObserver {
    @Override
    public void onConversationDurationStatus(int status, int hours, int minutes){
        super.onConversationDurationStatus(status, hours, minutes);
    }

    @Override
    public void onPushLog() {
        super.onPushLog();
        JNIPushLogParams pushLogParams = new JNIPushLogParams();
//        pushLogParams.account = m_account;
//        pushLogParams.logName = cacheDir;
//        nRet = JNINetProtocol.pushLog(pushLogParams);
//        if (nRet != 0) {
//            String msg = JNINetProtocol.codeToMsg(nRet);
//            Log.e(TAG, "pushLog failed! ret:" + nRet + ", msg:" + JNINetProtocol.codeToMsg(nRet));
//            return;
//        };
    }

    @Override
    public void onTimeSynchronization(long serverTimestamp) {
        super.onTimeSynchronization(serverTimestamp);
    }
}
