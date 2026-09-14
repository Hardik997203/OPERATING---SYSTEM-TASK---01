package JavaTask;

public class ProducerConsumer {

int n;
boolean status = false;

//
synchronized public void produce_item(int n ) {
	if(status) {
		try {
			wait();
		}
		catch(InterruptedException e ) {
			e.printStackTrace();
		}
		
	}
	this.n = n;
	System.out.println("Produced:"+this.n);
	status = true;
	notify();
}
	//consume
	synchronized public int consume_item() {
		if(!status) {
			try {
				wait();
			}
			catch(InterruptedException e ) {
				e.printStackTrace();
			}
		}
		
	System.out.println("Consumed:"+ this.n);
	status = false;
	notify();
	return this.n;
	}
}
	
package JavaTask;

public class Producer extends Thread {
	ProducerConsumer c;
	Producer(ProducerConsumer c){
		this.c = c;
		}
//run imp
	public void run(){
		int i = 1;
		while (true) {
			this.c.produce_item(i);
			try {
				Thread.sleep(1000);
				i++;
				
			}catch(InterruptedException e ) {
				e.printStackTrace();
			}
			
		 }
	 }
	
  }
		package JavaTask;

public class Consumer extends Thread {
	ProducerConsumer c;
	Consumer(ProducerConsumer c){
		this.c =c;
	}
	//run imp
	public void run() {
		while(true) {
			this.c.consume_item();
			try {
				Thread.sleep(1000);
			}
			catch(InterruptedException e ) {
				e.printStackTrace();
			}
		}
	
    }

}
package JavaTask;

public class MianImp {

	public static void main (String arg[]) {
		ProducerConsumer c = new ProducerConsumer();
		Producer pro = new Producer(c);
		Consumer con = new Consumer(c);
		
		
		pro.start();
		con.start();

	}

}


	
