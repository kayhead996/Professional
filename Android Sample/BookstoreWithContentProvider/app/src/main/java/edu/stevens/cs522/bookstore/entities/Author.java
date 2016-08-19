package edu.stevens.cs522.bookstore.entities;

import android.content.ContentValues;
import android.database.Cursor;
import android.os.Parcel;
import android.os.Parcelable;

import contracts.AuthorContract;

public class Author implements Parcelable{
	
	// Done Modify this to implement the Parcelable interface.

	// NOTE: middleInitial may be NULL!
	
	public String firstName;
	
	public String middleInitial;
	
	public String lastName;

	public int describeContents()
	{
		return 0;
	}

	public void writeToParcel(Parcel out, int flags) {
		out.writeString(firstName);
		out.writeString(middleInitial);
		out.writeString(lastName);
	}

	public static final Parcelable.Creator<Author> CREATOR
			= new Parcelable.Creator<Author>() {
		public Author createFromParcel(Parcel in) {
			return new Author(in);
		}

		public Author[] newArray(int size) {
			return new Author[size];
		}
	};

	public Author(String fn, String mi, String ln)
	{
		firstName = fn;
		middleInitial = mi;
		lastName = ln;
	}

	private Author(Parcel in) {
		firstName = in.readString();
		middleInitial = in.readString();
		lastName = in.readString();
	}

	public Author(Cursor cursor)
    {
        String name = AuthorContract.getName(cursor);
        String[] author = name.split(" ");
        this.firstName = author[0];

        if (author.length == 2) {
            middleInitial = null;
            lastName = author[1];
        }
        else
        {
            middleInitial = author[1];
            lastName = author[2];
        }
    }

    public void writeToProvider(ContentValues values, long bookfk)
    {
        AuthorContract.putName(values, this.toString());
        AuthorContract.putForeignKey(values, bookfk);
    }

    public String toString()
    {
        String out = new String();

        out += firstName + " ";
        out += middleInitial == null ? "": middleInitial + " ";
        out += lastName == null? "": lastName;
        return out;
    }
}
