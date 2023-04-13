#include "JNICommon.h"
#include "JNICustomGlobalRef.h"

#include "SDNPLogger.h"

namespace SDNP
{
	int JNICommon::addEleIntoArrayList(JNIEnv *env, jobject &joArrayList, jobject joEle)
	{
		jclass arrayListClass = env->GetObjectClass(joArrayList);
		if (!arrayListClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jmethodID addMethodId = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");
		env->DeleteLocalRef(arrayListClass);

		env->CallBooleanMethod(joArrayList, addMethodId, joEle);

		return 0;
	}

	int JNICommon::setFieldValueTest(JNIEnv *env, OrgMemberInfo cppMemberInfo, jobject &joMemberInfo)
	{
		if (!joMemberInfo)
		{
			errorf("object is null.");
			return -1;
		}

		jclass jniMemerInfoClass = env->GetObjectClass(joMemberInfo);
		if (!jniMemerInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID orgIdID = env->GetFieldID(jniMemerInfoClass, "orgId", JNI_jint_SIGN);
		jfieldID accountID = env->GetFieldID(jniMemerInfoClass, "account", JNI_jstring_SIGN);
		jfieldID nameID = env->GetFieldID(jniMemerInfoClass, "name", JNI_jstring_SIGN);
		jfieldID userIconID = env->GetFieldID(jniMemerInfoClass, "userIcon", JNI_jstring_SIGN);
		jfieldID statusID = env->GetFieldID(jniMemerInfoClass, "status", JNI_jint_SIGN);
		jfieldID serialNumberID = env->GetFieldID(jniMemerInfoClass, "serialNumber", JNI_jstring_SIGN);
		jfieldID uuidID = env->GetFieldID(jniMemerInfoClass, "uuid", JNI_jstring_SIGN);
		jfieldID phoneID = env->GetFieldID(jniMemerInfoClass, "phone", JNI_jstring_SIGN);
		jfieldID emailID = env->GetFieldID(jniMemerInfoClass, "email", JNI_jstring_SIGN);
		jfieldID departFullNameID = env->GetFieldID(jniMemerInfoClass, "departFullName", JNI_jstring_SIGN);
		jfieldID isFrequentContactID = env->GetFieldID(jniMemerInfoClass, "isFrequentContact", JNI_jboolean_SIGN);
		env->DeleteLocalRef(jniMemerInfoClass);

		jstring jstrAccount = env->NewStringUTF(cppMemberInfo.account.c_str());
		jstring jstrName = env->NewStringUTF(cppMemberInfo.name.c_str());
		jstring jstrUserIcon = env->NewStringUTF(cppMemberInfo.userIcon.c_str());
		jstring jstrSerialNumber = env->NewStringUTF(cppMemberInfo.serialNumber.c_str());
		jstring jstrUuid = env->NewStringUTF(cppMemberInfo.uuid.c_str());
		jstring jstrPhone = env->NewStringUTF(cppMemberInfo.phone.c_str());
		jstring jstrEmail = env->NewStringUTF(cppMemberInfo.email.c_str());
		jstring jstrDepartFullName = env->NewStringUTF(cppMemberInfo.departFullName.c_str());

		env->SetIntField(joMemberInfo, orgIdID, cppMemberInfo.orgId);
		env->SetObjectField(joMemberInfo, accountID, jstrAccount);
		env->SetObjectField(joMemberInfo, nameID, jstrName);
		env->SetObjectField(joMemberInfo, userIconID, jstrUserIcon);
		env->SetIntField(joMemberInfo, statusID, cppMemberInfo.status);
		env->SetObjectField(joMemberInfo, serialNumberID, jstrSerialNumber);
		env->SetObjectField(joMemberInfo, uuidID, jstrUuid);
		env->SetObjectField(joMemberInfo, phoneID, jstrPhone);
		env->SetObjectField(joMemberInfo, emailID, jstrEmail);
		env->SetObjectField(joMemberInfo, departFullNameID, jstrDepartFullName);
		env->SetBooleanField(joMemberInfo, isFrequentContactID, cppMemberInfo.isFrequentContact);

		env->DeleteLocalRef(jstrAccount);
		env->DeleteLocalRef(jstrUuid);
		env->DeleteLocalRef(jstrName);
		env->DeleteLocalRef(jstrUserIcon);
		env->DeleteLocalRef(jstrPhone);
		env->DeleteLocalRef(jstrEmail);
		env->DeleteLocalRef(jstrDepartFullName);
		env->DeleteLocalRef(jstrSerialNumber);

		return 0;
	}

	std::string JNICommon::getJStringValue(JNIEnv *env, jstring jstr)
	{
		if (jstr == nullptr)
		{
			errorf("Get value from NULL java.lang.String!!!");
			return "";
		}
		const char *cppStr = env->GetStringUTFChars(jstr, NULL);
		std::string result(cppStr);
		env->ReleaseStringUTFChars(jstr, cppStr);
		return result;
	}

	int JNICommon::setJStringValue(JNIEnv *env, std::string str, jstring &jstr)
	{
		jstring jstrTmp = env->NewStringUTF(str.c_str());
		jstr = std::move(jstrTmp);
		env->DeleteLocalRef(jstrTmp);
		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joStringList, std::vector<std::string> &cppStringList)
	{
		jclass arrayListClass = env->GetObjectClass(joStringList);
		if (!arrayListClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}

		jmethodID getMethodId = env->GetMethodID(arrayListClass, "get", "(I)Ljava/lang/Object;");
		jmethodID sizeMethodId = env->GetMethodID(arrayListClass, "size", "()I");
		env->DeleteLocalRef(arrayListClass);

		int arrayListSize = env->CallIntMethod(joStringList, sizeMethodId);
		for (int i = 0; i < arrayListSize; i++)
		{
			jstring jstrString = (jstring)env->CallObjectMethod(joStringList, getMethodId, i);

			cppStringList.push_back(getJStringValue(env, jstrString));

			env->DeleteLocalRef(jstrString);
		}
		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joLong, long long &cppLong)
	{
		jclass LongClass = env->GetObjectClass(joLong);
		if (!LongClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jmethodID longId = env->GetMethodID(LongClass, "longValue", "()J");
		env->DeleteLocalRef(LongClass);

		cppLong = env->CallLongMethod(joLong, longId);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joParam, StSubscribeStreamParam &cppSubscribeStreamParam) 
	{
		jclass jniParamClass = env->GetObjectClass(joParam);
		if (!jniParamClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID accountID = env->GetFieldID(jniParamClass, "account", JNI_jstring_SIGN);
		jfieldID streamTypeID = env->GetFieldID(jniParamClass, "streamType", JNI_jint_SIGN);
		jfieldID sdpOfferID = env->GetFieldID(jniParamClass, "sdpOffer", JNI_jstring_SIGN);
		jfieldID mediaTypeID = env->GetFieldID(jniParamClass, "mediaType", JNI_jint_SIGN);
		jfieldID transportIdID = env->GetFieldID(jniParamClass, "transportId", JNI_jstring_SIGN);
		
		env->DeleteLocalRef(jniParamClass);

		jstring jstrAccount = (jstring)env->GetObjectField(joParam, accountID);
		jint jiStreamType = env->GetIntField(joParam, streamTypeID);
		jstring jstrSdpOffer = (jstring)env->GetObjectField(joParam, sdpOfferID);
		jint jiMediaType = env->GetIntField(joParam, mediaTypeID);
		jstring jstrTransportId = (jstring)env->GetObjectField(joParam, transportIdID);
		// jint jiOperation = env->GetIntField(joParam, operationID);

		cppSubscribeStreamParam.account = JNICommon::getJStringValue(env, jstrAccount);
		cppSubscribeStreamParam.streamType = (EnStreamType)jiStreamType;
		cppSubscribeStreamParam.sdpOffer = JNICommon::getJStringValue(env, jstrSdpOffer);
		cppSubscribeStreamParam.mediaType = (EnMediaType)jiMediaType;
		cppSubscribeStreamParam.transportId = JNICommon::getJStringValue(env, jstrTransportId);

		env->DeleteLocalRef(jstrAccount);
		env->DeleteLocalRef(jstrSdpOffer);
		env->DeleteLocalRef(jstrTransportId);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StSubscribeStreamResponse cppSubRsp, jobject &joSubRsp)
	{
		jclass jniSubscribeStreamResponseClass = env->GetObjectClass(joSubRsp);
		if (!jniSubscribeStreamResponseClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID sdpID = env->GetFieldID(jniSubscribeStreamResponseClass, "sdp", JNI_jstring_SIGN);
		jfieldID errorCodeID = env->GetFieldID(jniSubscribeStreamResponseClass, "errorCode", JNI_jint_SIGN);
		jfieldID accountID = env->GetFieldID(jniSubscribeStreamResponseClass, "account", JNI_jstring_SIGN);
		jfieldID streamTypeID = env->GetFieldID(jniSubscribeStreamResponseClass, "streamType", JNI_jint_SIGN);
		jfieldID mediaTypeID = env->GetFieldID(jniSubscribeStreamResponseClass, "mediaType", JNI_jint_SIGN);
		jfieldID transportIdID = env->GetFieldID(jniSubscribeStreamResponseClass, "transportId", JNI_jstring_SIGN);
		
		env->DeleteLocalRef(jniSubscribeStreamResponseClass);

		jstring jstr_sdp = env->NewStringUTF(cppSubRsp.sdp.c_str());
		jstring jstr_account = env->NewStringUTF(cppSubRsp.account.c_str());
		jstring jstr_transportId = env->NewStringUTF(cppSubRsp.transportId.c_str());

		env->SetObjectField(joSubRsp, sdpID, jstr_sdp);
		env->SetIntField(joSubRsp, errorCodeID, cppSubRsp.errorCode);
		env->SetObjectField(joSubRsp, accountID, jstr_account);
		env->SetIntField(joSubRsp, streamTypeID, cppSubRsp.streamType);
		env->SetIntField(joSubRsp, mediaTypeID, cppSubRsp.mediaType);
		env->SetObjectField(joSubRsp, transportIdID, jstr_transportId);


		env->DeleteLocalRef(jstr_sdp);
		env->DeleteLocalRef(jstr_account);
		env->DeleteLocalRef(jstr_transportId);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joProjectionInfo, StProjectionInfo &cppProjectionInfo)
	{
		jclass jniProjectionInfoClass = env->GetObjectClass(joProjectionInfo);
		if (!jniProjectionInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID nameID = env->GetFieldID(jniProjectionInfoClass, "name", JNI_jstring_SIGN);
		jfieldID serialNumberID = env->GetFieldID(jniProjectionInfoClass, "serialNumber", JNI_jstring_SIGN);
		jfieldID projectionCodeID = env->GetFieldID(jniProjectionInfoClass, "projectionCode", JNI_jstring_SIGN);
		jfieldID wsAddressID = env->GetFieldID(jniProjectionInfoClass, "wsAddress", JNI_jstring_SIGN);
		env->DeleteLocalRef(jniProjectionInfoClass);

		jstring jstrName = (jstring)env->GetObjectField(joProjectionInfo, nameID);
		jstring jstrSerialNumber = (jstring)env->GetObjectField(joProjectionInfo, serialNumberID);
		jstring jstrProjectionCode = (jstring)env->GetObjectField(joProjectionInfo, projectionCodeID);
		jstring jstrWsAddress = (jstring)env->GetObjectField(joProjectionInfo, wsAddressID);

		cppProjectionInfo.name = JNICommon::getJStringValue(env, jstrName);
		cppProjectionInfo.serialNumber = JNICommon::getJStringValue(env, jstrSerialNumber);
		cppProjectionInfo.projectionCode = JNICommon::getJStringValue(env, jstrProjectionCode);
		cppProjectionInfo.wsAddress = JNICommon::getJStringValue(env, jstrWsAddress);

		env->DeleteLocalRef(jstrName);
		env->DeleteLocalRef(jstrSerialNumber);
		env->DeleteLocalRef(jstrProjectionCode);
		env->DeleteLocalRef(jstrWsAddress);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StProjectionInfo cppProjectionInfo, jobject &joProjectionInfo)
	{
		jclass jniProjectionInfoClass = env->GetObjectClass(joProjectionInfo);
		if (!jniProjectionInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID nameID = env->GetFieldID(jniProjectionInfoClass, "name", JNI_jstring_SIGN);
		jfieldID serialNumberID = env->GetFieldID(jniProjectionInfoClass, "serialNumber", JNI_jstring_SIGN);
		jfieldID projectionCodeID = env->GetFieldID(jniProjectionInfoClass, "projectionCode", JNI_jstring_SIGN);
		jfieldID wsAddressID = env->GetFieldID(jniProjectionInfoClass, "wsAddress", JNI_jstring_SIGN);
		env->DeleteLocalRef(jniProjectionInfoClass);		

		jstring jstrName = env->NewStringUTF(cppProjectionInfo.name.c_str());
		jstring jstrSerialNumber = env->NewStringUTF(cppProjectionInfo.serialNumber.c_str());
		jstring jstrProjectionCode = env->NewStringUTF(cppProjectionInfo.projectionCode.c_str());
		jstring jstrWsAddress = env->NewStringUTF(cppProjectionInfo.wsAddress.c_str());

		env->SetObjectField(joProjectionInfo, nameID, jstrName);
		env->SetObjectField(joProjectionInfo, serialNumberID, jstrSerialNumber);
		env->SetObjectField(joProjectionInfo, projectionCodeID, jstrProjectionCode);
		env->SetObjectField(joProjectionInfo, wsAddressID, jstrWsAddress);

		env->DeleteLocalRef(jstrName);
		env->DeleteLocalRef(jstrSerialNumber);
		env->DeleteLocalRef(jstrProjectionCode);
		env->DeleteLocalRef(jstrWsAddress);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joParam, StPtzControlParam &cppParam)
	{
		jclass jniPtzControlParamClass = env->GetObjectClass(joParam);
		if (!jniPtzControlParamClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID targetAccountID = env->GetFieldID(jniPtzControlParamClass, "targetAccount", JNI_jstring_SIGN);
		jfieldID operationID = env->GetFieldID(jniPtzControlParamClass, "operation", JNI_jint_SIGN);
		jfieldID maxDurationID = env->GetFieldID(jniPtzControlParamClass, "maxDuration", JNI_jint_SIGN);
		env->DeleteLocalRef(jniPtzControlParamClass);

		jstring jstrTargetAccount = (jstring)env->GetObjectField(joParam, targetAccountID);
		jint jiOperation = env->GetIntField(joParam, operationID);
		jint jjMaxDuration = env->GetIntField(joParam, maxDurationID);

		const char *cppTargetAccount = env->GetStringUTFChars(jstrTargetAccount, NULL);

		cppParam.targetAccount = cppTargetAccount;
		cppParam.operation = jiOperation;
		cppParam.maxDuration = jjMaxDuration;

		env->ReleaseStringUTFChars(jstrTargetAccount, cppTargetAccount);
		env->DeleteLocalRef(jstrTargetAccount);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StPtzControlParam cppParam, jobject &joParam)
	{
		jclass jniPtzControlParamClass = env->FindClass(PTZ_CONTROL_PARAM_CLASS_NAME);
		if (!jniPtzControlParamClass)
		{
			errorf("FIND CLASS FAILED!!!");
			return -1;
		}
		jfieldID targetAccountID = env->GetFieldID(jniPtzControlParamClass, "targetAccount", JNI_jstring_SIGN);
		jfieldID operationID = env->GetFieldID(jniPtzControlParamClass, "operation", JNI_jint_SIGN);
		jfieldID maxDurationID = env->GetFieldID(jniPtzControlParamClass, "maxDuration", JNI_jint_SIGN);
		env->DeleteLocalRef(jniPtzControlParamClass);

		jstring jstrTargetAccount = env->NewStringUTF(cppParam.targetAccount.c_str());

		env->SetObjectField(joParam, targetAccountID, jstrTargetAccount);
		env->SetIntField(joParam, operationID, cppParam.operation);
		env->SetIntField(joParam, maxDurationID, cppParam.maxDuration);

		env->DeleteLocalRef(jstrTargetAccount);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joPageInfoIn, StDataPageInfo &pageInfo)
	{
		jclass dataPageInfoInClass = env->GetObjectClass(joPageInfoIn);
		if (!dataPageInfoInClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID upToAllID = env->GetFieldID(dataPageInfoInClass, "upToAll", JNI_jboolean_SIGN);
		jfieldID totalDatasID = env->GetFieldID(dataPageInfoInClass, "totalDatas", JNI_jint_SIGN);
		jfieldID pageNumID = env->GetFieldID(dataPageInfoInClass, "pageNum", JNI_jint_SIGN);
		jfieldID pageSizeID = env->GetFieldID(dataPageInfoInClass, "pageSize", JNI_jint_SIGN);
		jfieldID totalPagesID = env->GetFieldID(dataPageInfoInClass, "totalPages", JNI_jint_SIGN);
		jfieldID versionID = env->GetFieldID(dataPageInfoInClass, "version", JNI_jstring_SIGN);
		env->DeleteLocalRef(dataPageInfoInClass);

		jboolean jbUpToAll = env->GetBooleanField(joPageInfoIn, upToAllID);
		jint jintTotalDatas = env->GetIntField(joPageInfoIn, totalDatasID);
		jint jintPageNum = env->GetIntField(joPageInfoIn, pageNumID);
		jint jintPageSize = env->GetIntField(joPageInfoIn, pageSizeID);
		jint jintTotalPages = env->GetIntField(joPageInfoIn, totalPagesID);
		jstring jstrVersion = (jstring)env->GetObjectField(joPageInfoIn, versionID);
		const char *cppVersion = env->GetStringUTFChars(jstrVersion, NULL);

		pageInfo = StDataPageInfo(jbUpToAll, jintTotalDatas, jintPageNum, jintPageSize, jintTotalPages, cppVersion);

		env->ReleaseStringUTFChars(jstrVersion, cppVersion);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StDataPageInfo dataPageInfo, jobject &joPageInfoIn)
	{
		if (!joPageInfoIn)
		{
			errorf("object is null.");
			return -1;
		}

		jclass dataPageInfoClass = env->GetObjectClass(joPageInfoIn);
		if (!dataPageInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID upToAllID = env->GetFieldID(dataPageInfoClass, "upToAll", JNI_jboolean_SIGN);
		jfieldID totalDatasID = env->GetFieldID(dataPageInfoClass, "totalDatas", JNI_jint_SIGN);
		jfieldID curPageID = env->GetFieldID(dataPageInfoClass, "pageNum", JNI_jint_SIGN);
		jfieldID curPageSizeID = env->GetFieldID(dataPageInfoClass, "pageSize", JNI_jint_SIGN);
		jfieldID totalPagesID = env->GetFieldID(dataPageInfoClass, "totalPages", JNI_jint_SIGN);
		jfieldID versionID = env->GetFieldID(dataPageInfoClass, "version", JNI_jstring_SIGN);
		env->DeleteLocalRef(dataPageInfoClass);

		jstring jstrVersion = (jstring)env->NewStringUTF(dataPageInfo.version.c_str());
		env->SetBooleanField(joPageInfoIn, upToAllID, dataPageInfo.upToAll);
		env->SetIntField(joPageInfoIn, totalDatasID, dataPageInfo.totalDatas);
		env->SetIntField(joPageInfoIn, curPageID, dataPageInfo.pageNum);
		env->SetIntField(joPageInfoIn, curPageSizeID, dataPageInfo.pageSize);
		env->SetIntField(joPageInfoIn, totalPagesID, dataPageInfo.totalPages);
		env->SetObjectField(joPageInfoIn, versionID, jstrVersion);
		env->DeleteLocalRef(jstrVersion);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joMemberInfo, OrgMemberInfo &cppMemberInfo)
	{
		jclass jniOrgMemberInfoClass = env->GetObjectClass(joMemberInfo);
		if (!jniOrgMemberInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID orgIdID = env->GetFieldID(jniOrgMemberInfoClass, "orgId", JNI_jint_SIGN);
		jfieldID accountID = env->GetFieldID(jniOrgMemberInfoClass, "account", JNI_jstring_SIGN);
		jfieldID nameID = env->GetFieldID(jniOrgMemberInfoClass, "name", JNI_jstring_SIGN);
		jfieldID userIconID = env->GetFieldID(jniOrgMemberInfoClass, "userIcon", JNI_jstring_SIGN);
		jfieldID statusID = env->GetFieldID(jniOrgMemberInfoClass, "status", JNI_jint_SIGN);
		jfieldID accountTypeID = env->GetFieldID(jniOrgMemberInfoClass, "accountType", JNI_jint_SIGN);
		jfieldID serialNumberID = env->GetFieldID(jniOrgMemberInfoClass, "serialNumber", JNI_jstring_SIGN);
		jfieldID uuidID = env->GetFieldID(jniOrgMemberInfoClass, "uuid", JNI_jstring_SIGN);
		jfieldID phoneID = env->GetFieldID(jniOrgMemberInfoClass, "phone", JNI_jstring_SIGN);
		jfieldID emailID = env->GetFieldID(jniOrgMemberInfoClass, "email", JNI_jstring_SIGN);
		jfieldID departFullNameID = env->GetFieldID(jniOrgMemberInfoClass, "departFullName", JNI_jstring_SIGN);
		jfieldID isFrequentContactID = env->GetFieldID(jniOrgMemberInfoClass, "isFrequentContact", JNI_jboolean_SIGN);
		env->DeleteLocalRef(jniOrgMemberInfoClass);

		jint jintOrgId = env->GetIntField(joMemberInfo, orgIdID);
		jstring jstrAccount = (jstring)env->GetObjectField(joMemberInfo, accountID);
		jstring jstrName = (jstring)env->GetObjectField(joMemberInfo, nameID);
		jstring jstrUserIcon = (jstring)env->GetObjectField(joMemberInfo, userIconID);
		jint jintStatus = env->GetIntField(joMemberInfo, statusID);
		jint jintAccountType = env->GetIntField(joMemberInfo, accountTypeID);
		jstring jstrSerialNumber = (jstring)env->GetObjectField(joMemberInfo, serialNumberID);
		jstring jstrUuid = (jstring)env->GetObjectField(joMemberInfo, uuidID);
		jstring jstrPhone = (jstring)env->GetObjectField(joMemberInfo, phoneID);
		jstring jstrEmail = (jstring)env->GetObjectField(joMemberInfo, emailID);
		jstring jstrDepartFullName = (jstring)env->GetObjectField(joMemberInfo, departFullNameID);
		jboolean jbIsFrequentContact = env->GetBooleanField(joMemberInfo, isFrequentContactID);

		const char *cppAccount = env->GetStringUTFChars(jstrAccount, NULL);
		const char *cppName = env->GetStringUTFChars(jstrName, NULL);
		const char *cppUserIcon = env->GetStringUTFChars(jstrUserIcon, NULL);
		const char *cppSerialNumber = env->GetStringUTFChars(jstrSerialNumber, NULL);
		const char *cppUuid = env->GetStringUTFChars(jstrUuid, NULL);
		const char *cppPhone = env->GetStringUTFChars(jstrPhone, NULL);
		const char *cppEmail = env->GetStringUTFChars(jstrEmail, NULL);
		const char *cppDepartFullName = env->GetStringUTFChars(jstrDepartFullName, NULL);

		cppMemberInfo.orgId = jintOrgId;
		cppMemberInfo.account = cppAccount;
		cppMemberInfo.name = cppName;
		cppMemberInfo.userIcon = cppUserIcon;
		cppMemberInfo.status = (EnTerminalStatus)jintStatus;
		cppMemberInfo.accountType = (EnAccountType)jintAccountType;
		cppMemberInfo.serialNumber = cppSerialNumber;
		cppMemberInfo.uuid = cppUuid;
		cppMemberInfo.phone = cppPhone;
		cppMemberInfo.email = cppEmail;
		cppMemberInfo.departFullName = cppDepartFullName;
		cppMemberInfo.isFrequentContact = jbIsFrequentContact;

		env->ReleaseStringUTFChars(jstrAccount, cppAccount);
		env->ReleaseStringUTFChars(jstrName, cppName);
		env->ReleaseStringUTFChars(jstrUserIcon, cppUserIcon);
		env->ReleaseStringUTFChars(jstrSerialNumber, cppSerialNumber);
		env->ReleaseStringUTFChars(jstrUuid, cppUuid);
		env->ReleaseStringUTFChars(jstrPhone, cppPhone);
		env->ReleaseStringUTFChars(jstrEmail, cppEmail);
		env->ReleaseStringUTFChars(jstrDepartFullName, cppDepartFullName);

		env->DeleteLocalRef(jstrAccount);
		env->DeleteLocalRef(jstrName);
		env->DeleteLocalRef(jstrUserIcon);
		env->DeleteLocalRef(jstrSerialNumber);
		env->DeleteLocalRef(jstrUuid);
		env->DeleteLocalRef(jstrPhone);
		env->DeleteLocalRef(jstrEmail);
		env->DeleteLocalRef(jstrDepartFullName);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, OrgMemberInfo cppMemberInfo, jobject &joMemberInfo)
	{
		if (!joMemberInfo)
		{
			errorf("object is null.");
			return -1;
		}

		jclass jniMemerInfoClass = env->GetObjectClass(joMemberInfo);
		if (!jniMemerInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID orgIdID = env->GetFieldID(jniMemerInfoClass, "orgId", JNI_jint_SIGN);
		jfieldID accountID = env->GetFieldID(jniMemerInfoClass, "account", JNI_jstring_SIGN);
		jfieldID nameID = env->GetFieldID(jniMemerInfoClass, "name", JNI_jstring_SIGN);
		jfieldID userIconID = env->GetFieldID(jniMemerInfoClass, "userIcon", JNI_jstring_SIGN);
		jfieldID statusID = env->GetFieldID(jniMemerInfoClass, "status", JNI_jint_SIGN);
		jfieldID accountTypeID = env->GetFieldID(jniMemerInfoClass, "accountType", JNI_jint_SIGN);
		jfieldID serialNumberID = env->GetFieldID(jniMemerInfoClass, "serialNumber", JNI_jstring_SIGN);
		jfieldID uuidID = env->GetFieldID(jniMemerInfoClass, "uuid", JNI_jstring_SIGN);
		jfieldID phoneID = env->GetFieldID(jniMemerInfoClass, "phone", JNI_jstring_SIGN);
		jfieldID emailID = env->GetFieldID(jniMemerInfoClass, "email", JNI_jstring_SIGN);
		jfieldID departFullNameID = env->GetFieldID(jniMemerInfoClass, "departFullName", JNI_jstring_SIGN);
		jfieldID isFrequentContactID = env->GetFieldID(jniMemerInfoClass, "isFrequentContact", JNI_jboolean_SIGN);
		env->DeleteLocalRef(jniMemerInfoClass);

		jstring jstrAccount = env->NewStringUTF(cppMemberInfo.account.c_str());
		jstring jstrName = env->NewStringUTF(cppMemberInfo.name.c_str());
		jstring jstrUserIcon = env->NewStringUTF(cppMemberInfo.userIcon.c_str());
		jstring jstrSerialNumber = env->NewStringUTF(cppMemberInfo.serialNumber.c_str());
		jstring jstrUuid = env->NewStringUTF(cppMemberInfo.uuid.c_str());
		jstring jstrPhone = env->NewStringUTF(cppMemberInfo.phone.c_str());
		jstring jstrEmail = env->NewStringUTF(cppMemberInfo.email.c_str());
		jstring jstrDepartFullName = env->NewStringUTF(cppMemberInfo.departFullName.c_str());

		env->SetIntField(joMemberInfo, orgIdID, cppMemberInfo.orgId);
		env->SetObjectField(joMemberInfo, accountID, jstrAccount);
		env->SetObjectField(joMemberInfo, nameID, jstrName);
		env->SetObjectField(joMemberInfo, userIconID, jstrUserIcon);
		env->SetIntField(joMemberInfo, statusID, cppMemberInfo.status);
		env->SetIntField(joMemberInfo, accountTypeID, cppMemberInfo.accountType);
		env->SetObjectField(joMemberInfo, serialNumberID, jstrSerialNumber);
		env->SetObjectField(joMemberInfo, uuidID, jstrUuid);
		env->SetObjectField(joMemberInfo, phoneID, jstrPhone);
		env->SetObjectField(joMemberInfo, emailID, jstrEmail);
		env->SetObjectField(joMemberInfo, departFullNameID, jstrDepartFullName);
		env->SetBooleanField(joMemberInfo, isFrequentContactID, cppMemberInfo.isFrequentContact);

		env->DeleteLocalRef(jstrAccount);
		env->DeleteLocalRef(jstrUuid);
		env->DeleteLocalRef(jstrName);
		env->DeleteLocalRef(jstrUserIcon);
		env->DeleteLocalRef(jstrPhone);
		env->DeleteLocalRef(jstrEmail);
		env->DeleteLocalRef(jstrDepartFullName);
		env->DeleteLocalRef(jstrSerialNumber);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joConfLayout, StConferenceLayout &cppConfLayout)
	{
		jclass jniConfLayoutClass = env->GetObjectClass(joConfLayout);
		if (!jniConfLayoutClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID automaticallyID = env->GetFieldID(jniConfLayoutClass, "automatically", JNI_jboolean_SIGN);
		jfieldID modeID = env->GetFieldID(jniConfLayoutClass, "mode", JNI_jint_SIGN);
		env->DeleteLocalRef(jniConfLayoutClass);

		jboolean jbAutomatically = env->GetBooleanField(joConfLayout, automaticallyID);
		jint jiMode = env->GetIntField(joConfLayout, modeID);

		cppConfLayout.automatically = jbAutomatically;
		cppConfLayout.mode = jiMode;

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StConferenceLayout cppConfLayout, jobject &joConfLayout)
	{
		jclass jniConfLayoutClass = env->GetObjectClass(joConfLayout);
		if (!jniConfLayoutClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID automaticallyID = env->GetFieldID(jniConfLayoutClass, "automatically", JNI_jboolean_SIGN);
		jfieldID modeID = env->GetFieldID(jniConfLayoutClass, "mode", JNI_jint_SIGN);
		env->DeleteLocalRef(jniConfLayoutClass);

		env->SetBooleanField(joConfLayout, automaticallyID, cppConfLayout.automatically);
		env->SetIntField(joConfLayout, modeID, cppConfLayout.mode);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StMeeting cppMeetingInfo, jobject &joStMeeting)
	{
		if (!joStMeeting)
		{
			errorf("object is null.");
			return -1;
		}

		jclass jniStMeetingClass = env->GetObjectClass(joStMeeting);
		if (!jniStMeetingClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID roomID = env->GetFieldID(jniStMeetingClass, "room", BASE_MEETING_ROOM_CLASS_SIGH);
		jfieldID ruidID = env->GetFieldID(jniStMeetingClass, "ruid", JNI_jstring_SIGN);
		jfieldID passwordID = env->GetFieldID(jniStMeetingClass, "password", JNI_jstring_SIGN);
		jfieldID subjectID = env->GetFieldID(jniStMeetingClass, "subject", JNI_jstring_SIGN);
		jfieldID detailID = env->GetFieldID(jniStMeetingClass, "detail", JNI_jstring_SIGN);
		jfieldID numberOfParticipantID = env->GetFieldID(jniStMeetingClass, "numberOfParticipant", JNI_jint_SIGN);
		jfieldID subscribeMediaModeID = env->GetFieldID(jniStMeetingClass, "subscribeMediaMode", JNI_jint_SIGN);
		jfieldID currentMediaModeID = env->GetFieldID(jniStMeetingClass, "currentMediaMode", JNI_jint_SIGN);
		jfieldID layoutID = env->GetFieldID(jniStMeetingClass, "layout", JAVA_ARRAYLIST_SIGN);
		jfieldID durationID = env->GetFieldID(jniStMeetingClass, "duration", JNI_jint_SIGN);
		jfieldID startTimeMsID = env->GetFieldID(jniStMeetingClass, "startTimeMs", JNI_jlong_SIGN);
		jfieldID endTimeMsID = env->GetFieldID(jniStMeetingClass, "endTimeMs", JNI_jlong_SIGN);
		jfieldID startRecordTimeMsID = env->GetFieldID(jniStMeetingClass, "startRecordTimeMs", JNI_jlong_SIGN);
		jfieldID joinRoomMuteModeID = env->GetFieldID(jniStMeetingClass, "joinRoomMuteMode", JNI_jint_SIGN);
		jfieldID allowRecordMeetingID = env->GetFieldID(jniStMeetingClass, "allowRecordMeeting", JNI_jboolean_SIGN);
		jfieldID isRecordingID = env->GetFieldID(jniStMeetingClass, "isRecording", JNI_jboolean_SIGN);
		jfieldID permissionJoinRoomByIdID = env->GetFieldID(jniStMeetingClass, "permissionJoinRoomById", JNI_jboolean_SIGN);
		jfieldID allowPartOpenSpeakerID = env->GetFieldID(jniStMeetingClass, "allowPartOpenSpeaker", JNI_jboolean_SIGN);
		jfieldID allowPartOpenMicID = env->GetFieldID(jniStMeetingClass, "allowPartOpenMic", JNI_jboolean_SIGN);
		jfieldID imPermissionID = env->GetFieldID(jniStMeetingClass, "imPermission", JNI_jint_SIGN);
		jfieldID hostInfoID = env->GetFieldID(jniStMeetingClass, "hostInfo", USER_INFO_CLASS_SIGN);
		jfieldID inviteUrlID = env->GetFieldID(jniStMeetingClass, "inviteUrl", JNI_jstring_SIGN);
		jfieldID roleThresholdID = env->GetFieldID(jniStMeetingClass, "roleThreshold", JNI_jint_SIGN);
		jfieldID mediaModeThresholdID = env->GetFieldID(jniStMeetingClass, "mediaModeThreshold", JNI_jint_SIGN);
		jfieldID meetingLockID = env->GetFieldID(jniStMeetingClass, "meetingLock", JNI_jboolean_SIGN);

		env->DeleteLocalRef(jniStMeetingClass);

		jobject joRoom = env->GetObjectField(joStMeeting, roomID);
		jstring jstrRuid = env->NewStringUTF(cppMeetingInfo.ruid.c_str());
		jstring jstrPassword = env->NewStringUTF(cppMeetingInfo.password.c_str());
		jstring jstrSubject = env->NewStringUTF(cppMeetingInfo.subject.c_str());
		jstring jstrDetail = env->NewStringUTF(cppMeetingInfo.detail.c_str());
		jobject joLayout = env->GetObjectField(joStMeeting, layoutID);
		jobject joHostInfo = env->GetObjectField(joStMeeting, hostInfoID);
		jstring jstrInviteUrl = env->NewStringUTF(cppMeetingInfo.inviteUrl.c_str());

		{
			setFieldValue(env, cppMeetingInfo.room, joRoom);
			env->SetObjectField(joStMeeting, ruidID, jstrRuid);
			env->SetObjectField(joStMeeting, passwordID, jstrPassword);
			env->SetObjectField(joStMeeting, subjectID, jstrSubject);
			env->SetObjectField(joStMeeting, detailID, jstrDetail);
			env->SetIntField(joStMeeting, numberOfParticipantID, cppMeetingInfo.numberOfParticipant);
			env->SetIntField(joStMeeting, subscribeMediaModeID, cppMeetingInfo.subscribeMediaMode);
			env->SetIntField(joStMeeting, currentMediaModeID, cppMeetingInfo.currentMediaMode);

			// setFieldArrayValue中调用了findClass，而当前方法会在onMeetingInfoChanged中被调用
			jobject joView = JNICustomGlobalRef::instance()->getGlobalRef(VIEW_CLASS_NAME);
			setFieldArrayValue(env, cppMeetingInfo.layout, "" /*VIEW_CLASS_NAME*/, joLayout, joView);

			env->SetIntField(joStMeeting, durationID, cppMeetingInfo.duration);
			env->SetLongField(joStMeeting, startTimeMsID, cppMeetingInfo.startTimeMs);
			env->SetLongField(joStMeeting, endTimeMsID, cppMeetingInfo.endTimeMs);
			env->SetLongField(joStMeeting, startRecordTimeMsID, cppMeetingInfo.startRecordTimeMs);
			env->SetIntField(joStMeeting, joinRoomMuteModeID, cppMeetingInfo.joinRoomMuteMode);
			env->SetBooleanField(joStMeeting, allowRecordMeetingID, cppMeetingInfo.allowRecordMeeting);
			env->SetBooleanField(joStMeeting, isRecordingID, cppMeetingInfo.isRecording);
			env->SetBooleanField(joStMeeting, permissionJoinRoomByIdID, cppMeetingInfo.permissionJoinRoomById);
			env->SetBooleanField(joStMeeting, allowPartOpenSpeakerID, cppMeetingInfo.allowPartOpenSpeaker);
			env->SetBooleanField(joStMeeting, allowPartOpenMicID, cppMeetingInfo.allowPartOpenMic);
			env->SetIntField(joStMeeting, imPermissionID, cppMeetingInfo.imPermission);
			setFieldValue(env, cppMeetingInfo.hostInfo, joHostInfo);
			env->SetObjectField(joStMeeting, inviteUrlID, jstrInviteUrl);
			env->SetIntField(joStMeeting, roleThresholdID, cppMeetingInfo.roleThreshold);
			env->SetIntField(joStMeeting, mediaModeThresholdID, cppMeetingInfo.mediaModeThreshold);
			env->SetBooleanField(joStMeeting, meetingLockID, cppMeetingInfo.meetingLock);
		}

		env->DeleteLocalRef(joRoom);
		env->DeleteLocalRef(jstrRuid);
		env->DeleteLocalRef(jstrPassword);
		env->DeleteLocalRef(jstrSubject);
		env->DeleteLocalRef(jstrDetail);
		env->DeleteLocalRef(joLayout);
		env->DeleteLocalRef(joHostInfo);
		env->DeleteLocalRef(jstrInviteUrl);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joStMeetingAttribute, StMeetingAttribute &cppAttributeInfo)
	{
		jclass jniStMeetingAttributeClass = env->GetObjectClass(joStMeetingAttribute);
		if (!jniStMeetingAttributeClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID micStatusID = env->GetFieldID(jniStMeetingAttributeClass, "micStatus", JNI_jboolean_SIGN);
		jfieldID cameraStatusID = env->GetFieldID(jniStMeetingAttributeClass, "cameraStatus", JNI_jboolean_SIGN);
		jfieldID speakerStatusID = env->GetFieldID(jniStMeetingAttributeClass, "speakerStatus", JNI_jboolean_SIGN);
		jfieldID isReconnectedID = env->GetFieldID(jniStMeetingAttributeClass, "isReconnected", JNI_jboolean_SIGN);
		jfieldID joinTypeID = env->GetFieldID(jniStMeetingAttributeClass, "joinType", JNI_jboolean_SIGN);
		jfieldID touristNicknameID = env->GetFieldID(jniStMeetingAttributeClass, "touristNickname", JNI_jstring_SIGN);
		jfieldID inAdvanceToJoinID = env->GetFieldID(jniStMeetingAttributeClass, "inAdvanceToJoin", JNI_jboolean_SIGN);

		env->DeleteLocalRef(jniStMeetingAttributeClass);

		jboolean jbMicStatus = env->GetBooleanField(joStMeetingAttribute, micStatusID);
		jboolean jbCameraStatus = env->GetBooleanField(joStMeetingAttribute, cameraStatusID);
		jboolean jbSpeakerStatus = env->GetBooleanField(joStMeetingAttribute, speakerStatusID);
		jboolean jbIsReconnected = env->GetBooleanField(joStMeetingAttribute, isReconnectedID);
		jboolean jbJoinType = env->GetBooleanField(joStMeetingAttribute, joinTypeID);
		jboolean jbInAdvanceToJoin = env->GetBooleanField(joStMeetingAttribute, inAdvanceToJoinID);

		jstring jstrTouristNickname = (jstring)env->GetObjectField(joStMeetingAttribute, touristNicknameID);

		{
			cppAttributeInfo.micStatus = jbMicStatus;
			cppAttributeInfo.cameraStatus = jbCameraStatus;
			cppAttributeInfo.speakerStatus = jbSpeakerStatus;
			cppAttributeInfo.isReconnected = jbIsReconnected;
			cppAttributeInfo.joinType = jbJoinType;
			cppAttributeInfo.touristNickname = getJStringValue(env, jstrTouristNickname);
			cppAttributeInfo.inAdvanceToJoin = jbInAdvanceToJoin;
		}

		env->DeleteLocalRef(jstrTouristNickname);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joStMeeting, StMeeting &cppMeetingInfo)
	{
		jclass jniStMeetingClass = env->GetObjectClass(joStMeeting);
		if (!jniStMeetingClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID roomID = env->GetFieldID(jniStMeetingClass, "room", BASE_MEETING_ROOM_CLASS_SIGH);
		jfieldID ruidID = env->GetFieldID(jniStMeetingClass, "ruid", JNI_jstring_SIGN);
		jfieldID passwordID = env->GetFieldID(jniStMeetingClass, "password", JNI_jstring_SIGN);
		jfieldID subjectID = env->GetFieldID(jniStMeetingClass, "subject", JNI_jstring_SIGN);
		jfieldID detailID = env->GetFieldID(jniStMeetingClass, "detail", JNI_jstring_SIGN);
		jfieldID numberOfParticipantID = env->GetFieldID(jniStMeetingClass, "numberOfParticipant", JNI_jint_SIGN);
		jfieldID subscribeMediaModeID = env->GetFieldID(jniStMeetingClass, "subscribeMediaMode", JNI_jint_SIGN);
		jfieldID currentMediaModeID = env->GetFieldID(jniStMeetingClass, "currentMediaMode", JNI_jint_SIGN);
		jfieldID layoutID = env->GetFieldID(jniStMeetingClass, "layout", JAVA_ARRAYLIST_SIGN);
		jfieldID durationID = env->GetFieldID(jniStMeetingClass, "duration", JNI_jint_SIGN);
		jfieldID startTimeMsID = env->GetFieldID(jniStMeetingClass, "startTimeMs", JNI_jlong_SIGN);
		jfieldID endTimeMsID = env->GetFieldID(jniStMeetingClass, "endTimeMs", JNI_jlong_SIGN);
		jfieldID startRecordTimeMsID = env->GetFieldID(jniStMeetingClass, "startRecordTimeMs", JNI_jlong_SIGN);
		jfieldID joinRoomMuteModeID = env->GetFieldID(jniStMeetingClass, "joinRoomMuteMode", JNI_jint_SIGN);
		jfieldID allowRecordMeetingID = env->GetFieldID(jniStMeetingClass, "allowRecordMeeting", JNI_jboolean_SIGN);
		jfieldID isRecordingID = env->GetFieldID(jniStMeetingClass, "isRecording", JNI_jboolean_SIGN);
		jfieldID permissionJoinRoomByIdID = env->GetFieldID(jniStMeetingClass, "permissionJoinRoomById", JNI_jboolean_SIGN);
		jfieldID allowPartOpenSpeakerID = env->GetFieldID(jniStMeetingClass, "allowPartOpenSpeaker", JNI_jboolean_SIGN);
		jfieldID allowPartOpenMicID = env->GetFieldID(jniStMeetingClass, "allowPartOpenMic", JNI_jboolean_SIGN);
		jfieldID imPermissionID = env->GetFieldID(jniStMeetingClass, "imPermission", JNI_jint_SIGN);
		jfieldID hostInfoID = env->GetFieldID(jniStMeetingClass, "hostInfo", USER_INFO_CLASS_SIGN);
		jfieldID inviteUrlID = env->GetFieldID(jniStMeetingClass, "inviteUrl", JNI_jstring_SIGN);
		jfieldID roleThresholdID = env->GetFieldID(jniStMeetingClass, "roleThreshold", JNI_jint_SIGN);
		jfieldID mediaModeThresholdID = env->GetFieldID(jniStMeetingClass, "mediaModeThreshold", JNI_jint_SIGN);
		jfieldID meetingLockID = env->GetFieldID(jniStMeetingClass, "meetingLock", JNI_jboolean_SIGN);

		env->DeleteLocalRef(jniStMeetingClass);

		jobject joRoom = env->GetObjectField(joStMeeting, roomID);
		jstring jstrRuid = (jstring)env->GetObjectField(joStMeeting, ruidID);
		jstring jstrPassword = (jstring)env->GetObjectField(joStMeeting, passwordID);
		jstring jstrSubject = (jstring)env->GetObjectField(joStMeeting, subjectID);
		jstring jstrDetail = (jstring)env->GetObjectField(joStMeeting, detailID);
		jint jintNumberOfParticipant = env->GetIntField(joStMeeting, numberOfParticipantID);
		jint jintSubscribeMediaMode = env->GetIntField(joStMeeting, subscribeMediaModeID);
		jint jintCurrentMediaMode = env->GetIntField(joStMeeting, currentMediaModeID);
		jobject joLayout = env->GetObjectField(joStMeeting, layoutID);
		jint jintDuration = env->GetIntField(joStMeeting, durationID);
		jlong jlongStartTimeMs = env->GetLongField(joStMeeting, startTimeMsID);
		jlong jlongEndTimeMs = env->GetLongField(joStMeeting, endTimeMsID);
		jlong jlongStartRecordTimeMs = env->GetLongField(joStMeeting, startRecordTimeMsID);
		jint jintJoinRoomMuteMode = env->GetIntField(joStMeeting, joinRoomMuteModeID);
		jboolean jbAllowRecordMeeting = env->GetBooleanField(joStMeeting, allowRecordMeetingID);
		jboolean jbIsRecording = env->GetBooleanField(joStMeeting, isRecordingID);
		jboolean jbPermissionJoinRoomById = env->GetBooleanField(joStMeeting, permissionJoinRoomByIdID);
		jboolean jbAllowPartOpenSpeaker = env->GetBooleanField(joStMeeting, allowPartOpenSpeakerID);
		jboolean jbAllowPartOpenMic = env->GetBooleanField(joStMeeting, allowPartOpenMicID);
		jint jintImPermission = env->GetIntField(joStMeeting, imPermissionID);
		jobject joHostInfo = env->GetObjectField(joStMeeting, hostInfoID);
		jstring jstrInviteUrl = (jstring)env->GetObjectField(joStMeeting, inviteUrlID);
		jint jintRoleThreshold = env->GetIntField(joStMeeting, roleThresholdID);
		jint jintMediaModeThreshold = env->GetIntField(joStMeeting, mediaModeThresholdID);
		jboolean jbMeetingLock = env->GetBooleanField(joStMeeting, meetingLockID);

		{
			// set cppMeetingInfo's values
			//cppMeetingInfo.roomId = getJStringValue(env, jstrRoomId);
			getFieldValue(env, joRoom, cppMeetingInfo.room);
			cppMeetingInfo.ruid = getJStringValue(env, jstrRuid);
			cppMeetingInfo.password = getJStringValue(env, jstrPassword);
			cppMeetingInfo.subject = getJStringValue(env, jstrSubject);
			cppMeetingInfo.detail = getJStringValue(env, jstrDetail);
			cppMeetingInfo.numberOfParticipant = jintNumberOfParticipant;
			cppMeetingInfo.subscribeMediaMode = (EnMediaMode)jintSubscribeMediaMode;
			cppMeetingInfo.currentMediaMode = (EnMediaMode)jintCurrentMediaMode;
			getFieldArrayValue(env, joLayout, cppMeetingInfo.layout);
			cppMeetingInfo.duration = jintDuration;
			cppMeetingInfo.startTimeMs = jlongStartTimeMs;
			cppMeetingInfo.endTimeMs = jlongEndTimeMs;
			cppMeetingInfo.startRecordTimeMs = jlongStartRecordTimeMs;
			cppMeetingInfo.joinRoomMuteMode = (EnJoinRoomMuteMode)jintJoinRoomMuteMode;
			cppMeetingInfo.allowRecordMeeting = jbAllowRecordMeeting;
			cppMeetingInfo.isRecording = jbIsRecording;
			cppMeetingInfo.permissionJoinRoomById = jbPermissionJoinRoomById;
			cppMeetingInfo.allowPartOpenSpeaker = jbAllowPartOpenSpeaker;
			cppMeetingInfo.allowPartOpenMic = jbAllowPartOpenMic;
			cppMeetingInfo.imPermission = static_cast<EnIMPermission>(jintImPermission);
			getFieldValue(env, joHostInfo, cppMeetingInfo.hostInfo);
			cppMeetingInfo.inviteUrl = getJStringValue(env, jstrInviteUrl);
			cppMeetingInfo.roleThreshold = jintRoleThreshold;
			cppMeetingInfo.mediaModeThreshold = jintMediaModeThreshold;
			cppMeetingInfo.meetingLock = jbMeetingLock;
		}
		env->DeleteLocalRef(joRoom);
		env->DeleteLocalRef(jstrRuid);
		env->DeleteLocalRef(jstrPassword);
		env->DeleteLocalRef(jstrSubject);
		env->DeleteLocalRef(jstrDetail);
		env->DeleteLocalRef(joLayout);
		env->DeleteLocalRef(joHostInfo);
		env->DeleteLocalRef(jstrInviteUrl);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joMeetingRooms, StMeetingRoom &cppRoom)
	{
		jclass jniMeetingRoomsClass = env->GetObjectClass(joMeetingRooms);
		if (!jniMeetingRoomsClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID typeID = env->GetFieldID(jniMeetingRoomsClass, "type", JNI_jint_SIGN);
		jfieldID idID = env->GetFieldID(jniMeetingRoomsClass, "id", JNI_jstring_SIGN);
		jfieldID nameID = env->GetFieldID(jniMeetingRoomsClass, "name", JNI_jstring_SIGN);
		jfieldID statusID = env->GetFieldID(jniMeetingRoomsClass, "status", JNI_jint_SIGN);
		jfieldID capacityID = env->GetFieldID(jniMeetingRoomsClass, "capacity", JNI_jint_SIGN);
		jfieldID shortNumID = env->GetFieldID(jniMeetingRoomsClass, "shortNum", JNI_jstring_SIGN);
		jfieldID expiredDateID = env->GetFieldID(jniMeetingRoomsClass, "expiredDate", JNI_jstring_SIGN);
		jfieldID roomIconID = env->GetFieldID(jniMeetingRoomsClass, "roomIcon", JNI_jstring_SIGN);
		jfieldID hasAdminRightsID = env->GetFieldID(jniMeetingRoomsClass, "hasAdminRights", JNI_jboolean_SIGN);

		env->DeleteLocalRef(jniMeetingRoomsClass);

		jint jintType = env->GetIntField(joMeetingRooms, typeID);
		jstring jstrId = (jstring)env->GetObjectField(joMeetingRooms, idID);
		jstring jstrName = (jstring)env->GetObjectField(joMeetingRooms, nameID);
		jint jintStatus = env->GetIntField(joMeetingRooms, statusID);
		jint jintCapacity = env->GetIntField(joMeetingRooms, capacityID);
		jstring jstrShortNum = (jstring)env->GetObjectField(joMeetingRooms, shortNumID);
		jstring jstrExpiredDate = (jstring)env->GetObjectField(joMeetingRooms, expiredDateID);
		jstring jstrRoomIcon = (jstring)env->GetObjectField(joMeetingRooms, roomIconID);
		jboolean jzHasAdminRights = env->GetBooleanField(joMeetingRooms, hasAdminRightsID);

		{
			cppRoom.type = (EnRoomIdType)jintType;
			cppRoom.id = getJStringValue(env, jstrId);
			cppRoom.name = getJStringValue(env, jstrName);
			cppRoom.status = (EnMeetingRoomStatus)jintStatus;
			cppRoom.capacity = jintCapacity;
			cppRoom.shortNum = getJStringValue(env, jstrShortNum);
			cppRoom.expiredDate = getJStringValue(env, jstrExpiredDate);
			cppRoom.icon = getJStringValue(env, jstrRoomIcon);
			cppRoom.hasAdminRights = jzHasAdminRights;
		}
		env->DeleteLocalRef(jstrId);
		env->DeleteLocalRef(jstrName);
		env->DeleteLocalRef(jstrShortNum);
		env->DeleteLocalRef(jstrExpiredDate);
		env->DeleteLocalRef(jstrRoomIcon);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joParam, StJoinRoomParam &cppParam)
	{
		jclass jniJoinRoomParamClass = env->GetObjectClass(joParam);
		if (!jniJoinRoomParamClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID roomIdID = env->GetFieldID(jniJoinRoomParamClass, "roomId", JNI_jstring_SIGN);
		jfieldID passwordID = env->GetFieldID(jniJoinRoomParamClass, "password", JNI_jstring_SIGN);
		jfieldID mediaModeID = env->GetFieldID(jniJoinRoomParamClass, "mediaMode", JNI_jint_SIGN);
		jfieldID durationID = env->GetFieldID(jniJoinRoomParamClass, "duration", JNI_jint_SIGN);
		jfieldID useIdInRoomID = env->GetFieldID(jniJoinRoomParamClass, "useIdInRoom", JNI_jstring_SIGN);
		jfieldID streamTypeID = env->GetFieldID(jniJoinRoomParamClass, "streamType", JNI_jint_SIGN);
		jfieldID videoStatusID = env->GetFieldID(jniJoinRoomParamClass, "videoStatus", JNI_jboolean_SIGN);
		jfieldID audioStatusID = env->GetFieldID(jniJoinRoomParamClass, "audioStatus", JNI_jboolean_SIGN);
		jfieldID jointypeID = env->GetFieldID(jniJoinRoomParamClass, "jointype", JNI_jboolean_SIGN);
		jfieldID isReconnectedID = env->GetFieldID(jniJoinRoomParamClass, "isReconnected", JNI_jboolean_SIGN);
		jfieldID ruidID = env->GetFieldID(jniJoinRoomParamClass, "ruid", JNI_jstring_SIGN);
		jfieldID roleID = env->GetFieldID(jniJoinRoomParamClass, "role", JNI_jint_SIGN);
		jfieldID nicknameID = env->GetFieldID(jniJoinRoomParamClass, "nickname", JNI_jstring_SIGN);
		env->DeleteLocalRef(jniJoinRoomParamClass);

		jstring jstrRoomId = (jstring)env->GetObjectField(joParam, roomIdID);
		jstring jstrPassword = (jstring)env->GetObjectField(joParam, passwordID);
		jint jintMediaType = env->GetIntField(joParam, mediaModeID);
		jint jintDuration = env->GetIntField(joParam, durationID);
		jstring jstrUseIdInRoom = (jstring)env->GetObjectField(joParam, useIdInRoomID);
		jint jintStreamType = env->GetIntField(joParam, streamTypeID);
		jboolean jzVideoStatus = env->GetBooleanField(joParam, videoStatusID);
		jboolean jzAudioStatus = env->GetBooleanField(joParam, audioStatusID);
		jboolean jzJoinType = env->GetBooleanField(joParam, jointypeID);
		jboolean jzIsReconnected = env->GetBooleanField(joParam, isReconnectedID);
		jstring jstrRuId = (jstring)env->GetObjectField(joParam, ruidID);
		jint jintRole = env->GetIntField(joParam, roleID);
		jstring jstrNickname = (jstring)env->GetObjectField(joParam, nicknameID);

		{
			// set cppRoomInfo's values
			cppParam.roomId = getJStringValue(env, jstrRoomId);
			cppParam.password = getJStringValue(env, jstrPassword);
			cppParam.mediaMode = static_cast<EnMediaMode>(jintMediaType);
			cppParam.duration = jintDuration;
			cppParam.useIdInRoom = getJStringValue(env, jstrUseIdInRoom);
			cppParam.streamType = static_cast<EnStreamType>(jintStreamType);
			cppParam.videoStatus = jzVideoStatus;
			cppParam.audioStatus = jzAudioStatus;
			cppParam.joinType = jzJoinType;
			cppParam.isReconnected = jzIsReconnected;
			cppParam.ruid = getJStringValue(env, jstrRuId);
			cppParam.role = static_cast<EnRoomRole>(jintRole);
			cppParam.nickname = getJStringValue(env, jstrNickname);
		}

		env->DeleteLocalRef(jstrRoomId);
		env->DeleteLocalRef(jstrPassword);
		env->DeleteLocalRef(jstrUseIdInRoom);
		env->DeleteLocalRef(jstrRuId);
		env->DeleteLocalRef(jstrNickname);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, std::vector<OrgMemberInfo> memberList, jobject &joArrayList)
	{
		if (!joArrayList)
		{
			errorf("object is null.");
			return -1;
		}

		jclass jniOrgMemberInfoClass = env->FindClass(ORG_MEMBER_INFO_CLASS_NAME);
		if (!jniOrgMemberInfoClass)
		{
			errorf("FIND CLASS FAILED!!!");
			return -1;
		}
		jmethodID orgMemberInfoConstructorID = env->GetMethodID(jniOrgMemberInfoClass, "<init>", "()V");

		for (auto orgMember : memberList)
		{
			jobject joOrgMemberInfo = env->NewObject(jniOrgMemberInfoClass, orgMemberInfoConstructorID);

			if (JNICommon::setFieldValue(env, orgMember, joOrgMemberInfo) != 0)
			{
				errorf("setFieldValue failed.");
				continue;
			}
			else
			{
				JNICommon::addEleIntoArrayList(env, joArrayList, joOrgMemberInfo);
			}

			env->DeleteLocalRef(joOrgMemberInfo);
		}
		env->DeleteLocalRef(jniOrgMemberInfoClass);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joAppointConference, StAppointConference &cppAppointConference)
	{
		jclass jnijoAppointConferenceClass = env->GetObjectClass(joAppointConference);
		if (!jnijoAppointConferenceClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID meetingInfoID = env->GetFieldID(jnijoAppointConferenceClass, "meetingInfo", STMEETING_INFO_CLASS_SIGN);
		jfieldID meetingStatusID = env->GetFieldID(jnijoAppointConferenceClass, "meetingStatus", JNI_jint_SIGN);
		jfieldID autoCallID = env->GetFieldID(jnijoAppointConferenceClass, "autoCall", JNI_jboolean_SIGN);
		jfieldID allowParticipantJoinInAdvanceID = env->GetFieldID(jnijoAppointConferenceClass, "allowParticipantJoinInAdvance", JNI_jboolean_SIGN);
		jfieldID participantListID = env->GetFieldID(jnijoAppointConferenceClass, "participantList", JAVA_ARRAYLIST_SIGN);
		jfieldID moderatorVideoStatusID = env->GetFieldID(jnijoAppointConferenceClass, "moderatorVideoStatus", JNI_jboolean_SIGN);
		jfieldID moderatorMicStatusID = env->GetFieldID(jnijoAppointConferenceClass, "moderatorMicStatus", JNI_jboolean_SIGN);
		jfieldID participantVideoStatusID = env->GetFieldID(jnijoAppointConferenceClass, "participantVideoStatus", JNI_jboolean_SIGN);
		jfieldID participantMicStatusID = env->GetFieldID(jnijoAppointConferenceClass, "participantMicStatus", JNI_jboolean_SIGN);
		env->DeleteLocalRef(jnijoAppointConferenceClass);

		jobject joMeetingInfo = env->GetObjectField(joAppointConference, meetingInfoID);
		jint jintMeetingStatus = env->GetIntField(joAppointConference, meetingStatusID);
		jboolean jbAutoCall = env->GetBooleanField(joAppointConference, autoCallID);
		jboolean jbAllowParticipantJoinInAdvance = env->GetBooleanField(joAppointConference, allowParticipantJoinInAdvanceID);
		jobject joParticipantList = env->GetObjectField(joAppointConference, participantListID);
		jboolean jbModeratorVideoStatus = env->GetBooleanField(joAppointConference, moderatorVideoStatusID);
		jboolean jbModeratorMicStatus = env->GetBooleanField(joAppointConference, moderatorMicStatusID);
		jboolean jbParticipantVideoStatus = env->GetBooleanField(joAppointConference, participantVideoStatusID);
		jboolean jbParticipantMicStatus = env->GetBooleanField(joAppointConference, participantMicStatusID);

		{
			getFieldValue(env, joMeetingInfo, cppAppointConference.meetingInfo);
			cppAppointConference.meetingStatus = (EnMeetingStatus)jintMeetingStatus;
			cppAppointConference.autoCall = jbAutoCall;
			cppAppointConference.allowParticipantJoinInAdvance = jbAllowParticipantJoinInAdvance;
			getFieldArrayValue(env, joParticipantList, cppAppointConference.participantList);
			cppAppointConference.moderatorVideoStatus = jbModeratorVideoStatus;
			cppAppointConference.moderatorMicStatus = jbModeratorMicStatus;
			cppAppointConference.participantVideoStatus = jbParticipantVideoStatus;
			cppAppointConference.participantMicStatus = jbParticipantMicStatus;
		}

		env->DeleteLocalRef(joMeetingInfo);
		env->DeleteLocalRef(joParticipantList);
		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StAppointConference cppAppointConference, jobject &joAppointConference)
	{
		jclass jnijoAppointConferenceClass = env->GetObjectClass(joAppointConference);
		if (!jnijoAppointConferenceClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID meetingInfoID = env->GetFieldID(jnijoAppointConferenceClass, "meetingInfo", STMEETING_INFO_CLASS_SIGN);
		jfieldID meetingStatusID = env->GetFieldID(jnijoAppointConferenceClass, "meetingStatus", JNI_jint_SIGN);
		jfieldID autoCallID = env->GetFieldID(jnijoAppointConferenceClass, "autoCall", JNI_jboolean_SIGN);
		jfieldID allowParticipantJoinInAdvanceID = env->GetFieldID(jnijoAppointConferenceClass, "allowParticipantJoinInAdvance", JNI_jboolean_SIGN);
		jfieldID participantListID = env->GetFieldID(jnijoAppointConferenceClass, "participantList", JAVA_ARRAYLIST_SIGN);
		jfieldID moderatorVideoStatusID = env->GetFieldID(jnijoAppointConferenceClass, "moderatorVideoStatus", JNI_jboolean_SIGN);
		jfieldID moderatorMicStatusID = env->GetFieldID(jnijoAppointConferenceClass, "moderatorMicStatus", JNI_jboolean_SIGN);
		jfieldID participantVideoStatusID = env->GetFieldID(jnijoAppointConferenceClass, "participantVideoStatus", JNI_jboolean_SIGN);
		jfieldID participantMicStatusID = env->GetFieldID(jnijoAppointConferenceClass, "participantMicStatus", JNI_jboolean_SIGN);
		env->DeleteLocalRef(jnijoAppointConferenceClass);

		{
			jobject joMeetingInfo = env->GetObjectField(joAppointConference, meetingInfoID);
			setFieldValue(env, cppAppointConference.meetingInfo, joMeetingInfo);
			env->SetIntField(joAppointConference, meetingStatusID, static_cast<int>(cppAppointConference.meetingStatus));
			env->SetBooleanField(joAppointConference, autoCallID, cppAppointConference.autoCall);
			env->SetBooleanField(joAppointConference, allowParticipantJoinInAdvanceID, cppAppointConference.allowParticipantJoinInAdvance);
			jobject joParticipantList = env->GetObjectField(joAppointConference, participantListID);
			setFieldArrayValue(env, cppAppointConference.participantList, USER_INFO_CLASS_NAME, joParticipantList);
			env->SetBooleanField(joAppointConference, moderatorVideoStatusID, cppAppointConference.moderatorVideoStatus);
			env->SetBooleanField(joAppointConference, moderatorMicStatusID, cppAppointConference.moderatorMicStatus);
			env->SetBooleanField(joAppointConference, participantVideoStatusID, cppAppointConference.participantVideoStatus);
			env->SetBooleanField(joAppointConference, participantMicStatusID, cppAppointConference.participantMicStatus);

			env->DeleteLocalRef(joMeetingInfo);
			env->DeleteLocalRef(joParticipantList);
		}

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StCompanyInfo cppCompanyInfo, jobject &joCompanyInfo)
	{
		jclass jniCompanyInfoClass = env->GetObjectClass(joCompanyInfo);
		if (!jniCompanyInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID nameID = env->GetFieldID(jniCompanyInfoClass, "name", JNI_jstring_SIGN);
		jfieldID codeID = env->GetFieldID(jniCompanyInfoClass, "code", JNI_jstring_SIGN);
		jfieldID randomRoomCapacityID = env->GetFieldID(jniCompanyInfoClass, "randomRoomCapacity", JNI_jint_SIGN);
		jfieldID isExpiredID = env->GetFieldID(jniCompanyInfoClass, "isExpired", JNI_jboolean_SIGN);
		jfieldID expireDateID = env->GetFieldID(jniCompanyInfoClass, "expireDate", JNI_jstring_SIGN);
		jfieldID daysToExpiredDateID = env->GetFieldID(jniCompanyInfoClass, "daysToExpiredDate", JNI_jint_SIGN);
		jfieldID surplusConversationHoursID = env->GetFieldID(jniCompanyInfoClass, "surplusConversationHours", JNI_jint_SIGN);
		jfieldID surplusConversationMinsID = env->GetFieldID(jniCompanyInfoClass, "surplusConversationMins", JNI_jint_SIGN);
		jfieldID surplusConversationDurationID = env->GetFieldID(jniCompanyInfoClass, "surplusConversationDuration", JNI_jint_SIGN);
		jfieldID cloudRecordUsedSpaceID = env->GetFieldID(jniCompanyInfoClass, "cloudRecordUsedSpace", JNI_jstring_SIGN);
		jfieldID cloudRecordTotalSpaceID = env->GetFieldID(jniCompanyInfoClass, "cloudRecordTotalSpace", JNI_jstring_SIGN);
		jfieldID fixedMeetingRoomCountID = env->GetFieldID(jniCompanyInfoClass, "fixedMeetingRoomCount", JNI_jint_SIGN);
		env->DeleteLocalRef(jniCompanyInfoClass);

		jstring jstrName = env->NewStringUTF(cppCompanyInfo.name.c_str());
		jstring jstrCode = env->NewStringUTF(cppCompanyInfo.code.c_str());
		jstring jstrExpireDate = env->NewStringUTF(cppCompanyInfo.expireDate.c_str());
		jstring jstrCloudRecordUsedSpace = env->NewStringUTF(cppCompanyInfo.cloudRecordUsedSpace.c_str());
		jstring jstrCloudRecordTotalSpace = env->NewStringUTF(cppCompanyInfo.cloudRecordTotalSpace.c_str());

		env->SetObjectField(joCompanyInfo, nameID, jstrName);
		env->SetObjectField(joCompanyInfo, codeID, jstrCode);
		env->SetIntField(joCompanyInfo, randomRoomCapacityID, cppCompanyInfo.randomRoomCapacity);
		env->SetBooleanField(joCompanyInfo, isExpiredID, cppCompanyInfo.isExpired);
		env->SetObjectField(joCompanyInfo, expireDateID, jstrExpireDate);
		env->SetIntField(joCompanyInfo, daysToExpiredDateID, cppCompanyInfo.daysToExpiredDate);
		env->SetIntField(joCompanyInfo, surplusConversationHoursID, cppCompanyInfo.surplusConversationHours);
		env->SetIntField(joCompanyInfo, surplusConversationMinsID, cppCompanyInfo.surplusConversationMins);
		env->SetIntField(joCompanyInfo, surplusConversationDurationID, cppCompanyInfo.surplusConversationDuration);
		env->SetObjectField(joCompanyInfo, cloudRecordUsedSpaceID, jstrCloudRecordUsedSpace);
		env->SetObjectField(joCompanyInfo, cloudRecordTotalSpaceID, jstrCloudRecordTotalSpace);
		env->SetIntField(joCompanyInfo, fixedMeetingRoomCountID, cppCompanyInfo.fixedMeetingRoomCount);

		env->DeleteLocalRef(jstrName);
		env->DeleteLocalRef(jstrCode);
		env->DeleteLocalRef(jstrExpireDate);
		env->DeleteLocalRef(jstrCloudRecordUsedSpace);
		env->DeleteLocalRef(jstrCloudRecordTotalSpace);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StIceServerInfo cppIceServerInfo, jobject &joIceServerInfo)
	{
		jclass jniIceServerInfoClass = env->GetObjectClass(joIceServerInfo);
		if (!jniIceServerInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID typeID = env->GetFieldID(jniIceServerInfoClass, "type", JNI_jint_SIGN);
		jfieldID hostID = env->GetFieldID(jniIceServerInfoClass, "host", JNI_jstring_SIGN);
		jfieldID portID = env->GetFieldID(jniIceServerInfoClass, "port", JNI_jint_SIGN);
		jfieldID usernameID = env->GetFieldID(jniIceServerInfoClass, "username", JNI_jstring_SIGN);
		jfieldID passwordID = env->GetFieldID(jniIceServerInfoClass, "password", JNI_jstring_SIGN);
		env->DeleteLocalRef(jniIceServerInfoClass);

		jstring jstrHost = env->NewStringUTF(cppIceServerInfo.host.c_str());
		jstring jstrUsername = env->NewStringUTF(cppIceServerInfo.username.c_str());
		jstring jstrPassword = env->NewStringUTF(cppIceServerInfo.password.c_str());

		env->SetIntField(joIceServerInfo, typeID, (int)cppIceServerInfo.type);
		env->SetObjectField(joIceServerInfo, hostID, jstrHost);
		env->SetIntField(joIceServerInfo, portID, cppIceServerInfo.port);
		env->SetObjectField(joIceServerInfo, usernameID, jstrUsername);
		env->SetObjectField(joIceServerInfo, passwordID, jstrPassword);

		env->DeleteLocalRef(jstrHost);
		env->DeleteLocalRef(jstrUsername);
		env->DeleteLocalRef(jstrPassword);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joServerInfo, ServerInfo &cppServerInfo)
	{
		jclass serverInfoClass = env->GetObjectClass(joServerInfo);
		if (!serverInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID isProxyID = env->GetFieldID(serverInfoClass, "isProxy", JNI_jboolean_SIGN);
		jfieldID hostID = env->GetFieldID(serverInfoClass, "host", JNI_jstring_SIGN);
		jfieldID httpPortID = env->GetFieldID(serverInfoClass, "httpPort", JNI_jint_SIGN);
		jfieldID httpsPortID = env->GetFieldID(serverInfoClass, "httpsPort", JNI_jint_SIGN);
		env->DeleteLocalRef(serverInfoClass);

		jboolean jzIsProxy = env->GetBooleanField(joServerInfo, isProxyID);
		jstring jstrHost = (jstring)env->GetObjectField(joServerInfo, hostID);
		jint jiHttpPort = env->GetIntField(joServerInfo, httpPortID);
		jint jiHttpsPort = env->GetIntField(joServerInfo, httpsPortID);
		const char *cppHost = env->GetStringUTFChars(jstrHost, NULL);

		cppServerInfo.isProxy = jzIsProxy;
		cppServerInfo.host = cppHost;
		cppServerInfo.httpPort = jiHttpPort;
		cppServerInfo.httpsPort = jiHttpsPort;

		env->ReleaseStringUTFChars(jstrHost, cppHost);
		env->DeleteLocalRef(jstrHost);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, ServerInfo cppServerInfo, jobject &joServerInfo)
	{
		jclass serverInfoClass = env->GetObjectClass(joServerInfo);
		if (!serverInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID isProxyID = env->GetFieldID(serverInfoClass, "isProxy", JNI_jboolean_SIGN);
		jfieldID hostID = env->GetFieldID(serverInfoClass, "host", JNI_jstring_SIGN);
		jfieldID httpPortID = env->GetFieldID(serverInfoClass, "httpPort", JNI_jint_SIGN);
		jfieldID httpsPortID = env->GetFieldID(serverInfoClass, "httpsPort", JNI_jint_SIGN);
		env->DeleteLocalRef(serverInfoClass);

		jstring jstrHost = env->NewStringUTF(cppServerInfo.host.c_str());

		env->SetBooleanField(joServerInfo, isProxyID, cppServerInfo.isProxy);
		env->SetObjectField(joServerInfo, hostID, jstrHost);
		env->SetIntField(joServerInfo, httpPortID, cppServerInfo.httpPort);
		env->SetIntField(joServerInfo, httpsPortID, cppServerInfo.httpsPort);

		env->DeleteLocalRef(jstrHost);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joBasicInfo, BasicInfo &cppBasicInfo)
	{
		jclass basicInfoClass = env->GetObjectClass(joBasicInfo);
		if (!basicInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID serverInfosID = env->GetFieldID(basicInfoClass, "serverInfos", JAVA_ARRAYLIST_SIGN);
		jfieldID terminalTypeID = env->GetFieldID(basicInfoClass, "terminalType", JNI_jint_SIGN);
		jfieldID deviceModelID = env->GetFieldID(basicInfoClass, "deviceModel", JNI_jstring_SIGN);
		jfieldID localInfoID = env->GetFieldID(basicInfoClass, "localInfo", TERMINAL_LOCAL_INFO_CLASS_SIGN);
		jfieldID udidID = env->GetFieldID(basicInfoClass, "udid", JNI_jstring_SIGN);
		jfieldID macAddrID = env->GetFieldID(basicInfoClass, "macAddr", JNI_jstring_SIGN);
		jfieldID appVersionID = env->GetFieldID(basicInfoClass, "appVersion", JNI_jstring_SIGN);
		jfieldID appVersionCodeID = env->GetFieldID(basicInfoClass, "appVersionCode", JNI_jstring_SIGN);
		jfieldID serialNumberID = env->GetFieldID(basicInfoClass, "serialNumber", JNI_jstring_SIGN);
		jfieldID projectID = env->GetFieldID(basicInfoClass, "project", JNI_jstring_SIGN);
		jfieldID appKeyID = env->GetFieldID(basicInfoClass, "appKey", JNI_jstring_SIGN);
		env->DeleteLocalRef(basicInfoClass);

		jobject joServerInfos = env->GetObjectField(joBasicInfo, serverInfosID);
		jint jiTerminalType = env->GetIntField(joBasicInfo, terminalTypeID);
		jstring jstrDeviceModel = (jstring)env->GetObjectField(joBasicInfo, deviceModelID);
		jobject joLocalInfo = env->GetObjectField(joBasicInfo, localInfoID);
		jstring jstrUdid = (jstring)env->GetObjectField(joBasicInfo, udidID);
		jstring jstrMacAddr = (jstring)env->GetObjectField(joBasicInfo, macAddrID);
		jstring jstrAppVersion = (jstring)env->GetObjectField(joBasicInfo, appVersionID);
		jstring jstrAppVersionCode = (jstring)env->GetObjectField(joBasicInfo, appVersionCodeID);
		jstring jstrSerialNumber = (jstring)env->GetObjectField(joBasicInfo, serialNumberID);
		jstring jstrProject = (jstring)env->GetObjectField(joBasicInfo, projectID);
		jstring jstrAppKey = (jstring)env->GetObjectField(joBasicInfo, appKeyID);

		{
			JNICommon::getFieldArrayValue<ServerInfo>(env, joServerInfos, cppBasicInfo.serverInfos);
			cppBasicInfo.terminalType = (EnTerminalType)jiTerminalType;
			cppBasicInfo.deviceModel = JNICommon::getJStringValue(env, jstrDeviceModel);
			cppBasicInfo.udid = JNICommon::getJStringValue(env, jstrUdid);
			cppBasicInfo.macAddr = JNICommon::getJStringValue(env, jstrMacAddr);
			cppBasicInfo.appVersion = JNICommon::getJStringValue(env, jstrAppVersion);
			cppBasicInfo.appVersionCode = JNICommon::getJStringValue(env, jstrAppVersionCode);
			cppBasicInfo.serialNumber = JNICommon::getJStringValue(env, jstrSerialNumber);
			cppBasicInfo.project = JNICommon::getJStringValue(env, jstrProject);
			cppBasicInfo.appKey = JNICommon::getJStringValue(env, jstrAppKey);
			

			getFieldValue(env, joLocalInfo, cppBasicInfo.localInfo);
		}

		env->DeleteLocalRef(joServerInfos);
		env->DeleteLocalRef(jstrDeviceModel);
		env->DeleteLocalRef(joLocalInfo);
		env->DeleteLocalRef(jstrUdid);
		env->DeleteLocalRef(jstrMacAddr);
		env->DeleteLocalRef(jstrAppVersion);
		env->DeleteLocalRef(jstrAppVersionCode);
		env->DeleteLocalRef(jstrSerialNumber);
		env->DeleteLocalRef(jstrProject);
		env->DeleteLocalRef(jstrAppKey);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, BasicInfo cppBasicRoomInfo, jobject &joBasicInfo)
	{
		jclass basicInfoClass = env->GetObjectClass(joBasicInfo);
		if (!basicInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID serverInfosID = env->GetFieldID(basicInfoClass, "serverInfos", JAVA_ARRAYLIST_SIGN);
		jfieldID terminalTypeID = env->GetFieldID(basicInfoClass, "terminalType", JNI_jint_SIGN);
		jfieldID deviceModelID = env->GetFieldID(basicInfoClass, "deviceModel", JNI_jstring_SIGN);
		jfieldID localInfoID = env->GetFieldID(basicInfoClass, "localInfo", TERMINAL_LOCAL_INFO_CLASS_SIGN);
		jfieldID udidID = env->GetFieldID(basicInfoClass, "udid", JNI_jstring_SIGN);
		jfieldID macAddrID = env->GetFieldID(basicInfoClass, "macAddr", JNI_jstring_SIGN);
		jfieldID appVersionID = env->GetFieldID(basicInfoClass, "appVersion", JNI_jstring_SIGN);
		jfieldID appVersionCodeID = env->GetFieldID(basicInfoClass, "appVersionCode", JNI_jstring_SIGN);
		jfieldID serialNumberID = env->GetFieldID(basicInfoClass, "serialNumber", JNI_jstring_SIGN);
		jfieldID projectID = env->GetFieldID(basicInfoClass, "project", JNI_jstring_SIGN);
		jfieldID appKeyID = env->GetFieldID(basicInfoClass, "appKey", JNI_jstring_SIGN);

		env->DeleteLocalRef(basicInfoClass);

		jobject joServerInfos = env->GetObjectField(joBasicInfo, serverInfosID);
		setFieldArrayValue(env, cppBasicRoomInfo.serverInfos, SERVER_INFO_CLASS_NAME, joServerInfos);

		jobject joLocalInfo = env->GetObjectField(joBasicInfo, localInfoID);
		setFieldValue(env, cppBasicRoomInfo.localInfo, joLocalInfo);

		jstring jstrDeviceModel = env->NewStringUTF(cppBasicRoomInfo.deviceModel.c_str());
		jstring jstrUdid = env->NewStringUTF(cppBasicRoomInfo.udid.c_str());
		jstring jstrMacAddr = env->NewStringUTF(cppBasicRoomInfo.macAddr.c_str());
		jstring jstrAppVersion = env->NewStringUTF(cppBasicRoomInfo.appVersion.c_str());
		jstring jstrAppVersionCode = env->NewStringUTF(cppBasicRoomInfo.appVersionCode.c_str());
		jstring jstrSerialNumber = env->NewStringUTF(cppBasicRoomInfo.serialNumber.c_str());
		jstring jstrProject = env->NewStringUTF(cppBasicRoomInfo.project.c_str());
		jstring jstrAppKey = env->NewStringUTF(cppBasicRoomInfo.appKey.c_str());

		env->SetObjectField(joBasicInfo, serverInfosID, joServerInfos);
		env->SetIntField(joBasicInfo, terminalTypeID, cppBasicRoomInfo.terminalType);
		env->SetObjectField(joBasicInfo, deviceModelID, jstrDeviceModel);
		env->SetObjectField(joBasicInfo, udidID, jstrUdid);
		env->SetObjectField(joBasicInfo, macAddrID, jstrMacAddr);
		env->SetObjectField(joBasicInfo, appVersionID, jstrAppVersion);
		env->SetObjectField(joBasicInfo, appVersionCodeID, jstrAppVersionCode);
		env->SetObjectField(joBasicInfo, serialNumberID, jstrSerialNumber);
		env->SetObjectField(joBasicInfo, projectID, jstrProject);
		env->SetObjectField(joBasicInfo, appKeyID, jstrAppKey);

		env->DeleteLocalRef(joServerInfos);
		env->DeleteLocalRef(joLocalInfo);
		env->DeleteLocalRef(jstrDeviceModel);
		env->DeleteLocalRef(jstrUdid);
		env->DeleteLocalRef(jstrMacAddr);
		env->DeleteLocalRef(jstrAppVersion);
		env->DeleteLocalRef(jstrAppVersionCode);
		env->DeleteLocalRef(jstrSerialNumber);
		env->DeleteLocalRef(jstrProject);
		env->DeleteLocalRef(jstrAppKey);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joInfo, StTerminalLocalInfo &cppInfo)
	{
		jclass terminalLocalInfoClass = env->GetObjectClass(joInfo);
		if (!terminalLocalInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID abilityID = env->GetFieldID(terminalLocalInfoClass, "ability", JNI_jstring_SIGN);
		jfieldID functionalityID = env->GetFieldID(terminalLocalInfoClass, "functionality", JNI_jstring_SIGN);
		env->DeleteLocalRef(terminalLocalInfoClass);

		jstring jstrAbility = (jstring)env->GetObjectField(joInfo, abilityID);
		jstring jstrFunctionality = (jstring)env->GetObjectField(joInfo, functionalityID);

		cppInfo.ability = getJStringValue(env, jstrAbility);
		cppInfo.functionality = getJStringValue(env, jstrFunctionality);

		env->DeleteLocalRef(jstrAbility);
		env->DeleteLocalRef(jstrFunctionality);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StTerminalLocalInfo cppInfo, jobject &joInfo)
	{
		jclass terminalLocalInfoClass = env->GetObjectClass(joInfo);
		if (!terminalLocalInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID abilityID = env->GetFieldID(terminalLocalInfoClass, "ability", JNI_jstring_SIGN);
		jfieldID functionalityID = env->GetFieldID(terminalLocalInfoClass, "functionality", JNI_jstring_SIGN);
		env->DeleteLocalRef(terminalLocalInfoClass);

		jstring jstrAbility = env->NewStringUTF(cppInfo.ability.c_str());
		jstring jstrFunctionality = env->NewStringUTF(cppInfo.functionality.c_str());

		env->SetObjectField(joInfo, abilityID, jstrAbility);
		env->SetObjectField(joInfo, functionalityID, jstrFunctionality);

		env->DeleteLocalRef(jstrAbility);
		env->DeleteLocalRef(jstrFunctionality);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StUnfinishedRoomInfo cppRoomInfo, jobject &joRoomInfo)
	{
		jclass jniUnfinishedRoomInfoClass = env->GetObjectClass(joRoomInfo);
		if (!jniUnfinishedRoomInfoClass)
		{
			errorf("FIND CLASS FAILED!!!");
			return -1;
		}
		jfieldID roomIdID = env->GetFieldID(jniUnfinishedRoomInfoClass, "roomId", JNI_jstring_SIGN);
		jfieldID hostAccountID = env->GetFieldID(jniUnfinishedRoomInfoClass, "hostAccount", JNI_jstring_SIGN);
		jfieldID passwordID = env->GetFieldID(jniUnfinishedRoomInfoClass, "password", JNI_jstring_SIGN);
		jfieldID subjectID = env->GetFieldID(jniUnfinishedRoomInfoClass, "subject", JNI_jstring_SIGN);
		jfieldID remainTimeID = env->GetFieldID(jniUnfinishedRoomInfoClass, "remainTime", JNI_jint_SIGN);
		jfieldID roleID = env->GetFieldID(jniUnfinishedRoomInfoClass, "role", JNI_jint_SIGN);
		jfieldID audioOutStatusID = env->GetFieldID(jniUnfinishedRoomInfoClass, "audioOutStatus", JNI_jboolean_SIGN);
		jfieldID audioInStatusID = env->GetFieldID(jniUnfinishedRoomInfoClass, "audioInStatus", JNI_jboolean_SIGN);
		jfieldID videoStatusID = env->GetFieldID(jniUnfinishedRoomInfoClass, "videoStatus", JNI_jboolean_SIGN);
		jfieldID shareStatusID = env->GetFieldID(jniUnfinishedRoomInfoClass, "shareStatus", JNI_jboolean_SIGN);
		jfieldID handStatusID = env->GetFieldID(jniUnfinishedRoomInfoClass, "handStatus", JNI_jboolean_SIGN);
		jfieldID speakStatusID = env->GetFieldID(jniUnfinishedRoomInfoClass, "speakStatus", JNI_jboolean_SIGN);
		jfieldID orderID = env->GetFieldID(jniUnfinishedRoomInfoClass, "order", JNI_jint_SIGN);
		env->DeleteLocalRef(jniUnfinishedRoomInfoClass);

		jstring jstrRoomId = env->NewStringUTF(cppRoomInfo.roomId.c_str());
		jstring jstrHostAccount = env->NewStringUTF(cppRoomInfo.hostAccount.c_str());
		jstring jstrPassword = env->NewStringUTF(cppRoomInfo.password.c_str());
		jstring jstrSubject = env->NewStringUTF(cppRoomInfo.subject.c_str());

		env->SetObjectField(joRoomInfo, roomIdID, jstrRoomId);
		env->SetObjectField(joRoomInfo, hostAccountID, jstrHostAccount);
		env->SetObjectField(joRoomInfo, passwordID, jstrPassword);
		env->SetObjectField(joRoomInfo, subjectID, jstrSubject);
		env->SetIntField(joRoomInfo, remainTimeID, cppRoomInfo.remainTime);
		env->SetIntField(joRoomInfo, roleID, cppRoomInfo.role);
		env->SetBooleanField(joRoomInfo, audioOutStatusID, cppRoomInfo.audioOutStatus);
		env->SetBooleanField(joRoomInfo, audioInStatusID, cppRoomInfo.audioInStatus);
		env->SetBooleanField(joRoomInfo, videoStatusID, cppRoomInfo.videoStatus);
		env->SetBooleanField(joRoomInfo, shareStatusID, cppRoomInfo.shareStatus);
		env->SetBooleanField(joRoomInfo, handStatusID, cppRoomInfo.handStatus);
		env->SetBooleanField(joRoomInfo, speakStatusID, cppRoomInfo.speakStatus);
		env->SetIntField(joRoomInfo, orderID, cppRoomInfo.order);

		env->DeleteLocalRef(jstrRoomId);
		env->DeleteLocalRef(jstrHostAccount);
		env->DeleteLocalRef(jstrPassword);
		env->DeleteLocalRef(jstrSubject);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joNetworkQuality, StNetworkQuality &cppNetworkQuality)
	{
		jclass networkQualityClass = env->GetObjectClass(joNetworkQuality);
		if (!networkQualityClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID uploadBandwidthID = env->GetFieldID(networkQualityClass, "uploadBandwidth", JNI_jstring_SIGN);
		jfieldID downloadBandwidthID = env->GetFieldID(networkQualityClass, "downloadBandwidth", JNI_jstring_SIGN);
		jfieldID delayID = env->GetFieldID(networkQualityClass, "delay", JNI_jint_SIGN);
		env->DeleteLocalRef(networkQualityClass);

		jstring jstrUploadBandwidth = (jstring)env->GetObjectField(joNetworkQuality, uploadBandwidthID);
		jstring jstrDownloadBandwidth = (jstring)env->GetObjectField(joNetworkQuality, downloadBandwidthID);
		jint jintDelay = env->GetIntField(joNetworkQuality, delayID);

		cppNetworkQuality.uploadBandwidth = getJStringValue(env, jstrUploadBandwidth);
		cppNetworkQuality.downloadBandwidth = getJStringValue(env, jstrDownloadBandwidth);
		cppNetworkQuality.delay = jintDelay;

		env->DeleteLocalRef(jstrUploadBandwidth);
		env->DeleteLocalRef(jstrDownloadBandwidth);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joStreamQuality, StStreamQuality &cppStreamQuality)
	{
		jclass streamQualityClass = env->GetObjectClass(joStreamQuality);
		if (!streamQualityClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID typeID = env->GetFieldID(streamQualityClass, "type", JNI_jint_SIGN);
		jfieldID resolutionID = env->GetFieldID(streamQualityClass, "resolution", JNI_jstring_SIGN);
		jfieldID videoBitRateID = env->GetFieldID(streamQualityClass, "videoBitRate", JNI_jstring_SIGN);
		jfieldID audioBitRateID = env->GetFieldID(streamQualityClass, "audioBitRate", JNI_jstring_SIGN);
		jfieldID fpsID = env->GetFieldID(streamQualityClass, "fps", JNI_jint_SIGN);
		jfieldID videoPacketLostRateID = env->GetFieldID(streamQualityClass, "videoPacketLostRate", JNI_jdouble_SIGN);
		jfieldID audioPacketLostRateID = env->GetFieldID(streamQualityClass, "audioPacketLostRate", JNI_jdouble_SIGN);
		env->DeleteLocalRef(streamQualityClass);

		jint jintType = env->GetIntField(joStreamQuality, typeID);
		jstring jstrResolution = (jstring)env->GetObjectField(joStreamQuality, resolutionID);
		jstring jstrVideoBitRate = (jstring)env->GetObjectField(joStreamQuality, videoBitRateID);
		jstring jstrAudioBitRate = (jstring)env->GetObjectField(joStreamQuality, audioBitRateID);
		jint jintFps = env->GetIntField(joStreamQuality, fpsID);
		jdouble jdVideoPackageLostRate = env->GetDoubleField(joStreamQuality, videoPacketLostRateID);
		jdouble jdAudioPackageLostRate = env->GetDoubleField(joStreamQuality, audioPacketLostRateID);

		cppStreamQuality.type = static_cast<EnStreamType>(jintType);
		cppStreamQuality.resolution = getJStringValue(env, jstrResolution);
		cppStreamQuality.videoBitRate = getJStringValue(env, jstrVideoBitRate);
		cppStreamQuality.audioBitRate = getJStringValue(env, jstrVideoBitRate);
		cppStreamQuality.fps = jintFps;
		cppStreamQuality.videoPacketLostRate = jdVideoPackageLostRate;
		cppStreamQuality.audioPacketLostRate = jdAudioPackageLostRate;

		env->DeleteLocalRef(jstrResolution);
		env->DeleteLocalRef(jstrVideoBitRate);
		env->DeleteLocalRef(jstrAudioBitRate);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StHardTerminalDeviceInfo deviceInfo, jobject &joDeviceInfo)
	{
		jclass jniDeviceInfoClass = env->GetObjectClass(joDeviceInfo);
		if (!jniDeviceInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID nickNameID = env->GetFieldID(jniDeviceInfoClass, "nickName", "Ljava/lang/String;");
		env->DeleteLocalRef(jniDeviceInfoClass);

		jstring jstrNickName = env->NewStringUTF(deviceInfo.nickName.c_str());

		env->SetObjectField(joDeviceInfo, nickNameID, jstrNickName);

		env->DeleteLocalRef(jstrNickName);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joBarrage, StBarrage &cppBarrage)
	{
		jclass jniBarrageClass = env->GetObjectClass(joBarrage);
		if (!jniBarrageClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID contentID = env->GetFieldID(jniBarrageClass, "content", JNI_jstring_SIGN);
		jfieldID positionID = env->GetFieldID(jniBarrageClass, "position", JNI_jint_SIGN);
		jfieldID displayModeID = env->GetFieldID(jniBarrageClass, "displayMode", JNI_jint_SIGN);
		jfieldID fontSizeID = env->GetFieldID(jniBarrageClass, "fontSize", JNI_jint_SIGN);
		jfieldID bgColorID = env->GetFieldID(jniBarrageClass, "bgColor", JNI_jstring_SIGN);
		jfieldID opacityID = env->GetFieldID(jniBarrageClass, "opacity", JNI_jfloat_SIGN);
		env->DeleteLocalRef(jniBarrageClass);

		jstring jstrContent = (jstring)env->GetObjectField(joBarrage, contentID);
		jint jintPosition = env->GetIntField(joBarrage, positionID);
		jint jintDisplayMode = env->GetIntField(joBarrage, displayModeID);
		jint jintFontSize = env->GetIntField(joBarrage, fontSizeID);
		jstring jstrBgColor = (jstring)env->GetObjectField(joBarrage, bgColorID);
		jfloat jfOpacity = env->GetFloatField(joBarrage, opacityID);

		cppBarrage.content = getJStringValue(env, jstrContent);
		cppBarrage.position = static_cast<StBarrage::EnPosition>(jintPosition);
		cppBarrage.displayMode = static_cast<StBarrage::EnDisplayMode>(jintDisplayMode);
		cppBarrage.fontSize = static_cast<StBarrage::EnFontSize>(jintFontSize);
		cppBarrage.bgColor = getJStringValue(env, jstrBgColor);
		cppBarrage.opacity = jfOpacity;

		env->DeleteLocalRef(jstrContent);
		env->DeleteLocalRef(jstrBgColor);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StBarrage cppBarrage, jobject &joBarrage)
	{
		jclass jniBarrageClass = env->GetObjectClass(joBarrage);
		if (!jniBarrageClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID contentID = env->GetFieldID(jniBarrageClass, "content", JNI_jstring_SIGN);
		jfieldID positionID = env->GetFieldID(jniBarrageClass, "position", JNI_jint_SIGN);
		jfieldID displayModeID = env->GetFieldID(jniBarrageClass, "displayMode", JNI_jint_SIGN);
		jfieldID fontSizeID = env->GetFieldID(jniBarrageClass, "fontSize", JNI_jint_SIGN);
		jfieldID bgColorID = env->GetFieldID(jniBarrageClass, "bgColor", JNI_jstring_SIGN);
		jfieldID opacityID = env->GetFieldID(jniBarrageClass, "opacity", JNI_jfloat_SIGN);
		env->DeleteLocalRef(jniBarrageClass);

		jstring jstrContent = env->NewStringUTF(cppBarrage.content.c_str());
		jstring jstrBgColor = env->NewStringUTF(cppBarrage.bgColor.c_str());

		env->SetObjectField(joBarrage, contentID, jstrContent);
		env->SetIntField(joBarrage, positionID, static_cast<int>(cppBarrage.position));
		env->SetIntField(joBarrage, displayModeID, static_cast<int>(cppBarrage.displayMode));
		env->SetIntField(joBarrage, fontSizeID, static_cast<int>(cppBarrage.fontSize));
		env->SetObjectField(joBarrage, bgColorID, jstrBgColor);
		env->SetFloatField(joBarrage, opacityID, static_cast<float>(cppBarrage.opacity));

		env->DeleteLocalRef(jstrContent);
		env->DeleteLocalRef(jstrBgColor);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joMessage, StIMMessage &cppMessage)
	{
		jclass jniIMMessageClass = env->GetObjectClass(joMessage);
		if (!jniIMMessageClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID isResendID = env->GetFieldID(jniIMMessageClass, "isResend", JNI_jboolean_SIGN);
		jfieldID targetID = env->GetFieldID(jniIMMessageClass, "target", JNI_jint_SIGN);
		jfieldID idID = env->GetFieldID(jniIMMessageClass, "id", JNI_jlong_SIGN);
		jfieldID timestampID = env->GetFieldID(jniIMMessageClass, "timestamp", JNI_jlong_SIGN);
		jfieldID msgTypeID = env->GetFieldID(jniIMMessageClass, "msgType", JNI_jint_SIGN);
		jfieldID contentID = env->GetFieldID(jniIMMessageClass, "content", JNI_jstring_SIGN);
		jfieldID receiversID = env->GetFieldID(jniIMMessageClass, "receivers", JAVA_ARRAYLIST_SIGN);
		jfieldID atUsersID = env->GetFieldID(jniIMMessageClass, "atUsers", JAVA_ARRAYLIST_SIGN);
		jfieldID senderID = env->GetFieldID(jniIMMessageClass, "sender", STPARTICIPANTINFO_INFO_CLASS_SIGN);
		jfieldID sendStatusID = env->GetFieldID(jniIMMessageClass, "sendStatus", JNI_jint_SIGN);
		jfieldID extraDataID = env->GetFieldID(jniIMMessageClass, "extraData", JNI_jstring_SIGN);
		env->DeleteLocalRef(jniIMMessageClass);

		jboolean jbIsResend = env->GetBooleanField(joMessage, isResendID);
		jint jintTarget = env->GetIntField(joMessage, targetID);
		jlong jlId = env->GetLongField(joMessage, idID);
		jlong jlTimestamp = env->GetLongField(joMessage, timestampID);
		jint jintMsgType = env->GetIntField(joMessage, msgTypeID);
		jstring jstrContent = (jstring)env->GetObjectField(joMessage, contentID);
		jobject joReceivers = env->GetObjectField(joMessage, receiversID);
		jobject joAtUsers = env->GetObjectField(joMessage, atUsersID);
		jobject joSender = env->GetObjectField(joMessage, senderID);
		jint jintSendStatus = env->GetIntField(joMessage, sendStatusID);
		jstring jstrExtraData = (jstring)env->GetObjectField(joMessage, extraDataID);

		cppMessage.isResend = jbIsResend;
		cppMessage.target = static_cast<StIMMessage::EnIMMessageTarget>(jintTarget);
		cppMessage.id = jlId;
		cppMessage.timestamp = jlTimestamp;
		cppMessage.msgType = static_cast<StIMMessage::EnIMMessageType>(jintMsgType);
		cppMessage.content = getJStringValue(env, jstrContent);
		JNICommon::getFieldArrayValue<StParticipantInfo>(env, joReceivers, cppMessage.receivers);
		JNICommon::getFieldArrayValue<StParticipantInfo>(env, joAtUsers, cppMessage.atUsers);
		JNICommon::getFieldValue(env, joSender, cppMessage.sender);
		cppMessage.sendStatus = static_cast<StIMMessage::EnIMMessageSendStatus>(jintSendStatus);
		cppMessage.extraData = getJStringValue(env, jstrExtraData);

		env->DeleteLocalRef(jstrContent);
		env->DeleteLocalRef(joReceivers);
		env->DeleteLocalRef(joAtUsers);
		env->DeleteLocalRef(joSender);
		env->DeleteLocalRef(jstrExtraData);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StIMMessage cppMessage, jobject &joMessage)
	{
		jclass jniIMMessageClass = env->GetObjectClass(joMessage);
		if (!jniIMMessageClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID isResendID = env->GetFieldID(jniIMMessageClass, "isResend", JNI_jboolean_SIGN);
		jfieldID targetID = env->GetFieldID(jniIMMessageClass, "target", JNI_jint_SIGN);
		jfieldID idID = env->GetFieldID(jniIMMessageClass, "id", JNI_jlong_SIGN);
		jfieldID timestampID = env->GetFieldID(jniIMMessageClass, "timestamp", JNI_jlong_SIGN);
		jfieldID msgTypeID = env->GetFieldID(jniIMMessageClass, "msgType", JNI_jint_SIGN);
		jfieldID contentID = env->GetFieldID(jniIMMessageClass, "content", JNI_jstring_SIGN);
		jfieldID receiversID = env->GetFieldID(jniIMMessageClass, "receivers", JAVA_ARRAYLIST_SIGN);
		jfieldID atUsersID = env->GetFieldID(jniIMMessageClass, "atUsers", JAVA_ARRAYLIST_SIGN);
		jfieldID senderID = env->GetFieldID(jniIMMessageClass, "sender", STPARTICIPANTINFO_INFO_CLASS_SIGN);
		jfieldID sendStatusID = env->GetFieldID(jniIMMessageClass, "sendStatus", JNI_jint_SIGN);
		jfieldID extraDataID = env->GetFieldID(jniIMMessageClass, "extraData", JNI_jstring_SIGN);
		env->DeleteLocalRef(jniIMMessageClass);

		jstring jstrContent = env->NewStringUTF(cppMessage.content.c_str());
		jstring jstrExtraData = env->NewStringUTF(cppMessage.extraData.c_str());

		jobject joReceivers = env->GetObjectField(joMessage, receiversID);
		jobject joAtUsers = env->GetObjectField(joMessage, atUsersID);
		jobject joSender = env->GetObjectField(joMessage, senderID);
		{
			// 使用全局引用，避免在子线程回调自定义类型而崩溃
			jobject joParticipantInfo = JNICustomGlobalRef::instance()->getGlobalRef(STPARTICIPANTINFO_INFO_CLASS_NAME);
			JNICommon::setFieldArrayValue(env, cppMessage.receivers, "" /*STPARTICIPANTINFO_INFO_CLASS_NAME*/, joReceivers, joParticipantInfo);
			JNICommon::setFieldArrayValue(env, cppMessage.atUsers, "" /*STPARTICIPANTINFO_INFO_CLASS_NAME*/, joAtUsers, joParticipantInfo);
		}
		JNICommon::setFieldValue(env, cppMessage.sender, joSender);

		env->SetBooleanField(joMessage, isResendID, cppMessage.isResend);
		env->SetIntField(joMessage, targetID, static_cast<int>(cppMessage.target));
		env->SetLongField(joMessage, idID, cppMessage.id);
		env->SetLongField(joMessage, timestampID, cppMessage.timestamp);
		env->SetIntField(joMessage, msgTypeID, static_cast<int>(cppMessage.msgType));
		env->SetObjectField(joMessage, contentID, jstrContent);
		env->SetObjectField(joMessage, receiversID, joReceivers);
		env->SetObjectField(joMessage, atUsersID, joAtUsers);
		env->SetObjectField(joMessage, senderID, joSender);
		env->SetIntField(joMessage, sendStatusID, static_cast<int>(cppMessage.sendStatus));
		env->SetObjectField(joMessage, extraDataID, jstrExtraData);

		env->DeleteLocalRef(jstrContent);
		env->DeleteLocalRef(joReceivers);
		env->DeleteLocalRef(joAtUsers);
		env->DeleteLocalRef(joSender);
		env->DeleteLocalRef(jstrExtraData);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joAccountInfo, StAccountInfo &cppAccountInfo)
	{
		jclass jniAccountInfoClass = env->GetObjectClass(joAccountInfo);
		if (!jniAccountInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID phoneID = env->GetFieldID(jniAccountInfoClass, "phone", JNI_jstring_SIGN);
		jfieldID emailID = env->GetFieldID(jniAccountInfoClass, "email", JNI_jstring_SIGN);
		jfieldID usernameID = env->GetFieldID(jniAccountInfoClass, "username", JNI_jstring_SIGN);
		jfieldID userOrgNameID = env->GetFieldID(jniAccountInfoClass, "userOrgName", JNI_jstring_SIGN);
		jfieldID userIconID = env->GetFieldID(jniAccountInfoClass, "userIcon", JNI_jstring_SIGN);
		env->DeleteLocalRef(jniAccountInfoClass);

		jstring jstrPhone = (jstring)env->GetObjectField(joAccountInfo, phoneID);
		jstring jstrEmail = (jstring)env->GetObjectField(joAccountInfo, emailID);
		jstring jstrUsername = (jstring)env->GetObjectField(joAccountInfo, usernameID);
		jstring jstrUserOrgName = (jstring)env->GetObjectField(joAccountInfo, userOrgNameID);
		jstring jstrUserIcon = (jstring)env->GetObjectField(joAccountInfo, userIconID);

		cppAccountInfo.phone = getJStringValue(env, jstrPhone);
		cppAccountInfo.email = getJStringValue(env, jstrEmail);
		cppAccountInfo.username = getJStringValue(env, jstrUsername);
		cppAccountInfo.userOrgName = getJStringValue(env, jstrUserOrgName);
		cppAccountInfo.userIcon = getJStringValue(env, jstrUserIcon);

		env->DeleteLocalRef(jstrPhone);
		env->DeleteLocalRef(jstrEmail);
		env->DeleteLocalRef(jstrUsername);
		env->DeleteLocalRef(jstrUserOrgName);
		env->DeleteLocalRef(jstrUserIcon);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StAccountInfo cppAccountInfo, jobject &joAccountInfo)
	{
		jclass jniAccountInfoClass = env->GetObjectClass(joAccountInfo);
		if (!jniAccountInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID phoneID = env->GetFieldID(jniAccountInfoClass, "phone", JNI_jstring_SIGN);
		jfieldID emailID = env->GetFieldID(jniAccountInfoClass, "email", JNI_jstring_SIGN);
		jfieldID usernameID = env->GetFieldID(jniAccountInfoClass, "username", JNI_jstring_SIGN);
		jfieldID userOrgNameID = env->GetFieldID(jniAccountInfoClass, "userOrgName", JNI_jstring_SIGN);
		jfieldID userIconID = env->GetFieldID(jniAccountInfoClass, "userIcon", JNI_jstring_SIGN);
		env->DeleteLocalRef(jniAccountInfoClass);

		jstring jstrPhone = env->NewStringUTF(cppAccountInfo.phone.c_str());
		jstring jstrEmail = env->NewStringUTF(cppAccountInfo.email.c_str());
		jstring jstrUsername = env->NewStringUTF(cppAccountInfo.username.c_str());
		jstring jstrUserOrgName = env->NewStringUTF(cppAccountInfo.userOrgName.c_str());
		jstring jstrUserIcon = env->NewStringUTF(cppAccountInfo.userIcon.c_str());

		env->SetObjectField(joAccountInfo, phoneID, jstrPhone);
		env->SetObjectField(joAccountInfo, emailID, jstrEmail);
		env->SetObjectField(joAccountInfo, usernameID, jstrUsername);
		env->SetObjectField(joAccountInfo, userOrgNameID, jstrUserOrgName);
		env->SetObjectField(joAccountInfo, userIconID, jstrUserIcon);

		env->DeleteLocalRef(jstrPhone);
		env->DeleteLocalRef(jstrEmail);
		env->DeleteLocalRef(jstrUsername);
		env->DeleteLocalRef(jstrUserOrgName);
		env->DeleteLocalRef(jstrUserIcon);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joUserInfo, StUserInfo &cppUserInfo)
	{
		jclass jniUserInfoClass = env->GetObjectClass(joUserInfo);
		if (!jniUserInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID accountID = env->GetFieldID(jniUserInfoClass, "account", JNI_jstring_SIGN);
		jfieldID nameID = env->GetFieldID(jniUserInfoClass, "name", JNI_jstring_SIGN);
		jfieldID iconID = env->GetFieldID(jniUserInfoClass, "icon", JNI_jstring_SIGN);
		jfieldID departmentID = env->GetFieldID(jniUserInfoClass, "department", JNI_jstring_SIGN);
		jfieldID departmentIdID = env->GetFieldID(jniUserInfoClass, "departmentId", JNI_jint_SIGN);
		jfieldID accountTypeID = env->GetFieldID(jniUserInfoClass, "accountType", JNI_jint_SIGN);
		jfieldID terminalTypeID = env->GetFieldID(jniUserInfoClass, "terminalType", JNI_jint_SIGN);
		jfieldID serialNumberID = env->GetFieldID(jniUserInfoClass, "serialNumber", JNI_jstring_SIGN);
		jfieldID deviceModelID = env->GetFieldID(jniUserInfoClass, "deviceModel", JNI_jstring_SIGN);
		jfieldID phoneID = env->GetFieldID(jniUserInfoClass, "phone", JNI_jstring_SIGN);
		jfieldID emailID = env->GetFieldID(jniUserInfoClass, "email", JNI_jstring_SIGN);
		env->DeleteLocalRef(jniUserInfoClass);

		jstring jstrAccount = (jstring)env->GetObjectField(joUserInfo, accountID);
		jstring jstrName = (jstring)env->GetObjectField(joUserInfo, nameID);
		jstring jstrIcon = (jstring)env->GetObjectField(joUserInfo, iconID);
		jstring jstrDepartment = (jstring)env->GetObjectField(joUserInfo, departmentID);
		jint jintDepartmentId = env->GetIntField(joUserInfo, departmentIdID);
		jint jintAccountType = env->GetIntField(joUserInfo, accountTypeID);
		jint jintTerminalType = env->GetIntField(joUserInfo, terminalTypeID);
		jstring jstrSerialNumber = (jstring)env->GetObjectField(joUserInfo, serialNumberID);
		jstring jstrDeviceModel = (jstring)env->GetObjectField(joUserInfo, deviceModelID);
		jstring jstrPhone = (jstring)env->GetObjectField(joUserInfo, phoneID);
		jstring jstrEmail = (jstring)env->GetObjectField(joUserInfo, emailID);

		cppUserInfo.account = getJStringValue(env, jstrAccount);
		cppUserInfo.name = getJStringValue(env, jstrName);
		cppUserInfo.icon = getJStringValue(env, jstrIcon);
		cppUserInfo.department = getJStringValue(env, jstrDepartment);
		cppUserInfo.departmentId = jintDepartmentId;
		cppUserInfo.accountType = static_cast<EnAccountType>(jintAccountType);
		cppUserInfo.terminalType = static_cast<EnTerminalType>(jintTerminalType);
		cppUserInfo.serialNumber = getJStringValue(env, jstrSerialNumber);
		cppUserInfo.deviceModel = getJStringValue(env, jstrDeviceModel);
		cppUserInfo.phone = getJStringValue(env, jstrPhone);
		cppUserInfo.email = getJStringValue(env, jstrEmail);

		env->DeleteLocalRef(jstrAccount);
		env->DeleteLocalRef(jstrName);
		env->DeleteLocalRef(jstrDepartment);
		env->DeleteLocalRef(jstrIcon);
		env->DeleteLocalRef(jstrSerialNumber);
		env->DeleteLocalRef(jstrDeviceModel);
		env->DeleteLocalRef(jstrPhone);
		env->DeleteLocalRef(jstrEmail);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StUserInfo cppUserInfo, jobject &joUserInfo)
	{
		jclass jniUserInfoClass = env->GetObjectClass(joUserInfo);
		if (!jniUserInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID accountID = env->GetFieldID(jniUserInfoClass, "account", JNI_jstring_SIGN);
		jfieldID nameID = env->GetFieldID(jniUserInfoClass, "name", JNI_jstring_SIGN);
		jfieldID iconID = env->GetFieldID(jniUserInfoClass, "icon", JNI_jstring_SIGN);
		jfieldID departmentID = env->GetFieldID(jniUserInfoClass, "department", JNI_jstring_SIGN);
		jfieldID departmentIdID = env->GetFieldID(jniUserInfoClass, "departmentId", JNI_jint_SIGN);
		jfieldID accountTypeID = env->GetFieldID(jniUserInfoClass, "accountType", JNI_jint_SIGN);
		jfieldID terminalTypeID = env->GetFieldID(jniUserInfoClass, "terminalType", JNI_jint_SIGN);
		jfieldID serialNumberID = env->GetFieldID(jniUserInfoClass, "serialNumber", JNI_jstring_SIGN);
		jfieldID deviceModelID = env->GetFieldID(jniUserInfoClass, "deviceModel", JNI_jstring_SIGN);
		jfieldID phoneID = env->GetFieldID(jniUserInfoClass, "phone", JNI_jstring_SIGN);
		jfieldID emailID = env->GetFieldID(jniUserInfoClass, "email", JNI_jstring_SIGN);
		env->DeleteLocalRef(jniUserInfoClass);

		jstring jstrAccount = env->NewStringUTF(cppUserInfo.account.c_str());
		jstring jstrName = env->NewStringUTF(cppUserInfo.name.c_str());
		jstring jstrIcon = env->NewStringUTF(cppUserInfo.icon.c_str());
		jstring jstrDepartment = env->NewStringUTF(cppUserInfo.department.c_str());
		jstring jstrSerialNumber = env->NewStringUTF(cppUserInfo.serialNumber.c_str());
		jstring jstrDeviceModel = env->NewStringUTF(cppUserInfo.deviceModel.c_str());
		jstring jstrPhone = env->NewStringUTF(cppUserInfo.phone.c_str());
		jstring jstrEmail = env->NewStringUTF(cppUserInfo.email.c_str());

		env->SetObjectField(joUserInfo, accountID, jstrAccount);
		env->SetObjectField(joUserInfo, nameID, jstrName);
		env->SetObjectField(joUserInfo, iconID, jstrIcon);
		env->SetObjectField(joUserInfo, departmentID, jstrDepartment);
		env->SetIntField(joUserInfo, departmentIdID, cppUserInfo.departmentId);
		env->SetIntField(joUserInfo, accountTypeID, static_cast<int>(cppUserInfo.accountType));
		env->SetIntField(joUserInfo, terminalTypeID, static_cast<int>(cppUserInfo.terminalType));
		env->SetObjectField(joUserInfo, serialNumberID, jstrSerialNumber);
		env->SetObjectField(joUserInfo, deviceModelID, jstrDeviceModel);
		env->SetObjectField(joUserInfo, phoneID, jstrPhone);
		env->SetObjectField(joUserInfo, emailID, jstrEmail);

		env->DeleteLocalRef(jstrAccount);
		env->DeleteLocalRef(jstrName);
		env->DeleteLocalRef(jstrDepartment);
		env->DeleteLocalRef(jstrIcon);
		env->DeleteLocalRef(jstrSerialNumber);
		env->DeleteLocalRef(jstrDeviceModel);
		env->DeleteLocalRef(jstrPhone);
		env->DeleteLocalRef(jstrEmail);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, LoginInfo cppLoginInfo, jobject &joLoginInfo)
	{
		jclass jniLoginInfoClass = env->GetObjectClass(joLoginInfo);
		if (!jniLoginInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID userInfoID = env->GetFieldID(jniLoginInfoClass, "userInfo", USER_INFO_CLASS_SIGN);
		jfieldID tokenID = env->GetFieldID(jniLoginInfoClass, "token", JNI_jstring_SIGN);
		jfieldID companyInfoID = env->GetFieldID(jniLoginInfoClass, "companyInfo", COMPANY_INFO_CLASS_SIGN);
		jfieldID serverTimestampID = env->GetFieldID(jniLoginInfoClass, "serverTimestamp", JNI_jlong_SIGN);
		jfieldID isFirstLoginID = env->GetFieldID(jniLoginInfoClass, "isFirstLogin", JNI_jboolean_SIGN);
		jfieldID isPrivateDeployID = env->GetFieldID(jniLoginInfoClass, "isPrivateDeploy", JNI_jboolean_SIGN);
		jfieldID loginStatusID = env->GetFieldID(jniLoginInfoClass, "loginStatus", JNI_jboolean_SIGN);
		env->DeleteLocalRef(jniLoginInfoClass);

		jobject joUserInfo = env->GetObjectField(joLoginInfo, userInfoID);
		jstring jstrToken = env->NewStringUTF(cppLoginInfo.token.c_str());
		jobject joCompanyInfo = env->GetObjectField(joLoginInfo, companyInfoID);

		JNICommon::setFieldValue(env, cppLoginInfo.companyInfo, joCompanyInfo);
		JNICommon::setFieldValue(env, cppLoginInfo.userInfo, joUserInfo);

		env->SetObjectField(joLoginInfo, userInfoID, joUserInfo);
		env->SetObjectField(joLoginInfo, tokenID, jstrToken);
		env->SetObjectField(joLoginInfo, companyInfoID, joCompanyInfo);
		env->SetLongField(joLoginInfo, serverTimestampID, cppLoginInfo.serverTimestamp);
		env->SetBooleanField(joLoginInfo, isFirstLoginID, cppLoginInfo.isFirstLogin);
		env->SetBooleanField(joLoginInfo, isPrivateDeployID, cppLoginInfo.isPrivateDeploy);
		env->SetBooleanField(joLoginInfo, loginStatusID, cppLoginInfo.loginStatus);

		env->DeleteLocalRef(joUserInfo);
		env->DeleteLocalRef(jstrToken);
		env->DeleteLocalRef(joCompanyInfo);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StPushedMsg cppPushedMsg, jobject &joPushedMsg)
	{
		jclass jniPushedMsgClass = env->GetObjectClass(joPushedMsg);
		if (!jniPushedMsgClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID idID = env->GetFieldID(jniPushedMsgClass, "id", JNI_jlong_SIGN);
		jfieldID timestampID = env->GetFieldID(jniPushedMsgClass, "timestamp", JNI_jlong_SIGN);
		jfieldID typeID = env->GetFieldID(jniPushedMsgClass, "type", JNI_jint_SIGN);
		jfieldID unreadFlagID = env->GetFieldID(jniPushedMsgClass, "unreadFlag", JNI_jboolean_SIGN);
		jfieldID contentID = env->GetFieldID(jniPushedMsgClass, "content", JNI_jstring_SIGN);
		jfieldID ruidID = env->GetFieldID(jniPushedMsgClass, "ruid", JNI_jstring_SIGN);
		env->DeleteLocalRef(jniPushedMsgClass);

		jstring jstrContent = env->NewStringUTF(cppPushedMsg.content.c_str());
		jstring jstrRuid = env->NewStringUTF(cppPushedMsg.ruid.c_str());

		env->SetLongField(joPushedMsg, idID, cppPushedMsg.id);
		env->SetLongField(joPushedMsg, timestampID, cppPushedMsg.timestamp);
		env->SetIntField(joPushedMsg, typeID, static_cast<int>(cppPushedMsg.type));
		env->SetBooleanField(joPushedMsg, unreadFlagID, cppPushedMsg.unreadFlag);
		env->SetObjectField(joPushedMsg, contentID, jstrContent);
		env->SetObjectField(joPushedMsg, ruidID, jstrRuid);

		env->DeleteLocalRef(jstrContent);
		env->DeleteLocalRef(jstrRuid);

		return 0;
	}
	
	int JNICommon::setFieldValue(JNIEnv *env, StParticipantInfo cppStParticipantInfo, jobject &joStParticipantInfo)
	{
		jclass jniStPartInfoClass = env->GetObjectClass(joStParticipantInfo);
		if (!jniStPartInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID userInfoID = env->GetFieldID(jniStPartInfoClass, "userInfo", USER_INFO_CLASS_SIGN);
		jfieldID roleID = env->GetFieldID(jniStPartInfoClass, "role", JNI_jint_SIGN);
		jfieldID orderID = env->GetFieldID(jniStPartInfoClass, "order", JNI_jint_SIGN);
		jfieldID createTimeMsID = env->GetFieldID(jniStPartInfoClass, "createTimeMs", JNI_jlong_SIGN);
		jfieldID onlineStatusID = env->GetFieldID(jniStPartInfoClass, "onlineStatus", JNI_jboolean_SIGN);
		jfieldID cameraStatusID = env->GetFieldID(jniStPartInfoClass, "cameraStatus", JNI_jboolean_SIGN);
		jfieldID micStatusID = env->GetFieldID(jniStPartInfoClass, "micStatus", JNI_jboolean_SIGN);
		jfieldID speakerStatusID = env->GetFieldID(jniStPartInfoClass, "speakerStatus", JNI_jboolean_SIGN);
		jfieldID handStatusID = env->GetFieldID(jniStPartInfoClass, "handStatus", JNI_jboolean_SIGN);
		jfieldID lectureStatusID = env->GetFieldID(jniStPartInfoClass, "lectureStatus", JNI_jboolean_SIGN);
		jfieldID shareStatusID = env->GetFieldID(jniStPartInfoClass, "shareStatus", JNI_jboolean_SIGN);
		jfieldID isVoiceModeID = env->GetFieldID(jniStPartInfoClass, "isVoiceMode", JNI_jboolean_SIGN);
		jfieldID streamsID = env->GetFieldID(jniStPartInfoClass, "streams", JAVA_ARRAYLIST_SIGN);
		jfieldID appVersionID = env->GetFieldID(jniStPartInfoClass, "appVersion", JNI_jstring_SIGN);
		jfieldID functionalityID = env->GetFieldID(jniStPartInfoClass, "functionality", JNI_jstring_SIGN);
		env->DeleteLocalRef(jniStPartInfoClass);

		jstring jstrAppVersion = env->NewStringUTF(cppStParticipantInfo.appVersion.c_str());
		jstring jstrFunctionality = env->NewStringUTF(cppStParticipantInfo.functionality.c_str());

		env->SetIntField(joStParticipantInfo, roleID, cppStParticipantInfo.role);
		env->SetIntField(joStParticipantInfo, orderID, cppStParticipantInfo.order);
		env->SetLongField(joStParticipantInfo, createTimeMsID, cppStParticipantInfo.createTimeMs);
		env->SetBooleanField(joStParticipantInfo, onlineStatusID, cppStParticipantInfo.onlineStatus);
		env->SetBooleanField(joStParticipantInfo, cameraStatusID, cppStParticipantInfo.cameraStatus);
		env->SetBooleanField(joStParticipantInfo, micStatusID, cppStParticipantInfo.micStatus);
		env->SetBooleanField(joStParticipantInfo, speakerStatusID, cppStParticipantInfo.speakerStatus);
		env->SetBooleanField(joStParticipantInfo, handStatusID, cppStParticipantInfo.handStatus);
		env->SetBooleanField(joStParticipantInfo, lectureStatusID, cppStParticipantInfo.lectureStatus);
		env->SetBooleanField(joStParticipantInfo, shareStatusID, cppStParticipantInfo.shareStatus);
		env->SetBooleanField(joStParticipantInfo, isVoiceModeID, cppStParticipantInfo.isVoiceMode);

		env->SetObjectField(joStParticipantInfo, appVersionID, jstrAppVersion);
		env->SetObjectField(joStParticipantInfo, functionalityID, jstrFunctionality);

		jobject joUserInfo = env->GetObjectField(joStParticipantInfo, userInfoID);
		jobject jostreamsList = env->GetObjectField(joStParticipantInfo, streamsID);

		setFieldValue(env, cppStParticipantInfo.userInfo, joUserInfo);

		jobject joStreamInfo = JNICustomGlobalRef::instance()->getGlobalRef(STSTREAM_INFO_CLASS_NAME);
		setFieldArrayValue(env, cppStParticipantInfo.streams, "" /*STSTREAM_INFO_CLASS_NAME*/, jostreamsList, joStreamInfo);

		env->DeleteLocalRef(jstrAppVersion);
		env->DeleteLocalRef(jstrFunctionality);
		env->DeleteLocalRef(joUserInfo);
		env->DeleteLocalRef(jostreamsList);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joStParticipantInfo, StParticipantInfo &cppStParticipantInfo)
	{
		jclass jniStPartInfoClass = env->GetObjectClass(joStParticipantInfo);
		if (!jniStPartInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID userInfoID = env->GetFieldID(jniStPartInfoClass, "userInfo", USER_INFO_CLASS_SIGN);
		jfieldID roleID = env->GetFieldID(jniStPartInfoClass, "role", JNI_jint_SIGN);
		jfieldID orderID = env->GetFieldID(jniStPartInfoClass, "order", JNI_jint_SIGN);
		jfieldID createTimeMsID = env->GetFieldID(jniStPartInfoClass, "createTimeMs", JNI_jlong_SIGN);
		jfieldID onlineStatusID = env->GetFieldID(jniStPartInfoClass, "onlineStatus", JNI_jboolean_SIGN);
		jfieldID cameraStatusID = env->GetFieldID(jniStPartInfoClass, "cameraStatus", JNI_jboolean_SIGN);
		jfieldID micStatusID = env->GetFieldID(jniStPartInfoClass, "micStatus", JNI_jboolean_SIGN);
		jfieldID speakerStatusID = env->GetFieldID(jniStPartInfoClass, "speakerStatus", JNI_jboolean_SIGN);
		jfieldID handStatusID = env->GetFieldID(jniStPartInfoClass, "handStatus", JNI_jboolean_SIGN);
		jfieldID lectureStatusID = env->GetFieldID(jniStPartInfoClass, "lectureStatus", JNI_jboolean_SIGN);
		jfieldID shareStatusID = env->GetFieldID(jniStPartInfoClass, "shareStatus", JNI_jboolean_SIGN);
		jfieldID isVoiceModeID = env->GetFieldID(jniStPartInfoClass, "isVoiceMode", JNI_jboolean_SIGN);
		jfieldID streamsID = env->GetFieldID(jniStPartInfoClass, "streams", JAVA_ARRAYLIST_SIGN);
		jfieldID appVersionID = env->GetFieldID(jniStPartInfoClass, "appVersion", JNI_jstring_SIGN);
		jfieldID functionalityID = env->GetFieldID(jniStPartInfoClass, "functionality", JNI_jstring_SIGN);
		env->DeleteLocalRef(jniStPartInfoClass);

		jobject joUserInfo = env->GetObjectField(joStParticipantInfo, userInfoID);
		jint jintRole = env->GetIntField(joStParticipantInfo, roleID);
		jint jintOrder = env->GetIntField(joStParticipantInfo, orderID);
		jlong jlCreateTimeMs = env->GetLongField(joStParticipantInfo, createTimeMsID);
		jboolean jbOnLineStatus = env->GetBooleanField(joStParticipantInfo, onlineStatusID);
		jboolean jbCameraStatus = env->GetBooleanField(joStParticipantInfo, cameraStatusID);
		jboolean jbMicStatus = env->GetBooleanField(joStParticipantInfo, micStatusID);
		jboolean jbSpeakerStatus = env->GetBooleanField(joStParticipantInfo, speakerStatusID);
		jboolean jbHandStatus = env->GetBooleanField(joStParticipantInfo, handStatusID);
		jboolean jbLectureStatus = env->GetBooleanField(joStParticipantInfo, lectureStatusID);
		jboolean jbShareStatus = env->GetBooleanField(joStParticipantInfo, shareStatusID);
		jboolean jbIsVoiceMode = env->GetBooleanField(joStParticipantInfo, isVoiceModeID);
		jobject joStreams = env->GetObjectField(joStParticipantInfo, streamsID);
		jstring jstrAppVersion = (jstring)env->GetObjectField(joStParticipantInfo, appVersionID);
		jstring jstrFunctionality = (jstring)env->GetObjectField(joStParticipantInfo, functionalityID);

		getFieldValue(env, joUserInfo, cppStParticipantInfo.userInfo);
		cppStParticipantInfo.role = static_cast<EnRoomRole>(jintRole);
		cppStParticipantInfo.order = jintOrder;
		cppStParticipantInfo.createTimeMs = jlCreateTimeMs;
		cppStParticipantInfo.onlineStatus = jbOnLineStatus;
		cppStParticipantInfo.cameraStatus = jbCameraStatus;
		cppStParticipantInfo.micStatus = jbMicStatus;
		cppStParticipantInfo.speakerStatus = jbSpeakerStatus;
		cppStParticipantInfo.handStatus = jbHandStatus;
		cppStParticipantInfo.lectureStatus = jbLectureStatus;
		cppStParticipantInfo.shareStatus = jbShareStatus;
		cppStParticipantInfo.isVoiceMode = jbIsVoiceMode;
		getFieldArrayValue(env, joStreams, cppStParticipantInfo.streams);
		cppStParticipantInfo.appVersion = getJStringValue(env, jstrAppVersion);
		cppStParticipantInfo.functionality = getJStringValue(env, jstrFunctionality);

		env->DeleteLocalRef(joUserInfo);
		env->DeleteLocalRef(joStreams);
		env->DeleteLocalRef(jstrAppVersion);
		env->DeleteLocalRef(jstrFunctionality);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joConfigInfo, StPresetPositionConfigInfo &cppConfigInfo)
	{
		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StPresetPositionConfigInfo cppConfigInfo, jobject &joConfigInfo)
	{
		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StMeetingRoom cppRoom, jobject &joMeetingRooms)
	{
		jclass jniConferenceRoomClass = env->GetObjectClass(joMeetingRooms);
		if (!jniConferenceRoomClass)
		{
			errorf("GET CLASS FAILED!!!");
			return -1;
		}
		jfieldID typeID = env->GetFieldID(jniConferenceRoomClass, "type", JNI_jint_SIGN);
		jfieldID idID = env->GetFieldID(jniConferenceRoomClass, "id", JNI_jstring_SIGN);
		jfieldID nameID = env->GetFieldID(jniConferenceRoomClass, "name", JNI_jstring_SIGN);
		jfieldID statusID = env->GetFieldID(jniConferenceRoomClass, "status", JNI_jint_SIGN);
		jfieldID capacityID = env->GetFieldID(jniConferenceRoomClass, "capacity", JNI_jint_SIGN);
		jfieldID shortNumID = env->GetFieldID(jniConferenceRoomClass, "shortNum", JNI_jstring_SIGN);
		jfieldID expiredDateID = env->GetFieldID(jniConferenceRoomClass, "expiredDate", JNI_jstring_SIGN);
		jfieldID roomIconID = env->GetFieldID(jniConferenceRoomClass, "roomIcon", JNI_jstring_SIGN);
		jfieldID hasAdminRightsID = env->GetFieldID(jniConferenceRoomClass, "hasAdminRights", JNI_jboolean_SIGN);
		env->DeleteLocalRef(jniConferenceRoomClass);

		jstring jstrId = env->NewStringUTF(cppRoom.id.c_str());
		jstring jstrName = env->NewStringUTF(cppRoom.name.c_str());
		jstring jstrShortNum = env->NewStringUTF(cppRoom.shortNum.c_str());
		jstring jstrExpiredDate = env->NewStringUTF(cppRoom.expiredDate.c_str());
		jstring jstrRoomIcon = env->NewStringUTF(cppRoom.icon.c_str());

		env->SetIntField(joMeetingRooms, typeID, cppRoom.type);
		env->SetObjectField(joMeetingRooms, idID, jstrId);
		env->SetObjectField(joMeetingRooms, nameID, jstrName);
		env->SetIntField(joMeetingRooms, statusID, cppRoom.status);
		env->SetIntField(joMeetingRooms, capacityID, cppRoom.capacity);
		env->SetObjectField(joMeetingRooms, shortNumID, jstrShortNum);
		env->SetObjectField(joMeetingRooms, expiredDateID, jstrExpiredDate);
		env->SetObjectField(joMeetingRooms, roomIconID, jstrRoomIcon);
		env->SetBooleanField(joMeetingRooms, hasAdminRightsID, cppRoom.hasAdminRights);

		env->DeleteLocalRef(jstrId);
		env->DeleteLocalRef(jstrName);
		env->DeleteLocalRef(jstrShortNum);
		env->DeleteLocalRef(jstrExpiredDate);
		env->DeleteLocalRef(jstrRoomIcon);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StAllMeetingRooms cppRooms, jobject &joMeetingRooms)
	{
		jclass jniAllMeetingRoomClass = env->GetObjectClass(joMeetingRooms);
		if (!jniAllMeetingRoomClass)
		{
			errorf("GET CLASS FAILED!!!");
			return -1;
		}
		jfieldID fixedConfRoomsID = env->GetFieldID(jniAllMeetingRoomClass, "fixedMeetingRooms", JAVA_ARRAYLIST_SIGN);
		env->DeleteLocalRef(jniAllMeetingRoomClass);

		jobject joFixedConfRooms = env->GetObjectField(joMeetingRooms, fixedConfRoomsID);
		if (!joFixedConfRooms)
		{
			errorf("Get object field failed.");
			return -1;
		}
		int ret = setFieldArrayValue(env, cppRooms.fixedMeetingRooms, BASE_MEETING_ROOM_CLASS_NAME, joFixedConfRooms);
		if (ret != 0)
		{
			errorf("Set field's value failed.");
			return ret;
		}

		env->SetObjectField(joMeetingRooms, fixedConfRoomsID, joFixedConfRooms);

		env->DeleteLocalRef(joFixedConfRooms);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, std::vector<OrgInfo> departList, jobject &joOrgInfoArrayList)
	{
		if (!joOrgInfoArrayList)
		{
			errorf("object is null.");
			return -1;
		}

		jclass jniOrgInfoClass = env->FindClass(ORG_INFO_CLASS_NAME);
		if (!jniOrgInfoClass)
		{
			errorf("FIND CLASS FAILED!!!");
			return -1;
		}
		jfieldID orgIdID = env->GetFieldID(jniOrgInfoClass, "orgId", JNI_jint_SIGN);
		jfieldID orgNameID = env->GetFieldID(jniOrgInfoClass, "orgName", JNI_jstring_SIGN);
		jfieldID parentIdID = env->GetFieldID(jniOrgInfoClass, "parentId", JNI_jint_SIGN);
		jfieldID hasChildID = env->GetFieldID(jniOrgInfoClass, "hasChild", JNI_jboolean_SIGN);
		jfieldID hasMemberID = env->GetFieldID(jniOrgInfoClass, "hasMember", JNI_jboolean_SIGN);
		jfieldID numOfEmpID = env->GetFieldID(jniOrgInfoClass, "numOfEmp", JNI_jint_SIGN);
		jmethodID orgInfoConstructorID = env->GetMethodID(jniOrgInfoClass, "<init>", "()V");

		for (auto orgInfo : departList)
		{
			jobject joOrgInfo = env->NewObject(jniOrgInfoClass, orgInfoConstructorID);

			jstring jstrOrgName = (jstring)env->NewStringUTF(orgInfo.orgName.c_str());

			env->SetIntField(joOrgInfo, orgIdID, orgInfo.orgId);
			env->SetObjectField(joOrgInfo, orgNameID, jstrOrgName);
			env->SetIntField(joOrgInfo, parentIdID, orgInfo.parentId);
			env->SetBooleanField(joOrgInfo, hasChildID, orgInfo.hasChild);
			env->SetBooleanField(joOrgInfo, hasMemberID, orgInfo.hasMember);
			env->SetIntField(joOrgInfo, numOfEmpID, orgInfo.numOfEmp);

			JNICommon::addEleIntoArrayList(env, joOrgInfoArrayList, joOrgInfo);

			env->DeleteLocalRef(jstrOrgName);
			env->DeleteLocalRef(joOrgInfo);
		}
		env->DeleteLocalRef(jniOrgInfoClass);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, std::vector<StChatGroup> cppGroupList, jobject &joGroupInfoArrayList)
	{
		if (!joGroupInfoArrayList)
		{
			errorf("object is null.");
			return -1;
		}

		jclass jniGroupInfoClass = env->FindClass(BASE_GROUP_INFO_CLASS_NAME);
		if (!jniGroupInfoClass)
		{
			errorf("FIND CLASS FAILED!!!");
			return -1;
		}
		jfieldID groupIdID = env->GetFieldID(jniGroupInfoClass, "groupId", JNI_jint_SIGN);
		jfieldID groupNameID = env->GetFieldID(jniGroupInfoClass, "groupName", JNI_jstring_SIGN);
		jfieldID numOfPeopleID = env->GetFieldID(jniGroupInfoClass, "numOfPeople", JNI_jint_SIGN);
		jfieldID groupIconID = env->GetFieldID(jniGroupInfoClass, "groupIcon", JNI_jstring_SIGN);
		jfieldID typeID = env->GetFieldID(jniGroupInfoClass, "type", JNI_jint_SIGN);
		jmethodID groupInfoConstructorID = env->GetMethodID(jniGroupInfoClass, "<init>", "()V");

		for (auto groupInfo : cppGroupList)
		{
			jobject joGroupInfo = env->NewObject(jniGroupInfoClass, groupInfoConstructorID);

			jstring jstrGroupName = (jstring)env->NewStringUTF(groupInfo.groupName.c_str());
			jstring jstrGroupIcon = (jstring)env->NewStringUTF(groupInfo.groupIcon.c_str());

			env->SetIntField(joGroupInfo, groupIdID, groupInfo.groupId);
			env->SetObjectField(joGroupInfo, groupNameID, jstrGroupName);
			env->SetIntField(joGroupInfo, numOfPeopleID, groupInfo.numOfPeople);
			env->SetObjectField(joGroupInfo, groupIconID, jstrGroupIcon);
			env->SetIntField(joGroupInfo, typeID, groupInfo.type);

			JNICommon::addEleIntoArrayList(env, joGroupInfoArrayList, joGroupInfo);

			env->DeleteLocalRef(jstrGroupName);
			env->DeleteLocalRef(jstrGroupIcon);
			env->DeleteLocalRef(joGroupInfo);
		}
		env->DeleteLocalRef(jniGroupInfoClass);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joStreamInfoList, std::vector<StreamInfo> &cppStreamInfoList)
	{
		jclass arrayListClass = env->GetObjectClass(joStreamInfoList);
		if (!arrayListClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jmethodID getMethodId = env->GetMethodID(arrayListClass, "get", "(I)Ljava/lang/Object;");
		jmethodID sizeMethodId = env->GetMethodID(arrayListClass, "size", "()I");
		env->DeleteLocalRef(arrayListClass);

		jclass jniStreamInfoClass = env->FindClass(STREAM_INFO_CLASS_NAME);
		if (!jniStreamInfoClass)
		{
			errorf("FIND CLASS FAILED!!!");
			return -1;
		}
		jfieldID idID = env->GetFieldID(jniStreamInfoClass, "id", JNI_jstring_SIGN);
		jfieldID typeID = env->GetFieldID(jniStreamInfoClass, "type", JNI_jint_SIGN);
		jfieldID hasVideoID = env->GetFieldID(jniStreamInfoClass, "hasVideo", JNI_jboolean_SIGN);
		jfieldID hasAudioID = env->GetFieldID(jniStreamInfoClass, "hasAudio", JNI_jboolean_SIGN);
		env->DeleteLocalRef(jniStreamInfoClass);

		int arrayListSize = env->CallIntMethod(joStreamInfoList, sizeMethodId);
		for (int i = 0; i < arrayListSize; i++)
		{
			jobject joStreamInfo = env->CallObjectMethod(joStreamInfoList, getMethodId, i);

			jstring jstrId = (jstring)env->GetObjectField(joStreamInfo, idID);
			jint jintType = env->GetIntField(joStreamInfo, typeID);
			jboolean jbHasVideo = env->GetBooleanField(joStreamInfo, hasVideoID);
			jboolean jbHasAudio = env->GetBooleanField(joStreamInfo, hasAudioID);

			const char *cppId = env->GetStringUTFChars(jstrId, NULL);

			StreamInfo streamInfo;
			streamInfo.id = cppId;
			streamInfo.type = (EnStreamType)jintType;
			streamInfo.hasVideo = jbHasVideo;
			streamInfo.hasAudio = jbHasAudio;

			cppStreamInfoList.push_back(streamInfo);

			env->ReleaseStringUTFChars(jstrId, cppId);
			env->DeleteLocalRef(joStreamInfo);
		}
		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joStreamInfo, StreamInfo &cppStreamInfo)
	{
		jclass jniStreamInfoClass = env->GetObjectClass(joStreamInfo);
		if (!jniStreamInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID idID = env->GetFieldID(jniStreamInfoClass, "id", JNI_jstring_SIGN);
		jfieldID typeID = env->GetFieldID(jniStreamInfoClass, "type", JNI_jint_SIGN);
		jfieldID hasVideoID = env->GetFieldID(jniStreamInfoClass, "hasVideo", JNI_jboolean_SIGN);
		jfieldID hasAudioID = env->GetFieldID(jniStreamInfoClass, "hasAudio", JNI_jboolean_SIGN);
		env->DeleteLocalRef(jniStreamInfoClass);

		jstring jstrStreamId = (jstring)env->GetObjectField(joStreamInfo, idID);
		jint jintType = env->GetIntField(joStreamInfo, typeID);
		jboolean jbHasVideo = env->GetBooleanField(joStreamInfo, hasVideoID);
		jboolean jbHasAudio = env->GetBooleanField(joStreamInfo, hasAudioID);

		cppStreamInfo.id = getJStringValue(env, jstrStreamId);
		cppStreamInfo.type = static_cast<EnStreamType>(jintType);
		cppStreamInfo.hasVideo = jbHasVideo;
		cppStreamInfo.hasAudio = jbHasAudio;

		env->DeleteLocalRef(jstrStreamId);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StreamInfo cppStreamInfo, jobject &joStreamInfo)
	{
		jclass jniStreamInfoClass = env->GetObjectClass(joStreamInfo);
		if (!jniStreamInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID idID = env->GetFieldID(jniStreamInfoClass, "id", JNI_jstring_SIGN);
		jfieldID typeID = env->GetFieldID(jniStreamInfoClass, "type", JNI_jint_SIGN);
		jfieldID hasVideoID = env->GetFieldID(jniStreamInfoClass, "hasVideo", JNI_jboolean_SIGN);
		jfieldID hasAudioID = env->GetFieldID(jniStreamInfoClass, "hasAudio", JNI_jboolean_SIGN);
		env->DeleteLocalRef(jniStreamInfoClass);

		jstring jstrStreamId = env->NewStringUTF(cppStreamInfo.id.c_str());

		env->SetObjectField(joStreamInfo, idID, jstrStreamId);
		env->SetIntField(joStreamInfo, typeID, static_cast<int>(cppStreamInfo.type));
		env->SetBooleanField(joStreamInfo, hasVideoID, cppStreamInfo.hasVideo);
		env->SetBooleanField(joStreamInfo, hasAudioID, cppStreamInfo.hasAudio);

		env->DeleteLocalRef(jstrStreamId);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joStStreamInfo, StStreamInfo &cppStStreamInfo)
	{
		jclass jniStStreamInfoClass = env->GetObjectClass(joStStreamInfo);
		if (!jniStStreamInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID idID = env->GetFieldID(jniStStreamInfoClass, "id", JNI_jstring_SIGN);
		jfieldID typeID = env->GetFieldID(jniStStreamInfoClass, "type", JNI_jint_SIGN);
		jfieldID hasVideoID = env->GetFieldID(jniStStreamInfoClass, "hasVideo", JNI_jboolean_SIGN);
		jfieldID hasAudioID = env->GetFieldID(jniStStreamInfoClass, "hasAudio", JNI_jboolean_SIGN);
		jfieldID pushStreamStatusID = env->GetFieldID(jniStStreamInfoClass, "pushStreamStatus", JNI_jint_SIGN);
		jfieldID pullStreamStatusID = env->GetFieldID(jniStStreamInfoClass, "pullStreamStatus", JNI_jint_SIGN);
		env->DeleteLocalRef(jniStStreamInfoClass);

		jstring jstrStreamId = (jstring)env->GetObjectField(joStStreamInfo, idID);
		jint jintType = env->GetIntField(joStStreamInfo, typeID);
		jboolean jbHasVideo = env->GetBooleanField(joStStreamInfo, hasVideoID);
		jboolean jbHasAudio = env->GetBooleanField(joStStreamInfo, hasAudioID);
		jint jintPushStreamStatus = env->GetIntField(joStStreamInfo, pushStreamStatusID);
		jint jintPullStreamStatus = env->GetIntField(joStStreamInfo, pullStreamStatusID);

		cppStStreamInfo.id = getJStringValue(env, jstrStreamId);
		cppStStreamInfo.type = static_cast<EnStreamType>(jintType);
		cppStStreamInfo.hasVideo = jbHasVideo;
		cppStStreamInfo.hasAudio = jbHasAudio;
		cppStStreamInfo.pushStreamStatus = static_cast<EnStreamStatus>(jintPushStreamStatus);
		cppStStreamInfo.pullStreamStatus = static_cast<EnStreamStatus>(jintPullStreamStatus);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StStreamInfo cppStStreamInfo, jobject &joStStreamInfo)
	{
		jclass jniStStreamInfoClass = env->GetObjectClass(joStStreamInfo);
		if (!jniStStreamInfoClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID idID = env->GetFieldID(jniStStreamInfoClass, "id", JNI_jstring_SIGN);
		jfieldID typeID = env->GetFieldID(jniStStreamInfoClass, "type", JNI_jint_SIGN);
		jfieldID hasVideoID = env->GetFieldID(jniStStreamInfoClass, "hasVideo", JNI_jboolean_SIGN);
		jfieldID hasAudioID = env->GetFieldID(jniStStreamInfoClass, "hasAudio", JNI_jboolean_SIGN);
		jfieldID pushStreamStatusID = env->GetFieldID(jniStStreamInfoClass, "pushStreamStatus", JNI_jint_SIGN);
		jfieldID pullStreamStatusID = env->GetFieldID(jniStStreamInfoClass, "pullStreamStatus", JNI_jint_SIGN);
		env->DeleteLocalRef(jniStStreamInfoClass);

		jstring jstrStreamId = env->NewStringUTF(cppStStreamInfo.id.c_str());

		env->SetObjectField(joStStreamInfo, idID, jstrStreamId);
		env->SetIntField(joStStreamInfo, typeID, static_cast<int>(cppStStreamInfo.type));
		env->SetBooleanField(joStStreamInfo, hasVideoID, cppStStreamInfo.hasVideo);
		env->SetBooleanField(joStStreamInfo, hasAudioID, cppStStreamInfo.hasAudio);
		env->SetIntField(joStStreamInfo, pushStreamStatusID, cppStStreamInfo.pushStreamStatus);
		env->SetIntField(joStStreamInfo, pullStreamStatusID, cppStStreamInfo.pullStreamStatus);

		env->DeleteLocalRef(jstrStreamId);
		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joMediaControlParamList, std::vector<StMediaControlParam> &cppMediaControlParamList)
	{
		jclass arrayListClass = env->GetObjectClass(joMediaControlParamList);
		if (!arrayListClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jmethodID getMethodId = env->GetMethodID(arrayListClass, "get", "(I)Ljava/lang/Object;");
		jmethodID sizeMethodId = env->GetMethodID(arrayListClass, "size", "()I");
		env->DeleteLocalRef(arrayListClass);

		int arrayListSize = env->CallIntMethod(joMediaControlParamList, sizeMethodId);
		for (int i = 0; i < arrayListSize; i++)
		{
			jobject joMediaControlParam = env->CallObjectMethod(joMediaControlParamList, getMethodId, i);
			StMediaControlParam cppParam;

			getFieldValue(env, joMediaControlParam, cppParam);

			cppMediaControlParamList.push_back(cppParam);

			env->DeleteLocalRef(joMediaControlParam);
		}
		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joMediaControlParam, StMediaControlParam &cppMediaControlParam)
	{
		jclass jniMediaControlParamClass = env->GetObjectClass(joMediaControlParam);
		if (!jniMediaControlParamClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID accountID = env->GetFieldID(jniMediaControlParamClass, "account", JNI_jstring_SIGN);
		jfieldID streamTypeID = env->GetFieldID(jniMediaControlParamClass, "streamType", JNI_jint_SIGN);
		jfieldID mediaTypeID = env->GetFieldID(jniMediaControlParamClass, "mediaType", JNI_jint_SIGN);
		env->DeleteLocalRef(jniMediaControlParamClass);

		jstring jstrAccount = (jstring)env->GetObjectField(joMediaControlParam, accountID);
		jint jintStreamType = env->GetIntField(joMediaControlParam, streamTypeID);
		jint jintMediaType = env->GetIntField(joMediaControlParam, mediaTypeID);

		cppMediaControlParam.account = getJStringValue(env, jstrAccount);
		cppMediaControlParam.streamType = (EnStreamType)jintStreamType;
		cppMediaControlParam.mediaType = (EnMediaType)jintMediaType;

		env->DeleteLocalRef(jstrAccount);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joRect, StRect &cppRect)
	{
		jclass jniClass = env->GetObjectClass(joRect);
		if (!jniClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID xID = env->GetFieldID(jniClass, "x", JNI_jint_SIGN);
		jfieldID yID = env->GetFieldID(jniClass, "y", JNI_jint_SIGN);
		jfieldID widthID = env->GetFieldID(jniClass, "width", JNI_jint_SIGN);
		jfieldID heightID = env->GetFieldID(jniClass, "height", JNI_jint_SIGN);
		env->DeleteLocalRef(jniClass);

		cppRect.x = env->GetIntField(joRect, xID);
		cppRect.y = env->GetIntField(joRect, yID);
		cppRect.width = env->GetIntField(joRect, widthID);
		cppRect.height = env->GetIntField(joRect, heightID);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StRect cppRect, jobject &joRect)
	{
		jclass jniClass = env->GetObjectClass(joRect);
		if (!jniClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID xID = env->GetFieldID(jniClass, "x", JNI_jint_SIGN);
		jfieldID yID = env->GetFieldID(jniClass, "y", JNI_jint_SIGN);
		jfieldID widthID = env->GetFieldID(jniClass, "width", JNI_jint_SIGN);
		jfieldID heightID = env->GetFieldID(jniClass, "height", JNI_jint_SIGN);
		env->DeleteLocalRef(jniClass);

		env->SetIntField(joRect, xID, cppRect.x);
		env->SetIntField(joRect, yID, cppRect.y);
		env->SetIntField(joRect, widthID, cppRect.width);
		env->SetIntField(joRect, heightID, cppRect.height);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joView, StView &cppView)
	{
		jclass jniClass = env->GetObjectClass(joView);
		if (!jniClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID accountID = env->GetFieldID(jniClass, "account", JNI_jstring_SIGN);
		jfieldID usernameID = env->GetFieldID(jniClass, "username", JNI_jstring_SIGN);
		jfieldID streamTypeID = env->GetFieldID(jniClass, "streamType", JNI_jint_SIGN);
		jfieldID rectID = env->GetFieldID(jniClass, "rect", RECT_CLASS_SIGN);
		env->DeleteLocalRef(jniClass);

		jstring jstrAccount = (jstring)env->GetObjectField(joView, accountID);
		jstring jstrUsername = (jstring)env->GetObjectField(joView, usernameID);
		jint jintStreamType = env->GetIntField(joView, streamTypeID);
		jobject joRect = env->GetObjectField(joView, rectID);

		cppView.account = getJStringValue(env, jstrAccount);
		cppView.username = getJStringValue(env, jstrUsername);
		cppView.streamType = (EnStreamType)jintStreamType;
		getFieldValue(env, joRect, cppView.rect);

		env->DeleteLocalRef(jstrAccount);
		env->DeleteLocalRef(jstrUsername);
		env->DeleteLocalRef(joRect);

		return 0;
	}

	int JNICommon::setFieldValue(JNIEnv *env, StView cppView, jobject &joView)
	{
		jclass jniClass = env->GetObjectClass(joView);
		if (!jniClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID accountID = env->GetFieldID(jniClass, "account", JNI_jstring_SIGN);
		jfieldID usernameID = env->GetFieldID(jniClass, "username", JNI_jstring_SIGN);
		jfieldID streamTypeID = env->GetFieldID(jniClass, "streamType", JNI_jint_SIGN);
		jfieldID rectID = env->GetFieldID(jniClass, "rect", RECT_CLASS_SIGN);
		env->DeleteLocalRef(jniClass);

		jstring jstrAccount = env->NewStringUTF(cppView.account.c_str());
		jstring jstrUsername = env->NewStringUTF(cppView.username.c_str());
		jobject joRect = env->GetObjectField(joView, rectID);

		env->SetObjectField(joView, accountID, jstrAccount);
		env->SetObjectField(joView, usernameID, jstrUsername);
		env->SetIntField(joView, streamTypeID, static_cast<int>(cppView.streamType));

		setFieldValue(env, cppView.rect, joRect);
		env->SetObjectField(joView, rectID, joRect);

		env->DeleteLocalRef(jstrAccount);
		env->DeleteLocalRef(jstrUsername);
		env->DeleteLocalRef(joRect);

		return 0;
	}

	int JNICommon::getFieldValue(JNIEnv *env, jobject joCalleeInfo, StCalleeInfo &cppCalleeInfo)
	{
		jclass jniClass = env->GetObjectClass(joCalleeInfo);
		if (!jniClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID userInfoID = env->GetFieldID(jniClass, "userInfo", USER_INFO_CLASS_SIGN);
		jfieldID expireTimeID = env->GetFieldID(jniClass, "expireTime", JNI_jlong_SIGN);
		env->DeleteLocalRef(jniClass);

		jobject joUserInfo = env->GetObjectField(joCalleeInfo, userInfoID);
		jlong jlExpireTime = env->GetIntField(joCalleeInfo, expireTimeID);

		getFieldValue(env, joUserInfo, cppCalleeInfo.userInfo);
		cppCalleeInfo.expireTime = jlExpireTime;

		env->DeleteLocalRef(joUserInfo);

		return 0;
	}
	
	int JNICommon::setFieldValue(JNIEnv *env, StCalleeInfo cppCalleeInfo, jobject &joCalleeInfo)
	{
		jclass jniClass = env->GetObjectClass(joCalleeInfo);
		if (!jniClass)
		{
			errorf("GET OBJECT CLASS FAILED!!!");
			return -1;
		}
		jfieldID userInfoID = env->GetFieldID(jniClass, "userInfo", USER_INFO_CLASS_SIGN);
		jfieldID expireTimeID = env->GetFieldID(jniClass, "expireTime", JNI_jlong_SIGN);
		env->DeleteLocalRef(jniClass);

		jobject joUserInfo = env->GetObjectField(joCalleeInfo, userInfoID);

		setFieldValue(env, cppCalleeInfo.userInfo, joUserInfo);	
		// Note(guol)
		//	jobject 为指针，java调用jniTest，userInfo.account成功被复制	
		// env->SetObjectField(joCalleeInfo, userInfoID, joUserInfo);
		env->SetLongField(joCalleeInfo, expireTimeID, cppCalleeInfo.expireTime);

		env->DeleteLocalRef(joUserInfo);

		return 0;
	}
}
