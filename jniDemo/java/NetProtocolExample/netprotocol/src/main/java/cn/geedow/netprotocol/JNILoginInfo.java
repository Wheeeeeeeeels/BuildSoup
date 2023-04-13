package cn.geedow.netprotocol;

import java.io.Serializable;

import cn.geedow.netprotocol.basicDataStructure.JNICompanyInfo;
import cn.geedow.netprotocol.basicDataStructure.JNIUserInfo;

public class JNILoginInfo  implements Serializable {
    public JNIUserInfo userInfo;
    public String token;
    public JNICompanyInfo companyInfo;
    public long serverTimestamp;
	public boolean isFirstLogin;
	public boolean isPrivateDeploy;
	public boolean loginStatus;

    @Override
    public String toString() {
        return "JNILoginInfo{" +
                "userInfo=" + userInfo +
                ", token='" + token + '\'' +
                ", companyInfo=" + companyInfo +
                ", serverTimestamp=" + serverTimestamp +
                ", isFirstLogin=" + isFirstLogin +
                ", isPrivateDeploy=" + isPrivateDeploy +
                ", loginStatus=" + loginStatus +
                '}';
    }

    public JNILoginInfo(){
        userInfo = new JNIUserInfo();
        token = "";
        companyInfo = new JNICompanyInfo();
        serverTimestamp = 0;
        isFirstLogin = false;
        isPrivateDeploy = false;
        loginStatus = false;
    }

}