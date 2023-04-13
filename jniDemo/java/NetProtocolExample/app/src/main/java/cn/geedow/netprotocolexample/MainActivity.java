package cn.geedow.netprotocolexample;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.squareup.leakcanary.LeakCanary;

import java.util.ArrayList;

import cn.geedow.netprotocol.JNIBasicInfo;
import cn.geedow.netprotocol.JNICommType;
import cn.geedow.netprotocol.JNIH5PageInfo;
import cn.geedow.netprotocol.JNILogObserver;
import cn.geedow.netprotocol.JNILoginInfo;
import cn.geedow.netprotocol.JNINetProtocol;
import cn.geedow.netprotocol.JNIOrgInfo;
import cn.geedow.netprotocol.JNIOrgMemberInfo;
import cn.geedow.netprotocol.JNIPushLogParams;
import cn.geedow.netprotocol.JNIServerInfo;
import cn.geedow.netprotocol.JNIStMeeting;
import cn.geedow.netprotocol.JNIStParticipantInfo;
import cn.geedow.netprotocol.JNIUnfinishedRoomInfo;
import cn.geedow.netprotocol.basicDataStructure.JNIAllMeetingRooms;
import cn.geedow.netprotocol.basicDataStructure.JNICalleeInfo;
import cn.geedow.netprotocol.basicDataStructure.JNICompanyInfo;
import cn.geedow.netprotocol.basicDataStructure.JNIDataPageInfo;
import cn.geedow.netprotocol.basicDataStructure.JNIGroupInfo;
import cn.geedow.netprotocol.basicDataStructure.JNIMediaControlParam;
import cn.geedow.netprotocol.basicDataStructure.JNIMeetingRoom;
import cn.geedow.netprotocol.basicDataStructure.JNINetworkQuality;
import cn.geedow.netprotocol.basicDataStructure.JNIPresetPositionConfigInfo;
import cn.geedow.netprotocol.basicDataStructure.JNIPtzControlParam;
import cn.geedow.netprotocol.basicDataStructure.JNIStAppointConference;
import cn.geedow.netprotocol.basicDataStructure.JNIStMeetingAttribute;
import cn.geedow.netprotocol.basicDataStructure.JNIStreamQuality;
import cn.geedow.netprotocol.basicDataStructure.JNITerminalLocalInfo;
import cn.geedow.netprotocol.basicDataStructure.JNIUserInfo;
import cn.geedow.netprotocol.basicDataStructure.JNIView;
import cn.geedow.netprotocol.projection.JNIProjectionClient;
import cn.geedow.netprotocol.projection.JNIProjectionServer;
import cn.geedow.netprotocol.projection.JNIProjectionServerObserver;
import cn.geedow.netprotocolexample.projection.ProjectionServerObserver;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "NetProtocolExample";
    private Button buttonLogin;
    private TextView textInformation;

    int nRet = 0;

    //    String m_account = "80100201128";
    String m_account = "80100201091";
    String m_passwd = "123456";
    //    String m_account = "17682319269";
    String m_host = "172.25.11.200";
    //    String m_roomId = "80100201150";
    String m_roomId = "80100201091";
    String m_roomPasswd = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        LeakCanary.install(getApplication());

        this.textInformation = findViewById(R.id.textInformation);

        this.buttonLogin = findViewById(R.id.buttonLogin);

        this.buttonLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                final JNINetProtocol sdNProtocol = new JNINetProtocol();

                String versionInfo = sdNProtocol.version();
                Log.e(TAG, "SudiNetProtocol SDK Version: " + sdNProtocol.version());
                Log.e(TAG, "SudiNetProtocol codeToMsg: " + sdNProtocol.codeToMsg(0));

                init();
                TEST_setParams();
                TEST_getParams();

                TEST_arrayListInTest();

                if (true) {
                    /**
                     * 投屏业务测试
                     */
                    if (true) {
                        /**
                         * 服务端测试用例
                         */
                        final JNIProjectionServerObserver observer = new ProjectionServerObserver();
                        JNIProjectionServer.init();
                        JNIProjectionServer.registerObserver(observer);
                        JNIProjectionServer.setIpv4Address("172.25.30.2");

                        JNIProjectionServer.test();
                        JNICommType projectionCode = new JNICommType();
                        JNIProjectionServer.applyForProjectionCode("1", "2", "3", projectionCode);

                        JNIProjectionServer.startProjectionService();
                        JNIProjectionServer.stopProjectionService();
                        JNIProjectionServer.startProjectionService();

                        sleep(5 * 1000);
                    }
                    else {
                        /**
                         * 客户端测试用例
                         */
                        final JNIProjectionClient projectionClient = new JNIProjectionClient();
                        projectionClient.init();
//                        projectionClient.setIpv4Address("172.25.25.19");

                        projectionClient.startProject("719471", "guol");

                        sleep(5 * 1000);
                    }
                } else {
//                TEST_getAccount();

//                    JNICalleeInfo calleeInfo = new JNICalleeInfo();
//                    sdNProtocol.jniTest(calleeInfo);

                    JNILoginInfo loginInfo = new JNILoginInfo();
                    Log.d(TAG, "loginByPwd begin");
                    nRet = sdNProtocol.loginByPwd(m_account, m_passwd, loginInfo);
                    if (nRet != 0) {
                        String msg = sdNProtocol.codeToMsg(nRet);
                        Log.e(TAG, "loginByPwd failed! ret:" + nRet + ", msg:" + sdNProtocol.codeToMsg(nRet));
                        return;
                    } else {
                        textInformation.append("\nlogin success, account: " + m_account);
                    }
                    Log.d(TAG, "loginByPwd done");
                    Log.d(TAG, "loginByPwd done account :" + loginInfo.userInfo.account);

                    TEST_getLoginInfo();

//                    TEST_pushLog();
//                    nRet = TEST_uploadTerminalInfo();
//
//                    TEST_setPresetPosition();
////jwj
//                    TEST_needVersionUpgrade();
//                    TEST_getH5Pages();

                    // 账号信息相关
                    if (false) {
                        TEST_queryOperationPermission();
//                        TEST_getCompanyResourceInfo();
                    }

                    // 预约会议相关
                    if (true) {
//                        TEST_getAllMeetingRooms();
                        StringBuilder ruid = new StringBuilder();
//                        TEST_valueString(ruid);
                        TEST_createAppointRoom(loginInfo, ruid);
                        TEST_updateAppointmentRoom(loginInfo, ruid);
                        TEST_getAllConferenceSummary();
                        getAllConferenceSummaryOfPeriodOfTime();
                        TEST_getAppointmentRoomDetails("appt-08f9e01f608546169bf34228c7894ad5");
                    }

                    // 会控相关
                    if (true) {
//                        TEST_getUnfinishedRoom();
//                        TEST_countParticipatedDuration();
                        TEST_createMeeting();
                        TEST_joinMeeting();
//                        TEST_publishVideo();
//                        TEST_stopPublishVideo();
                        TEST_inviteParticipant();
                        TEST_getCalleeList();

//                        TEST_getSubscriber();
//                        TEST_getMeetingInfo();
//                        TEST_setMeetingInfo();
//                        TEST_applyOpenMic();
//                        TEST_changeMeetingLayout();

                        TEST_leaveMeeting();

//                        TEST_getAllPublishers();
//                        TEST_getPagesOfParticipants();
//                        TEST_getParticipant();
//                        TEST_receiveVideo();
//                        TEST_stopReceiveVideo();

//                        TEST_leaveMeeting();
//                        TEST_closeMeeting();
                        // TEST_setHandStatus();
                        //TEST_setRollCallStatus();
//                        TEST_setShareStatus();
                        //TEST_getMeetingInfo();
                        //TEST_joinRoomEx();
//
                        //JNIRoomInfo roomInfo = new JNIRoomInfo();
                        //TEST_getRoomInfo(roomInfo);
//
//                        TEST_setPushStreamStatus();
//                        TEST_setConferenceLayout();
//                        TEST_uploadMeetingQuality();
//                        TEST_switchVoiceMode();
//                        TEST_setPtzControlStatus();
//                        TEST_adjustResolution();
//                        JNIRoomInfo roomInfo = new JNIRoomInfo();
//                        TEST_getRoomInfo(roomInfo);
//                        // jwj
//                        TEST_getAllParticipants();
//                        TEST_setPushStreamStatus();
//                        TEST_setPullStreamStatus();
//                        TEST_meetingControl();
//                        TEST_setRollCall();
//                        JNIRoomInfo roomInfoGet = new JNIRoomInfo();
//                        TEST_getRoomInfo(roomInfoGet);
                    }

                    // 通讯录相关
                    if (true) {
//                        TEST_getPagesOfOrgDepart();
//                        TEST_groupRelated();
//
//                        TEST_getPagesOfOrgDepart();
//                        TEST_getPagesOfOrgMemebers();
//                        TEST_getOrgMemberRecursively();

//                        JNIOrgMemberInfo memberInfo = new JNIOrgMemberInfo();
//                        TEST_getFrequentContacts(memberInfo);
//                        memberInfo.account = memberInfo.account.isEmpty() ? "80100201090" : memberInfo.account;
//                        TEST_getMemberDetails(memberInfo);
//                        TEST_updateContact(memberInfo);
                    }
//                TEST_closeRoom();
                    TEST_logout();

                    if (false) {
                        while (true) {
                            try {
                                Thread.sleep(5);
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                        }
                    }
                }
            }
        });
    }

    public void init() {
        final String cacheDir = this.getCacheDir().getPath() + "android_writeFileTest.txt";
        RoomObserver roomObserver = new RoomObserver();
        Observer observer = new Observer();
        JNINetProtocol.init(observer, roomObserver);

        JNINetProtocol.setLogObserver(new JNILogObserver() {
            @Override
            public void onPrintLog(int level, String log) {
//                        super.onPrintLog(level, log);
                Log.e(TAG, log);
            }
        });
    }

    public void TEST_setParams() {
        JNIBasicInfo param = new JNIBasicInfo();
        JNIServerInfo serverInfo1 = new JNIServerInfo();
        serverInfo1.isProxy = false;
        serverInfo1.host = m_host;
        serverInfo1.httpPort = 5000;
        serverInfo1.httpsPort = 443;
        param.serverInfos.add(serverInfo1);
        param.terminalType = 0;
        param.deviceModel = "deviceModel";
        param.localInfo.ability = "MultiCastPlay";
        param.macAddr = "00:11:22:33:44:55";
//jwj        param.appVersion = "1.0.7";  //"1.0.8.111";
        param.appVersion = "107";  //"1.0.8.111";
        param.serialNumber = "SDNP000001";
        param.udid = "";
        JNINetProtocol.setParams(param);
    }

    public void TEST_getParams() {
        JNIBasicInfo basicInfo = new JNIBasicInfo();
        nRet = JNINetProtocol.getParams(basicInfo);
        Log.e(TAG, "getParams: " + basicInfo.toString());
    }

    public int TEST_login(JNILoginInfo loginInfo) {
        nRet = JNINetProtocol.loginByPwd(m_account, "123456", loginInfo);
        if (nRet != 0) {
            Log.e(TAG, "loginByPwd failed! ret:" + nRet + ", msg:" + JNINetProtocol.codeToMsg(nRet));
        }
        textInformation.append("\nlogin success, account: " + m_account);
        return nRet;
    }

    public int TEST_logout() {
        nRet = JNINetProtocol.logout();
        if (nRet != 0) {
            Log.e(TAG, "logout failed! ret:" + nRet + ", msg:" + JNINetProtocol.codeToMsg(nRet));
        }
        return nRet;
    }

    public int TEST_createMeeting() {
        JNIStMeeting stMeeting = new JNIStMeeting();
        //JNIMeetingRoom meetingRoom = new JNIMeetingRoom();
        stMeeting.room.type = 1;
        stMeeting.room.id = m_roomId;
        stMeeting.room.name = "";
        stMeeting.room.status = 0;
        stMeeting.room.capacity = 0;
        stMeeting.room.shortNum = "";
        stMeeting.room.expiredDate = "";
        stMeeting.room.roomIcon = "";

        stMeeting.ruid = "";
        stMeeting.password = "";
        stMeeting.subject = "";
        stMeeting.detail = "";
        stMeeting.numberOfParticipant = 0;
        stMeeting.currentMediaMode = 0;
        stMeeting.duration = 0;
        stMeeting.startTimeMs = 0;
        stMeeting.endTimeMs = 0;


        nRet = JNINetProtocol.createMeeting(stMeeting);
        if (nRet != 0) {
            Log.e(TAG, "createRoom failed! ret:" + nRet + ", msg:" + JNINetProtocol.codeToMsg(nRet));
        }
        else {
            m_roomId = stMeeting.room.id;
        }

        if (stMeeting.ruid == null) {
            Log.e(TAG, "create meetingid is null or empty");
        }

        textInformation.append("\ncreate room  success, roomId: ");
        return nRet;
    }

    public int TEST_joinMeeting() {
        JNIStMeeting stMeeting = new JNIStMeeting();
        JNIStMeetingAttribute stMeetingAttribute = new JNIStMeetingAttribute();
        //JNIMeetingRoom meetingRoom = new JNIMeetingRoom();
        stMeeting.room.type = -1;
        stMeeting.room.id = m_roomId;
        stMeeting.room.name = "";
        stMeeting.room.status = 0;
        stMeeting.room.capacity = 0;
        stMeeting.room.shortNum = "";
        stMeeting.room.expiredDate = "";
        stMeeting.room.roomIcon = "";

        stMeeting.ruid = "";
        stMeeting.password = m_roomPasswd;
        stMeeting.subject = "";
        stMeeting.detail = "";
        stMeeting.numberOfParticipant = 0;
        stMeeting.currentMediaMode = 0;
        stMeeting.duration = 0;
        stMeeting.startTimeMs = 0;
        stMeeting.endTimeMs = 0;


        nRet = JNINetProtocol.joinMeeting(stMeeting, stMeetingAttribute);
        if (nRet != 0) {
            Log.e(TAG, "join meetin failed! ret:" + nRet + ", msg:" + JNINetProtocol.codeToMsg(nRet));
        }

        if (stMeeting.ruid == null) {
            Log.e(TAG, "join meeting id is null or empty");
        }

        textInformation.append("\njoin meeting  success, roomId: ");
        return nRet;
    }

    public int TEST_leaveMeeting() {
        JNIStMeeting stMeeting = new JNIStMeeting();
        //JNIMeetingRoom meetingRoom = new JNIMeetingRoom();
        stMeeting.room.type = -1;
        stMeeting.room.id = "80100201091";
        stMeeting.room.name = "";
        stMeeting.room.status = 0;
        stMeeting.room.capacity = 0;
        stMeeting.room.shortNum = "";
        stMeeting.room.expiredDate = "";
        stMeeting.room.roomIcon = "";

        stMeeting.ruid = "";
        stMeeting.password = "";
        stMeeting.subject = "";
        stMeeting.detail = "";
        stMeeting.numberOfParticipant = 0;
        stMeeting.currentMediaMode = 0;
        stMeeting.duration = 0;
        stMeeting.startTimeMs = 0;
        stMeeting.endTimeMs = 0;


        nRet = JNINetProtocol.leaveMeeting(stMeeting);
        if (nRet != 0) {
            Log.e(TAG, "leave meeting failed! ret:" + nRet + ", msg:" + JNINetProtocol.codeToMsg(nRet));
        }

        if (stMeeting.ruid == null) {
            Log.e(TAG, "leave meeting id is null or empty");
        }

        textInformation.append("\nleave meeting  success, roomId: ");
        return nRet;
    }

    public int TEST_closeMeeting() {
        JNIStMeeting stMeeting = new JNIStMeeting();
        //JNIMeetingRoom meetingRoom = new JNIMeetingRoom();
        stMeeting.room.type = -1;
        stMeeting.room.id = "80100201091";
        stMeeting.room.name = "";
        stMeeting.room.status = 0;
        stMeeting.room.capacity = 0;
        stMeeting.room.shortNum = "";
        stMeeting.room.expiredDate = "";
        stMeeting.room.roomIcon = "";

        stMeeting.ruid = "";
        stMeeting.password = "";
        stMeeting.subject = "";
        stMeeting.detail = "";
        stMeeting.numberOfParticipant = 0;
        stMeeting.currentMediaMode = 0;
        stMeeting.duration = 0;
        stMeeting.startTimeMs = 0;
        stMeeting.endTimeMs = 0;


        nRet = JNINetProtocol.closeMeeting(stMeeting);
        if (nRet != 0) {
            Log.e(TAG, " close meeting failed! ret:" + nRet + ", msg:" + JNINetProtocol.codeToMsg(nRet));
        }

        if (stMeeting.ruid == null) {
            Log.e(TAG, "close meeting id is null or empty");
        }

        textInformation.append("\n close meeting  success, roomId: ");
        return nRet;
    }

    public int TEST_publishVideo() {
        int StreamType = 0;
        String sdpOffer = "v=0\\r\\no=- 2840664192477222864 2 IN IP4 127.0.0.1\\r\\ns=-\\r\\nt=0 0\\r\\na=group:BUNDLE audio video\\r\\na=msid-semantic: WMS 102\\r\\nm=audio 9 UDP/TLS/RTP/SAVPF 111 103 104 9 102 0 8 106 105 13 110 112 113 126\\r\\nc=IN IP4 0.0.0.0\\r\\na=rtcp:9 IN IP4 0.0.0.0\\r\\na=ice-ufrag:qhTS\\r\\na=ice-pwd:e/Hlnt4p+eMZaVkJs/1R8ilD\\r\\na=ice-options:trickle renomination\\r\\na=fingerprint:sha-256 8A:95:4B:28:BF:4C:EB:C3:BE:F9:63:1A:98:43:C2:C9:D7:51:B3:4B:D1:94:85:87:05:D4:5C:8A:C6:54:29:4F\\r\\na=setup:actpass\\r\\na=mid:audio\\r\\na=extmap:1 urn:ietf:params:rtp-hdrext:ssrc-audio-level\\r\\na=extmap:2 http://www.ietf.org/id/draft-holmer-rmcat-transport-wide-cc-extensions-01\\r\\na=sendrecv\\r\\na=rtcp-mux\\r\\na=rtpmap:111 opus/48000/2\\r\\na=rtcp-fb:111 transport-cc\\r\\na=fmtp:111 minptime=10;useinbandfec=1\\r\\na=rtpmap:103 ISAC/16000\\r\\na=rtpmap:104 ISAC/32000\\r\\na=rtpmap:9 G722/8000\\r\\na=rtpmap:102 ILBC/8000\\r\\na=rtpmap:0 PCMU/8000\\r\\na=rtpmap:8 PCMA/8000\\r\\na=rtpmap:106 CN/32000\\r\\na=rtpmap:105 CN/16000\\r\\na=rtpmap:13 CN/8000\\r\\na=rtpmap:110 telephone-event/48000\\r\\na=rtpmap:112 telephone-event/32000\\r\\na=rtpmap:113 telephone-event/16000\\r\\na=rtpmap:126 telephone-event/8000\\r\\na=ssrc:729307836 cname:1DUhCbcb2vBW9MsN\\r\\na=ssrc:729307836 msid:102 101\\r\\na=ssrc:729307836 mslabel:102\\r\\na=ssrc:729307836 label:101\\r\\nm=video 9 UDP/TLS/RTP/SAVPF 96 97 98 99 100 101 127 123 125 122 124\\r\\nc=IN IP4 0.0.0.0\\r\\na=rtcp:9 IN IP4 0.0.0.0\\r\\na=ice-ufrag:qhTS\\r\\na=ice-pwd:e/Hlnt4p+eMZaVkJs/1R8ilD\\r\\na=ice-options:trickle renomination\\r\\na=fingerprint:sha-256 8A:95:4B:28:BF:4C:EB:C3:BE:F9:63:1A:98:43:C2:C9:D7:51:B3:4B:D1:94:85:87:05:D4:5C:8A:C6:54:29:4F\\r\\na=setup:actpass\\r\\na=mid:video\\r\\na=extmap:14 urn:ietf:params:rtp-hdrext:toffset\\r\\na=extmap:13 http://www.webrtc.org/experiments/rtp-hdrext/abs-send-time\\r\\na=extmap:3 urn:3gpp:video-orientation\\r\\na=extmap:2 http://www.ietf.org/id/draft-holmer-rmcat-transport-wide-cc-extensions-01\\r\\na=extmap:5 http://www.webrtc.org/experiments/rtp-hdrext/playout-delay\\r\\na=extmap:6 http://www.webrtc.org/experiments/rtp-hdrext/video-content-type\\r\\na=extmap:7 http://www.webrtc.org/experiments/rtp-hdrext/video-timing\\r\\na=extmap:8 http://tools.ietf.org/html/draft-ietf-avtext-framemarking-07\\r\\na=extmap:9 http://www.webrtc.org/experiments/rtp-hdrext/color-space\\r\\na=sendrecv\\r\\na=rtcp-mux\\r\\na=rtcp-rsize\\r\\na=rtpmap:96 H264/90000\\r\\na=rtcp-fb:96 goog-remb\\r\\na=rtcp-fb:96 transport-cc\\r\\na=rtcp-fb:96 ccm fir\\r\\na=rtcp-fb:96 nack\\r\\na=rtcp-fb:96 nack pli\\r\\na=fmtp:96 level-asymmetry-allowed=1;packetization-mode=1;profile-level-id=42e01f\\r\\na=rtpmap:97 rtx/90000\\r\\na=fmtp:97 apt=96\\r\\na=rtpmap:98 VP8/90000\\r\\na=rtcp-fb:98 goog-remb\\r\\na=rtcp-fb:98 transport-cc\\r\\na=rtcp-fb:98 ccm fir\\r\\na=rtcp-fb:98 nack\\r\\na=rtcp-fb:98 nack pli\\r\\na=rtpmap:99 rtx/90000\\r\\na=fmtp:99 apt=98\\r\\na=rtpmap:100 VP9/90000\\r\\na=rtcp-fb:100 goog-remb\\r\\na=rtcp-fb:100 transport-cc\\r\\na=rtcp-fb:100 ccm fir\\r\\na=rtcp-fb:100 nack\\r\\na=rtcp-fb:100 nack pli\\r\\na=rtpmap:101 rtx/90000\\r\\na=fmtp:101 apt=100\\r\\na=rtpmap:127 H265/90000\\r\\na=rtcp-fb:127 goog-remb\\r\\na=rtcp-fb:127 transport-cc\\r\\na=rtcp-fb:127 ccm fir\\r\\na=rtcp-fb:127 nack\\r\\na=rtcp-fb:127 nack pli\\r\\na=rtpmap:123 rtx/90000\\r\\na=fmtp:123 apt=127\\r\\na=rtpmap:125 red/90000\\r\\na=rtpmap:122 rtx/90000\\r\\na=fmtp:122 apt=125\\r\\na=rtpmap:124 ulpfec/90000\\r\\na=ssrc-group:FID 342252422 3252828985\\r\\na=ssrc:342252422 cname:1DUhCbcb2vBW9MsN\\r\\na=ssrc:342252422 msid:102 100\\r\\na=ssrc:342252422 mslabel:102\\r\\na=ssrc:342252422 label:100\\r\\na=ssrc:3252828985 cname:1DUhCbcb2vBW9MsN\\r\\na=ssrc:3252828985 msid:102 100\\r\\na=ssrc:3252828985 mslabel:102\\r\\na=ssrc:3252828985 label:100\\r\\n\n";
        boolean videoStatus = true;
        boolean audioStatus = true;
        JNICommType sdpAnwser = new JNICommType();
        ;
        int nRet = JNINetProtocol.publishVideo(StreamType, sdpOffer, videoStatus, audioStatus, sdpAnwser);
        if (nRet != 0) {
            Log.e(TAG, "publish video failed! ret:" + nRet + ", msg:" + JNINetProtocol.codeToMsg(nRet));
        }
        return nRet;
    }

    public int TEST_stopPublishVideo() {
        int StreamType = 0;
        //String sdpOffer = "v=0\\r\\no=- 2840664192477222864 2 IN IP4 127.0.0.1\\r\\ns=-\\r\\nt=0 0\\r\\na=group:BUNDLE audio video\\r\\na=msid-semantic: WMS 102\\r\\nm=audio 9 UDP/TLS/RTP/SAVPF 111 103 104 9 102 0 8 106 105 13 110 112 113 126\\r\\nc=IN IP4 0.0.0.0\\r\\na=rtcp:9 IN IP4 0.0.0.0\\r\\na=ice-ufrag:qhTS\\r\\na=ice-pwd:e/Hlnt4p+eMZaVkJs/1R8ilD\\r\\na=ice-options:trickle renomination\\r\\na=fingerprint:sha-256 8A:95:4B:28:BF:4C:EB:C3:BE:F9:63:1A:98:43:C2:C9:D7:51:B3:4B:D1:94:85:87:05:D4:5C:8A:C6:54:29:4F\\r\\na=setup:actpass\\r\\na=mid:audio\\r\\na=extmap:1 urn:ietf:params:rtp-hdrext:ssrc-audio-level\\r\\na=extmap:2 http://www.ietf.org/id/draft-holmer-rmcat-transport-wide-cc-extensions-01\\r\\na=sendrecv\\r\\na=rtcp-mux\\r\\na=rtpmap:111 opus/48000/2\\r\\na=rtcp-fb:111 transport-cc\\r\\na=fmtp:111 minptime=10;useinbandfec=1\\r\\na=rtpmap:103 ISAC/16000\\r\\na=rtpmap:104 ISAC/32000\\r\\na=rtpmap:9 G722/8000\\r\\na=rtpmap:102 ILBC/8000\\r\\na=rtpmap:0 PCMU/8000\\r\\na=rtpmap:8 PCMA/8000\\r\\na=rtpmap:106 CN/32000\\r\\na=rtpmap:105 CN/16000\\r\\na=rtpmap:13 CN/8000\\r\\na=rtpmap:110 telephone-event/48000\\r\\na=rtpmap:112 telephone-event/32000\\r\\na=rtpmap:113 telephone-event/16000\\r\\na=rtpmap:126 telephone-event/8000\\r\\na=ssrc:729307836 cname:1DUhCbcb2vBW9MsN\\r\\na=ssrc:729307836 msid:102 101\\r\\na=ssrc:729307836 mslabel:102\\r\\na=ssrc:729307836 label:101\\r\\nm=video 9 UDP/TLS/RTP/SAVPF 96 97 98 99 100 101 127 123 125 122 124\\r\\nc=IN IP4 0.0.0.0\\r\\na=rtcp:9 IN IP4 0.0.0.0\\r\\na=ice-ufrag:qhTS\\r\\na=ice-pwd:e/Hlnt4p+eMZaVkJs/1R8ilD\\r\\na=ice-options:trickle renomination\\r\\na=fingerprint:sha-256 8A:95:4B:28:BF:4C:EB:C3:BE:F9:63:1A:98:43:C2:C9:D7:51:B3:4B:D1:94:85:87:05:D4:5C:8A:C6:54:29:4F\\r\\na=setup:actpass\\r\\na=mid:video\\r\\na=extmap:14 urn:ietf:params:rtp-hdrext:toffset\\r\\na=extmap:13 http://www.webrtc.org/experiments/rtp-hdrext/abs-send-time\\r\\na=extmap:3 urn:3gpp:video-orientation\\r\\na=extmap:2 http://www.ietf.org/id/draft-holmer-rmcat-transport-wide-cc-extensions-01\\r\\na=extmap:5 http://www.webrtc.org/experiments/rtp-hdrext/playout-delay\\r\\na=extmap:6 http://www.webrtc.org/experiments/rtp-hdrext/video-content-type\\r\\na=extmap:7 http://www.webrtc.org/experiments/rtp-hdrext/video-timing\\r\\na=extmap:8 http://tools.ietf.org/html/draft-ietf-avtext-framemarking-07\\r\\na=extmap:9 http://www.webrtc.org/experiments/rtp-hdrext/color-space\\r\\na=sendrecv\\r\\na=rtcp-mux\\r\\na=rtcp-rsize\\r\\na=rtpmap:96 H264/90000\\r\\na=rtcp-fb:96 goog-remb\\r\\na=rtcp-fb:96 transport-cc\\r\\na=rtcp-fb:96 ccm fir\\r\\na=rtcp-fb:96 nack\\r\\na=rtcp-fb:96 nack pli\\r\\na=fmtp:96 level-asymmetry-allowed=1;packetization-mode=1;profile-level-id=42e01f\\r\\na=rtpmap:97 rtx/90000\\r\\na=fmtp:97 apt=96\\r\\na=rtpmap:98 VP8/90000\\r\\na=rtcp-fb:98 goog-remb\\r\\na=rtcp-fb:98 transport-cc\\r\\na=rtcp-fb:98 ccm fir\\r\\na=rtcp-fb:98 nack\\r\\na=rtcp-fb:98 nack pli\\r\\na=rtpmap:99 rtx/90000\\r\\na=fmtp:99 apt=98\\r\\na=rtpmap:100 VP9/90000\\r\\na=rtcp-fb:100 goog-remb\\r\\na=rtcp-fb:100 transport-cc\\r\\na=rtcp-fb:100 ccm fir\\r\\na=rtcp-fb:100 nack\\r\\na=rtcp-fb:100 nack pli\\r\\na=rtpmap:101 rtx/90000\\r\\na=fmtp:101 apt=100\\r\\na=rtpmap:127 H265/90000\\r\\na=rtcp-fb:127 goog-remb\\r\\na=rtcp-fb:127 transport-cc\\r\\na=rtcp-fb:127 ccm fir\\r\\na=rtcp-fb:127 nack\\r\\na=rtcp-fb:127 nack pli\\r\\na=rtpmap:123 rtx/90000\\r\\na=fmtp:123 apt=127\\r\\na=rtpmap:125 red/90000\\r\\na=rtpmap:122 rtx/90000\\r\\na=fmtp:122 apt=125\\r\\na=rtpmap:124 ulpfec/90000\\r\\na=ssrc-group:FID 342252422 3252828985\\r\\na=ssrc:342252422 cname:1DUhCbcb2vBW9MsN\\r\\na=ssrc:342252422 msid:102 100\\r\\na=ssrc:342252422 mslabel:102\\r\\na=ssrc:342252422 label:100\\r\\na=ssrc:3252828985 cname:1DUhCbcb2vBW9MsN\\r\\na=ssrc:3252828985 msid:102 100\\r\\na=ssrc:3252828985 mslabel:102\\r\\na=ssrc:3252828985 label:100\\r\\n\n";
        //boolean videoStatus = true;
        //boolean audioStatus = true;
        //JNICommType sdpAnwser = new JNICommType();;
        int nRet = JNINetProtocol.stopPublishVideo(StreamType);
        if (nRet != 0) {
            Log.e(TAG, "publish video failed! ret:" + nRet + ", msg:" + JNINetProtocol.codeToMsg(nRet));
        }
        return nRet;
    }

    public int TEST_receiveVideo() {
        int StreamType = 0;
        String account = "80100201090";
        String sdpOffer = "v=0\\r\\no=- 2840664192477222864 2 IN IP4 127.0.0.1\\r\\ns=-\\r\\nt=0 0\\r\\na=group:BUNDLE audio video\\r\\na=msid-semantic: WMS 102\\r\\nm=audio 9 UDP/TLS/RTP/SAVPF 111 103 104 9 102 0 8 106 105 13 110 112 113 126\\r\\nc=IN IP4 0.0.0.0\\r\\na=rtcp:9 IN IP4 0.0.0.0\\r\\na=ice-ufrag:qhTS\\r\\na=ice-pwd:e/Hlnt4p+eMZaVkJs/1R8ilD\\r\\na=ice-options:trickle renomination\\r\\na=fingerprint:sha-256 8A:95:4B:28:BF:4C:EB:C3:BE:F9:63:1A:98:43:C2:C9:D7:51:B3:4B:D1:94:85:87:05:D4:5C:8A:C6:54:29:4F\\r\\na=setup:actpass\\r\\na=mid:audio\\r\\na=extmap:1 urn:ietf:params:rtp-hdrext:ssrc-audio-level\\r\\na=extmap:2 http://www.ietf.org/id/draft-holmer-rmcat-transport-wide-cc-extensions-01\\r\\na=sendrecv\\r\\na=rtcp-mux\\r\\na=rtpmap:111 opus/48000/2\\r\\na=rtcp-fb:111 transport-cc\\r\\na=fmtp:111 minptime=10;useinbandfec=1\\r\\na=rtpmap:103 ISAC/16000\\r\\na=rtpmap:104 ISAC/32000\\r\\na=rtpmap:9 G722/8000\\r\\na=rtpmap:102 ILBC/8000\\r\\na=rtpmap:0 PCMU/8000\\r\\na=rtpmap:8 PCMA/8000\\r\\na=rtpmap:106 CN/32000\\r\\na=rtpmap:105 CN/16000\\r\\na=rtpmap:13 CN/8000\\r\\na=rtpmap:110 telephone-event/48000\\r\\na=rtpmap:112 telephone-event/32000\\r\\na=rtpmap:113 telephone-event/16000\\r\\na=rtpmap:126 telephone-event/8000\\r\\na=ssrc:729307836 cname:1DUhCbcb2vBW9MsN\\r\\na=ssrc:729307836 msid:102 101\\r\\na=ssrc:729307836 mslabel:102\\r\\na=ssrc:729307836 label:101\\r\\nm=video 9 UDP/TLS/RTP/SAVPF 96 97 98 99 100 101 127 123 125 122 124\\r\\nc=IN IP4 0.0.0.0\\r\\na=rtcp:9 IN IP4 0.0.0.0\\r\\na=ice-ufrag:qhTS\\r\\na=ice-pwd:e/Hlnt4p+eMZaVkJs/1R8ilD\\r\\na=ice-options:trickle renomination\\r\\na=fingerprint:sha-256 8A:95:4B:28:BF:4C:EB:C3:BE:F9:63:1A:98:43:C2:C9:D7:51:B3:4B:D1:94:85:87:05:D4:5C:8A:C6:54:29:4F\\r\\na=setup:actpass\\r\\na=mid:video\\r\\na=extmap:14 urn:ietf:params:rtp-hdrext:toffset\\r\\na=extmap:13 http://www.webrtc.org/experiments/rtp-hdrext/abs-send-time\\r\\na=extmap:3 urn:3gpp:video-orientation\\r\\na=extmap:2 http://www.ietf.org/id/draft-holmer-rmcat-transport-wide-cc-extensions-01\\r\\na=extmap:5 http://www.webrtc.org/experiments/rtp-hdrext/playout-delay\\r\\na=extmap:6 http://www.webrtc.org/experiments/rtp-hdrext/video-content-type\\r\\na=extmap:7 http://www.webrtc.org/experiments/rtp-hdrext/video-timing\\r\\na=extmap:8 http://tools.ietf.org/html/draft-ietf-avtext-framemarking-07\\r\\na=extmap:9 http://www.webrtc.org/experiments/rtp-hdrext/color-space\\r\\na=sendrecv\\r\\na=rtcp-mux\\r\\na=rtcp-rsize\\r\\na=rtpmap:96 H264/90000\\r\\na=rtcp-fb:96 goog-remb\\r\\na=rtcp-fb:96 transport-cc\\r\\na=rtcp-fb:96 ccm fir\\r\\na=rtcp-fb:96 nack\\r\\na=rtcp-fb:96 nack pli\\r\\na=fmtp:96 level-asymmetry-allowed=1;packetization-mode=1;profile-level-id=42e01f\\r\\na=rtpmap:97 rtx/90000\\r\\na=fmtp:97 apt=96\\r\\na=rtpmap:98 VP8/90000\\r\\na=rtcp-fb:98 goog-remb\\r\\na=rtcp-fb:98 transport-cc\\r\\na=rtcp-fb:98 ccm fir\\r\\na=rtcp-fb:98 nack\\r\\na=rtcp-fb:98 nack pli\\r\\na=rtpmap:99 rtx/90000\\r\\na=fmtp:99 apt=98\\r\\na=rtpmap:100 VP9/90000\\r\\na=rtcp-fb:100 goog-remb\\r\\na=rtcp-fb:100 transport-cc\\r\\na=rtcp-fb:100 ccm fir\\r\\na=rtcp-fb:100 nack\\r\\na=rtcp-fb:100 nack pli\\r\\na=rtpmap:101 rtx/90000\\r\\na=fmtp:101 apt=100\\r\\na=rtpmap:127 H265/90000\\r\\na=rtcp-fb:127 goog-remb\\r\\na=rtcp-fb:127 transport-cc\\r\\na=rtcp-fb:127 ccm fir\\r\\na=rtcp-fb:127 nack\\r\\na=rtcp-fb:127 nack pli\\r\\na=rtpmap:123 rtx/90000\\r\\na=fmtp:123 apt=127\\r\\na=rtpmap:125 red/90000\\r\\na=rtpmap:122 rtx/90000\\r\\na=fmtp:122 apt=125\\r\\na=rtpmap:124 ulpfec/90000\\r\\na=ssrc-group:FID 342252422 3252828985\\r\\na=ssrc:342252422 cname:1DUhCbcb2vBW9MsN\\r\\na=ssrc:342252422 msid:102 100\\r\\na=ssrc:342252422 mslabel:102\\r\\na=ssrc:342252422 label:100\\r\\na=ssrc:3252828985 cname:1DUhCbcb2vBW9MsN\\r\\na=ssrc:3252828985 msid:102 100\\r\\na=ssrc:3252828985 mslabel:102\\r\\na=ssrc:3252828985 label:100\\r\\n\n";
        JNICommType sdpAnwser = new JNICommType();
        ;
        int nRet = JNINetProtocol.receiveVideo(account, StreamType, sdpOffer, sdpAnwser);
        if (nRet != 0) {
            Log.e(TAG, "receive video failed! ret:" + nRet + ", msg:" + JNINetProtocol.codeToMsg(nRet));
        }
        return nRet;
    }

    public int TEST_stopReceiveVideo() {
        int StreamType = 0;
        String account = "80100201090";
        int nRet = JNINetProtocol.stopReceiveVideo(account, StreamType);
        if (nRet != 0) {
            Log.e(TAG, "receive video failed! ret:" + nRet + ", msg:" + JNINetProtocol.codeToMsg(nRet));
        }
        return nRet;
    }

    public int TEST_setHandStatus() {
        String[] account = new String[1];
        account[0] = "80100201091";
        boolean status = true;
        int nRet = JNINetProtocol.setHandStatus(account, status);
        if (nRet != 0) {
            Log.e(TAG, "setHandStatus failed! ret:" + nRet + ", msg:" + JNINetProtocol.codeToMsg(nRet));
        }
        return nRet;
    }

    public int TEST_setRollCallStatus() {
        String oldAccount = "80100201091";
        String newAccount = "";
        boolean status = true;
        int source = 0;
        int nRet = JNINetProtocol.setRollCallStatus(oldAccount, newAccount, status, source);
        if (nRet != 0) {
            Log.e(TAG, "setRollCallStatus failed! ret:" + nRet + ", msg:" + JNINetProtocol.codeToMsg(nRet));
        }
        return nRet;
    }

    public int TEST_setShareStatus() {
        String operatorAccount = "80100201091";
        String shareAccount = "80100201091";
        boolean status = true;
        int nRet = JNINetProtocol.setShareState(operatorAccount, shareAccount, status);
        if (nRet != 0) {
            Log.e(TAG, "setShareState failed! ret:" + nRet + ", msg:" + JNINetProtocol.codeToMsg(nRet));
        }
        return nRet;
    }

    public int TEST_createAppointRoom(JNILoginInfo loginInfo, StringBuilder ruid) {
        JNIStAppointConference appointConference = new JNIStAppointConference();
        appointConference.meetingInfo.room.id = m_roomId;
        appointConference.meetingInfo.ruid = "";
        appointConference.meetingInfo.password = "111111";
        appointConference.meetingInfo.subject = "TEST_createAppointmentRoom";
        appointConference.meetingInfo.currentMediaMode = 0;
        appointConference.autoCall = true;
        appointConference.meetingInfo.room.capacity = 4;
        appointConference.meetingInfo.startTimeMs = 1622393931;    // 2023-01-01 00:00:00
        appointConference.meetingInfo.duration = 120;
        appointConference.meetingInfo.detail = "Android JNI test.";
        //appointConference.moderatorRoomId = loginInfo.account;
        appointConference.meetingInfo.hostInfo.name = "WinExample";
        //appointConference.createorAccount = loginInfo.account;

        JNIUserInfo userInfo = new JNIUserInfo();
        userInfo.account = m_account;
        userInfo.name = loginInfo.userInfo.name;
        appointConference.participantList.add(userInfo);

        JNIUserInfo userInfo1 = new JNIUserInfo();
        userInfo1.account = "80100101061";
        userInfo1.name = "Centos2";
        appointConference.participantList.add(userInfo1);

        JNIUserInfo userInfo2 = new JNIUserInfo();
        userInfo2.account = "80100101059";
        userInfo2.name = "GUOL-WinExample";
        appointConference.participantList.add(userInfo2);

        JNICommType appointRuid = new JNICommType();
        nRet = JNINetProtocol.createAppointConference(appointConference);
        if (nRet != 0) {
            Log.e(TAG, "createAppointConference failed. ret: " + String.valueOf(nRet) + " msg: " + JNINetProtocol.codeToMsg(nRet));
        } else {
            ruid.append(appointRuid.str);
        }
        return nRet;
    }

    public int TEST_updateAppointmentRoom(JNILoginInfo loginInfo, StringBuilder ruid) {
        JNIStAppointConference appointConference = new JNIStAppointConference();
        appointConference.meetingInfo.room.id = m_roomId;
        appointConference.meetingInfo.ruid = "";
        appointConference.meetingInfo.password = "111111";
        appointConference.meetingInfo.subject = "TEST_updateAppointmentRoom";
        appointConference.meetingInfo.currentMediaMode = 0;
        appointConference.autoCall = true;
        appointConference.meetingInfo.room.capacity = 4;
        appointConference.meetingInfo.startTimeMs = 1609430400000L;    // 2021-01-01 00:00:00
        appointConference.meetingInfo.duration = 120;
        appointConference.meetingInfo.detail = "Android JNI test.";
        //appointConference.moderatorRoomId = loginInfo.account;
        appointConference.meetingInfo.hostInfo.name = "WinExample";
        //appointConference.createorAccount = loginInfo.account;

        JNIUserInfo userInfo = new JNIUserInfo();
        userInfo.account = m_account;
        userInfo.name = loginInfo.userInfo.name;
        appointConference.participantList.add(userInfo);

        JNIUserInfo userInfo1 = new JNIUserInfo();
        userInfo1.account = "80100101061";
        userInfo1.name = "Centos2";
        appointConference.participantList.add(userInfo1);

        JNICommType appointRuid = new JNICommType();
        nRet = JNINetProtocol.updateAppointConference(appointConference);
        if (nRet != 0) {
            Log.e(TAG, "updateAppointConference failed. ret: " + String.valueOf(nRet) + " msg: " + JNINetProtocol.codeToMsg(nRet));
        }
        return nRet;
    }

    public int TEST_getAppointmentRoomDetails(String ruid) {
        JNIStAppointConference appointConference = new JNIStAppointConference();
        JNICommType isStart = new JNICommType();
//        nRet = JNINetProtocol.getAppointmentRoomDetails(ruid, appointConference, isStart);
        if (nRet != 0) {
            Log.e(TAG, "TEST_getAppointmentRoom failed! ret:" + nRet + ", msg:" + JNINetProtocol.codeToMsg(nRet));
        } else {
            Log.d(TAG, "status[" + ruid + "]");
        }
        String msg =
                "{\n" +
                    "\troomId: " + appointConference.meetingInfo.room.id + ",\n" +
                    "\truid: " + appointConference.meetingInfo.ruid + ",\n" +
                    "\tpassword: " + appointConference.meetingInfo.password + ",\n" +
                    "\tsubject: " + appointConference.meetingInfo.subject + ",\n" +
                    "\tcreateorAccount: " + appointConference.meetingInfo.hostInfo.account + ",\n" +
                    "\tparticipantList: \n" +
                "{\n";
        for (JNIUserInfo appointParticipantInfo : appointConference.participantList) {
            msg +=
                        "\t\taccount: " + appointParticipantInfo.account + ",\n" +
                        "\t\tnickName: " + appointParticipantInfo.name + ",\n" +
                        "\t\torgId: " + String.valueOf(appointParticipantInfo.departmentId) + ",\n" +
                        "\t\tuserIcon: " + appointParticipantInfo.icon + ",\n";
        }
        msg +=
                "}\n" +
                        "}\n";
        Log.d(TAG, msg);
        return nRet;
    }

    public int TEST_arrayListInTest() {
        ArrayList<JNIOrgInfo> orgInfos = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            JNIOrgInfo orgInfo = new JNIOrgInfo();
            orgInfo.orgId = i;
            orgInfo.orgName = "orgName_" + String.valueOf(i);
            orgInfo.parentId = -1;
            orgInfo.hasChild = i % 2 == 0;
            orgInfos.add(orgInfo);

            Log.d("guol_debug", "orgInfos.size = " + orgInfos.size());
            JNIOrgInfo orgInfo1 = null;
            orgInfos.add(orgInfo1);
            Log.d("guol_debug", "orgInfos.size = " + orgInfos.size());
        }
        nRet = JNINetProtocol.arrayListTest(orgInfos);
        return nRet;
    }

    public int TEST_arrayListTest() {
        ArrayList<JNIOrgInfo> orgInfo = new ArrayList<>();
        nRet = JNINetProtocol.arrayListTest(orgInfo);
        if (nRet != 0) {
            Log.e(TAG, "arrayListTest failed! ret: " + String.valueOf(nRet) + " msg: " + JNINetProtocol.codeToMsg(nRet));
            return nRet;
        }
        for (JNIOrgInfo jniOrgInfo : orgInfo) {
            if (jniOrgInfo.orgId < 10) {
                Log.e(TAG, "jniOrgInfo.orgId = " + jniOrgInfo.orgId);
                Log.e(TAG, "jniOrgInfo.orgName = " + jniOrgInfo.orgName);
                Log.e(TAG, "jniOrgInfo.parentId = " + jniOrgInfo.parentId);
                Log.e(TAG, "jniOrgInfo.hasChild = " + jniOrgInfo.hasChild);
            }
        }
        return nRet;
    }

    public int TEST_httpGet() {
        JNICommType rspBody = new JNICommType();
        return JNINetProtocol.httpGet("https://www.baidu.com/", rspBody);
    }

    public int TEST_needVersionUpgrade() {
        JNICommType needUpgrade = new JNICommType();
        JNICommType forceStatus = new JNICommType();
        JNICommType downLoadUrl = new JNICommType();
        JNICommType version = new JNICommType();
        JNICommType apkSize = new JNICommType();
        JNICommType details = new JNICommType();
        nRet = JNINetProtocol.needVersionUpgrade(needUpgrade, forceStatus, downLoadUrl, version, apkSize, details);
        if (nRet != 0) {
            Log.e(TAG, "needUpgrade failed");
            return nRet;
        }
        Log.d(TAG, "TEST_needVersionUpgrade needupgrade:" + needUpgrade.boolVar + "url:" + downLoadUrl.str + "version:" + version.str);
        return nRet;
    }

    public int TEST_getMeetingInfo() {
        JNIStMeeting meetinginfo = new JNIStMeeting();
        nRet = JNINetProtocol.getMeetingInfo(meetinginfo);
        if (nRet != 0) {
            Log.e(TAG, "getmeetinginfo failed");
        } else {
            Log.e(TAG, "meeting info  mute mode : " + String.valueOf(meetinginfo.joinRoomMuteMode));
        }
        return nRet;
    }

    public int TEST_getAllConferenceSummary() {
        JNIDataPageInfo pageInfoIn = new JNIDataPageInfo();
        pageInfoIn.upToAll = true;
        pageInfoIn.pageNum = 1;
        pageInfoIn.pageSize = 10;

        ArrayList<JNIStAppointConference> summaries = new ArrayList<>();
        JNIDataPageInfo pageInfoOut = new JNIDataPageInfo();
        nRet = JNINetProtocol.getAllConferenceSummary(1, "", pageInfoIn, summaries, pageInfoOut);
        if (nRet != 0) {
            Log.e(TAG, "getAllConferenceSummary failed");
            return nRet;
        }
        return nRet;
    }

    public int getAllConferenceSummaryOfPeriodOfTime() {
        JNIDataPageInfo pageInfoIn = new JNIDataPageInfo();
        pageInfoIn.upToAll = true;
        pageInfoIn.pageNum = 1;
        pageInfoIn.pageSize = 10;

        ArrayList<JNIStAppointConference> summaries = new ArrayList<>();
        JNIDataPageInfo pageInfoOut = new JNIDataPageInfo();
        nRet = JNINetProtocol.getAllConferenceSummaryOfPeriodOfTime(1, "2021-04-27", "2021-05-03", pageInfoIn, summaries, pageInfoOut);
        if (nRet != 0) {
            Log.e(TAG, "getAllConferenceSummary failed");
            return nRet;
        }
        return nRet;
    }

    public int TEST_setFrenquentContact() {
        JNIOrgMemberInfo memberInfo = new JNIOrgMemberInfo();
        memberInfo.account = "80100101060";
        memberInfo.uuid = "80100101060";
        memberInfo.isFrequentContact = true;
        nRet = JNINetProtocol.updateContact(memberInfo);
        if (nRet != 0) {
            Log.e(TAG, "updateContact failed");
            return nRet;
        }
        return nRet;
    }

    public int TEST_getPagesOfOrgDepart() {
        JNIDataPageInfo pageInfoIn = new JNIDataPageInfo();
        pageInfoIn.pageNum = 1;
        pageInfoIn.pageSize = 3;

        ArrayList<JNIOrgInfo> orgInfos = new ArrayList<>();
        JNIDataPageInfo pageInfoOut = new JNIDataPageInfo();
        nRet = JNINetProtocol.getPagesOfOrgDepart(0, pageInfoIn, orgInfos, pageInfoOut);
        if (nRet != 0) {
            Log.e(TAG, "getPagesOfOrgDepart failed");
            return nRet;
        }
        return nRet;
    }

    private int TEST_getPagesOfOrgMemebers() {
        JNIDataPageInfo pageInfoIn = new JNIDataPageInfo();
        pageInfoIn.pageNum = 1;
        pageInfoIn.pageSize = 3;

        ArrayList<JNIOrgMemberInfo> memberInfos = new ArrayList<>();
        JNIDataPageInfo pageInfoOut = new JNIDataPageInfo();
        nRet = JNINetProtocol.getPagesOfOrgMember(1, pageInfoIn, memberInfos, pageInfoOut);
        if (nRet != 0) {
            Log.e(TAG, "getPagesOfOrgMember failed");
            return nRet;
        }
        return nRet;
    }

    public int TEST_getGroupList() {
        JNIDataPageInfo pageInfoIn = new JNIDataPageInfo();
        pageInfoIn.upToAll = true;
        pageInfoIn.pageNum = 1;
        pageInfoIn.pageSize = 3;

        ArrayList<JNIGroupInfo> groupInfos = new ArrayList<>();
        JNIDataPageInfo pageInfoOut = new JNIDataPageInfo();
        nRet = JNINetProtocol.getGroupList(0, pageInfoIn, groupInfos, pageInfoOut);
        if (nRet != 0) {
            Log.e(TAG, "getGroupList failed");
            return nRet;
        }
        return nRet;
    }

    public int TEST_setMeetingInfo(JNIStMeeting roomInfo) {
        // Note(guol)
        //  可适配
        int option = 0;
//        roomInfo.isLocked = true;
//        nRet = JNINetProtocol.setMeetingInfo(option, roomInfo);
//        if (nRet != 0) {
//            Log.e(TAG, "setRoomInfo[" + String.valueOf(option) + "] failed");
//        }

//        option = 2;
//        roomInfo.allowPartOperSpeaker = false;
//        nRet = JNINetProtocol.setMeetingInfo(option, roomInfo);
//        if (nRet != 0) {
//            Log.e(TAG, "setRoomInfo[" + String.valueOf(option) + "] failed");
//        }
//
//        option = 3;
//        roomInfo.permissionShare = false;
//        nRet = JNINetProtocol.setMeetingInfo(option, roomInfo);
//        if (nRet != 0) {
//            Log.e(TAG, "setRoomInfo[" + String.valueOf(option) + "] failed");
//        }
//
        option = 4;
        roomInfo.allowPartOpenMic = false;
        nRet = JNINetProtocol.setMeetingInfo(option, roomInfo);
        if (nRet != 0) {
            Log.e(TAG, "setRoomInfo[" + String.valueOf(option) + "] failed");
        }
//
//        option = 5;
//        roomInfo.allowPartInviteOthers = true;
//        nRet = JNINetProtocol.setMeetingInfo(option, roomInfo);
//        if (nRet != 0) {
//            Log.e(TAG, "setRoomInfo[" + String.valueOf(option) + "] failed");
//        }
//
//        option = 6;
//        roomInfo.allowCallInType = 0;
//        nRet = JNINetProtocol.setMeetingInfo(option, roomInfo);
//        if (nRet != 0) {
//            Log.e(TAG, "setRoomInfo[" + String.valueOf(option) + "] failed");
//        }

        option = 8;
        roomInfo.joinRoomMuteMode = 2;        nRet = JNINetProtocol.setMeetingInfo(option, roomInfo);
        if (nRet != 0) {
            Log.e(TAG, "setRoomInfo[" + String.valueOf(option) + "] failed");
        }

        return nRet;
    }

    public int TEST_groupRelated() {
        nRet = 0;
        String groupName = "Android_demo_createGroup_1";

        String[] memberList_createGroup = new String[2];
        memberList_createGroup[0] = "80100101059";
        memberList_createGroup[1] = "80100101060";

        nRet = JNINetProtocol.createGroup(groupName, memberList_createGroup);
        if (nRet != 0) {
            Log.e(TAG, "createGroup failed");
        }

        nRet = JNINetProtocol.createGroup(groupName, memberList_createGroup);
        if (nRet != 0) {
            Log.e(TAG, "createGroup failed");
        }

        JNIDataPageInfo pageInfoIn = new JNIDataPageInfo();
        pageInfoIn.upToAll = true;
        pageInfoIn.pageSize = 10;
        ArrayList<JNIGroupInfo> groupInfos = new ArrayList<>();
        JNIDataPageInfo pageInfoOut = new JNIDataPageInfo();
        nRet = JNINetProtocol.getGroupList(0, pageInfoIn, groupInfos, pageInfoOut);
        if (nRet != 0) {
            Log.e(TAG, "getGroupList failed");
        }

        if (groupInfos.size() > 0) {
            JNIGroupInfo groupInfo = groupInfos.get(0);
            groupName = "Android_demo_updateGroup";
            String[] memberList_updateGroup = new String[3];
            memberList_updateGroup[0] = "80100101059";
            memberList_updateGroup[1] = "80100101060";
            memberList_updateGroup[2] = "80100101061";
//        nRet = JNINetProtocol.updateGroup(groupInfo.groupId, groupName, memberList_updateGroup);
            if (nRet != 0) {
                Log.e(TAG, "updateGroup failed");
            }

            ArrayList<JNIOrgMemberInfo> memberInfos = new ArrayList<>();
            nRet = JNINetProtocol.getGroupMember(groupInfo.groupId, pageInfoIn, memberInfos, pageInfoOut);
            if (nRet != 0) {
                Log.e(TAG, "getGroupMember failed");
            }
        }

        groupInfos.clear();
        nRet = JNINetProtocol.getGroupList(0, pageInfoIn, groupInfos, pageInfoOut);
        if (nRet != 0) {
            Log.e(TAG, "getGroupList failed");
        }

//        if (true) {
//            nRet = JNINetProtocol.delGroup(groupInfo.groupId);
//            if (nRet != 0) {
//                Log.e(TAG, "delGroup failed");
//            }
//        }
//        else {
//            for (int i = 9; i < 12; i++) {
//                nRet = JNINetProtocol.delGroup(i);
//                if (nRet != 0) {
//                    Log.e(TAG, "delGroup failed");
//                }
//            }
//        }

//        groupInfos.clear();
//        nRet = JNINetProtocol.getGroupList(0, pageInfoIn, groupInfos, pageInfoOut);
//        if (nRet != 0) {
//            Log.e(TAG, "getGroupList failed");
//        }

        return nRet;
    }

    public int TEST_getOrgMemberRecursively() {
        ArrayList<Integer> integers = new ArrayList<>();
        integers.add(2);

        ArrayList<String> strings = new ArrayList<>();
        strings.add("80100101060");

        ArrayList<JNIOrgMemberInfo> memberInfos = new ArrayList<>();
        nRet = JNINetProtocol.getOrgMemberRecursively(integers, strings, memberInfos);
        if (nRet != 0) {
            Log.e(TAG, "getOrgMemberRecursively failed");
        }
        return nRet;
    }

    public int TEST_meetingControl() {
        String account = m_account;

        JNICommType livingUrl = new JNICommType();
        nRet = JNINetProtocol.startLive(account, livingUrl);
        if (nRet != 0) {
            Log.e(TAG, "startLive failed! ret:" + String.valueOf(nRet));
        }

        nRet = JNINetProtocol.stopLive(account);
        if (nRet != 0) {
            Log.e(TAG, "stopLive failed! ret:" + String.valueOf(nRet));
        }

        JNICommType liveStatus = new JNICommType();
        nRet = JNINetProtocol.getLiveStatus(account, liveStatus);
        if (nRet != 0) {
            Log.e(TAG, "stopLive failed! ret:" + String.valueOf(nRet));
        }

        nRet = JNINetProtocol.startConferenceRecord(account, false);
        if (nRet != 0) {
            Log.e(TAG, "startConferenceRecord failed! ret:" + String.valueOf(nRet));
        }

        nRet = JNINetProtocol.stopConferenceRecord(account);
        if (nRet != 0) {
            Log.e(TAG, "startConferenceRecord failed! ret:" + String.valueOf(nRet));
        }

            /*    nRet = sdNProtocol
                if (nRet != 0) {
                    Log.e(TAG, "startConferenceRecord failed! ret:" + String.valueOf(nRet));
                }*/

        nRet = JNINetProtocol.evictedParticipant(account);
        if (nRet != 0) {
            Log.e(TAG, "evictedParticipant failed! ret:" + String.valueOf(nRet));
        }

        return nRet;
    }

    public int TEST_setPullStreamStatus() {
        ArrayList<JNIMediaControlParam> params = new ArrayList<>();
        params.add(new JNIMediaControlParam(m_account, 0, 1));
        nRet = JNINetProtocol.setPullStreamStatus(params, 0);
        if (nRet != 0) {
            Log.e(TAG, "setStreamStatus failed! ret:" + String.valueOf(nRet));
        }
        return nRet;
    }

    public int TEST_setPushStreamStatus() {
        nRet = JNINetProtocol.setPushStreamStatus(m_account, 0, 1);
        nRet = JNINetProtocol.setPushStreamStatus(m_account, 0, 0);
        return nRet;
    }

    public int TEST_setRollCall() {
        nRet = JNINetProtocol.setRollCallStatus("80100201091", "80100201091", true, 0);
        if (nRet != 0) {
            Log.e(TAG, "setRollCallStatus failed! ret:" + String.valueOf(nRet));
        }
        return nRet;
    }

    public int TEST_setConferenceLayout() {
//        nRet = JNINetProtocol.setConferenceLayout(true, 4, 0);
        if (nRet != 0) {
            Log.e(TAG, "setConferenceLayout failed");
        }
        return nRet;
    }

    private int TEST_getH5Pages() {
        ArrayList<JNIH5PageInfo> jnih5PageInfos = new ArrayList<>();
        nRet = JNINetProtocol.getH5Pages(0, jnih5PageInfos);
        if (nRet != 0) {
            Log.e(TAG, "getH5Pages failed");
        }

        jnih5PageInfos.clear();
        nRet = JNINetProtocol.getH5PagesByHttp(0, jnih5PageInfos);
        if (nRet != 0) {
            Log.e(TAG, "getH5PagesByHttp failed");
        }
        return nRet;
    }

    private int TEST_setPtzControlStatus() {
        JNIPtzControlParam ptzControlParam = new JNIPtzControlParam();
        ptzControlParam.targetAccount = m_account;
        ptzControlParam.operation = 1;
        ptzControlParam.maxDuration = 100;
        nRet = JNINetProtocol.setPtzControlStatus(true, ptzControlParam);
        if (nRet != 0) {
            Log.e(TAG, "setPtzControlStatus[true] failed");
        }

        nRet = JNINetProtocol.setPtzControlStatus(false, ptzControlParam);
        if (nRet != 0) {
            Log.e(TAG, "setPtzControlStatus[false] failed");
        }

        return nRet;
    }

    private int TEST_adjustResolution() {
        int resolution = 1080;
        nRet = JNINetProtocol.adjustResolution(resolution);
        if (nRet != 0) {
            Log.e(TAG, "adjustResolution[" + String.valueOf(resolution) + "] failed");
        }

        return nRet;
    }

    private int TEST_setPresetPosition() {
        String serialNumber = "serialNumber";
        int index = 0;
        String image = "image";
        JNIPresetPositionConfigInfo configInfo = new JNIPresetPositionConfigInfo();
        nRet = JNINetProtocol.setPresetPosition(serialNumber, index, image, configInfo);
        if (nRet != 0) {
            Log.e(TAG, "setPresetPosition[" + String.valueOf(index) + "] failed");
        }

        return nRet;
    }

    private int TEST_valueString(StringBuilder str) {
        str.append("hello world");
        return 0;
    }

    private int TEST_getCompanyResourceInfo() {
        JNICompanyInfo companyInfo = new JNICompanyInfo();
        nRet = JNINetProtocol.getCompanyResourceInfo(companyInfo);

        return nRet;
    }

    private int TEST_switchVoiceMode() {
        nRet = JNINetProtocol.switchVoiceMode(0);
        return nRet;
    }

    private int TEST_uploadTerminalInfo() {
        JNITerminalLocalInfo info = new JNITerminalLocalInfo();
        info.ability = "MultiCastPlay";
        info.functionality = "{\"MultiCastPlay\": true,\"MultiCastPlayUsable\": true,\"ScreenShare\": false,\"ScreenShareUsable\": false}";
        nRet = JNINetProtocol.uploadTerminalInfo(info);
        return nRet;
    }

    private int TEST_countParticipatedDuration() {
        JNIDataPageInfo pageInfoIn = new JNIDataPageInfo();
        pageInfoIn.upToAll = true;
        pageInfoIn.pageNum = 1;
        pageInfoIn.pageSize = 10;

        ArrayList<JNIStMeeting> roomInfos = new ArrayList<>();
        JNIDataPageInfo pageInfoOut = new JNIDataPageInfo();
        nRet = JNINetProtocol.countParticipatedDuration(pageInfoIn, roomInfos, pageInfoOut);
        if (nRet != 0) {
            Log.e(TAG, "countParticipatedDuration failed");
            return nRet;
        }
        return nRet;
    }

    private int TEST_getUnfinishedRoom() {
        JNIUnfinishedRoomInfo roomInfo = new JNIUnfinishedRoomInfo();
        nRet = JNINetProtocol.getUnfinishedRoom(roomInfo);
        if (nRet != 0) {
            Log.e(TAG, "getUnfinishedRoom failed");
            return nRet;
        }
        return nRet;
    }

    private int TEST_uploadMeetingQuality() {
        JNINetworkQuality networkQuality = new JNINetworkQuality();
        networkQuality.uploadBandwidth = "uploadBandwidth";
        networkQuality.downloadBandwidth = "downloadBandwidth";
        networkQuality.delay = 30;

        ArrayList<JNIStreamQuality> streamQualities = new ArrayList<>();
        JNIStreamQuality streamQuality1 = new JNIStreamQuality();
        streamQuality1.type = 0;
        streamQuality1.resolution = "resolution";
        streamQuality1.videoBitRate = "videoBitRate";
        streamQuality1.audioBitRate = "audioBitRate";
        streamQuality1.fps = 15;
        streamQuality1.videoPacketLostRate = 10.0D;
        streamQuality1.audioPacketLostRate = 10.0D;
        streamQualities.add(streamQuality1);

        JNIStreamQuality streamQuality2 = new JNIStreamQuality();
        streamQuality2.type = 1;
        streamQuality2.resolution = "resolution";
        streamQuality2.videoBitRate = "videoBitRate";
        streamQuality2.audioBitRate = "audioBitRate";
        streamQuality2.fps = 15;
        streamQuality2.videoPacketLostRate = 10.0D;
        streamQuality2.audioPacketLostRate = 10.0D;
        streamQualities.add(streamQuality2);

        JNIStreamQuality streamQuality3 = new JNIStreamQuality();
        streamQuality3.type = 2;
        streamQuality3.resolution = "resolution";
        streamQuality3.videoBitRate = "videoBitRate";
        streamQuality3.audioBitRate = "audioBitRate";
        streamQuality3.fps = 15;
        streamQuality3.videoPacketLostRate = 10.0D;
        streamQuality3.audioPacketLostRate = 10.0D;
        streamQualities.add(streamQuality3);

        nRet = JNINetProtocol.uploadMeetingQuality(networkQuality, streamQualities);
        if (nRet != 0) {
            Log.e(TAG, "uploadMeetingQuality failed");
            return nRet;
        }
        return nRet;
    }

    private int TEST_pushLog() {
        JNIPushLogParams params = new JNIPushLogParams();
        params.account = m_account;
        params.logName = "logName";
        params.version = "version";
        params.terminalType = 1;
        params.deviceModel = "deviceModel";

        nRet = JNINetProtocol.pushLog(params);
        if (nRet != 0) {
            Log.e(TAG, "pushLog failed");
            return nRet;
        }
        return nRet;
    }

    private int TEST_getAccount() {
        JNICommType account = new JNICommType();
        JNICommType passwd = new JNICommType();
        nRet = JNINetProtocol.getAccount("C9Z20200608003", account, passwd);
        if (nRet != 0) {
            Log.e(TAG, "getAccount failed");
            return nRet;
        }
        return nRet;
    }

    private int TEST_queryOperationPermission() {
        ArrayList<Integer> permissions = new ArrayList<>();
        ArrayList<Integer> abilities = new ArrayList<>();
        nRet = JNINetProtocol.queryOperationPermission(permissions, abilities);
        return nRet;
    }

    private int TEST_getAppointedMeetingRoom() {
        JNIMeetingRoom meetingRoom = new JNIMeetingRoom();
        JNICommType ruid = new JNICommType();
        nRet = JNINetProtocol.getAppointedMeetingRoom(m_account, meetingRoom, ruid);
        return nRet;
    }

    private int TEST_getFrequentContacts(JNIOrgMemberInfo memberInfo) {
        JNIDataPageInfo pageInfoIn = new JNIDataPageInfo();
        pageInfoIn.upToAll = true;

        ArrayList<JNIOrgMemberInfo> contactList = new ArrayList<>();
        JNIDataPageInfo pageInfoOut = new JNIDataPageInfo();

        nRet = JNINetProtocol.getFrequentContacts(pageInfoIn, contactList, pageInfoOut);
        if (contactList.size() > 0) {
            memberInfo = contactList.get(0);
        }
        return nRet;
    }

    private int TEST_getMemberDetails(JNIOrgMemberInfo memberInfo) {
        nRet = JNINetProtocol.getMemberDetails(memberInfo.account, memberInfo);
        return nRet;
    }

    private int TEST_updateContact(JNIOrgMemberInfo memberInfo) {
        memberInfo.isFrequentContact = !memberInfo.isFrequentContact;
//        memberInfo.isFrequentContact = false;
        nRet = JNINetProtocol.updateContact(memberInfo);
        return nRet;
    }

    private int TEST_getAllMeetingRooms() {
        JNIDataPageInfo pageInfoIn = new JNIDataPageInfo();
        pageInfoIn.upToAll = true;

        JNIAllMeetingRooms allMeetingRooms = new JNIAllMeetingRooms();
        JNIDataPageInfo pageInfoOut = new JNIDataPageInfo();
        nRet = JNINetProtocol.getAllMeetingRooms(pageInfoIn, false, allMeetingRooms, pageInfoOut);
        for (JNIMeetingRoom meetingRoom : allMeetingRooms.fixedMeetingRooms) {
            Log.d(TAG, "TEST_getAllMeetingRooms: \n" +
                    "_________________________________________________" + "\n" +
                    "type: " + meetingRoom.type + "\n" +
                    "id: " + meetingRoom.id + "\n" +
                    "name: " + meetingRoom.name + "\n" +
                    "status: " + meetingRoom.status + "\n" +
                    "capacity: " + meetingRoom.capacity + "\n" +
                    "shortNum: " + meetingRoom.shortNum + "\n" +
                    "expiredDate: " + meetingRoom.expiredDate + "\n" +
                    "roomIcon: " + meetingRoom.roomIcon + "\n" +
                    "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
        }
        return nRet;
    }

    private int TEST_getAllPublishers() {
        ArrayList<JNIStParticipantInfo> publishers = new ArrayList<>();
        JNIStParticipantInfo lecturer = new JNIStParticipantInfo();
        JNIStParticipantInfo sharer = new JNIStParticipantInfo();
        nRet = JNINetProtocol.getAllPublishers(publishers, lecturer, sharer);
        for (JNIStParticipantInfo participantInfo : publishers) {
            Log.d(TAG, "part: " + participantInfo.toString());
        }

        return nRet;
    }

    private int TEST_getPagesOfParticipants() {
        int order = 0;
        int countOfParticipant = 1;
        boolean positive = true;
        for (; ; ) {
            ArrayList<JNIStParticipantInfo> participantInfos = new ArrayList<>();
            nRet = JNINetProtocol.getPagesOfParticipants(order++, countOfParticipant, positive, participantInfos);
            if (participantInfos.isEmpty() || nRet != 0) {
                break;
            }
        }

        return nRet;
    }

    private int sleep(int millis) {
        try {
            Thread.sleep(millis);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return 0;
    }

    private int TEST_getLoginInfo() {
        JNILoginInfo loginInfo = new JNILoginInfo();
        nRet = JNINetProtocol.getLoginInfo(loginInfo);
        return nRet;
    }

    private int TEST_getParticipant() {
        JNIStParticipantInfo participantInfo = new JNIStParticipantInfo();
        return JNINetProtocol.getParticipant(m_account, participantInfo);
    }

    private int TEST_getSubscriber() {
        JNIStParticipantInfo participantInfo = new JNIStParticipantInfo();
        return JNINetProtocol.getSubscriber(m_account, participantInfo);
    }

    private int TEST_setMeetingInfo() {
        JNIStMeeting meeting = new JNIStMeeting();
        nRet = JNINetProtocol.getMeetingInfo(meeting);

        meeting.allowPartOpenMic = false;
        nRet = JNINetProtocol.setMeetingInfo(4, meeting);

        meeting.joinRoomMuteMode = 1;
        nRet = JNINetProtocol.setMeetingInfo(8, meeting);

        return nRet;
    }

    private int TEST_applyOpenMic() {
        nRet = JNINetProtocol.applyOpenMic();
        return nRet;
    }

    private int TEST_changeMeetingLayout() {
        JNIView view = new JNIView();
        view.account = m_account;
        view.streamType = 0;

        ArrayList<JNIView> views = new ArrayList<>();
        views.add(view);

        nRet = JNINetProtocol.changeMeetingLayout(1, 1, views);
        return nRet;
    }

    private int TEST_inviteParticipant() {
        String roomId = m_roomId;
        String[] accountList = new String[]{"80100201090"};
        long expireTime = 1634805734000l;
        nRet = JNINetProtocol.inviteParticipant(roomId, accountList, expireTime);
        return nRet;
    }

    private int TEST_getCalleeList() {
        ArrayList<JNICalleeInfo> calleeInfos = new ArrayList<>();
        nRet = JNINetProtocol.getCalleeList(calleeInfos);
        for (JNICalleeInfo calleeInfo : calleeInfos)
        {
            Log.d(TAG, "TEST_getCalleeList: " + calleeInfo.userInfo.account);
        }

        return nRet;
    }
}
