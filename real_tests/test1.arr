start
    int[] arr = [1, 2, 3, 4, 5];
    double multiplier = 4;
    double sum = 0;
    arr.forEach(x->{
        sum = sum + x * multiplier;
    });

    if (sum > 40){
        print arr;
    } else {
        print "Sum by 4 not greater than 40";
    }
end