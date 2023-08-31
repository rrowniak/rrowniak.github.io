/**
 * Created by rr on 11.01.17.
 */
public class Timer {
    private long start;

    public Timer() {
        this.start = 0;
    }

    public void Start(String msg) {
        System.out.println(msg);
        this.start = System.currentTimeMillis();
    }

    public void Report() {
        long diff = System.currentTimeMillis() - start;
        System.out.println("Time elapsed: " + Long.toString(diff) + " ms");
    }
}
