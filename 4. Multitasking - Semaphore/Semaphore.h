#pragma once
#include <mutex>
#include <condition_variable>
using namespace std;
class semaphore
{
	mutex mtx;
	condition_variable cv;
	int count;

public:

		semaphore(int count_ = 1) : count{ count_ }
		{}
		// unlockt die Mutex
		void notify()
		{
			unique_lock<mutex> lck(mtx);
			++count;
			cv.notify_one();
		}
		// Wait ; Lockt die Mutex
		void wait()
		{
			unique_lock<mutex> lck(mtx);
			while (count == 0)
			{
				cv.wait(lck);
			}

			--count;
		}
}; 
