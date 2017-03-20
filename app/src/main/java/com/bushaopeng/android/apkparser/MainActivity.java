package com.bushaopeng.android.apkparser;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

import com.bushaopeng.android.parseapk.ApkParser;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
//        tv.setText(stringFromJNI());
        parseApk();
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
