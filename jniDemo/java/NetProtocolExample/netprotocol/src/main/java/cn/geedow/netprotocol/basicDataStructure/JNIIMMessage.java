package cn.geedow.netprotocol.basicDataStructure;

import java.io.Serializable;
import java.util.ArrayList;

import cn.geedow.netprotocol.JNIStParticipantInfo;

public class JNIIMMessage implements Serializable {
    public boolean isResend;
    public int target;

    public long id;
    public long timestamp;
    public int msgType;
    public String content;

    public ArrayList<JNIStParticipantInfo> receivers;
    public ArrayList<JNIStParticipantInfo> atUsers;
    public JNIStParticipantInfo sender;

    public int sendStatus;

    public String extraData;


    public JNIIMMessage() {
        isResend = false;
        target = 0;
        id = 0l;
        timestamp = 0l;
        msgType = 0;
        content = "";
        receivers = new ArrayList<>();
        atUsers = new ArrayList<>();
        sender = new JNIStParticipantInfo();
        sendStatus = 0;
        extraData = "";
    }
}
