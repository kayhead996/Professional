package edu.stevens.cs522.bookstore.activities;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.Toast;

import edu.stevens.cs522.bookstore.R;

public class CheckoutActivity extends Activity {

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.checkout);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		super.onCreateOptionsMenu(menu);
		//  display ORDER and CANCEL options.
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.checkout_menu, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		super.onOptionsItemSelected(item);
		//
        Intent intent = getIntent();
		int numBooks = 0;
		// ORDER: display a toast message of how many books have been ordered and return
        switch(item.getItemId())
        {
            case R.id.check:
				numBooks = intent.getExtras().getInt(BookStoreActivity.BOOKNUMBERKEY);
                /*numBooks = intent.getParcelableArrayListExtra(BookStoreActivity.SHOPPING_CART).size();
                Toast.makeText(this.getApplicationContext(), numBooks + " book(s) ordered", Toast.LENGTH_SHORT).show();*/
				Toast.makeText(getApplicationContext(), numBooks + " book(s) ordered", Toast.LENGTH_SHORT).show();
                setResult(BookStoreActivity.CHECKOUT_REQUEST);
                finish();
                return true;
            case R.id.cancel:
                setResult(RESULT_CANCELED);
                finish();
                return true;
			default:
				return super.onOptionsItemSelected(item);

        }
		
		// CANCEL: just return with REQUEST_CANCELED as the result code
	}
	
}