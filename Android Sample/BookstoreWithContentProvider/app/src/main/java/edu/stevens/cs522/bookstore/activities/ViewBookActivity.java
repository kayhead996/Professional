package edu.stevens.cs522.bookstore.activities;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import edu.stevens.cs522.bookstore.R;
import edu.stevens.cs522.bookstore.entities.Book;

public class ViewBookActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_view_book);

        Intent intent = getIntent();

        Book book = intent.getParcelableExtra(BookStoreActivity.BOOKVIEWKEY);


        ((TextView)findViewById(R.id.display_title)).setText(book.title);

        TextView authorView = ((TextView) findViewById(R.id.display_author));

        for (int i = 0; i < book.authors.length; i++) {
            authorView.append(book.authors[i].toString().trim());
            if (i != book.authors.length - 1)
                authorView.append(", ");
        }
        ((TextView)findViewById(R.id.display_isbn)).setText(book.isbn);
        ((TextView)findViewById(R.id.display_price)).setText(book.price);
    }
}
