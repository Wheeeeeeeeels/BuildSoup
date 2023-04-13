package cn.geedow.netprotocolexample;

import android.util.Log;

import java.util.ArrayList;

import cn.geedow.netprotocol.JNIRoomObserver;
import cn.geedow.netprotocol.basicDataStructure.JNIBarrage;
import cn.geedow.netprotocol.basicDataStructure.JNIIMMessage;
import cn.geedow.netprotocol.basicDataStructure.JNIView;

public class RoomObserver extends JNIRoomObserver {
    public String tag = "guol_RoomObserver";

    @Override
    public void onAudioInStatus(String roomId, String sourceAccount, String targetAccount, boolean status) {
        super.onAudioInStatus(roomId, sourceAccount, targetAccount, status);
        Log.e(tag, "roomId: " + roomId +
                " sourceAccount: " + sourceAccount +
                " targetAccount: " + targetAccount +
                " status: " + status);
    }

    @Override
    public void onMessage(String accout, String nickname, int messageType) {
        super.onMessage(accout, nickname, messageType);
        Log.e(tag, "accout: " + accout +
                " nickname: " + nickname +
                " messageType: " + messageType);
    }

    @Override
    public void onInvite(
            String roomId, String subject, String accountFrom, String usernameFrom,
            long expireTime, String password, String userIcon, boolean audioInStatus, boolean videoStatus) {
        super.onInvite(roomId, subject, accountFrom, usernameFrom, expireTime, password, userIcon, audioInStatus, videoStatus);
        Log.e(tag, "roomId: " + roomId +
                " subject: " + subject +
                " accountFrom: " + accountFrom +
                " expireTime: " + expireTime +
                " audioInStatus: " + audioInStatus +
                " videoStatus: " + videoStatus);
    }

    //jwj add
    public void onScrollBarrage(String roomId, boolean status, JNIBarrage barrage){
        super.onScrollBarrage(roomId, status, barrage);
        Log.d(tag, "JAVA onScrollBarrage position:" + barrage.position+ "size:" +barrage.fontSize+"opacity:"+barrage.opacity+"content:"+barrage.content);
    }

    @Override
    public void onIMMessage(String roomId, JNIIMMessage message) {
        super.onIMMessage(roomId, message);
    }

    @Override
    public void onMeetingLayoutChanged(JNIView[] layouts, int size) {
        super.onMeetingLayoutChanged(layouts, size);
    }

    @Override
    public void onStartConferenceRecord(long startRecordingTime) {
        super.onStartConferenceRecord(startRecordingTime);
    }
}
