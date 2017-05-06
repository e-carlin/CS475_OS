import java.util.concurrent.Semaphore;
import java.util.concurrent.ThreadLocalRandom;

public class Bartender extends Thread {

        Semaphore customerHere;
        Semaphore roomToEnter;
        Semaphore orderPlaced;
        Semaphore orderReady;
        Semaphore padiForDrink;
        Semaphore paymentReceived;
        Semaphore customerGone;

        public Bartender(Semaphore customerHere, Semaphore roomToEnter, Semaphore orderPlaced, Semaphore orderReady, Semaphore paidForDrink, Semaphore paymentReceived, Semaphore customerGone){
            this.customerHere = customerHere;
            this.roomToEnter = roomToEnter;
            this.orderPlaced = orderPlaced;
            this.orderReady = orderReady;
            this.padiForDrink = paidForDrink;
            this.paymentReceived = paymentReceived;
            this.customerGone = customerGone;
        }
    public void run() {
        while (true) {
            try {
                waitForCustomer();
                mixDrink();
                atCashRegister();
                paymentAccepted();
            }
            catch( InterruptedException e){
                System.out.println("Bartender interrupted: "+e);
                System.exit(1);
            }
        }
    }

    private void waitForCustomer() throws InterruptedException {

        System.out.println("\t\t\t\t\t\t\t\t\t\t\t\t\t| src.Bartender");

        this.customerHere.acquire();
    }

    private void mixDrink() throws InterruptedException {

            this.roomToEnter.release();

            this.orderPlaced.acquire();

            System.out.println("\t\t\t\t\t\t\t\t\t\t\t\t\t| \t\tsrc.Bartender");

            //Sleep for time to mix drink
            Thread.sleep(ThreadLocalRandom.current().nextInt(5, 1000 + 1));

            //Order is ready
            this.orderReady.release();
    }

    private void atCashRegister() throws InterruptedException {

            System.out.println("\t\t\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\tsrc.Bartender");

            //Wait for customer to pay
            padiForDrink.acquire();
    }

    private void paymentAccepted() throws InterruptedException {

            System.out.println("\t\t\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\t\t\tsrc.Bartender");

            paymentReceived.release();

            customerGone.acquire();
    }
}