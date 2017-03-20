package com.bushaopeng.android.parseapk.utils;

import android.util.Log;

/**
 * Created by bushaopeng on 17/2/8.
 */
public class LogUtils {
    private static final String TAG = "parseApk";

    public static void log(Object msg) {
        if (msg == null) {
            return;
        }
        Log.i(TAG, msg.toString());
    }

    public static void logDiv() {
        log("==============================");
    }

    public static void logEach(Object... msgs) {
        for (Object msg : msgs) {
            System.out.print(msg.toString());
            System.out.print("\t");
        }
        System.out.print("\n");
    }

    public static void logOpcode(int opCode) {
        LogUtils.log("指令：" + getOpName(opCode));
    }

    public static String getOpName(int opCode) {
        return Utils.getOpMap().get(opCode);
    }
}
