package cn.geedow.netprotocol;

public class JNIPushLogParams {
    public String account;          // 上传用户账号
    public String logName;          // 日志文件路径
    public String version;          // app version
    public int terminalType;        // 终端类型
    public String deviceModel;      // 设备型号，终端类型为HDC时必传

    public JNIPushLogParams(){
        account = "";
        logName = "";
        version = "";
        terminalType = 6;
        deviceModel = "";
    }
}
