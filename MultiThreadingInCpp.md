@ Multi Threading in C++ -

1. Multithreading is a technique where a program is divided into smaller units of execution called thread.
2. Each thread run independently but shares resources like memory, allowing tasks to ve performed simultaneously.
3. This helps improve performance by utilizing multiple CPU cores efficiently.

@ Importance of Multithreading -

1. Leverages Cpu cores to execute tasks in parallel, reducing overall execution time.
2. Keeps application responsive by running background operation withouot blocking the main theard.
   For example - In a word document one thread does auto formatting along with the main thread.

3. Makes it easier to handle large workloads or multiple simultaneous operations such as servers or real-time systems.

@ Common Operations on Thread -
The <thread> header in C++ provides a simple and powerfull interface for managing threads.

@ Create a Thread -
The std::thread class represent the thread. Threading a instance of this class will create a thread with given callable as its task.

thread thread_name(callable);

where,

1. thread_name is object of thread class.
2. callable is a callable object like for pointer, function object (functors).

#inlcude<bits/stdc++.h>
#include<thread>
using namespace std;

void func(){
cout << "Hello from the thread!" << endl ;
}

int main(){
thread t(func);
t.join;
cout << "Main thread fininshed." << endl;
return 0;
}

output -
Hello from the thread!
Main thread fininshed.

1. The prgram creates a new worker thread to run a function.
2. Main thread starts default when the program begin executing main().
3. The main thread and the worker thread execute concurrently.
4. The main thread calls join() to wait for the worker to finish.

@ One main thread and Multiple worker thread -

#inlcude<bits/stdc++.h>
#include<thread>
#include<chrono>
using namespace std;

void worker (int id){
cout << "Worker" << id << "started on thread" << std::this_thread::get_id() << endl;
this_thread::sleep_for(chrono::milliseconds(100\*(id+1)));

    cout<<"worker" << id << "finished in thread" << std::this_thread::get_id() << endl;

}

int main(){
const int num_worker = 4;
vector<thread> workers;

    for (int i =0; i<num_workers; ++i){
        workers.emplace_back(worker.i);
    }

    cout << "Main thread id (" << this_thread::get_if() << ") is coordinating." << endl;

    for(auto &t : workers) t.join();

    cout << "All workers finished. Main threads ends." << endl;

    return 0;

}

@ Joinig a thread -

1. Before joining a thread it is preferred to check if the thread can be joined using the joinable() method.
2. The joinable() method checks wheater the thread is in a valid state for these operations or not.

thread_name.joinable();

The joinable() method return true if the thread is joinable else return false.

- Joinig two threads C++ blocks the current thread until the thread associated with the std::thread object finished execution.

To joinig two threads in C++ we can use join() function which is called inside the body of the thread to which the specified thread is to be joined.

thread_name.join();

The thread.join function throws std::system_error if the thread is not joinable.

Note :- Joining two non-main thread is risky as it may lead to race condition or logic errors.

@Detaching a Thread -

A joined thread can be detached from the calling thread using the detach() member function of the std::thread class. When a thread is detached it runs independently in the background, and the other thread does not waits for it to finish.

thread_name.detach();

@ Getting Thread ID

In multithreading each thread has a unique Id which can be obtained by using the get_id() function.

thread_name.get_id();

The get_id() function return an object represents the thread's ID.

#include<bits/stdc++.h>
#include<thread>
#include<chrono>

using namespace std;

void task1(){
cout << "Thread 1 is running. ID: " << this_thread :: get_id() << "\n";
}

void task2(){
cout << "Thread 1 is running. ID: " << this_thread :: get_id() << "\n";
}

int main(){
thread t1(tasks1);
thread t2(tasks2);

    cout << "t1 ID: " << t1.get_id() << "\n;
    cout << "t2 ID: " << t2.get_id() << "\n;

    if(t1.joinable()){
        ti.join();
        cout << "t1 joined \n" ;
    }

    if(t2.joinable()){
        t2.detach()
        cout << "t2 detached \n";
    }

    cout << "Main thread sleeping for 1 second....\n";
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Main thread awake.\n";

    return 0;

}

Output -
t1 ID: 0x1234
t2 ID: 0x5678
Thread 1 is running. ID: 0x1234
t1 joined.
Thread 2 is running. ID: 0x5678
t2 joined.
Main thread is sleeping for 1 second....
Main thread awake.

@Callables in Multithreading

A callable (such as function, lambda or function object) is passed to a thread. The callable is execute in parallel to a the thread when it starts like, thread t(func).

Creates a thread that runs the func function. We can also pass parameters along with callable, like this thread t(func, param1, param2);

In C++, callable can be divinded into 4 categories.

1. function.
2. Lambda Expression.
3. Functionn object.
4. Non-static or Static Member function

@ Function Pointer -
A function can bbe a callable object to pass to the thread constructor for inititalizing a thread.

#include<bits/stdc++.h>
#include<thread>
using namespace std;

void func(int n){
cout << n;
}

