/* StackFromQueue.java
 *
 * "I pledge my honor that I have abided by the Stevens Honor System
 *
 * Keyur Ved (c) 2014
 *
 */
package week7;

/**
 * Emulates a Stack data type
 *
 * @author Keyur Ved
 * @version 1.0
 * @since 20141015
 *
 */
public class StackFromQueue {
    /**
     * This implementation of a Stack uses two Queues
     *
     */
    private Queue storageQueue;
    private Queue tempQueue;

    public StackFromQueue() {
        this(50);
    }

    public StackFromQueue(int i) {

        storageQueue = new Queue(i);
        tempQueue = new Queue(i);
    }

    /**
     * Returns the current size of StackFromQueue
     *
     * @return  The size of the StackFromQueue
     *
     */
    public int size() {

        int value = storageQueue.size();

        return value;
    }

    /**
     * Adds a value to the top of the StackFromQueue
     *
     * @param   i   The value to add to the top of the StackFromQueue
     *
     */
    public void push(int i) {

        if (this.full()) {
            System.out.println("Stack is full");
        }
        else {
            storageQueue.enqueue(i);
        }
    }

    /**
     * Gets the first value in the StackFromQueue
     *
     * @return  The first value in StackFromQueue
     */
    public int pop() {
        int value = -1;
        
        if (this.empty()) {
            System.out.println("Stack is empty: printing a -1");
        }
        else {
            while (storageQueue.size() > 1) {
                tempQueue.enqueue(storageQueue.dequeue());
            }
            value = storageQueue.dequeue();
            Queue q1 = tempQueue;
            tempQueue = storageQueue;
            storageQueue = q1;
        }
        return value;  
    }

    /**
     * Checks if the StackFromQueue is empty
     *
     * @return  Whether the StackFromQueue is empty or not
     *
     */
    public boolean empty() {
        return (storageQueue.empty());
    }

    /**
     * Checks if the StackFromQueue is full
     *
     * @return  Whether the StackFromQueue is full or not
     *
     */
    public boolean full() {
        return (storageQueue.full());
    }

    /**
     * Shows the first value in the StackFromQueue
     *
     * @return  The first value in the StackFromQueue
     *
     */
    public int peek() {
        
        int value = -1;
        
        if (this.empty()){
            System.out.println("StackFromQueue is empty: printing -1");
        }
        else {
            while (storageQueue.size() > 1) {
                tempQueue.enqueue(storageQueue.dequeue());
            }

            value = storageQueue.peek();
            Queue q1 = tempQueue;
            tempQueue = storageQueue;
            storageQueue = q1;
            storageQueue.enqueue(value);
        }
        
        return value;
    }

    /**
     * Returns a String representation of this StackFromQueue
     *
     * @return  The String representation of this StackFromQueue
     *
     */
    public String toString() {
        
        String s  = new String();

        while (storageQueue.size() > 0) {
            s+=storageQueue.peek() + " ";
            tempQueue.enqueue(storageQueue.dequeue());
        }

        Queue q1 = tempQueue;
        tempQueue = storageQueue;
        storageQueue = q1;

        return s;
    }
    
}
