package edu.stevens.cs522.bookstore.activities;

import java.util.ArrayList;

import android.app.ListActivity;
import android.app.LoaderManager;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.CursorLoader;
import android.content.Intent;
import android.content.Loader;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.ActionMode;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.Toast;

import com.google.android.gms.appindexing.Action;

import adapters.BookAdapter;
import contracts.BookContract;
import edu.stevens.cs522.bookstore.R;
import edu.stevens.cs522.bookstore.entities.Book;

public class BookStoreActivity extends ListActivity implements LoaderManager.LoaderCallbacks<Cursor> {

    // Use this when logging errors and warnings.
    private static final String TAG = BookStoreActivity.class.getCanonicalName();

    // These are request codes for subactivity request calls
    static final private int ADD_REQUEST = 1;

    static final public int CHECKOUT_REQUEST = ADD_REQUEST + 1;

    static final public int SEARCH_REQUEST = CHECKOUT_REQUEST + 1;

    // There is a reason this must be an ArrayList instead of a List.
    private ArrayList<Book> shoppingCart;


    // Key for shopping cart
    static final public String SHOPPING_CART = "shopcart";
    static final public String BOOK_VIEW = "books";
    static final public String BOOKNUMBERKEY = "booknumberkey";
    static final public String BOOKVIEWKEY = "bookviewkey";
    private static final int LOADER_ID = 1;

    static private ListView bookListView;
    static private Cursor cursor;
    static private BookAdapter cursorAdapter;
    static private ContentResolver cr;
    static private CursorLoader loader;
    static private ArrayList<Long> checkedItemList = new ArrayList<>();


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //  Set the layout (use cart.xml layout)
        setContentView(R.layout.cart);

        LoaderManager lm = getLoaderManager();
        loader = (CursorLoader)lm.initLoader(LOADER_ID, null, this);
        //  use an array adapter to display the cart contents.
        bookListView = (ListView) findViewById(android.R.id.list);

