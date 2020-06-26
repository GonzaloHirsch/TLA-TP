start
    print "This program shows the array indexation";
    double[] arr = [0, 0, 0, 0, 0];
    print "This is the initial arr";
    print arr;
    print "Choose how many numbers to change";
    int nums = getInt();
    if (nums <= 0){
        print "Number has to be greater than 0";
    } else {
        int j = 0;
        int n;
        double newNum;
        while (j < nums){
            print "Choose an index";
            n = getInt();
            print "Choose the new number";
            newNum = getDouble();
            arr[n] = newNum;
            print "This is your new array";
            print arr;
            j = j + 1;
        }
    }
end