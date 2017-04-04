public class Bartender extends Thread {

    public void run() {
        while (true) {
            waitForCustomer();
            mixDrink();
            atCashRegister();
            paymentAccepted();
        }
    }

    private void waitForCustomer() {
        System.out.println("\t\t\t\t\t\t\t\t\t\t\t\t| src.Bartender");
    }

    private void mixDrink() {
        System.out.println("\t\t\t\t\t\t\t\t\t\t\t\t| \t\tsrc.Bartender");
    }

    private void atCashRegister() {
        System.out.println("\t\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\tsrc.Bartender");
    }

    private void paymentAccepted() {
        System.out.println("\t\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\t\t\tsrc.Bartender");
    }
}