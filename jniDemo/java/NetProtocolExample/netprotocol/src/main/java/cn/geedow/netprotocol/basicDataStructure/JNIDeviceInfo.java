package cn.geedow.netprotocol.basicDataStructure;

import java.io.Serializable;

public class JNIDeviceInfo implements Serializable {
    public String serialNumber;                 // 设备序列号
    public String deviceModel;                  // 设备型号
    public String deviceName;                   // 设备名
    public String deviceOrgName;                // 设备所属组织名
    public String deviceVersion;                // 设备程序版本

    public JNIDeviceInfo(){
        serialNumber = "";
        deviceModel = "";
        deviceName = "";
        deviceOrgName = "";
        deviceVersion = "";
    }
}
