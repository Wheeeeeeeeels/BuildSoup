#ifndef __JNI_COMMON_H__
#define __JNI_COMMON_H__

#include <jni.h>
#include <type_traits>
#include "INetProtocol.h"
#include "IProjection.h"
#include "SDNPLogger.h"

namespace SDNP
{

//// JNI common type sign
#define JNI_jboolean_SIGN "Z"
#define JNI_jbyte_SIGN "B"
#define JNI_jchar_SIGN "C"
#define JNI_jshort_SIGN "S"
#define JNI_jint_SIGN "I"
#define JNI_jlong_SIGN "J"
#define JNI_jfloat_SIGN "F"
#define JNI_jdouble_SIGN "D"
#define JNI_jstring_SIGN "Ljava/lang/String;"

//// Java primitive class name
#define JAVA_ARRAYLIST_NAME "java/util/ArrayList"
#define JAVA_ARRAYLIST_SIGN "Ljava/util/ArrayList;"
#define JAVA_INTEGER_NAME "java/lang/Integer"
#define JAVA_INTEGER_SIGN "Ljava/lang/Integer;"
#define JAVA_LONG_NAME "java/lang/Long"
#define JAVA_LONG_SIGN "Ljava/lang/Long;"

//// Java project
#define PROJECTION_INFO_NAME "cn/geedow/netprotocol/projection/JNIProjectionInfo"
#define PROJECTION_INFO_SIGN "Lcn/geedow/netprotocol/projection/JNIProjectionInfo;"

//// Java base data structure class name & signture
#define BASE_ACCOUNT_INFO_CLASS_NAME ""
#define BASE_ACCOUNT_INFO_CLASS_SIGH ""
#define BASE_DATA_PAGE_INFO_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIDataPageInfo"
#define BASE_DATA_PAGE_INFO_CLASS_SIGH "Lcn/geedow/netprotocol/basicDataStructure/JNIDataPageInfo;"
#define BASE_MEETING_ROOM_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIMeetingRoom"
#define BASE_MEETING_ROOM_CLASS_SIGH "Lcn/geedow/netprotocol/basicDataStructure/JNIMeetingRoom;"
#define BASE_GROUP_INFO_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIGroupInfo"
#define BASE_GROUP_INFO_CLASS_SIGH "Lcn/geedow/netprotocol/basicDataStructure/JNIGroupInfo;"
#define MEDIA_CONTROL_PARAM_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIMediaControlParam"
#define MEDIA_CONTROL_PARAM_CLASS_SIGH "Lcn/geedow/netprotocol/basicDataStructure/JNIMediaControlParam;"
#define PTZ_CONTROL_PARAM_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIPtzControlParam"
#define PTZ_CONTROL_PARAM_CLASS_SIGH "Lcn/geedow/netprotocol/basicDataStructure/JNIPtzControlParam;"
#define PRESET_POSITION_CONFIG_INFO_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIPresetPositionConfigInfo"
#define PRESET_POSITION_CONFIG_INFO_CLASS_SIGH "Lcn/geedow/netprotocol/basicDataStructure/JNIPresetPositionConfigInfo;"
#define COMPANY_INFO_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNICompanyInfo"
#define COMPANY_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNICompanyInfo;"
#define ICE_SERVER_INFO_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIIceServerInfo"
#define ICE_SERVER_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNIIceServerInfo;"
#define TERMINAL_LOCAL_INFO_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNITerminalLocalInfo"
#define TERMINAL_LOCAL_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNITerminalLocalInfo;"
#define NETWORK_QUALITY_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNINetworkQuality"
#define NETWORK_QUALITY_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNINetworkQuality;"
#define STREAM_QUALITY_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIStreamQuality"
#define STREAM_QUALITY_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNIStreamQuality;"
#define JOINROOM_PARAM_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNiJoinRoomParam"
#define JOINROOM_PARAM_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNiJoinRoomParam;"
#define BARRAGE_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIBarrage"
#define BARRAGE_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNIBarrage;"
#define IM_MESSAGE_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIIMMessage"
#define IM_MESSAGE_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNIIMMessage;"
#define DEVICE_INFO_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIDeviceInfo"
#define DEVICE_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNIDeviceInfo;"
#define ACCOUNT_INFO_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIAccountInfo"
#define ACCOUNT_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNIAccountInfo;"
#define USER_INFO_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIUserInfo"
#define USER_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNIUserInfo;"
#define PUSHED_MSG_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIPushedMsg"
#define PUSHED_MSG_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNIPushedMsg;"
#define HARD_TERMINAL_DEVICE_INFO_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIHardTerminalDeviceInfo"
#define HARD_TERMINAL_DEVICE_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNIHardTerminalDeviceInfo;"
#define BASE_ALL_MEETING_ROOMS_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIAllMeetingRooms"
#define BASE_ALL_MEETING_ROOMS_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNIAllMeetingRooms;"
#define STAPPOINT_CONFERENCE_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIStAppointConference"
#define STAPPOINT_CONFERENCE_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNIStAppointConference;"
#define RECT_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIRect"
#define RECT_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNIRect;"
#define VIEW_CLASS_NAME "cn/geedow/netprotocol/basicDataStructure/JNIView"
#define VIEW_CLASS_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNIView;"
#define CALLEE_INFO_NAME "cn/geedow/netprotocol/basicDataStructure/JNICalleeInfo"
#define CALLEE_INFO_SIGN "Lcn/geedow/netprotocol/basicDataStructure/JNICalleeInfo;"

//// Java class name
#define Subscribe_Stream_Param_CLASS_NAME "cn/geedow/netprotocol/JNISubscribeStreamParam"
#define Subscribe_Stream_Param_CLASS_SIGN "Lcn/geedow/netprotocol/JNISubscribeStreamParam;"
#define Subscribe_Stream_Response_CLASS_NAME "cn/geedow/netprotocol/JNISubscribeStreamResponse"
#define Subscribe_Stream_Response_CLASS_SIGN "Lcn/geedow/netprotocol/JNISubscribeStreamResponse;"


#define COMM_TYPE_CLASS_NAME "cn/geedow/netprotocol/JNICommType"
#define COMM_TYPE_CLASS_SIGN "Lcn/geedow/netprotocol/JNICommType;"
#define BASIC_INFO_CLASS_NAME "cn/geedow/netprotocol/JNIBasicInfo"
#define BASIC_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/JNIBasicInfo;"
#define SERVER_INFO_CLASS_NAME "cn/geedow/netprotocol/JNIServerInfo"
#define SERVER_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/JNIServerInfo;"
#define STREAM_INFO_CLASS_NAME "cn/geedow/netprotocol/JNIStreamInfo"
#define STREAM_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/JNIStreamInfo;"
#define ORG_INFO_CLASS_NAME "cn/geedow/netprotocol/JNIOrgInfo"
#define ORG_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/JNIOrgInfo;"
#define CONFERENCE_SUMMARY_CLASS_NAME "cn/geedow/netprotocol/JNIConferenceSummary"
#define CONFERENCE_SUMMARY_CLASS_SIGN "[Lcn/geedow/netprotocol/JNIConferenceSummary;"
#define ORG_MEMBER_INFO_CLASS_NAME "cn/geedow/netprotocol/JNIOrgMemberInfo"
#define ORG_MEMBER_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/JNIOrgMemberInfo;"
#define H5_PAGE_INFO_CLASS_NAME "cn/geedow/netprotocol/JNIH5PageInfo"
#define H5_PAGE_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/JNIH5PageInfo;"

#define STSTREAM_INFO_CLASS_NAME "cn/geedow/netprotocol/JNIStStreamInfo"
#define STSTREAM_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/JNIStStreamInfo;"
#define STMEETING_INFO_CLASS_NAME "cn/geedow/netprotocol/JNIStMeeting"
#define STMEETING_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/JNIStMeeting;"
#define STPARTICIPANTINFO_INFO_CLASS_NAME "cn/geedow/netprotocol/JNIStParticipantInfo"
#define STPARTICIPANTINFO_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/JNIStParticipantInfo;"

#define APPOINT_PARTICIPANT_INFO_CLASS_NAME "cn/geedow/netprotocol/JNIAppointParticipantInfo"
#define APPOINT_PARTICIPANT_INFO_CLASS_SIGN "[Lcn/geedow/netprotocol/JNIAppointParticipantInfo;"
#define PERSONAL_CONF_ROOM_INFO_CLASS_NAME "cn/geedow/netprotocol/JNIConfRoomInfo"
#define PERSONAL_CONF_ROOM_INFO_CLASS_SIGN "Lcn/geedow/netprotocol/JNIConfRoomInfo;"

#define CONFERENCE_RECORD_CLASS_NAME "cn/geedow/netprotocol/JNIConferenceRecordInfo"
#define CONFERENCE_RECORD_CLASS_SIGN "Lcn/geedow/netprotocol/JNIConferenceRecordInfo;"
#define CONFERENCE_LAYOUT_CLASS_NAME "cn/geedow/netprotocol/JNIRoomInfo$JNIConferenceLayout"
#define CONFERENCE_LAYOUT_CLASS_SIGN "Lcn/geedow/netprotocol/JNIRoomInfo$JNIConferenceLayout;"

