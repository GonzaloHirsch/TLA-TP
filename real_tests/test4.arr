start
    print "This program shows the array indexation\n";
    double[] arr = [0, 0, 0, 0, 0];
    print "This is the initial arr\n";
    print arr;
    print "Choose how many numbers to change\n";
    int nums = getInt();
    if (nums <= 0){
        print "Number has to be greater than 0\n";
    } else {
        int j = 0;
        int n;
        double newNum;
        while (j < nums){
            print "Choose an index\n";
            n = getInt();
            print "Choose the new number\n";
            newNum = getDouble();
            arr[n] = newNum;
            print "This is your new array\n";
            print arr;
            j = j + 1;
        }
    }
end