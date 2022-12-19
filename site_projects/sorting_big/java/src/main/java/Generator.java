/**
 * Created by rr on 11.01.17.
 */
public class Generator {
    private final long a = 48271;
    private final long c = 0;
    private final long m = 2147483647;

    private long prev = 1;

    public long gen() {
        this.prev = (this.prev * this.a + this.c) % this.m;
        return this.prev;
    }
}
