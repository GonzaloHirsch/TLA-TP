start
    print "This program asks the user for a multiplier and multiples each array item in 3 different ways (1 - forEach multiplying in each iteration, 2 - multiplying the array with the number and then using forEach, 3 - while to iterate and multiply each time) and obtains the sum of all the items\n";
    print "The array is this:\n";
    int[] arr = [1, 2, 3, 4, 5];
    print arr;
    print "\nChoose a double multiplier number: ";
    double multiplier = getDouble();
    print "\nChoose a limit to compare the sum to: ";
    double limit = getDouble();
    print "\nChoose a message in case the sum is greater than the limit: ";
    str msgOk = getString();
    print "\nChoose a message in case the sum is smallet than the limit: ";
    str msgFail = getString();

    print "\n####################\n";

    double sum = 0;
    arr.forEach(x->{
        sum = sum + x * multiplier;
    });

    print "\nResult 1 - Sum with multiplication with forEach in each iteration: ";
    if (sum > limit || limit < sum){
        print msgOk;
        print "\n";
    } else {
        print msgFail;
        print "\n";
    }

    double[] arr2 = arr * multiplier;
    sum = 0;
    arr2.forEach(x->{
        sum = sum + x;
    });

    print "\nResult 2 - Sum with multiplication in one line: ";
    if (sum > limit){
        print msgOk;
    } else {
        print msgFail;
    }

    int i = 0;
    while (i < 5){
        sum = sum + arr[i] * multiplier;
        i = i + 1;
    }

    print "\nResult 3 - Sum with while iteration and multiplication in each iteration: ";
    if (sum > limit){
        print msgOk;
    } else {
        print msgFail;
    }
end