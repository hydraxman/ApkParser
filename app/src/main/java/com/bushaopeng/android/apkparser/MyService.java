package com.bushaopeng.android.apkparser;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import com.bushaopeng.android.parseapk.utils.LogUtils;

public class MyService extends Service {
    public MyService() {
    }

    @Override
    public void onCreate() {
        super.onCreate();
        LogUtils.log("MyService onCreate ");

    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        LogUtils.log("onStartCommand onStartCommand ");
        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
}
