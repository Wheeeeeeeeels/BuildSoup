package cn.geedow.netprotocol;

import java.io.Serializable;
import java.util.ArrayList;

import cn.geedow.netprotocol.basicDataStructure.JNIUserInfo;

public class JNIStParticipantInfo implements Serializable {

	public JNIUserInfo userInfo;					// 用户信息
	public int role;								// 与会者角色
	public int order;								// 与会者顺序，主持人为0
	public long createTimeMs;						// 入会时间
	public boolean onlineStatus;					// 是否在线
	public boolean cameraStatus;					// 视频是否打开状态
	public boolean micStatus;						// 麦克风是否打开状态
	public boolean speakerStatus;					// 扬声器是否打开状态
	public boolean handStatus;						// 举手状态
	public boolean lectureStatus;					// 发言状态
	public boolean shareStatus;						// 共享状态
	public boolean isVoiceMode;						// 是否为语音模式
	public ArrayList<JNIStStreamInfo> streams;		                // 流列表
	public String appVersion;						// 与会者使用app版本号，游客入会使用
	public String functionality;					// 设备能力属性集

    public JNIStParticipantInfo() {
    	userInfo = new JNIUserInfo();
        role = 1;
        order = -1;
        createTimeMs = 0;
        onlineStatus = true;
        cameraStatus = false;
        micStatus = false;
        speakerStatus = false;
        handStatus = false;
        lectureStatus = false;
        shareStatus = false;
        isVoiceMode = false;
        streams = new ArrayList<JNIStStreamInfo>();
        appVersion = "";
        functionality = "";
    }






}
