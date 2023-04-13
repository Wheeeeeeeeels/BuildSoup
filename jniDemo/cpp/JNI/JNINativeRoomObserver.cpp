#include "JNINativeRoomObserver.h"
#include "jvm.h"

#include "SDNPLogger.h"
#include "JNICommon.h"

namespace SDNP {

    CJNINativeRoomObserver::CJNINativeRoomObserver()
    {
		m_globalRef = NULL;
    }

    CJNINativeRoomObserver::~CJNINativeRoomObserver()
    {

    }
    
    void CJNINativeRoomObserver::onMeetingCreated(std::string roomId)
    {
        infof("====== onRoomCreated, roomId: %s", roomId.c_str());
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass) {
            errorf("FIND CLASS FAILED!!!");
            return ;
        }
        
        jmethodID onRoomCreatedID = jniEnv->GetMethodID(roomObserverClass, "onMeetingCreated", 
                                                    "(Ljava/lang/String;)V");
        jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
        jniEnv->CallVoidMethod(m_jniRoomObserver, onRoomCreatedID, jstrRoomId);
        jniEnv->DeleteLocalRef(jstrRoomId);
        jniEnv->DeleteLocalRef(roomObserverClass);
    }

    void CJNINativeRoomObserver::onMeetingClosed(EnMeetingClosedReason reason)
    {
        infof("====== onMeetingClosed");
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass) {
            errorf("FIND CLASS FAILED!!!");
            return ;
        }
        
        jmethodID onMeetingClosedID = jniEnv->GetMethodID(roomObserverClass, "onMeetingClosed", "(I)V");
        jniEnv->CallVoidMethod(m_jniRoomObserver, onMeetingClosedID, (int)reason);
        jniEnv->DeleteLocalRef(roomObserverClass);
    }

	void CJNINativeRoomObserver::onMeetingInfoChanged(EnMeetingInfoOption option, StMeeting meetingInfo)
	{
        infof("====== onMeetingInfoChanged: option[%d].", static_cast<int>(option));
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass) {
            errorf("FIND CLASS FAILED!!!");
            return ;
        }        
        jmethodID onMeetingClosedID = jniEnv->GetMethodID(roomObserverClass, "onMeetingInfoChanged", 
			"(ILcn/geedow/netprotocol/JNIStMeeting;)V");
        jniEnv->DeleteLocalRef(roomObserverClass);

		jclass jniMeetingInfoClass = jniEnv->GetObjectClass(m_globalRef->getGlobalRef(STMEETING_INFO_CLASS_NAME));
		if (!jniMeetingInfoClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return ;
		}
		jmethodID meetingInfoConstructorID = jniEnv->GetMethodID(jniMeetingInfoClass, "<init>", "()V");
		jobject joMeetingInfo = jniEnv->NewObject(jniMeetingInfoClass, meetingInfoConstructorID);
		jniEnv->DeleteLocalRef(jniMeetingInfoClass);
		
		JNICommon::setFieldValue(jniEnv, meetingInfo, joMeetingInfo);

        jniEnv->CallVoidMethod(m_jniRoomObserver, onMeetingClosedID, (int)option, joMeetingInfo);
	}

	void CJNINativeRoomObserver::onJoined(std::string roomId, std::string account, StParticipantInfo participant)
	{
         infof("====== onJoined, roomId: %s, account: %s", roomId.c_str(), account.c_str());
         JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

         jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
         if (!roomObserverClass) {
             errorf("AttachCurrentThreadIfNeeded FIND CLASS FAILED!!!");         
             return ;
         }        
         jmethodID onJoinedID = jniEnv->GetMethodID(roomObserverClass, "onJoined", 
		 	"(Ljava/lang/String;Ljava/lang/String;Lcn/geedow/netprotocol/JNIStParticipantInfo;)V");
		 jniEnv->DeleteLocalRef(roomObserverClass);

         jclass jniPartInfoClass = jniEnv->GetObjectClass(m_globalRef->getGlobalRef(STPARTICIPANTINFO_INFO_CLASS_NAME));
         if (!jniPartInfoClass) {
             errorf("FIND CLASS FAILED!!!");
             return ;
         }
         jmethodID partInfoConstructorID = jniEnv->GetMethodID(jniPartInfoClass, "<init>", "()V");
		 jobject joPartInfo = jniEnv->NewObject(jniPartInfoClass, partInfoConstructorID);
		 jniEnv->DeleteLocalRef(jniPartInfoClass);

		 JNICommon::setFieldValue(jniEnv, participant, joPartInfo);
		 jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
		 jstring jstrAccount = jniEnv->NewStringUTF(account.c_str());

         jniEnv->CallVoidMethod(m_jniRoomObserver, onJoinedID, jstrRoomId, jstrAccount, joPartInfo);

         jniEnv->DeleteLocalRef(jstrRoomId);
         jniEnv->DeleteLocalRef(jstrAccount);
         jniEnv->DeleteLocalRef(joPartInfo);
	}

	void CJNINativeRoomObserver::onLeftNotify(std::string roomId, std::string account, EnParticipantLeftReason reason)
	{
		infof("====== onLeftNotify, roomId: %s, account: %s", roomId.c_str(), account.c_str());
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass) {
			errorf("FIND CLASS FAILED!!!");
			return;
		}

		jmethodID onLeftID = jniEnv->GetMethodID(roomObserverClass, "onLeftNotify",
			"(Ljava/lang/String;Ljava/lang/String;I)V");
		jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
		jstring jstrAccount = jniEnv->NewStringUTF(account.c_str());
		jniEnv->CallVoidMethod(m_jniRoomObserver, onLeftID, jstrRoomId, jstrAccount, (int)reason);
		jniEnv->DeleteLocalRef(jstrRoomId);
		jniEnv->DeleteLocalRef(jstrAccount);
		jniEnv->DeleteLocalRef(roomObserverClass);
	}

    void CJNINativeRoomObserver::onPublished(std::string roomId, std::string account, EnStreamType streamType, bool videoStatus, bool audioStatus)
    {
         infof("====== onPublished, roomId: %s, account: %s, streamType: %d, videoStatus: %d, audioStatus: %d",
             roomId.c_str(), account.c_str(), streamType, videoStatus, audioStatus);
         JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

         jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
         if (!roomObserverClass) {
             errorf("FIND CLASS FAILED!!!");
             return ;
         }
        
         jmethodID onPublishedID = jniEnv->GetMethodID(roomObserverClass, "onPublished", 
                                                     "(Ljava/lang/String;Ljava/lang/String;IZZ)V");
         jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
         jstring jstrAccount = jniEnv->NewStringUTF(account.c_str());
         jniEnv->CallVoidMethod(m_jniRoomObserver, onPublishedID, jstrRoomId, jstrAccount, streamType, videoStatus, audioStatus);
         jniEnv->DeleteLocalRef(jstrRoomId);
         jniEnv->DeleteLocalRef(jstrAccount);
         jniEnv->DeleteLocalRef(roomObserverClass);
    }

	void CJNINativeRoomObserver::onStopPublished(std::string roomId, std::string account, EnStreamType streamType)
	{
         infof("====== onStopPublished, roomId: %s, account: %s, streamType: %d", roomId.c_str(), account.c_str(), streamType);
         JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

         jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
         if (!roomObserverClass) {
             errorf("FIND CLASS FAILED!!!");
             return ;
         }        
         jmethodID onUnpublishedID = jniEnv->GetMethodID(roomObserverClass, "onStopPublished", 
                                                     "(Ljava/lang/String;Ljava/lang/String;I)V");
         jniEnv->DeleteLocalRef(roomObserverClass);	

         jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
         jstring jstrAccount = jniEnv->NewStringUTF(account.c_str());
         jniEnv->CallVoidMethod(m_jniRoomObserver, onUnpublishedID, jstrRoomId, jstrAccount, streamType);
         jniEnv->DeleteLocalRef(jstrRoomId);
         jniEnv->DeleteLocalRef(jstrAccount);
	}

    void CJNINativeRoomObserver::onIceCandidate(std::string roomId, std::string account, EnStreamType streamType, std::string sdpMid, std::string sdpMLineIndex, std::string candidate)
    {
        infof("====== onIceCandidate, roomId: %s, account: %s, streamType: %d, sdpMid: %s, sdpMLineIndex: %s, candidate: %s",
            roomId.c_str(), account.c_str(), streamType, sdpMid.c_str(), sdpMLineIndex.c_str(), candidate.c_str());
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass) {
            errorf("FIND CLASS FAILED!!!");
            return ;
        }
        
        jmethodID onIceCandidateID = jniEnv->GetMethodID(roomObserverClass, "onIceCandidate", 
                                                    "(Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
        jstring jstrAccount = jniEnv->NewStringUTF(account.c_str());
        jstring jstSdpMid = jniEnv->NewStringUTF(sdpMid.c_str());
        jstring jstrSdpMLineIndex = jniEnv->NewStringUTF(sdpMLineIndex.c_str());
        jstring jstrCandidate = jniEnv->NewStringUTF(candidate.c_str());
        jniEnv->CallVoidMethod(m_jniRoomObserver, onIceCandidateID, jstrRoomId, jstrAccount, streamType, 
                                 jstSdpMid, jstrSdpMLineIndex, jstrCandidate);
        jniEnv->DeleteLocalRef(jstrRoomId);
        jniEnv->DeleteLocalRef(jstrAccount);
        jniEnv->DeleteLocalRef(jstSdpMid);
        jniEnv->DeleteLocalRef(jstrSdpMLineIndex);
        jniEnv->DeleteLocalRef(jstrCandidate);
        jniEnv->DeleteLocalRef(roomObserverClass);
    }

	void CJNINativeRoomObserver::onSetShareState(std::string handleAccount, std::string shareAccount, bool shareState)
	{
		infof("====== onSetShareState, handleAccount: %s, shareAccount: %s", handleAccount.c_str(), shareAccount.c_str());
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass) {
			errorf("FIND CLASS FAILED!!!");
			return;
		}

		jmethodID onSetShareStateID = jniEnv->GetMethodID(roomObserverClass, "onSetShareState",
			"(Ljava/lang/String;Ljava/lang/String;Z)V");
		jstring jstrHandleAccount = jniEnv->NewStringUTF(handleAccount.c_str());
		jstring jstrShareAccount = jniEnv->NewStringUTF(shareAccount.c_str());
		jniEnv->CallVoidMethod(m_jniRoomObserver, onSetShareStateID, jstrHandleAccount, jstrShareAccount, shareState);
		jniEnv->DeleteLocalRef(jstrHandleAccount);
		jniEnv->DeleteLocalRef(jstrShareAccount);
		jniEnv->DeleteLocalRef(roomObserverClass);
	}

	void CJNINativeRoomObserver::onInvite(std::string roomId, std::string subject, std::string accountFrom, std::string usernameFrom,
		long long expireTime, std::string password, std::string userIcon, bool audioInStatus, bool videoStatus)
	{
        infof("====== onInvite, roomId: %s, subject: %s, accountFrom: %s, expireTime:%lld, password: %s", 
                roomId.c_str(), subject.c_str(), accountFrom.c_str(), expireTime, password.c_str());
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass) {
            errorf("FIND CLASS FAILED!!!");
            return ;
        }        
        jmethodID onInviteID = jniEnv->GetMethodID(roomObserverClass, "onInvite", 
			"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;JLjava/lang/String;Ljava/lang/String;ZZ)V");
        jniEnv->DeleteLocalRef(roomObserverClass);

        jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
        jstring jstrSubject = jniEnv->NewStringUTF(subject.c_str());
        jstring jstrAccountFrom = jniEnv->NewStringUTF(accountFrom.c_str());
        jstring jstUsernameFrom = jniEnv->NewStringUTF(usernameFrom.c_str());
        jstring jstPassword = jniEnv->NewStringUTF(password.c_str());
        jstring jstrUserIcon = jniEnv->NewStringUTF(userIcon.c_str());

        jniEnv->CallVoidMethod(m_jniRoomObserver, onInviteID, 
			jstrRoomId, jstrSubject, jstrAccountFrom, jstUsernameFrom, expireTime, jstPassword, jstrUserIcon, audioInStatus, videoStatus);

        jniEnv->DeleteLocalRef(jstrRoomId);
        jniEnv->DeleteLocalRef(jstrSubject);
        jniEnv->DeleteLocalRef(jstrAccountFrom);
        jniEnv->DeleteLocalRef(jstUsernameFrom);
        jniEnv->DeleteLocalRef(jstPassword);
        jniEnv->DeleteLocalRef(jstrUserIcon);
	}

    void CJNINativeRoomObserver::onCancelInvite(std::string roomId, std::string accountFrom, std::string usernameFrom)
    {
        infof("====== onCancelInvite, roomId: %s, accountFrom: %s", roomId.c_str(), accountFrom.c_str());
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass) {
            errorf("FIND CLASS FAILED!!!");
            return ;
        }
        
        jmethodID onCancelInviteID = jniEnv->GetMethodID(roomObserverClass, "onCancelInvite", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
        jstring jstrAccountFrom = jniEnv->NewStringUTF(accountFrom.c_str());
        jstring jstUsernameFrom = jniEnv->NewStringUTF(usernameFrom.c_str());
        jniEnv->CallVoidMethod(m_jniRoomObserver, onCancelInviteID, jstrRoomId, jstrAccountFrom, jstUsernameFrom);
        jniEnv->DeleteLocalRef(jstrRoomId);
        jniEnv->DeleteLocalRef(jstrAccountFrom);
        jniEnv->DeleteLocalRef(jstUsernameFrom);
        jniEnv->DeleteLocalRef(roomObserverClass);
    }

	void CJNINativeRoomObserver::onRinging(std::string roomId, std::string accountFrom)
	{
		infof("====== onRinging, roomId: %s, accountFrom: %s", roomId.c_str(), accountFrom.c_str());
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass) {
			errorf("FIND CLASS FAILED!!!");
			return;
		}

		jmethodID onRingringNotifyID = jniEnv->GetMethodID(roomObserverClass, "onRinging", "(Ljava/lang/String;Ljava/lang/String;)V");
		jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
		jstring jstrAccountFrom = jniEnv->NewStringUTF(accountFrom.c_str());
		jniEnv->CallVoidMethod(m_jniRoomObserver, onRingringNotifyID, jstrRoomId, jstrAccountFrom);
		jniEnv->DeleteLocalRef(jstrRoomId);
		jniEnv->DeleteLocalRef(jstrAccountFrom);
		jniEnv->DeleteLocalRef(roomObserverClass);
	}

    void CJNINativeRoomObserver::onRefuseInvite(std::string roomId, std::string accountFrom, std::string usernameFrom, EnRefuseInviteReason reason)
    {
        infof("====== onRefuseInvite, roomId: %s, accountFrom: %s", roomId.c_str(), accountFrom.c_str());
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass) {
            errorf("FIND CLASS FAILED!!!");
            return ;
        }
        
        jmethodID onRefuseInviteID = jniEnv->GetMethodID(roomObserverClass, "onRefuseInvite", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V");
        jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
        jstring jstrAccountFrom = jniEnv->NewStringUTF(accountFrom.c_str());
        jstring jstUsernameFrom = jniEnv->NewStringUTF(usernameFrom.c_str());
        jniEnv->CallVoidMethod(m_jniRoomObserver, onRefuseInviteID, jstrRoomId, jstrAccountFrom, jstUsernameFrom, reason);
        jniEnv->DeleteLocalRef(jstrRoomId);
        jniEnv->DeleteLocalRef(jstrAccountFrom);
        jniEnv->DeleteLocalRef(jstUsernameFrom);
        jniEnv->DeleteLocalRef(roomObserverClass);
    }

	void CJNINativeRoomObserver::onToggleCamera()
	{
        infof("====== onToggleCamera");
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass) {
            errorf("FIND CLASS FAILED!!!");
            return ;
        }        
        jmethodID callbackMethodID = jniEnv->GetMethodID(roomObserverClass, "onToggleCamera", "()V");
        jniEnv->DeleteLocalRef(roomObserverClass);

        jniEnv->CallVoidMethod(m_jniRoomObserver, callbackMethodID);
	}

    void CJNINativeRoomObserver::onVideoStatus(std::string roomId, std::string accountFrom, std::string accountTo, bool status)
    {
        infof("====== onVideoStatus, roomId: %s, accountFrom: %s, accountTo: %s, status: %s", roomId.c_str(), accountFrom.c_str(), accountTo.c_str(), status ? "on" : "off");
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass) {
            errorf("FIND CLASS FAILED!!!");
            return ;
        }
        
        jmethodID onVideoStatusID = jniEnv->GetMethodID(roomObserverClass, "onVideoStatus", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");
        jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
        jstring jstrAccountFrom = jniEnv->NewStringUTF(accountFrom.c_str());
        jstring jstrAccountTo = jniEnv->NewStringUTF(accountTo.c_str());
        jniEnv->CallVoidMethod(m_jniRoomObserver, onVideoStatusID, jstrRoomId, jstrAccountFrom, jstrAccountTo, status);
        jniEnv->DeleteLocalRef(jstrRoomId);
        jniEnv->DeleteLocalRef(jstrAccountFrom);
        jniEnv->DeleteLocalRef(jstrAccountTo);
        jniEnv->DeleteLocalRef(roomObserverClass);
    }

    void CJNINativeRoomObserver::onAudioInStatus(std::string roomId, std::string accountFrom, std::string accountTo, bool status)
    {
		infof("====== onAudioInStatus, roomId: %s, accountFrom: %s, accountTo: %s, status: %s", roomId.c_str(), accountFrom.c_str(), accountTo.c_str(), status ? "on" : "off");
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass) {
            errorf("FIND CLASS FAILED!!!");
            return ;
        }
        
        jmethodID onAudioInStatusID = jniEnv->GetMethodID(roomObserverClass, "onAudioInStatus", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");
        jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
		jstring jstrAccountFrom = jniEnv->NewStringUTF(accountFrom.c_str());
		jstring jstrAccountTo = jniEnv->NewStringUTF(accountTo.c_str());
		jniEnv->CallVoidMethod(m_jniRoomObserver, onAudioInStatusID, jstrRoomId, jstrAccountFrom, jstrAccountTo, status);
        jniEnv->DeleteLocalRef(jstrRoomId);
		jniEnv->DeleteLocalRef(jstrAccountFrom);
		jniEnv->DeleteLocalRef(jstrAccountTo);
        jniEnv->DeleteLocalRef(roomObserverClass);
    }

    void CJNINativeRoomObserver::onAudioOutStatus(std::string roomId, std::string accountFrom, std::string accountTo, bool status)
    {
		infof("====== onAudioOutStatus, roomId: %s, accountFrom: %s, accountTo: %s, status: %s", roomId.c_str(), accountFrom.c_str(), accountTo.c_str(), status ? "on" : "off");
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass) {
            errorf("FIND CLASS FAILED!!!");
            return ;
        }
        
        jmethodID onAudioOutStatusID = jniEnv->GetMethodID(roomObserverClass, "onAudioOutStatus", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");
        jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
		jstring jstrAccountFrom = jniEnv->NewStringUTF(accountFrom.c_str());
		jstring jstrAccountTo = jniEnv->NewStringUTF(accountTo.c_str());
		jniEnv->CallVoidMethod(m_jniRoomObserver, onAudioOutStatusID, jstrRoomId, jstrAccountFrom, jstrAccountTo, status);
        jniEnv->DeleteLocalRef(jstrRoomId);
		jniEnv->DeleteLocalRef(jstrAccountFrom);
		jniEnv->DeleteLocalRef(jstrAccountTo);
		jniEnv->DeleteLocalRef(roomObserverClass);
    }

    void CJNINativeRoomObserver::onHandStatus(std::string roomId, std::string accountFrom, std::string accountTo, bool status)
    {
		infof("====== onHandStatus, roomId: %s, accountFrom: %s, accountTo: %s, status: %s", roomId.c_str(), accountFrom.c_str(), accountTo.c_str(), status ? "on" : "off");
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass) {
            errorf ("FIND CLASS FAILED!!!");
            return ;
        }
        
        jmethodID onHandStatusID = jniEnv->GetMethodID(roomObserverClass, "onHandStatus", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");
        jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
		jstring jstrAccountFrom = jniEnv->NewStringUTF(accountFrom.c_str());
		jstring jstrAccountTo = jniEnv->NewStringUTF(accountTo.c_str());
		jniEnv->CallVoidMethod(m_jniRoomObserver, onHandStatusID, jstrRoomId, jstrAccountFrom, jstrAccountTo, status);
        jniEnv->DeleteLocalRef(jstrRoomId);
		jniEnv->DeleteLocalRef(jstrAccountFrom);
		jniEnv->DeleteLocalRef(jstrAccountTo);
        jniEnv->DeleteLocalRef(roomObserverClass);
	}

	void CJNINativeRoomObserver::onNotifyPartRoleChanged(std::string account, EnRoomRole presentRole)
	{
		int role = static_cast<int>(presentRole);
		infof("====== onNotifyPartRoleChanged, account: %s, presentRole: %d", account.c_str(), role);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass) {
			errorf("FIND CLASS FAILED!!!");
			return;
		}
		jmethodID onNotifyPartRoleChangedID = jniEnv->GetMethodID(roomObserverClass, "onNotifyPartRoleChanged", "(Ljava/lang/String;I)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jstring jstrAccount = jniEnv->NewStringUTF(account.c_str());

		jniEnv->CallVoidMethod(m_jniRoomObserver, onNotifyPartRoleChangedID, jstrAccount, role);

		jniEnv->DeleteLocalRef(jstrAccount);
	}

	void CJNINativeRoomObserver::onSetRollCallStatus(bool lectureStatus, std::string newLecturer, std::string oldLecturer)
	{
		infof("====== onSetRollCallStatus, lectureStatus: %d", lectureStatus);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass) {
			errorf("FIND CLASS FAILED!!!");
			return;
		}

		jmethodID onSetRollCallStatusID = jniEnv->GetMethodID(roomObserverClass, "onSetRollCallStatus", "(ZLjava/lang/String;Ljava/lang/String;)V");
		jstring jstrnewLecturer = jniEnv->NewStringUTF(newLecturer.c_str());
		jstring jstroldLecturer = jniEnv->NewStringUTF(oldLecturer.c_str());
		jniEnv->CallVoidMethod(m_jniRoomObserver, onSetRollCallStatusID, lectureStatus, jstrnewLecturer, jstroldLecturer);
		jniEnv->DeleteLocalRef(jstrnewLecturer);
		jniEnv->DeleteLocalRef(jstroldLecturer);
		jniEnv->DeleteLocalRef(roomObserverClass);
	}

    void CJNINativeRoomObserver::onSwitchVoiceModeNotify(std::string account, EnSwitch operation)
    {
        infof("====== onSwitchVoiceModeNotify, account: %s, operation: %d", account.c_str(), operation);
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass)
        {
            errorf("FIND CLASS FAILED!!!");
            return;
        }

        jmethodID onSwitchVoiceModeNotifyID = jniEnv->GetMethodID(roomObserverClass, "onSwitchVoiceModeNotify", "(Ljava/lang/String;I)V");
        jstring jstrAccount = jniEnv->NewStringUTF(account.c_str());
        jniEnv->CallVoidMethod(m_jniRoomObserver, onSwitchVoiceModeNotifyID, jstrAccount, operation);
        jniEnv->DeleteLocalRef(jstrAccount);
        jniEnv->DeleteLocalRef(roomObserverClass);
    }

    void CJNINativeRoomObserver::onDisconnect(std::string account)
    {
        infof("====== onDisconnect, account: %s", account.c_str());
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass) {
            errorf ("FIND CLASS FAILED!!!");
            return ;
        }
        
        jmethodID onDisconnectID = jniEnv->GetMethodID(roomObserverClass, "onDisconnect", "(Ljava/lang/String;)V");
        jstring jstrAccount = jniEnv->NewStringUTF(account.c_str());
        jniEnv->CallVoidMethod(m_jniRoomObserver, onDisconnectID, jstrAccount);
        jniEnv->DeleteLocalRef(jstrAccount);
        jniEnv->DeleteLocalRef(roomObserverClass);
    }

    void CJNINativeRoomObserver::onReconnect(std::string account)
    {
        infof("====== onReconnect, account: %s", account.c_str());
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass) {
            errorf ("FIND CLASS FAILED!!!");
            return ;
        }
        
        jmethodID onReconnectID = jniEnv->GetMethodID(roomObserverClass, "onReconnect", "(Ljava/lang/String;)V");
        jstring jstrAccount = jniEnv->NewStringUTF(account.c_str());
        jniEnv->CallVoidMethod(m_jniRoomObserver, onReconnectID, jstrAccount);
        jniEnv->DeleteLocalRef(jstrAccount);
        jniEnv->DeleteLocalRef(roomObserverClass);
    }

    void CJNINativeRoomObserver::onTempBroken(std::string account) 
    {
        infof("====== onTempBroken, account: %s", account.c_str());
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass) {
            errorf ("FIND CLASS FAILED!!!");
            return ;
        }
        
        jmethodID onTempBrokenID = jniEnv->GetMethodID(roomObserverClass, "onTempBroken", "(Ljava/lang/String;)V");
        jstring jstrAccount = jniEnv->NewStringUTF(account.c_str());
        jniEnv->CallVoidMethod(m_jniRoomObserver, onTempBrokenID, jstrAccount);
        jniEnv->DeleteLocalRef(jstrAccount);
        jniEnv->DeleteLocalRef(roomObserverClass);
    }

	void CJNINativeRoomObserver::onStartConferenceRecord(long long startRecordingTime)
	{
        infof("====== onStartConferenceRecord, startRecordingTime: %lld", startRecordingTime);
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass)
        {
            errorf("FIND CLASS FAILED!!!");
            return;
        }
        jmethodID onStartConferenceRecordID = jniEnv->GetMethodID(roomObserverClass, "onStartConferenceRecord", "(J)V");
        jniEnv->DeleteLocalRef(roomObserverClass);	

        jniEnv->CallVoidMethod(m_jniRoomObserver, onStartConferenceRecordID, startRecordingTime);
	}

    void CJNINativeRoomObserver::onStopConferenceRecord(bool isStoped, EnStopRecordReason reason)
    {
        infof("====== onStopConferenceRecord, isStoped:%s, reason:%d", isStoped ? "true" : "false", (int)reason);
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass)
        {
            errorf("FIND CLASS FAILED!!!");
            return;
        }

        jmethodID onStopConferenceRecordID = jniEnv->GetMethodID(roomObserverClass, "onStopConferenceRecord", "(ZI)V");
        jniEnv->CallVoidMethod(m_jniRoomObserver, onStopConferenceRecordID, isStoped, (int)reason);
        jniEnv->DeleteLocalRef(roomObserverClass);
    }

    void CJNINativeRoomObserver::onStartLive()
    {
        infof("====== onStartLive");
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass)
        {
            errorf("FIND CLASS FAILED!!!");
            return;
        }

        jmethodID onStartLiveID = jniEnv->GetMethodID(roomObserverClass, "onStartLive", "()V");
        jniEnv->CallVoidMethod(m_jniRoomObserver, onStartLiveID);
        jniEnv->DeleteLocalRef(roomObserverClass);
    }

    void CJNINativeRoomObserver::onStopLive()
    {
        infof("====== onStopLive");
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
        if (!roomObserverClass)
        {
            errorf("FIND CLASS FAILED!!!");
            return;
        }

        jmethodID onStopLiveID = jniEnv->GetMethodID(roomObserverClass, "onStopLive", "()V");
        jniEnv->CallVoidMethod(m_jniRoomObserver, onStopLiveID);
        jniEnv->DeleteLocalRef(roomObserverClass);
	}

	void CJNINativeRoomObserver::onUpdateParticipantsOrder(std::vector<StParticipantInfo> participantList)
	{
		infof("====== onUpdateParticipantsOrder, participants counts: %d", participantList.size());
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		// 获取roomObserver对象
		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("FIND CLASS FAILED!!!");
			return;
		}
