1.ProducerConsumer using threads in java
pproach: The program implements the Producer-Consumer problem using two threads that share a common ProducerConsumer object. The Producer thread generates numbers starting from 1 and calls produce_item() to store each number in the shared buffer, while the Consumer thread calls consume_item() to read the produced number. In the ProducerConsumer class, the synchronized keyword ensures that only one thread accesses the shared methods at a time. The status variable is used to check whether the buffer contains an item or is empty. If the buffer already contains an item, the producer waits using wait(), and if the buffer is empty, the consumer waits. After producing or consuming an item, notify() wakes up the waiting thread. Thus, the program allows the Producer and Consumer to communicate safely while sharing the same buffer.

Logic:PRODUCER ↓ Creates item ↓ ProducerConsumer BUFFER ↓ Stores item temporarily ↓ CONSUMER ↓ Consumes item

Basic Rules: Buffer contains item → Producer waits Buffer is empty → Consumer waits Producer adds item → Consumer can proceed Consumer removes item → Producer can proceed notify() → Wakes up the waiting thread