        cursorAdapter = new BookAdapter(this, null);
        setListAdapter(cursorAdapter);
        cursorAdapter.swapCursor(cursor);
        cr = getContentResolver();
        bookListView.setChoiceMode(bookListView.CHOICE_MODE_SINGLE);
        bookListView.setChoiceMode(bookListView.CHOICE_MODE_MULTIPLE_MODAL);
        bookListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                cursor = cr.query(BookContract.withExtendedPath(BookContract.BOOK_URI, new String[]{Long.toString(id)}), null, null, new String[]{Long.toString(id)}, null);
                cursor.moveToFirst();
                Book book = new Book(cursor);
                Intent intent = new Intent(view.getContext(), ViewBookActivity.class);
                intent.putExtra(BOOKVIEWKEY, book);
                startActivity(intent);
            }
        });
        bookListView.setMultiChoiceModeListener(new AbsListView.MultiChoiceModeListener() {
            public boolean onCreateActionMode(ActionMode mode, Menu menu) {
                mode.setTitle(getString(R.string.options));
                mode.getMenuInflater().inflate(R.menu.bookstore_context_menu, menu);
                return true;
            }
            public boolean onPrepareActionMode(ActionMode mode, Menu menu) {
                return false;
            }

            public void onItemCheckedStateChanged(ActionMode mode, int position, long id, boolean checked) {
                if (checked)
                    checkedItemList.add(id);
                else {
                    for (int i = 0; i < checkedItemList.size(); i++) {
                        if (checkedItemList.get(i) == id)
                            checkedItemList.remove(i);
                    }
                }

                mode.setTitle(checkedItemList.size() + " book(s) selected");
            }


            public boolean onActionItemClicked(ActionMode mode, MenuItem item) {
                switch (item.getItemId()) {
                    case R.id.delete:
                        for (int i = 0; i < checkedItemList.size(); i++) {
                            cr.delete(BookContract.withExtendedPath(BookContract.BOOK_URI, new String[]{Long.toString(checkedItemList.get(i))}), null, null);
                        }
                        cursor = cr.query(BookContract.BOOK_URI, null, null, null, null);
                        cursorAdapter.swapCursor(cursor);
                        mode.finish();
                        break;
                }
                return true;
            }

            public void onDestroyActionMode(ActionMode mode) {
                mode = null;
            }


        });
    }

    public Loader<Cursor> onCreateLoader(int loaderID, Bundle bundle) {

        switch (loaderID)
        {
            case LOADER_ID:
                return new CursorLoader(this, BookContract.BOOK_URI, null, null, null, null);
            default:
                return null;
        }
    }

    public void onLoadFinished(Loader<Cursor> loader, Cursor cursor)
    {
        switch (loader.getId())
        {
            case LOADER_ID:
                this.cursorAdapter.swapCursor(cursor);
                break;
        }
    }

    public void onLoaderReset(Loader<Cursor> loader)
    {
        switch(loader.getId())
        {
            case LOADER_ID:
                this.cursorAdapter.swapCursor(null);
        }
    }

    @Override
	public boolean onCreateOptionsMenu(Menu menu) {
		super.onCreateOptionsMenu(menu);

		// provide ADD, DELETE and CHECKOUT options
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.bookstore_menu, menu);


		return true;
	}


	@Override
	public boolean onOptionsItemSelected(MenuItem item) {

        AdapterView.AdapterContextMenuInfo info =
                (AdapterView.AdapterContextMenuInfo) item.getMenuInfo();

        Intent addIntent;

        // ADD provide the UI for adding a book
        switch (item.getItemId()) {
            case R.id.add:
                addIntent = new Intent(this, AddBookActivity.class);
                startActivityForResult(addIntent, ADD_REQUEST);
                return true;
            case R.id.delete:
                for (int i = 0; i < checkedItemList.size(); i++)
                {
                    long id = checkedItemList.get(i);
                    cr.delete(BookContract.withExtendedPath(BookContract.BOOK_URI, new String[] {Long.toString(id)}), null, new String[] {Long.toString(id)});
                }
                cursor = cr.query(BookContract.BOOK_URI, null, null, null, null);
                cursorAdapter.swapCursor(cursor);
                return true;
            case R.id.checkout:
                cursor = cr.query(BookContract.BOOK_URI, null, null, null, null);
                cursor.moveToFirst();
                int size = cursor.getCount();
                if (size == 0)
                {
                    Toast.makeText(getApplicationContext(), "Error: cart is empty", Toast.LENGTH_SHORT).show();
                }
                else
                {
                    Intent checkoutIntent = new Intent(this, CheckoutActivity.class);
                    checkoutIntent.putExtra(BOOKNUMBERKEY, size);
                    startActivityForResult(checkoutIntent, CHECKOUT_REQUEST);
                }
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }


        // CHECKOUT provide the UI for checking out
    }

	@Override
	protected void onActivityResult(int requestCode, int resultCode,
									Intent intent) {
		super.onActivityResult(requestCode, resultCode, intent);
		// Handle results from the Search and Checkout activities.

        // Use SEARCH_REQUEST and CHECKOUT_REQUEST codes to distinguish the cases.

		// SEARCH: add the book that is returned to the shopping cart.
        switch (resultCode)
        {
            case SEARCH_REQUEST:
                Book book = (Book)intent.getParcelableExtra(AddBookActivity.BOOK_RESULT_KEY);
                ContentValues values = new ContentValues();
                book.writeToProvider(values);
                cr.insert(BookContract.BOOK_URI, values);
                cursor = cr.query(BookContract.BOOK_URI, null, null, null, null);
                cursorAdapter.swapCursor(cursor);
                break;
            case CHECKOUT_REQUEST:
                cr.delete(BookContract.BOOK_URI, null, null);
                cursor = cr.query(BookContract.BOOK_URI, null, null, null, null);
                cursorAdapter.swapCursor(cursor);
                break;
            default:
                break;
        }

		// CHECKOUT: empty the shopping cart.

	}

	@Override
	public void onSaveInstanceState(Bundle savedInstanceState) {
		// save the shopping cart contents (which should be a list of parcelables).
        savedInstanceState.putParcelableArrayList(SHOPPING_CART, shoppingCart);
        super.onSaveInstanceState(savedInstanceState);
	}

	@Override
	public void onStart() {
		super.onStart();

		Action viewAction = Action.newAction(
				Action.TYPE_VIEW, // TODO: choose an action type.
				"BookStore Page", // TODO: Define a title for the content shown.
				// TODO: If you have web page content that matches this app activity's content,
				// make sure this auto-generated web page URL is correct.
				// Otherwise, set the URL to null.
				Uri.parse("http://host/path"),
				// TODO: Make sure this auto-generated app deep link URI is correct.
				Uri.parse("android-app://edu.stevens.cs522.bookstore.activities/http/host/path")
		);
	}

	@Override
	public void onStop() {
		super.onStop();


		Action viewAction = Action.newAction(
				Action.TYPE_VIEW, // TODO: choose an action type.
				"BookStore Page", // TODO: Define a title for the content shown.
				// TODO: If you have web page content that matches this app activity's content,
				// make sure this auto-generated web page URL is correct.
				// Otherwise, set the URL to null.
				Uri.parse("http://host/path"),
				// TODO: Make sure this auto-generated app deep link URI is correct.
				Uri.parse("android-app://edu.stevens.cs522.bookstore.activities/http/host/path")
		);

	}
}