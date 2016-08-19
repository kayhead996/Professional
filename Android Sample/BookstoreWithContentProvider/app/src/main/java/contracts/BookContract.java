package contracts;

import android.content.ContentValues;
import android.database.Cursor;
import android.net.Uri;

import java.util.ArrayList;
import java.util.regex.Pattern;

import edu.stevens.cs522.bookstore.entities.Author;

/**
 * Created by keyur on 2/13/16.
 */
public final class BookContract
{

    public static final String BOOK_TABLE = "Book";
    public static final String TITLE = "title";
    public static final String AUTHORS = "authors";
    public static final String ISBN = "isbn";
    public static final String PRICE = "price";
    public static final String _ID = "_id";
    public static final char SEPARATOR_CHAR = ',';
    private static final Pattern SEPARATOR =
            Pattern.compile(Character.toString(SEPARATOR_CHAR),	Pattern.LITERAL);


    public static final String AUTHORITY = "edu.stevens.cs522.bookstore";
    public static final String PATH = BOOK_TABLE;
    public static final Uri BOOK_URI = CONTENT_URI(AUTHORITY, PATH);

    public static String CONTENT_PATH(Uri uri)
    {
        return uri.getPath().substring(1);
    }

    public static Uri CONTENT_URI(String authority, String path)
    {
        return new Uri.Builder().scheme("content").authority(authority).path(path).build();
    }

    public static Uri withExtendedPath(Uri uri, String[] path)
    {
        Uri.Builder builder = uri.buildUpon();

        for (String p : path)
            builder.appendPath(p);

        return builder.build();
    }

    public static long getId(Uri uri)
    {
        return Long.parseLong(uri.getLastPathSegment());
    }
    public static String contentType(Uri content)
    {
        return "vnd.android.cursor/vnd." + AUTHORITY + "." + content + "s";
    }

    public static String contentItemType(Uri content)
    {
        return "vnd.android.cursor.item/vnd." + AUTHORITY + "." + content;
    }

    public static String getTitle(Cursor cursor)
    {
        return cursor.getString(cursor.getColumnIndexOrThrow(TITLE));
    }


    public static String getISBN(Cursor cursor)
    {
        return cursor.getString(cursor.getColumnIndexOrThrow(ISBN));
    }

    public static String getPrice(Cursor cursor) {
        return cursor.getString(cursor.getColumnIndexOrThrow(PRICE));
    }

    public static int getID(Cursor cursor)
    {
        return cursor.getInt(cursor.getColumnIndexOrThrow(_ID));
    }

    public static String getAuthors(Cursor cursor)
    {
        return cursor.getString(cursor.getColumnIndexOrThrow(AUTHORS));
    }

    public static void putTitle(ContentValues values, String title)
    {
        values.put(TITLE, title);
    }

    public static void putAuthors(ContentValues values, Author[] authors)
    {
        String author = new String();
        for (int i = 0; i < authors.length; i++)
        {
            author += authors[i];
            if (i != authors.length - 1)
                author += ", ";
        }
        values.put(AUTHORS, author);
    }

    public static void putISBN(ContentValues values, String isbn)
    {
        values.put(ISBN, isbn);
    }

    public static void putPrice(ContentValues values, String price)
    {
        values.put(PRICE, price);
    }

    public static void putID(ContentValues values, int id)
    {
        values.put(_ID, id);
    }

    public static String[] readStringArray(String in)	{
        return SEPARATOR.split(in);
    }

    public static Author[] strToAuthors(String s)
    {
        String[] authors = BookContract.readStringArray(s);
        Author[] authorList = new Author[authors.length];
        String fn, mn, ln;

        for (int i = 0; i < authors.length; i++)
        {
            String[] name = authors[i].split(" ");
            fn = name[0];

            if (name.length == 2)
            {
                mn = null;
                ln = name[1];
            }
            else if (name.length > 2)
            {
                mn = name[1];
                ln = name[2];
            }
            else
            {
                mn = "";
                ln = "";
            }

            authorList[i] = new Author(fn, mn, ln);
        }

        return authorList;
    }
}

