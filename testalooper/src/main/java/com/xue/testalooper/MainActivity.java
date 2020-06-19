package com.xue.testalooper;


import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends Activity implements View.OnClickListener {

    static {
        System.loadLibrary("testalooper");
    }
    Button thread1Button;
    Button thread2Button;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        thread1Button = findViewById(R.id.thread1Button);
        thread1Button.setOnClickListener(this);
        thread2Button = findViewById(R.id.thread2Button);
        thread2Button.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        if (v == thread1Button){
            new Thread(new Runnable() {
                @Override
                public void run() {
                    createLooper();

                }
            }).start();
        }else if(v == thread2Button){
            createLooper2();//createLooper2创建了一个native线程，然后通过管道向线程发送文字。子线程用looper实时接收消息

        }
    }

    native void createLooper();
    native void createLooper2();
}