	/**
	 * setFieldValue: set the value of java object
	 * getFieldValue: get the value of java object
	 */
	class JNICommon
	{
	public:
		static int setFieldValueTest(JNIEnv *env, OrgMemberInfo cppMemberInfo, jobject &joMemberInfo);

		static int addEleIntoArrayList(JNIEnv *env, jobject &joArrayList, jobject joEle);

		// std::vector<T> <-> ArrayList<java.lang.Integer>
		template <typename T>
		static int getIntFieldValue(JNIEnv *env, jobject joIntegerList, std::vector<T> &cppIntList);
		template <typename T>
		static int setIntFieldValue(JNIEnv *env, std::vector<T> cppIntList, jobject &joIntegerList);

		template <typename T>
		static int getFieldArrayValue(JNIEnv *env, jobject joList, std::vector<T> &cppList);
		template <typename T>
		static int setFieldArrayValue(JNIEnv *env, std::vector<T> cppList, std::string elementName, jobject &joList, jobject joElement = nullptr);

		template <typename T>
		static int setCommonTypeValue(JNIEnv *env, T value, jobject &joCommonType);

		static std::string getJStringValue(JNIEnv *env, jstring jstr);
		static int setJStringValue(JNIEnv *env, std::string str, jstring &jstr);
		// ArrayList<String> -> std::vector<std::string>
		static int getFieldValue(JNIEnv *env, jobject joStringList, std::vector<std::string> &cppStringList);

