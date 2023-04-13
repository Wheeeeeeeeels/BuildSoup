package cn.geedow.netprotocol.basicDataStructure;

import java.io.Serializable;

public class JNIStMeetingAttribute implements Serializable {
    public boolean micStatus;           //入会是否打开麦克风
    public boolean cameraStatus;        //入会是否打开摄像头
    public boolean speakerStatus;       //入会是否打开扬声器
    public boolean isReconnected;       //true表示断线重连入会，false表示正常入会
    public boolean joinType;            //true表示主动入会，false表示被动入会
    public boolean inAdvanceToJoin;     //true表示提前入会，false表示正常入会

    public String touristNickname;      // 游客入会昵称

    public JNIStMeetingAttribute() {
        micStatus = true;
        cameraStatus = true;
        speakerStatus = true;
        isReconnected = false;
        joinType = true;

        touristNickname = "";
        inAdvanceToJoin = true;
    }
}
