package cn.geedow.netprotocol;

import java.io.Serializable;
import java.util.ArrayList;

import cn.geedow.netprotocol.basicDataStructure.JNITerminalLocalInfo;

public class JNIBasicInfo implements Serializable {
    public ArrayList<JNIServerInfo> serverInfos;    // 服务器信息
    public int terminalType;						// 终端类型
    public String deviceModel;                      // 设置型号，仅硬终端输入
    public JNITerminalLocalInfo localInfo;          // 硬终端使用，表示硬终端独有的能力选项
    public String udid;                			    // 设备唯一标识符
    public String macAddr;                			// 终端Mac地址
    public String appVersion;             			// 应用版本号，如"1.3.5"
    public String appVersionCode;             		// 应用版本号号，如"1351"
    public String serialNumber;           			// 终端序列号
    public String project;                          // 项目，如"alpha"
    public String appKey;                           // 项目，如"e5460e82b254776c86b81d97da2613e7"

    public JNIBasicInfo() {
        serverInfos = new ArrayList<>();
        localInfo = new JNITerminalLocalInfo();
        deviceModel = "";
        udid = "";
        macAddr = "";
        appVersion = "";
        appVersionCode = "";
        serialNumber = "";
        project = "alpha";
        appKey = "";
    }

    @Override
    public String toString() {
        return "JNIBasicInfo{" +
                "terminalType=" + terminalType +
                ", deviceModel='" + deviceModel + '\'' +
                ", udid='" + udid + '\'' +
                ", macAddr='" + macAddr + '\'' +
                ", appVersion='" + appVersion + '\'' +
                ", appVersionCode='" + appVersionCode + '\'' +
                ", serialNumber='" + serialNumber + '\'' +
                ", project='" + project + '\'' +
                ", appKey='" + appKey + '\'' +
                '}';
    }
}