		static int getFieldValue(JNIEnv *env, jobject joLong, long long &cppLong);

		static int getFieldValue(JNIEnv *env, jobject joProjectionInfo, StProjectionInfo &cppProjectionInfo);
		static int setFieldValue(JNIEnv *env, StProjectionInfo cppProjectionInfo, jobject &joProjectionInfo);

		// StPtzControlParam <-> cn.geedow.netprotocol.basicDataStructure.JNIPtzControlParam
		static int getFieldValue(JNIEnv *env, jobject joParam, StPtzControlParam &cppParam);
		static int setFieldValue(JNIEnv *env, StPtzControlParam cppParam, jobject &joParam);

		// StDataPageInfo <-> cn.geedow.netprotocol.basicDataStructure.JNIDataPageInfo
		static int getFieldValue(JNIEnv *env, jobject joPageInfoIn, StDataPageInfo &pageInfo);
		static int setFieldValue(JNIEnv *env, StDataPageInfo dataPageInfo, jobject &joPageInfoIn);

		// OrgMemberInfo <-> cn.geedow.netprotocol.JNIOrgMemberInfo
		static int getFieldValue(JNIEnv *env, jobject joMemberInfo, OrgMemberInfo &cppMemberInfo);
		static int setFieldValue(JNIEnv *env, OrgMemberInfo cppMemberInfo, jobject &joMemberInfo);

