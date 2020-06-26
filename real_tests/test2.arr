start
    print "Set a number limit";
    int limit = getInt();
    int[] arr = [1, 2, 3, 4, 5, 6];
    arr.forEach(x->{
        if (x > limit){
            print "LIMIT BREAKER";
        } else {
            print "INSIDE LIMIT";
        }
    });
end