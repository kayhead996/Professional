package edu.stevens.cs522.bookstore.entities;

import android.content.ContentValues;
import android.database.Cursor;
import android.os.Parcel;
import android.os.Parcelable;

import contracts.AuthorContract;
import contracts.BookContract;

public class Book implements Parcelable{

	
	public int id;
	
	public String title;
	
	public Author[] authors;
	
	public String isbn;
	
	public String price;

    public Book()
    {
        super();
    }
	public Book(int id, String title, Author[] author, String isbn, String price) {
		this.id = id;
		this.title = title;
		this.authors = author;
		this.isbn = isbn;
		this.price = price;
	}

    private Book(Parcel in) {
        id = in.readInt();
        title = in.readString();
        authors = in.createTypedArray(Author.CREATOR);
        isbn = in.readString();
        price = in.readString();
    }

    public Book(Cursor cursor)
    {
        this.id = BookContract.getID(cursor);
        this.title = BookContract.getTitle(cursor);
        this.authors = authorsFromStr(BookContract.getAuthors(cursor));
        this.isbn = BookContract.getISBN(cursor);
        this.price = BookContract.getPrice(cursor);

    }

    public void writeToProvider(ContentValues values)
    {
        BookContract.putTitle(values, title);
        BookContract.putAuthors(values, authors);
        BookContract.putISBN(values, isbn);
        BookContract.putPrice(values, price);

    }
    public int describeContents()
    {
        return 0;
    }

    public void writeToParcel(Parcel out, int flags) {
        out.writeInt(id);
        out.writeString(title);
        out.writeTypedArray(authors, 0);
        out.writeString(isbn);
        out.writeString(price);
    }


    public static final Parcelable.Creator<Book> CREATOR
            = new Parcelable.Creator<Book>() {
        public Book createFromParcel(Parcel in) {
            return new Book(in);
        }

        public Book[] newArray(int size) {
            return new Book[size];
        }
    };

    public String toString()
    {
        String out = new String();
        out += title;

        return out;
    }

    private Author[] authorsFromStr(String s)
    {
        String[] authors = s.split("\\|");
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