/* Stack.java
 *
 * "I pledge my honor that I have abided by the Stevens Honor System.
 *
 * Keyur Ved (c) 2014
 *
 */
package week7;

/**
 * Emulates a Stack data type.
 *
 * @author Keyur Ved
 * @version 1.0
 * @since 20141010
 *
 */
public class Stack {
    /**
     * This implementation of a Stack uses an array
     *
     */
    private int[] array;
    private int top;
    
    public Stack(){
        this(50);
    }

    public Stack(int i){
        array = new int[i];
        top = -1;
    }

    /**
     * Returns the current size of the Stack
     *
     * @return  The size of the Stack
     */
    public int size(){
        return (top+1);
    }
    
    /** 
     * Adds a value to the top of the Stack
     *
     * @param   i   The value to add to the Stack
     *
     */
    public void push(int i){
        
        top++;
        if (this.full()) {
            System.out.println("Error: Stack size exceeded");
            top=array.length-1;
        }   
        else {
            array[top]=i;
        }
    }
    
    /**
     * Removes the top value from the Stack
     *
     * @return  The value at the top of the Stack
     *
     */
    public int pop(){
        int value = 0;

        if (this.empty()) {
            System.out.println("Error: Stack is empty");
        }
        else {
            value = array[top];
            top--;
        }
        
        return value;
    }

    /**
     * Returns the top value in the Stack
     *
     * @return  The top value in the Stack
     *
     */
    public int peek(){
        int value = -1;
        
        if (this.empty()){
            System.out.println("Error: Stack is empty printing a -1");
        }
        else {
            value = array[top];
        }

        return value;
    }

    /**
     * Checks if the Stack is empty
     *
     * @return  True if the Stack is empty, false if it is not
     *
     */
    public boolean empty(){

        if (top == 0){
            return true;
        }
        
        return false;
    }

    /**
     * Checks if the Stack is full
     *
     * @return  True if the Stack is full, false if it is not
     *
     */
    public boolean full(){
        
        if (top >= array.length){
            return true;
        }

        return false;
    }
    
    /**
     * Creates a String representation of the Stack
     *
     * @return  A String representation of the Stack
     */

    public String toString(){
        String s = new String();

        for (int i = 0; i<=top; i++){
            s+=array[i] + " ";
        }

        return s;
    }

}