		static int getFieldValue(JNIEnv *env, jobject joConfLayout, StConferenceLayout &cppConfLayout);
		static int setFieldValue(JNIEnv *env, StConferenceLayout cppConfLayout, jobject &joConfLayout);
		// StMeeting -> cn.geedow.netprotocol.JNIStMeeting
		static int getFieldValue(JNIEnv *env, jobject joStMeeting, StMeeting &cppMeetingInfo);
		static int setFieldValue(JNIEnv *env, StMeeting cppMeetingInfo, jobject &joStMeeting);

		//StMeetingAttribute
		static int getFieldValue(JNIEnv *env, jobject joStMeetingAttribute, StMeetingAttribute &cppAttributeInfo);
		static int setFieldValue(JNIEnv *env, StMeetingAttribute cppAttributeInfo, jobject &joStMeetingAttribute);

		static int getFieldValue(JNIEnv *env, jobject joParam, StJoinRoomParam &cppParam);

		// std::vector<OrgMemberInfo> -> ArrayList<cn.geedow.netprotocol.JNIOrgMemberInfo>
		static int setFieldValue(JNIEnv *env, std::vector<OrgMemberInfo> memberList, jobject &joArrayList);

		static int getFieldValue(JNIEnv *env, jobject joMeetingRooms, StMeetingRoom &cppRoom);
		static int setFieldValue(JNIEnv *env, StMeetingRoom cppRoom, jobject &joMeetingRooms);

		static int setFieldValue(JNIEnv *env, StAllMeetingRooms cppRooms, jobject &joMeetingRooms);

		// std::vector<OrgInfo> -> ArrayList<JNIOrgInfo>
		static int setFieldValue(JNIEnv *env, std::vector<OrgInfo> departList, jobject &joOrgInfoArrayList);

		// std::vector<StChatGroup> -> ArrayList<cn.geedow.netprotocol.basicDataStructure.JNIGroupInfo>
		static int setFieldValue(JNIEnv *env, std::vector<StChatGroup> cppGroupList, jobject &joGroupInfoArrayList);

		// std::vector<StreamInfo> <- ArrayList<cn.geedow.netprotocol.JNIStreamInfo>
		static int getFieldValue(JNIEnv *env, jobject joStreamInfoList, std::vector<StreamInfo> &cppStreamInfoList);
		static int getFieldValue(JNIEnv *env, jobject joStreamInfo, StreamInfo &cppStreamInfo);
		static int setFieldValue(JNIEnv *env, StreamInfo cppStreamInfo, jobject &joStreamInfo);

		//StStreamInfo
		static int getFieldValue(JNIEnv *env, jobject joStStreamInfo, StStreamInfo &cppStStreamInfo);
		static int setFieldValue(JNIEnv *env, StStreamInfo cppStStreamInfo, jobject &joStStreamInfo);
		// std::vector<StMediaControlParam> <- ArrayList<cn.geedow.netprotocol.basicDataStructure.JNIMediaControlParam>
		static int getFieldValue(JNIEnv *env, jobject joMediaControlParamList, std::vector<StMediaControlParam> &cppMediaControlParamList);
		static int getFieldValue(JNIEnv *env, jobject joMediaControlParam, StMediaControlParam &cppMediaControlParam);

