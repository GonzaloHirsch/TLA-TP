start
    int[] arr = [1, 2, 3, 4, 5, 6];
    print "This program asks the user for a number to compare against every array item";
    print "The array is this";
    print arr;
    print "Set a number limit";
    double[] arr2 = [1, 2, 3, 4];
    double[] b = arr * arr2;
    int limit = getInt();
    arr.forEach(x->{
        if (x > limit){
            print "LIMIT BREAKER";
        } else {
            print "INSIDE LIMIT";
        }
    });
end