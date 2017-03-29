package com.bushaopeng.android.apkparser;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.widget.TextView;

import com.bushaopeng.android.parseapk.ApkParser;

public class MainActivity extends Activity {
    static {
        System.loadLibrary("deamon");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
//        tv.setText(stringFromJNI());
//        parseApk();
        tv.setText("parsing apk");
        startService(MyService.class.getName(), Environment.getExternalStorageDirectory().getAbsolutePath());
    }

    private void parseApk() {
        final String sourceDir = getApplicationInfo().sourceDir;
        new Thread() {
            @Override
            public void run() {
                ApkParser.parseApk(sourceDir);
            }
        }.start();
    }

    public static native int startService(String serviceName, String sdPath);

//    /**
//     * A native method that is implemented by the 'native-lib' native library,
//     * which is packaged with this application.
//     */
//    public native String stringFromJNI();
//
//    // Used to load the 'native-lib' library on application startup.
//    static {
//        System.loadLibrary("native-lib");
//    }
}
