start
    print "This program promts the user for a number of iterations to evaluate the array and a limit in each iteratio to evaluate each array item";
    print "Choose number of iterations";
    int iters = getInt();

    int[] arr = [1,2,3,4,5];
    int i = 0;

    int arrlimit;
    while (i < iters){
        print "Choose limit of array";
        arrlimit = getInt();
        arr.forEach(y->{
            if (y < arrlimit){
                print y;
            }
        });
        i = i + 1;
    }
end