/* Queue.java
 *
 * "I pledge my honor that I have abided by the Stevens Honor System
 *
 * Keyur Ved (c) 2014
 *
 */
package week7;

/**
 * Emulates a Queue data type.
 *
 * @author Keyur Ved
 * @version 1.0
 * @since 20141010
 *
 */
public class Queue {
    /**
     * This implementation of a Queue uses an array.
     *
     */
    private int[] array;
    private int front;
    private int back;

    public Queue(){
        this(50);
    }

    public Queue(int i) {
        array = new int[i];
        front = -1;
        back = 0;
    }

    /**
     * Returns the current size of the Queue
     *
     * @return The size of the Queue
     */
    public int size() {
        int size = (front+1) - back;
        return size;
    }

    /**
     * Adds a value to the back of the Queue, or prints an error if the Queue is full.
     *
     * @param   i   The value to add to the Queue
     *
     */
    public void enqueue(int n) {
        
        front++;
        if  (this.full()){
            System.out.println("Error: Queue size exceeded");
            front = array.length-1;
        }
        else {
            for (int i = front; i>back; i--) {
                array[i] = array[i-1];
            }
            array[back]=n;
        }
    }

    /**
     * Removes the first value from the Queue or prints an error if the Queue is empty.
     *
     * @return  The first value in the queue
     *
     */

    public int dequeue() {
        int value = -1;

        if (this.empty()){
            System.out.println("Error: Queue is empty, printing a -1");
        }
        else {
            value = array[front];
            front--;
        }

        return value;
    }
    
    /**
     * Checks if the Queue is empty
     *
     * @return  If the Queue is empty or not
     *
     */
    public boolean empty() {
        boolean bool = false;

        if (this.size()<=0) {
            bool = true;
        }

        return bool;
    }

    /**
     * Returns the first value in the Queue without removing it
     *
     * @return  The first value in the Queue
     *
     */
    public int peek() {
        int value = -1;

        if (this.empty()){
            System.out.println("Empty: printing a -1");
        }
        else {
            value = array[front];
        }

        return value;
    }

    /**
     * Checks if the Queue is full
     *
     * @return  If the Queue is full or not
     *
     */
    public boolean full() {
        boolean bool = false;

        if (front >= array.length){
            bool = true;
        }
        
        return bool;
    }

    /**
     * Returns a String representation of this Queue
     *
     * @return  The String representation of this Queue
     *
     */
    public String toString() {
        String s = new String();
        for (int i = back; i<=front; i++){
            s += array[i] + " ";
        }
        return s;
    }
}

