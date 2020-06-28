start
    print "This program evaluates operations of two arrays of size 5\n";
    double[] arr1 = [0.0,0,0,0,0];
    double[] arr2 = [0.0,0,0,0,0];
    double[] res;

    print "Choose the values for the first arrays\n";
    int i =0;
    while(i < 5){
       arr1[i] = getDouble();
       i=i+1;
    }

    print "Choose the values for the second arrays\n";
    i =0;
    while(i < 5){
        arr2[i] = getDouble();
        i = i +1;
    }

    print "Choose the operation: \n\t1. * \n\t2. + \n\t3. / \n\t4. -\n";
    int op = getInt();

    if(op == 1){
        res = arr1 * arr2;
    }
    else if(op == 2){
        res = arr1 + arr2;
    }
    else if(op == 3){
        res = arr1 / arr2;
    }
    else if(op == 4){
        res = arr1 - arr2;
    }
    else {
        print "Invalid Choice\n";
        exit();
    }

    print "Result\n";
    print res;
    
end