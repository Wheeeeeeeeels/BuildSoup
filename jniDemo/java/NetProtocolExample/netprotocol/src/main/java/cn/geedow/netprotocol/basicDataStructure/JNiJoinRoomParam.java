package cn.geedow.netprotocol.basicDataStructure;

public class JNiJoinRoomParam {
    public String roomId;					    // 会议ID
    public String password;				        // 入会密码
    public int mediaMode;				        // 架构类型
    public int duration;						// 会议持续时长(单位为分钟)
    public String useIdInRoom;			        // 仅主持人可通过RoomID入会：onlyModerator,  全体参会人员可通过RoomID入会：allParticipants
    public int streamType;			            // 码流类型
    public boolean videoStatus;					// 入会时视频状态
    public boolean audioStatus;					// 入会时麦克风状态
    public boolean jointype;				    // true表示主动入会，false表示被邀请入会
    public boolean isReconnected;		        // true表示断线重连入会，false表示正常入会
    public String ruid;					        // 会议记录ID，发起会议时缺省，从预约会议详情入会时必须赋值
    public int role;					        // 入会时角色
    public String nickname;                     // 与会者昵称

    public JNiJoinRoomParam()
    {
        roomId = "";
        password = "";
        mediaMode = 0;
        duration = 120;
        useIdInRoom = "";
        streamType = 0;
        videoStatus = true;
        audioStatus = true;
        jointype = true;
        isReconnected = false;
        ruid = "";
        role = 1;
        nickname = "";
    }
}
