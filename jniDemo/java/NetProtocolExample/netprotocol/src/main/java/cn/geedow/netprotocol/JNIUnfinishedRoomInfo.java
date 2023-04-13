package cn.geedow.netprotocol;

public class JNIUnfinishedRoomInfo {
    public String roomId;               // 会议ID
    public String hostAccount;          // 主持人账号
    public String password;             // 入会密码
    public String subject;              // 会议主题
    public int remainTime;                     // 剩余时间
    public int role;					        // 会议中角色
    public boolean audioOutStatus;				// 扬声器状态
    public boolean audioInStatus;				// 麦克风状态
    public boolean videoStatus;				// 视频状态
    public boolean shareStatus;				// 共享状态
    public boolean handStatus;                 // 是否在举手
    public boolean speakStatus;                // 是否在发言
    public int order;							// 与会者顺序

    public JNIUnfinishedRoomInfo() {
        roomId = "";
        hostAccount = "";
        password = "";
        subject = "";
        remainTime = 0;
        role = 1;
        audioOutStatus = true;
        audioInStatus = true;
        videoStatus = true;
        shareStatus = false;
        handStatus = false;
        speakStatus = false;
        order = 0;
    }
}
