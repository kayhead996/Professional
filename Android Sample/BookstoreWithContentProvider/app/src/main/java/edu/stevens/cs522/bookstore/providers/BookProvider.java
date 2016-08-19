package edu.stevens.cs522.bookstore.providers;

import android.content.ContentProvider;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Context;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.net.Uri;
import android.util.Log;

import contracts.AuthorContract;
import contracts.BookContract;
import edu.stevens.cs522.bookstore.entities.Author;

/**
 * Created by keyur on 2/26/16.
 */
public class BookProvider extends ContentProvider
{
    private static final String DATABASE_NAME = "cart.db";
    private static final int DATABASE_VERSION = 1;
    private SQLiteDatabase db;
    private DatabaseHelper dbHelper;

    private static final String DATABASE_CREATE1 = "CREATE TABLE " + BookContract.BOOK_TABLE + " ("
            + BookContract._ID    + " INTEGER PRIMARY KEY AUTOINCREMENT, "
            + BookContract.TITLE + " TEXT NOT NULL, "
            + BookContract.ISBN  + " TEXT, "
            + BookContract.PRICE + " TEXT NOT NULL);";

    private static final String DATABASE_CREATE2 = "CREATE TABLE " + AuthorContract.AUTHOR_TABLE + " ("
            + AuthorContract._ID + " INTEGER PRIMARY KEY AUTOINCREMENT, "
            + AuthorContract.NAME  + " TEXT NOT NULL, "
            + AuthorContract.BOOKFOREIGNKEY + " INTEGER NOT NULL, "
            + "FOREIGN KEY ("+ AuthorContract.BOOKFOREIGNKEY+") " +
            "REFERENCES "+BookContract.BOOK_TABLE+"("+BookContract._ID+") ON DELETE CASCADE);";
    private static final String DATABASE_CREATE3 = "CREATE INDEX " + AuthorContract.INDEX + " ON " +
            AuthorContract.AUTHOR_TABLE + "(" + AuthorContract.BOOKFOREIGNKEY + ");";

    private static final int ALL_ROWS = 1;
    private static final int SINGLE_ROW = 2;

    private static final String CONTENT_PATH = BookContract.CONTENT_PATH(BookContract.BOOK_URI);
    private static final String CONTENT_PATH_ITEM = BookContract.CONTENT_PATH(BookContract.withExtendedPath(BookContract.BOOK_URI, new String[] {"#"}));

    private static final UriMatcher uriMatcher = new UriMatcher(UriMatcher.NO_MATCH);


    public BookProvider()
    {
        dbHelper = new DatabaseHelper(getContext(), DATABASE_NAME, null, DATABASE_VERSION);
    }
    public BookProvider(Context context)
    {
        this.dbHelper = new DatabaseHelper(context, DATABASE_NAME, null, DATABASE_VERSION);
    }
    public boolean onCreate()
    {
        dbHelper = new DatabaseHelper(getContext(), DATABASE_NAME, null, DATABASE_VERSION);
        db = dbHelper.getWritableDatabase();
        db.execSQL("PRAGMA foreign_keys=ON;");
        uriMatcher.addURI(BookContract.AUTHORITY, CONTENT_PATH, ALL_ROWS);
        uriMatcher.addURI(BookContract.AUTHORITY, CONTENT_PATH_ITEM, SINGLE_ROW);

        return true;
    }

    public Cursor query(Uri uri, String[] projection, String selection, String[] selectionArgs, String sort)
    {
        String query;
        switch (uriMatcher.match(uri))
        {
            case ALL_ROWS:
                query = "SELECT " + BookContract.BOOK_TABLE + "." + BookContract._ID + ", " +
                        BookContract.TITLE + ", " +
                        BookContract.PRICE + ", " +
                        BookContract.ISBN + ", " +
                        "GROUP_CONCAT(" + AuthorContract.NAME + ",'|') as " + BookContract.AUTHORS +
                        " FROM " + BookContract.BOOK_TABLE + " LEFT OUTER JOIN " + AuthorContract.AUTHOR_TABLE + " ON " +
                        BookContract.BOOK_TABLE + "." + BookContract._ID + "=" +
                        AuthorContract.AUTHOR_TABLE + "." + AuthorContract.BOOKFOREIGNKEY +
                        " GROUP BY " + BookContract.BOOK_TABLE + "." + BookContract._ID + ", " +
                        BookContract.TITLE + ", " + BookContract.PRICE + ", " + BookContract.ISBN;
                return db.rawQuery(query, null);
            case SINGLE_ROW:
                query = "SELECT " + BookContract.BOOK_TABLE + "." + BookContract._ID + ", " +
                        BookContract.TITLE + ", " +
                        BookContract.PRICE + ", " +
                        BookContract.ISBN + ", " +
                        "GROUP_CONCAT(" + AuthorContract.NAME + ",'|') as " + BookContract.AUTHORS +
                        " FROM " + BookContract.BOOK_TABLE + " LEFT OUTER JOIN " + AuthorContract.AUTHOR_TABLE + " ON " +
                        BookContract.BOOK_TABLE + "." + BookContract._ID + "=" +
                        AuthorContract.AUTHOR_TABLE + "." + AuthorContract.BOOKFOREIGNKEY + " WHERE "+
                        BookContract.BOOK_TABLE + "." + BookContract._ID + "=?" +
                        " GROUP BY " + BookContract.BOOK_TABLE + "." + BookContract._ID + ", " +
                        BookContract.TITLE + ", " +
                        BookContract.PRICE + ", " +
                        BookContract.ISBN;
                return db.rawQuery(query, selectionArgs);
            default:
                throw new IllegalArgumentException("Unmatched URI: " + uri);
        }


    }

