public class TicketMaker {
    private static TicketMaker instance = new TicketMaker();
    private int ticket = 1000;

    private TicketMaker() {
    }

    public int getNextTicketNumber() {
        return ticket++;
    }

    public static TicketMaker getInstance() {
        return instance;
    }

    public static void main(String[] args) {
        TicketMaker maker1 = TicketMaker.getInstance();
        TicketMaker maker2 = TicketMaker.getInstance();
        System.out.println(maker1.getNextTicketNumber());
        System.out.println(maker1.getNextTicketNumber());
        System.out.println(maker2.getNextTicketNumber());
        System.out.println(maker2.getNextTicketNumber());
    }
}