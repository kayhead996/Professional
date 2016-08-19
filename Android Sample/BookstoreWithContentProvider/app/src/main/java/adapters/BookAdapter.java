package adapters;

import android.content.Context;
import android.database.Cursor;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ResourceCursorAdapter;
import android.widget.TextView;

import edu.stevens.cs522.bookstore.entities.Book;

/**
 * Created by keyur on 2/26/16.
 */
public class BookAdapter extends ResourceCursorAdapter
{
    protected final static int ROW_LAYOUT = android.R.layout.simple_list_item_2;

    public BookAdapter(Context context, Cursor cursor)
    {
        super(context, ROW_LAYOUT, cursor, 0);
    }

    public View newView(Context context, Cursor cursor, ViewGroup parent)
    {
        LayoutInflater inflater = (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        return inflater.inflate(ROW_LAYOUT, parent, false);
    }

    public void bindView(View view, Context context, Cursor cursor)
    {
        TextView titleLine = (TextView) view.findViewById(android.R.id.text1);
        TextView authorLine = (TextView) view.findViewById(android.R.id.text2);

        Book book = new Book(cursor);
        titleLine.setText(book.title);
        authorLine.setText(book.authors[0].toString());

    }
}


