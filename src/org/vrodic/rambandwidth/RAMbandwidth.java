/*
 * 
 */

package org.vrodic.rambandwidth;

import android.app.Activity;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class RAMbandwidth extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        setContentView(R.layout.main);
   	 	final EditText ed1 = (EditText) findViewById(R.id.editText1);
   	 	final EditText ed2 = (EditText) findViewById(R.id.editText2);
   	 	ed1.setText("20");
   	 	ed2.setText("20");
        
        final Button button = (Button) findViewById(R.id.button1);
        button.setOnClickListener(new View.OnClickListener()
        {
                public void onClick(View v)
                {
                	
                	 TextView  tv = (TextView) findViewById(R.id.result);
                	
                	 
                	
                	 double mt = Double.parseDouble(ed1.getText().toString());
                	 int nr_loops = Integer.parseInt(ed2.getText().toString());
                     
                       tv.setText( Double.toString(testMBW(mt, nr_loops)) + " MB/sec");
                    
                }
        });

        
        
       
        
        

    }
 

    public native double testMBW(double mt, int nr_loops);
    
    static {
        System.loadLibrary("rambw");
    }
}