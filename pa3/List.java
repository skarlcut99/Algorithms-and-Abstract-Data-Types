public class List {

    private class Node {

        Object data;
        Node next;
        Node prev;

        Node(Object data) {
            this.data = data;
            next = null;
            prev = null;
        }

        Node(Object data, Node nextNode, Node prevNode) {
            this.data = data;
            next = nextNode;
            prev = prevNode;
        }

        public String toString() {
            return String.valueOf(data);
        }

    }

    private Node front;
    private Node back;
    private Node cursor;
    private int index;
    private int length;

    List() {
        length = 0;
        front = null;
        cursor = null;
        back = null;
        index = -1;

    }

    int length() {
        return length;
    }

    int index() {
        return index;
    }
    Object front() {
        if (length > 0) {
            return front.data;
        }
        return -1;
    }

    Object back() {
        if (length > 0) {
            return back.data;
        }
        return -1;
    }

    Object get() {
        if (length() == 0) {
            return null;
        } else if (index == -1) {
            return null;
        } else {
            return cursor.data;
        }
    }

    void clear() {
        cursor = front;
        if (cursor != null) {
            while (cursor.next != null) {
                Node temp = cursor;
                cursor = cursor.next;
                temp.next = null;
                temp.prev = null;
            }
            cursor = null;
            front = null;
            back = null;
            length = 0;
            index = -1;
        }

    }

    void moveFront() {
        if (length > 0) {
            cursor = front;
            index = 0;
        }
    }

    void moveBack() {
        if (length > 0) {
            cursor = back;
            index = length - 1;
        }
    }

    void movePrev() {
        if (cursor != null && !cursor.equals(front)) {
            cursor = cursor.prev;
            index--;
        } else if (cursor != null && cursor.equals(front)) {
            cursor = null;
            index = -1;
        } else
            return;

    }

    void moveNext() {

        if (cursor != null && !cursor.equals(back)) {
            cursor = cursor.next;
            index++;
        } else if (cursor != null && cursor.equals(back)) {
            cursor = null;
            index = -1;
        } else
            return;
    }

    void prepend(Object data) {
        if (length > 0) {
            Node newFront = new Node(data, front, null);
            front.prev = newFront;
            front = newFront;
            length++;
            index++;
        } else {
            Node newFront = new Node(data);
            front = newFront;
            back = newFront;
            length++;
            index++;
        }
    }

    void append(Object data) {
        if (length > 0) {
            Node newFront = new Node(data, null, back);
            back.next = newFront;
            back = newFront;
            length++;
        } else {
            Node newFront = new Node(data);
            front = newFront;
            back = newFront;
            length++;
        }
    }

    void insertBefore(Object data) {
        if (length() <= 0) {
            return;
        } else if (index() < 0) {
            return;
        }
        Node newNode = new Node(data);
        if (index() == 0) {
            prepend(data);
        } else {
            newNode.next = cursor;
            newNode.prev = cursor.prev;
            cursor.prev.next = newNode;
            cursor.prev = newNode;
            index++;
            length++;
        }
    }

    void insertAfter(Object data) {
        if (length() <= 0) {
            return;
        } else if (index() < 0) {
            return;
        }
        Node newNode = new Node(data);
        if (index() == length() - 1) {
            append(data);
        } else {
            newNode.prev = cursor;
            newNode.next = cursor.next;
            cursor.next.prev = newNode;
            cursor.next = newNode;
            length++;
        }

    }

    void advanceTo(int i) {
        if (i == index) return;
        if (i >= length() || i < 0) {
            cursor = null;
            index = -1;
            return;
        }
        if (i == 0)
        {
            cursor = front;
        }
        if (i == length() - 1)
        {
            cursor = back;
        }
        else {
            int splitter = 0;
            int first = length() - i;
            int second = i;
            int third = Math.abs(index - i);
            int min = first;
            if (min > second)
            {
                min = second;
            }
            if (min > third)
            {
                min = third;
            }
            if (min == first) {
                cursor = back;
                index = length() - 1;
                splitter = 0;
            } else if (min == second) {
                cursor = front;
                index = 0;
                splitter = 1;
            } else if (min == third) {
                if (i > index) splitter = 1;
            }
            for (int j = 0; j < i; j++) {
                if (splitter == 1) moveNext();
                else movePrev();
            }
        }
        index = i;
    }

    void deleteFront() {
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

    void deleteBack() {
        if(length() == 1)
                        first = null;
                else
                {
                        last = last.prev;
                        last.next = null;
                }
                length --;
    }

    void delete() {
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

    public boolean equals(Object x) {
        List L;
        if (x instanceof List) {
            L = (List) x;
            if (this.length == L.length) {
                Node firstList = this.front;
                Node secondList = L.front;
                while (firstList != null && secondList != null) {
                    if (firstList.data.equals(secondList.data)) {
                        firstList = firstList.next;
                        secondList = secondList.next;
                    } else return false;
                }
                return true;
            } else {
                return false;
            }
        } else return false;
    }

    public String toString() {
        String str = "";
        for (Node N = front; N != null; N = N.next) {
            str += N.toString() + " ";
        }
        return str;
    }
}
