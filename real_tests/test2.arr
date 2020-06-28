start
    int[] arr = [5, 0, 1, 0, 1, 0];
    print "This program asks the user for a number to compare against every array item\n";
    print "The array is this\n";
    print arr;
    print "Set a number limit\n";
    int limit = getInt();
    arr.forEach(x->{
        if (!x){
            print "LIMIT BREAKER\n";
        } else {
            print "INSIDE LIMIT\n";
        }
    });


    int[] arr2 = [1, 2, 3];
    int[] arr3 = [2, 3, 4];
    int res = arr2 *. arr3;
    arr2 = arr2 *x arr3;
    print res;
    print "\n";
    print arr2;
    print "\n";
end