int main(){
thread t(func, 4);
t.join();
return 0;
}

output - 4

@Lambda Expression -
Thread object can also use a lanbda expressoin as a callable which can be passes directly inside the thread object.

#include<bits/stdc++.h>
#include<thread>
using namespace std;

int main(){
int n = 3;
thread t([] (int n) {
cout << n;
});

    t.join();
    return 0;

}

output - 3

Lambda Syntax - ( [capture-clause] (parameter) -> return-type{} )

@Capture Clause -
A lambda expression can have more power than an ordinary function by more power than an ordinary function by having access to variables from the enclosing scope we can capture extrenal variables friom the enclosing scope in there ways usning capture clause.

1. [&] - Capture all external variables by reference.
2. [=] - Capture all external variables by values.
3. [a, &b] - Capture by both value and reference 'a' by value and 'b' by reference.

#include<bits/stdc++.h>
#include<thread>
using namespace std;

void print(vector<int> v){
for(auto x:v) cout << " ";
cout << encl;
}

int main(){
vector<int> v1, v2;

    auto byRef = [&] (int n) {            // by reference change will happen.
        v1.push_back(m);
        v2.push_back(m);
    }

    auto byVal = [=] (int n){             // by value changes doesn't affect the original vector.
        v1.push_back(m);
        v2.push_back(m);
    }

    auto mixed = [v1, &v2] (int n){       // only by reference changes will happen.
        v1.push_back(m);
        v2.push_back(m);
    }

    byRef(20);
    byVal(234);
    mixed(10);
    return 0;

}

output -
20
20 10

@ Sort vector using Lambda

#include <bits/stdc++.h>
#include<thread>
using namespace std;

int main(){
vector <int> v = {5, 1, 8, 3, 9, 2};

    sort (v.begin(), v.end(), [](const int &a, const int &b){
        return a < b;        //1, 2, 3, 5, 8, 9
        //return a > b;      //9, 8, 5, 3, 2, 1
    })

}

@Function Object -
Function object or Functors can also be used for a thread as callable. To make funtion callable we need to overload the operator parantheses operator();

#incude<bits/stdc++.h>
#include<threads>
using namespace std;

class SumFunctor{
public:
int n;
sumFunctor (int a) : n(a){}

            void operator()() const{
                cout << n;
            }

};

int main(){
thread t(sumFunctor(3));
t.join();
return 0;
}

output - 3

@ Non-Static and Static Member Function
We can also use thread using the non-static or static member functions of a class. For non-static member function, we need to create an object of a class but it's not necessary with static member functions.

#include <iostream>
#include <thread>
​
using namespace std;
​
class MyClass {
public:
void f1(int num) { //Non-Static
cout << num << endl;
}
​
static void f2(int num) { //Static
cout << num;
}
};
​
int main() {

    MyClass obj;

    thread t1(&MyClass::f1, &obj, 3);

    t1.join();

    thread t2(&MyClass::f2, 7);

    t2.join();
    return 0;

}

Output -
3
7

@ Thread Management
In C++ thread library, various functions are defined to manage threads that can be reused to perform multiple tasks. Some of the are listed below:

Classes/Methods Description

1. join() - It ensures that the calling thread waits for the specified thread to complete its execution.
2. detach() - Allows the thread to run independently of the main thread, meaning the main thread does not need to wait.
3. mutex - A mutex is used to protect shared data between threads to prevent data races and ensure synchronization.

4. lock_guard - A wrapper for mutexes that automatically locks and unlocks the mutex in a scoped block.
5. condition_variable - Used to synchronize threads, allowing one thread to wait for a condition before proceeding.
6. atomic - Manages shared variables between threads in a thread-safe manner without using locks.

7. sleep_for() - Pauses the execution of the current thread for a specified duration.
8. sleep_until() - Pauses the execution of the current thread until a specified time point is reached.
9. hardware_concurrency() - Returns the number of hardware threads available for use, allowing you to optimize the use of system resources.

10. get_id - Retrieves the unique ID of the current thread, useful for logging or debugging purposes.

@ Problems with Multithreading
Multithreading improves the performance and utilization of CPU, but it also introduces various problems:

1. Deadlock
2. Race Condition
3. Starvation

@ Deadlock
A deadlock occurs when two or more threads are blocked forever because they are each waiting for shared resources that the other threads hold. This creates a cycle of waiting, and none of the threads can proceed.

@ Race Condition
A race condition occurs when two or more threads access shared resources at the same time, and at least one of them modifies the resource. Since the threads are competing to read and write the data, the final result depends on the order in which the threads execute, leading to unpredictable or incorrect results.

@ Starvation
Starvation occurs when a thread is continuously unable to access shared resources because other threads keep getting priority, preventing it from executing and making progress.

@ Thread Synchronization
In multithreading, synchronization is the way to control the access of multiple threads to shared resources, ensuring that only one thread can access a resource at a time to prevent data corruption or inconsistency. This is typically done using tools like mutexes, locks, and condition variables.
