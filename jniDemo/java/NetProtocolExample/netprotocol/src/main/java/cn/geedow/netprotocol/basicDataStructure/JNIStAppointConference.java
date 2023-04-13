package cn.geedow.netprotocol.basicDataStructure;

import java.io.Serializable;
import java.util.ArrayList;

import cn.geedow.netprotocol.JNIStMeeting;
import cn.geedow.netprotocol.JNIStStreamInfo;

public class JNIStAppointConference implements Serializable {

    public JNIStMeeting meetingInfo;		        // 会议信息

    public int meetingStatus;				        // 会议状态

    public boolean autoCall;						// 是否自动呼叫
    public boolean allowParticipantJoinInAdvance;						// 是否自动呼叫

    public ArrayList<JNIUserInfo> participantList;  // 与会者列表

    public boolean moderatorVideoStatus;			// 主持人入会视频状态
    public boolean moderatorMicStatus;			    // 主持人入会麦克风状态
    public boolean participantVideoStatus;		    // 与会者入会视频状态
    public boolean participantMicStatus;			// 与会者入会麦克风状态

    public JNIStAppointConference() {
        meetingInfo = new JNIStMeeting();
        meetingStatus = 0;

        autoCall = true;
        allowParticipantJoinInAdvance = true;
        participantList = new ArrayList<JNIUserInfo>();

        moderatorVideoStatus = true;
        moderatorMicStatus = true;
        participantVideoStatus = true;
        participantMicStatus = true;
    }

}
