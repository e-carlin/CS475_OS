import java.util.concurrent.Semaphore;

public class TheBar {
    public static void main(String[] args) {
        if (args.length != 1) {
            printUsage();
        }

        int num = 0;
        try {
            num = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            printUsage();
        }

        System.out.println("src.Customer:\t\t\t\t\t\t\t\t\t\t\t| Employee:");
        System.out.print("Traveling\tArrived\t\tOrdering\tBrowsing\tAt Register\tLeaving");
        System.out.println("\t\t| Waiting\tMixing Drinks\t\tAt Register\tPayment Accepted");
        System.out.println("---------------------------------------------------"
                + "---------------------------------------------+--------"
                + "-------------------------------------------------------------------");


        //Declare semaphores
        Semaphore customerHere = new Semaphore(0);
        Semaphore roomToEnter = new Semaphore(0);
        Semaphore orderPlaced = new Semaphore(0);
        Semaphore orderReady = new Semaphore(0);
        Semaphore paidForDrink = new Semaphore(0);
        Semaphore paymentReceived = new Semaphore(0);
        Semaphore customerGone = new Semaphore(0);


        Thread emp = new Bartender(customerHere,
                roomToEnter,
                orderPlaced,
                orderReady,
                paidForDrink,
                paymentReceived,
                customerGone);

        emp.start();

        Thread[] custs = new Thread[num];
        for (int i = 0; i < num; i++) {

            custs[i] = new Customer(i,
                    customerHere,
                    roomToEnter,
                    orderPlaced,
                    orderReady,
                    paidForDrink,
                    paymentReceived,
                    customerGone);

            custs[i].start();
        }
        for (int i = 0; i < num; i++) {

            try {
                custs[i].join();
            } catch (InterruptedException e) {
            }
        }

        System.exit(0);
    }

    private static void printUsage() {
        System.out.println("Usage: java src.TheBar <num>");
        System.out.println("  <num>: Number of customers.");
        System.exit(-1);
    }

}


