class List{
	Node first, last, cursor;
	int length;
	//Constructor
	List() //creates a new empty list
	{
		first = null;
		last = null;
		cursor = null;
		length = 0;
	}

	// Access functions 
	int length() // Returns the number of elements in this List.
	{
		return length;
	}
	int index() // If cursor is defined, returns the index of the cursor element, otherwise return -1
	{
		if(cursor == null)
			return -1;
		if(first == null)
			return -1;
		Node temp = first;
		for(int i = 0; i < length(); i ++)
		{
			if(temp == cursor)
				return i;
			temp = temp.next;
		}
		return -1;
	}
	int front() // Returns front element. Pre: length()>0
	{
		return first.data;
	}
	int back() // Returns back element. Pre: length()>0
	{
		return last.data;
	}
	int get() // Returns cursor element. Pre: length()>0, index()>=0
	{
		return cursor.data;
	}
	boolean equals(List L) // Returns true if and only if this List and L are the same integer sequence. The states of the cursors in the two Lists are not used in determining equality
	{
		if(this == null && L == null)
			return true;
		else if((this == null && L != null) || (this != null && L == null))
			return false;
		else if(length() != L.length())
			return false;
		else
		{
			cursor = first;
			L.cursor = L.first;
			for(int i = 0; i < length(); i ++)
			{
				if(get() != L.get())
					return false;
				moveNext();
				L.moveNext();
			}
		}
		return true;
	}

	//Manipulation procedures
	void clear() // Resets this List to its original empty state.
	{
		first = null;
		length = 0;
	}
	void moveFront() // If List is non-empty, places the cursor under the front element, otherwise does nothing
	{
		if(length != 0)
			cursor = first;
	}
	void moveBack() // If List is non-empty, places the cursor under the back element, otherwise does nothing
	{
		if(length != 0)
			cursor = last;
	}
	void movePrev() // If cursor is defined and not at front, moves cursor one step toward front of this List, if cursor is defined and at front, cursor becomes undefined, if cursor is undefined does nothing.
	{
		if(cursor == null)
			return;
		else if(cursor == first)
			cursor = null;
		else
			cursor = cursor.prev;

	}
	void moveNext() // If cursor is defined and not at back, moves cursor one step toward back of this List, if cursor is defined and at back, cursor becomes undefined, if cursor is undefined does nothing.
	{
		if(cursor == null)
			return;
		else if(cursor == last)
			cursor = null;
		else
			cursor = cursor.next;
	}
	void prepend(int data) // Insert new element into this List. If List is non-empty, insertion takes place before front element.
	{
		if(first == null)
			first = new Node(data);
		else
		{
			Node temp = first;
			first = new Node(data);
			temp.prev = first;
			first.next = temp;
			if(last == null)
				last = first.next;
		}
		length ++;
	}
	void append(int data) // Insert new element into this List. If List is non-empty, insertion takes place after back element.
	{
		if(first == null)
			first = new Node(data);
		else if(last == null)
		{
			last = new Node(data);
			first.next = last;
			last.prev = first;
		}
		else
		{
			Node temp = last; 
			last = new Node(data);
			temp.next = last;
			last.prev = temp;
		}
		length ++;
	}
	void insertBefore(int data) // Insert new element before cursor. Pre: length()>0, index()>=0
	{
		if(cursor == first)
		{
			prepend(data);
			return;
		}
		Node curr = new Node(data);
		cursor.prev.next = curr;
		curr.prev = cursor.prev;
		curr.next = cursor;
		cursor.prev = curr;
		length ++;
	}
	void insertAfter(int data) // Inserts new element after cursor. Pre: length()>0, index()>=0
	{
		if(length == 1)
		{
			append(data);
			return;
		}
		if(cursor == last)
		{
			append(data);
			return;
		}
		Node curr = new Node(data);
		cursor.next.prev = curr;
		curr.next = cursor.next;
		curr.prev = cursor;
		cursor.next = curr;
		length ++;
	}
	void deleteFront() // Deletes the front element. Pre: length()>0
	{
		if(length() == 1)
		{
			first = null;
			length--;
			return;
		}
		first = first.next;
		first.prev = null;
		length --;
	}
	void deleteBack() // Deletes the back element. Pre: length()>0
	{
		if(length() == 1)
			first = null;
		else
		{
			last = last.prev;
			last.next = null;
		}
		length --;
	}
	void delete() // Deletes cursor element, making cursor undefined. Pre: length()>0, index()>=0
	{
		if(cursor == first)
		{
			first = first.next;
			first.prev = null;
			cursor = null;
		}
		else if(cursor == last)
		{
			last = last.prev;
			last.next = null;
			cursor = null;
		}
		else
		{
			if (cursor.next != null) 
			{ 
            			cursor.next.prev = cursor.prev; 
        		} 
        		if (cursor.prev != null) 
        		{ 
            			cursor.prev.next = cursor.next; 
        		}
        		cursor = null;
		}
		length--;
	}
	public String toString() // Overrides Object's toString method. Returns a String representation of this List consisting of a space separated sequence of integers, with front on left.
	{
		String list = "";
		//moveFront();
		for(moveFront(); index() >= 0; moveNext())
		{
			list += get() + " ";
			//moveNext();
		}
		return list;
	}
	List copy() // Returns a new List representing the same integer sequence as this List. The cursor in the new list is undefined, regardless of the state of the cursor in this List. This List is unchanged.
	{
		//if(first == null || length() == 0)
		//	return null;
		List l = new List();
		if(first == null || length() == 0)
			return l;
		//l.length = length();
		Node temp = first;
		
		for(int i = 0; i < length(); i ++)
		{
			l.append(temp.data);
			temp = temp.next;
		}
		return l;
	}

	private class Node //Node class, List is made up of nodes
	{
		int data;
		Node prev, next;
		//Constructor
		Node(int n)
		{
			data = n;
			prev = null;
			next = null;
		}

	}
}
