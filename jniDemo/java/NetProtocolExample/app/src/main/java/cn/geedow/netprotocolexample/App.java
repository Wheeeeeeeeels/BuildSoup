package cn.geedow.netprotocolexample;

import android.app.Application;

import com.tencent.bugly.crashreport.CrashReport;

public class App extends Application {
    @Override
    public void onCreate() {
        super.onCreate();

        CrashReport.UserStrategy strategy = new CrashReport.UserStrategy(this);
        strategy.setAppVersion(BuildConfig.VERSION_NAME);

        CrashReport.initCrashReport(this,"e62267137a",true, strategy);
    }
}
