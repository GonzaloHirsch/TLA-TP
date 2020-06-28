start
    print "This program prompts the user for a number of iterations to evaluate the array and a limit in each iteratio to evaluate each array item\n";
    print "The array is this: ";
    int[] arr = [1,2,3,4,5,6,7,8,9,10];
    print arr;
    print "Choose number of iterations: ";
    int iters = getInt();
    int i = 0;

    int arrlimit;
    while (i < iters){
        print "Choose a number to compare to: ";
        arrlimit = getInt();
        print "Items greater than "; print arrlimit; print " :";
        arr.forEach(y->{
            if (y >= arrlimit){
                print " "; print y; print " ";
            }
        });
        print "\n";
        i = i + 1;
    }
end