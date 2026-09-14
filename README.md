# OPERATING---SYSTEM-TASK---01
# Producer-Consumer Problem Using Threads in Java

## Aim

Implement the **Producer-Consumer problem using threads in Java**.

## Approach

This program uses two threads, **Producer** and **Consumer**, which share a common `ProducerConsumer` object.

The **Producer** generates numbers starting from `1` and sends them to the shared object using the `produce_item()` method. The **Consumer** receives the values using the `consume_item()` method.

The `status` variable is used to keep track of whether the shared buffer currently contains a value.

* `synchronized` ensures that only one thread can access the methods at a time.
* If the buffer already contains a value, the Producer waits using `wait()`.
* If the buffer is empty, the Consumer waits.
* After producing or consuming a value, `notify()` wakes the waiting thread.
* `Thread.sleep()` is used to create a small delay between operations.

This allows the Producer and Consumer to work together without consuming a value before it has been produced.

## Logic

```text
        PRODUCER
           ↓
      Creates value
           ↓
   Shared Buffer/Object
           ↓
       CONSUMER
           ↓
     Consumes value
```

## Basic Rules

```text
Buffer contains data → Producer waits
Buffer is empty      → Consumer waits

Producer produces    → Consumer can consume
Consumer consumes    → Producer can produce again
```

## Classes Used

### `ProducerConsumer`

Acts as the shared buffer. It contains:

* `produce_item()` → produces and stores a value.
* `consume_item()` → consumes the stored value.
* `status` → keeps track of whether a value is available.

### `Producer`

Extends `Thread` and continuously produces values starting from `1`.

### `Consumer`

Extends `Thread` and continuously consumes values from the shared object.

### `MianImp`

Contains the `main()` method. It creates the shared object, Producer thread, and Consumer thread, and starts both threads.

## Example Output

```text
Produced:1
Consumed:1
Produced:2
Consumed:2
Produced:3
Consumed:3
Produced:4
Consumed:4
Produced:5
Consumed:5
...
```

The program continues running because both Producer and Consumer use an infinite `while(true)` loop.
