package cn.geedow.netprotocol;

import java.io.Serializable;
import java.util.ArrayList;

import cn.geedow.netprotocol.basicDataStructure.JNIUserInfo;
import cn.geedow.netprotocol.basicDataStructure.JNIMeetingRoom;
import cn.geedow.netprotocol.basicDataStructure.JNIView;


public class JNIStMeeting implements Serializable {
		
	public JNIMeetingRoom room;								// 会议室信息

	public String ruid;										// 会议ID
	public String password;									// 入会密码
	public String subject;									// 会议主题
	public String detail;									// 会议详情

	public int numberOfParticipant;							// 已入会人数

	public int subscribeMediaMode;							// 订阅媒体模式，根据该字段确认拉SFU/MCU流
	public int currentMediaMode;							// 会议中当前媒体模式

	public ArrayList<JNIView> layout;						// 会议布局信息

	public int duration;									// 会议持续时长(单位为分钟)
	public long startTimeMs;								// 会议开始时间
	public long endTimeMs;									// 会议结束时间
	public long startRecordTimeMs;							// 开始录制时间

	public int joinRoomMuteMode;							// 入会静音模式

	public boolean allowRecordMeeting;						// 是否允许录制会议

	public boolean isRecording;								// 是否正在录制会议

	public boolean permissionJoinRoomById;					// 是否任何人都有通过ID入会的权限(主持人始终允许)

	public boolean allowPartOpenSpeaker;					// 是否允许与会者自主开启收听
	public boolean allowPartOpenMic;						// 是否允许与会者自主开启麦克风

	public int imPermission;								// IM权限设置

	public JNIUserInfo hostInfo;							// 主持人信息

	public String inviteUrl;								// 邀请链接

	public int roleThreshold;								// 角色阈值，order > 该值默认为 subscribe 角色

	public int mediaModeThreshold;							// 媒体模式阈值，order > 该值默认为MCU模式

	/// 锁定状态，true为锁定, false为关闭锁定
    public boolean meetingLock;
				
    public JNIStMeeting() {
    	room = new JNIMeetingRoom();
       	ruid = "";
       	password = "";
		subject = "";
		detail = "";
		numberOfParticipant = 0;
		subscribeMediaMode = 0;
		currentMediaMode = 0;
		layout = new ArrayList<>();
		duration = 0;
		startTimeMs = 0;
		endTimeMs = 0;
		startRecordTimeMs = 0;
		joinRoomMuteMode = 2;
		allowRecordMeeting = true;
		isRecording = false;
		permissionJoinRoomById = true;		
		allowPartOpenSpeaker = true;
		allowPartOpenMic = true;
		imPermission = 0;
		hostInfo = new JNIUserInfo();			
		inviteUrl = "";		
		roleThreshold = 0;
		mediaModeThreshold = 0;
		meetingLock = false;
    }

}
