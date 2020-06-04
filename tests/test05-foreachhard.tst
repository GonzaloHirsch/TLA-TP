start
    double[] arr = [1.3,2,3,4,5,6,7,8,9,10];
    arr.forEach(x->{
        if (x < 3) {
            int i = 0;
            while (i < x) {
                print "I'm in a whileee!";
                i = i + 1;
            }
            print "less than 3";
            print x;
        } else if (x < 7) {
            int i = 0;
            while (i < x) {
                print "I'm in a wheeel!";
                i = i + 1;
            }
            print "less than 5";
            print x;
        } else {
            print "5 or more";
            print x;
        }
    }
    );
end