#if 1
		// 调用参数为数组的java api
		jmethodID onUpdateParticipantsOrderID = jniEnv->GetMethodID(roomObserverClass, "onUpdateParticipantsOrder", "([Lcn/geedow/netprotocol/JNIStParticipantInfo;I)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jclass jniPartInfoClass = jniEnv->GetObjectClass(m_globalRef->getGlobalRef(STPARTICIPANTINFO_INFO_CLASS_NAME));
		if (!jniPartInfoClass) {
			errorf("FIND CLASS FAILED!!!");
			return;
		}
		jmethodID partInfoConstructorID = jniEnv->GetMethodID(jniPartInfoClass, "<init>", "()V");

		int localPartInfoListSize = participantList.size();
		infof("localPartInfoListSize:%d", localPartInfoListSize);

		jobjectArray jniPartInfoList = jniEnv->NewObjectArray(localPartInfoListSize, jniPartInfoClass, NULL);
		for (int i = 0; i < localPartInfoListSize; i++)
		{
			jobject joPartInfo = jniEnv->NewObject(jniPartInfoClass, partInfoConstructorID);

			JNICommon::setFieldValue(jniEnv, participantList[i], joPartInfo);

			jniEnv->SetObjectArrayElement(jniPartInfoList, i, joPartInfo);

			jniEnv->DeleteLocalRef(joPartInfo);
		}
		jniEnv->DeleteLocalRef(jniPartInfoClass);

		jniEnv->CallVoidMethod(m_jniRoomObserver, onUpdateParticipantsOrderID, jniPartInfoList, localPartInfoListSize);

		jniEnv->DeleteLocalRef(jniPartInfoList);
#else
		// 调用参数为ArrayList的java api
		debugf("[guol]");
		jmethodID onUpdateParticipantsOrderID = jniEnv->GetMethodID(roomObserverClass, "onUpdateParticipantsOrder", "(Ljava/util/ArrayList;)V");
		debugf("[guol]");
		jniEnv->DeleteLocalRef(roomObserverClass);

		debugf("[guol]");
		jclass jniArrayListClass = jniEnv->FindClass(JAVA_ARRAYLIST_NAME);
		debugf("[guol]");
		if (!jniArrayListClass)
		{
			errorf("FIND CLASS FAILED!!!");
			return;
		}
		jmethodID arrayListConstructorID = jniEnv->GetMethodID(jniArrayListClass, "<init>", "()V");
		jobject joArrayList = jniEnv->NewObject(jniArrayListClass, arrayListConstructorID);
		jniEnv->DeleteLocalRef(jniArrayListClass);

		//debugf("[guol]");
		//jclass jniPartInfoClass = jniEnv->GetObjectClass(m_globalRef->getGlobalRef(STPARTICIPANTINFO_INFO_CLASS_NAME));
		//if (!jniPartInfoClass) {
		//	errorf("FIND CLASS FAILED!!!");
		//	return;
		//}
		//debugf("[guol]");
		//jmethodID partInfoConstructorID = jniEnv->GetMethodID(jniPartInfoClass, "<init>", "()V");
		//jobject joPartInfo = jniEnv->NewObject(jniPartInfoClass, partInfoConstructorID);
		//debugf("[guol]");
		//jniEnv->DeleteLocalRef(jniPartInfoClass);

		////ANDROID_CONSOLE(1, "[guol]");
		//debugf("[guol]");
		//JNICommon::setFieldArrayValue(jniEnv, participantList, "", joArrayList, joPartInfo);

		//ANDROID_CONSOLE(1, "[guol]");
		debugf("[guol]");
		jniEnv->CallVoidMethod(m_jniRoomObserver, onUpdateParticipantsOrderID, joArrayList);
		//ANDROID_CONSOLE(1, "[guol]");
		debugf("[guol]");

		jniEnv->DeleteLocalRef(joArrayList);
		//ANDROID_CONSOLE(1, "[guol]");
		debugf("[guol]");
#endif

		infof("%s out <<<", __FUNCTION__);
	
	}

	void CJNINativeRoomObserver::onSetSpeakerPermission(std::string account, bool action)
	{
		infof("====== onSetSpeakerPermission, account: %s, action: %d", account.c_str(), (int)action);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		// 获取roomObserver对象
		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("FIND CLASS FAILED!!!");
			return;
		}

		jmethodID onSetSpeakerPermissionID = jniEnv->GetMethodID(roomObserverClass, "onSetSpeakerPermission", "(Ljava/lang/String;Z)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jstring jstrAccount = jniEnv->NewStringUTF(account.c_str());

		jniEnv->CallVoidMethod(m_jniRoomObserver, onSetSpeakerPermissionID, jstrAccount, action);

		jniEnv->DeleteLocalRef(jstrAccount);

		infof("%s out <<<", __FUNCTION__);
	}

	void CJNINativeRoomObserver::onMessage(std::string account, std::string nickname, EnMessageType msgType)
	{
		infof("====== onMessage, account: %s, msgType: %d", account.c_str(), msgType);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		// 获取roomObserver对象
		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("FIND CLASS FAILED!!!");
			return;
		}

		jmethodID onMessageID = jniEnv->GetMethodID(roomObserverClass, "onMessage", "(Ljava/lang/String;Ljava/lang/String;I)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jstring jstrAccount = jniEnv->NewStringUTF(account.c_str());
		jstring jstrNickname = jniEnv->NewStringUTF(nickname.c_str());

		jniEnv->CallVoidMethod(m_jniRoomObserver, onMessageID, jstrAccount, jstrNickname, (int)msgType);

		jniEnv->DeleteLocalRef(jstrAccount);
		jniEnv->DeleteLocalRef(jstrNickname);

		infof("%s out <<<", __FUNCTION__);
	}

	void CJNINativeRoomObserver::onSetPushStreamStatus(std::string roomId, std::string account, EnStreamType streamType, EnStreamStatus status)
	{
		infof("====== onSetPushStreamStatus, account: %s, streamType: %d, status: %d", account.c_str(), streamType, status);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		// 获取roomObserver对象
		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID onSetPushStreamStatusID = jniEnv->GetMethodID(roomObserverClass, "onSetPushStreamStatus", "(Ljava/lang/String;Ljava/lang/String;II)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
		jstring jstrAccount = jniEnv->NewStringUTF(account.c_str());

		jniEnv->CallVoidMethod(m_jniRoomObserver, onSetPushStreamStatusID, jstrRoomId, jstrAccount, (int)streamType, (int)status);

		jniEnv->DeleteLocalRef(jstrRoomId);
		jniEnv->DeleteLocalRef(jstrAccount);

		infof("%s out <<<", __FUNCTION__);
	}

	void CJNINativeRoomObserver::onSetPtzControlStatus(bool action, std::string serialNumber, StPtzControlParam param)
	{
		infof("====== onSetPtzControlStatus, method: %s, serialNumber: %s, operationCode: %d, duration: %d",
			action ? "startPtzControlNotify" : "stopPtzControlNotify",
			serialNumber.c_str(), param.operation, param.maxDuration);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		// 获取roomObserver对象
		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID onSetPtzControlStatusID = jniEnv->GetMethodID(roomObserverClass, "onSetPtzControlStatus", "(ZLjava/lang/String;II)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jstring jstrSerialNumber = jniEnv->NewStringUTF(serialNumber.c_str());

		jniEnv->CallVoidMethod(m_jniRoomObserver, onSetPtzControlStatusID, action, jstrSerialNumber, param.operation, param.maxDuration);

		jniEnv->DeleteLocalRef(jstrSerialNumber);

		infof("%s out <<<", __FUNCTION__);
	}

	void CJNINativeRoomObserver::onAdjustResolution(std::string serialNumber, int resolution)
	{
		infof("====== onAdjustResolution, serialNumber: %s, resolution: %d", serialNumber.c_str(), resolution);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		// 获取roomObserver对象
		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID onAdjustResolutionID = jniEnv->GetMethodID(roomObserverClass, "onAdjustResolution", "(Ljava/lang/String;I)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jstring jstrSerialNumber = jniEnv->NewStringUTF(serialNumber.c_str());

		jniEnv->CallVoidMethod(m_jniRoomObserver, onAdjustResolutionID, jstrSerialNumber, resolution);

		jniEnv->DeleteLocalRef(jstrSerialNumber);

		infof("%s out <<<", __FUNCTION__);
	}

	void CJNINativeRoomObserver::onAdjustToPresetPosition(std::string serialNumber, int index, StPresetPositionConfigInfo configInfo)
	{
		infof("====== onAdjustToPresetPosition -> index[%d]", index);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID onAdjustToPresetPositionID = jniEnv->GetMethodID(roomObserverClass, "onAdjustToPresetPosition",
			"(Ljava/lang/String;ILcn/geedow/netprotocol/basicDataStructure/JNIPresetPositionConfigInfo;)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jclass presetPositionConfigInfoClass = jniEnv->GetObjectClass(m_globalRef->getGlobalRef(PRESET_POSITION_CONFIG_INFO_CLASS_NAME));
		if (!presetPositionConfigInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID presetPositionConfigInfoConstructorID = jniEnv->GetMethodID(presetPositionConfigInfoClass, "<init>", "()V");
		jobject joConfigInfo = jniEnv->NewObject(presetPositionConfigInfoClass, presetPositionConfigInfoConstructorID);
		JNICommon::setFieldValue(jniEnv, configInfo, joConfigInfo);
		jniEnv->DeleteLocalRef(presetPositionConfigInfoClass);

		jstring jstrSerialNumber = (jstring)jniEnv->NewStringUTF(serialNumber.c_str());

		jniEnv->CallVoidMethod(m_jniRoomObserver, onAdjustToPresetPositionID, jstrSerialNumber, index, joConfigInfo);

		jniEnv->DeleteLocalRef(jstrSerialNumber);
		jniEnv->DeleteLocalRef(joConfigInfo);

		infof("%s out <<<", __FUNCTION__);
	}

	void CJNINativeRoomObserver::onSetPollingStatus(std::string roomId, bool status, int timeInterval)
	{
		infof("====== onSetPollingStatus -> roomId[%s] timeInterval[%d]", roomId.c_str(), timeInterval);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID onSetPollingStatusID = jniEnv->GetMethodID(roomObserverClass, "onSetPollingStatus",
			"(Ljava/lang/String;ZI)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jstring jstrRoomId = (jstring)jniEnv->NewStringUTF(roomId.c_str());

		jniEnv->CallVoidMethod(m_jniRoomObserver, onSetPollingStatusID, jstrRoomId, status, timeInterval);

		jniEnv->DeleteLocalRef(jstrRoomId);
	}

	void CJNINativeRoomObserver::onPollingNotify(EnPollingNotify pollingNotify, std::string account)
	{
		infof("====== onPollingNotify -> pollingNotify[%d] account[%s]", (int)pollingNotify, account.c_str());
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID onPollingNotifyID = jniEnv->GetMethodID(roomObserverClass, "onPollingNotify",
			"(ILjava/lang/String;)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jstring jstrAccount = (jstring)jniEnv->NewStringUTF(account.c_str());

		jniEnv->CallVoidMethod(m_jniRoomObserver, onPollingNotifyID, (int)pollingNotify, jstrAccount);

		jniEnv->DeleteLocalRef(jstrAccount);
	}

	void CJNINativeRoomObserver::onRoomAutoProlong(std::string roomId, std::string ruid)
	{
		infof("====== %s ", __FUNCTION__);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID callbackID = jniEnv->GetMethodID(roomObserverClass, "onRoomAutoProlong", "(Ljava/lang/String;Ljava/lang/String;)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jstring jstrRoomId = (jstring)jniEnv->NewStringUTF(roomId.c_str());
		jstring jstrRuid = (jstring)jniEnv->NewStringUTF(ruid.c_str());

		jniEnv->CallVoidMethod(m_jniRoomObserver, callbackID, jstrRoomId, jstrRuid);

		jniEnv->DeleteLocalRef(jstrRoomId);
		jniEnv->DeleteLocalRef(jstrRuid);
	}

	void CJNINativeRoomObserver::onUploadMeetingQuality(std::string roomId)
	{
		infof("====== %s ", __FUNCTION__);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID callbackID = jniEnv->GetMethodID(roomObserverClass, "onUploadMeetingQuality", "(Ljava/lang/String;)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jstring jstrRoomId = (jstring)jniEnv->NewStringUTF(roomId.c_str());

		jniEnv->CallVoidMethod(m_jniRoomObserver, callbackID, jstrRoomId);

		jniEnv->DeleteLocalRef(jstrRoomId);
	}

	void CJNINativeRoomObserver::onScrollBarrage(std::string roomId, bool status, StBarrage barrage)
	{
		infof("====== %s ", __FUNCTION__);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID callbackID = jniEnv->GetMethodID(roomObserverClass, "onScrollBarrage", 
			"(Ljava/lang/String;ZLcn/geedow/netprotocol/basicDataStructure/JNIBarrage;)V");
		jniEnv->DeleteLocalRef(roomObserverClass);
		
		jclass jniBarrageClass = jniEnv->GetObjectClass(m_globalRef->getGlobalRef(BARRAGE_CLASS_NAME));
		if (!jniBarrageClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID barrageConstructorID = jniEnv->GetMethodID(jniBarrageClass, "<init>", "()V");
		jobject joBarrage = jniEnv->NewObject(jniBarrageClass, barrageConstructorID);
		jniEnv->DeleteLocalRef(jniBarrageClass);

		JNICommon::setFieldValue(jniEnv, barrage, joBarrage);
		jstring jstrRoomId = (jstring)jniEnv->NewStringUTF(roomId.c_str());

		jniEnv->CallVoidMethod(m_jniRoomObserver, callbackID, jstrRoomId, status, joBarrage);

		jniEnv->DeleteLocalRef(jstrRoomId);
		jniEnv->DeleteLocalRef(joBarrage);
	}

	void CJNINativeRoomObserver::onIMMessage(std::string roomId, StIMMessage message)
	{
		infof("====== %s ", __FUNCTION__);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID callbackID = jniEnv->GetMethodID(roomObserverClass, "onIMMessage",
			"(Ljava/lang/String;Lcn/geedow/netprotocol/basicDataStructure/JNIIMMessage;)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jclass jniIMMessageClass = jniEnv->GetObjectClass(m_globalRef->getGlobalRef(IM_MESSAGE_CLASS_NAME));
		if (!jniIMMessageClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID IMMessageConstructorID = jniEnv->GetMethodID(jniIMMessageClass, "<init>", "()V");
		jobject joIMMessage = jniEnv->NewObject(jniIMMessageClass, IMMessageConstructorID);
		jniEnv->DeleteLocalRef(jniIMMessageClass);

		JNICommon::setFieldValue(jniEnv, message, joIMMessage);
		jstring jstrRoomId = (jstring)jniEnv->NewStringUTF(roomId.c_str());

		jniEnv->CallVoidMethod(m_jniRoomObserver, callbackID, jstrRoomId, joIMMessage);

		jniEnv->DeleteLocalRef(jstrRoomId);
		jniEnv->DeleteLocalRef(joIMMessage);
	}

	void CJNINativeRoomObserver::onIMPermission(std::string roomId, EnIMPermission permission)
	{
		infof("====== %s ", __FUNCTION__);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID callbackID = jniEnv->GetMethodID(roomObserverClass, "onIMPermission",
			"(Ljava/lang/String;I)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jstring jstrRoomId = (jstring)jniEnv->NewStringUTF(roomId.c_str());

		jniEnv->CallVoidMethod(m_jniRoomObserver, callbackID, jstrRoomId, static_cast<int>(permission));

		jniEnv->DeleteLocalRef(jstrRoomId);
	}

	void CJNINativeRoomObserver::onCountDown(std::string roomId, std::string subject, std::string creator, long long startTime, int minutesAheadOfSchedule)
	{
		infof("====== %s ", __FUNCTION__);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID callbackID = jniEnv->GetMethodID(roomObserverClass, "onCountDown",
			"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;JI)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jstring jstrRoomId = (jstring)jniEnv->NewStringUTF(roomId.c_str());
		jstring jstrSubject = (jstring)jniEnv->NewStringUTF(subject.c_str());
		jstring jstrCreator = (jstring)jniEnv->NewStringUTF(creator.c_str());

		jniEnv->CallVoidMethod(m_jniRoomObserver, callbackID, jstrRoomId, jstrSubject, jstrCreator, startTime, minutesAheadOfSchedule);

		jniEnv->DeleteLocalRef(jstrRoomId);
		jniEnv->DeleteLocalRef(jstrSubject);
		jniEnv->DeleteLocalRef(jstrCreator);
	}

	void CJNINativeRoomObserver::onMediaModeChanged(EnMediaMode mediaMode)
	{
		infof("====== %s ", __FUNCTION__);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID callbackID = jniEnv->GetMethodID(roomObserverClass, "onMediaModeChanged",
			"(I)V");
		jniEnv->DeleteLocalRef(roomObserverClass);
		
		jniEnv->CallVoidMethod(m_jniRoomObserver, callbackID, static_cast<int>(mediaMode));
	}

	void CJNINativeRoomObserver::onMeetingLayoutChanged(std::vector<StView> streamLayoutList)
	{
		infof("====== %s ", __FUNCTION__);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID callbackID = jniEnv->GetMethodID(roomObserverClass, "onMeetingLayoutChanged",
			"([Lcn/geedow/netprotocol/basicDataStructure/JNIView;I)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jclass jniViewClass = jniEnv->GetObjectClass(m_globalRef->getGlobalRef(VIEW_CLASS_NAME));
		if (!jniViewClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID constructorID = jniEnv->GetMethodID(jniViewClass, "<init>", "()V");

		int size = streamLayoutList.size();
		jobjectArray jniViewList = jniEnv->NewObjectArray(size, jniViewClass, NULL);
		for (int i = 0; i < size; i++)
		{
			jobject joView = jniEnv->NewObject(jniViewClass, constructorID);

			JNICommon::setFieldValue(jniEnv, streamLayoutList[i], joView);

			jniEnv->SetObjectArrayElement(jniViewList, i, joView);

			jniEnv->DeleteLocalRef(joView);
		}
		jniEnv->DeleteLocalRef(jniViewClass);

		jniEnv->CallVoidMethod(m_jniRoomObserver, callbackID, jniViewList, size);

		jniEnv->DeleteLocalRef(jniViewList);
	}

	void CJNINativeRoomObserver::onNumberOfParticipantChanged(int numberOfParticipant)
	{
		infof("====== %s ", __FUNCTION__);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass roomObserverClass = jniEnv->GetObjectClass(m_jniRoomObserver);
		if (!roomObserverClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID callbackID = jniEnv->GetMethodID(roomObserverClass, "onNumberOfParticipantChanged",
			"(I)V");
		jniEnv->DeleteLocalRef(roomObserverClass);

		jniEnv->CallVoidMethod(m_jniRoomObserver, callbackID, numberOfParticipant);

	}

    void CJNINativeRoomObserver::setJNIJavaRoomObserver(jobject jniRoomObserver)
    {
        m_jniRoomObserver = jniRoomObserver;
    }

	void CJNINativeRoomObserver::setGlobalRef(JNICustomGlobalRef * globalRef)
	{
		if (globalRef == NULL)
		{
			errorf("Global reference is NULL.");
			return;
		}
		m_globalRef = globalRef;
	}

}
