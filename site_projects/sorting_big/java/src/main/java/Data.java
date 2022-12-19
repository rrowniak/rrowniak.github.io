import java.math.BigInteger;

/**
 * Created by rr on 11.01.17.
 */
public class Data implements Comparable<Data> {
    long id;
    long value;

    public Data(long i, long v) {
        this.id = i;
        this.value = v;
    }

    public int compareTo(Data d) {
        if (this.value < d.value) {
            return -1;
        } else if (this.value > d.value) {
            return 1;
        }

        return 0;
    }
}
