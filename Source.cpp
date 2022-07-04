#include<iostream>
using namespace std;

template <typename T>
class Queue {
private:
    T* qptr;
    int front;
    int rear;
    int n, cap;

    //next index in circular l
    inline int numOccupied() {
        return n + 1;
    }
    inline int next(int i) {
        return (i + 1) % cap;
    }

    void init() {
        front = rear = 0;
        n = 0;
        cap = 1;
        qptr = new T[1];//dummy slot
    }


public:
    Queue() {
        init();
    }

    inline bool empty() {
        return front == rear;
    }

    inline int size() {
        return n;
    }

    T peek() {
        return qptr[next(front)];
    }


    void enque(const T& obj) {
        if (empty()) {
            delete qptr;
            qptr = new T[2];
            qptr[1] = obj;
            front = 0;
            rear = 1;
            n = 1;
            cap = 2;
        }
        else if (numOccupied() == cap) {//no more space
            T* temp = new T[cap * 2];
            //copy the data into the new array
            int i, j;
            for (j = 1, i = next(front); i != rear; i = next(i)) {
                temp[j++] = qptr[i];
            }temp[j] = qptr[i];//copying the real element

            //add the new element
            temp[++j] = obj;
            //set the new front and rear values
            front = 0;//dummy at 0
            rear = j;
            //make qptr point to the new space
            delete[] qptr;
            qptr = temp;
            //adjust sizes
            cap *= 2;
            n++;
        }
        else {//there is space in the queue
            rear = next(rear);
            qptr[rear] = obj;
            n++;
        }
    }

    void deque() {
        if (empty()) return;//includes the case where cap==1
        else {
            //first deque the element
            front = next(front);
            n--;
            if (empty()) {
                delete[] qptr;
                init();
            }
            //if the number of occupied cells has fallen below cap/2,
              //halve the array.ss
            else if (numOccupied() < cap / 2) {//if less than half storage is used
                T* temp = new T[cap / 2];
                int i, j;
                for (j = 1, i = next(front); i != rear; i = next(i)) {
                    temp[j++] = qptr[i];
                }temp[j] = qptr[i];//copy the rear elements
                front = 0;
                rear = j;
                delete[] qptr;
                qptr = temp;
                cap /= 2;
            }
        }
    }

    void display()
    {
        int i = next(front);
        while (i != rear)
        {
            cout << qptr[i] << " ";
            i = next(i);
        }
        cout << qptr[i];
        cout << endl;
    }

    ~Queue() {
        delete[] qptr;
    }
};

int main()
{
    Queue<int> q;
    for (int i = 0; i < 20; i++)
        q.enque(rand()%50);
    q.display();
    Queue<int> q1;
    Queue<int> q2;
    while (!q.empty())
    {
        int temp = q.peek();
        q.deque();
        if (!q1.empty())
        {
            while (!q1.empty() && q1.peek() < temp)
            {
                q2.enque(q1.peek());
                q1.deque();
            }
            q2.enque(temp);
            while (!q1.empty())
            {
                q2.enque(q1.peek());
                q1.deque();
            }
            while (!q2.empty())
            {
                q1.enque(q2.peek());
                q2.deque();
            }
        }
        else
        {
            q1.enque(temp);
        }
    }
    while (!q1.empty())
    {
        q.enque(q1.peek());
        q1.deque();
    }
    q.display();
}