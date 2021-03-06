# ReadWriteLock

In computer systems, it is common to have some processes (called readers) that read data and others (called writers) that write it. For example, in a bank there may be many more readers than writers – many inquiries will be made against a database of bank accounts before the customer withdraws or deposits some money.

Because readers do not change the balance of the account, many readers may access the account at once. But a writer can modify the account balance, so it must have exclusive access. When a writer is active, no other readers or writers may be active. This exclusion needs only to be enforced at the record level. It is not necessary to grant a writer exclusive access to the entire database.
