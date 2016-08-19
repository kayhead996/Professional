package edu.stevens.cs522.bookstore.activities;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Parcelable;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.EditText;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

import edu.stevens.cs522.bookstore.R;
import edu.stevens.cs522.bookstore.entities.Author;
import edu.stevens.cs522.bookstore.entities.Book;

public class AddBookActivity extends Activity {
	
	// Use this as the key to return the book details as a Parcelable extra in the result intent.
	public static final String BOOK_RESULT_KEY = "book_result";
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.add_book);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		super.onCreateOptionsMenu(menu);
		MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.addbook_menu, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		super.onOptionsItemSelected(item);
        Intent intent = getIntent();

		// SEARCH: return the book details to the BookStore activity
        switch(item.getItemId())
        {
            case R.id.search:
                intent.putExtra(BOOK_RESULT_KEY, searchBook());
                setResult(BookStoreActivity.SEARCH_REQUEST, intent);
                finish();
                return true;
            case R.id.cancel:
                setResult(RESULT_CANCELED);
                finish();
                return true;
            default:
                return super.onOptionsItemSelected(item);

        }
	}
	
	public Book searchBook(){
		/*
		 * Search for the specified book.
		 */
		// Just build a Book object with the search criteria and return that.

        EditText title = (EditText)findViewById(R.id.search_title);
        EditText author = (EditText)findViewById(R.id.search_author);
        EditText isbn = (EditText)findViewById(R.id.search_isbn);


        List<String> authorList = Arrays.asList(author.getText().toString().split(","));
        Author[] authors = new Author[authorList.size()];
        for (int i = 0; i < authorList.size(); i++)
            authors[i] = new Author(authorList.get(i).trim(), null, null);
        Random r = new Random();
        int price = r.nextInt(50);


		return new Book(0, title.getText().toString(), authors, isbn.getText().toString(), "$" + price);
	}

}