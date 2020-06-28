start
    print "This program asks the user for a multiplier and multiples each array item in 2 different ways and obtains the sum of all the items\n";
    print "The array is this\n";
    int[] arr = [1, 2, 3, 4, 5];
    print arr;
    print "Choose a double multiplier number";
    double multiplier = getDouble();
    print "Choose a limit\n";
    double limit = getDouble();
    print "Choose a message of success\n";
    str msgOk = getString();
    print "Choose a message of failure\n";
    str msgFail = getString();

    print "\n####################\n";

    double sum = 0;
    arr.forEach(x->{
        sum = sum + x * multiplier;
    });

    print "Result 1 - Sum with multiplication in each iteration";
    if (sum > limit || limit < sum){
        print msgOk;
        print "\n";
    } else {
        print msgFail;
        print "\n";
    }

    print "Result 2 - Sum with multiplication in one line";
    double[] arr2 = arr * multiplier;
    sum = 0;
    arr2.forEach(x->{
        sum = sum + x;
    });

    if (sum > limit){
        print msgOk;
    } else {
        print msgFail;
    }

    print "\n";
end