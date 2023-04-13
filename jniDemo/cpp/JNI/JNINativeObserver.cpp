#include "JNINativeObserver.h"
#include "jvm.h"

#include "SDNPLogger.h"
#include "JNICommon.h"

namespace SDNP
{

	CJNINativeObserver::CJNINativeObserver()
	{

	}

	CJNINativeObserver::~CJNINativeObserver()
	{
		debugf("~CJNINativeObserver() ");
	}

	EnDeviceNetState CJNINativeObserver::onFetchDeviceNetState() {
		infof("====== onFetchDeviceNetState >>>");
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return EnDeviceNetState(0);
		}

		jmethodID onFetchDeviceNetStateID = jniEnv->GetMethodID(observerClass, "onFetchDeviceNetState", "()I");
		int ret = jniEnv->CallIntMethod(m_jniJavaObserver, onFetchDeviceNetStateID);
		jniEnv->DeleteLocalRef(observerClass);
		infof("====== onFetchDeviceNetState <<<");
		return EnDeviceNetState(ret);
	}




	void CJNINativeObserver::onTokenBecameInvalid()
	{
		infof("====== onTokenBecameInvalid >>>");
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}

		jmethodID onTokenBecameInvalidID = jniEnv->GetMethodID(observerClass, "onTokenBecameInvalid", "()V");
		jniEnv->CallVoidMethod(m_jniJavaObserver, onTokenBecameInvalidID);
		jniEnv->DeleteLocalRef(observerClass);
		infof("====== onTokenBecameInvalid <<<");
	}


	void CJNINativeObserver::onOthersLogin()
	{
		infof("====== onOthersLogin >>>");
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}

		jmethodID onOthersLoginID = jniEnv->GetMethodID(observerClass, "onOthersLogin", "()V");
		jniEnv->CallVoidMethod(m_jniJavaObserver, onOthersLoginID);
		jniEnv->DeleteLocalRef(observerClass);
		infof("====== onOthersLogin <<<");
	}

	void CJNINativeObserver::onServiceAvailableChange(bool state, int code, std::string message)
	{
		infof("====== onServiceAvailableChange -> [%d]", state);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();
		infof("%s %d jniEnv:%p", __FUNCTION__, __LINE__, jniEnv);

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jstring jstrMessage = jniEnv->NewStringUTF(message.c_str());
		jmethodID onServiceAvailableChangeID = jniEnv->GetMethodID(observerClass, "onServiceAvailableChange", "(ZILjava/lang/String;)V");
		jniEnv->CallVoidMethod(m_jniJavaObserver, onServiceAvailableChangeID, state, code, jstrMessage);
		jniEnv->DeleteLocalRef(jstrMessage);
		jniEnv->DeleteLocalRef(observerClass);
	}

	void CJNINativeObserver::onNetworkConnectStatusChange(EnNetState state, int code, std::string message)
	{
		infof("====== onNetworkConnectStatusChange -> [%d]", state);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();
		infof("%s %d jniEnv:%p", __FUNCTION__, __LINE__, jniEnv);

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}

		jstring jstrMessage = jniEnv->NewStringUTF(message.c_str());

		jmethodID onNetworkConnectStatusChangeID = jniEnv->GetMethodID(observerClass, "onNetworkConnectStatusChange", "(IILjava/lang/String;)V");
		jniEnv->CallVoidMethod(m_jniJavaObserver, onNetworkConnectStatusChangeID, (int)state, code, jstrMessage);
		jniEnv->DeleteLocalRef(jstrMessage);
		jniEnv->DeleteLocalRef(observerClass);

	}

	void CJNINativeObserver::onOnlineStateChange(bool online)
	{
		infof("====== onOnlineStateChange -> [%s]", online ? "online" : "offline");
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();
		infof("%s %d jniEnv:%p", __FUNCTION__, __LINE__, jniEnv);

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}

		jmethodID onOnlineStateChangeID = jniEnv->GetMethodID(observerClass, "onOnlineStateChange", "(Z)V");
		jniEnv->CallVoidMethod(m_jniJavaObserver, onOnlineStateChangeID, online);
		jniEnv->DeleteLocalRef(observerClass);
	}


	void CJNINativeObserver::onVersionUpgrade(bool foreStatus, std::string downLoadUrl, std::string version, std::string details)
	{
		infof("====== onVersionUpgrade -> [%s]", foreStatus ? "true" : "false");
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();
		infof("%s %d jniEnv:%p", __FUNCTION__, __LINE__, jniEnv);

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}

		jstring jstrDownLoadUrl = jniEnv->NewStringUTF(downLoadUrl.c_str());
		jstring jstrVersion = jniEnv->NewStringUTF(version.c_str());
		jstring jstrDetails = jniEnv->NewStringUTF(downLoadUrl.c_str());
		jmethodID onVersionUpgradeID = jniEnv->GetMethodID(observerClass, "onVersionUpgrade", "(ZLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		jniEnv->CallVoidMethod(m_jniJavaObserver, onVersionUpgradeID, foreStatus, jstrDownLoadUrl, jstrVersion, jstrDetails);
		jniEnv->DeleteLocalRef(jstrDownLoadUrl);
		jniEnv->DeleteLocalRef(jstrVersion);
		jniEnv->DeleteLocalRef(jstrDetails);
		jniEnv->DeleteLocalRef(observerClass);
	}

	void SDNP::CJNINativeObserver::onVersionUpgrade(std::string serialNumber, bool foreStatus, std::string downLoadUrl, std::string version, std::string details)
	{
		infof("====== onVersionUpgrade -> [%s]", foreStatus ? "true" : "false");
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();
		infof("%s %d jniEnv:%p", __FUNCTION__, __LINE__, jniEnv);

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}

		jstring jstrSerialNumber = jniEnv->NewStringUTF(serialNumber.c_str());
		jstring jstrDownLoadUrl = jniEnv->NewStringUTF(downLoadUrl.c_str());
		jstring jstrVersion = jniEnv->NewStringUTF(version.c_str());
		jstring jstrDetails = jniEnv->NewStringUTF(downLoadUrl.c_str());
		jmethodID onVersionUpgradeID = jniEnv->GetMethodID(observerClass, "onVersionUpgrade", 
			"(Ljava/lang/String;ZLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		jniEnv->CallVoidMethod(m_jniJavaObserver, onVersionUpgradeID, jstrSerialNumber, foreStatus, jstrDownLoadUrl, jstrVersion, jstrDetails);
		jniEnv->DeleteLocalRef(jstrSerialNumber);
		jniEnv->DeleteLocalRef(jstrDownLoadUrl);
		jniEnv->DeleteLocalRef(jstrVersion);
		jniEnv->DeleteLocalRef(jstrDetails);
		jniEnv->DeleteLocalRef(observerClass);
	}

	void CJNINativeObserver::onPushLog(PushLogStrategy strategy)
	{
		infof("====== onPushLog");
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}

		jmethodID onPushLogID = jniEnv->GetMethodID(observerClass, "onPushLog", "()V");
		jniEnv->CallVoidMethod(m_jniJavaObserver, onPushLogID);
		jniEnv->DeleteLocalRef(observerClass);
	}

	void CJNINativeObserver::onPushLogResult(bool result)
	{
		infof("====== onPushLogResult -> [%s]", result ? "true" : "false");
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}

		jmethodID onPushLogResultID = jniEnv->GetMethodID(observerClass, "onPushLogResult", "(Z)V");
		jniEnv->CallVoidMethod(m_jniJavaObserver, onPushLogResultID, result);
		jniEnv->DeleteLocalRef(observerClass);
	}

	void CJNINativeObserver::onServiceExpired(bool isExpired, std::string expiredDate, int daysToExpiredDate)
	{
		infof("====== onServiceExpired -> [%s]", isExpired ? "true" : "false");
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}

		jstring jstrExpiredDate = jniEnv->NewStringUTF(expiredDate.c_str());

		jmethodID onServiceExpiredID = jniEnv->GetMethodID(observerClass, "onServiceExpired", "(ZLjava/lang/String;I)V");
		jniEnv->CallVoidMethod(m_jniJavaObserver, onServiceExpiredID, isExpired, jstrExpiredDate, daysToExpiredDate);

		jniEnv->DeleteLocalRef(jstrExpiredDate);
		jniEnv->DeleteLocalRef(observerClass);
	}

	void CJNINativeObserver::onConversationDurationStatus(EnConversationDuration duration, int hours, int minutes)
	{
		infof("====== onConversationDurationStatus -> [%d]", static_cast<int>(duration));
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}

		jmethodID callbackID = jniEnv->GetMethodID(observerClass, "onConversationDurationStatus", "(III)V");
		jniEnv->CallVoidMethod(m_jniJavaObserver, callbackID, static_cast<int>(duration), hours, minutes);

		jniEnv->DeleteLocalRef(observerClass);
	}
	
	void CJNINativeObserver::onTimeSynchronization(long long serverTimestamp)
	{
		infof("====== onTimeSynchronization -> [%lld]", serverTimestamp);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID callbackID = jniEnv->GetMethodID(observerClass, "onTimeSynchronization", "(J)V");
		jniEnv->DeleteLocalRef(observerClass);

		jniEnv->CallVoidMethod(m_jniJavaObserver, callbackID, serverTimestamp);
	}

	void CJNINativeObserver::onEvictedByCorp()
	{
		infof("====== onEvictedByCorp");
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID callbackID = jniEnv->GetMethodID(observerClass, "onEvictedByCorp", "()V");
		jniEnv->DeleteLocalRef(observerClass);

		jniEnv->CallVoidMethod(m_jniJavaObserver, callbackID);
	}

	void CJNINativeObserver::onHardTerminalDeviceInfoChanged(StHardTerminalDeviceInfo deviceInfo)
	{
		infof("====== onHardTerminalDeviceInfoChanged -> [%s]", deviceInfo.nickName.c_str());
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID callbackID = jniEnv->GetMethodID(observerClass, 
			"onHardTerminalDeviceInfoChanged", "(Lcn/geedow/netprotocol/basicDataStructure/JNIHardTerminalDeviceInfo;)V");
		jniEnv->DeleteLocalRef(observerClass);

		jclass jniDeviceInfoClass = jniEnv->GetObjectClass(m_globalRef->getGlobalRef(HARD_TERMINAL_DEVICE_INFO_CLASS_NAME));
		if (!jniDeviceInfoClass) {
			errorf("FIND CLASS FAILED!!!");
			return;
		}
		jmethodID constructorID = jniEnv->GetMethodID(jniDeviceInfoClass, "<init>", "()V");
		jobject joDeviceInfo = jniEnv->NewObject(jniDeviceInfoClass, constructorID);
		jniEnv->DeleteLocalRef(jniDeviceInfoClass);

		JNICommon::setFieldValue(jniEnv, deviceInfo, joDeviceInfo);

		jniEnv->CallVoidMethod(m_jniJavaObserver, callbackID, joDeviceInfo);

		jniEnv->DeleteLocalRef(joDeviceInfo);
	}

	void CJNINativeObserver::onConferenceToBegin(std::string username, std::string subject, long long startTime, long long endTime)
	{
        infof("====== onConferenceToBegin, startTime: %lld, endTime: %lld", startTime, endTime);
        JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

        jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
        if (!observerClass) {
            errorf ("FIND CLASS FAILED!!!");
            return ;
        }        
		jmethodID onConferenceToBeginID = jniEnv->GetMethodID(observerClass, 
			"onConferenceToBegin", 
			"(Ljava/lang/String;Ljava/lang/String;JJ)V");
        jniEnv->DeleteLocalRef(observerClass);

		jstring jstrUsername = jniEnv->NewStringUTF(username.c_str());
        jstring jstrSubject = jniEnv->NewStringUTF(subject.c_str());

        jniEnv->CallVoidMethod(m_jniJavaObserver, onConferenceToBeginID, jstrUsername, jstrSubject, startTime, endTime);

        jniEnv->DeleteLocalRef(jstrUsername);
        jniEnv->DeleteLocalRef(jstrSubject);
	}

	void CJNINativeObserver::onConferenceCreated(std::string username, std::string subject, long long startTime, long long endTime)
	{
		infof("====== onConferenceCreated, startTime: %lld, endTime: %lld", startTime, endTime);
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID onConferenceCreatedID = jniEnv->GetMethodID(observerClass, 
			"onConferenceCreated", 
			"(Ljava/lang/String;Ljava/lang/String;JJ)V");
		jniEnv->DeleteLocalRef(observerClass);

		jstring jstrUsername = jniEnv->NewStringUTF(username.c_str());
		jstring jstrSubject = jniEnv->NewStringUTF(subject.c_str());
		
		jniEnv->CallVoidMethod(m_jniJavaObserver, onConferenceCreatedID, jstrUsername, jstrSubject, startTime, endTime);

		jniEnv->DeleteLocalRef(jstrUsername);
		jniEnv->DeleteLocalRef(jstrSubject);		
	}

	void CJNINativeObserver::onConferenceCanceled(std::string roomId, std::string ruid, std::string subject, EnConferenceCanceledReason reason)
	{
		infof("====== onConferenceCanceled, roomId: %s, reason: %d", roomId.c_str(), static_cast<int>(reason));
		JNIEnv *jniEnv = AttachCurrentThreadIfNeeded();

		jclass observerClass = jniEnv->GetObjectClass(m_jniJavaObserver);
		if (!observerClass) {
			errorf("GET OBJECT CLASS FAILED!!!");
			return;
		}
		jmethodID onConferenceCanceledID = jniEnv->GetMethodID(observerClass, "onConferenceCanceled", 
			"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V");
		jniEnv->DeleteLocalRef(observerClass);

		jstring jstrRoomId = jniEnv->NewStringUTF(roomId.c_str());
		jstring jstrRuid = jniEnv->NewStringUTF(ruid.c_str());
		jstring jstrSubject = jniEnv->NewStringUTF(subject.c_str());

		jniEnv->CallVoidMethod(m_jniJavaObserver, onConferenceCanceledID, jstrRoomId, jstrRuid, jstrSubject, static_cast<int>(reason));

		jniEnv->DeleteLocalRef(jstrRoomId);
		jniEnv->DeleteLocalRef(jstrRuid);
		jniEnv->DeleteLocalRef(jstrSubject);
	}

	void CJNINativeObserver::setJNIJavaObserver(jobject& observer)
	{
		m_jniJavaObserver = observer;
	}

	void CJNINativeObserver::setGlobalRef(JNICustomGlobalRef * globalRef)
	{
		if (globalRef == NULL)
		{
			errorf("Global reference is NULL.");
			return;
		}
		m_globalRef = globalRef;
	}

}   // end namespace SDP
