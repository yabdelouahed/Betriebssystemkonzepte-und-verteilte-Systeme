#include <mutex>
#include <iostream>
#include "Semaphore.h"
#include <string>
#include <thread>
using namespace std;
mutex mtx;


void alphabet(semaphore &s)
{
	char buchstabe = 'a';
	s.wait();
	mtx.lock();
	for (int i = 0; i < 26; i++, buchstabe++)
	{

		cout << buchstabe;

	}
	s.notify();
	mtx.unlock();
}

void zahlen(semaphore &s)
{
	mtx.lock();
	s.wait();
	for (int i = 0; i <= 32; i++)
	{

		std::cout << i;

	}
	s.notify();
	mtx.unlock();
}

void alphabetG(semaphore &s)
{
	mtx.lock();
	s.wait();
	char buchstabe = 'A';
	for (int i = 0; i < 26; i++, buchstabe++)
	{
		std::cout << buchstabe;
	}
	s.notify();
	mtx.unlock();
}

int main()
{
	semaphore s(2);					// how many threads are allowed the access the available ressource
	thread first(alphabet, ref(s));	//Start  the Thread  => the value of the semaphore is decremented by 1
									// The Main thread waits until the first thread is finished by calling the fkt join()

	thread seconds(zahlen, ref(s));	// Start the 2 Thread =>  the value of the Semaphore is decremented by 1
	thread third(alphabetG, ref(s)); // Starts the third Thread 

	first.join();					// Reihenfolge
	seconds.join();
	third.join();
	
	cout << endl;
	system("pause");



	return 0;
}







/*The main thread creates and starts the t1 and t2 threads.The two threads start running in parallel.
The main thread calls t1.join() to wait for the t1 thread to finish.
The t1 thread completes and the t1.join() method returns in the main thread.Note that t1 could already have finished before the join() call is made in which case the join() call will return immediately.
The main thread calls t2.join() to wait for the t2 thread to finish.*/