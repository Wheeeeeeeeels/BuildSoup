package cn.geedow.netprotocol.basicDataStructure;

public class JNITerminalLocalInfo {
    public String ability;                  // 设备能力集枚举：MultiCastPlay多屏能力；ScreenShare屏幕分享
    public String functionality;            // 设备功能：json字符串，数据内容及格式由硬终端和web端协定

    public JNITerminalLocalInfo(){
        ability = "";
        functionality = "";
    }
}
