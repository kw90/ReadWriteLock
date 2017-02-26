#include "BankAccount.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main() {
	const int nThreads = 10;
	const int nRuns = 10;

	mutex mtx;							// synchronized access to standard output cout
	BankAccount account;				// synchronized bank account
	double unsynchronizedAccount = 0;	// unsychronized bank account
	thread t[nThreads];					// thread pool

	// parallel task
	auto task = [nRuns,&account,&mtx,&unsynchronizedAccount] {
		srand((unsigned int)hash<thread::id>()(this_thread::get_id()));	// ensures that all threads have a different seed for the random number generator

		for (int i = 0; i < nRuns; i++) {
			if (i & 1) {
				const double amount = rand()*1000/RAND_MAX;
				const double b = unsynchronizedAccount + amount;
				account.deposit(amount);
				unsynchronizedAccount = b;
				mtx.lock();
				cout << "thread " << this_thread::get_id() << " deposits " << amount << endl;
				mtx.unlock();
			}
			const double balance = account.getBalance();
			mtx.lock();
			cout << "thread " << this_thread::get_id() << ": balance is = " << balance << ", unsychronized balance is = " << unsynchronizedAccount << endl;
			cout << "concurrent readers: " << account.getReaders() << endl;
			mtx.unlock();
		}
	};

	cout << "main thread id = " << this_thread::get_id() << ", hw concurrency = " << thread::hardware_concurrency() <<endl;

	// start threads
	for (int i = 0; i < nThreads; i++) {
		t[i] = thread(task);	// thread uses move-semantics: t[i] will run the task and the temporary thread will immediately finish
	}

	// join threads: main thread waits for parallel threads
	for (int i = 0; i < nThreads; i++) {
		cout << "wait until thread " << t[i].get_id() << " has finished" << endl;
		t[i].join();
	}
	system("pause");
}