		// std::vector<StParticipantInfo>
		static int setFieldValue(JNIEnv *env, StParticipantInfo cppStParticipantInfo, jobject &joStParticipantInfo);
		static int getFieldValue(JNIEnv *env, jobject joStParticipantInfo, StParticipantInfo &cppStParticipantInfo);

		static int getFieldValue(JNIEnv *env, jobject joConfigInfo, StPresetPositionConfigInfo &cppConfigInfo);
		static int setFieldValue(JNIEnv *env, StPresetPositionConfigInfo cppConfigInfo, jobject &joConfigInfo);

		static int getFieldValue(JNIEnv *env, jobject joAppointConference, StAppointConference &cppAppointConference);
		static int setFieldValue(JNIEnv *env, StAppointConference cppAppointConference, jobject &joAppointConference);

		static int setFieldValue(JNIEnv *env, StCompanyInfo cppCompanyInfo, jobject &joCompanyInfo);

		static int setFieldValue(JNIEnv *env, StIceServerInfo cppIceServerInfo, jobject &joIceServerInfo);

		static int getFieldValue(JNIEnv *env, jobject joServerInfo, ServerInfo &cppServerRoomInfo);
		static int setFieldValue(JNIEnv *env, ServerInfo cppServerRoomInfo, jobject &joServerInfo);

		static int getFieldValue(JNIEnv *env, jobject joBasicInfo, BasicInfo &cppBasicRoomInfo);
		static int setFieldValue(JNIEnv *env, BasicInfo cppBasicRoomInfo, jobject &joBasicInfo);

		static int getFieldValue(JNIEnv *env, jobject joInfo, StTerminalLocalInfo &cppInfo);
		static int setFieldValue(JNIEnv *env, StTerminalLocalInfo cppInfo, jobject &joInfo);

		static int setFieldValue(JNIEnv *env, StUnfinishedRoomInfo cppRoomInfo, jobject &joRoomInfo);

		static int getFieldValue(JNIEnv *env, jobject joNetworkQuality, StNetworkQuality &cppNetworkQuality);

		static int getFieldValue(JNIEnv *env, jobject joStreamQuality, StStreamQuality &cppStreamQuality);

		static int getFieldValue(JNIEnv *env, jobject joBarrage, StBarrage &cppBarrage);
		static int setFieldValue(JNIEnv *env, StBarrage cppBarrage, jobject &joBarrage);

		static int getFieldValue(JNIEnv *env, jobject joMessage, StIMMessage &cppMessage);
		static int setFieldValue(JNIEnv *env, StIMMessage cppMessage, jobject &joMessage);

		static int getFieldValue(JNIEnv *env, jobject joAccountInfo, StAccountInfo &cppAccountInfo);
		static int setFieldValue(JNIEnv *env, StAccountInfo cppAccountInfo, jobject &joAccountInfo);
		static int getFieldValue(JNIEnv *env, jobject joUserInfo, StUserInfo &cppUserInfo);
		static int setFieldValue(JNIEnv *env, StUserInfo cppUserInfo, jobject &joUserInfo);

		static int setFieldValue(JNIEnv *env, LoginInfo cppLoginInfo, jobject &joLoginInfo);

		static int setFieldValue(JNIEnv *env, StPushedMsg cppPushedMsg, jobject &joPushedMsg);
		static int setFieldValue(JNIEnv *env, StHardTerminalDeviceInfo deviceInfo, jobject &joDeviceInfo);

		static int getFieldValue(JNIEnv *env, jobject joRect, StRect &cppRect);
		static int setFieldValue(JNIEnv *env, StRect cppRect, jobject &joRect);

		static int getFieldValue(JNIEnv *env, jobject joView, StView &cppView);
		static int setFieldValue(JNIEnv *env, StView cppView, jobject &joView);

		static int getFieldValue(JNIEnv *env, jobject joCalleeInfo, StCalleeInfo &cppCalleeInfo);
		static int setFieldValue(JNIEnv *env, StCalleeInfo cppCalleeInfo, jobject &joCalleeInfo);


