import java.util.concurrent.Semaphore;
import java.util.concurrent.ThreadLocalRandom;

public class Customer extends Thread {

    private int id;
    Semaphore customerHere;
    Semaphore roomToEnter;
    Semaphore orderPlaced;
    Semaphore orderReady;
    Semaphore padiForDrink;
    Semaphore paymentReceived;
    Semaphore customerGone;

    public Customer(int id, Semaphore customerHere, Semaphore roomToEnter, Semaphore orderPlaced, Semaphore orderReady, Semaphore padiForDrink, Semaphore paymentReceived, Semaphore customerGone) {

        this.id = id;
        this.customerHere = customerHere;
        this.roomToEnter = roomToEnter;
        this.orderPlaced = orderPlaced;
        this.orderReady = orderReady;
        this.padiForDrink = padiForDrink;
        this.paymentReceived = paymentReceived;
        this.customerGone = customerGone;
    }

    public void run() {
        try {
            travelToBar();
            arriveAtBar();
            placeOrder();
            browseArt();
            atRegister();
            leaveBar();
        }
        catch( InterruptedException e){
            System.out.printf("Customer interrrupted: "+e);
            System.exit(1);
        }
    }

    private void travelToBar() throws InterruptedException {

        System.out.println("src.Customer " + id + "\t\t\t\t\t\t\t\t\t\t\t|");

        //Wait a random travel time
        Thread.sleep(ThreadLocalRandom.current().nextInt(20, 5000 + 1));

        //Let the bartender know someone is here
        customerHere.release();
    }

    private void arriveAtBar() throws InterruptedException{

        //Wait for room to enter the bar
        roomToEnter.acquire();

        //Enter the bar
        System.out.println("\t\tsrc.Customer " + id + "\t\t\t\t\t\t\t\t\t|");
    }

    private void placeOrder() {

        System.out.println("\t\t\t\tsrc.Customer " + id + "\t\t\t\t\t\t\t|");
        orderPlaced.release();
    }

    private void browseArt() throws InterruptedException {
        System.out.println("\t\t\t\t\t\tsrc.Customer " + id + "\t\t\t\t\t|");

        Thread.sleep(ThreadLocalRandom.current().nextInt(3, 4000 + 1));

    }

    private void atRegister() throws InterruptedException{

        //Wait at the register for the bartender to finish mixing the drink
        System.out.println("\t\t\t\t\t\t\t\tsrc.Customer " + id + "\t\t\t|");
        orderReady.acquire();

        padiForDrink.release();
    }

    private void leaveBar() throws InterruptedException {

        //Wait for bartender to receive payment
        this.paymentReceived.acquire();
        System.out.println("\t\t\t\t\t\t\t\t\t\tsrc.Customer " + id + "\t|");
        this.customerGone.release();
    }
}
