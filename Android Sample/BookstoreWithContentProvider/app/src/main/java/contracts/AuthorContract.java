package contracts;

import android.content.ContentValues;
import android.database.Cursor;
import android.net.Uri;

/**
 * Created by keyur on 2/13/16.
 */
public final class AuthorContract {
    public static final String AUTHOR_TABLE= "Author";
    public static final String NAME = "name";
    public static final String _ID = "_id";
    public static final String BOOKFOREIGNKEY = "book_fk";
    public static final String INDEX = "AuthorBookIndex";

    public static final String AUTHORITY = "edu.stevens.cs522.bookstore";
    public static final String PATH = AUTHOR_TABLE;
    public static final Uri CONTENT_URI = CONTENT_URI(AUTHORITY, PATH);

    public static Uri withExtendedPath(Uri uri, String[] path)
    {
        Uri.Builder builder = uri.buildUpon();

        for (String p : path)
            builder.appendPath(p);

        return builder.build();
    }

    public static Uri CONTENT_URI(String authority, String path)
    {
        return new Uri.Builder().scheme("content").authority(authority).path(path).build();
    }


    public static String contentType(String content)
    {
        return "vnd.android.cursor/vnd." + AUTHORITY + "." + content + "s";
    }

    public static String contentItemType(String content)
    {
        return "vnd.android.cursor.item/vnd." + AUTHORITY + "." + content;
    }
    public static String getName(Cursor cursor)
    {
        return cursor.getString(cursor.getColumnIndexOrThrow(NAME));
    }

    public static String getId(Cursor cursor)
    {
        return cursor.getString(cursor.getColumnIndexOrThrow(_ID));
    }

    public static String getForeignKey(Cursor cursor)
    {
        return cursor.getString(cursor.getColumnIndexOrThrow(BOOKFOREIGNKEY));
    }

    public static void putName(ContentValues values, String name)
    {
        values.put(NAME, name);
    }

    public static void putID(ContentValues values, String id)
    {
        values.put(_ID, id);
    }

    public static void putForeignKey(ContentValues values, long fk)
    {
        values.put(BOOKFOREIGNKEY, fk);
    }
}