		static int getFieldValue(JNIEnv *env, jobject joParam, StSubscribeStreamParam &cppSubscribeStreamParam);
		static int setFieldValue(JNIEnv *env, StSubscribeStreamResponse cppSubRsp, jobject &joSubRsp);
		
	};

	template <typename T>
	inline int JNICommon::getIntFieldValue(JNIEnv *env, jobject joIntegerList, std::vector<T> &cppIntList)
	{
		jclass arrayListClass = env->GetObjectClass(joIntegerList);
		if (!arrayListClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jmethodID getMethodId = env->GetMethodID(arrayListClass, "get", "(I)Ljava/lang/Object;");
		jmethodID sizeMethodId = env->GetMethodID(arrayListClass, "size", "()I");
		env->DeleteLocalRef(arrayListClass);

		jclass intClass = env->FindClass("java/lang/Integer");
		if (intClass == NULL)
		{
			errorf("FIND CLASS FAILED!!!");
			return -1;
		}
		jmethodID intValueId = env->GetMethodID(intClass, "intValue", "()I");
		env->DeleteLocalRef(intClass);

		int arrayListSize = env->CallIntMethod(joIntegerList, sizeMethodId);
		for (int i = 0; i < arrayListSize; i++)
		{
			jobject joInteger = env->CallObjectMethod(joIntegerList, getMethodId, i);
			jint jintInt = env->CallIntMethod(joInteger, intValueId);

			cppIntList.push_back(static_cast<T>(jintInt));

			env->DeleteLocalRef(joInteger);
		}
		return 0;
	}

	template <typename T>
	inline int JNICommon::setIntFieldValue(JNIEnv *env, std::vector<T> cppIntList, jobject &joIntegerList)
	{
		jclass integerClass = env->FindClass("java/lang/Integer");
		if (integerClass == NULL)
		{
			errorf("FIND CLASS FAILED!!!");
			return -1;
		}
		jmethodID integerConstructorId = env->GetMethodID(integerClass, "<init>", "(I)V");

		for (auto cppInt : cppIntList)
		{
			jobject joInterger = env->NewObject(integerClass, integerConstructorId, static_cast<int>(cppInt));

			JNICommon::addEleIntoArrayList(env, joIntegerList, joInterger);

			env->DeleteLocalRef(joInterger);
		}

		env->DeleteLocalRef(integerClass);
		return 0;
	}

	template <typename T>
	inline int JNICommon::getFieldArrayValue(JNIEnv *env, jobject joList, std::vector<T> &cppList)
	{

		jclass arrayListClass = env->GetObjectClass(joList);
		if (!arrayListClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jmethodID getMethodId = env->GetMethodID(arrayListClass, "get", "(I)Ljava/lang/Object;");
		jmethodID sizeMethodId = env->GetMethodID(arrayListClass, "size", "()I");
		env->DeleteLocalRef(arrayListClass);

		int arrayListSize = env->CallIntMethod(joList, sizeMethodId);
		for (int i = 0; i < arrayListSize; i++)
		{
			jobject joElement = env->CallObjectMethod(joList, getMethodId, i);

			T cppElement;
			getFieldValue(env, joElement, cppElement);
			cppList.push_back(cppElement);

			env->DeleteLocalRef(joElement);
		}
		return 0;
	}

	template <typename T>
	inline int JNICommon::setFieldArrayValue(JNIEnv *env, std::vector<T> cppList, std::string elementName, jobject &joList, jobject joElement)
	{
		if (elementName.empty() && joElement == nullptr)
		{
			// return if data required is invalid
			errorf("The elementName is empty as joElement is nullptr.");
			return -1;
		}

		jclass jniElementClass = nullptr;
		if (!elementName.empty())
		{
			// 使用指定元素类型名称，主线程调用该方法进入该分支
			jniElementClass = env->FindClass(elementName.c_str());
		}
		else if (joElement != nullptr)
		{
			// Note(guol)
			//	强烈建议优先传入元素对象，避免在子线程回调自定义类时由于FindClass失败而崩溃
			//	从元素对象获取临时引用，子线程调用该方法进入该分支

			jniElementClass = env->GetObjectClass(joElement);
		}
		if (jniElementClass == nullptr)
		{
			errorf("(FIND/GET OBJECT) CLASS FAILED!!!");
			return -1;
		}
		jmethodID elementConstructorId = env->GetMethodID(jniElementClass, "<init>", "()V");

		for (auto cppElement : cppList)
		{
			jobject joElementTmp = env->NewObject(jniElementClass, elementConstructorId);

			setFieldValue(env, cppElement, joElementTmp);

			JNICommon::addEleIntoArrayList(env, joList, joElementTmp);

			env->DeleteLocalRef(joElementTmp);
		}

		env->DeleteLocalRef(jniElementClass);
		return 0;
	}

	template <>
	inline int JNICommon::setCommonTypeValue<std::string>(JNIEnv *env, std::string value, jobject &joCommonType)
	{
		jclass jniCommonTypeClass = env->GetObjectClass(joCommonType);
		if (!jniCommonTypeClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID fieldID = env->GetFieldID(jniCommonTypeClass, "str", JNI_jstring_SIGN);
		env->DeleteLocalRef(jniCommonTypeClass);

		jstring jstrValue = env->NewStringUTF(value.c_str());
		env->SetObjectField(joCommonType, fieldID, jstrValue);
		env->DeleteLocalRef(jstrValue);

		return 0;
	}

	template <typename T>
	inline int JNICommon::setCommonTypeValue(JNIEnv *env, T value, jobject &joCommonType)
	{
		std::string fieldName = "", typeSign = "";
		bool isString = false; // jstring需要申请空间，故单独处理

		if (std::is_same<int, T>::value)
		{
			fieldName = "number";
			typeSign = JNI_jint_SIGN;
		}
		else if (std::is_same<std::string, T>::value)
		{
			fieldName = "str";
			typeSign = JNI_jstring_SIGN;
			isString = true;
			errorf("[guol] holy shit");
		}
		else if (std::is_same<long, T>::value || std::is_same<long long, T>::value)
		{
			fieldName = "longNumber";
			typeSign = JNI_jlong_SIGN;
		}
		else if (std::is_same<bool, T>::value)
		{
			fieldName = "boolVar";
			typeSign = JNI_jboolean_SIGN;
		}
		else if (std::is_same<double, T>::value)
		{
			fieldName = "doubleNumber";
			typeSign = JNI_jdouble_SIGN;
		}
		else
		{
			errorf("Not supported type!!!");
			return -1;
		}

		jclass jniCommonTypeClass = env->GetObjectClass(joCommonType);
		if (!jniCommonTypeClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID fieldID = env->GetFieldID(jniCommonTypeClass, fieldName.c_str(), typeSign.c_str());
		env->DeleteLocalRef(jniCommonTypeClass);

		if (isString)
		{
		}
		else
		{
			auto tmpFunc = []() {};
			std::is_same<int, T>::value ? (env->SetIntField(joCommonType, fieldID, static_cast<int>(value))) : (std::is_same<long, T>::value || std::is_same<long long, T>::value) ? (env->SetLongField(joCommonType, fieldID, static_cast<long long>(value)))
																										   : std::is_same<bool, T>::value										   ? (env->SetBooleanField(joCommonType, fieldID, static_cast<bool>(value)))
																										   : std::is_same<double, T>::value										   ? (env->SetDoubleField(joCommonType, fieldID, static_cast<double>(value)))
																																												   : tmpFunc();
		}

		return 0;
	}

}

#endif // __JNI_COMMON_H__
