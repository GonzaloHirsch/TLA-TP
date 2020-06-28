start
    int[] arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    print "This program asks the user for a number to compare against every array item\n";
    print "The array is this: ";
    print arr;
    print "Set a number limit: ";
    int limit = getInt();
    arr.forEach(x->{
        print x;
        if (x >= limit){
            print " is over o equals the limit\n";
        } else {
            print " is bellow the limit\n";
        }
    });
end