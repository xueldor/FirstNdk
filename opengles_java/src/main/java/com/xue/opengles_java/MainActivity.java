package com.xue.opengles_java;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;

public class MainActivity extends Activity {
    GLSurfaceView mGLView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mGLView = new ExampleGLSurfaceView(this);
        setContentView(mGLView);
    }

    @Override
    protected void onResume() {
        super.onResume();
        mGLView.onResume();
    }
    @Override
    protected void onPause() {
        super.onPause();
        //opengl渲染可能非常密集。调用onPause确保activity不活动时不占用太多资源
        mGLView.onPause();
    }

}
