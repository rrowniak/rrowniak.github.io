import java.util.ArrayList;
import java.util.Collections;

/**
 * Created by rr on 11.01.17.
 * Modified by rr on 01.11.22.
 */
public class Main {
    private static int RecordsNum = 100000000;

    public static void main(String[] args) {

        if (args.length > 1) {
            RecordsNum = Integer.parseInt(args[1]);
        }
        Timer t = new Timer();

        t.Start("Building " + Integer.toString(RecordsNum) + " records...");
        ArrayList<Data> d = new ArrayList<Data>(RecordsNum);
        buildDataSet(d);
        t.Report();

        t.Start("Sorting " + Integer.toString(RecordsNum) + " records...");
        sort(d);
        t.Report();

        t.Start("Checking whether the collection is sorted...");
        check(d);
        t.Report();
    }

    private static void buildDataSet(ArrayList<Data> d) {
        Generator gen = new Generator();
        for (int i = 0; i < RecordsNum; ++i) {
            long g = gen.gen();
            d.add(new Data(g + 10, g));
        }
    }

    private static void sort(ArrayList<Data> d) {
        Collections.sort(d);
    }

    private static void check(ArrayList<Data> d) {
        for (int i = 0; i < RecordsNum - 1; ++i) {
            if (d.get(i).value > d.get(i + 1).value) {
                System.out.println("Not sorted!");
                break;
            }
        }
    }
}
