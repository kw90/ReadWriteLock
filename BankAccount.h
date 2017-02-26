#pragma once

#include "RWLock.h"
#include <chrono>

class BankAccount {
	mutable RWLock m_lock;	// mutable: can be modified even in const methods
	double m_balance = 0;	// bank account balance

public:
	void deposit(double amount) {
		m_lock.lockW();
		m_balance += amount;
		this_thread::sleep_for(chrono::milliseconds(900));
		m_lock.unlockW();
	}

	double getBalance() const {
		m_lock.lockR();
		this_thread::sleep_for(chrono::milliseconds(500));
		m_lock.unlockR();
		return m_balance;
	}

	size_t getReaders() const {
		return m_lock.getReaders();
	}
};