package com.xue.firstndk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        System.out.println(JniTest.getString());

        JniTest test = new JniTest();
        test.printHello();
        test.printStr("test print in cpp");
        System.out.println(test.reverseBoolean(true));
        System.out.println(test.toUpperChar('a'));
        System.out.println(test.incShort((short)3));
        System.out.println(test.createIntArr(5));
        System.out.println(test.incLong(45));
        System.out.println(test.getFloat(3.2F));
        System.out.println(test.getDouble(5.54));
        System.out.println(test.charsToString(new char[]{'a','b','c'}));
    }
}
