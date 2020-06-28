start
    print "This program prompts the user for a number of iterations to evaluate the array and a limit in each iteratio to evaluate each array item\n";
    print "Choose number of iterations\n";
    int iters = getInt();

    int[] arr = [1,2,3,4,5];
    int i = 0;

    int arrlimit;
    while (i < iters){
        print "Choose limit of array\n";
        arrlimit = getInt();
        print "Res: \n";
        arr.forEach(y->{
            if (y < arrlimit){
                print y;
                print "\n";
            }
        });
        i = i + 1;
    }
end