    public Uri insert(Uri uri, ContentValues values)
    {
        Object authorObj = values.get(BookContract.AUTHORS);
        values.remove(BookContract.AUTHORS);
        long row = db.insert(BookContract.BOOK_TABLE, null, values);

        if (row > 0 && authorObj != null)
        {
            Author[] authors = BookContract.strToAuthors(authorObj.toString());
            for (Author author: authors)
            {
                ContentValues value2 = new ContentValues();
                author.writeToProvider(value2, row);
                db.insert(AuthorContract.AUTHOR_TABLE, null, value2);
            }

            Uri instanceUri = BookContract.withExtendedPath(BookContract.BOOK_URI, new String[]{Long.toString(row)});

            ContentResolver cr = getContext().getContentResolver();
            cr.notifyChange(instanceUri, null);

            return instanceUri;
        }

        throw new SQLException("Insertion Failed");
    }

    public int delete(Uri uri, String where, String[] whereArgs)
    {
        long count;
        switch (uriMatcher.match(uri))
        {
            case ALL_ROWS:
                count = db.delete(BookContract.BOOK_TABLE, where, whereArgs);
                break;
            case SINGLE_ROW:
                where = BookContract._ID + "= ?";
                whereArgs = new String[] {uri.getLastPathSegment()};
                count = db.delete(BookContract.BOOK_TABLE, where, whereArgs);
                break;
            default:
                throw new IllegalArgumentException("Unmatched URI: " + uri);
        }
        Uri instanceUri = BookContract.withExtendedPath(BookContract.BOOK_URI, new String[] {Long.toString(count)});

        ContentResolver cr = getContext().getContentResolver();
        cr.notifyChange(instanceUri, null);

        return (int)count;
    }

    public int update(Uri uri, ContentValues values, String where, String[] whereArgs) {
        Object authorObj = values.get(BookContract.AUTHORS);
        long row = db.update(BookContract.BOOK_TABLE, values, where, whereArgs);

        if (row > 0 && authorObj != null) {
            Author[] authors = BookContract.strToAuthors(authorObj.toString());
            for (Author author : authors) {
                ContentValues value2 = new ContentValues();
                author.writeToProvider(value2, row);
                db.update(AuthorContract.AUTHOR_TABLE, value2, where, whereArgs);
            }

            Uri instanceUri = BookContract.withExtendedPath(BookContract.BOOK_URI, new String[] {Long.toString(row)});

            ContentResolver cr = getContext().getContentResolver();
            cr.notifyChange(instanceUri, null);

            return (int)row;
        }

        throw new SQLException("Update Failed");
    }

    public String getType(Uri uri)
    {
        switch (uriMatcher.match(uri))
        {
            case ALL_ROWS:
                return BookContract.contentType(uri);
            case SINGLE_ROW:
                return BookContract.contentType(uri);
            default:
                return null;
        }
    }


    private static class DatabaseHelper extends SQLiteOpenHelper
    {
        public DatabaseHelper(Context context, String name,
                              SQLiteDatabase.CursorFactory factory, int version)
        {
            super(context, name, factory, version);
        }

        public void onCreate(SQLiteDatabase _db)
        {
            _db.execSQL("PRAGMA foreign_keys=ON;");
            _db.execSQL(DATABASE_CREATE1);
            _db.execSQL(DATABASE_CREATE2);
            _db.execSQL(DATABASE_CREATE3);
        }

        public void onUpgrade(SQLiteDatabase _db, int _oldVersion, int _newVersion)
        {
            _db.execSQL("DROP TABLE IF EXISTS" + BookContract.BOOK_TABLE);
            _db.execSQL("DROP TABLE IF EXISTS" + AuthorContract.AUTHOR_TABLE);
            onCreate(_db);
        }
    }
}
