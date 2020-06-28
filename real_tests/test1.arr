start
    print "This program asks the user for a multiplier and multiples each array item in 2 different ways and obtains the sum of all the items";
    print "The array is this";
    int[] arr = [1, 2, 3, 4, 5];
    print arr;
    print "Choose a decimal number";
    double multiplier = getDouble();
    print "Choose a limit";
    double limit = getDouble();
    print "Choose a message of success";
    str msgOk = getString();
    print "Choose a message of failure";
    str msgFail = getString();

    print "\n####################\n";

    double sum = 0;
    arr.forEach(x->{
        sum = sum + x * multiplier;
    });

    print "Result 1";
    if (sum > limit || limit < sum){
        print msgOk;
    } else {
        print msgFail;
    }

    print "Result 2";
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
end